/**
 * @file DateTime.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */
#include <string>
#include <iostream>
#include <sstream>
#include "DateTime.h"
using namespace std;
/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split( const std::string & line, int & y, int & m, int & d, int & h, int & mn, int & s);

DateTime::DateTime() {
    initDefault();
}

void DateTime::initDefault() {
    _year = 1971;
    _month = 1;
    _day = 1;
    _hour = _min = _sec = 0;
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {
    bool correct;
    int lastDay = 31;
    if(month == 4 || month == 6 || month == 9 || month == 11){
        lastDay = 30;
    } else if(month == 2){
        lastDay = 28;
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
            lastDay = 29;
        }
    }
    
    correct = (month >= 1 && month <= 12) && (day <= lastDay) && (hour >= 0 && hour < 24) 
            && (min >= 0 && min < 60) && (sec >= 0 && sec < 60);
    
    return correct;
}

void split( const std::string & line, int & y, int & m, int & d, int & h, int & mn, int & s) {
   
    string cad;
    cad = line.substr(0,4);
    
    try{
        y = stoi(cad);
        m = stoi(line.substr(5,2));
        d = stoi(line.substr(8,2));
        h = stoi(line.substr(11,2));
        mn = stoi(line.substr(14,2));
        s = stoi(line.substr(17,2));    
    } catch (...) {
        split(DATETIME_DEFAULT, y, m, d, h, mn, s);
    }

}

void DateTime::set(const std::string & line) {
    int year, month, day, hour, min, sec;
        split(line, year, month, day, hour, min, sec);
        if(isCorrect(year, month, day, hour, min, sec)) {
            split(line, _year, _month, _day, _hour, _min, _sec);
        } else {
            initDefault();
        } 
}

DateTime::DateTime(const string & line) {
    set(line);
}

int DateTime::year() const {
    return _year;
}

int DateTime::month() const {
    return _month;
}

int DateTime::day() const {
    return _day;
}

int DateTime::hour() const {
    return _hour;
}

int DateTime::min() const {
    return _min;
}

int DateTime::sec() const {
    return _sec;
}

bool DateTime::isBefore( const DateTime & one) const {
    return to_string() < one.to_string();
}

int DateTime::weekDay() const {
    int q = _day;
    int y = _year;
    int m = _month;
    if (m < 3) {
        m += 12;
        y--;
    }
    return ((q + (31 * ((m - 2)) / 12) + y + (y / 4) - (y / 100) + (y / 400)) % 7);
    
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

bool DateTime::sameDay(const DateTime & other) const {
    if(other._day == _day && other._month == _month && other._year == _year)
        return true;
    else 
        return false;
}