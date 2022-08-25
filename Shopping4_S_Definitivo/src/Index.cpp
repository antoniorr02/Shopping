/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Index.h"

using namespace std;

void Index::copy_to(Pair *dest) {
    for (int i = 0; i < size(); i++)
        dest[i] = _entries[i];
}

void Index::copy(const Index &orig) {
    setIOnWhich(orig.getIOnWhich());
    for (int i = 0; i < orig.size(); i++)
        _entries[i] = orig.at(i);
}

Index::Index(int onBrand) {
    setIOnWhich(onBrand);
    _nEntries = 0;
    _maxEntries = 0;
    _entries = nullptr;
}

Index::Index(const Index & orig) {
    _nEntries = orig.size();
    _maxEntries = orig._maxEntries;
    _entries = new Pair[_maxEntries];
    copy(orig);
}

void Index::setIOnWhich(int val) {
    if (val == 1)
        _onBrand = val;
    else
        _onBrand = 0;
}

void Index::reallocate(int size) {
    Pair *aux = _entries;
    _entries = new Pair[size];
    for (int i = 0; i < _nEntries; i++) {
        _entries[i] = aux[i];
    }
    delete[] aux;
}

void Index::deallocate() {
    if (_entries != nullptr) {
        delete[] _entries;
        _entries = nullptr;
    } // Evita hacer delete a nullptr que es un error.
}

int Index::size() const {
    return _nEntries;
}

void Index::clear() {
    _nEntries = 0;
    _maxEntries = 0;
    deallocate();
}

int Index::getIOnWhich() const {
    return _onBrand;
}

int Index::add(const Pair & pair) {
    int correcto = 0;
    if (!pair.isEmpty()) {
        if (_nEntries >= _maxEntries) {
            _maxEntries = _maxEntries * 2 + 1;
            reallocate(_maxEntries);
        }

        int pos = upper_bound(pair.getKey());
        for (int i = _nEntries; i > pos; i--) {
            _entries[i] = _entries[i - 1];
        } // Desplazamos los elementos a la derecha de la pos.
        _entries[pos] = pair;
        _nEntries++;
        correcto = 1;
    }

    return correcto;
}

/**
 * @brief Build the index using the Brand o the userID as searching key
 * @param evSet origin
 */
void Index::build(const EventSet & evSet, int onBrand) {
    clear();
    setIOnWhich(onBrand);
    Pair pair;

    for (int i = 0; i < evSet.size(); i++) {
        if (_onBrand == 1) {
            pair.set(evSet.at(i).getBrand(), i);
        } else if (_onBrand == 0) {
            pair.set(evSet.at(i).getUserID(), i);
        }
        if (pair.getKey() != "") {
            add(pair);
        }
    }

}

/**
 * @brief Returns the position to the first element in the Index
 * which is not considered to go before key (i.e., either it is equivalent is the first one
 * or it goes after), look at the example.
 * @param key the searching key a string
 * example: // 10 20 30 30 40 50 60 70
 * low_bound(30) ....^
 * low_bound(35) ..........^
 * @return a position in the Index
 */

/* la solucion propuesta está basada en la busqueda binaria pero con claves duplicadas*/

int Index::lower_bound(const std::string & key) const {

    int pos = 0;
    bool found = false, found_1 = false;
    if (_nEntries == 0) {
        pos = 0;
    } else {
        int inf = 0, sup = _nEntries - 1, center;
        while (inf <= sup && !found) {
            center = (inf + sup) / 2;
            if (_entries[center].getKey() == key) {
                pos = center;
                found = true;
            } else if (_entries[center].getKey() < key) inf = center + 1;
            else sup = center - 1;
        }

        if (found) {
            for (int i = pos - 1; i >= 0 && !found_1; i--) {
                if (_entries[i].getKey() != key) {
                    pos = i + 1;
                    found_1 = true;
                }
            }
            if (!found_1)
                pos = 0;
        } else {
            pos = sup;
        }
    }

    return pos;

}
//

/**
 * @brief Returns the position to the first element in the Index which is considered to go after val.
 * look at the example.
 * example: // 10 20 30 30 40 50 60 70
 * upper_bound(30) ........^
 * upper_bound(35) ........^
 * @param key the searching key a string
 * @return a position in the Index
 */
int Index::upper_bound(const std::string & key) const {

    int pos = 0;
    bool found = false, found_1 = false;
    int inf = 0, sup = _nEntries - 1, center;
    while (inf <= sup && !found) {
        center = (inf + sup) / 2;
        if (_entries[center].getKey() == key) {
            pos = center;
            found = true;
        } else if (_entries[center].getKey() < key) inf = center + 1;
        else sup = center - 1;
    }

    if (found) {
        for (int i = pos; i < _nEntries && !found_1; i++) {
            if (_entries[i].getKey() != key) {
                pos = i;
                found_1 = true;
            }
        }
        if (!found_1)
            pos = _nEntries;
    } else {
        pos = inf;
    }

    return pos;

}

const Pair & Index::at(const int pos) const {
    if (pos >= 0 && pos < MAXEVENT) {
        return _entries[pos];
    } else {
        return NULL_PAIR;
    }
}

Pair & Index::at(const int pos) {
    if (pos >= 0 && pos < MAXEVENT) {
        return _entries[pos];
    } else {
        return NULL_PAIR;
    }
}

void Index::print()const {
    for (int i = 0; i < _nEntries; i++)
        cout << _entries[i].to_string() << endl;
}

Index & Index::operator=(const Index & one) {
    clear();
    _nEntries = one.size();
    _maxEntries = one._maxEntries;
    _entries = new Pair [_maxEntries];
    copy(one);
    return *this;
}

Index::~Index() {
    clear();
}

// external functions

Event getEvent(const EventSet & evSet, const Index & indx, const int pos) {
    return evSet.at(indx.at(pos).getPos());
}

void write(ofstream & os, const EventSet & evSet, const Index & indx) {
    if (os.is_open()) {
        for (int i = 0; i < indx.size(); i++) {
            os << getEvent(evSet, indx, i).to_string() << endl;
        }
    } else {
        os << "Error in call" << endl;
    }
}
// external functions

Index rawFilterIndex(const EventSet &evSet, const Index &indx, const std::string &field, const std::string & value) {

    Index pair_validos(indx.getIOnWhich());

    if ((field == "UserID" && indx.getIOnWhich() == 0) || (field == "Brand" && indx.getIOnWhich() == 1)) {
        int pos_ini = indx.lower_bound(value);
        int pos_fin = indx.upper_bound(value);
        for (int i = pos_ini; i < pos_fin; i++) {
            pair_validos.add(indx.at(i));
        }
    } else if (field == "DateTime") {
        DateTime aux;
        aux.set(value);
        for (int i = 0; i < indx.size(); i++) {
            if (getEvent(evSet, indx, i).getDateTime().sameDay(aux)) {
                pair_validos.add(indx.at(i));
            }
        }
    } else {
        for (int i = 0; i < indx.size(); i++) {
            if (getEvent(evSet, indx, i).getField(field) == value) {
                pair_validos.add(indx.at(i));
            }
        }
    }

    return pair_validos;

}

float sumPrice(const EventSet &evSet, const Index &indx) {
    float suma = 0;
    for (int i = 0; i < indx.size(); i++) {
        suma += getEvent(evSet, indx, i).getPrice();
    }
    return suma;
}