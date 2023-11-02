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

    int path_len = sizeof(argv[2]);
    char* graph_path = new char[path_len];
    strcpy(graph_path, argv[2]);
    strcat(graph_path, "/time_graph.png");
    char* info_path = new char[path_len];
    strcpy(info_path, argv[2]);
    strcat(info_path, "/time_info.json");

    wav* w = get_wav(argv[1]);

    std::cout << w->freq << std::endl;
    std::cout << w->quant << std::endl;
    std::cout << w->channel << std::endl;
    std::cout << w->data_len << std::endl;

    float* data_f = new float[w->data_len];
    for(unsigned long i = 0; i < w->data_len; ++i)
        data_f[i] = (float)w->datas[0][i];

    plot_data(2048, 1024, graph_path, w->data_len, data_f, -32767, 32767);

    std::ofstream f;
    f.open(info_path, std::ios::out);
    f << "{\"time\": " << (float)w->data_len / (float)w->freq << "}" << std::endl;
    f.close();

    delete data_f;
    delete w;
    delete graph_path;
    delete info_path;

    return 0;
}