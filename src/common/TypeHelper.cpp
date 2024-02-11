/**
 * @file Types.cpp
 * @author ayano
 * @date 2/1/24
 * @brief
*/

#include "Types/TypeHelper.h"


namespace YasashiiServer {
    std::unordered_map<std::string, std::unique_ptr<TypeStrategy>> TypeHelper::types;
}