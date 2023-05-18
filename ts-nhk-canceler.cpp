#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

// Written with ChatGPT (GPT-4)

// 全国の NHK の TSID のリスト
// ref: http://soranikakaruhashi.blog.fc2.com/blog-entry-71.html
const std::vector<int> NHK_TSID_LIST = {
    // NHK総合/Eテレ・東京
    32736, 32737,
    // NHKEテレ・大阪
    32721,
    // NHKEテレ・名古屋
    32705,
    // NHK総合/Eテレ・札幌
    32592, 32593,
    // NHK総合/Eテレ・函館
    32576, 32577,
    // NHK総合/Eテレ・旭川
    32560, 32561,
    // NHK総合/Eテレ・帯広
    32544, 32545,
    // NHK総合/Eテレ・釧路
    32528, 32529,
    // NHK総合/Eテレ・北見
    32512, 32513,
    // NHK総合/Eテレ・室蘭
    32496, 32497,
    // NHK総合/Eテレ・仙台
    32480, 32481,
    // NHK総合/Eテレ・秋田
    32464, 32465,
    // NHK総合/Eテレ・山形
    32448, 32449,
    // NHK総合/Eテレ・盛岡
    32432, 32433,
    // NHK総合/Eテレ・福島
    32416, 32417,
    // NHK総合/Eテレ・青森
    32400, 32401,
    // NHK総合・前橋
    32352,
    // NHK総合・水戸
    32336,
    // NHK総合・宇都宮
    32304,
    // NHK総合/Eテレ・長野
    32272, 32273,
    // NHK総合/Eテレ・新潟
    32256, 32257,
    // NHK総合/Eテレ・甲府
    32240, 32241,
    // NHK総合・名古屋
    32224,
    // NHK総合/Eテレ・金沢
    32208, 32209,
    // NHK総合/Eテレ・静岡
    32192, 32193,
    // NHK総合/Eテレ・福井
    32176, 32177,
    // NHK総合/Eテレ・富山
    32160, 32161,
    // NHK総合・津
    32144,
    // NHK総合・岐阜
    32128,
    // NHK総合・大阪
    32112,
    // NHK総合・京都
    32096,
    // NHK総合・神戸
    32080,
    // NHK総合・和歌山
    32064,
    // NHK総合・奈良
    32048,
    // NHK総合・大津
    32032,
    // NHK総合/Eテレ・広島
    32016, 32017,
    // NHK総合/Eテレ・岡山
    32000, 32001,
    // NHK総合/Eテレ・松江
    31984, 31985,
    // NHK総合/Eテレ・鳥取
    31968, 31969,
    // NHK総合/Eテレ・山口
    31952, 31953,
    // NHK総合/Eテレ・松山
    31936, 31937,
    // NHK総合/Eテレ・高松
    31920, 31921,
    // NHK総合/Eテレ・徳島
    31904, 31905,
    // NHK総合/Eテレ・高知
    31888, 31889,
    // NHK総合/Eテレ・福岡
    31872, 31873,
    // NHK総合/Eテレ・北九州
    30848, 30849,
    // NHK総合/Eテレ・熊本
    31856, 31857,
    // NHK総合/Eテレ・長崎
    31840, 31841,
    // NHK総合/Eテレ・鹿児島
    31824, 31825,
    // NHK総合/Eテレ・宮崎
    31808, 31809,
    // NHK総合/Eテレ・大分
    31792, 31793,
    // NHK総合/Eテレ・佐賀
    31776, 31777,
    // NHK総合/Eテレ・沖縄
    31760, 31761,
    // BS: NHK BS1 (BS15/TS0: 929ch "Dpaダウンロード" を含む)
    16625,
    // BS: NHK BSプレミアム (BS03/TS1)
    16433,
};

bool is_nhk_transport_stream(int id) {
    return std::find(NHK_TSID_LIST.begin(), NHK_TSID_LIST.end(), id) != NHK_TSID_LIST.end();
}

int main() {
    #ifdef _WIN32
    // Set binary mode for stdin and stdout
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
    #endif

    unsigned char buffer[188];  // Use unsigned char here
    while (std::cin.read(reinterpret_cast<char*>(buffer), 1)) {
        if (buffer[0] != 0x47) { // Not a sync byte
            continue;
        }
        if (!std::cin.read(reinterpret_cast<char*>(buffer) + 1, sizeof(buffer) - 1)) { // Incomplete packet
            continue;
        }
        // Check Transport Error Indicator (buffer[1] & 0x80)
        if (buffer[1] & 0x80) { // Packet is corrupt
            continue;
        }
        // Get PID (buffer[1] & 0x1F and buffer[2])
        int pid = ((buffer[1] & 0x1F) << 8) | buffer[2];
        if (pid == 0x0) { // PAT
            int transport_stream_id = (buffer[8] << 8) | buffer[9];
            std::cerr << "transport_stream_id: " << transport_stream_id << std::endl;
            if (is_nhk_transport_stream(transport_stream_id)) {
                std::cerr << "NHK channel detected. exit." << std::endl;
                return 1;
            }
        }
        std::cout.write(reinterpret_cast<char*>(buffer), sizeof(buffer));
    }
    return 0;
}
