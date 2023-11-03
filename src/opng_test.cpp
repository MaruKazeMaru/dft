// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>

#include <opng.hpp>

int main(int argc, char** argv){
    std::cout << "start" << std::endl;

    if(argc < 2){
        std::cout << "few argument" << std::endl;
        return 1;
    }

    unsigned int width=64;
    unsigned int height=32;
    unsigned char** data;
    data = new unsigned char*[width];
    for(unsigned int x = 0; x < width; ++x){
        data[x] = new unsigned char[height];
        for(unsigned int y = 0; y < height; ++y){
            if(x >= width / 2 && y >= height / 2)
                data[x][y] = 255;
            else
                data[x][y] = 0;
        }
    }

    std::cout << "ddefined data" << std::endl;
    opng* png = new opng(width, height, data);
    std::cout << "ddefined png" << std::endl;

    png->write(argv[1]);

    std::cout << "write finish" << std::endl;

    delete png;

    std::cout << "exit" << std::endl;

    return 0;
}