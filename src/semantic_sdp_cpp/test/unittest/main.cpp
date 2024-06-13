// "Copyright [2024] <Oldnick85>"

#include "gtest/gtest.h"

#include "./direction.h"
#include "./direction_way.h"
#include "./candidate_info.h"
#include "./rtcp_feedback_info.h"
#include "./codec_info.h"
#include "./crypto_info.h"
#include "./data_channel_info.h"
#include "./dtls_info.h"
#include "./setup.h"
#include "./ice_info.h"
#include "./rid_info.h"
#include "./simulcast_info.h"
#include "./simulcast_stream_info.h"
#include "./source_group_info.h"
#include "./source_info.h"
#include "./track_encoding_info.h"
#include "./track_info.h"
#include "./media_info.h"
#include "./stream_info.h"

TEST(Base, compiling) {
    semantic_sdp::Direction dir = semantic_sdp::direction::ByValue("sendrecv");
    ASSERT_EQ(dir, semantic_sdp::Direction::SendRecv);
    semantic_sdp::DirectionWay dir_way = semantic_sdp::direction_way::ByValue("send");
    ASSERT_EQ(dir_way, semantic_sdp::DirectionWay::Send);
    semantic_sdp::Setup setup = semantic_sdp::setup::ByValue("actpass");
    ASSERT_EQ(setup, semantic_sdp::Setup::ActPass);
    semantic_sdp::CandidateInfo c_info;
    semantic_sdp::RTCPFeedbackInfo f_info;
    semantic_sdp::CodecInfo cod_info;
    semantic_sdp::CryptoInfo crp_info;
    semantic_sdp::DataChannelInfo dch_info;
    semantic_sdp::DTLSInfo dtls_info;
    semantic_sdp::ICEInfo ice_info;
    semantic_sdp::RIDInfo rid_info;
    semantic_sdp::SimulcastInfo s_info;
    semantic_sdp::SimulcastStreamInfo ss_info;
    semantic_sdp::SourceGroupInfo sg_info;
    semantic_sdp::SourceInfo src_info;
    semantic_sdp::TrackEncodingInfo te_info;
    semantic_sdp::TrackInfo t_info;
    semantic_sdp::MediaInfo media_info;
    semantic_sdp::StreamInfo stream_info;
    ASSERT_TRUE(true);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
