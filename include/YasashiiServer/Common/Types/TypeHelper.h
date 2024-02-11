/**
 * @file Types.hpp
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_TYPEHELPER_H
#define YASASHIISERVER_TYPEHELPER_H
#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include <cxxabi.h>
#include "Types/Types.hpp"
#include "KawaiiMQ/kawaiiMQ.h"
#include "Logger.h"

namespace YasashiiServer {

    class TypeHelper {
    public:
        static std::shared_ptr<TypeHelper> Instance() {
            static std::shared_ptr<TypeHelper> instance = std::make_shared<TypeHelper>();
            return instance;
        }
        template<Serializable T, class S>
        void registerType() {
            Logger::info("Registering type " + demangle(typeid(T).name()) + " to TypeHelper");
            types.try_emplace(demangle(typeid(T).name()), std::make_unique<S>());
        }
        static std::unordered_map<std::string, std::unique_ptr<TypeStrategy>> types;
        static std::string demangle(const char *name) {
            int status;
            char *realname = abi::__cxa_demangle(name, 0, 0, &status);
            std::string result(realname);
            free(realname);
            return result;
        }
    };

}


#endif //YASASHIISERVER_TYPEHELPER_H
