/**
 * @file Types.hpp
 * @author ayano
 * @date 2/1/24
 * @brief
*/

#ifndef YASASHIISERVER_TYPES_HPP
#define YASASHIISERVER_TYPES_HPP

#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/polymorphic.hpp"
#include "KawaiiMQ/kawaiiMQ.h"



namespace YasashiiServer {

    class ISerializable : public KawaiiMQ::MessageData {
    public:
        ISerializable() = default;
        virtual ~ISerializable() = default;

        template <class Archive>
        void serialize( Archive & ar )
        {
            // nothing to serialize
        }
    };

    struct SampleClass : public ISerializable {
        SampleClass() = default;
        SampleClass& operator=(const SampleClass &other) = default;
        int a;
        int b;
        int c;
        template<class Archive>
        void serialize(Archive &archive) {
            archive(cereal::base_class<ISerializable>(this), a, b, c);
        }
    };

    struct StringClass : public ISerializable {
        StringClass() = default;
        StringClass& operator=(const StringClass &other) = default;
        std::string str;
        template<class Archive>
        void serialize(Archive &archive) {
            archive(cereal::base_class<ISerializable>(this), str);
        }
    };

    template<typename T>
    concept Serializable =
    cereal::traits::detail::count_input_serializers<T, cereal::BinaryInputArchive>::value != 0 &&
    std::is_base_of_v<ISerializable, T>;

    class TypeStrategy {
    public:
        virtual ~TypeStrategy() = default;
        virtual std::shared_ptr<ISerializable> getType(const std::shared_ptr<ISerializable> val) = 0;
    };

    class TypeContext {
    public:
        void setTypeStrategy(std::unique_ptr<TypeStrategy> strategy) {
            this->strategy = std::move(strategy);
        }
        std::shared_ptr<ISerializable> getType(const std::shared_ptr<ISerializable> val) {
            return strategy->getType(val);
        }
    private:
        std::unique_ptr<TypeStrategy> strategy;
    };

    class SampleTypeStrategy : public TypeStrategy {
    public:
        std::shared_ptr<ISerializable> getType(const std::shared_ptr<ISerializable> val) override {
            return std::dynamic_pointer_cast<SampleClass>(val);
        }
    };

    class StringTypeStrategy : public TypeStrategy {
    public:
        std::shared_ptr<ISerializable> getType(const std::shared_ptr<ISerializable> val) override {
            return std::dynamic_pointer_cast<StringClass>(val);}
    };



}




// must register this class to be able to serialize it
CEREAL_REGISTER_TYPE(YasashiiServer::SampleClass);
CEREAL_REGISTER_TYPE(YasashiiServer::StringClass);

// also need to register all polymorphic relations
CEREAL_REGISTER_POLYMORPHIC_RELATION(YasashiiServer::ISerializable, YasashiiServer::SampleClass);
CEREAL_REGISTER_POLYMORPHIC_RELATION(YasashiiServer::ISerializable, YasashiiServer::StringClass);


#endif //YASASHIISERVER_TYPES_HPP
