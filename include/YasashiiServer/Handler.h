/**
 * @file Handler.h
 * @author ayano
 * @date 1/29/24
 * @brief
*/

#ifndef YASASHIISERVER_HANDLER_H
#define YASASHIISERVER_HANDLER_H

#include "httplib.h"
#include "KawaiiMQ/kawaiiMQ.h"
#include "Logger.h"
#include "Types/SerializationTypes.h"
#include "Utility.hpp"
#include "ServerHelper.h"
#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/polymorphic.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "Types/Types.h"
#include <cstdlib>
#include <type_traits>
#include <string>
#include <typeinfo>

namespace YasashiiServer {

    class RelateHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class UnrelateHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class ProducerSubscribeHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class ProducerUnsubscribeHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class ConsumerSubscribeHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class ConsumerUnsubscribeHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class SetTimeoutHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class SetSafeTimeoutHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };

    class SendHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res);
    };
}

#endif //YASASHIISERVER_HANDLER_H
