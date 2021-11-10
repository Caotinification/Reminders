#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

using std::string;

namespace DateAccessories {
    enum class DateFormatType {Short, Long};

    const int MAX_MONTHS = 12;
    const int MonthlyDays[MAX_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    const char DateSeparator = '/';

    string DayNames[7] = {
        string("Sunday"),
        string("Monday"),
        string("Tuesday"),
        string("Wednesday"),
        string("Thursday"),
        string("Friday"),
        string("Saturday")
    };

    string MonthNames[MAX_MONTHS] = {
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
}

using namespace DateAccessories;

class Date {

    public:
        Date(); //initializes today
        Date(int day, int month, int year): d(day), m(month - 1), y(year), isLeapYear(year % 4 == 0){};

        int GetDay() const {return d;};
        int GetMonth() const {return m + 1;};
        int GetYear() const {return y;};

        string GetDayOfWeek() const; // calculated using Zeller's Rule, returns name of day of week

        Date& ChangeDate(int day, int month = 0, int year = 0);

        Date& operator++();
        Date& operator--();

        std::ostream& Display(std::ostream& out, DateFormatType dateFormat = DateFormatType::Short) const {
            if (dateFormat != DateFormatType::Short)
                out << MonthNames[m + 1] << " " << d << ", " << y;
            else
                out << d << DateSeparator << m + 1 << DateSeparator << y;
            return out;
        }

        friend std::ostream& operator<<(std::ostream& out, const Date& date) {
            return date.Display(out);
        }
        friend std::istream& operator>>(std::istream& in, Date& date) {
            int day = 0, month = 0, year = 0;

            in >> day;
            in >> month;
            in >> year;

            try {
                if (month <= 0 || month > MAX_MONTHS)
                    throw std::runtime_error("ERROR: Invalid input for months. Please enter an integer from [1,12].\n");
                if (day <= 0 || MonthlyDays[month] > day)
                    throw std::runtime_error("ERROR: Invalid number of days for specified month.\n");
            }
            catch(std::runtime_error& exception) {
                std::cerr << exception.what() << std::endl;
                return in >> date;
            }

            date.ChangeDate(day, month, year);
            return in;
        };
    private:
        bool checkLeapYear();
        int d, m, y; // months stored from 0-11
        bool isLeapYear;
};

#endif