#include <stdio.h>

#define right ptr_to_right_node
#define left ptr_to_left_node
int n, cur = 0;
typedef struct Node
{
    int number;
    Node *ptr_to_right_node;
    Node *ptr_to_left_node;
} Node;

int idxsearch(int *inorder, int num, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        if (inorder[i] == num)
            return i;
    }
}
Node *buildtree(int *inorder, int *preorder, int start, int end)
{
    if (start > end)
        return NULL;
    Node *tree_node = (Node *)malloc(sizeof(Node));
    tree_node->number = preorder[cur++];
    int idx = idxsearch(inorder, tree_node->number, start, end);
    tree_node->left = buildtree(inorder, preorder,start, idx - 1);
    tree_node->right = buildtree(inorder, preorder, idx + 1, end);
    return tree_node;
}
void showposter(Node *root)
{
    if (root != NULL)
    {
        showposter(root->left);
        showposter(root->right);
        printf("%d ", root->number);
    }
}
void freeTree(Node *root)
{
    cur = 0;
    if (root != NULL)
    {
        freeTree(root->right);
        freeTree(root->left);
        free(root);
    }
}
int main()
{
    int id = 1;
    while (scanf("%d", &n) != EOF)
    {
        int inorder[100], preorder[100];
        for (int i = 0; i < n; i++)
            scanf("%d", &inorder[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &preorder[i]);
        Node *root = buildtree(inorder, preoder, 0, n - 1);
        printf("testcase%d: ", id++);
        showPostorder(root);
        printf("\n");
        freeTree(root);
    }
    return 0;
}
