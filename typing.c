#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define next ptr_to_next_node
#define prev ptr_to_prev_node
#define ch character

void insert(Node **cur, char c)
{
    Node *np = (Node *)malloc(sizeof(Node));
    np->ch = c;
    np->next = (*cur)->next;
    (*cur)->next->prev = np;
    (*cur)->next = np;
    np->prev = (*cur);
    if ((*cur) == tail)
        tail = np;
}
void deletion(Node **cur)
{
    if ((*cur) != tail)
    {
        Node *del = (*cur)->next;
        (*cur)->next = del->next;
        del->next->prev = (*cur);
        if (del == tail)
            tail = (*cur);
        free(del);
    }
}
void backspace(Node **cur)
{
    if ((*cur) != head)
    {
        Node *back = (*cur);
        (*cur)->prev->next = back->next;
        back->next->prev = (*cur)->prev;
        (*cur) = back->prev;
        if (back == head)
            head = (*cur);
        free(back);
    }
}
void go_left(Node **cur, int t)
{
    while (t--)
    {
        (*cur) = (*cur)->prev;
    }
}
void go_right(Node **cur, int t)
{
    while (t--)
    {
        (*cur) = (*cur)->next;
    }
}
void go_home(Node **cur)
{
    (*cur) = head;
}
void go_end(Node **cur)
{
    (*cur) = tail;
}