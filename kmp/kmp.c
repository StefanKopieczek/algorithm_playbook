#include "kmp.h"

#include <stdlib.h>
#include <string.h>

static int *calculate_overlap(char *s);

/*****************************************************************************/
/* FUNC kmp -finds all occurrences of a given string in a larger string,     */
/* including overlaps.                                                       */
/* Params:                                                                   */
/*  - text - The body of text in which to search.                            */
/*  - s    - The string to be located.                                       */
/* Returns:                                                                  */
/*  An array of int indices 'text' pointing to matches.                      */
/*****************************************************************************/
int *kmp(char *text, char *s) {
    int text_len = strlen(text);
    int s_len = strlen(s);

    int *overlap = calculate_overlap(s);

    // Pre-allocate an array to hold all the matches up front.
    // Could be improved by using the overlap array, or by using a linked list
    // until the algorithm is complete.
    int *matches = malloc(text_len - s_len + 2);

    int ii = 0;
    int last_overlap = 0;
    int match_num = 0;
    while (ii < text_len - s_len + 1) {
        int jj = last_overlap;
        for (jj = last_overlap; jj < s_len && ii + jj < text_len; jj++) {
            if (text[ii + jj] != s[jj])
                break;
        }

        if (jj == s_len) {
            matches[match_num++] = ii;
        }

        last_overlap = overlap[jj-1];
        ii += (jj - last_overlap) > 1 ? jj - last_overlap : 1;
    }

    matches[match_num] = -1;
    matches = realloc(matches, match_num + 1);
    free(overlap);
    return matches;
}

static int *calculate_overlap(char *s) {
    int len = strlen(s);
    int *overlap = malloc(sizeof(int) * len);
    overlap[0] = -1;

    int idx;
    for (idx = 1; idx < len; idx++) {
        overlap[idx] = overlap[idx - 1] + 1;
        while (overlap[idx] > 0 && s[idx-1] != s[overlap[idx] - 1]) {
            overlap[idx] = overlap[overlap[idx] - 1] + 1;
        }
    }

    return overlap;
}
