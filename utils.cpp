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
    if (!guest_node) {
        Guest guest(guest_name);
        for (int i = 0; i < level_size[airline]; ++i) {
            if (!airlines[airline].is_ordered[level - 1][i]) {
                guest.seat[level - 1][guest.num_of_tickets[level - 1]++] = i;
                airlines[airline].is_ordered[level - 1][i] = true;
                ++cnt;
                if (cnt == order_size) break;
            }
        }
        airlines[airline].guests_ordered.insert(guest);
    }
    else {
        auto& guest = guest_node->data;
        for (int i = 0; i < level_size[airline]; ++i) {
            if (!airlines[airline].is_ordered[level - 1][i]) {
                guest.seat[level - 1][guest.num_of_tickets[level - 1]++] = i;
                airlines[airline].is_ordered[level - 1][i] = true;
                ++cnt;
                if (cnt == order_size) break;
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
    return true;
}

void return_ticket(Airline* airlines, unsigned num_of_airlines, const string& airline,
                   const string& guest_name, const string& level) {

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
            cout << ans[i].id_airline << ", " << ans[i].id_plane << ", " << to_string(ans[i].time)
                 << ", " << ans[i].closest.to_string() << endl;
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
        cout << "Sorry, but there aren't enough seats. Do you want to wait in queue?"
             << "(yes/no) [yes] ";
        while (true) {
            string in; getline(cin, in);
            if (in.length() == 0 || to_lower(in) == "yes") {
                airlines[airline].guest_waiting.push(Guest(guest_name));
                cout << "You have joined the waiting queue." << endl;
                break;
            }
            else if (to_lower(in) != "no")
                cout << R"(Please type "yes" or "no".)" << endl;
            else break;
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
