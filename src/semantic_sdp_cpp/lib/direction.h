// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>

#include "./util.h"

namespace semantic_sdp {
/**
 * Enum for Direction values.
 */
enum class Direction {
    Unknown = -1,
    Inactive = 0,
    SendOnly,
    RecvOnly,
    SendRecv
};

namespace direction {
/**
{
 * Get Direction by name
 * @param [in] direction
 * @returns direction
 */
Direction ByValue(const std::string& direction) {
    const std::string str{to_lower_case_copy(direction)};
    if (str == "sendrecv")
        return Direction::SendRecv;
    if (str == "sendonly")
        return Direction::SendOnly;
    if (str == "recvonly")
        return Direction::RecvOnly;
    if (str == "inactive")
        return Direction::Inactive;
    return Direction::Unknown;
}

/**
 * Get Direction name
 * @param [in] direction
 * @returns name
 */
std::string ToString(const Direction& direction) {
    switch (direction) {
        case Direction::SendRecv:
            return "sendrecv";
        case Direction::SendOnly:
            return "sendonly";
        case Direction::RecvOnly:
            return "recvonly";
        case Direction::Inactive:
            return "inactive";
        default:
            return "";
    }
    return "";
}

/**
 * Get reverse direction
 * @param [in] direction
 * @returns Reversed direction
 */
Direction Reverse(const Direction& direction) {
    switch (direction) {
        case Direction::SendRecv:
            return Direction::SendRecv;
        case Direction::SendOnly:
            return Direction::RecvOnly;
        case Direction::RecvOnly:
            return Direction::SendOnly;
        case Direction::Inactive:
            return Direction::Inactive;
        default:
            return Direction::Unknown;
    }
    return Direction::Unknown;
}

}    // namespace direction

}    // namespace semantic_sdp
