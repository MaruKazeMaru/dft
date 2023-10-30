// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>

#include <iwav.hpp>

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "few argument" << std::endl;
        return 1;
    }

    wav* w = get_wav(argv[1]);
    std::cout << "read" << std::endl;

    std::cout << "freq     = " << w->freq << std::endl;
    std::cout << "quant    = " << w->quant << std::endl;
    std::cout << "channel  = " << w->channel << std::endl;
    std::cout << "data_len = " << w->data_len << std::endl;

    delete w;

    return 0;
}