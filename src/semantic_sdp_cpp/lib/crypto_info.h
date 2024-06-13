// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

namespace semantic_sdp {

class CCryptoInfo;
using CryptoInfo = std::unique_ptr<CCryptoInfo>;

/**
 * SDES peer info
 */
class CCryptoInfo {
 private:
    int                m_tag;
    std::string        m_suite;
    std::string        m_key_params;
    std::string        m_session_params;

 public:
    /**
     * @constructor for CCryptoInfo
     * @param [in] tag
     * @param [in] suite
     * @param [in] key_params
     * @param [in] session_params
     */
    CCryptoInfo(const int tag, const std::string& suite,
                const std::string& key_params, const std::string& session_params)
    : m_tag(tag)
    , m_suite(suite)
    , m_key_params(key_params)
    , m_session_params(session_params)
    {}

    /**
     * Create a clone of this SDES info object
     * @returns crypto info
     */
    CryptoInfo Clone() {
        return std::make_unique<CCryptoInfo>(m_tag, m_suite, m_key_params, m_session_params);
    }

    /**
     * Return the SDES session params
     * @returns session params
     */
    const auto& GetSessionParams() const {
        return m_session_params;
    }

    /**
     * Return the SDES key params
     * @returns key params
     */
    const auto& GetKeyParams() const {
        return m_key_params;
    }

    /**
     * Returns the chypher suite
     * @returns suite
     */
    const auto& GetSuite() const {
        return m_suite;
    }

    /**
     * Get SDES tag
     * @returns tag
     */
    const auto& GetTag() const {
        return m_tag;
    }
};

}    // namespace semantic_sdp
