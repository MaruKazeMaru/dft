// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <string.h>

#include <parse_stdin.hpp>
#include <iwav.hpp>
#include <dft.hpp>
#include <opng.hpp>
#include <heatmap.hpp>

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

    unsigned int width, height;
    width = (int)((float)w-> data_len / (float)(window_len / 2)) - 1;
    height = window_len / 2 + 1;

    float* data_f = new float[window_len];

    for(unsigned short c = 0; c < w->channel; ++c){
        char* graph_path_r = set_path_index("spectrogram_0.png", c);
        char* graph_path = join_path(result_dir, graph_path_r);

        float spectrogram_max = 0.0;
        float** spectrogram = new float*[width];
        for(unsigned x = 0; x < width; ++x){
            unsigned int d = x * (window_len / 2);
            for(unsigned int i = 0; i < window_len; ++i)
                data_f[i] = w->datas[c][d + i];
            spectrogram[x] = fft(window_len, data_f);

            for(unsigned int y = 0; y < height; ++y)
                if(spectrogram[x][y] > spectrogram_max)
                    spectrogram_max = spectrogram[x][y];
        }

        opng* png = new opng(
            width, height,
            get_heatmap(width, height, 0.0, spectrogram_max, spectrogram)
        );
        png->invert_y();
        png->write(graph_path);

        delete png, graph_path;
        for(unsigned int x = 0; x < width; ++x)
            delete spectrogram[x];
        delete spectrogram;


        char* info_path_r = set_path_index("spectrogram_info_0.json", c);
        char* info_path = join_path(result_dir, info_path_r);
        delete info_path_r;

        std::fstream f;
        f.open(info_path, std::ios::out);
        f << "{";
        f << "\"type\":\"heatmap\"";
        f << ",\"graph_path\":\"" << graph_path_r << "\"";
        f << ",\"xlabel\":\"time [s]\"";
        f << ",\"xmin\":" << 0;
        f << ",\"xmax\":" << (float)w->data_len / (float)w->freq;
        f << ",\"ylabel\":\"frequency [kHz]\"";
        f << ",\"ymin\":" << 0;
        f << ",\"ymax\":" << (float)w->freq / (2.0 * 1000.0);
        f << ",\"clabel\":\"intensity\"";
        f << "}";
        f.close();

        delete info_path, graph_path_r;
    }

    delete w, wav_path, result_dir, data_f;


    return 0;
}