// "Copyright 2024 <Oldnick85>"

#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <list>
#include <random>
#include <unordered_map>
#include <vector>

namespace semantic_sdp {

using ParamsMap = std::unordered_map<std::string, std::string>;

class TrackType {
 private:
    enum class Type {
        audio,
        video,
    };
    std::string audio_str{"audio"};
    std::string video_str{"video"};

    Type    type{Type::audio};
 public:
    const std::string& type_str() const {
        switch (type) {
        case Type::audio:       return audio_str;
        case Type::video:       return video_str;
        default:                break;
        }
        return audio_str;
    }
};

class MediaType {
 private:
    enum class Type {
        audio,
        video,
        application,
    };
    std::string audio_str{"audio"};
    std::string video_str{"video"};
    std::string application_str{"application"};

    Type    type{Type::audio};
 public:
    const std::string& type_str() const {
        switch (type) {
        case Type::audio:       return audio_str;
        case Type::video:       return video_str;
        case Type::application: return application_str;
        default:                break;
        }
        return audio_str;
    }
};

std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    std::string s;
    s.reserve(bytes.size()*2+1);
    for (const auto byte : bytes) {
        const auto h = byte / 16;
        const char hc = (h < 10) ? '0' + h : 'A' + h - 10;
        s += hc;
        const auto l = byte % 16;
        const char lc = (l < 10) ? '0' + l : 'A' + l - 10;
        s += lc;
    }
    return s;
}

std::vector<uint8_t> random_bytes(const std::size_t count) {
    std::vector<uint8_t> bytes;
    bytes.reserve(count);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 256);
    for (std::size_t i = 0; i < count; ++i)
        bytes.push_back(dist(rng));

    return bytes;
}

std::string to_lower_case_copy(const std::string &s) {
    std::string str{s};
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return s;
}

void to_lower_case(std::string* str) {
    if (str == nullptr)
        return;
    std::transform(str->begin(), str->end(), str->begin(), ::tolower);
}

bool eq_case_insensitive(const std::string &s1, const std::string &s2) {
    const auto s1_ = to_lower_case_copy(s1);
    const auto s2_ = to_lower_case_copy(s2);
    return (s1_ == s2_);
}

std::list<std::string> split(const std::string &s, char delim) {
    std::list<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// trim from start (in place)
inline void ltrim(std::string* s) {
    if (s == nullptr)
        return;
    s->erase(s->begin(), std::find_if(s->begin(), s->end(),
        [](unsigned char ch) {
            return !std::isspace(ch);
        }));
}

// trim from end (in place)
inline void rtrim(std::string* s) {
    if (s == nullptr)
        return;
    s->erase(std::find_if(s->rbegin(), s->rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s->end());
}

// trim from both ends (in place)
inline void trim(std::string* s) {
    if (s == nullptr)
        return;
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(&s);
    return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(&s);
    return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(&s);
    return s;
}

}    // namespace semantic_sdp
