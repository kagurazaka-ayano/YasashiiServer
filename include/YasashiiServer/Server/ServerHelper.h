/**
 * @file ServerHelper.h
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_SERVERHELPER_H
#define YASASHIISERVER_SERVERHELPER_H

#include "KawaiiMQ/kawaiiMQ.h"
#include "cereal/types/polymorphic.hpp"
#include "cereal/archives/portable_binary.hpp"
#include <unordered_map>

namespace YasashiiServer {

    struct ServerHelper {
        static std::unordered_map<std::string, KawaiiMQ::Producer> producer_map;
        static std::unordered_map<std::string, KawaiiMQ::Consumer> consumer_map;
        static std::unordered_map<std::string, std::shared_ptr<KawaiiMQ::Queue>> queue_map;
    };

}


#endif //YASASHIISERVER_SERVERHELPER_H
