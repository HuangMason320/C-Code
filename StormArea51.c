#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct _Node
{
    struct _Node *left, *right;
    char idx[10];
} Node;

int x = 0, y = 0, z = 0;

Node *BuildTree()
{
    Node *temp = (Node *)malloc(sizeof(Node));
    scanf("%s", temp->idx);
    if (!strcmp(temp->idx, "+") || !strcmp(temp->idx, "-") || !strcmp(temp->idx, "*") || !strcmp(temp->idx, "/"))
    {
        temp->left = BuildTree();
        temp->right = BuildTree();
    }
    else
    {
        temp->right = NULL;
        temp->left = NULL;
    }
    return temp;
}

Node *PrintTree(Node *tree)
{
    if (tree)
    {
        PrintTree(tree->left);
        printf("%s", tree->idx);
        PrintTree(tree->right);
    }
}

int cal(Node *tree)
{
    if (!strcmp(tree->idx, "+"))
        return cal(tree->left) + cal(tree->right);
    else if (!strcmp(tree->idx, "-"))
        return cal(tree->left) - cal(tree->right);
    else if (!strcmp(tree->idx, "*"))
        return cal(tree->left) * cal(tree->right);
    else if (!strcmp(tree->idx, "/"))
        return cal(tree->left) / cal(tree->right);
    else if (!strcmp(tree->idx, "x"))
        return x;
    else if (!strcmp(tree->idx, "y"))
        return y;
    else if (!strcmp(tree->idx, "z"))
        return z;
    else
        return atoi(tree->idx);
}

int main()
{
    Node *tree = BuildTree();
    scanf("%d %d %d", &x, &y, &z);
    PrintTree(tree);
    printf("\n%d", cal(tree));
}