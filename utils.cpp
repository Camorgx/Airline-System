#include "utils.hpp"
#include <fstream>
#include <algorithm>
using namespace std;

void init_system(vector<Airline>& airlines, const string& data_file) {
    ifstream fin; fin.open(data_file);
    int len; fin >> len;
    for (int i = 0; i < len; ++i) {
        string from, to, airline, plane;
        unsigned weekday;
        fin >> from >> to >> airline >> plane;
        fin >> weekday;
        airlines.push_back(Airline(from, to, airline, plane, weekday));
    }
    sort(airlines.begin(), airlines.end());
    fin.close();
}

void search_airline(vector<Airline>& ans, vector<Airline>& airlines, const string& to) {
    for (const auto& airline : airlines)
        if (airline.to == to) ans.push_back(airline);
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

bool order(vector<Airline>& airlines, const string& guest_name, unsigned airline, unsigned level,
           size_t order_size) {
    if (order_size > airlines[airline].tickets_left[level - 1])
        return false;
    Guest guest(guest_name);
    for (int i = 0; i < level_size[airline - 1]; ++i) {
        if (!airlines[airline].is_ordered[level - 1][i]) {
            guest.seat.push_back(i);
            airlines[airline].is_ordered[level - 1][i] = true;
        }
    }
    airlines[airline].guests_ordered.insert(guest);
    return true;
}

std::string to_lower(std::string in) {
    for (char& i : in) i = tolower(i);
    return in;
}
