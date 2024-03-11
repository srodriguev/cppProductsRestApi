#include "functions.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <fstream>
#include <sstream>

using namespace web;
using namespace web::http;

std::map<int, std::pair<std::string, double>> loadDataFromCSV(const std::string filename) {
    std::map<int, std::pair<std::string, double>> data;
    std::ifstream file(filename);
    std::string line, idStr, name, priceStr;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::getline(s, idStr, ',');
        std::getline(s, name, ',');
        std::getline(s, priceStr, ',');

        int id = std::stoi(idStr);
        double price = std::stod(priceStr);

        data[id] = {name, price};
    }

    return data;
}

json::value getData(int id, std::map<int, std::pair<std::string, double>> data){
    // Create a JSON response
    json::value response;

    // Check if the id exists in the data
    if (data.find(id) != data.end()) {
        auto foundData = data[id];
        
        response[U("id")] = json::value::number(id);
        response[U("name")] = json::value::string(foundData.first);
        response[U("price")] = json::value::number(foundData.second);
        
    }
    return response;
}

void handle_get(http_request request) {
    // Parse the query
    auto query = uri::split_query(request.relative_uri().query());
    int id = std::stoi(query[U("id")]);
    auto data = loadDataFromCSV("data.csv");

    json::value response = getData(id, data);
    if (response.is_null()){        
        request.reply(status_codes::NotFound, U("Data not found"));
    }else{
        request.reply(status_codes::OK, response);
    }   
}
