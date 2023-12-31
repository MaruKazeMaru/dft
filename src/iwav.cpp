// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <fstream>

#include <iwav.hpp>

bool comp4(char* l, const char* r){
    for(uint8_t i = 0; i < 4; ++i)
        if(l[i] != r[i])
            return false;

    return true;
}

wav::~wav(){
    for(unsigned short c = 0; c < channel; ++c)
        delete datas[c];
    delete datas;
}

wav::wav(
    unsigned int freq, unsigned short quant, unsigned short channel,
    unsigned int data_len, short** datas
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
    short** datas;

    //-------------
    // RIFF chunk
    //-------------
    char s[4];
    f.read(s, 4);
    if(!comp4(s, "RIFF"))
        throw wav_format_error("format is not RIFF");
    f.seekg(4, std::ios_base::cur);
    f.read(s, 4);
    if(!comp4(s, "WAVE"))
        throw wav_format_error("format is not WAVE");

    bool fmt_read = false;
    bool data_read = false;
    while(!f.eof()){
        f.read(s, 4);
        unsigned int chunk_size;
        f.read((char*)&chunk_size, 4);

        //-------------
        // fmt chunk
        //-------------
        if(comp4(s, "fmt ")){
            if(chunk_size < 16)
                throw wav_format_error("fmt chunk is too small");

            f.seekg(2, std::ios_base::cur);
            f.read((char*)&channel, 2);
            f.read((char*)&freq, 4);
            f.seekg(6, std::ios_base::cur);
            f.read((char*)&quant, 2);
            if(quant > 16)
                throw wav_format_error("too large quantization bit");
            quant /= 8;
            f.seekg(chunk_size - 16, std::ios_base::cur);

            fmt_read = true;
        }
        //-------------
        // data chunk
        //-------------
        else if(comp4(s, "data")){
            if(!fmt_read)
                throw wav_format_error("fmt chunk missing");

            data_len = chunk_size / (channel * quant);

            datas = new short*[channel];
            for(unsigned short c = 0; c < channel; ++c)
                datas[c] = new short[data_len];

            char temp1;
            short temp2;

            for(unsigned int i = 0; i < data_len; ++i){
                for(unsigned short c = 0; c < channel; ++c){
                    if(quant == 1){
                        f.read(&temp1, 1);
                        datas[c][i] = (short) temp1;
                    }
                    else{
                        f.read((char*)&temp2, 2);
                        datas[c][i] = temp2;
                    }
                }
            }

            data_read = true;
            break;
        }
        else{
            f.seekg(chunk_size, std::ios_base::cur);
        }
    }

    if(!data_read)
        throw wav_format_error("data chunk missing");

    return new wav(freq, quant, channel, data_len, datas);
}

