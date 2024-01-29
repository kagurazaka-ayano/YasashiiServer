/**
 * @file Logger.cpp
 * @author ayano
 * @date 1/28/24
 * @brief
*/

#include "Logger.h"

namespace YasashiiServer {

    LogLevel Logger::log_level = LogLevel::DEBUG;
    std::ostream* Logger::log_stream = &std::cout;
    std::string Logger::log_save_path = "";

    std::string Logger::getDateTimeString() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_time);
        std::string date_time_string = std::to_string(now_tm->tm_year + 1900) + "/" + std::to_string(now_tm->tm_mon + 1) + "/" + std::to_string(now_tm->tm_mday) + " " + std::to_string(now_tm->tm_hour) + ":" + std::to_string(now_tm->tm_min) + ":" + std::to_string(now_tm->tm_sec);
        return date_time_string;
    }

    void Logger::saveLog(const std::string &log) {
        if (log_save_path.empty()) {
            return;
        }
        std::ofstream ofs(log_save_path, std::ios::app);
        ofs << log << std::endl;
        ofs.close();
    }

    std::string Logger::getLogLevelString(LogLevel level) {
        return Logger::log_level_strings[static_cast<int>(level)];
    }

    void Logger::setLogSavePath(const std::string &path) {
        log_save_path = path;
    }

    void Logger::setLogStream(std::ostream &os) {
        log_stream = &os;
    }

    void Logger::setLogLevel(LogLevel level) {
        log_level = level;
    }

    void Logger::debug(const std::string &message) {
        if (log_level > LogLevel::DEBUG) {
            return;
        }
        std::string log_string = getLogString(message, LogLevel::DEBUG);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    void Logger::info(const std::string &message) {
        if (log_level > LogLevel::INFO) {
            return;
        }
        std::string log_string = getLogString(message, LogLevel::INFO);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    void Logger::warning(const std::string &message) {
        if (log_level > LogLevel::WARNING) {
            return;
        }
        std::string log_string = getLogString(message, LogLevel::WARNING);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    void Logger::error(const std::string &message) {
        if (log_level > LogLevel::ERROR) {
            return;
        }
        std::string log_string = getLogString(message, LogLevel::ERROR);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    void Logger::critical(const std::string &message) {
        if (log_level > LogLevel::CRITICAL) {
            return;
        }
        std::string log_string = getLogString(message, LogLevel::CRITICAL);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    std::string Logger::getLogString(const std::string &message, LogLevel log_level) {
        std::string color = log_level_colors[static_cast<int>(log_level)];
        std::string log_string = color + "[" + getDateTimeString() + "]" + message + "\033[0m";
        return log_string;
    }

    void ServerLogger::operator()(const httplib::Request &req, const httplib::Response &res) {
        LogLevel log_level;
        if (res.status == 200) {
            log_level = LogLevel::INFO;
        }
        else if (res.status >= 400 && res.status < 500) {
            log_level = LogLevel::WARNING;
        }
        else if (res.status >= 500) {
            log_level = LogLevel::ERROR;
        }
        else {
            log_level = LogLevel::DEBUG;
        }
        std::string color = log_level_colors[static_cast<int>(log_level)];
        std::string log_string = color + "[" + getDateTimeString() + "] " + getLogLevelString(log_level) + ": " + req.method + " from " + req.remote_addr + " accessing " + req.path + " " + std::to_string(res.status) + " " + res.body + "\033[0m";
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }

    void ClientLogger::operator()(const httplib::Request &req, const httplib::Response &res) {
        LogLevel log_level;
        if (res.status == 200) {
            log_level = LogLevel::INFO;
        }
        else if (res.status >= 400 && res.status < 500) {
            log_level = LogLevel::WARNING;
        }
        else if (res.status >= 500) {
            log_level = LogLevel::ERROR;
        }
        else {
            log_level = LogLevel::DEBUG;
        }
        std::string color = log_level_colors[static_cast<int>(log_level)];
        std::string log_string = fmt::format(
                "{}[{}]: {} to {} at server {} status: {} body: {}\033[0m",
                color,
                getDateTimeString(),
                getLogLevelString(log_level),
                req.method, req.path, req.remote_addr,
                std::to_string(res.status), res.body);
        *log_stream << log_string << std::endl;
        saveLog(log_string);
    }
}
