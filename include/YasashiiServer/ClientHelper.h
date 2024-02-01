/**
 * @file ClientManager.h
 * @author ayano
 * @date 1/30/24
 * @brief
*/

#ifndef YASASHIISERVER_CLIENTHELPER_H
#define YASASHIISERVER_CLIENTHELPER_H

#include "httplib.h"
#include "KawaiiMQ/kawaiiMQ.h"
#include "SerializationTypes.h"
#include "Logger.h"
#include "Utility.hpp"
#include "apiDefinition.h"
#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include <limits>
#include <memory>


namespace YasashiiServer {

    httplib::Result relate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue> queue);

    httplib::Result unrelate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue>& queue);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result setTimeout(httplib::Client &client, int timeout);

    httplib::Result setSafeTimeout(httplib::Client& client, std::shared_ptr<KawaiiMQ::Queue> queue, int timeout);

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
    httplib::Result send(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg, const KawaiiMQ::Topic& topic);

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
    httplib::Result broadcast(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg);

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
    httplib::Result fetch(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
    httplib::Result fetchAll(httplib::Client& client, const KawaiiMQ::Consumer& con);
}



#endif //YASASHIISERVER_CLIENTHELPER_H
