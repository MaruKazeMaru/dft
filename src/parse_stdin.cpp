// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <parse_stdin.hpp>
#include <iostream>
#include <filesystem>
#include <math.h>

namespace fs = std::filesystem;

char* string_to_char_arr(std::string s){
    int len = s.length();
    char* carr = new char[len + 1];
    for(int i = 0; i < len; ++i)
        carr[i] = s[i];
    carr[len] = '\0';
    return carr;
}


bool get_paths(char** wav_path, char** result_dir){
    std::string s;
    std::cin >> s;
    if(!fs::exists(s)){
        std::cout << "input wav file doesn't exist" << std::endl;
        return false;
    }
    *wav_path = string_to_char_arr(s);

    std::cin >> s;
    if(!fs::exists(s)){
        fs::create_directory(s);
    }
    else if(!fs::is_directory(s)){
        delete *wav_path;
        std::cout << "output path is not directory" << std::endl;
        return false;
    }
    *result_dir = string_to_char_arr(s);

    return true;
}


bool get_window_len(unsigned int freq, unsigned int* window_len){
    float window_time;
    std::cin >> window_time;

    float temp_f = (float)freq * window_time;

    if(temp_f <= 0){
        std::cout << "window size is negative" << std::endl;
        return false;
    }

    temp_f = log2f(temp_f);
    int temp_d = (int)(temp_f + 0.5);

    if(temp_d < 0){
        std::cout << "window size is too small" << std::endl;
        return false;
    }

    *window_len = 1;
    for(int i = 0; i < temp_d; ++i)
        *window_len *= 2;

    return true;
}


char* join_path(char* dir, char* file){
    int dir_len = 0;
    while(dir[dir_len] != '\0')
        ++dir_len;

    int file_len = 0;    
    while(file[file_len] != '\0')
        ++file_len;

    char* path = new char[dir_len + file_len + 2];
    for(int i = 0; i < dir_len; ++i)
        path[i] = dir[i];
    path[dir_len] = '/';
    int d = dir_len + 1;
    for(int i = 0; i < file_len; ++i)
        path[d + i] = file[i];
    path[d + file_len] = '\0';

    return path;
}


char* set_path_index(const char* path, int index){
    int path_len = 0;
    while(path[path_len] != '\0')
        ++path_len;

    char* new_path = new char[path_len + 1];

    int n = 0;
    new_path[0] = path[0];
    for(int i = 1; i < path_len; ++i){
        new_path[i] = path[i];
        if(path[i - 1] == '0' && path[i] == '.')
            n = i - 1;
    }
    new_path[n] = '0' + index;
    new_path[path_len] = '\0';

    return new_path;
}
