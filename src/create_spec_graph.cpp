// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <filesystem>
#include <bits/stdc++.h> 
#include <math.h>
#include <string.h>

#include <iwav.hpp>
#include <dft.hpp>
#include <linegraph.hpp>

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

    if(!fs::exists(wav_path)){
        std::cout << "wav file doesn't exist" << std::endl;
        delete wav_path;
        return 1;
    }

    std::cin >> s;
    char* result_dir = string_to_char_arr(s);

    if(!fs::exists(result_dir)){
        fs::create_directory(result_dir);
    }
    else if(!fs::is_directory(result_dir)){
        std::cout << "output path already exists & it's not dir" << std::endl;
        delete wav_path, result_dir;
        return 1;
    }

    float window_time;
    std::cin >> window_time;
    if(window_time <= 0){
        std::cout << "length of window [s] is negative" << std::endl;
        delete wav_path, result_dir;
        return 1;
    }

    float start_time;
    std::cin >> start_time;
    if(start_time <= 0){
        std::cout << "window start is negative" << std::endl;
        delete wav_path, result_dir;
        return 1;
    }

    wav* w = get_wav(wav_path);


    float temp_f = (float)w->freq * window_time;
    temp_f = log2f(temp_f);
    int temp_d = (int)(temp_f + 0.5);
    unsigned int window_len = 1;
    for(int i = 0; i < temp_d; ++i)
        window_len *= 2;

    unsigned int start = (unsigned int)(start_time * (float)w->freq);

    if(start + window_len > w->data_len){
        std::cout << "window is too big" << std::endl;
        delete wav_path, result_dir, w;
        return 1;
    }

    int path_len = 0;
    while(wav_path[path_len] != '\0')
        ++ path_len;
    ++path_len;

    char* graph_path = new char[path_len + 17];
    // 17 = |/spec_graph_0.png|
    strcpy(graph_path, result_dir);
    strcat(graph_path, "/spec_graph_0.png");

    float* data_f = new float[window_len];
    float* spec_max = new float[w->channel];

    for(unsigned short c = 0; c < w->channel; ++c){
        ++graph_path[path_len + 11];

        for(unsigned int i = 0; i < window_len; ++i)
            data_f[i] = (float)w->datas[c][start + i];

        float* spec = fft(window_len, data_f);

        spec_max[c] = 0.0;
        for(unsigned int i = 0; i < window_len; ++i)
            if(spec[i] > spec_max[c])
                spec_max[c] = spec[i];

        plot_data(2048, 1024, graph_path, window_len, spec, 0.0, spec_max[c]);

        delete spec;
    }

    delete graph_path, data_f;

    char* info_path = new char[path_len + 21];
    // 21 = |/spec_graph_info.json|
    strcpy(info_path, result_dir);
    strcat(info_path, "/spec_graph_info.json");

    std::ofstream f;
    f.open(info_path, std::ios::out);
    f << "{\"window_len\":" << window_len;
    f << ",\"start\":" << start;
    f << ",\"maxs\":[" << spec_max[0];
    for(unsigned short c = 1; c < w->channel; ++c)
        f << "," << spec_max[c];
    f << "]";
    f << "}";
    f.close();

    delete info_path, wav_path, result_dir, w, spec_max;

    return 0;
}