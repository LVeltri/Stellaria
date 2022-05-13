#ifndef TIME_CAL_HPP
#define TIME_CALC_HPP

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

// Variable Declaration

//Heure sidérale au méridien de greenwich le 1er janvier 2000 à 12h
float HSG = 18.697374558;
// Jour solaire
float JS = 24.065709824419;
float TSL0 = 0.0;

std::string heureSiderale;

// Functions

//Leap year boolean
bool leapYear(int year){
    bool leap = false;
    if(year % 4 == 0){
        if(year % 100 == 0){
            leap = true;
            if(year % 400 == 0){
                leap = true;
            }else{
                leap = false;
            }
        }
        leap = true;
    }else{
        leap = false;
    }
    return leap;
}

// Convert date to a int number from J2000
int dateval(int day, int month, int year){
    int date;
    // additional day
    int l = 0;
    // Calcul the nb of days pass since J2000
    date = (year - 2000) * 365;
    // Check if i year is a leap year
    for(int i = 2000; i < year; i++){
        if(leapYear(i)){
            // if leap year add 1 day supp
            l++;
        }
    }
    // Add additional day from leap year
    date += (l - 1);
    //Add days passed to the actual date;
    switch(month){
        case 1:
            date += day;
            break;
        case 2:
            date += 31 + day;
            break;
        case 3:
            date += 59 + day;
            break;
        case 4:
            date += 90 + day;
            break;
        case 5:
            date += 120 +day;
            break;
        case 6:
            date += 151 + day;
            break;
        case 7:
            date += 181 + day;
            break;
        case 8:
            date += 212 + day;
            break;
        case 9:
            date += 243 + day;
            break;
        case 10:
            date += 273 +day;
            break;
        case 11:
            date += 304 + day;
            break;
        case 12:
            date += 334 + day;
            break;
    }    
    // add J2000 date value
    date += 36526;
    return date;
}

// convert time in floating hour
float convertTime(int hour, int minutes, int seconds){
    float time = 0;
     
    time = hour + (minutes / 60.0) + (seconds / 3600.0);

    return time;
}

// converting floating hour to hh::mm::ss
std::string convertTime2(float decimalHour){
    int hours, minutes, seconds;
    hours = decimalHour;
    minutes = (decimalHour - hours) * 60;
    seconds = (((decimalHour - hours) * 60) - minutes) * 60 ;

    return heureSiderale = std::to_string(hours) + ":"+std::to_string(minutes) + ":"+std::to_string(seconds);
}

// Give the local sideral time
double sideralTime(int day, int month, int year, int hour, int minutes, int seconds, int longitude){
    double time;
    int D, D1;
    double newHour;

    newHour = convertTime(hour - 2, minutes, seconds);
    // std::cout << "New Hour: " << newHour << std::endl;

    // D1 = dateval(day, month, year);
    D = dateval(day, month, year) - 36526;
    time = fmod( HSG + (JS  * ( (double)D + (newHour / 24.0) - 0.5 )) + ((double)longitude/15.0), 24.0);

    return time;
}
#endif