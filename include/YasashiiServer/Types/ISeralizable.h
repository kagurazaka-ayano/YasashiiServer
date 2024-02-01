/**
 * @file ISeralizable.h
 * @author ayano
 * @date 2/1/24
 * @brief
*/

#ifndef YASASHIISERVER_ISERALIZABLE_H
#define YASASHIISERVER_ISERALIZABLE_H

#include "cereal/archives/binary.hpp"

namespace YasashiiServer {

    class ISeralizable {
    public:
        virtual ~ISeralizable() = default;

        template<class Archive>
        void serialize(Archive &archive) {
            // Do nothing
        }
    };


    template<typename T>
    concept Serializable =
    cereal::traits::detail::count_input_serializers<T, cereal::BinaryInputArchive>::value != 0 &&
    std::is_base_of_v<ISeralizable, T>;

}

#endif //YASASHIISERVER_ISERALIZABLE_H
