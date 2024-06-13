// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>

#include "./util.h"

namespace semantic_sdp {

/**
 * Enum for Setup values.
 */
enum class Setup {
    Unknown = -1,
    Inactive = 0,
    Active,
    Passive,
    ActPass
};

namespace setup {

/**
 * Get Setup by name
 * @param [in] setup
 * @returns setup
 */
Setup ByValue(const std::string& setup) {
    std::string str{to_lower_case_copy(setup)};
    if (str == "inactive")
        return Setup::Inactive;
    if (str == "active")
        return Setup::Active;
    if (str == "passive")
        return Setup::Passive;
    if (str == "actpass")
        return Setup::ActPass;
    return Setup::Unknown;
}

/**
 * Get Setup name
 * @param [in] setup
 * @returns name
 */
std::string ToString(Setup setup) {
    switch (setup) {
        case Setup::Active:
            return "active";
        case Setup::Passive:
            return "passive";
        case Setup::ActPass:
            return "actpass";
        case Setup::Inactive:
            return "inactive";
        default:
            return "";
    }
    return "";
}

/**
 * Get reverse Setup
 * @param [in] setup
 * @param [in] prefferActive
 * @returns setup
 */
Setup Reverse(const Setup setup, const bool prefferActive) {
    switch (setup) {
        case Setup::Active:
            return Setup::Passive;
        case Setup::Passive:
            return Setup::Active;
        case Setup::ActPass:
            return prefferActive ? Setup::Active : Setup::Passive;
        case Setup::Inactive:
            return Setup::Inactive;
        default:
            return Setup::Unknown;
    }
    return Setup::Unknown;
}

}    // namespace setup

}    // namespace semantic_sdp
