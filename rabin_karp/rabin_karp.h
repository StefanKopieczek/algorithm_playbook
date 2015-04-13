#ifndef SMK_RABIN_KARP
#define SMK_RABIN_KARP

#include "bloom.h"

int *rabin_karp_match(char *text, char *s);

int *rabin_karp_multi_match(char *text, char **s, int num_targets);

#endif
