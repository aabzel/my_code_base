#ifndef COMPARE_VERSION_H
#define COMPARE_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

int extract_val (char *version, int pos, int rank);
int calc_rank (char *version);
int compareVersion (char *version1, char *version2);

#ifdef __cplusplus
}
#endif

#endif /* COMPARE_VERSION_H */
