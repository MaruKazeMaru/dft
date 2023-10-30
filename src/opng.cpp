// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <png.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

#include <opng.hpp>

opng_rgb::opng_rgb(
    unsigned int width, unsigned int height,
    unsigned char*** data
){
    this->width = width;
    this->height = height;
    this->data = data;
}

opng_rgb::~opng_rgb(){
    for(unsigned int x = 0; x < width; ++x){
        for(unsigned int y = 0; y < height; ++y)
            delete data[x][y];
        delete data[x];
    }
    delete data;
}

void opng_rgb::write(char* file_path){
    std::cout << "start" << std::endl;
    FILE* fp = fopen(file_path, "wb");
    if(fp == NULL)
        throw new opng_write_error("can't open file");

    std::cout << "opened" << std::endl;
    png_struct* psp = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    std::cout << "defined psp" << std::endl;
    png_info* pip = png_create_info_struct(psp);
    std::cout << "defined pip" << std::endl;

    png_init_io(psp, fp);
    std::cout << "inited psp" << std::endl;
    png_set_IHDR(
        psp, pip,
        width, height, 8, PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    std::cout << "set IHDR" << std::endl;

    png_byte** buffer = (png_byte**)png_malloc(psp, sizeof(png_byte*) * height);
    size_t row_size = sizeof(png_byte) * 3 * width;
    for(unsigned int y = 0; y < height; ++y){
        buffer[y] = (png_byte*)png_malloc(psp, row_size);
        for(unsigned int x = 0; x < width; ++x)
            for(unsigned char c = 0; c < 3; ++c)
                buffer[y][x * 3 + c] = data[x][y][c];
    }

    std::cout << "buffed" << std::endl;

    png_set_rows(psp, pip, buffer);

    std::cout << "set rows" << std::endl;

    png_write_png(psp, pip, PNG_TRANSFORM_IDENTITY, NULL);

    std::cout << "wrote" << std::endl;

    for(unsigned int y = 0; y < height; ++y)
        png_free(psp, buffer[y]);
    png_free(psp, buffer);
    png_destroy_write_struct(&psp, &pip);
    fclose(fp);
}
