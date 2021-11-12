#include <iostream>
#include <chrono>

#include "Date.hpp"

typedef std::tm DateParts;

using namespace DateAccessories;

DateParts* GetToday() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    return std::localtime(&now_c);
}

Date::Date() {
	DateParts* today = GetToday();
    d = today->tm_mday;
    m = today->tm_mon; // 0-11 months
    y = today->tm_year + 1900; // years since 1900
}

string Date::GetDayOfWeek() const { //calculated using Zeller's Congruence
    int day = d, month = m + 1, year = y % 100;
    int century = y - year;
    int weekday = 0;
    switch(month) {
    case 1:
        month = 13;
        year--;
        break;
    case 2:
        month = 14;
        year--;
        break;
    }
    weekday = day + 13 * (month + 1) / 5 + year + (y + century)/4 + 5*year;
    return DayNames[weekday % 7];
}

Date& Date::ChangeDate(int day, int month/*= 0*/, int year/*= 0*/){
    d = day;

    if (month > 0)
        m = month;

    if (year > 0)
        y = year;
    
    return *this;
}

Date& Date::operator++(){ // TODO: account for leap year
    d++;
    if (d > MonthlyDays[m]) {// days overflow, go to next month
        m++;
        d = 1;
        if (m > MAX_MONTHS) { // months overflow, go to next year
            m = 1;
            y++; // happy new year
            this->checkLeapYear();
        }
    }
    return *this;
}

Date& Date::operator--(){
    d--;
    if (d <= 0) {// days underflow, go to previous month
        m--;
        d = MonthlyDays[m];
        if (m <= 0) { // months underflow, go to last year
            m = MAX_MONTHS;
            y--;
            this->checkLeapYear();
        }
    }
    return *this;
}

void Date::checkLeapYear() {
    isLeapYear = y % 4 == 0;
}