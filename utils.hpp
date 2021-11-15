//
//  utils.hpp
//  航空客运订票系统
//
//  Created by 曹高翔 on 2021/10/18.
//

#ifndef utils_hpp
#define utils_hpp

#include "Airline.hpp"

void init_system(std::vector<Airline>& airlines, std::string data_file);
Airline* search_airline(std::vector<Airline>& airlines, std::string to);

#endif /* utils_hpp */
