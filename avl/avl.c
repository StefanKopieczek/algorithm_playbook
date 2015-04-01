#include "avl.h"

static int abs(int);
static short sgn(int);

static void avl_rotate(NODE *);
static int avl_get_balance(NODE *);
static void avl_ensure_balanced(NODE *);
static void avl_apply_height_increase(NODE *);
static NODE *avl_get_taller_child(NODE *);

#include <stdio.h> // TODO remove

#include <stdlib.h>

NODE *new_avl_tree(int key, void *value)
{
    NODE *node = malloc(sizeof(NODE));
    node->key = key;
    node->value = value;
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    node->height = 1;
    return node;
}

void avl_insert(NODE *node, int key, void *value)
{
    if (node->key == key)
    {
        node->value = value;
        return;
    }

    NODE **child_ptr;
    if (node->key > key)
    {
        child_ptr = &(node->left);
    }
    else
    {
        child_ptr = &(node->right);
    }

    if (!*child_ptr)
    {
        // We've reached the tip of the tree, so add the new node in the
        // correct position.
        *child_ptr = calloc(1, sizeof(NODE));
        (*child_ptr)->key = key;
        (*child_ptr)->value = value;
        (*child_ptr)->parent = node;
        (*child_ptr)->height = 1;
        avl_ensure_balanced(node);
    }
    else
    {
        // Recurse down the tree until we find the tip.
        avl_insert(*child_ptr, key, value);
    }
}

static void avl_ensure_balanced(NODE *node)
{
    if (abs(avl_get_balance(node)) == 2)
    {
        // Rebalancing needed.
        NODE *taller_child = avl_get_taller_child(node);
        if (sgn(avl_get_balance(node)) != sgn(avl_get_balance(taller_child)))
        {
            avl_rotate(taller_child);
            node = taller_child;
        }

        avl_rotate(node);
    }

    // Continue rebalancing all the way up the tree.
    if (node->parent)
    {
        avl_ensure_balanced(node->parent);
    }
}

static void avl_rotate(NODE *node)
{
    NODE *old_parent = node->parent;

    node->parent = old_parent->parent;
    printf("%p %p %p %p\n", node, node->key, node->parent, old_parent);
    if (node->key < node->parent->key)
    {
        node->parent->left = node;
    }
    else
    {
        node->parent->right = node;
    }

    if (sgn(avl_get_balance(node)) == -1)
    {
        // Rotate left
        old_parent->right = node->left;
        node->left = old_parent;
    }
    else
    {
        // Rotate right
        old_parent->left = node->right;
        node->right = old_parent;
    }
}

NODE *avl_get_taller_child(NODE *node)
{
    if (!node || avl_get_balance(node) == 0)
    {
        return 0;
    }
    else if (avl_get_balance(node) > 0)
    {
        return node->left;
    }
    else
    {
        return node->right;
    }
}

static int avl_get_balance(NODE *node)
{
    int left_height = 0;
    int right_height = 0;

    if (node->left)
        left_height = node->left->height;

    if (node->right)
        right_height = node->right->height;
}

static void apply_height_increase(NODE *node)
{
    // TODO
}

static int abs(int n)
{
    if (n < 0)
        return n * -1;
    else
        return n;
}

static short sgn(int n)
{
    if (n < 0)
        return -1;
    else if (n == 0)
        return 0;
    else
        return 1;
}
