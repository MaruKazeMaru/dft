// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __WAVIO_HPP__
#define __WAVIO_HPP__

#include <iostream>
#include <fstream>

class wav_format_error: public std::runtime_error{
    public:
    wav_format_error(const char* msg):runtime_error(msg){};
};

class wav{
    public:
    unsigned int freq;
    unsigned short quant;
    unsigned short channel;
    unsigned int data_len;
    int** datas;

    wav(
        unsigned int freq, unsigned short quant, unsigned short channel,
        unsigned int data_len, int** datas
    );
    ~wav();

    float get_time_len();
};

wav* get_wav(char* file_path);

#endif