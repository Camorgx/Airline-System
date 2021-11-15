//
//  Airline.hpp
//  航空客运订票系统
//
//  Created by 曹高翔 on 2021/10/11.
//

#ifndef Airline_hpp
#define Airline_hpp

#include "Guest.hpp"
#include "Queue.hpp"
#include "PriorityList.hpp"

//一周中的每一天
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

//一年中的每个月
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
const std::string to_string(Month month);

//日期
class Date {
public:
    //年份
    unsigned year = 2021;
    //月份
    Month month = Month::October;
    //日
    unsigned day = 1;

    Date() {}
    Date(unsigned year, unsigned month, unsigned day) 
        : year(year), month((Month)month), day(day) {}
    //格式化输出
    const std::string to_string();
    //duration为一个月（31天）之内的天数
    Date operator+(unsigned duration) const;
};
const std::string to_string(Date& date);
Date get_closest_date(Weekday weekday);

class Airline {
public:
    //始发站
    std::string from;
    //终点站
    std::string to;
    //航班号
    std::string id_airline;
    //飞机号
    std::string id_plane;
    //飞行时间
    Weekday time = Weekday::Monday;
    //最近一天航班的日期
    Date closest;
    //最近一天航班的余票数
    unsigned tickets_left = 0;
    //已订票的客户名单
    PriorityList guests_ordered;
    //候补客户名单
    Queue guest_waiting;
    
    Airline() {}
    Airline(std::string fro, std::string t, std::string airline,
            std::string plane, unsigned weekday, unsigned left) {
        from = fro; to = t; id_airline = airline;
        id_plane = plane; time = (Weekday)weekday;
        closest = get_closest_date(time);
        tickets_left = left;
    }
    
    bool operator<(const Airline& b) const {
        return id_airline < b.id_airline;
    }
};

#endif /* Airline_hpp */
