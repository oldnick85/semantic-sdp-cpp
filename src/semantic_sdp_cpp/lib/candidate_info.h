// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <optional>
#include <memory>

namespace semantic_sdp {

class CCandidateInfo;
using CandidateInfo = std::unique_ptr<CCandidateInfo>;

class CCandidateInfo {
 private:
    std::string                 m_foundation;
    int                         m_component_id;
    std::string                 m_transport;
    int                         m_priority;
    std::string                 m_address;
    int                         m_port;
    std::string                 m_type;
    std::optional<std::string>  m_rel_addr;
    std::optional<int>          m_rel_port;

 public:
    /**
     * CanditateInfo constructor
     * @param [in] foundation
     * @param [in] componentId
     * @param [in] transport
     * @param [in] priority
     * @param [in] address
     * @param [in] port
     * @param [in] type
     * @param [in] rel_addr
     * @param [in] rel_port
     */
    CCandidateInfo(const std::string& foundation, const int component_id, const std::string& transport,
                    const int priority, const std::string& address, const int port, const std::string& type,
                    const std::optional<std::string>& rel_addr, const std::optional<int> rel_port)
        : m_foundation(foundation)
        , m_component_id(component_id)
        , m_transport(transport)
        , m_priority(priority)
        , m_address(address)
        , m_port(port)
        , m_type(type)
        , m_rel_addr(rel_addr)
        , m_rel_port(rel_port)
    {}

    /**
     * Check if the ice candadate has same info as us
     * @param [in] candidate ICE candadate to check against
     * @returns boolean
     */
    bool Equals(const CCandidateInfo& candidate) const {
        return (
            (candidate.m_foundation     == m_foundation)        &&
            (candidate.m_component_id == m_component_id)        &&
            (candidate.m_transport     == m_transport)          &&
            (candidate.m_priority     == m_priority)            &&
            (candidate.m_address     == m_address)              &&
            (candidate.m_port         == m_port)                &&
            (candidate.m_type         == m_type)                &&
            (candidate.m_rel_addr     == m_rel_addr)            &&
            (candidate.m_rel_port     == m_rel_port));
    }

    /**
     * Check if the ice candadate has same info as us
     * @param [in] candidate ICE candadate to check against
     * @returns boolean
     */
    bool Equals(const CandidateInfo& candidate) const {
        return (
            (candidate->m_foundation == m_foundation)           &&
            (candidate->m_component_id == m_component_id)       &&
            (candidate->m_transport     == m_transport)         &&
            (candidate->m_priority     == m_priority)           &&
            (candidate->m_address     == m_address)             &&
            (candidate->m_port         == m_port)               &&
            (candidate->m_type         == m_type)               &&
            (candidate->m_rel_addr     == m_rel_addr)           &&
            (candidate->m_rel_port     == m_rel_port));
    }

    /**
     * Create a clone of this Candidate info object
     * @returns candidate info
     */
    CandidateInfo Clone() const {
        auto c = std::make_unique<CCandidateInfo>(
            m_foundation,
            m_component_id,
            m_transport,
            m_priority,
            m_address,
            m_port,
            m_type,
            m_rel_addr,
            m_rel_port);
        return c;
    }

    /**
     * Get the candidate foundation
     * @returns foundation
     */
    const auto& GetFoundation() const {
        return m_foundation;
    }

    /**
     * Get the candidate component id
     * @returns component id
     */
    auto GetComponentId() const {
        return m_component_id;
    }

    /**
     * Get the candidate transport type
     * @returns transport type
     */
    const auto& GetTransport() const {
        return m_transport;
    }

    /**
     * Get the candidate priority
     * @returns priority
     */
    auto GetPriority() const {
        return m_priority;
    }

    /**
     * Get the candidate IP address
     * @returns IP address
     */
    const auto& GetAddress() const {
        return m_address;
    }

    /**
     * Get the candidate IP port
     * @returns IP port
     */
    auto GetPort() const {
        return m_port;
    }

    /**
     * Get the candidate type
     * @returns type
     */
    const auto& GetType() const {
        return m_type;
    }

    /**
     * Get the candidate related IP address for relfexive candidates
     * @returns related IP address
     */
    const auto& GetRelAddr() const {
        return m_rel_addr;
    }

    /**
     * Get the candidate related IP port for relfexive candidates
     * @returns related IP port
     */
    auto GetRelPort() const {
        return m_rel_port;
    }
};

}    // namespace semantic_sdp
