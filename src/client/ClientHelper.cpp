/**
 * @file ClientManager.cpp
 * @author ayano
 * @date 1/30/24
 * @brief
*/

#include "ClientHelper.h"

//namespace YasashiiServer {
//
//    std::string demangle(const char* name) {
//        int status = -4;
//
//        std::unique_ptr<char, void(*)(void*)> res {
//                abi::__cxa_demangle(name, NULL, NULL, &status),
//                std::free
//        };
//
//        return (status==0) ? res.get() : name ;
//    }
//
//    httplib::Result relate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue> queue) {
////        std::stringstream topic_data_out;
////        {
////            cereal::BinaryOutputArchive oarchive(topic_data_out);
////            TopicData topic_data;
////            topic_data.name = topic.getName();
////            oarchive(topic_data);
////        }
////        std::stringstream queue_data_out;
////        {
////            cereal::BinaryOutputArchive oarchive(queue_data_out);
////            QueueData queue_data;
////            queue_data.name = queue->getName();
////            queue_data.timeout_ms = queue->getTimeout();
////            queue_data.safe_timeout_ms = queue->getSafeTimeout();
////            oarchive(queue_data);
////        }
////        httplib::Params params = {
////                {"topic_name", topic.getName()},
////                {"queue_name", queue->getName()},
////                {"topic_data", topic_data_out.str()},
////                {"queue_data", queue_data_out.str()}
////        };
////        auto res = client.Post(RELATE, params);
////        return res;
//    }
//
//    httplib::Result unrelate(httplib::Client& client, const KawaiiMQ::Topic& topic, std::shared_ptr<KawaiiMQ::Queue>& queue){
//
//        std::stringstream topic_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(topic_data_out);
//            TopicData topic_data;
//            topic_data.name = topic.getName();
//            oarchive(topic_data);
//        }
//        std::stringstream queue_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(queue_data_out);
//            QueueData queue_data;
//            queue_data.name = queue->getName();
//            queue_data.timeout_ms = queue->getTimeout();
//            queue_data.safe_timeout_ms = queue->getSafeTimeout();
//            oarchive(queue_data);
//        }
//        httplib::Params params = {
//                {"topic_name", topic.getName()},
//                {"queue_name", queue->getName()},
//                {"topic_data", topic_data_out.str()},
//                {"queue_data", queue_data_out.str()}
//        };
//        auto res = client.Post(UNRELATE, params);
//        return res;
//    }
//
//    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic) {
//
//        std::stringstream consumer_data_out;
//        {
//            ConsumerData consumer;
//            consumer.name = con.getName();
//            for (const auto& t : con.getSubscribedTopics()) {
//                consumer.subscribed.push_back(TopicData{t.getName()});
//            }
//            cereal::BinaryOutputArchive oarchive(consumer_data_out);
//            oarchive(consumer);
//        }
//        std::stringstream topic_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(topic_data_out);
//            TopicData topic_data;
//            topic_data.name = topic.getName();
//            oarchive(topic_data);
//        }
//        httplib::Params params = {
//                {"consumer_name", con.getName()},
//                {"topic_name", topic.getName()},
//                {"consumer_data", consumer_data_out.str()},
//                {"topic_data", topic_data_out.str()}
//        };
//        auto res = client.Post(CONSUMER_SUBSCRIBE, params);
//        return res;
//    }
//
//    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Consumer& con, const KawaiiMQ::Topic& topic) {
//
//        std::stringstream consumer_data_out;
//        {
//            ConsumerData consumer;
//            consumer.name = con.getName();
//            for (const auto& t : con.getSubscribedTopics()) {
//                consumer.subscribed.push_back(TopicData{t.getName()});
//            }
//            cereal::BinaryOutputArchive oarchive(consumer_data_out);
//            oarchive(consumer);
//        }
//        std::stringstream topic_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(topic_data_out);
//            TopicData topic_data;
//            topic_data.name = topic.getName();
//            oarchive(topic_data);
//        }
//        httplib::Params params = {
//                {"consumer_name", con.getName()},
//                {"topic_name", topic.getName()},
//                {"consumer_data", consumer_data_out.str()},
//                {"topic_data", topic_data_out.str()}
//        };
//        auto res = client.Post(CONSUMER_UNSUBSCRIBE, params);
//        return res;
//    }
//
//    httplib::Result subscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic) {
//        std::stringstream producer_data_out;
//        {
//            ProducerData producer_data;
//            producer_data.name = prod.getName();
//            for (const auto& t : prod.getSubscribedTopics()) {
//                producer_data.subscribed.push_back(TopicData{t.getName()});
//            }
//            cereal::BinaryOutputArchive oarchive(producer_data_out);
//            oarchive(producer_data);
//        }
//        std::stringstream topic_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(topic_data_out);
//            TopicData topic_data;
//            topic_data.name = topic.getName();
//            oarchive(topic_data);
//        }
//        httplib::Params params = {
//                {"producer_name", prod.getName()},
//                {"topic_name",    topic.getName()},
//                {"producer_data", producer_data_out.str()},
//                {"topic_data",    topic_data_out.str()}
//        };
//        auto res = client.Post(PRODUCER_SUBSCRIBE, params);
//        return res;
//    }
//
//    httplib::Result unsubscribe(httplib::Client& client, const KawaiiMQ::Producer& prod, const KawaiiMQ::Topic& topic) {
//        std::stringstream producer_data_out;
//        {
//            ProducerData producer_data;
//            producer_data.name = prod.getName();
//            for (const auto& t : prod.getSubscribedTopics()) {
//                producer_data.subscribed.push_back(TopicData{t.getName()});
//            }
//            cereal::BinaryOutputArchive oarchive(producer_data_out);
//            oarchive(producer_data);
//        }
//        std::stringstream topic_data_out;
//        {
//            cereal::BinaryOutputArchive oarchive(topic_data_out);
//            TopicData topic_data;
//            topic_data.name = topic.getName();
//            oarchive(topic_data);
//        }
//        httplib::Params params = {
//                {"producer_name", prod.getName()},
//                {"topic_name",    topic.getName()},
//                {"producer_data", producer_data_out.str()},
//                {"topic_data",    topic_data_out.str()}
//        };
//        auto res = client.Post(PRODUCER_UNSUBSCRIBE, params);
//        return res;
//    }
//
//    httplib::Result setTimeout(httplib::Client &client, const KawaiiMQ::Queue& queue, int timeout) {
//        httplib::Params params = {
//                {"queue_name", queue.getName()},
//                {"timeout", std::to_string(timeout)},
//        };
//        auto res = client.Post(TIMEOUT, params);
//        return res;
//    }
//
//    httplib::Result setSafeTimeout(httplib::Client& client, std::shared_ptr<KawaiiMQ::Queue> queue, int timeout) {
//        httplib::Params params = {
//                {"queue_name", queue->getName()},
//                {"timeout", std::to_string(timeout)}
//        };
//        auto res = client.Post(SAFE_TIMEOUT, params);
//        return res;
//    }

