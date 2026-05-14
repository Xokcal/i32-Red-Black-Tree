//
// Created by 26432 on 2026/5/12.
//

#include "typedef.h"
#include <stdio.h>
#include "blackRedTree.h"
#include <stdlib.h>

RBNode *rb_i32_create_new_NIL() {
    RBNode *nil = (RBNode *) malloc(sizeof(RBNode));
    nil->color = BLACK;
    nil->right = nil;
    nil->left = nil;
    nil->parent = nil;
    return nil;
}

RBTree *rb_i32_create_new_root() {
    RBTree *root = (RBTree *) malloc(sizeof(RBTree));
    root->NIL = rb_i32_create_new_NIL();
    root->root = root->NIL;
    return root;
}

RBNode *rb_i32_create_new_node(RBTree *root, i32 v) {
    RBNode *node = (RBNode *) malloc(sizeof(RBNode));
    node->v = v;
    node->color = RED;

    node->parent = root->NIL;
    node->right = root->NIL;
    node->left = root->NIL;
    return node;
}

void rb_i32_print(RBTree *root) {
    if (root->root == root->NIL)return;
    printf("[");
    rb_i32_print_impl(root, root->root);
    printf("]");
}

static i32 a = 1;

void rb_i32_print_impl(RBTree *root, RBNode *h) {
    if (h == root->NIL)return;
    rb_i32_print_impl(root, h->left);
    if (a == 1) {
        printf("%d", h->v);
        a = 0;
    } else {
        printf(",%d", h->v);
    }
    rb_i32_print_impl(root, h->right);
}

void rb_i32_add(RBTree *root, i32 v) {
    RBNode *new = rb_i32_create_new_node(root, v);
    if (root->root == root->NIL) {
        root->root = new;
        root->root->color = BLACK;
        return;
    }
    RBNode *curr = root->root;
    RBNode *pre = root->NIL;
    while (curr != root->NIL) {
        pre = curr; /* here previous get curr pre node,
         outside can get curr's pre when 'while' end! */
        if (v < curr->v) { //search left
            curr = curr->left;
        } else if (v == curr->v) { // return when v equal has stored v!
            free(new);
            return;
        } else { //NOTE: if v == curr->v ,need't add this new node!!
            curr = curr->right;
        }
    }
    new->parent = pre;
    /* judge v should insert 'pre' right or left! */
    if (v < pre->v) {
        pre->left = new;
    } else {
        pre->right = new;
    }

    rb_i32_fixup(root, new);
    return;
}

void rb_i32_left_rotate(RBTree *root, RBNode *h) {
    RBNode *x = h->right;
    h->right = x->left;
    if (x->left != root->NIL) // suppose: x.left not is NULL,set x.left.parent.
        x->left->parent = h;
    x->parent = h->parent;
    // h.parent's situation 3!
    if (h->parent == root->NIL)
        root->root = x;
    else if (h == h->parent->left) //judge h is equal h.parent.left(h self)!!
        h->parent->left = x;
    else
        h->parent->right = x;

    /*relation has handed :
      made x.left = h ; h.parent = x is ok  */
    x->left = h;
    h->parent = x;
}

void rb_i32_right_rotate(RBTree *root, RBNode *h) {
    RBNode *x = h->left;
    h->left = x->right;
    if (x->right != root->NIL)
        x->right->parent = h;
    x->parent = h->parent;
    if (h->parent == root->NIL)
        root->root = x;
    else if (h == h->parent->left)
        h->parent->left = x;
    else
        h->parent->right = x;

    x->right = h;
    h->parent = x;
}

void rb_i32_fixup(RBTree *root, RBNode *new) {
    RBNode *new_node = new;
    /* new.parent equal RED need to tackle,
     * and new.parent not is NIL!! */
    while (new_node->parent->color == RED && new_node->parent != root->NIL) {
        //new.parent in new.parent.parent left !
        if (new_node->parent == new_node->parent->parent->left) {
            RBNode *uncle = new_node->parent->parent->right;
            // uncle is RED need't to rotate
            if (uncle->color == RED) { // uncle = RED
                uncle->color = BLACK;
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                /* let new = grandparent 'while' can continus tackle on up */
                new_node = new_node->parent->parent;
            } else { //uncle = BLACK
                if (new_node == new_node->parent->right) { // LR型
                    new_node = new_node->parent;
                    rb_i32_left_rotate(root, new_node);
                } //LL型
                new_node->parent->parent->color = RED;
                new_node->parent->color = BLACK;
                rb_i32_right_rotate(root, new_node->parent->parent);
            }
            //new.parent in new.parent.parent right !
        } else {
            RBNode *uncle = new_node->parent->parent->left;
            if (uncle->color == RED) {
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                uncle->color = BLACK;
                new_node = new_node->parent->parent;
            } else {
                if (new_node->parent->left == new_node) { // RL型
                    new_node = new_node->parent;
                    rb_i32_right_rotate(root, new_node);
                } //RR型
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                rb_i32_left_rotate(root, new_node->parent->parent);
            }
        }
    }
    root->root->color = BLACK;
}
//fix if void od euqal the log
/*
 * if RED and BLACK */

RBNode *rb_i32_min(RBTree *root, RBNode *h) {
    if (h->left == root->NIL)return h;
    h = rb_i32_min(root, h->left);
}

void rb_i32_del(RBTree *root, i32 v) {
    if (root->root == root->NIL)return;
    RBNode *h = root->root;
    while (h != root->NIL) {
        if (v < h->v)
            h = h->left;
        else if (v > h->v)
            h = h->right;
        else
            break;
    }
    if (h == root->NIL)return;
    Color del_cor = h->color; // doc del target's color !!
    RBNode *del = h;
    RBNode *rep = root->NIL;
    RBNode *parent = h->parent;
    if (h->left == root->NIL)
        rep = h->right;
    else if (h->right == root->NIL)
        rep = h->left;
    else {
        RBNode *min = rb_i32_min(root , h->right);
        h->v = min->v;
        /* bucause del target have right and left node ,
         *  so need to get del target.right's min node,
         *  del become min ;
         *  parent become min.parent!!!
         *  rep become min.right*/
        del = min;
        parent = min->parent;
        rep = min->right;
    }

    if (parent == root->NIL)
        root->root = rep;
    else if (parent->right == del)
        parent->right = rep;
    else
        parent->left = rep;

    if (rep != root->NIL)
        rep->parent = parent;

    /* del color equal RED need's to execute fixup(),
     * contrary ! color euqal BLACK need exe fixup(). */
    if (del_cor == BLACK)
        rb_i32_del_fixup(root , del , parent);

    free(del);
    return;

}

/*
 * 概念1：
 *  ！就是看兄弟那边有没有红色，然后把红色弄到删除的那一边（parent。left）然后把红色变成黑色，
 *  因为红色少一个多一个无所谓，只要没有两个红色链接就行了，这样就平衡了。就相当于如果有红色就说明，
 *  红色是潜在的黑色，红色缓换成黑色相当于加一个黑色，然后我删除一个黑色，加一个黑色（红变黑）等于没变
 *
 *  概念2：
 *  ！就是让parent变成子，他原本不算分支的红黑但是变成子后，他本身就算是分支的一个节点
 *  （不管他原来是黑色还是红色，变成子后都相当于加一个黑色），然后远端少一个黑，把红色变成黑就抵消了，
 *  然后这样左边原本少了一个黑，由parent变成子后就抵消了，然后右边红色变成黑色也抵消了，最后两个分支黑色数量对等！
 *
 * 概念3：
 * ！假如parent.right（x）那分支原本有8个黑，左边（parent.left）也有8个黑，
 * 然后我原本删除了x那一支下面的某个黑色节点（变成7个黑了），然后处理不了，我让x等于黑，
 * 这个时候parent.right又是8个黑，然后....？？！好像平衡了！！
 *
 *  */

void rb_i32_del_fixup(RBTree *root, RBNode *delT , RBNode* parent) {
    //抛出x，x。color == RED，直接退出循环
    while (delT != root->root && (delT->color == BLACK || delT == root->NIL)){
        if (delT == parent->left){
            RBNode *bro = parent->right; // del是在parent左边，所以拿right兄弟
            //判断bro的颜色
            if(bro->color == RED){
                bro->color = BLACK;
                parent->color = RED;
                rb_i32_left_rotate(root , parent);
                bro = parent->right; // ！！！这里旋转之后t的目标兄弟是parent.right！！！
            }
            //此时bro是黑色
            //并且两个孩子全黑
            if ((bro == root->NIL)||
            (bro->left == root->NIL || bro->left->color == BLACK)&&
            (bro->right == root->NIL || bro->right->color == BLACK)){
                //抛出delT给上层节点
                delT = parent;
                parent = delT->parent;
            }
            else {
                //反之bro左孩子是红色
                if (bro->right == root->NIL || bro->right->color == BLACK){
                    if (bro->left != root->NIL)
                        bro->left->color = BLACK;
                    bro->color = RED;
                    rb_i32_right_rotate(root , bro);
                    bro = parent->right; // ！！！这里可以直接等于parent的right（准确的bro）
                }
                //如果bro左孩子是红色（最终解决情况）
                rb_i32_left_rotate(root , parent);
                bro->color = parent->color;
                parent->color = BLACK;
                bro->right->color = BLACK;
                return;
            }
        }
        //在右边
        else {
            RBNode *bro = parent->left;
            if (bro != root->NIL && bro->color == RED){
                bro->color = BLACK;
                parent->color = RED;
                rb_i32_right_rotate(root , parent);
                bro = parent->left;
            }
            if (bro == root->NIL ||
            ( bro->left == root->NIL || bro->left->color == BLACK)&&
            (bro->right == root->NIL || bro->right->color == BLACK)){
                delT = parent;
                parent = delT->parent;
            } else{
                if (bro->left == root->NIL || bro->left->color == BLACK){
                    bro->color = RED;
                    if (bro->right != root->NIL)
                        bro->right->color = BLACK;
                    rb_i32_left_rotate(root , bro);
                    bro = parent->left;
                }
                bro->color = parent->color;
                parent->color = BLACK;
                bro->left->color = BLACK;
                rb_i32_right_rotate(root , parent);
                return;
            }
        }
    }
    if (delT != root->NIL)
        delT->color = BLACK;
    return;
}













