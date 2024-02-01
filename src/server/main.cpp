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
#include "Types/Types.h"
#include "fmt/format.h"

using namespace YasashiiServer;

constexpr int PORT = 33667;

int main() {
    httplib::Server server;

    server.set_logger(ServerLogger());
    if(!server.is_valid()) {
        Logger::critical("server is not valid");
        return 1;
    }


    TypeHelper::Instance()->registerType<SampleClass>();


    Logger::info("server started at port: " + std::to_string(PORT));
    server.Post(RELATE, RelateHandler());
    server.Post(UNRELATE, UnrelateHandler());

    for(const auto& type: TypeHelper::types) {
        Logger::info(fmt::format("subscribing to type: {}", TypeHelper::Instance()->demangle(type.c_str())));
        server.Post(SEND_BASE + TypeHelper::Instance()->demangle(type.c_str()), SendHandler());
    }

    server.listen("localhost", PORT);
}