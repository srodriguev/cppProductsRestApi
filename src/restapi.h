// restapi.h
#pragma oncedat

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;


std::map<int, std::pair<std::string, double>> loadDataFromCSV(const std::string& filename);
json::value getData(int id, std::map<int, std::pair<std::string, double>> data); 
void handle_get(http_request request);