// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "./util.h"
#include "./track_encoding_info.h"

namespace semantic_sdp {

class CTrackInfo;
using TrackInfo = std::unique_ptr<CTrackInfo>;

/**
 * Media Track information
 */
class CTrackInfo {
 public:
    using Groups = std::vector<SourceGroupInfo>;

 private:
    MediaType           m_media;
    std::string         m_id;
    std::string         m_media_id;
    std::vector<int>    m_ssrcs;
    Groups              m_groups;
    EncodingsListList   m_encodings;

 public:
    /**
     * constructor for TrackInfo
     * @param [in] media Media type
     * @param [in] id Track id
     */
    CTrackInfo(MediaType media, const std::string& id)
    : m_media(media)
    , m_id(id)
    {}

    /**
     * Create a clone of this track info object
     * @returns track info
     */
    TrackInfo Clone() const {
        auto cloned = std::make_unique<CTrackInfo>(m_media, m_id);
        cloned->SetMediaId(m_media_id);
        for (const auto& ssrc : m_ssrcs)
            cloned->AddSSRC(ssrc);
        for (const auto& group : m_groups)
            cloned->AddSourceGroup(group->Clone());
        for (const auto& alternatives : m_encodings) {
            EncodingsList alternatives_;
            // For each alternative
            for (const auto& alternative : alternatives)
                alternatives_.push_back(alternative->Clone());
            cloned->AddAlternativeEncodings(std::move(alternatives_));
        }
        return cloned;
    }

    /**
     * Get media type
     * @returns media type
     */
    const auto& GetMedia() const {
        return m_media;
    }

    /**
     * Set the media line id this track belongs to. Set to null for first media line of the media type
     * @param [in] mediaId MediaInfo id
     */
    void SetMediaId(const std::string& mediaId) {
        m_media_id = mediaId;
    }

    /**
     * Returns the MediaInfo id this track belongs two (unified) or undefined if indiferent (plan B)
     * @returns media id
     */
    const auto& GetMediaId() const {
        return m_media_id;
    }

    /**
     * Get track id
     * @returns track id
     */
    const auto& GetId() const {
        return m_id;
    }

    /**
     * Add ssrc for this track
     * @param ssrc
     */
    void AddSSRC(int ssrc) {
        m_ssrcs.push_back(ssrc);
    }

    /**
     * Get all
     * @returns all ssrcs
     */
    const auto& GetSSRCs() const {
        return m_ssrcs;
    }

    /**
     * Add source group to track
     * @param [in] group
     */
    void AddSourceGroup(SourceGroupInfo&& group) {
        m_groups.push_back(std::move(group));
    }

    /**
     * Get the source group fot the desired type
     * @param [in] schematics Group type
     * @returns source group
     */
    const SourceGroupInfo* getSourceGroup(const std::string& schematics) const {
        const auto schema = to_lower_case_copy(schematics);
        for (const auto& group : m_groups) {
            if (to_lower_case_copy(group->GetSemantics()) == schema)
                return &group;
        }
        return nullptr;
    }

    /**
     * Get all source groups for this track
     * @returns source groups
     */
    const auto& GetSourceGroups() const {
        return m_groups;
    }

    /**
     * Check if track has a group for this type
     * @param [in] schematics
     * @returns boolean
     */
    bool HasSourceGroup(const std::string& schematics) const {
        return std::any_of(m_groups.cbegin(), m_groups.cend(),
                            [&schematics](const SourceGroupInfo& group) {
                                return eq_case_insensitive(group->GetSemantics(), schematics);
                                });
    }

    /**
     * Get simulcast encoding information for this track (if any)
     * @returns encoding information
     */
    const auto& GetEncodings() const {
        return m_encodings;
    }

    /**
     * Add simulcast encoding information for this track
     * @param [in] encoding Simulcast encoding info
     */
    void AddEncoding(TrackEncodingInfo&& encoding) {
        EncodingsList encodings;
        encodings.push_back(std::move(encoding));
        m_encodings.push_back(std::move(encodings));
    }

    /**
     * Add simulcast encoding information for this track
     * @param [in] alternatives Simulcast encoding info
     */
    void AddAlternativeEncodings(EncodingsList&& alternatives) {
        m_encodings.push_back(std::move(alternatives));
    }

    /**
     * Add simulcast encoding information for this track
     * @param [in] encodings Simulcast encoding info
     */
    void SetEncodings(EncodingsListList&& encodings) {
        m_encodings = std::move(encodings);
    }
};

}    // namespace semantic_sdp
