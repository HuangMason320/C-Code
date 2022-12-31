// Construct tree by inorder and preorder

#include <stdio.h>
#include <stdlib.h>

#define left ptr_to_left_node
#define right ptr_to_right_node

typedef struct _NODE
{
    int number;
    struct _NODE *ptr_to_right_node;
    struct _NODE *ptr_to_left_node;
} Node;

int n, cur = 0;

int idxsearch(int *inorder, int num, int a, int b)
{
    for (int i = a; i <= b; i++)
    {
        if (inorder[i] == num)
            return i;
    }
}

Node *buildTree(int *inorder, int *preorder, int start, int end)
{
    if (start > end)
        return NULL;
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->number = preorder[cur++];
    int idx = idxsearch(inorder, temp->number, start, end);
    temp->left = buildTree(inorder, preorder, start, idx - 1);
    temp->right = buildTree(inorder, preorder, idx + 1, end);
    return temp;
}

void showPostorder(Node *tree)
{
    if (tree)
    {
        showPostorder(tree->left);
        showPostorder(tree->right);
        printf("%d", tree->number);
    }
}

void freeTree(Node *tree)
{
    cur = 0;
    if (tree)
    {
        freeTree(tree->right);
        freeTree(tree->left);
        free(tree);
    }
}

int main(void)
{
    int id = 1;
    while (~scanf("%d", &n))
    {
        int inorder[100], preorder[100];
        for (int i = 0; i < n; i++)
            scanf("%d", &inorder[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &preorder[i]);
        Node *root = buildTree(inorder, preorder, 0, n - 1);
        printf("testcase%d: ", id++);
        showPostorder(root);
        printf("\n");
        freeTree(root);
    }
    return 0;
}