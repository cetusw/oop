//
// Created by cetus on 4/8/25.
//

#ifndef TYPES_H
#define TYPES_H
#include <functional>

using CarCommands = std::unordered_map<std::string, std::function<bool(int arg)>>;

enum class Direction
{
    FORWARD,
    BACKWARD,
    STANDING_STILL
};

#endif //TYPES_H
