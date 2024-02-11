/**
 * @file main.cpp
 * @author ayano
 * @date 1/27/24
 * @brief
*/

#include "KawaiiMQ/kawaiiMQ.h"
#include "httplib.h"
#include "Logger.h"
#include "ClientHelper.h"
#include "Types/Types.hpp"
constexpr int PORT = 33667;
constexpr char HOST[] = "localhost";

using namespace YasashiiServer;

int main() {


    auto queue = KawaiiMQ::makeQueue("testqueue");
    KawaiiMQ::Topic topic("testtopic");
    KawaiiMQ::Producer prod("testprod");
    KawaiiMQ::Consumer con("testcon");
    auto sample = std::make_shared<SampleClass>();
    sample->a = 1;
    sample->b = 2;
    sample->c = 3;
    httplib::Client client(HOST, PORT);
    client.set_logger(ClientLogger());
    relate(client, topic, queue);
    subscribe(client, con, topic);
    subscribe(client, prod, topic);
    auto ret = send<SampleClass>(client, prod, sample, topic);

}
