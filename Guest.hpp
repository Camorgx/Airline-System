#ifndef Guest_hpp
#define Guest_hpp

#include <string>

class Guest {
public:
    std::string name;
    unsigned seat[3][20];
    unsigned tickets_needed[3] = {0};
    unsigned num_of_tickets[3] = { 0 };
    
    Guest() {}
    Guest(std::string name) : name(name) {}
    const bool operator<(const Guest& b) const {
        return name < b.name;
    }
    const bool operator>(const Guest& b) const {
        return name > b.name;
    }
    const bool operator==(const Guest& b) const {
        return name == b.name && tickets_needed == b.tickets_needed
            && num_of_tickets[0] == b.num_of_tickets[0]
            && num_of_tickets[1] == b.num_of_tickets[1]
            && num_of_tickets[2] == b.num_of_tickets[2];
    }
    const bool operator!=(const Guest& b) const {
        return !(*(this) == b);
    }
};

#endif /* Guest_hpp */
