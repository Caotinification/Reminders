#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

#include "DateClass/Date.hpp"

using std::cout;
using std::cin;
using std::endl;

const static string commands[] = {
    "create",
    "read"
};

const static string fileName = "reminderData.txt";

int main(int argc, char** argv) {// space is token separator of argv

    string command;
    std::fstream data;

    cout << "\t\t[REMINDERS CREATOR V0]" << endl;
    cout << "Please type \"create\" or \"read\" to create or read a reminder: ";
    cin >> command;

    if (!command.compare(commands[0])) {
        Date setDate;
        string note;
        data.open(fileName, std::ios_base::app);
        cout << "You've chosen to create a reminder." << endl;
        cout << "Please enter a reminder note: ";
        cin >> note;
        cout << "Please enter a date to set the reminder [dd/mm/yyyy]: ";
        cin >> setDate;
        data  << Date() << ':' << endl;
        data << note << " - ";
        setDate.Display(data, DateAccessories::DateFormatType::Long) << endl;
    }
    return 0;
}