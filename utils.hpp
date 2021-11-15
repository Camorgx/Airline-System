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
void search_airline(std::vector<Airline>& ans, std::vector<Airline>& airlines, const std::string& to);
void order(std::string airline, size_t order);
void string_split(std::vector<std::string>& ans, const std::string& source,
                  const std::string& split = " ");

#endif /* utils_hpp */
