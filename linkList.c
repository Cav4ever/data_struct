#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0

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
        return FALSE;
    }
    return TRUE;
}

void ClearList(LinkList L)
{
    LinkList p, q;
    p = L->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
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

Status ListInsert(LinkList L, int i, ElemType e)
{
    int j = 1;
    LinkList p, s;
    p = L;
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

Status ListDelete(LinkList L, int i, ElemType *e)
{
    int j = 1;
    LinkList p, q;
    p = L;
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

int main()
{
    LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));
    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    ClearList(L);
    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
        ListInsert(L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
    printf("ListLength(L)=%d \n",ListLength(L));

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j);
        if(k)
            printf("第%d个元素的值为%d\n",k,j);
        else
            printf("没有值为%d的元素\n",j);
    }

    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(L,j,&e); /* 删除第j个数据 */
        if(i==ERROR)
            printf("删除第%d个数据失败\n",j);
        else
            printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L);

    j=5;
    ListDelete(L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L);

    ClearList(L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L);

    ClearList(L);
    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L);

    return 0;
}
