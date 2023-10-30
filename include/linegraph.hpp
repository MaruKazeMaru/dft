// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __LINEGRAPH_HPP__
#define __LINEGRAPH_HPP__

#define ANTIALIAS_STEP 4

unsigned char*** plot_small_data(
    unsigned int img_height,
    unsigned char* background_color, unsigned char* line_color,
    float line_width, unsigned int width_per_data,
    unsigned int data_size, float* data, float data_min, float data_max
);

#endif