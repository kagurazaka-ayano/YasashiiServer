/**
 * @file main.cpp
 * @author ayano
 * @date 1/27/24
 * @brief
*/

#include "KawaiiMQ/kawaiiMQ.h"
#include "httplib.h"
#include "Logger.h"
constexpr int PORT = 33667;
constexpr char HOST[] = "localhost";

using namespace YasashiiServer;

int main() {

    httplib::Client client(HOST, PORT);
    client.set_logger(ClientLogger());
    int a, b;
    std::cin >> a >> b;
    if(auto res = client.Get(fmt::format("/add/?a={}&b={}", a, b)); res && res->status == 200) {
        Logger::info(fmt::format("{} + {} = {}", a, b, res->body));
    } else {
        std::cerr << "error" << std::endl;
    }

}
