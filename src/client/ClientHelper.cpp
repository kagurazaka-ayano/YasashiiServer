/**
 * @file ClientManager.cpp
 * @author ayano
 * @date 1/30/24
 * @brief
*/

#include "ClientHelper.h"

namespace YasashiiServer {

    httplib::Result relate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue> queue) {
        std::stringstream topic_data_out;
        {
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        std::stringstream queue_data_out;
        {
            cereal::BinaryOutputArchive oarchive(queue_data_out);
            QueueData queue_data;
            queue_data.name = queue->getName();
            queue_data.timeout_ms = queue->getTimeout();
            queue_data.safe_timeout_ms = queue->getSafeTimeout();
            oarchive(queue_data);
        }
        httplib::Params params = {
                {"topic_name", topic.getName()},
                {"queue_name", queue->getName()},
                {"topic_data", topic_data_out.str()},
                {"queue_data", queue_data_out.str()}
        };
        auto res = client.Post(RELATE, params);
        return res;
    }

    httplib::Result unrelate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue>& queue){

        std::stringstream topic_data_out;
        {
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        std::stringstream queue_data_out;
        {
            cereal::BinaryOutputArchive oarchive(queue_data_out);
            QueueData queue_data;
            queue_data.name = queue->getName();
            queue_data.timeout_ms = queue->getTimeout();
            queue_data.safe_timeout_ms = queue->getSafeTimeout();
            oarchive(queue_data);
        }
        httplib::Params params = {
                {"topic_name", topic.getName()},
                {"queue_name", queue->getName()},
                {"topic_data", topic_data_out.str()},
                {"queue_data", queue_data_out.str()}
        };
        auto res = client.Post(UNRELATE, params);
        return res;
    }

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic) {

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
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"consumer_name", con.getName()},
                {"topic_name", topic.getName()},
                {"consumer_data", consumer_data_out.str()},
                {"topic_data", topic_data_out.str()}
        };
        auto res = client.Post(CONSUMER_SUBSCRIBE, params);
        return res;
    }

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic) {

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
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"consumer_name", con.getName()},
                {"topic_name", topic.getName()},
                {"consumer_data", consumer_data_out.str()},
                {"topic_data", topic_data_out.str()}
        };
        auto res = client.Post(CONSUMER_UNSUBSCRIBE, params);
        return res;
    }

    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic) {
        std::stringstream producer_data_out;
        {
            ProducerData producer_data;
            producer_data.name = prod.getName();
            for (const auto& t : prod.getSubscribedTopics()) {
                producer_data.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(producer_data_out);
            oarchive(producer_data);
        }
        std::stringstream topic_data_out;
        {
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"producer_name", prod.getName()},
                {"topic_name",    topic.getName()},
                {"producer_data", producer_data_out.str()},
                {"topic_data",    topic_data_out.str()}
        };
        auto res = client.Post(PRODUCER_SUBSCRIBE, params);
        return res;
    }

    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic) {
        std::stringstream producer_data_out;
        {
            ProducerData producer_data;
            producer_data.name = prod.getName();
            for (const auto& t : prod.getSubscribedTopics()) {
                producer_data.subscribed.push_back(TopicData{t.getName()});
            }
            cereal::BinaryOutputArchive oarchive(producer_data_out);
            oarchive(producer_data);
        }
        std::stringstream topic_data_out;
        {
            cereal::BinaryOutputArchive oarchive(topic_data_out);
            TopicData topic_data;
            topic_data.name = topic.getName();
            oarchive(topic_data);
        }
        httplib::Params params = {
                {"producer_name", prod.getName()},
                {"topic_name",    topic.getName()},
                {"producer_data", producer_data_out.str()},
                {"topic_data",    topic_data_out.str()}
        };
        auto res = client.Post(PRODUCER_UNSUBSCRIBE, params);
        return res;
    }

    httplib::Result setTimeout(httplib::Client &client, const KawaiiMQ::Queue& queue, int timeout) {
        httplib::Params params = {
                {"queue_name", queue.getName()},
                {"timeout", std::to_string(timeout)},
        };
        auto res = client.Post(TIMEOUT, params);
        return res;
    }

    httplib::Result setSafeTimeout(httplib::Client& client, std::shared_ptr<KawaiiMQ::Queue> queue, int timeout) {\
        httplib::Params params = {
                {"queue_name", queue->getName()},
                {"timeout", std::to_string(timeout)}
        };
        auto res = client.Post(SAFE_TIMEOUT, params);
        return res;
    }

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
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
            message.message = msg;
            message.type = typeid(T).name();
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
        auto res = client.Post(SEND, params);
        return res;
    }

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
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
        auto res = client.Post(BROADCAST, params);
        return res;
    }

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
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

    template<typename T>
    requires std::is_convertible_v<T, std::byte> || std::is_fundamental_v<T>
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
