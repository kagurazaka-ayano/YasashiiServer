/**
 * @file Logger.h
 * @author ayano
 * @date 1/28/24
 * @brief
*/

#ifndef YASASHIISERVER_LOGGER_H
#define YASASHIISERVER_LOGGER_H

#include "httplib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

namespace YasashiiServer {

    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    /**
     * @brief Logger class
     */
    class Logger {
    public:
        void setLogLevel(LogLevel level);

        void setLogStream(std::ostream& os);

        void setLogSavePath(const std::string& path);

        static void debug(const std::string& message);

        static void info(const std::string& message);

        static void warning(const std::string& message);

        static void error(const std::string& message);

        static void critical(const std::string& message);

        static LogLevel log_level;
        static std::ostream* log_stream;
        static std::string log_save_path;
        constexpr static const char* log_level_strings[] = {
                "DEBUG",
                "INFO",
                "WARNING",
                "ERROR",
                "CRITICAL"
        };

        constexpr static const char* log_level_colors[] = {
                "\033[34m",
                "\033[32m",
                "\033[33m",
                "\033[31m",
                "\033[35m"
        };

        static std::string getLogLevelString(LogLevel level);

        static std::string getDateTimeString();

        static std::string getLogString(const std::string& message, LogLevel log_level);

        static void saveLog(const std::string& log);
    };

    class ServerLogger : public Logger, public httplib::Logger {
        public:
            void operator()(const httplib::Request &req, const httplib::Response &res);
        };
    class ClientLogger : public Logger, public httplib::Logger {
        public:
            void operator()(const httplib::Request &req, const httplib::Response &res);
        };
}

#endif //YASASHIISERVER_LOGGER_H
