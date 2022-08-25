/**
 * @file Event.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods print and read To be implemented by students 
 * 
 */
#include <fstream>
#include <string>
#include "Event.h"
using namespace std;

Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

Event::Event(const string &line) {
    set(line);
}

DateTime Event::getDateTime() const  {
    return _dateTime;
}

string Event::getType() const {
    return _type;
}

string Event::getProductID() const {
    return _prod_id;
}

string Event::getCategoryID() const {
    return _cat_id;
}

string Event::getCategoryCode() const {
    return _cat_cod;
}

string Event::getBrand() const {
    return _brand;
}

double Event::getPrice() const {
    return _price;
}

string Event::getUserID() const {
    return _user_id;
}

string Event::getSession() const {
    return _session;
}

void Event::setDateTime(const string & time) {
    _dateTime.set(time);
}

void Event::setType(const std::string & type) {
    bool correcto = false;
    for(int i = 0; i < 4 && correcto == false; i++){
        if(VALID_TYPES[i] == type){
            correcto = true;
        } 
    }  
    
    if(correcto){
        _type = type;
    } else {
        _type = VALID_TYPES[0];
    }
}

void Event::setProductID(const std::string & prod_id) {
    if(prod_id != ""){
        _prod_id = prod_id; 
    } else {
        _prod_id = EMPTY_FIELD;
    } 
 }

void Event::setCategoryID(const std::string & cat_id) {
    _cat_id = cat_id; 
}

void Event::setCategoryCode(const std::string & cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string & brand) {
    _brand = brand;
}

void Event::setPrice(const double price) {
    if(price >= 0)
        _price = price; 
    else 
        _price = -1.000000;
}

void Event::setUserID(const std::string  &user_id) {
    _user_id = user_id; 
}

void Event::setSession(const std::string & session) {
    if(session != "")
        _session = session;
    else
        _session = EMPTY_FIELD;
}

void Event::set(const std::string & line) {
    string date, time, data;
    int pos, posn; // aux for the beginning of the fields

    pos = 0;
    posn = line.find(',', pos); // beginning of the next field
    for (int nfield = 0; nfield < 8 && posn != string::npos; nfield++) {
        data = line.substr(pos, posn - pos);
        pos = posn + 1;
        switch (nfield) {
            case 0:
                setDateTime(data);
                break;
            case 1:
                setType(data);
                break;
            case 2:
                setProductID(data);
                break;
            case 3:
                setCategoryID(data);
                break;
            case 4:
                setCategoryCode(data);
                break;
            case 5:
                setBrand(data);
                break;
            case 6:
                setPrice(stod(data));
                break;
            case 7:
                setUserID(data);
                break;
        }
        posn = line.find(',', pos); // beginning of the next field
    }
    // the last field does not have comma
    posn = line.length();
    data = line.substr(pos, posn - pos);
    setSession(data);
//    int a, b, c, d, e, f, g, h;
//    a = line.find(",");
//    b = line.substr(a + 1, line.length()).find(",") + a + 1;
//    c = line.substr(b + 1, line.length()).find(",") + b + 1;
//    d = line.substr(c + 1, line.length()).find(",") + c + 1;
//    e = line.substr(d + 1, line.length()).find(",") + d + 1;
//    f = line.substr(e + 1, line.length()).find(",") + e + 1;
//    g = line.substr(f + 1, line.length()).find(",") + f + 1;
//    h = line.substr(g + 1, line.length()).find(",") + g + 1;
//      
//    double x = stod(line.substr(f + 1,g-f));
//    
//    setDateTime(line.substr(0,a));
//    setType(line.substr(a +1,b-a-1)); // El sumar 1 a cada componente es para quitar la coma.
//    setProductID(line.substr(b +1,c-b-1));
//    setCategoryID(line.substr(c +1,d-c-1));
//    setCategoryCode(line.substr(d + 1,e-d-1));
//    setBrand(line.substr(e + 1,f-e-1));
//    setPrice(x);
//    setUserID(line.substr(g + 1,h-g-1));
//    setSession(line.substr(h + 1,line.length()-h)); // Este era mi código, lo he comentado 
    // porque me abortaba el test y no quiero borrarlo  _03_Advanced.Integrated_ErrorData
    // LO SUSTITUYO POR EL CÓDIGO QUE SE NOS DIO PARA CORREGIR SHOPPING 2.
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
//    string a1 = (line.substr(0,a)); // Usado para comprobar valores en debbuger.
//    string a2 = (line.substr(a +1,b-a-1));
//    string a3 = (line.substr(b +1,c-b-1));
//    string a4 = (line.substr(c +1,d-c-1));
//    string a5 = (line.substr(d + 1,e-d-1));
//    string a6 = (line.substr(e + 1,f-e-1));
//    int pfkr = (x);
//    string a7 = (line.substr(g + 1,h-g-1));
//    string a8 = (line.substr(h + 1,line.length()-h));
    
}// Buscar "," para hacer varios strings para cada dato.


bool Event::isEmpty() const {
    if(_prod_id == EMPTY_FIELD || _brand == EMPTY_FIELD || 
            _user_id == EMPTY_FIELD || _session == EMPTY_FIELD)
        return true;
    else
        return false;
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
//    salida = salida +"," + DAYNAME[this->getDateTime().weekDay()];
    return salida;
}

std::string Event::getField(const std::string &field) const{
    string result = EMPTY_FIELD;
    if (field == "DateTime") {
        result = getDateTime().to_string();
    } else if (field == "Type") {
        result = getType();
    } else if (field == "ProductID") {
        result = getProductID();
    } else if (field == "CategoryID") {
        result = getCategoryID();
    } else if (field == "CategoryCode") {
        result = getCategoryCode();
    } else if (field == "Brand") {
        result = getBrand();
    } else if (field == "Price") {
        result = std::to_string(getPrice());
    } else if (field == "UserID") {
        result = getUserID();
    } else if (field == "Session") {
        result = getSession();
    }
    return result;
}

void Event::write(ofstream &os) const {
    os << this->to_string();    
}

void Event::read(ifstream &is) {
    string line;
    getline(is,line); 
    set(line); 
}