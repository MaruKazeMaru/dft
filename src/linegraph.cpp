// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#include <linegraph.hpp>
#include <stdio.h>

void plot_data(
    unsigned int width, unsigned int height, char* file_path,
    unsigned int data_size, float* data,
    double y_min, double y_max
){
    FILE* pp = popen("gnuplot ", "w");

    fprintf(pp, "set terminal png size %u,%u\n", width, height);
    fprintf(pp, "set output '%s'\n", file_path);
    fprintf(pp, "unset tics\n");
    fprintf(pp, "set margins 0,0,0,0\n");
    fprintf(pp, "set xrange [0:%u]\n", data_size - 1);
    fprintf(pp, "set yrange [%lf:%lf]\n", y_min, y_max);
    fprintf(pp, "unset key\n");
    fprintf(pp, "plot '-' with lines linecolor 'black'\n");

    for(unsigned int i = 0; i < data_size; ++i){
        fprintf(pp, "%i %f\n", i, data[i]);
    }

    fprintf(pp, "e\n");

    pclose(pp);
}
