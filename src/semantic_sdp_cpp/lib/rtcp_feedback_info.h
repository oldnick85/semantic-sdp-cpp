// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <vector>

namespace semantic_sdp {

/**
 * RTCP Feedback parameter
 */
class CRTCPFeedbackInfo;
using RTCPFeedbackInfo = std::unique_ptr<CRTCPFeedbackInfo>;

class CRTCPFeedbackInfo {
 private:
    std::string                 m_id;
    std::vector<std::string>    m_params;

 public:
    /**
     * constructor for CRTCPFeedbackInfo
     * @param [in] id RTCP feedback id
     * @param [in] params RTCP feedback params
     */
    CRTCPFeedbackInfo(const std::string& id, const std::vector<std::string>& params)
        : m_id(id)
        , m_params(params)
    {}

    /**
     * Create a clone of this RTCPFeedbackParameter info object
     * @returns RTCP feedback info
     */
    RTCPFeedbackInfo Clone() const {
        return std::make_unique<CRTCPFeedbackInfo>(m_id, m_params);
    }

    /**
     * Get id fo the rtcp feedback parameter
     * @returns feedback parameter
     */
    const auto& GetId() const {
        return m_id;
    }

    /**
     * Get codec  rtcp feedback parameters
     * @returns parameters
     */
    const auto& GetParams() const {
        return m_params;
    }
};

}    // namespace semantic_sdp
