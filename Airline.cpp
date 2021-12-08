#include "Airline.hpp"
#include <ctime>
using namespace std;

const string Weekday_name[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
string to_string(Weekday weekday) {
    return Weekday_name[int(weekday) - 1];
}

const string Month_name[] = {
    "January",
    "February",
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
};
string to_string(Month month) {
    return Month_name[int(month) - 1];
}

string Date::to_string() const {
    char tmp[50];
    string st;
    if (day >= 20 || day <= 10)
        switch (day % 10) {
            case 1 : st = "st"; break;
            case 2 : st = "nd"; break;
            case 3 : st = "rd"; break;
            default: st = "th";
        }
    else st = "th";
    sprintf(tmp, "%s %d%s, %d", ::to_string(month).c_str(), 
        day, st.c_str(), year);
    return {tmp};
}

string to_string(Date& date) {
    return date.to_string();
}

Date Date::operator+(unsigned duration) const {
    int n_year = int(year), n_month = int(month), n_day = day + duration;
    if (n_month == 4 || n_month == 6 || n_month == 9 || n_month == 11) {
        if (n_day > 30) { n_day -= 30; n_month += 1; }
    }
    else if (n_month == 2) {
        if ((n_year % 4 == 0 && n_year % 100 != 0) ||
            n_year % 400 == 0) {
            if (n_day > 29) { n_day -= 29; n_month += 1; }
        }
        else if (n_day > 28) { n_day -= 28; n_month += 1; }
    }
    else if (n_day > 31) { n_day -= 31; n_month += 1; }
    if (n_month == 4 || n_month == 6 || n_month == 9 || n_month == 11) {
        if (n_day > 30) { n_day -= 30; n_month += 1; }
    }
    else if (n_month == 2) {
        if ((n_year % 4 == 0 && n_year % 100 != 0) ||
            n_year % 400 == 0) {
            if (n_day > 29) { n_day -= 29; n_month += 1; }
        }
        else if (n_day > 28) { n_day -= 28; n_month += 1; }
    }
    if (n_month > 12) { n_month -= 12; n_year += 1; }
    return {static_cast<unsigned int>(n_year), static_cast<unsigned int>(n_month),
            static_cast<unsigned int>(n_day)};
}

Date get_closest_date(Weekday weekday) {
    time_t t = time(nullptr);
    tm* tme = localtime(&t);
    int now_week_day = tme->tm_wday;
    if (now_week_day == 0) now_week_day = 7;
    if (int(weekday) > now_week_day)
        return Date(tme->tm_year + 1900, tme->tm_mon + 1,
                    tme->tm_mday) + (int(weekday) - now_week_day);
    else if (int(weekday) == now_week_day)
        return Date(tme->tm_year + 1900, tme->tm_mon + 1,
                    tme->tm_mday) + 7;
    else return Date(tme->tm_year + 1900, tme->tm_mon + 1,
                     tme->tm_mday) + (7 + int(weekday) - now_week_day);
}
