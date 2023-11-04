// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <filesystem>
#include <bits/stdc++.h> 
#include <math.h>
#include <string.h>

#include <iwav.hpp>
#include <dft.hpp>
#include <opng.hpp>
#include <heatmap.hpp>

namespace fs = std::filesystem;

char* string_to_char_arr(std::string s){
    int len = s.length();
    char* carr = new char[len + 1];
    for(int i = 0; i < len; ++i)
        carr[i] = s[i];
    carr[len] = '\0';
    return carr;
}

int main(void){
    std::string s;
    std::cin >> s;
    char* wav_path = string_to_char_arr(s);

    std::cin >> s;
    char* result_dir = string_to_char_arr(s);

    float window_time;
    std::cin >> window_time;
    if(window_time <= 0){
        std::cout << "length of window [s] is negative" << std::endl;
        return 1;
    }

    wav* w = get_wav(wav_path);

    float temp_f = (float)w->freq * window_time;
    temp_f = log2f(temp_f);
    int temp_d = (int)(temp_f + 0.5);
    unsigned int window_len = 1;
    for(int i = 0; i < temp_d; ++i)
        window_len *= 2;

    unsigned int width, height;
    width = (int)((float)w-> data_len / (float)(window_len / 2)) - 1;
    height = window_len;

    int path_len = 0;
    while(wav_path[path_len] != '\0')
        ++ path_len;
    ++path_len;

    char* graph_path = new char[path_len + 18];
    // 18 = |/spectrogram_0.png|
    strcpy(graph_path, result_dir);
    strcat(graph_path, "/spectrogram_0.png");

    float* data_f = new float[window_len];
    float* spectrogram_max = new float[w->channel];

    for(unsigned short c = 0; c < w->channel; ++c){
        ++graph_path[path_len + 12];

        spectrogram_max[c] = 0.0;

        float** spectrogram = new float*[width];
        for(unsigned x = 0; x < width; ++x){
            unsigned int d = x * (window_len / 2);
            for(unsigned int i = 0; i < window_len; ++i)
                data_f[i] = w->datas[c][d + i];
            spectrogram[x] = fft(window_len, data_f);

            for(unsigned int y = 0; y < height; ++y)
                if(spectrogram[x][y] > spectrogram_max[c])
                    spectrogram_max[c] = spectrogram[x][y];
        }

        opng* png = new opng(
            width, height,
            get_heatmap(width, height, 0.0, spectrogram_max[c], spectrogram)
        );

        png->write(graph_path);

        delete png;

        for(unsigned int x = 0; x < width; ++x)
            delete spectrogram[x];
        delete spectrogram;
    }

    delete graph_path, data_f;

    char* info_path = new char[path_len + 22];
    // 22 = |/spectrogram_info.json|
    strcpy(info_path, result_dir);
    strcat(info_path, "/spectrogram_info.json");

    std::ofstream f;
    f.open(info_path, std::ios::out);
    f << "{\"window_len\":" << window_len;
    f << ",\"maxs\":[" << spectrogram_max[0];
    for(unsigned short c = 1; c < w->channel; ++c)
        f << "," << spectrogram_max[c];
    f << "]";
    f << "}";
    f.close();

    delete info_path, wav_path, result_dir, w;

    return 0;
}