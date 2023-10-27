// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __DFT_HPP__
#define __DFT_HPP__

float* fft(int f_size, float* f);
float** fft_recurs(int start, int size, int skip, float* f, float** w);

#endif