// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <string>
#include <utility> 
#include <cpprest/http_listener.h> // For http_request and related classes
#include <cpprest/json.h>          // For json::value

// Function declarations
std::map<int, std::pair<std::string, double>> loadDataFromCSV(const std::string filename);
web::json::value getData(int id, const std::map<int, std::pair<std::string, double>> data);
void handle_get(web::http::http_request request);

#endif // FUNCTIONS_H
