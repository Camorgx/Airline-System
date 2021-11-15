#include <iostream>
#include "Airline.hpp"
#include "utils.hpp"
using namespace std;

vector<Airline> airlines;

int main(int argc, const char * argv[]) {
    init_system(airlines, "database.txt");
    while (true) {
        string input; getline(cin, input);
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
                         << ", " << i.closest.to_string() << ", ";
                    if (i.tickets_left == 1)
                        cout << i.tickets_left << " ticket left." <<endl;
                    else cout << i.tickets_left << " tickets left." <<endl;
                }

            }
        }
        else cout << "Please check your input!" << endl;
    }
    return 0;
}
