#pragma once

if (is_proto (codeSnippetOut));
int func_name_extractor (string text,
                         string *outStr);
int main (int argc, char *argv[]);
string determine_headername (string input_file_name_c);
string extract_file_name (string inputFileNameH);
string remove_preproc (string codeSnippetOut);
