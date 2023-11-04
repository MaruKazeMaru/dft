// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __HEATMAP_HPP__
#define __HEATMAP_HPP__

unsigned char** get_heatmap(
    unsigned int width, unsigned int height,
    float data_min, float data_max, float** data
);

#endif