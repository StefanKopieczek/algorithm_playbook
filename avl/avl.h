#ifndef SMK_AVL
#define SMK_AVL

typedef struct node NODE;

struct node
{
    int key;
    void *value;

    NODE *parent;
    NODE *left;
    NODE *right;

    int height;
};

NODE *new_avl_tree(int key, void *value);
void avl_insert(NODE *node, int key, void *value);
char *avl_pretty_print(NODE *node);

#endif
