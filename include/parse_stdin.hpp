// SPDX-FileCopyrightText: 2023 ShinagwaKazemaru
// SPDX-License-Identifier: MIT License

#ifndef __PARSE_STDIN_HPP__
#define __PARSE_STDIN_HPP__

bool get_paths(char** wav_path, char** result_dir);
bool get_window_len(unsigned int freq, unsigned int* window_len);
char* join_path(char* dir, char* file);
char* set_path_index(const char* file, int index);

#endif