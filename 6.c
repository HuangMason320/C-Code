// Operation on Sequence
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int value;
    struct _NODE *next;
} Node;

Node *new_node(int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void insert(Node **head, int num, int unit)
{
    for (unit; unit > 0; unit--)
    {
        Node *tmp = new_node(num);
        tmp->next = (*head)->next;
        (*head)->next = tmp;
    }
}

void erase(Node **head, int unit)
{
    while (unit--)
    {
        Node *tmp = (*head)->next;
        (*head)->next = tmp->next;
        free(tmp);
    }
}

void move(Node **head, int unit, int len)
{
    unit = (unit % len + len) % len;
    while (unit--)
    {
        (*head) = (*head)->next;
    }
}

void show(Node **head)
{
    Node *now = (*head);
    do
    {
        printf("%d%c", now->value, " \n"[now->next == (*head)]);
        now = now->next;
    } while (now != (*head));
}

int main()
{
    int x, n, num1, num2, len;
    char action[100];
    scanf("%d", &x);
    Node *head = new_node(x);
    head->next = head;
    len = 1;
    scanf("%d", &n);
    for (n; n > 0; n--)
    {
        scanf("%s", action);
        if (!strcmp(action, "insert"))
        {
            scanf("%d %d", &num1, &num2);
            insert(&head, num1, num2);
            len += num2;
        }
        else if (!strcmp(action, "erase"))
        {
            scanf("%d", &num1);
            erase(&head, num1);
            len -= num1;
        }
        else if (!strcmp(action, "move"))
        {
            scanf("%d", &num1);
            move(&head, num1, len);
        }
        else if (!strcmp(action, "show"))
        {
            show(&head);
        }
    }
    return 0;
}