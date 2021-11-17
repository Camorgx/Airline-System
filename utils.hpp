#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"
#include <vector>

void init_system(Airline*& airlines, unsigned& num_of_airlines, const std::string& data_file);
Airline* search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& to, unsigned& ans_length);
void search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
bool book(Airline* airlines, const std::string& guest_name, unsigned airline, unsigned level,
           size_t order_size);
void book(Airline* airlines, unsigned num_of_airlines, const std::string& airline,
          const std::string& guest_name, const std::string& level, const std::string& size);
void string_split(std::vector<std::string>& ans, const std::string& source, const std::string& split = " ");
std::string to_lower(std::string in);
bool return_ticket(Airline* airlines, const std::string& guest_name, unsigned airline, unsigned level);
void list_guests(Airline* airlines, unsigned airline);
void list_guests(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
int find_airline(Airline* airlines, unsigned& num_of_airlines, const std::string& airline);

#endif /* utils_hpp */
