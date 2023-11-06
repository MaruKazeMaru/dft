// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <string.h>

#include <parse_stdin.hpp>
#include <iwav.hpp>
#include <dft.hpp>
#include <linegraph.hpp>

int main(void){
    char *wav_path, *result_dir;

    if(!get_paths(&wav_path, &result_dir))
        return 1;

    wav* w = get_wav(wav_path);

    unsigned int window_len;
    if(!get_window_len(w->freq, &window_len)){
        delete w, wav_path, result_dir;
        return 1;
    }

    float start_time;
    std::cin >> start_time;
    if(start_time < 0){
        std::cout << "window start is negative" << std::endl;
        delete w, wav_path, result_dir;
        return 1;
    }

    unsigned int start = (unsigned int)(start_time * (float)w->freq);

    if(start + window_len > w->data_len){
        std::cout << "window size is too big" << std::endl;
        delete w, wav_path, result_dir;
        return 1;
    }

    float* data_f = new float[window_len];

    for(unsigned short c = 0; c < w->channel; ++c){
        char* graph_path_r = set_path_index("spec_graph_0.png", c);
        char* graph_path = join_path(result_dir, graph_path_r);

        for(unsigned int i = 0; i < window_len; ++i)
            data_f[i] = (float)w->datas[c][start + i];

        float* spec = fft(window_len, data_f);

        float spec_max = 0.0;
        for(unsigned int i = 0; i < window_len; ++i)
            if(spec[i] > spec_max)
                spec_max = spec[i];

        plot_data(2048, 1024, graph_path, window_len / 2 + 1, spec, 0.0, spec_max);

        delete spec, graph_path;


        char* info_path_r = set_path_index("spec_graph_info_0.json", c);
        char* info_path = join_path(result_dir, info_path_r);
        delete info_path_r;

        std::ofstream f;
        f.open(info_path, std::ios::out);
        f << "{";
        f << "\"type\":\"linegraph\"";
        f << ",\"graph_path\":\"" << graph_path_r << "\"";
        f << ",\"xlabel\":\"frequency [Hz]\"";
        f << ",\"xmin\":" << 0;
        f << ",\"xmax\":" << (float)w->freq / 2.0;
        f << ",\"ylabel\":\"intensity\"";
        f << ",\"ymin\":" << 0;
        f << ",\"ymax\":" << spec_max;
        f << ",\"start\":" << (float)start / (float)w->freq;
        f << "}";
        f.close();

        delete info_path, graph_path_r;
    }

    delete w, data_f, wav_path, result_dir;

    return 0;
}