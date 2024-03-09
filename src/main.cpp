#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::map<int, std::pair<std::string, double>> loadDataFromCSV(const std::string& filename) {
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

json::value getData(int id){
    auto data = loadDataFromCSV("data.csv");

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

    json::value response = getData(id);
    if (response.is_null()){        
        request.reply(status_codes::NotFound, U("Data not found"));
    }else{
        request.reply(status_codes::OK, response);
    }   
}

int main() {
    uri_builder uri(U("http://localhost:5000"));
    auto addr = uri.to_uri().to_string();
    http_listener listener(addr);
    
    listener.support(methods::GET, handle_get);

    try {
        listener
            .open()
            .then([&listener]() { std::cout << "Starting to listen at: " << listener.uri().to_string() << std::endl; })
            .wait();

        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
