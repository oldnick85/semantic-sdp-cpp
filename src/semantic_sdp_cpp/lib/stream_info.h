// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

#include "./util.h"
#include "./track_info.h"

namespace semantic_sdp {

class CStreamInfo;
using StreamInfo = std::unique_ptr<CStreamInfo>;

/**
 * Media Stream information
 */
class CStreamInfo {
 public:
    using Tracks = std::unordered_map<std::string, TrackInfo>;

 private:
    std::string        m_id;
    Tracks            m_tracks;

 public:
    /**
     * constructor for StreamInfo
     * @param [in] id
     */
    explicit CStreamInfo(const std::string& id)
    : m_id(id)
    {}

    /**
     * Create a clone of this stream info object
     * @returns stream info
     */
    StreamInfo Clone() const {
        auto cloned = std::make_unique<CStreamInfo>(m_id);
        for (const auto& track_it : m_tracks)
            cloned->AddTrack(track_it.second->Clone());
        return cloned;
    }

    /**
     * Get the media stream id
     * @returns stream id
     */
    const auto& GetId() const {
        return m_id;
    }

    /**
     * Add media track
     * @param [in] track
     */
    void AddTrack(TrackInfo&& track) {
        m_tracks.emplace(track->GetId(), std::move(track));
    }

    /**
     * Remove a media track from stream
     * @param [in] track Info object from the track
     * @returns if the track was present on track map or not
     */
    void RemoveTrack(const TrackInfo& track) {
        m_tracks.erase(track->GetId());
    }

    /**
     * Remove a media track from stream
     * @param [in] track_id Id of the track to remote
     * @returns if the track was present on track map or not
     */
    void RemoveTrackById(const std::string& track_id) {
        m_tracks.erase(track_id);
    }
    /**
     * Get first track for the media type
     * @param [in] media Track type
     * @returns track info
     */
    const TrackInfo* GetFirstTrack(const TrackType& media) {
        const auto media_type = to_lower_case_copy(media.type_str());
        for (const auto& track_it : m_tracks) {
            auto type = track_it.second->GetMedia().type_str();
            if (to_lower_case_copy(type) == media_type)
                return &track_it.second;
        }
        return nullptr;
    }

    /**
     * Get all tracks from the media stream
     * @returns all tracks
     */
    const auto& GetTracks() {
        return m_tracks;
    }

    /**
     * Remove all tracks from media sream
     */
    void RemoveAllTracks() {
        m_tracks.clear();
    }

    /**
     * Get track by id
     * @param [in] track_id
     * @returns track info
     */
    const TrackInfo* GetTrack(const std::string& track_id) {
        auto track_it = m_tracks.find(track_id);
        if (track_it != m_tracks.end())
            return &track_it->second;
        return nullptr;
    }
};

}    // namespace semantic_sdp
