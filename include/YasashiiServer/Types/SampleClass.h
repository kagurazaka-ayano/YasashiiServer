/**
 * @file SampleClass.h
 * @author ayano
 * @date 2/1/24
 * @brief
*/

#ifndef YASASHIISERVER_SAMPLECLASS_H
#define YASASHIISERVER_SAMPLECLASS_H

#include "cereal/types/polymorphic.hpp"
#include "cereal/cereal.hpp"
#include "ISeralizable.h"

namespace YasashiiServer{
    struct SampleClass : public ISeralizable {
        SampleClass() = default;
        SampleClass& operator=(const SampleClass &other) = default;
        int a;
        int b;
        int c;
        template<class Archive>
        void serialize(Archive &archive) {
            archive(cereal::virtual_base_class<ISeralizable>(this), a, b, c);
        }
    };
}


#endif //YASASHIISERVER_SAMPLECLASS_H
