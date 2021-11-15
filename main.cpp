//
//  main.cpp
//  航空客运订票系统
//
//  Created by 曹高翔 on 2021/10/11.
//

#include <iostream>
#include "Airline.hpp"
#include "utils.hpp"
using namespace std;

vector<Airline> airlines;

int main(int argc, const char * argv[]) {
    init_system(airlines, "database.txt");
    for (auto i : airlines)
        cout << i.to << endl;
    string input = "To3";
    auto p = search_airline(airlines, input);
    if (p) cout << p->id_airline << endl;
    else cout << "Not found!" << endl;
    return 0;
}
