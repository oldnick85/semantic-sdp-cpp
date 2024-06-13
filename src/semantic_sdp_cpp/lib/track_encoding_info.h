// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "./util.h"
#include "./codec_info.h"

namespace semantic_sdp {

class CTrackEncodingInfo;
using TrackEncodingInfo = std::unique_ptr<CTrackEncodingInfo>;
/**
 * Simulcast encoding layer information for track
 */
class CTrackEncodingInfo {
 private:
    std::string     m_id;
    bool            m_paused;
    CodecsMap       m_codecs;
    ParamsMap       m_params;

 public:
    /**
     * constructor for DTLSInfo
     * @param [in] id rid value
     * @param [in] paused
     */
    explicit CTrackEncodingInfo(const std::string& id, bool paused = false)
    : m_id(id)
    , m_paused(paused)
    {}

    /**
     * Create a clone of this RID info object
     * @returns track encoding info
     */
    TrackEncodingInfo Clone() const {
        auto cloned = std::make_unique<CTrackEncodingInfo>(m_id, m_paused);
        for (const auto& codec_it : m_codecs)
            cloned->AddCodec(codec_it.second->Clone());
        cloned->SetParams(m_params);
        return cloned;
    }

    /**
     * Get the rid id value
     * @returns rid id
     */
    const auto& GetId() const {
        return m_id;
    }


    /**
     * Get codec information for this encoding
     * @returns codec information
     */
    const auto& GetCodecs() const {
        return m_codecs;
    }

    /**
     * Add codec info
     * @param [in] codec Codec Info
     */
    void AddCodec(CodecInfo&& codec) {
        const auto type = codec->GetType();
        m_codecs.emplace(type, std::move(codec));
    }

    /**
     * Get the rid params
     * @returns The params map
     */
    const auto& GetParams() const {
        return m_params;
    }

    /**
     * Set the rid params
     * @param [in] params rid params map
     */
    void SetParams(const ParamsMap& params) {
        m_params = params;
    }

    /**
     * Add an rid param
     * @param [in] id
     * @param [in] param
     */
    void AddParam(const std::string& id, const std::string& param) {
        m_params.emplace(id, param);
    }

    /**
     * Is the stream paused
     * @returns boolean
     */
    bool IsPaused() const {
        return m_paused;
    }
};

using EncodingsList = std::vector<TrackEncodingInfo>;
using EncodingsListList = std::vector<EncodingsList>;

}    // namespace semantic_sdp
