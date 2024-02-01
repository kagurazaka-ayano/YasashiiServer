/**
 * @file ServerHelper.h
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_SERVERHELPER_H
#define YASASHIISERVER_SERVERHELPER_H

#include "KawaiiMQ/kawaiiMQ.h"
#include <unordered_map>

namespace YasashiiServer {

    std::unordered_map<std::string, KawaiiMQ::Producer> producer_map;
    std::unordered_map<std::string, KawaiiMQ::Consumer> consumer_map;
    std::unordered_map<std::string, std::shared_ptr<KawaiiMQ::Queue>> queue_map;
    std::unordered_map<std::string, std::shared_ptr<KawaiiMQ::MessageData>> type_mapping;

    template<KawaiiMQ::MessageType T>
    requires std::is_convertible_v<T, std::byte>
    void registerType(const T& in) {
        type_mapping[typeid(T).name()] = KawaiiMQ::makeMessage(in);
    }
}


#endif //YASASHIISERVER_SERVERHELPER_H
