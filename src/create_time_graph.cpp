// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <filesystem>
#include <bits/stdc++.h> 
#include <math.h>
#include <string.h>

#include <iwav.hpp>
#include <linegraph.hpp>

namespace fs = std::filesystem;

int main(int argc, char** argv){
    if(argc < 3){
        std::cout << "few argument" << std::endl;
        return 1;
    }

    if(!fs::exists(argv[1])){
        std::cout << "wav file doesn't exist" << std::endl;
        return 1;
    }

    if(!fs::exists(argv[2])){
        fs::create_directory(argv[2]);
    }
    else if(!fs::is_directory(argv[2])){
        std::cout << "output path already exists & it's not dir" << std::endl;
        return 1;
    }

    wav* w = get_wav(argv[1]);

    float y_max;
    if(w->quant == 1)
        y_max = 127;
    else
        y_max = 32767;
    float* data_f = new float[w->data_len];
    int path_len = 0;
    while(argv[2][path_len] != '\0')
        ++ path_len;
    ++path_len;
    char* graph_path = new char[path_len + 17];
    // 17 = |/time_graph_0.png|
    strcpy(graph_path, argv[2]);
    strcat(graph_path, "/time_graph_0.png");

    for(unsigned short c = 0; c < w->channel; ++c){
        ++graph_path[path_len + 11];
        for(unsigned long i = 0; i < w->data_len; ++i)
            data_f[i] = (float)w->datas[c][i];
        plot_data(2048, 1024, graph_path, w->data_len, data_f, -y_max, y_max);
    }

    delete graph_path, data_f;

    char* info_path = new char[path_len + 15];
    // 15 = |/time_info.json|
    strcpy(info_path, argv[2]);
    strcat(info_path, "/time_info.json");

    std::ofstream f;
    f.open(info_path, std::ios::out);
    f << "{\"time\": " << (float)w->data_len / (float)w->freq;
    f << ", \"channel\": " << w->channel;
    f << ", \"freq\": " << w->freq;
    f << ", \"quant\": " << w->quant;
    f << ", \"data_len\": " << w->data_len;
    f << "}";
    f.close();

    delete info_path, w;

    return 0;
}