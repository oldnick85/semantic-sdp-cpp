// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>

#include "./util.h"

namespace semantic_sdp {
/**
 * Enum for DirectionWay values.
 */
enum class DirectionWay {
    Unknown = -1,
    Send = 1,
    Recv = 2
};

namespace direction_way {
/**
 * Get Direction Way by name
 * @param [in] direction
 * @returns direction way
 */
DirectionWay ByValue(const std::string& direction) {
    const std::string str{to_lower_case_copy(direction)};
    if (str == "send")
        return DirectionWay::Send;
    if (str == "recv")
        return DirectionWay::Recv;
    return DirectionWay::Unknown;
}

/**
 * Get Direction Way name
 * @param [in] direction
 * @returns string
 */
std::string ToString(DirectionWay direction) {
    switch (direction) {
        case DirectionWay::Send:
            return "send";
        case DirectionWay::Recv:
            return "recv";
        default:
            return "";
    }
    return "";
}

/**
 * Get reverse direction way
 * @param [in] direction
 * @returns Reversed direction
 */
DirectionWay Reverse(DirectionWay direction) {
    switch (direction) {
        case DirectionWay::Send:
            return DirectionWay::Recv;
        case DirectionWay::Recv:
            return DirectionWay::Send;
        default:
            return DirectionWay::Unknown;
    }
    return DirectionWay::Unknown;
}

}    // namespace direction_way

}    // namespace semantic_sdp
