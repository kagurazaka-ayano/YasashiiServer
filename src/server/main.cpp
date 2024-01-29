/**
 * @file main.cpp
 * @author ayano
 * @date 1/27/24
 * @brief
*/


#include "httplib.h"
#include "Logger.h"

using namespace YasashiiServer;

constexpr int PORT = 33667;

int main() {
    httplib::Server server;

    server.set_logger(ServerLogger());
    if(!server.is_valid()) {
        Logger::critical("server is not valid");
        return 1;
    }

    Logger::info("server started at port: " + std::to_string(PORT));

    server.Get("/add/", [](const httplib::Request& req, httplib::Response& res) {
        int a = req.get_param_value("a").empty() ? 0 : std::stoi(req.get_param_value("a"));
        int b = req.get_param_value("b").empty() ? 0 : std::stoi(req.get_param_value("b"));
        res.set_content(std::to_string(a + b), "text/plain");
    });

    server.listen("localhost", PORT);
}