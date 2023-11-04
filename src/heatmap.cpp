// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <heatmap.hpp>

unsigned char** get_heatmap(
    unsigned int width, unsigned int height,
    float data_min, float data_max, float** data
){
    float data_width = data_max - data_min;

    unsigned char** heatmap = new unsigned char*[width];
    for(unsigned int x = 0; x < width; ++x){
        heatmap[x] = new unsigned char[height];
        for(unsigned int y = 0; y < height; ++y){
            float v = data[x][y] - data_min;
            v /= data_width;
            v *= 255.0;
            if(v > 255.0)
                v = 255.0;
            else if(v < 0.0)
                v = 0.0;
            v += 0.5;
            heatmap[x][y] = (unsigned char)v;
            heatmap[x][y] = 255 - heatmap[x][y];
        }
    }

    return heatmap;
}