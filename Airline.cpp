#include "Airline.hpp"

const std::string Weekday_name[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
const std::string to_string(Weekday weekday) {
    return Weekday_name[int(weekday) - 1];
}

const std::string Month_name[] = {
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
std::string to_string(Month month) {
    return Month_name[int(month) - 1];
}

std::string Date::to_string() {
    char tmp[50];
    std::string st;
    if (day >= 20 || day <= 10)
        switch (day % 10) {
            case 1 : st = "st"; break;
            case 2 : st = "nd"; break;
            case 3 : st = "rd"; break;
            default: st = "th";
        }
    else st = "th";
    std::sprintf(tmp, "%s %d%s, %d", ::to_string(month).c_str(), 
        day, st.c_str(), year);
    return std::string(tmp);
}

const std::string to_string(Date& date) {
    return date.to_string();
}

Date Date::operator+(unsigned duration) const {
    int nyear = year, nmonth = int(month), nday = day + duration;
    if (nmonth == 4 || nmonth == 6 || nmonth == 9 || nmonth == 11) {
        if (nday > 30) { nday -= 30; nmonth += 1; }
    }
    else if (nmonth == 2) {
        if ((nyear % 4 == 0 && nyear % 100 != 0) ||
            nyear % 400 == 0) {
            if (nday > 29) { nday -= 29; nmonth += 1; }
        }
        else if (nday > 28) { nday -= 28; nmonth += 1; }
    }
    else if (nday > 31) { nday -= 31; nmonth += 1; }
    if (nmonth == 4 || nmonth == 6 || nmonth == 9 || nmonth == 11) {
        if (nday > 30) { nday -= 30; nmonth += 1; }
    }
    else if (nmonth == 2) {
        if ((nyear % 4 == 0 && nyear % 100 != 0) ||
            nyear % 400 == 0) {
            if (nday > 29) { nday -= 29; nmonth += 1; }
        }
        else if (nday > 28) { nday -= 28; nmonth += 1; }
    }
    if (nmonth > 12) { nmonth -= 12; nyear += 1; }
    return Date(nyear, nmonth, nday);
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
