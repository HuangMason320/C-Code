// Construct tree by inorder and postorder

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

int cur;

int idxsearch(int *inorder, int num, int a, int b)
{
    for (int i = a; i <= b; i++)
    {
        if (inorder[i] == num)
            return i;
    }
}

Node *buildtree(int *inorder, int *postorder, int start, int end)
{
    if (start > end)
        return NULL;
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = postorder[cur--];
    int idx = idxsearch(inorder, temp->value, start, end);
    temp->right = buildtree(inorder, postorder, idx + 1, end);
    temp->left = buildtree(inorder, postorder, start, idx - 1);
    return temp;
}

void showtree(Node *tree)
{
    if (tree)
    {
        printf("%d ", tree->value);
        showtree(tree->left);
        showtree(tree->right);
    }
}

void freetree(Node *tree)
{
    if (tree)
    {
        freetree(tree->right);
        freetree(tree->left);
        free(tree);
    }
}

int main()
{
    int n, times = 0;

    while (~scanf("%d", &n))
    {
        cur = n - 1;
        times++;
        int postorder[105], inorder[105];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &inorder[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &postorder[i]);
        }
        Node *tree = buildtree(inorder, postorder, 0, n - 1);
        printf("testcase%d: ", times);
        showtree(tree);
        freetree(tree);
        printf("\n");
    }
}
