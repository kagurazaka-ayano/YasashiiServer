/**
 * @file ServerHelper.cpp
 * @author ayano
 * @date 2/1/24
 * @brief
*/

#include "ServerHelper.h"
namespace YasashiiServer {
    std::unordered_map<std::string, KawaiiMQ::Producer> ServerHelper::producer_map;
    std::unordered_map<std::string, KawaiiMQ::Consumer> ServerHelper::consumer_map;
    std::unordered_map<std::string, std::shared_ptr<KawaiiMQ::Queue>> ServerHelper::queue_map;
}