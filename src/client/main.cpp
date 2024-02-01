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
#include "Types/Types.h"
constexpr int PORT = 33667;
constexpr char HOST[] = "localhost";

using namespace YasashiiServer;

int main() {

    auto queue = KawaiiMQ::makeQueue("testqueue");
    KawaiiMQ::Topic topic("testtopic");
    KawaiiMQ::Producer prod("testprod");
    KawaiiMQ::Consumer con("testcon");
    SampleClass sample;
    sample.a = 2;
    sample.b = 3;
    sample.c = 4;
    auto msg = KawaiiMQ::makeMessage(sample);
    httplib::Client client(HOST, PORT);
    client.set_logger(ClientLogger());
    relate(client, topic, queue);
    send<SampleClass>(client, prod, msg, topic);
}
