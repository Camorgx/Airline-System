#include <iostream>
#include <cstdio>
#include <string>
#include "Airline.hpp"
#include "utils.hpp"
using namespace std;

vector<Airline> airlines;

int main(int argc, const char * argv[]) {
    init_system(airlines, "database.txt");
    while (true) {
        string input; getline(cin, input);
        if (input.length() == 0) continue;
        vector<string> input_split;
        string_split(input_split, input);
        if (input_split[0] == "exit") break;
        else if (input_split[0] == "search") {
            if (input_split.size() != 2) {
                cout << "Please check your input." << endl;
                continue;
            }
            vector<Airline> ans;
            search_airline(ans, airlines, input_split[1]);
            if (ans.empty()) cout << "Sorry, we failed to find such airlines." <<endl;
            else {
                cout << ans.size() << " results found." << endl;
                for (auto& i : ans) {
                    cout << i.id_airline << ", " << i.id_plane << ", " << to_string(i.time)
                         << ", " << i.closest.to_string() << endl;
                    for (int j = 0; j < 3; ++j) {
                        cout << "Level " << j + 1 << " has ";
                        if (i.tickets_left[j] == 1)
                            cout << i.tickets_left[j] << " ticket left." <<endl;
                        else cout << i.tickets_left[j] << " tickets left." <<endl;
                    }

                }

            }
        }
        else if (input_split[0] == "book") {
            if (input_split.size() != 5) {
                cout << "Please check your input." << endl;
                continue;
            }
            size_t order_size, order_level;
            unsigned i = 0;
            for (; i < airlines.size(); ++i)
                if (airlines[i].id_airline == input_split[1])
                    break;
            if(i == airlines.size()) {
                cout << "There's no such airline. Please check your input." << endl;
                continue;
            }
            sscanf(input_split[3].c_str(), "%zd", &order_level);
            sscanf(input_split[4].c_str(), "%zd", &order_size);
            if (!order(airlines, input_split[1], i, order_level, order_size)) {
                cout << "Sorry, but there aren't enough seats. Do you want to wait in queue?"
                    << "(yes/no) [yes] ";
                while (true) {
                    string in; getline(cin, in);
                    if (in.length() == 0 || to_lower(in) == "yes") {
                        airlines[i].guest_waiting.push(Guest(input_split[1]));
                        cout << "You have joined the waiting queue." << endl;
                        break;
                    }
                    else if (to_lower(in) != "no")
                        cout << R"(Please type "yes" or "no".)" << endl;
                    else break;
                }
            }
        }
        else cout << "Please check your input." << endl;
    }
    return 0;
}
