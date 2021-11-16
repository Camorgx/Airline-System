#ifndef Airline_hpp
#define Airline_hpp

#include "Guest.hpp"
#include "Queue.hpp"
#include "PriorityList.hpp"

//Every day in a week
enum class Weekday {
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};
const std::string to_string(Weekday weekday);

//Every month in a year
enum class Month {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};
std::string to_string(Month month);

class Date {
public:
    unsigned year = 2021;
    Month month = Month::October;
    unsigned day = 1;

    Date() {}
    Date(unsigned year, unsigned month, unsigned day) 
        : year(year), month((Month)month), day(day) {}
    std::string to_string();
    //duration cannot be more than 31 days
    Date operator+(unsigned duration) const;
};
const std::string to_string(Date& date);
Date get_closest_date(Weekday weekday);
const unsigned level_size[3] = {30, 50, 100};

class Airline {
public:
    //Where does the plane start from
    std::string from;
    //Where does the plain arrive in
    std::string to;
    std::string id_airline;
    std::string id_plane;
    Weekday time = Weekday::Monday;
    Date closest;
    unsigned tickets_left[3] = {level_size[0], level_size[1], level_size[2]};
    bool is_ordered[3][200] = {false};
    PriorityList guests_ordered;
    Queue guest_waiting;
    
    Airline() {}
    Airline(std::string fro, std::string t, std::string airline,
            std::string plane, unsigned weekday) {
        from = fro; to = t; id_airline = airline;
        id_plane = plane; time = (Weekday)weekday;
        closest = get_closest_date(time);
    }
    
    bool operator<(const Airline& b) const {
        return id_airline < b.id_airline;
    }
};

#endif /* Airline_hpp */
