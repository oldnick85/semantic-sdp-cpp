// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "./util.h"
#include "./simulcast_stream_info.h"

namespace semantic_sdp {

class CSimulcastInfo;
using SimulcastInfo = std::unique_ptr<CSimulcastInfo>;
/**
 * Simulcast information
 */
class CSimulcastInfo {
 private:
    std::vector<std::vector<SimulcastStreamInfo>>    m_send;
    std::vector<std::vector<SimulcastStreamInfo>>    m_recv;

 public:
    /**
     * constructor for CSimulcastInfo
     */
    CSimulcastInfo() = default;

    /**
     * Create a clone of this track info object
     * @returns simulcast info
     */
    SimulcastInfo Clone() const {
        auto cloned = std::make_unique<CSimulcastInfo>();
        for (const auto& streams : m_send) {
            std::vector<SimulcastStreamInfo> streams_cloned;
            for (const auto& stream : streams)
                streams_cloned.push_back(stream->Clone());
            cloned->AddSimulcastAlternativeStreams(DirectionWay::Send, std::move(streams_cloned));
        }
        for (const auto& streams : m_recv) {
            std::vector<SimulcastStreamInfo> streams_cloned;
            for (const auto& stream : streams)
                streams_cloned.push_back(stream->Clone());
            cloned->AddSimulcastAlternativeStreams(DirectionWay::Recv, std::move(streams_cloned));
        }
        return cloned;
    }

    /**
     * Add a simulcast alternative streams for the specific direction
     * @param [in] direction Which direction you want the streams for
     * @param [in] streams Stream info of all the alternatives
     */
    void AddSimulcastAlternativeStreams(DirectionWay direction, std::vector<SimulcastStreamInfo>&& streams) {
        if (direction == DirectionWay::Send)
            m_send.push_back(std::move(streams));
        else if (direction == DirectionWay::Recv)
            m_recv.push_back(std::move(streams));
    }

    /**
     * Add a single simulcast stream for the specific direction
     * @param [in] direction Which direction you want the streams for
     * @param [in] stream Stream info of the single alternative
     */
    void AddSimulcastStream(DirectionWay direction, SimulcastStreamInfo&& stream) {
        std::vector<SimulcastStreamInfo> streams;
        streams.push_back(std::move(stream));
        if (direction == DirectionWay::Send)
            m_send.push_back(std::move(streams));
        else if (direction == DirectionWay::Recv)
            m_recv.push_back(std::move(streams));
    }

    /**
     * Get all simulcast streams by direction
     * @param [in] direction Which direction you want the streams for
     * @returns streams
     */
    const std::vector<std::vector<SimulcastStreamInfo>>* GetSimulcastStreams(DirectionWay direction) const {
        if (direction == DirectionWay::Send)
            return &m_send;
        else if (direction == DirectionWay::Recv)
            return &m_recv;
        return nullptr;
    }
};

}    // namespace semantic_sdp
