#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"
#include "Vector.hpp"

bool init_system(Airline*& airlines, unsigned& num_of_airlines, const std::string& data_file);
std::string get_help(const std::string& program_name = "Airline_System.exe", const std::string & help_command = "");
void string_split(Vector<std::string>& ans, const std::string& source, const std::string& split = " ");

void search_airline(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
void book(Airline* airlines, unsigned num_of_airlines, const std::string& airline,
          const std::string& guest_name, const std::string& level, const std::string& size);
void return_ticket(Airline* airlines, unsigned num_of_airlines, const std::string& airline,
                   const std::string& guest_name, const std::string& level);
void list_guests(Airline* airlines, unsigned num_of_airlines, const std::string& airline);
void leave_queue(Airline* airlines, unsigned num_of_airlines, std::string airline, std::string guest_name,
                 std::string level, std::string num);

#endif /* utils_hpp */
