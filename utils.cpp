#include "utils.hpp"
#include <fstream>
#include <algorithm>
using namespace std;

void init_system(vector<Airline>& airlines, string data_file) {
    ifstream fin; fin.open(data_file);
    int len; fin >> len;
    for (int i = 0; i < len; ++i) {
        string from, to, airline, plane;
        unsigned weekday, left;
        fin >> from >> to >> airline >> plane;
        fin >> weekday >> left;
        airlines.push_back(Airline(from, to, airline, plane, weekday, left));
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

void order(string airline, size_t order) {

}
