#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

static void show_tree(NODE*);

int main(int argc, char **argv)
{
    NODE *tree = new_avl_tree(3, 0);
    show_tree(tree);
    avl_insert(tree, 7, 0);
    show_tree(tree);
    avl_insert(tree, 2, 0);
    show_tree(tree);
    avl_insert(tree, 6, 0);
    show_tree(tree);
    avl_insert(tree, 9, 0);
    show_tree(tree);
    avl_insert(tree, 8, 0);
    show_tree(tree);
    show_tree(tree);

}

static void show_tree(NODE *tree)
{
    char *treestr = avl_pretty_print(tree);
    printf("%s\n\n", treestr);
    free(treestr);
}
