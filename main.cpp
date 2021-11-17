#include <iostream>
#include <string>
#include "Airline.hpp"
#include "utils.hpp"
using namespace std;

Airline* airlines;
unsigned num_of_airlines;

int main(int argc, const char * argv[]) {
    init_system(airlines, num_of_airlines, "database.txt");
    while (true) {
        string input; getline(cin, input);
        if (input.length() == 0) continue;
        vector<string> input_split;
        string_split(input_split, input);
        if (input_split[0] == "exit") break;
        //search Destination
        else if (input_split[0] == "search") {
            if (input_split.size() != 2) {
                cout << "Please check your input." << endl;
                continue;
            }
            search_airline(airlines, num_of_airlines, input_split[1]);
        }
        //book Airline Guest Level Num
        else if (input_split[0] == "book") {
            if (input_split.size() != 5) {
                cout << "Please check your input." << endl;
                continue;
            }
            book(airlines, num_of_airlines, input_split[1], input_split[2], input_split[3],
                 input_split[4]);
        }
        //list Airline
        else if (input_split[0] == "list") {
            if (input_split.size() != 2) {
                cout << "Please check your input." << endl;
                continue;
            }
            list_guests(airlines, num_of_airlines, input_split[1]);
        }
        else cout << "Please check your input." << endl;
    }
    return 0;
}
