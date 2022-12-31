// Uncle Huang choose Tutor(Easy version)
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int number;
    struct _Node *next;
} Node;

Node *ptr;

Node *createList(int n)
{
    Node *head, *now, *first = (Node *)malloc(sizeof(Node));
    for (int i = 1; i <= n; i++)
    {
        now = (Node *)malloc(sizeof(Node));
        now->number = i;
        if (i == 1)
            head = now;
        else
            first->next = now;
        if (i == n)
            now->next = head;
        else
            now->next = NULL;
        first = now;
    }
    ptr = head;
    return head;
}
void freeList(Node *head)
{
    free(head);
}
int solveJosephus(Node **head, int step)
{
    int n = 1, limit;
    Node *now, *tmp, *next;
    now = (*head);
    while (now->next != ptr)
    {
        n++;
        now = now->next;
    }
    for (int i = 0; i < n - 1; i++)
    {                                 // 會刪掉n-1個數，所以跑n-1次
        limit = (step - 1) % (n - i); // 算實際需要跑幾個，減1是為了只跑到要刪的數前面
        if (limit == 0)
            limit = n - i; // 因為從1開始跑，所以0的情況(自己那格)要微調
        for (int j = 1; j < limit; j++)
        {
            ptr = ptr->next; // 跑到完會是要刪的那個數的前面一格
        }
        tmp = ptr;              // 先記住前面那格
        next = ptr->next;       // 也要知道下面一格
        tmp->next = next->next; // 把前面那格直接只到要刪掉的下一格，那就跳過要刪掉的那一格了
        ptr = tmp->next;        // 讓ptr到下一次的起點
    }
    return tmp->number;
}

int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF)
    {
        Node *head;
        head = createList(n);
        printf("%d\n", solveJosephus(&head, k));
        freeList(head);
    }
    return 0;
}