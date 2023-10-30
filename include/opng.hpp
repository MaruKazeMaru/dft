// SPDX-License-Identifier: MIT License

#ifndef __OPNG_HPP__
#define __OPNG_HPP__

#include <iostream>

class opng_write_error: public std::runtime_error{
    public:
    opng_write_error(const char* msg):runtime_error(msg){};
};

class opng_rgb{
    private:
    unsigned int width;
    unsigned int height;
    unsigned char*** data;

    public:
    opng_rgb(
        unsigned int width, unsigned int height,
        unsigned char*** data
    );
    ~opng_rgb();

    void write(char* file_path);
};

#endif