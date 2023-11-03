// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <filesystem>
#include <string.h>

#include <iwav.hpp>

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

    int path_len = 0;
    while(argv[2][path_len] != '\0')
        ++ path_len;
    ++path_len;

    char* info_path = new char[path_len + 10];
    // 10 = |/info.json|
    strcpy(info_path, argv[2]);
    strcat(info_path, "/info.json");

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