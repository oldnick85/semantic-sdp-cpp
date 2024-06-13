// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <utility>

#include "./util.h"
#include "./codec_info.h"
#include "./rid_info.h"
#include "./simulcast_info.h"
#include "./direction.h"
#include "./direction_way.h"
#include "./rtcp_feedback_info.h"
#include "./data_channel_info.h"

namespace semantic_sdp {

struct sSupportedMedia {
    CodecsMap                        codecs;
    std::vector<std::string>        extensions;
    bool                            simulcast;
    std::vector<RTCPFeedbackInfo>     rtcpfbs;
    bool                            rtx;
    DataChannelInfo                    datachannel;
};
using SupportedMedia = std::unique_ptr<sSupportedMedia>;

class CMediaInfo;
using MediaInfo = std::unique_ptr<CMediaInfo>;

using ExtensionsMap = std::unordered_map<int, std::string>;

/**
 * Media information (relates to a m-line in SDP)
 */
class CMediaInfo {
 private:
    std::string            m_id;
    MediaType             m_type;
    Direction            m_direction{Direction::SendRecv};
    ExtensionsMap        m_extensions;
    CodecsMap            m_codecs;
    RIDsMap                m_rids;
    SimulcastInfo         m_simulcast;
    int                    m_bitrate{0};
    std::string            m_control;
    DataChannelInfo        m_data_channel;

 public:
    /**
     * constructor for CMediaInfo
     * @param [in] id Media id
     * @param [in] type Media type
     */
    CMediaInfo(const std::string& id, MediaType type)
    : m_id(id)
    , m_type(type)
    {}

    /**
     * Clone MediaInfo object
     * @returns media info cloned object
     */
    MediaInfo Clone() const {
        auto cloned = std::make_unique<CMediaInfo>(m_id, m_type);
        cloned->SetDirection(m_direction);
        cloned->SetBitrate(m_bitrate);
        for (const auto& codec_it : m_codecs)
            cloned->AddCodec(codec_it.second->Clone());
        for (const auto& extension_it : m_extensions)
            cloned->AddExtension(extension_it.first, extension_it.second);
        for (const auto& rid_it : m_rids)
            cloned->AddRID(rid_it.second->Clone());
        if (m_simulcast != nullptr)
            cloned->SetSimulcast(m_simulcast->Clone());
        cloned->SetControl(m_control);
        if (m_data_channel)
            cloned->SetDataChannel(m_data_channel->Clone());
        return cloned;
    }

    /**
     * Get media type
     * @returns media type
     */
    const auto& GetType() const {
        return m_type;
    }

    /**
     * Get id (msid) for the media info
     * @returns msid
     */
    const auto& GetId() const {
        return m_id;
    }

    /**
     * Set id (msid) for the media info
     * @param [in] id
     */
    void SetId(const std::string& id) {
        m_id = id;
    }

    /**
     * Add rtp header extension support
     * @param [in] id
     * @param [in] name
     */
    void AddExtension(const int id, const std::string& name) {
        m_extensions.emplace(id, name);
    }

    /**
     * Add rid information
     * @param [in] ridInfo
     */
    void AddRID(RIDInfo&& rid_info) {
        m_rids.emplace(rid_info->GetId(), std::move(rid_info));
    }

    /**
     * Add Codec support information
     * @param [in] codecInfo Codec info object
     */
    void AddCodec(CodecInfo&& codec_info) {
        const auto type = codec_info->GetType();
        m_codecs.emplace(type, std::move(codec_info));
    }

    /**
     * Set codec map
     * @param [in] codecs Map of codec info objecs
     */
    void SetCodecs(CodecsMap&& codecs) {
        m_codecs = std::move(codecs);
    }

    /**
     * Get codec for payload type number
     * @param [in] type Payload type number
     * @returns codec info object
     */
    const CodecInfo* GetCodecForType(const int type) const {
        const auto codec_it = m_codecs.find(type);
        if (codec_it != m_codecs.end())
            return &codec_it->second;
        return nullptr;
    }

    /**
     * Get codec by codec name
     * @param [in] codec Codec name (eg: "vp8")
     * @returns codec info
     */
    const CodecInfo* GetCodec(const std::string& codec) const {
        const std::string codec_{to_lower_case_copy(codec)};
        for (const auto& codec_it : m_codecs) {
            const auto& info = codec_it.second;
            if (to_lower_case_copy(info->GetCodec()) == codec_)
                return &info;
        }
        return nullptr;
    }

    /**
     * Check if this media has information for this codec
     * @param [in] codec Codec name
     * @returns boolean
     */
    bool HasCodec(const std::string& codec) const {
        return (GetCodec(codec) != nullptr);
    }

    /**
     * Get all codecs in this media
     * @returns all codecs
     */
    const auto& GetCodecs() const {
        return m_codecs;
    }

    /**
     * Check if any of the codecs on the media description supports rtx
     * @returns boolean
     */
    bool HasRTX() const {
        for (const auto& codec_it : m_codecs) {
            const auto& info = codec_it.second;
            if (info->HasRTX())
                return true;
        }
        return false;
    }

    /**
     * Get all extensions registered in this media info
     * @returns extensions
     */
    const auto& GetExtensions() const {
        return m_extensions;
    }

    /**
     * Get all rids registered in  this media info
     * @returns rids
     */
    const auto& GetRIDs() const {
        return m_rids;
    }

    /**
     * Get rid info for id
     * @param [in] id rid value to get info for
     * @returns RID info
     */
    const RIDInfo* GetRID(const std::string& id) const {
        auto rid_it = m_rids.find(id);
        if (rid_it != m_rids.end())
            return &rid_it->second;
        return nullptr;
    }

    /**
     * Returns maximum bitrate for this media
     * @returns maximum bitrate
     */
    auto GetBitrate() const {
        return m_bitrate;
    }

    /**
     * Set maximum bitrate for this media
     * @param [in] bitrate
     */
    void SetBitrate(int bitrate) {
        m_bitrate = bitrate;
    }

    /**
     * Get media direction
     * @returns direction
     */
    auto GetDirection() const {
        return m_direction;
    }

    /**
     * Set media direction
     * @param [in] direction
     */
    void SetDirection(Direction direction) {
        m_direction = direction;
    }

    /**
     * Check if media has control attribute
     * @returns boolean
     */
    bool HasControl() const {
        return (!m_control.empty());
    }

    /**
     * Get control attribute
     * @returns attribute
     */
    const auto& GetControl() const {
        return m_control;
    }

    /**
     * Set control attribute
     * @param [in] control
     */
    void SetControl(const std::string& control) {
        m_control = control;
    }

    /**
     * Check if media has a dataChannel
     * @returns boolean
     */
    bool HasDataChannel() const {
        return m_data_channel != nullptr;
    }

    /**
     * Get dataChannel info
     * @returns data channel info
     */
    const auto& GetDataChannel() const {
        return m_data_channel;
    }

    /**
     * Set dataChannel info
     * @param [in] dataChannel info
     */
    void SetDataChannel(DataChannelInfo&& data_channel) {
        m_data_channel = std::move(data_channel);
    }

    /**
     * Helper usefull for creating media info answers.
     * - Will reverse the direction
     * - For each supported codec, it will change the payload type to match the offer and append it to the answer
     * - For each supported extension, it will append the ones present on the offer with the id offered
     * @param [in] supported Supported codecs and extensions to be included on answer
     * @returns media info
     */
    MediaInfo Answer(SupportedMedia supported) const {
        auto answer = std::make_unique<CMediaInfo>(m_id, m_type);

        if (supported != nullptr) {
            // Set reverse direction
            answer->SetDirection(direction::Reverse(m_direction));

            const auto& codecs = supported->codecs;
            const auto& data_channel = supported->datachannel;

            if (!codecs.empty()) {
                auto supportedCodecs = MapFromNames(codecs, supported->rtx, supported->rtcpfbs);

                for (const auto& codec_it : m_codecs) {
                    const auto& codec = codec_it.second;
                    // Try to find a matching supported codec
                    for (const auto& supported_it : supportedCodecs) {
                        const auto& supported_ = supported_it.second;
                        // Codec name must match
                        if (!eq_case_insensitive(supported_->GetCodec(), codec->GetCodec()))
                            continue;
                        // If it is h264, check packetization mode
                        if ((supported_->GetCodec() == "h264")
                            && supported_->HasParam("packetization-mode")
                            && (supported_->GetParam("packetization-mode")
                                != codec->GetParam("packetization-mode", "0")))
                            // Ignore
                            continue;
                        // If it is h264, check profile-level-id
                        if ((supported_->GetCodec() == "h264")
                            && supported_->HasParam("profile-level-id")
                            && codec->HasParam("profile-level-id")
                            && (supported_->GetParam("profile-level-id") != codec->GetParam("profile-level-id")))
                            continue;
                        // If it is multiopus, check num_streams
                        if ((supported_->GetCodec() == "multiopus")
                            && supported_->HasParam("num_streams")
                            && codec->HasParam("num_streams")
                            && (supported_->GetParam("num_streams") != codec->GetParam("num_streams")))
                            continue;
                        auto cloned = supported_->Clone();
                        // Change payload type number
                        cloned->SetType(codec->GetType());
                        cloned->SetRTX(codec->GetRTX());
                        // Use same number of channels
                        cloned->SetChannels(codec->GetChannels());
                        cloned->AddParams(codec->GetParams());
                        answer->AddCodec(std::move(cloned));
                        break;
                    }
                }
            }

            // Get extension set
            auto extensions = supported->extensions;
            // Add audio extensions
            for (const auto& extension_it : m_extensions) {
                const auto& id = extension_it.first;
                const auto& uri = extension_it.second;
                // If is supported
                if (std::any_of(extensions.cbegin(), extensions.cend(),
                    [uri](const std::string& extension) { return (extension == uri); }))
                    // Add to answer
                    answer->AddExtension(id, uri);
            }

            // If simulcast is enabled
            if (supported->simulcast && (m_simulcast != nullptr)) {
                // Create anser
                auto simulcast = std::make_unique<CSimulcastInfo>();
                // Get send streams
                auto send = m_simulcast->GetSimulcastStreams(DirectionWay::Send);
                if (send != nullptr) {
                    for (const auto& streams : *send) {
                        // Clone streams
                        std::vector<SimulcastStreamInfo> cloned;
                        for (const auto& stream : streams)
                            cloned.push_back(stream->Clone());
                        // Add alternatives in reverse order
                        simulcast->AddSimulcastAlternativeStreams(DirectionWay::Recv, std::move(cloned));
                    }
                }
                // Get recv streams
                auto recv = m_simulcast->GetSimulcastStreams(DirectionWay::Recv);
                if (recv != nullptr) {
                    for (const auto& streams : *recv) {
                        // Clone streams
                        std::vector<SimulcastStreamInfo> cloned;
                        for (const auto& stream : streams)
                            cloned.push_back(stream->Clone());
                        // Add alternatives in reverse order
                        simulcast->AddSimulcastAlternativeStreams(DirectionWay::Send, std::move(cloned));
                    }
                }
                // Add rids
                for (const auto& rid_it : m_rids) {
                    // TODO(Unknown): check if formats is in supported list
                    auto reversed = rid_it.second->Clone();
                    reversed->SetDirection(direction_way::Reverse(rid_it.second->GetDirection()));
                    answer->AddRID(std::move(reversed));
                }
                answer->SetSimulcast(std::move(simulcast));
            }

            // If we support datachannel
            if ((data_channel != nullptr) && (m_data_channel != nullptr)) {
                auto dataChannelInfo = std::make_unique<CDataChannelInfo>(
                    m_data_channel->GetPort(),
                    data_channel->GetMaxMessageSize() ?
                        data_channel->GetMaxMessageSize() :
                        data_channel->GetMaxMessageSize());
                answer->SetDataChannel(std::move(dataChannelInfo));
            }
        } else {
            answer->SetDirection(Direction::Inactive);
        }
        return answer;
    }

    /**
     * Get Simulcast info
     * @returns simulcast info
     */
    const auto& GetSimulcast() const {
        return m_simulcast;
    }

    /**
     * Set stream simulcast info
     * @param [in] simulcast Simulcast stream info
     */
    void SetSimulcast(SimulcastInfo&& simulcast) {
        m_simulcast = std::move(simulcast);
    }
};

/**
* Helper factory for creating media info objects.
* @param [in] type Media type
* @param [in] supported Supported media capabilities to be included on media info
* @returns media info
*/
MediaInfo Create(const MediaType& type, const SupportedMedia& supported) {
    // Create new media
    auto media_info = std::make_unique<CMediaInfo>(type.type_str(), type);
    if (supported != nullptr) {
        CodecsMap codecs;
        for (const auto& codec_it : supported->codecs)
            codecs.emplace(codec_it.first, codec_it.second->Clone());
        media_info->SetCodecs(std::move(codecs));
    } else {
        // Inactive
        media_info->SetDirection(Direction::Inactive);
    }
    return media_info;
}

}    // namespace semantic_sdp
