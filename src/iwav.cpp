// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <fstream>

#include <iwav.hpp>

#define LE 1
#define BE 2

bool comp4(char* l, const char* r){
    for(uint8_t i = 0; i < 4; ++i)
        if(l[i] != r[i])
            return false;

    return true;
}

char get_host_endian(){
    short x_d = 1;
    char* x_s = (char*)x_d;
    if(x_s[0] == 1)
        return LE;
    else
        return BE;
}

void change_endian(char* target, unsigned short byte, char from_endian, char to_endian){
    if(from_endian == to_endian)
        return;

    unsigned short n = byte / 2;
    char temp;
    for(unsigned short i = 0; i < n; ++i){
        temp = target[i];
        target[i] = target[byte - i - 1];
        target[byte - i - 1] = temp;
    }
    return;
}

// endian of from_arr should be little
int char_arr_to_int(char* from_arr, unsigned short byte, char host_endian){
    char* val_s = new char[4];
    for(unsigned short i = 0; i < 4; ++i)
        val_s = 0;

    char mask = 1 << 7;
    char sign;
    sign = from_arr[byte - 1];
    sign &= mask;

    for(unsigned short i = 0; i < byte; ++i){
        if(host_endian == LE)
            val_s[i] = from_arr[i];
        else
            val_s[3 - i] = from_arr[i];
    }

    if(host_endian == LE)
        val_s[3] |= sign;
    else
        val_s[0] |= sign;

    int val_d = (int)val_s;
    delete val_s;
    return val_d;
}

wav::~wav(){
    for(unsigned short c = 0; c < channel; ++c)
        delete datas[c];
    delete datas;
}

wav::wav(
    unsigned int freq, unsigned short quant, unsigned short channel,
    unsigned int data_len, int** datas
){
    this->freq = freq;
    this->quant = quant;
    this->channel = channel;
    this->data_len = data_len;
    this->datas = datas;
}

wav* get_wav(char* file_path){
    std::ifstream f(file_path, std::ios::in | std::ios::binary);

    if(!f)
        throw wav_format_error("cannot read file");

    unsigned short quant, channel;
    unsigned int freq, data_len;
    int** datas;

    char host_endian = get_host_endian();
    char* chunk_id = new char[4];
    char* temp4 = new char[4];
    char* temp2 = new char[2];

    //-------------
    // RIFF chunk
    //-------------
    f.read(chunk_id, 4);
    if(!comp4(chunk_id, "RIFF")){
        delete chunk_id, temp4, temp2;
        throw wav_format_error("format is not RIFF");
    }
    f.seekg(4, std::ios_base::cur);
    f.read(temp4, 4);
    if(!comp4(temp4, "WAVE")){
        delete chunk_id, temp4, temp2;
        throw wav_format_error("format is not WAVE");
    }

    bool fmt_read = false;
    bool data_read = false;
    while(!f.eof()){
        f.read(chunk_id, 4);
        f.read((char*)temp4, 4);
        change_endian(temp4, 4, LE, host_endian);
        unsigned int chunk_size = (unsigned int)temp4;

        //-------------
        // fmt chunk
        //-------------
        if(comp4(chunk_id, "fmt ")){
            if(chunk_size < 16){
                delete chunk_id, temp4, temp2;
                throw wav_format_error("fmt chunk is too small");
            }

            f.seekg(2, std::ios_base::cur);

            f.read(temp2, 2);
            change_endian(temp2, 2, LE, host_endian);
            channel = (unsigned short)temp2;

            f.read(temp4, 4);
            change_endian(temp4, 4, LE, host_endian);
            freq = (unsigned short)temp4;

            f.seekg(6, std::ios_base::cur);

            f.read(temp2, 2);
            change_endian(temp2, 2, LE, host_endian);
            quant = (unsigned short)temp2 / 8;

            if(quant > 4){
                delete chunk_id, temp4, temp2;
                throw wav_format_error("too large quntization bit");
            }

            f.seekg(chunk_size - 16, std::ios_base::cur);

            fmt_read = true;
        }
        //-------------
        // data chunk
        //-------------
        else if(comp4(chunk_id, "data")){
            if(!fmt_read){
                delete chunk_id, temp4, temp2;
                throw wav_format_error("fmt chunk missing");
            }

            data_len = chunk_size / (channel * quant);

            char* tempq = new char[quant];

            datas = new int*[channel];
            for(unsigned short c = 0; c < channel; ++c)
                datas[c] = new int[data_len];

            for(unsigned int i = 0; i < data_len; ++i){
                for(unsigned short c = 0; c < channel; ++c){
                    f.read(tempq, quant);
                    datas[c][i] = char_arr_to_int(tempq, quant, host_endian);
                }
            }

            delete tempq;

            data_read = true;
            break;
        }
        else{
            f.seekg(chunk_size, std::ios_base::cur);
        }
    }

    delete chunk_id, temp4, temp2;

    if(!data_read)
        throw wav_format_error("data chunk missing");

    return new wav(freq, quant, channel, data_len, datas);
}

