#ifndef DATE_H
#define DATE_H



class Date {
    public:
        Date(); //initialize today
        Date(int day, int month, int year); // initialize given
        void DisplayDate();

        enum FormatType {Short, Long};
    private:
        int day, month, year;
        enum day {MONDAY, TUESDAY, WEDESNDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
        enum month {JANUARY = 31, FEBURARY = 28, MARCH = 30, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
        const string days[7] = {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"
        };
        const string months[12] {
            "January",
            "Feburary",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        }
}

#endif