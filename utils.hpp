#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"
#include <vector>

bool init_system(Airline*& airlines, unsigned& num_of_airlines, const std::string& data_file);
std::string get_help(const std::string& program_name = "Airline_System.exe", const std::string & help_command = "");
std::string to_lower(std::string in);

Airline* search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& to, unsigned& ans_length);
void search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
bool book(Airline* airlines, const std::string& guest_name, unsigned airline, unsigned level,
           size_t order_size);
void book(Airline* airlines, unsigned num_of_airlines, const std::string& airline,
          const std::string& guest_name, const std::string& level, const std::string& size);
void string_split(std::vector<std::string>& ans, const std::string& source, const std::string& split = " ");
bool return_ticket(Airline* airlines, const std::string& guest_name, unsigned airline, unsigned level);
void return_ticket(Airline* airlines, unsigned num_of_airlines, const std::string& airline,
                   const std::string& guest_name, const std::string& level);
void list_guests(Airline* airlines, unsigned airline);
void list_guests(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
int find_airline(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
void leave_queue(Airline* airlines, unsigned num_of_airlines, std::string airline, std::string guest_name,
                 std::string level, std::string num);

#endif /* utils_hpp */
