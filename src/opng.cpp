// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <iostream>
#include <png.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

#include <opng.hpp>

opng::opng(
    unsigned int width, unsigned int height,
    unsigned char** data
){
    this->width = width;
    this->height = height;
    this->data = data;
}


opng::~opng(){
    for(unsigned int x = 0; x < width; ++x)
        delete data[x];
    delete data;
}


void opng::invert_y(){
    unsigned int hh = height / 2;
    for(unsigned int y = 0; y < hh; ++y){
        unsigned int y1 = y;
        unsigned int y2 = height - 1 - y;
        for(unsigned int x = 0; x < width; ++x){
            unsigned char temp = data[x][y1];
            data[x][y1] = data[x][y2];
            data[x][y2] = temp;
        }
    }
}


void opng::write(char* file_path){
    FILE* fp = fopen(file_path, "wb");
    if(fp == NULL)
        throw opng_write_error("can't open file");

    png_struct* psp = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_info* pip = png_create_info_struct(psp);

    png_init_io(psp, fp);
    png_set_IHDR(
        psp, pip,
        width, height, 8, PNG_COLOR_TYPE_GRAY,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_byte** buffer = (png_byte**)png_malloc(psp, sizeof(png_byte*) * height);
    size_t row_size = sizeof(png_byte) * width;
    for(unsigned int y = 0; y < height; ++y){
        buffer[y] = (png_byte*)png_malloc(psp, row_size);
        for(unsigned int x = 0; x < width; ++x)
            buffer[y][x] = data[x][y];
    }

    png_set_rows(psp, pip, buffer);

    png_write_png(psp, pip, PNG_TRANSFORM_IDENTITY, NULL);

    for(unsigned int y = 0; y < height; ++y)
        png_free(psp, buffer[y]);
    png_free(psp, buffer);
    png_destroy_write_struct(&psp, &pip);
    fclose(fp);
}
