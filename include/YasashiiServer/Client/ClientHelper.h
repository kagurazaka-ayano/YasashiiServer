/**
 * @file ClientManager.h
 * @author ayano
 * @date 1/30/24
 * @brief
*/

#ifndef YASASHIISERVER_CLIENTHELPER_H
#define YASASHIISERVER_CLIENTHELPER_H

#include <limits>
#include <memory>
#include <cxxabi.h>
#include <httplib.h>
#include <KawaiiMQ/kawaiiMQ.h>
#include "Logger.h"
#include "ApiDefinition.h"
#include "BasicOperations.pb.h"


namespace YasashiiServer {

    std::string demangle(const char* name);

    httplib::Result relate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue> queue);

    httplib::Result unrelate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue>& queue);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result setTimeout(httplib::Client &client, const KawaiiMQ::Queue& queue, int timeout);

    httplib::Result setSafeTimeout(httplib::Client& client, std::shared_ptr<KawaiiMQ::Queue> queue, int timeout);

}



#endif //YASASHIISERVER_CLIENTHELPER_H
