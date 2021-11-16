#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"

void init_system(std::vector<Airline>& airlines, const std::string& data_file);
void search_airline(std::vector<Airline>& ans, std::vector<Airline>& airlines, const std::string& to);
bool order(std::vector<Airline>& airlines, const std::string& guest_name,unsigned airline, unsigned level,
           size_t order_size);
void string_split(std::vector<std::string>& ans, const std::string& source, const std::string& split = " ");
std::string to_lower(std::string in);

#endif /* utils_hpp */
