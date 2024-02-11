/**
 * @file Handler.cpp
 * @author ayano
 * @date 1/29/24
 * @brief
*/

#include "Handler.h"

namespace YasashiiServer {

    void RelateHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        Logger::info("relate request received");
        TopicData topic;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        QueueData queue;
        try {
            std::stringstream queue_stream(req.get_param_value("queue_data"));
            cereal::BinaryInputArchive iarchive(queue_stream);
            iarchive(queue);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize queue data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize queue data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto q = KawaiiMQ::makeQueue(queue.name);
        KawaiiMQ::Topic t(topic.name);
        q->setTimeout(queue.timeout_ms);
        q->setSafeTimeout(queue.safe_timeout_ms);
        try {
            manager->relate(t, q);
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to relate topic to queue");
            res.status = 500;
            res.set_content("failed to relate topic to queue", "text/plain");
            return;
        }
        ServerHelper::queue_map.try_emplace(queue.name, q);
        res.set_content("OK", "text/plain");
    }

    void UnrelateHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("unrelate request received");
        TopicData topic;
        QueueData queue;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        try {
            std::stringstream queue_stream(req.get_param_value("queue_data"));
            cereal::BinaryInputArchive iarchive(queue_stream);
            iarchive(queue);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize queue data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize queue data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        auto q = KawaiiMQ::makeQueue(queue.name);
        q->setTimeout(queue.timeout_ms);
        q->setSafeTimeout(queue.safe_timeout_ms);
        KawaiiMQ::Topic t(topic.name);
        try {
            manager->unrelate(t, q);
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to unrelate topic from queue");
            res.status = 500;
            res.set_content("failed to unrelate topic from queue, message: " + std::string(e.what()), "text/plain");
            return;
        }
        bool find = false;
        auto topics = manager->getRelatedTopic();
        for (const auto& topic_local : topics) {
            for (const auto& queue_local : manager->getAllRelatedQueue(topic_local)) {
                if (queue_local->getName() == queue.name) {
                    find = true;
                    break;
                }
            }
        }
        if(!find) {
            ServerHelper::queue_map.erase(queue.name);
        }
        res.set_content("OK", "text/plain");
    }


    void ProducerSubscribeHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("producer subscribe request received");
        TopicData topic;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        ProducerData producer;
        try {
            std::stringstream producer_stream(req.get_param_value("producer_data"));
            cereal::BinaryInputArchive iarchive(producer_stream);
            iarchive(producer);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize producer data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize producer data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        ServerHelper::producer_map.try_emplace(producer.name, producer.name);
        KawaiiMQ::Topic t(topic.name);
        try {
            ServerHelper::producer_map.at(producer.name).subscribe(t);
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to subscribe to topic");
            res.status = 500;
            res.set_content("failed to subscribe to topic, message: " + std::string(e.what()), "text/plain");
            return;
        }
    }

    void ProducerUnsubscribeHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("producer unsubscribe request received");
        TopicData topic;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        ProducerData producer;
        try {
            std::stringstream producer_stream(req.get_param_value("producer_data"));
            cereal::BinaryInputArchive iarchive(producer_stream);
            iarchive(producer);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize producer data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize producer data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        KawaiiMQ::Topic t(topic.name);
        try {
            ServerHelper::producer_map.at(producer.name).unsubscribe(t);
            if (ServerHelper::producer_map.at(producer.name).getSubscribedTopics().empty()) {
                ServerHelper::producer_map.erase(producer.name);
            }
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to unsubscribe from topic");
            res.status = 500;
            res.set_content("failed to unsubscribe from topic, message: " + std::string(e.what()), "text/plain");
            return;
        }
    }

    void ConsumerSubscribeHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("consumer subscribe request received");
        TopicData topic;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        ConsumerData consumer;
        try {
            std::stringstream consumer_stream(req.get_param_value("consumer_data"));
            cereal::BinaryInputArchive iarchive(consumer_stream);
            iarchive(consumer);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize consumer data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize consumer data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        ServerHelper::consumer_map.try_emplace(consumer.name, consumer.name);
        KawaiiMQ::Topic t(topic.name);
        try {
            ServerHelper::consumer_map.at(consumer.name).subscribe(t);
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to subscribe to topic");
            res.status = 500;
            res.set_content("failed to subscribe to topic, message: " + std::string(e.what()), "text/plain");
            return;
        }
    }

    void ConsumerUnsubscribeHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("consumer unsubscribe request received");
        TopicData topic;
        try {
            std::stringstream topic_stream(req.get_param_value("topic_data"));
            cereal::BinaryInputArchive iarchive(topic_stream);
            iarchive(topic);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize topic data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize topic data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        ConsumerData consumer;
        try {
            std::stringstream consumer_stream(req.get_param_value("consumer_data"));
            cereal::BinaryInputArchive iarchive(consumer_stream);
            iarchive(consumer);
        }
        catch (std::exception& e) {
            Logger::error("failed to deserialize consumer data, message: " + std::string(e.what()));
            res.status = 500;
            res.set_content("failed to deserialize consumer data, message: " + std::string(e.what()), "text/plain");
            return;
        }
        auto manager = KawaiiMQ::MessageQueueManager::Instance();
        KawaiiMQ::Topic t(topic.name);
        try {
            ServerHelper::producer_map.at(consumer.name).unsubscribe(t);
            if (ServerHelper::producer_map.at(consumer.name).getSubscribedTopics().empty()) {
                ServerHelper::producer_map.erase(consumer.name);
            }
        }
        catch(KawaiiMQ::TopicException& e) {
            Logger::error("failed to unsubscribe from topic");
            res.status = 500;
            res.set_content("failed to unsubscribe from topic, message: " + std::string(e.what()), "text/plain");
            return;
        }
        res.set_content("OK", "text/plain");
    }

    void SetTimeoutHandler::operator()(const httplib::Request &req, httplib::Response &res) {
        Logger::info("set timeout request received");
        std::string name = req.get_param_value("queue_name");
        int timeout = std::atoi(req.get_param_value("timeout").c_str());
        try
        {
            ServerHelper::queue_map.at(name)->setTimeout(timeout);
        }
        catch(const std::exception& e)
        {
            Logger::error("cannot find queue with name: " + name);
            res.status = 500;
            res.set_content("cannot find queue with name: " + name, "text/plain");
        }
        res.set_content("OK", "text/plain");
    }
    void SetSafeTimeoutHandler::operator()(const httplib::Request &req, httplib::Response &res)
    {
        Logger::info("set safe timeout request received");
        std::string name = req.get_param_value("queue_name");
        int timeout = std::atoi(req.get_param_value("timeout").c_str());
        try
        {
            ServerHelper::queue_map.at(name)->setSafeTimeout(timeout);
        }
        catch(const std::exception& e)
        {
            Logger::error("cannot find queue with name: " + name);
            res.status = 500;
            res.set_content("cannot find queue with name: " + name, "text/plain");
        }
    }

}


