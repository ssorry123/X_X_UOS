
#include <stdio.h>
#include "link.h"

int cal_direc_size(TreeNode *root) {
    int leftSize, rightSize;
    if (root != NULL) {
        leftSize = cal_direc_size(root->left);
        rightSize = cal_direc_size(root->right);
        return root->data + leftSize + rightSize;
    }
    return 0;
}
int get_node_count(TreeNode *node) {
    int count = 0;
    if (node != NULL) {
        count = 1 + get_node_count(node->left) + get_node_count(node->right);
        printf("name = %d\n", node->name);
    }
    return count;
}
void main() {
    TreeNode n4 = { 500, NULL, NULL,4 };
    TreeNode n5 = { 200, NULL, NULL ,5 };
    TreeNode n3 = { 100, &n4, &n5 ,3 };
    TreeNode n2 = { 50, NULL, NULL ,2 };
    TreeNode n1 = { 0, &n2, &n3 ,1 };
    //printf(" = %d\n", cal_direc_size(&n1));
    printf("%d\n", get_node_count(&n1));
}
