// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <utility>
#include <vector>

#include "./util.h"
#include "./rtcp_feedback_info.h"

namespace semantic_sdp {

class CCodecInfo;
using CodecInfo = std::unique_ptr<CCodecInfo>;

class CCodecInfo {
 public:
    using RTCPFBs = std::unordered_set<RTCPFeedbackInfo>;

 private:
    std::string         m_codec;
    int                 m_type;
    std::optional<int>  m_rtx;
    std::optional<int>  m_channels;
    ParamsMap           m_params;
    RTCPFBs             m_rtcpfbs;

 public:
    /**
     * @constructor CCodecInfo
     * @param [in] codec Codec name
     * @param [in] type the payload type number
     * @param [in] params Format params for codec
     */
    CCodecInfo(const std::string& codec, const int type, const ParamsMap& params = {})
        : m_codec(codec)
        , m_type(type) {
        AddParams(params);
    }

    /**
     * Create a clone of this Codec info object
     * @returns codec info
     */
    CodecInfo Clone() const {
        auto cloned = std::make_unique<CCodecInfo>(m_codec, m_type, m_params);
        cloned->SetRTX(GetRTX());
        for (const auto& rtcfb : m_rtcpfbs)
            cloned->AddRTCPFeedback(rtcfb->Clone());
        if (HasChannels())
            cloned->SetChannels(GetChannels());
        return cloned;
    }

    /**
     * Set the RTX payload type number for this codec
     * @param rtx
     */
    void SetRTX(const std::optional<int> rtx) {
        m_rtx = rtx;
    }

    /**
     * Get payload type for codec
     * @returns payload type
     */
    auto GetType() const {
        return m_type;
    }

    /**
     * Set the payload type for codec
     * @param type
     */
    void SetType(const int type) {
        m_type = type;
    }

    /**
     * Get codec name
     * @returns codec name
     */
    const auto& GetCodec() const {
        return m_codec;
    }

    /**
     * Get codec format parameters
     */
    const auto& GetParams() const {
        return m_params;
    }

    /**
     * Add codec info params
     * @param params
     */
    void AddParams(const ParamsMap& params) {
        for (const auto& it : params)
            m_params[it.first] = it.second;
    }

    /**
     * Add codec info param
     * @param [in] key
     * @param [in] value
     */
    void AddParam(const std::string& key, const std::string& value) {
        m_params[key] = value;
    }

    /**
     * Check if codec has requested param
     * @param [in] key
     * @returns boolean
     */
    bool HasParam(const std::string& key) const {
        const auto it = m_params.find(key);
        return (it != m_params.end());
    }

    /**
     * Get param
     * @param [in] key
     * @param [in] default_value default value if param is not found
     * @returns param
     */
    const std::string& GetParam(const std::string& key, const std::string& default_value = {}) {
        const auto it = m_params.find(key);
        if (it != m_params.end())
            return it->second;
        return default_value;
    }

    /**
     * Check if this codec has an associated RTX payload type
     * @returns boolean
     */
    bool HasRTX() const {
        return m_rtx.has_value();
    }

    /**
     * Get the associated RTX payload type for this codec
     * @returns payload type
     */
    std::optional<int> GetRTX() const {
        return m_rtx;
    }

    /**
     * Check if this codec has number of channels
     * @returns boolean
     */
    bool HasChannels() const {
        return m_channels.has_value();
    }

    /**
     * Get the number of channels
     * @returns number of channels
     */
    std::optional<int> GetChannels() const {
        return m_channels;
    }

    /**
     * Set the number of channels
     * @param [in] channels
     */
    void SetChannels(const std::optional<int>& channels) {
        m_channels = channels;
    }

    /**
     * Add an RTCP feedback parameter to this codec type
     * @param [in] rtcpfb RTCP feedback info object
     */
    void AddRTCPFeedback(RTCPFeedbackInfo&& rtcpfb) {
        m_rtcpfbs.insert(std::move(rtcpfb));
    }

    /**
     * Get all extensions rtcp feedback parameters in this codec info
     * @returns all extensions rtcp feedback parameters
     */
    const auto& GetRTCPFeedbacks() const {
        return m_rtcpfbs;
    }
};

using CodecsMap = std::unordered_map<int, CodecInfo>;

/**
 * Create a map of CodecInfo from codec names.
 * Payload type is assigned dinamically
 * @param [in] names
 * @param [in] rtx Should we add rtx?
 * @param [in] rtcpfbs RTCP feedback params
 * @returns map of CodecInfo
 */
CodecsMap MapFromNames(const std::vector<std::string>& names, bool rtx, const std::vector<RTCPFeedbackInfo>& rtcpfbs) {
    CodecsMap codecs;
    int dyn = 96;    // Base dyn payload
    for (const auto& element : names) {
        int pt = 0;
        // We can add params to codec names
        auto params = split(element, ';');
        // Get codec name from first param, and remove if from the param list
        auto name = params.front();
        params.pop_front();
        to_lower_case(&name);
        trim(&name);
        // Check name
        if (name == "pcmu")
            pt = 0;
        else if (name == "pcma")
            pt = 8;
        else
            // Dynamic
            pt = ++dyn;
        // Create new codec
        auto codec = std::make_unique<CCodecInfo>(name, pt);
        // Set default number of channels
        if (name == "opus")
            // two
            codec->SetChannels(2);
        else if (name == "multiopus")
            // 5.1 by default
            codec->SetChannels(6);
        // Check if we have to add rtx
        if (rtx && (name != "ulpfec") && (name != "flexfec-03") && (name != "red"))
            codec->SetRTX(++dyn);

        // Append all the  rtcp feedback info
        for (const auto& rtcpfb : rtcpfbs)
            codec->AddRTCPFeedback(std::make_unique<CRTCPFeedbackInfo>(rtcpfb->GetId(), rtcpfb->GetParams()));
        // Add params if any more
        for (const auto& param_element : params) {
            auto param = split(param_element, '=');
            const auto key = trim_copy(param.front());
            param.pop_front();
            const auto value = trim_copy(param.front());
            codec->AddParam(key, value);
        }
        codecs.emplace(pt, std::move(codec));
    }
    return codecs;
}

/**
 * Create a map of CodecInfo from codec names.
 * Payload type is assigned dinamically
 * @param [in] codecs
 * @param [in] rtx Should we add rtx?
 * @param [in] rtcpfbs RTCP feedback params
 * @returns map of CodecInfo
 */
CodecsMap MapFromNames(const CodecsMap& codecs, bool rtx, const std::vector<RTCPFeedbackInfo>& rtcpfbs) {
    std::vector<std::string> names;
    for (const auto& codec_it : codecs) {
        names.push_back(codec_it.second->GetCodec());
    }
    return MapFromNames(names, rtx, rtcpfbs);
}

}    // namespace semantic_sdp
