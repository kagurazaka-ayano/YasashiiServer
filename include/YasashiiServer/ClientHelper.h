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
#include "Types/SerializationTypes.h"
#include "Logger.h"
#include "Utility.hpp"
#include "ApiDefinition.h"
#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "Types/Types.h"
#include "Types/ISeralizable.h"
#include <limits>
#include <memory>


namespace YasashiiServer {

    httplib::Result relate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue> queue);

    httplib::Result unrelate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue>& queue);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic);

    httplib::Result setTimeout(httplib::Client &client, const KawaiiMQ::Queue& queue, int timeout);

    httplib::Result setSafeTimeout(httplib::Client& client, std::shared_ptr<KawaiiMQ::Queue> queue, int timeout);

    template<Serializable T>
    httplib::Result send(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg, const KawaiiMQ::Topic& topic);

    template<Serializable T>
    httplib::Result broadcast(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg);

    template<Serializable T>
    httplib::Result fetch(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic);

    template<Serializable T>
    httplib::Result fetchAll(httplib::Client& client, const KawaiiMQ::Consumer& con);

    template<Serializable T>
    httplib::Result send(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg, const KawaiiMQ::Topic& topic){
        std::stringstream producer_data_out;
        {
            ProducerData producer;
            producer.name = prod.getName();
            for(const auto& t : prod.getSubscribedTopics()) {
                producer.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(producer_data_out);
            oarchive(producer);
        }
        std::stringstream message_data_out;
        {
            MessageData<T> message;
            message.message_content = KawaiiMQ::getMessage<T>(msg);
            cereal::BinaryOutputArchive oarchive(message_data_out);
            oarchive(message);
        }
        std::stringstream topic_data_out;
        {
            TopicData topic_data;
            topic_data.name = topic.getName();
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"producer_name", prod.getName()},
                {"topic_name", topic.getName()},
                {"producer_data", producer_data_out.str()},
                {"message_data", message_data_out.str()},
                {"topic_data", topic_data_out.str()}
        };
        auto res = client.Post(std::string(SEND_BASE) + TypeHelper::Instance()->demangle(typeid(T).name()), params);
        return res;
    }

    template<Serializable T>
    httplib::Result broadcast(httplib::Client& client, const KawaiiMQ::Producer& prod, const std::shared_ptr<KawaiiMQ::Message<T>>& msg) {
        std::stringstream producer_data_out;
        {
            ProducerData producer;
            producer.name = prod.getName();
            for(const auto& t : prod.getSubscribedTopics()) {
                producer.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(producer_data_out);
            oarchive(producer);
        }
        std::stringstream message_data_out;
        {
            MessageData<T> message;
            message.message = msg;
            message.type = typeid(T).name();
            cereal::BinaryOutputArchive oarchive(message_data_out);
            oarchive(message);
        }
        httplib::Params params = {
                {"producer_name", prod.getName()},
                {"producer_data", producer_data_out.str()},
                {"message_data", message_data_out.str()},
        };
        auto res = client.Post(std::string(BROADCAST_BASE) + TypeHelper::Instance()->demangle(typeid(T).name()), params);
        return res;
    }

    template<Serializable T>
    httplib::Result fetch(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic) {
        std::stringstream consumer_data_out;
        {
            ConsumerData consumer;
            consumer.name = con.getName();
            for (const auto& t : con.getSubscribedTopics()) {
                consumer.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(consumer_data_out);
            oarchive(consumer);
        }
        std::stringstream topic_data_out;
        {
            TopicData topic_data;
            topic_data.name = topic.getName();
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"consumer_name", con.getName()},
                {"topic_name", topic.getName()},
                {"consumer_data", consumer_data_out.str()},
                {"topic_data", topic_data_out.str()}
        };
        auto res = client.Post(FETCH, params);
        return res;
    }

    template<Serializable T>
    httplib::Result fetchAll(httplib::Client& client, const KawaiiMQ::Consumer& con) {
        std::stringstream consumer_data_out;
        {
            ConsumerData consumer;
            consumer.name = con.getName();
            for (const auto& t : con.getSubscribedTopics()) {
                consumer.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(consumer_data_out);
            oarchive(consumer);
        }
        httplib::Params params = {
                {"consumer_name", con.getName()},
                {"consumer_data", consumer_data_out.str()},
        };
        auto res = client.Post(FETCH_ALL, params);
        return res;
    }
}



#endif //YASASHIISERVER_CLIENTHELPER_H
