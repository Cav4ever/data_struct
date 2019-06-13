#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct Node {
    ElemType data;
    struct Node *next;
} Node;
typedef Node *LinkList;

void visit(ElemType e)
{
    printf("%d ", e);    
}

Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    if (!(*L)) {
        return ERROR;
    }
    (*L)->next = NULL;
    return OK;
}

Status ListEmpty(LinkList L)
{
    if ((L->next)) {
        return ERROR;
    }
    return OK;
}

void ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;    
}

int ListLength(LinkList L)
{
    int len = 0;
    LinkList p = L;
    while (p->next) {
        len++;
        p = p->next;
    }
    return len;
}

Status GetElem(LinkList L, int i, ElemType *e)
{
    LinkList p = L->next;
    int j = 1;
    while (p && j < i) {
        j++;
        p = p->next;
    }
    if (!p || j > i) {
        return ERROR;
    }
    *e = p->data;
    return OK;
}

int LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;
    int i = 1;
    while (p) {
        if (p->data == e) {
            return i;
        }
        i++;
        p = p->next;
    }
    return 0;
}

Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 1;
    LinkList p, s;
    p = *L;
    while (p && j < i) {
        j++;
        p = p->next;
    }
    if(!p || j > i) {
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j = 1;
    LinkList p, q;
    p = *L;
    while (p->next && j < i) {
        j++;
        p = p->next;
    }
    if(!(p->next) || j > i) {
        return ERROR;
    }
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);

    return OK;
}

void ListTraverse(LinkList L)
{
    LinkList p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for (i = 0 ; i < n; i++) {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    for (i = 0 ; i < n; i++) {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}