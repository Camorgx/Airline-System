#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void init_system(Airline*& airlines, unsigned& num_of_airlines, const string& data_file) {
    ifstream fin; fin.open(data_file);
    fin >> num_of_airlines;
    airlines = new Airline[num_of_airlines];
    for (int i = 0; i < num_of_airlines; ++i) {
        string from, to, airline, plane;
        unsigned weekday;
        fin >> from >> to >> airline >> plane;
        fin >> weekday;
        airlines[i] = Airline(from, to, airline, plane, weekday);
    }
    sort(airlines, airlines + num_of_airlines);
    fin.close();
}

Airline* search_airline(Airline* airlines, unsigned num_of_airlines, const string& to, unsigned& ans_length) {
    auto ans = new Airline[num_of_airlines];
    ans_length = 0;
    for (int i = 0; i < num_of_airlines; ++i)
        if (airlines[i].to == to) ans[ans_length++] = airlines[i];
    if (ans_length == 0) {
        delete[] ans;
        return nullptr;
    }
    else return ans;
}

void string_split(vector<string>& ans, const string& source, const string& split) {
    auto pos2 = source.find(split);
    int pos1 = 0;
    while(pos2 != string::npos) {
        ans.push_back(source.substr(pos1, pos2 - pos1));
        pos1 = pos2 + split.size();
        pos2 = source.find(split, pos1);
    }
    if(pos1 != source.length())
        ans.push_back(source.substr(pos1));
}

bool book(Airline* airlines, const string& guest_name, unsigned airline, unsigned level,
           size_t order_size) {
    if (order_size > airlines[airline].tickets_left[level - 1])
        return false;
    airlines[airline].tickets_left[level - 1] -= order_size;
    unsigned cnt = 0;
    auto guest_node = airlines[airline].guests_ordered.find(Guest(guest_name));
    cout << "We have booked " << order_size << " tickets of level " << level 
        << " for guest " << guest_name << '.' << endl;
    cout << "Seat numbers are ";
    if (!guest_node) {
        Guest guest(guest_name);
        for (int i = 0; i < level_size[airline]; ++i) {
            if (!airlines[airline].is_ordered[level - 1][i]) {
                cout << i;
                guest.seat[level - 1][guest.num_of_tickets[level - 1]++] = i;
                airlines[airline].is_ordered[level - 1][i] = true;
                ++cnt;
                if (cnt == order_size) {
                    cout << '.' << endl;
                    break;
                }
                else cout << ", ";
            }
        }
        airlines[airline].guests_ordered.insert(guest);
    }
    else {
        auto& guest = guest_node->data;
        for (int i = 0; i < level_size[airline]; ++i) {
            if (!airlines[airline].is_ordered[level - 1][i]) {
                cout << i;
                guest.seat[level - 1][guest.num_of_tickets[level - 1]++] = i;
                airlines[airline].is_ordered[level - 1][i] = true;
                ++cnt;
                if (cnt == order_size) {
                    cout << '.' << endl;
                    break;
                }
                else cout << ', ';
            }
        }
    }
    return true;
}

std::string to_lower(std::string in) {
    for (char& i : in) i = tolower(i);
    return in;
}

bool return_ticket(Airline* airlines, const std::string& guest_name, unsigned airline, unsigned level) {
    auto guest_node = airlines[airline].guests_ordered.find(Guest(guest_name));
    if (!guest_node) {
        cout << "Sorry, we failed to find the guest in the requested airline." << endl;
        return false;
    }
    auto& guest = guest_node->data;
    if (guest.num_of_tickets[level - 1] == 0) {
        cout << guest.name << " didn't book any ticket of level " << level << '.' << endl;
        return false;
    }
    for (auto i = 0; i < guest.num_of_tickets[level - 1]; ++i)
        airlines[airline].is_ordered[level - 1][i] = false;
    airlines[airline].tickets_left[level - 1] += guest.num_of_tickets[level - 1];
    memset(guest.seat[level - 1], 0, sizeof(guest.seat[level - 1]));
    guest.num_of_tickets[level - 1] = 0;
    if (!guest.num_of_tickets[0] && !guest.num_of_tickets[1] && !guest.num_of_tickets[2])
        airlines[airline].guests_ordered.remove(guest_node);
    return true;
}

void return_ticket(Airline* airlines, unsigned num_of_airlines, const string& air,
                   const string& guest_name, const string& level) {
    int airline = find_airline(airlines, num_of_airlines, air);
    if (airline == -1) {
        cout << "Sorry, we failed to find such airline." << endl;
        return;
    }
    unsigned ticket_level;
    sscanf(level.c_str(), "%u", &ticket_level);
    if (return_ticket(airlines, guest_name, airline, ticket_level)) {
        if (!airlines[airline].guest_waiting.is_empty()) {
            for (auto ptr = airlines[airline].guest_waiting.head->next;
                ptr != airlines[airline].guest_waiting.tail; ptr = ptr->next) {
                auto& p = ptr->data;
                if (p.level_needed == ticket_level
                    && airlines[airline].tickets_left[ticket_level - 1] >= p.tickets_needed) {
                    cout << p.name << ", we have enough tickets now, do you want to book them?"
                            << "(yes/no) [yes] ";
                    while (true) {
                        string in; getline(cin, in);
                        if (in.length() == 0 || to_lower(in) == "yes") {
                            book(airlines, p.name, airline, p.level_needed, p.tickets_needed);
                            airlines[airline].guest_waiting.remove(p);
                            break;
                        }
                        else if (to_lower(in) != "no")
                            cout << R"(Please type "yes" or "no".)" << endl;
                        else break;
                    }
                }
            }
        }
    }
}

int find_airline(Airline* airlines, unsigned num_of_airlines, const string& airline) {
    unsigned i = 0;
    for (; i < num_of_airlines; ++i)
        if (airlines[i].id_airline == airline)
            break;
    if(i == num_of_airlines) return -1;
    else return int(i);
}

void list_guests(Airline* airlines, unsigned airline) {
    size_t size = airlines[airline].guests_ordered.size;
    if (size == 0) {
        cout << "No one has booked tickets." << endl;
        return;
    }
    else if (size == 1) {
        cout << "One guest has booked tickets." << endl;
    }
    else cout << size << " guests have booked tickets." << endl;
    auto p = airlines[airline].guests_ordered.head->next;
    while (p != airlines[airline].guests_ordered.tail) {
        cout << p->data.name << " booked ";
        unsigned tmp[3][2] = {0}, s = 0;
        for (int i = 0; i < 3; ++i) {
            if (p->data.num_of_tickets[i]) {
                tmp[s][0] = i + 1; //level
                tmp[s++][1] = p->data.num_of_tickets[i]; //num of tickets
            }
        }
        if (s == 1) {
            if (tmp[0][1] == 1) cout << "one ticket of level " << tmp[0][0] << '.' << endl;
            else cout << tmp[0][1] << " tickets of level " << tmp[0][0] << '.' << endl;
        }
        else if (s == 2) {
            if (tmp[0][1] == 1) cout << "one ticket of level " << tmp[0][0];
            else cout << tmp[0][1] << " tickets of level " << tmp[0][0];
            cout << " and ";
            if (tmp[1][1] == 1) cout << "one ticket of level " << tmp[1][0];
            else cout << tmp[1][1] << " tickets of level " << tmp[1][0];
            cout << "." << endl;
        }
        else {
            if (tmp[0][1] == 1) cout << "one ticket of level " << tmp[0][0];
            else cout << tmp[0][1] << " tickets of level " << tmp[0][0];
            cout << ", ";
            if (tmp[1][1] == 1) cout << "one ticket of level " << tmp[1][0];
            else cout << tmp[1][1] << " tickets of level " << tmp[1][0];
            cout << " and ";
            if (tmp[2][1] == 1) cout << "one ticket of level " << tmp[2][0];
            else cout << tmp[2][1] << " tickets of level " << tmp[2][0];
            cout << "." << endl;
        }
        p = p->next;
    }
}

void search_airline(Airline* airlines, unsigned num_of_airlines, const string& airline) {
    unsigned ans_length = 0;
    auto ans = search_airline(airlines, num_of_airlines, airline, ans_length);
    if (!ans) cout << "Sorry, we failed to find such airlines." << endl;
    else {
        cout << ans_length << " results found." << endl;
        for (int i = 0; i < ans_length; ++i) {
            cout << ans[i].id_airline << ", " << ans[i].id_plane << ", " 
                << "from " << ans[i].from << " to " << ans[i].to << ", "
                << to_string(ans[i].time) << ", " << ans[i].closest.to_string() << endl;
            for (int j = 0; j < 3; ++j) {
                cout << "Level " << j + 1 << " has ";
                if (ans[i].tickets_left[j] == 1)
                    cout << ans[i].tickets_left[j] << " ticket left." <<endl;
                else cout << ans[i].tickets_left[j] << " tickets left." <<endl;
            }
        }
        delete[] ans;
    }
}

void book(Airline* airlines, unsigned num_of_airlines, const string& air,
          const string& guest_name, const string& level, const string& size) {
    size_t order_size, order_level;
    int airline = find_airline(airlines, num_of_airlines, air);
    if (airline == -1) {
        cout << "Sorry, we failed to find such airline." << endl;
        return;
    }
    sscanf(level.c_str(), "%zd", &order_level);
    sscanf(size.c_str(), "%zd", &order_size);
    if (!book(airlines, guest_name, airline, order_level, order_size)) {
        cout << "Sorry, but there aren't enough seats. " << endl;
        unsigned len = 0;
        auto ans = search_airline(airlines, num_of_airlines,
            airlines[airline].to, len);
        if (ans) {
            cout << "But we have airlines toward the same destination that fits your acquirement:" << endl;
            for(int i = 0; i < len; ++i)
                if (ans[i].tickets_left[order_level - 1] >= order_size)
                    cout << ans[i].id_airline << ", " << ans[i].id_plane << ", "
                    << "from " << ans[i].from << " to " << ans[i].to << ", "
                    << to_string(ans[i].time) << ", " << ans[i].closest.to_string() << endl;
            delete[] ans;
        }
        cout << "Do you want to wait in queue or book another airline?" << endl;
        string in; getline(cin, in);
        if (in.length() == 0) return;
        vector<string> in_split;
        string_split(in_split, in);
        if (in_split[0] == "wait") {
            airlines[airline].guest_waiting.push(Guest(guest_name, order_level, order_size));
            cout << "You have joined the waiting queue." << endl;
        }
        else if (in_split[0] == "book") {
            if (in_split.size() != 5) {
                cout << "Please check your input." << endl;
                return;
            }
            book(airlines, num_of_airlines, in_split[1], in_split[2], in_split[3],
                in_split[4]);
        }
    }
}

void list_guests(Airline* airlines, unsigned num_of_airlines, const std::string& air) {
    int airline = find_airline(airlines, num_of_airlines, air);
    if (airline == -1) {
        cout << "Sorry, we failed to find such airline." << endl;
        return;
    }
    list_guests(airlines, airline);
}

void leave_queue(Airline* airlines, unsigned num_of_airlines, string air, string guest_name,
                 string level, string num) {
    unsigned int level_needed = 1, num_needed = 0;
    sscanf(level.c_str(), "%ud", &level_needed);
    sscanf(num.c_str(), "%ud", &num_needed);
    int airline = find_airline(airlines, num_of_airlines, air);
    if (airline == -1) {
        cout << "Sorry, we failed to find the airline." << endl;
        return;
    }
}

string get_help(const string& help_command) {
    string ans;
    if (help_command.length() == 0) {
        ans = R"(This is a simple airline system, which enables you to do some simple things about airlines.
Supported commands: exit, help, search, list, book.
Type "help [command] to get more information.
)";
    }
    else if (help_command == "exit") {
        ans = R"(Command "exit", to exit the system.
Format: exit
)";
    }
    else if (help_command == "help") {
        ans = R"(Command "help", to display general help information.
If Command is certain, display the usage of the given Command.
Format: help [Command]
)";
    }
    else if (help_command == "search") {
        ans = R"(Command "search", to search a given airline, giving its detailed information.
Format: search [Destination]
)";
    }
    else if (help_command == "list") {
        ans = R"(Command "list", to list guests who booked tickets of a given airline, giving its detailed information.
Format: list [Airline]
)";
    }
    else if (help_command == "book") {
        ans = R"(Command "book", to book certain tickets of a given airline for a given guest. If failed, you will be
asked whether the guest wants to wait in the waiting queue.
Format: book [Airline] [Guest Name] [Level of the Tickets] [Num of the Tickets]
)";
    }
    else if (help_command == "return") {
        ans = R"(Command "return", to return certain level of tickets bought by a given guest of a certain airline.
If succeeded and there are enough tickets for some people in the waiting queue, they will be asked whether they want to
book the ticketes returned by the previous guest. A guest will be removed from the guest list if all his tickets are returned.
Format: return [Airline] [Guest Name] [Level of the Tickets]
)";
    }
    else {
        ans = "Sorry, we failed to find such command.\n";
    }
    return ans;
}
