// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <string.h>

#include <parse_stdin.hpp>
#include <iwav.hpp>
#include <linegraph.hpp>

namespace fs = std::filesystem;

int main(void){
    char *wav_path, *result_dir;

    if(!get_paths(&wav_path, &result_dir))
        return 1;

    wav* w = get_wav(wav_path);

    float y_max;
    if(w->quant == 1)
        y_max = 127;
    else
        y_max = 32767;

    float* data_f = new float[w->data_len];

    for(unsigned short c = 0; c < w->channel; ++c){
        char* graph_path_r = set_path_index("time_graph_0.png", c);
        char* graph_path = join_path(result_dir, graph_path_r);

        for(unsigned long i = 0; i < w->data_len; ++i)
            data_f[i] = (float)w->datas[c][i];
        plot_data(2048, 1024, graph_path, w->data_len, data_f, -y_max, y_max);

        delete graph_path;


        char* info_path_r = set_path_index("time_graph_info_0.json", c);
        char* info_path = join_path(result_dir, info_path_r);
        delete info_path_r;

        std::fstream f;
        f.open(info_path, std::ios::out);
        f << "{";
        f << "\"type\":\"linegraph\"";
        f << ",\"graph_path\":\"" << graph_path_r << "\"";
        f << ",\"xlabel\":\"time [s]\"";
        f << ",\"xmin\":" << 0;
        f << ",\"xmax\":" << (float)w->data_len / (float)w->freq;
        f << ",\"ylabel\":\"amplitude\"";
        f << ",\"ymin\":-1";
        f << ",\"ymax\":1";
        f << "}";
        f.close();

        delete info_path, graph_path_r;
    }

    delete data_f, w;

    return 0;
}