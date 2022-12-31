#include <stdio.h>
#include <stdlib.h>
typedef struct _Node
{
    int val;
    struct _Node *next;
} Node;
int main(void)
{
    Node **pp;
    Node *p, *head = NULL;
    int i;
    printf("Part 1:\n");
    for (i = 3; i > 0; --i)
    {
        p = (Node *)malloc(sizeof(Node));
        p->val = i;
        p->next = head;
        head = p;
    }
    p = head;
    while (p)
    {
        printf("%p: %d | %p\n", p, p->val, p->next);
        p = p->next;
    }
    pp = &head;
    p = head;
    printf("Part 2:\n");
    printf("%p\n", p);
    printf("%p\n", *pp);
    while (p)
    {
        if (p->val == 2)
            *pp = p->next;
        pp = &p->next;
        p = p->next;
    }
    printf("Part 3:\n");
    p = head;
    while (p)
    {
        printf("%p: %d | %p\n", p, p->val, p->next);
        p = p->next;
    }
    return 0;
}