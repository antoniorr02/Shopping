/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods read and write To be implemented by students 
     * remove rawFilters is not longer used, -> deprecated
 */


#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include "DateTime.h"
#include "EventSet.h"
#include <iostream>

using namespace std;

Event NULL_EVENT = Event();

/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to llok for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name) {
    for (int i = 0; i < n_array; i++) {
        if (array[i] == name)
            return i;
    }
    return -1;
}

void EventSet::copy_to(Event *dest) const{
    for (int i = 0; i < size(); i++)
         dest[i] = _events[i];
    // size = _nEvent
}

void EventSet::copy(const EventSet &orig){
    for (int i = 0; i < orig.size(); i++)
        _events[i] = orig.at(i);
}

void EventSet::reallocate(unsigned size) {
    Event *aux = _events;
    _events = new Event[size];
    for (int i = 0; i < _nEvents; i++) {
        _events[i] = aux[i];
    }
    delete[] aux;
} 

void EventSet::deallocate() {
    if (_events != nullptr) {
        delete[] _events;
        _events = nullptr;
    } // Evitar hacer delete a nullptr que es un error.
}

EventSet::EventSet() {
    _nEvents = 0;
    _capacity = 0;
    _events = nullptr;
}

EventSet::EventSet(const EventSet & orig){
    _nEvents = orig.size();
    _capacity = orig._capacity;
    _events = new Event[_capacity];
    copy(orig);
}

int EventSet::size() const {
    return _nEvents;
}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

void EventSet::clear() {
    _nEvents = 0;
    _capacity = 0;
    deallocate();
}

int EventSet::add(const Event & e) {
    int n = 0;
    if (_nEvents >= _capacity) {
        _capacity = _capacity*2 + 1;
        reallocate(_capacity);
    }
    
    _events[_nEvents] = e;
    _nEvents++;
    n = 1;
    
    return n;
}

int EventSet::add(const std::string& line) {
    Event e(line);
    return add(e);
}

const Event & EventSet::at(int pos) const {
    if (pos < _nEvents && pos >= 0)
        return _events[pos];
    else
        return NULL_EVENT;

    //assert(pos <= _nEvents && pos >= 0);
}

void EventSet::write(ofstream &os) const {
    for (int i = 0; i < size(); i++) {
        at(i).write(os);
        os << endl;
    }
}

EventSet & EventSet::operator=(const EventSet & one) {
    clear();
    _nEvents = one.size();
    _capacity = one._capacity;
    _events = new Event [_capacity];
    copy(one);
    return *this;
}

EventSet::~EventSet(){
    clear();
}

bool EventSet::read(ifstream &is, int nelements) {
    bool success = true;
    Event one;
    clear();
    for (int i = 0; i < nelements && success; i++) {
        one.read(is);
        if (is.eof())
            success = false;
        if (!one.isEmpty()) // whenever all data are correct
            success = add(one); // check if the event fit int the eventSet
    }
    return success;
}
// external functions

float sumPrice(const EventSet & evSet) {
    double suma = 0;
    Event eventos;
    for (int i = 0; i < evSet.size(); i++) {
        eventos.set((evSet.at(i)).to_string());
        suma += stod(eventos.getField("Price"));
    }
    return suma;
    
}


void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    string value;
    n_values = 0;
    for (int i = 0; i < es.size(); i++) {
        value = es.at(i).getField(field);
        if (field != "DateTime") {
            if (findString(values, n_values, value) == -1)
                values[n_values++] = value;
        } else {
            DateTime dtValue(value);
            bool found=false;
            for (int d=0;d<n_values && !found; d++) {
                DateTime dtRecord;
                dtRecord.set(values[d]);
                if (dtRecord.sameDay(dtValue))
                    found=true;
            }
            if (! found) {
                value[11] = value[12] = value[14] = value[15] = value[17] = value[18] = '0';
                values[n_values++] = value;
            }
        }
    }

} // n_values muestra el número de @field diferentes que se han metido.

EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    EventSet eventos_validos;
    for (int i = 0; i < es.size(); i++) {
        if (es.at(i).getField(field) == value)
            eventos_validos.add(es.at(i).to_string());
    }
    return eventos_validos;
}