// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __LINEGRAPH_HPP__
#define __LINEGRAPH_HPP__

void plot_data(
    unsigned int width, unsigned int height, char* file_path,
    unsigned int data_size, float* data,
    double y_min, double y_max
);

#endif