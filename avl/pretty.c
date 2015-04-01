#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct partial_render PARTIAL_RENDER;

static PARTIAL_RENDER *pretty_print_subtree(NODE *node);
static void free_partial_render(PARTIAL_RENDER *pr);

struct partial_render
{
    char **rows;
    int num_rows;
};


char *avl_pretty_print(NODE *node)
{
    PARTIAL_RENDER *render_result = pretty_print_subtree(node);

    int buflen = 1;
    int idx;
    for (idx = 0; idx < render_result->num_rows; idx++)
    {
        // Calculate the amount of chars needed in our output string to
        // render this row, including the terminal newline.
        buflen += strlen(render_result->rows[idx]) + 1;
    }

    char *result = calloc(1, buflen);
    for (idx = 0; idx < render_result->num_rows; idx++)
    {
        char *row = render_result->rows[idx];
        strcat(result, row);
        strcat(result, "\n");
    }

    free_partial_render(render_result);
    return result;
}

/*****************************************************************************/
/* Here be dragons.                                                          */
/*****************************************************************************/
PARTIAL_RENDER *pretty_print_subtree(NODE *node)
{
    PARTIAL_RENDER *result = malloc(sizeof(PARTIAL_RENDER));

    if (!node)
    {
        result->num_rows = 1;
        result->rows = malloc(sizeof(char *));
        result->rows[0] = malloc(sizeof(char) * 2);
        result->rows[0][0] = '~';
        result->rows[0][1] = '\0';
        return result;
    }

    PARTIAL_RENDER *left = pretty_print_subtree(node->left);
    PARTIAL_RENDER *right = pretty_print_subtree(node->right);
    result->num_rows = left->num_rows + right->num_rows;
    result->rows = malloc(sizeof(char *) * result->num_rows);

    char key_buffer[sizeof(int) + 1];
    memset(key_buffer, 0, sizeof(int) + 1);
    sprintf(key_buffer, "%d", node->key);
    int key_len = strlen(key_buffer);

    int idx;
    char *key_padding = malloc(key_len);
    memset(key_padding, ' ', key_len - 1);
    key_padding[key_len - 1] = '\0';

    result->rows[0] = calloc(1, strlen(left->rows[0]) + key_len + 6);
    strcat(result->rows[0], key_buffer);
    strcat(result->rows[0], " --- ");
    strcat(result->rows[0], left->rows[0]);
    for (idx = 1; idx < left->num_rows; idx++)
    {
        result->rows[idx] = malloc(strlen(left->rows[idx]) + key_len + 6);
        result->rows[idx][0] = '\0';
        strcat(result->rows[idx], "|");
        strcat(result->rows[idx], key_padding);
        strcat(result->rows[idx], "     ");
        strcat(result->rows[idx], left->rows[idx]);
    }

    result->rows[idx] = malloc(strlen(right->rows[0]) + key_len + 6);
    result->rows[idx][0] = '\0';
    strcat(result->rows[idx], key_padding);
    strcat(result->rows[idx], " \\--- ");
    strcat(result->rows[idx], right->rows[0]);
    for (idx = 1; idx < right->num_rows; idx++)
    {
        result->rows[left->num_rows + idx] = malloc(strlen(right->rows[idx]) + key_len + 6);
        result->rows[left->num_rows + idx][0] = '\0';
        strcat(result->rows[left->num_rows + idx], key_padding);
        strcat(result->rows[left->num_rows + idx], "      ");
        strcat(result->rows[left->num_rows + idx], right->rows[idx]);
    }

    free_partial_render(left);
    free_partial_render(right);

    return result;
}

void free_partial_render(PARTIAL_RENDER *pr)
{
    int idx;
    for (idx = 0; idx < pr->num_rows; idx++)
    {
        free(pr->rows[idx]);
    }
    free(pr->rows);
    free(pr);
}
