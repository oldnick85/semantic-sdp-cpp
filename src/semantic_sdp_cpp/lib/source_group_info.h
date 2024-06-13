// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "./util.h"

namespace semantic_sdp {

class CSourceGroupInfo;
using SourceGroupInfo = std::unique_ptr<CSourceGroupInfo>;

/**
 * Group of SSRCS info
 */
class CSourceGroupInfo {
 private:
    std::string         m_semantics;
    std::vector<int>    m_ssrcs;

 public:
    /**
     * constructor for CSourceGroupInfo
     * @param [in] semantics Group semantics
     * @param [in] ssrcs SSRC list
     */
    CSourceGroupInfo(const std::string& semantics, const std::vector<int>& ssrcs)
    : m_semantics(semantics)
    , m_ssrcs(ssrcs)
    {}

    /**
     * Create a clone of this source group info object
     * @returns source group info
     */
    SourceGroupInfo Clone() const {
        return std::make_unique<CSourceGroupInfo>(m_semantics, m_ssrcs);
    }

    /**
     * Get group semantics
     * @returns group semantics
     */
    const auto& GetSemantics() const {
        return m_semantics;
    }

    /**
     * Get list of ssrcs from this group
     * @returns list of ssrcs
     */
    const auto& GetSSRCs() const {
        return m_ssrcs;
    }
};

}    // namespace semantic_sdp
