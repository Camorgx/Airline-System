//
//  utils.cpp
//  航空客运订票系统
//
//  Created by 曹高翔 on 2021/10/18.
//

#include "utils.hpp"
#include <cstring>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

void init_system(vector<Airline>& airlines, string data_file) {
    ifstream fin; fin.open(data_file);
    int len; fin >> len;
    cout << len << endl;
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

Airline* search_airline(vector<Airline>& airlines, string to) {
    for (int i = 0; i < airlines.size(); ++i)
        if (airlines[i].to == to) return &airlines[i];
    return nullptr;
}
