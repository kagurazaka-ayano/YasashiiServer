/**
 * @file main.cpp
 * @author ayano
 * @date 1/27/24
 * @brief
*/


#include "httplib.h"
#include "Logger.h"
#include "Handler.h"
#include "ApiDefinition.h"

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
    server.Post(RELATE, RelateHandler());
    server.Post(UNRELATE, UnrelateHandler());
    server.Post(CONSUMER_SUBSCRIBE, ConsumerSubscribeHandler());
    server.Post(PRODUCER_SUBSCRIBE, ProducerSubscribeHandler());


    server.listen("localhost", PORT);
}