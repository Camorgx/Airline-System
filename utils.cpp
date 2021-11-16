#include "utils.hpp"
#include <fstream>
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

bool order(Airline* airlines, const string& guest_name, unsigned airline, unsigned level,
           size_t order_size) {
    if (order_size > airlines[airline].tickets_left[level - 1])
        return false;
    airlines[airline].tickets_left[level - 1] -= order_size;
    unsigned cnt = 0;
    Guest guest(guest_name);
    for (int i = 0; i < level_size[airline]; ++i) {
        if (!airlines[airline].is_ordered[level - 1][i]) {
            guest.seat[level - 1][guest.num_of_tickets[level - 1]++] = i;
            airlines[airline].is_ordered[level - 1][i] = true;
            if (cnt == order_size) break;
        }
    }
    airlines[airline].guests_ordered.insert(guest);
    return true;
}

std::string to_lower(std::string in) {
    for (char& i : in) i = tolower(i);
    return in;
}
