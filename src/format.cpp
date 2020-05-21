#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hour;
    long minute;
    long second;
    string hourString;
    string minuteString;
    string secondString;
    hour=seconds/3600;
    if(hour<10){
    hourString="0"+to_string(hour);}
    else {hourString=to_string(hour);}
    minute=(seconds-hour*3600)/60;
    if(minute<10){
    minuteString="0"+to_string(minute);}
    else {minuteString=to_string(minute);}
    second=seconds-hour*3600-minute*60;
    if(second<10){
    secondString="0"+to_string(second);}
    else {secondString=to_string(second);}
    return hourString+":"+minuteString+":"+secondString;
    
}