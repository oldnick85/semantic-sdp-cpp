// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "./util.h"
#include "./direction_way.h"

namespace semantic_sdp {

class CRIDInfo;
using RIDInfo = std::unique_ptr<CRIDInfo>;

/**
 * RID info
 */
class CRIDInfo {
 private:
    std::string         m_id;
    DirectionWay        m_direction;
    std::vector<int>    m_formats;
    ParamsMap           m_params;

 public:
    /**
     * constructor for CDTLSInfo
     * @param [in] id rid value
     * @param [in] direction direction
     */
    CRIDInfo(const std::string& id, const DirectionWay direction)
    : m_id(id)
    , m_direction(direction)
    {}

    /**
     * Create a clone of this RID info object
     * @returns RID info
     */
    RIDInfo Clone() const {
        auto cloned = std::make_unique<CRIDInfo>(m_id, m_direction);
        cloned->SetFormats(m_formats);
        cloned->SetParams(m_params);
        return cloned;
    }

    /**
     * Get the rid id value
     * @returns {String}
     */
    const auto& GetId() const {
        return m_id;
    }

    /**
     * Get rid direction
     * @returns {DirectionWay}
     */
    auto GetDirection() const {
        return m_direction;
    }

    /**
     * Set direction setup
     * @param {DirectionWay} direction
     */
    void SetDirection(DirectionWay direction) {
        m_direction = direction;
    }

    /**
     * Get pt formats for rid
     * @returns {Array<Number>}
     */
    const auto& GetFormats() const {
        return m_formats;
    }

    /**
     * Set pt formats for rid
     * @param {Array<Number>} formats
     */
    void SetFormats(const std::vector<int>& formats) {
        m_formats = formats;
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
};

using RIDsMap = std::unordered_map<std::string, RIDInfo>;

}    // namespace semantic_sdp
