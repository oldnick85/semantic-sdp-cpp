// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

#include "./util.h"
#include "./direction_way.h"

namespace semantic_sdp {

class CSimulcastStreamInfo;
using SimulcastStreamInfo = std::unique_ptr<CSimulcastStreamInfo>;

/**
 * Simulcast streams info
 */
class CSimulcastStreamInfo {
 private:
    std::string     m_id;
    bool            m_paused;

 public:
    /**
     * constructor for CSimulcastStreamInfo
     * @param [in] id rid for this simulcast stream
     * @param [in] paused If this stream is initially paused
     */
    CSimulcastStreamInfo(const std::string& id, const bool paused)
    : m_id(id)
    , m_paused(paused)
    {}

    /**
     * Create a clone of this simulcast stream info object
     * @returns simulcast stream info
     */
    SimulcastStreamInfo Clone() const {
        return std::make_unique<CSimulcastStreamInfo>(m_id, m_paused);
    }

    /**
     * Is the stream paused
     * @returns boolean
     */
    auto IsPaused() const {
        return m_paused;
    }

    /**
     * Get rid in this stream
     * @returns rid
     */
    const auto& GetId() const {
        return m_id;
    }
};

}    // namespace semantic_sdp
