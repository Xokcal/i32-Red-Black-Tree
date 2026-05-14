//
// Created by 26432 on 2026/5/12.
//

#ifndef I32_BLACK_RED_BLACKREDTREE_H
#define I32_BLACK_RED_BLACKREDTREE_H

#include "typedef.h"
#include <stdio.h>

typedef enum {
    RED,
    BLACK
}Color;

typedef struct RBNode{
    i32 v;
    Color color;

    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
}RBNode;

typedef struct RBTree{
    RBNode* root;
    RBNode* NIL;
}RBTree;

RBNode *rb_i32_create_new_NIL();

RBTree *rb_i32_create_new_root();

RBNode *rb_i32_create_new_node(RBTree *root , i32 v);

void rb_i32_print(RBTree* root);

void rb_i32_print_impl(RBTree* root , RBNode *h);

void rb_i32_add(RBTree *root, i32 v);

void rb_i32_left_rotate(RBTree *root, RBNode *h);

void rb_i32_right_rotate(RBTree *root, RBNode *h);

void rb_i32_fixup(RBTree *root, RBNode *new);

void rb_i32_del(RBTree* root , i32 v);

RBNode *rb_i32_min(RBTree *root, RBNode *h);

void rb_i32_del_fixup(RBTree *root, RBNode *delT , RBNode* parent);

#endif //I32_BLACK_RED_BLACKREDTREE_H
