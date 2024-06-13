// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

#include "./util.h"

namespace semantic_sdp {

class CICEInfo;
using ICEInfo = std::unique_ptr<CICEInfo>;

/**
 * ICE information for a peer
 */
class CICEInfo {
// TODO(Unknown): ice-options: trickle
 private:
    std::string     m_ufrag;
    std::string     m_pwd;
    bool            m_lite = false;
    bool            m_end_of_candidates = false;

 public:
    /**
     * constructor for CICEInfo
     * @param [in] ufrag Peer ICE username framgent
     * @param [in] pwd Peer ICE password
     */
    CICEInfo(const std::string& ufrag, const std::string& pwd)
    : m_ufrag(ufrag)
    , m_pwd(pwd)
    {}

    /**
     * Create a clone of this Codec info object
     * @returns ICE info
     */
    ICEInfo Clone() const {
        auto cloned = std::make_unique<CICEInfo>(m_ufrag, m_pwd);
        cloned->SetLite(m_lite);
        cloned->SetEndOfCandidates(m_end_of_candidates);
        return cloned;
    }

    /**
     * Get username fragment
     * @returns ufrag
     */
    const auto& GetUfrag() const {
        return m_ufrag;
    }

    /**
     * Get username password
     * @returns password
     */
    const auto& GetPwd() const {
        return m_pwd;
    }

    /**
     * Is peer ICE lite
     * @returns boolean
     */
    auto IsLite() const {
        return m_lite;
    }

    /**
     * Set peer as ICE lite
     * @param [in] lite
     */
    void SetLite(const bool lite) {
        m_lite = lite;
    }

    auto IsEndOfCandidates() const {
        return m_end_of_candidates;
    }

    /**
     * @param [in] end_of_candidates
     */
    void SetEndOfCandidates(const bool end_of_candidates) {
         m_end_of_candidates = end_of_candidates;
    }
};

/**
 * Genereate a new peer ICE info with ramdom values
 * @param [in] lite Set ICE lite flag
 * @returns ICE info
 */
ICEInfo generate(const bool lite) {
    // Create key and pwd bytes
    const auto ufrag_b = random_bytes(8);
    const auto pwd_b = random_bytes(24);
    // Create ramdom pwd
    const auto ufrag = bytes_to_hex(ufrag_b);
    const auto pwd   = bytes_to_hex(pwd_b);

    auto info = std::make_unique<CICEInfo>(ufrag, pwd);
    info->SetLite(lite);
    return info;
}

}    // namespace semantic_sdp
