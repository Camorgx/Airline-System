#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"
#include <vector>

void init_system(Airline*& airlines, unsigned& num_of_airlines, const std::string& data_file);
Airline* search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& to, unsigned& ans_length);
bool order(Airline* airlines, const std::string& guest_name,unsigned airline, unsigned level,
           size_t order_size);
void string_split(std::vector<std::string>& ans, const std::string& source, const std::string& split = " ");
std::string to_lower(std::string in);

#endif /* utils_hpp */
