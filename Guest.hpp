#ifndef Guest_hpp
#define Guest_hpp

#include <string>
#include <utility>

class Guest {
public:
    std::string name;
    unsigned seat[3][20] = {0};
    unsigned tickets_needed = 0, level_needed = 1;
    unsigned num_of_tickets[3] = {0};
    
    Guest() = default;
    explicit Guest(std::string name) : name(std::move(name)) {}
    bool operator<(const Guest& b) const {
        return name < b.name;
    }
    bool operator>(const Guest& b) const {
        return name > b.name;
    }
    bool operator==(const Guest& b) const {
        return name == b.name;
    }
    bool operator!=(const Guest& b) const {
        return !(*(this) == b);
    }
};

#endif /* Guest_hpp */
