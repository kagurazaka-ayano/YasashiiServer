/**
 * @file Exceptions.h
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_EXCEPTIONS_H
#define YASASHIISERVER_EXCEPTIONS_H

namespace YasashiiServer {
    class DeserializationException : public std::exception {
    public:
        explicit DeserializationException(const std::string& message) : message(message) {}
        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }
    private:
        std::string message;
    };

}

#endif //YASASHIISERVER_EXCEPTIONS_H
