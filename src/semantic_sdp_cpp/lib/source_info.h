// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

#include "./util.h"

namespace semantic_sdp {

class CSourceInfo;
using SourceInfo = std::unique_ptr<CSourceInfo>;

/**
 * Strem Source information
 */
class CSourceInfo {
 private:
    int             m_ssrc;
    std::string     m_track_id;
    std::string     m_cname;
    std::string     m_stream_id;

 public:
    /**
     * constructor for CSourceInfo
     * @param [in] ssrc
     */
    explicit CSourceInfo(const int ssrc)
    : m_ssrc(ssrc)
    {}

    /**
     * Create a clone of this source info object
     * @returns source info
     */
    SourceInfo Clone() const {
        auto clone = std::make_unique<CSourceInfo>(m_ssrc);
        clone->SetCName(m_cname);
        clone->SetStreamId(m_stream_id);
        clone->SetTrackId(m_track_id);
        return clone;
    }

    /**
     * Get source CName
     * @returns CName
     */
    const std::string& GetCName() const {
        return m_cname;
    }

    /**
     * Set source CName
     * @param [in] cname
     */
    void SetCName(const std::string& cname) {
        m_cname = cname;
    }

    /**
     * Get associated stream id
     * @returns stream id
     */
    auto GetStreamId() const {
        return m_stream_id;
    }

    /**
     * Set associated stream id for this ssrc
     * @param [in] stream_id
     */
    void SetStreamId(const std::string& stream_id) {
        m_stream_id = stream_id;
    }

    /**
     * Get associated track id
     * @returns track id
     */
    auto GetTrackId() const {
        return m_track_id;
    }

    /**
     * Set associated track id for this ssrc
     * @param [in] track_id
     */
    void SetTrackId(const std::string& track_id) {
        m_track_id = track_id;
    }

    /**
     * Get ssrc from source
     * @returns ssrc
     */
    auto GetSSRC() const {
        return m_ssrc;
    }
};

}    // namespace semantic_sdp
