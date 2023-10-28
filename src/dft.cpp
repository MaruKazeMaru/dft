// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <dft.hpp>

#include <math.h>

float** fft_recurs(int start, int size, int skip, float* f, float** w);

float* fft(int f_size, float* f){
    float** w = new float*[f_size];
    float dtheta = 2.0 * M_PI / (float)f_size;
    for(int i = 0; i < f_size; ++i){
        w[i] = new float[2];
        w[i][0] = cosf((float)i * dtheta);
        w[i][1] = - sinf((float)i * dtheta);
    }

    float** f_hat = fft_recurs(0, f_size, 1, f, w);

    for(int i = 0; i < f_size; ++i)
        delete w[i];
    delete w;

    float* spec = new float[f_size];
    for(int i = 0; i < f_size; ++i){
        spec[i] = f_hat[i][0] * f_hat[i][0] + f_hat[i][1] * f_hat[i][1];

        delete f_hat[i];
    }

    return spec;
}

float** fft_recurs(int start, int size, int skip, float* f, float** w){
    if(size == 1){
        float** f_hat = new float*[1];
        f_hat[0] = new float[2];
        f_hat[0][0] = f[start];
        f_hat[0][1] = 0.0;
        return f_hat;
    }
    else{
        int size_h = size / 2;
        int skip_d = 2 * skip;
        float** f_hat_e = fft_recurs(start,        size_h, skip_d, f, w);
        float** f_hat_o = fft_recurs(start + skip, size_h, skip_d, f, w);

        float** f_hat = new float*[size];
        for(int i = 0; i < size_h; ++i){
            int i1 = i;
            f_hat[i1] = new float[2];
            f_hat[i1][0] = f_hat_e[i][0];
            f_hat[i1][0] += w[i1 * skip][0] * f_hat_o[i][0];
            f_hat[i1][0] -= w[i1 * skip][1] * f_hat_o[i][1];
            f_hat[i1][1] = f_hat_e[i][1];
            f_hat[i1][1] += w[i1 * skip][0] * f_hat_o[i][0];
            f_hat[i1][1] -= w[i1 * skip][1] * f_hat_o[i][1];

            int i2 = i + size_h;
            f_hat[i2] = new float[2];
            f_hat[i2][0] = f_hat_e[i][0];
            f_hat[i2][0] += w[i2 * skip][0] * f_hat_o[i][0];
            f_hat[i2][0] -= w[i2 * skip][1] * f_hat_o[i][1];
            f_hat[i2][1] = f_hat_e[i][1];
            f_hat[i2][1] += w[i2 * skip][0] * f_hat_o[i][0];
            f_hat[i2][1] -= w[i2 * skip][1] * f_hat_o[i][1];

            delete f_hat_e[i];
            delete f_hat_o[i];
        }

        delete f_hat_e;
        delete f_hat_o;

        return f_hat;
    }
}