// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

#include "./util.h"
#include "./setup.h"

namespace semantic_sdp {

class CDTLSInfo;
using DTLSInfo = std::unique_ptr<CDTLSInfo>;

/**
 * DTLS peer info
 */
class CDTLSInfo {
 private:
    Setup             m_setup;
    std::string     m_hash;
    std::string     m_fingerprint;

 public:
    /**
     * constructor for DTLSInfo
     * @param [in] setup Setup type
     * @param [in] hash Hash function
     * @param [in] fingerprint Peer fingerprint
     */
    CDTLSInfo(const Setup& setup, const std::string& hash, const std::string& fingerprint)
    : m_setup(setup)
    , m_hash(hash)
    , m_fingerprint(fingerprint)
    {}

    /**
     * Create a clone of this DTLS info object
     * @returns DTLS info
     */
    DTLSInfo Clone() const {
        return std::make_unique<CDTLSInfo>(m_setup, m_hash, m_fingerprint);
    }

    /**
     * Get peer fingerprint
     * @returns fingerprint
     */
    const auto& GetFingerprint() const {
        return m_fingerprint;
    }

    /**
     * Get hash function name
     * @returns name
     */
    const auto& GetHash() const {
        return m_hash;
    }

    /**
     * Get connection setup
     * @returns setup
     */
    auto GetSetup() const {
        return m_setup;
    }

    /**
     * Set connection setup
     * @param [in] setup
     */
    void SetSetup(Setup setup) {
        m_setup = setup;
    }
};

}    // namespace semantic_sdp
