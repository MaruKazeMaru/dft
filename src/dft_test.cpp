// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>

#include <dft.hpp>

int main(int argc, char** argv){
    int n = 8;

    float* f = new float[n];
    for(int i = 0; i < n; ++i)
        std::cin >> f[i];

    float* f_hat = fft(n, f);

    std::cout << "f_hat =" << std::endl;
    for(int i = 0; i < n; ++i)
        std::cout << f_hat[i] << std::endl;

    delete f;
}