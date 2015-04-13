#include "rabin_karp.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

// The prime number used as the base in the rolling hash function.
// TODO: Generate this dynamically according to the input data.
#define HASH_BASE 109

// The modulus applied to the output of the rolling hash function.
// TODO: Generate this dynamically according to the input data.
#define HASH_MOD 1000

static void debug(char *text, ...);
static unsigned int hash_init(char *start, int length);
static unsigned int roll_hash(unsigned int previous, char old, char new, int length);
static int naive_compare(char *a, char *b, int length);
static int mod_mult(int a, int b, int mod);
static int mod_div(int p, int q, int mod);
static int mod_inv(int n, int mod);
static int mod_exp(int base, unsigned int exp, int mod);

int *rabin_karp_match(char *text, char *s) {
    debug("Trying to match '%s' in '%s'\n", s, text);
    int *matches = malloc(strlen(text) * sizeof(int));
    int match_idx = 0;

    int s_len = strlen(s);
    unsigned int s_hash = hash_init(s, s_len);
    unsigned int text_hash = hash_init(text, s_len);
    debug("Target hash is %u\n", s_hash);

    int idx = 0;
    while (text[idx]) {
        debug("Text hash at %d is %u\n", idx, text_hash);
        if (s_hash == text_hash) {
            matches[match_idx] = idx;
            match_idx++;
        }

        idx++;
        text_hash = roll_hash(text_hash, text[idx-1], text[idx + s_len - 1], s_len);
    }

    matches[match_idx] = -1;
    matches = realloc(matches, sizeof(int) * (match_idx + 1));

    return matches;
}

int *rabin_karp_multi_match(char *text, char **s) {
}

static unsigned int hash_init(char *text, int length) {
    int multiplicand = 1;
    int idx;
    unsigned int hash = 0;
    for (idx = 0; idx < length; idx++) {
        hash = (hash + mod_mult(((unsigned char)text[idx]), multiplicand, HASH_MOD)) % HASH_MOD;
        multiplicand = mod_mult(HASH_BASE, multiplicand, HASH_MOD);
    }

    return hash;
}

static unsigned int roll_hash(unsigned int previous, char old, char new, int length) {
    unsigned int hash = previous;
    hash = (hash >= old) ? hash - old : hash + HASH_MOD - old;

    debug("Roll %u, %c (%u), %c (%u), %d\n", previous, old, (unsigned char)old, new, (unsigned char)new,  length);
    hash = mod_div(hash, HASH_BASE, HASH_MOD);
    hash += mod_mult(new, mod_exp(HASH_BASE, length - 1, HASH_MOD), HASH_MOD);
    return hash % HASH_MOD;
}

static int naive_compare(char *a, char *b, int length) {
    int idx;
    for (idx = 0; idx < length && a[idx] && b[idx] && a[idx] == b[idx]; idx++) ;
    return (idx == length);
}

/*****************************************************************************/
/* FUNC mod_mult - Multiply two numbers together over Z_mod.                 */
/* TODO: improve the efficiency and speed of this implementation using an    */
/*       accepted modular multiplication algorithm.                          */
/*****************************************************************************/
static int mod_mult(int a, int b, int mod) {
    int result = ((a % mod) * (b % mod)) % mod;
    return result;
}

/*****************************************************************************/
/* FUNC mod_exp - Raise 'base' to the power of 'exp', modulo 'mod'.          */
/* TODO: Use a sensible algorithm; the current implementation is slow as     */
/*       hell.                                                               */
/*****************************************************************************/
static int mod_exp(int base, unsigned int exp, int mod) {
    int idx;
    int result = 1;
    for (idx = 0; idx < exp; idx++) {
        result = mod_mult(result, base, mod);
    }

    return result;
}

static int mod_div(int p, int q, int mod) {
    int q_inv = mod_inv(q, mod);
    return (q_inv == -1) ? -1 : mod_mult(p, q_inv, mod);
}

static int mod_inv(int n, int mod) {
    int mod_orig = mod;
    int p[2] = {0, 1};
    int q[2], step;
    int last_r = 0;
    step = 0;
    while (1) {
        int r_next = mod % n;
        int q_next = mod / n;
        if (step > 1) {
            int p_next = (p[0] - p[1] * q[0]) % mod_orig;
            p_next = (p_next < 0) ? p_next + mod_orig : p_next;
            p[0] = p[1];
            p[1] = p_next;
        }

        q[0] = q[1];
        q[1] = q_next;

        if (r_next == 0)
            break;

        last_r = r_next;
        mod = n;
        n = r_next;
        step++;
    }

    if (last_r == 1) {
        int result = (p[0] - p[1] * q[0]) % mod_orig;
        result = (result > 0) ? result : result + mod_orig;
        return result;
    }
    else {
        return -1;
    }
}

static void debug(char *text, ...) {
    if (DEBUG) {
        va_list argp;
        va_start(argp, text);
        printf("DEBUG: ");
        vprintf(text, argp);
    }
}
