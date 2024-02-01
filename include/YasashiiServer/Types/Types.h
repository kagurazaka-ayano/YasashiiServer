/**
 * @file Types.hpp
 * @author ayano
 * @date 1/31/24
 * @brief
*/

#ifndef YASASHIISERVER_TYPES_H
#define YASASHIISERVER_TYPES_H
#include <string>
#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include "KawaiiMQ/kawaiiMQ.h"
#include "SampleClass.h"
#include "ISeralizable.h"
#include "cxxabi.h"

namespace YasashiiServer {

    class TypeHelper {
    public:
        static std::shared_ptr<TypeHelper> Instance() {
            static std::shared_ptr<TypeHelper> instance = std::make_shared<TypeHelper>();
            return instance;
        }
        template<Serializable T>
        void registerType() {
            types.emplace_back((typeid(T).name()));
        }
        static std::vector<std::string> types;
        std::string demangle(const char *name) {
            int status;
            char *realname = abi::__cxa_demangle(name, 0, 0, &status);
            std::string result(realname);
            free(realname);
            return result;
        }
    };

}

// Register all types here
CEREAL_REGISTER_TYPE(YasashiiServer::SampleClass);

// Register all polymorphic relations here
CEREAL_REGISTER_POLYMORPHIC_RELATION(YasashiiServer::ISeralizable, YasashiiServer::SampleClass);

#endif //YASASHIISERVER_TYPES_H
