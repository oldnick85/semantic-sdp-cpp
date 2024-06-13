// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>

namespace semantic_sdp {

class CDataChannelInfo;
using DataChannelInfo = std::unique_ptr<CDataChannelInfo>;

/**
 * DataChannel info
 */
class CDataChannelInfo {
 private:
    int        m_port;
    int        m_max_message_size;

 public:
    /**
     * constructor for DataChannelInfo
     * @param [in] port
     * @param [in] max_message_size
     */
    CDataChannelInfo(const int port, const int max_message_size)
    : m_port(port)
    , m_max_message_size(max_message_size)
    {}

    /**
     * Create a clone of this D info object
     * @returns data channel info
     */
    DataChannelInfo Clone() const {
        return std::make_unique<CDataChannelInfo>(m_port, m_max_message_size);
    }

    /**
     * Returns the sctp port number
     * @returns port number
     */
    auto GetPort() const {
        return m_port;
    }

    /**
     * Get max message size
     * @returns size
     */
    auto GetMaxMessageSize() const {
        return m_max_message_size;
    }
};

}    // namespace semantic_sdp
