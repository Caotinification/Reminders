#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <limits>
#include <iomanip>

using std::string;

namespace DateAccessories {
    enum class DateFormatType {Short, Long};
}

static const int MAX_MONTHS = 12;
static const int MonthlyDays[MAX_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const char DateSeparator = '/';

static const string DayNames[7] = {
    string("Sunday"),
    string("Monday"),
    string("Tuesday"),
    string("Wednesday"),
    string("Thursday"),
    string("Friday"),
    string("Saturday")
};
static const string MonthNames[MAX_MONTHS] = {
    string("January"),
    string("February"),
    string("March"),
    string("April"),
    string("May"),
    string("June"),
    string("July"),
    string("August"),
    string("September"),
    string("October"),
    string("November"),
    string("December"),
};

using namespace DateAccessories;

std::tm* GetToday();

class Date {

    public:
        Date(); //initializes today
        Date(int day, int month, int year): d(day), m(month - 1), y(year), isLeapYear(year % 4 == 0){};

        int GetDay() const {return d;};
        int GetMonth() const {return m + 1;};
        int GetYear() const {return y;};

        Date& ChangeDate(int day, int month = 0, int year = 0);
        Date& SetTime(int hours, int minutes) {hr = hours; min = minutes; return *this;};

        Date& operator++();
        Date& operator--();

        std::ostream& Display(std::ostream& out, DateFormatType dateFormat = DateFormatType::Short) const {
            if (dateFormat != DateFormatType::Short)
                out << GetDayOfWeek() << ", " << MonthNames[m] << " " << d << ", " << y;
            else {
                out << std::setw(2) << std::setfill('0') << d << DateSeparator;
                out << std::setw(2) << std::setfill('0') << (m + 1) << DateSeparator;
                out << y;
            }
            return out;
        }

        friend std::ostream& operator<<(std::ostream& out, const Date& date) {
            return date.Display(out);
        }
        
        friend std::istream& operator>>(std::istream& in, Date& date) {
            int day = 0, month = 0, year = 0;

            in >> day;
            in.ignore(1, DateSeparator); 
            in >> month;
            in.ignore(1, DateSeparator);
            in >> year;
            
            try {
                if (month <= 0 || month > MAX_MONTHS)
                    throw std::runtime_error("ERROR: Invalid input for months. Please enter an integer from [1,12].\n");
                if (day <= 0 || day > MonthlyDays[month])
                    throw std::runtime_error("ERROR: Invalid number of days for specified month.\n");
                if (year < 2021)
                    throw std::runtime_error("ERROR: Year cannot be in the past.\n");
            }
            catch(std::runtime_error& exception) {
                std::cerr << exception.what() << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return in >> date;
            }

            date.ChangeDate(day, month - 1, year);
            return in;
        }

    private:
        string GetDayOfWeek() const; // calculated using Zeller's Congruence, returns name of day of week
        void checkLeapYear();
        int d, m, y; //months internally stored from 0-11
        int hr, min;
        bool isLeapYear;
};

#endif