#include <iostream>
#include <cmath>

using namespace std;

//heure siderale au meridien de greenwich le 1 janvier 2000 a 12h UTC
float HSG = 18.697374558;

float TSL0;
//jour solaire = 24.065709824419
float JS = 24.065709824419;
float longitude=4;
float TSL;
int date;
int D = 0;
int D1;
int h=11;
int day = 18 ,month=3,year=2022;
bool leapYear(int year);
int dateval(int day, int month, int year);

int main(){
    cout << "Actual date: " << day <<"/" << month<<"/" << year << endl;
    cout << "Actual Time: " << h << endl;
    D1 = dateval(day, month, year);
    D = D1 - 36526;
    cout <<"D: " << D << endl;
    TSL0 = HSG + JS * (D + h / 24);
    TSL = TSL0 + (longitude/15.0);
    cout << "T0 " << TSL0 <<endl;
    TSL = fmod(TSL0, 24);
    cout << "TSL :" << TSL << endl;
    
    return 0;
}

int dateval(int day, int month, int year){
    int l = 0;
    date = (year - 2000) * 365;
    for(int i = 2000; i < year; i++){
        if(leapYear(i)){
            l++;
        }
    }
    date += (l - 1);
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
    date += 36526;
    return date;
}

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