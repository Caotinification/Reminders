#include <iostream>
#include <chrono>
#include <stdexcept>

#include "Date.hpp"

typedef std::tm DateParts;

using namespace DateAccessories;

static DateParts* GetToday() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    return std::localtime(&now_c);
}

Date::Date() {
	DateParts* today = GetToday();
    d = today->tm_mday;
    m = today->tm_mon + 1; // 0-11 months
    y = today->tm_year + 1900; // years since 1900
}

string Date::GetDayOfWeek() const { //calculated using Zeller's Rule
    int offsetedMonth = (m + MAX_MONTHS - 1) % (MAX_MONTHS + 1); // this makes march the first month, and feburary the last
    int millenium = y % 1000;
    int year = y - millenium;

    int weekday = d + ((MAX_MONTHS + 1) * offsetedMonth - 1)/5.0 + year + static_cast<double>(millenium)/2.0 + static_cast<double>(year)/2.0 - (2*year);
    
    return DayNames[weekday - 1];
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

bool Date::checkLeapYear() {
    return isLeapYear = y % 4 == 0;
}