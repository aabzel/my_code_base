#pragma once

#include <map>
#include <vector>

using namespace std;

bool findAndReplaceAll (string &data, string toSearch, string replaceStr);
int string_to_int (string text, int *outVal);
string int_to_string(int val);
void print_map (map<int, int> histogram);
void print_intervals (vector<vector<int>> &intervals);

template<class Type>
void print_vector (vector<Type> words);

#if 0
void print_vector_ints (vector<int> words);
void print_vector_chars (vector<char> words);
#endif

string load_file_to_string (string inputFileName);
