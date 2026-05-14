#include <stdio.h>
#include "typedef.h"
#include "blackRedTree.h"

int main() {
    RBTree *root = rb_i32_create_new_root();
    rb_i32_add(root , 12);
    rb_i32_add(root , 13);
    rb_i32_add(root , 21);
    rb_i32_add(root , 63);
    rb_i32_add(root , 65);
    rb_i32_add(root , 82);
    rb_i32_add(root , 8);
    rb_i32_add(root , 7);
    rb_i32_add(root , 72);
    rb_i32_add(root , 45);
    rb_i32_add(root , 324);
    rb_i32_add(root , 24);
    rb_i32_add(root , 765);
    rb_i32_add(root , 457);
    rb_i32_add(root , 257);
    rb_i32_add(root , 6247);
    rb_i32_add(root , 4573);
    rb_i32_add(root , 87);
    rb_i32_add(root , 875);
    rb_i32_add(root , 4352);
    rb_i32_add(root , 753);
    rb_i32_add(root , 236);
    rb_i32_add(root , 243);
    rb_i32_add(root , 8654);
    rb_i32_add(root , 8658);
    rb_i32_add(root , 733);
    rb_i32_add(root , 755);

    rb_i32_del(root , 4573);
    rb_i32_del(root , 4352);
    rb_i32_del(root , 8658);
    rb_i32_del(root , 733);
    rb_i32_del(root , 243);
    rb_i32_del(root , 8654);
    rb_i32_del(root , 1111);


    rb_i32_print(root);
    printf("\nSUCCESS!!");
    RBNode *min = rb_i32_min(root , root->root->right->right);
    printf("\n%d\n" , min->v);

    return 0;
}
