// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <linegraph.hpp>
#include <stdio.h>

void plot_data(
    unsigned int width, unsigned int height, char* file_path,
    unsigned int data_size, float** data,
    float x_min, float x_max, float y_min, float y_max
){
    FILE* pp = popen("gnuplot ", "w");

    fprintf(pp, "set terminal png size %u,%u\n", width, height);
    fprintf(pp, "set output '%s'\n", file_path);
    fprintf(pp, "unset tics\n");
    fprintf(pp, "set margins 0,0,0,0\n");
    fprintf(pp, "set xrange [%f:%f]\n", x_min, x_max);
    fprintf(pp, "set yrange [%f:%f]\n", y_min, y_max);
    fprintf(pp, "unset key\n");
    fprintf(pp, "plot '-' with lines linecolor 'black'\n");

    for(unsigned int i = 0; i < data_size; ++i){
        fprintf(pp, "%f %f\n", data[i][0], data[i][1]);
    }

    fprintf(pp, "e\n");

    pclose(pp);
}
