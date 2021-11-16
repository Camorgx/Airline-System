#ifndef Guest_hpp
#define Guest_hpp

#include <string>
#include <vector>

class Guest {
public:
    //姓名
    std::string name;
    //座位等级
    unsigned level = 1;
    //订的座位号
    std::vector<unsigned> seat;
    //需要的余票数
    unsigned tickets_needed = 0;
    
    Guest() {}
    Guest(std::string name, unsigned num_of_tickets = 0,
        unsigned level = 1, std::vector<unsigned> seat = {},
        unsigned tickets_needed = 0) 
    : name(name),
        level(level), seat(seat), tickets_needed(tickets_needed)
    {}
    const bool operator<(const Guest& b) const {
        return name < b.name;
    }
    const bool operator>(const Guest& b) const {
        return name > b.name;
    }
    const bool operator==(const Guest& b) const {
        return name == b.name && level == b.level 
            && seat == b.seat && tickets_needed == b.tickets_needed;
    }
    const bool operator!=(const Guest& b) const {
        return !(*(this) == b);
    }
    //订票数
    unsigned num_of_tickets() {
        return unsigned(seat.size());
    }
};

#endif /* Guest_hpp */
