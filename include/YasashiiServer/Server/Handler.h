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
#include "ServerHelper.h"
#include <cstdlib>
#include <type_traits>
#include <string>
#include <typeinfo>

namespace YasashiiServer {

    class IHandler {
    public:
        virtual void operator()(const httplib::Request &req, httplib::Response &res) = 0;
    };

    class RelateHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class UnrelateHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class ProducerSubscribeHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class ProducerUnsubscribeHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class ConsumerSubscribeHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class ConsumerUnsubscribeHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class SetTimeoutHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };

    class SetSafeTimeoutHandler : public IHandler {
    public:
        void operator()(const httplib::Request &req, httplib::Response &res) override;
    };


}

#endif //YASASHIISERVER_HANDLER_H
