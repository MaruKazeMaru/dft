// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <linegraph.hpp>
#include <math.h>

unsigned char*** plot_small_data(
    unsigned int img_width, unsigned int img_height,
    unsigned char* background_color, unsigned char* line_color,
    float line_width, unsigned int data_width,
    unsigned int data_size, float* data, float data_min, float data_max
){
    float d = 1.0 / (float)ANTIALIAS_STEP;

    unsigned char*** img = new unsigned char**[img_width];
    for(unsigned x = 0; x < img_width; ++x){
        img[x] = new unsigned char*[img_height];
        for(unsigned int y = 0; y < img_height; ++y){
            img[x][y] = new unsigned char[3];

            unsigned int dist_under_width_cnt = 0;

            float xf = (float)x + 0.5;
            float yf = (float)y + 0.5;
            for(unsigned char i = 0; i < ANTIALIAS_STEP; ++i){
                yf = (float)y + 0.5;
                for(unsigned char j = 0; j < ANTIALIAS_STEP; ++j){
                    float min_dist = (float) width;

                    for(unsigned int k = 1; k < data_size; ++k){
                        float x1 = xf - points[k][0];
                        float y1 = yf - points[k][1];
                        float x2 = xf - points[k - 1][0];
                        float y2 = yf - points[k - 1][1];
                        float x3 = points[k - 1][0] - points[k][0];
                        float y3 = points[k - 1][1] - points[k][1];
                        float dot1 = x1 * x3 + y1 * y3;
                        float dot2 = - x2 * x3 - y2 * y3;
                        float dist;
                        if(dot1 <= 0.0 && dot2 <= 0.0){
                            float dist1 = x1 * x1 + y1 * y1;
                            float dist2 = x2 * x2 + y2 * y2;
                            if(dist1 < dist2)
                                dist = dist1;
                            else
                                dist = dist2;
                        }
                        else{
                            dist = x1 * x1 + y1 * y1 - dot1 * dot1;
                            dist = sqrtf(dist);
                        }

                        for
                    }

                    yf += d;
                }
                xf += d;
            }
        }
    }

    return img;
}
