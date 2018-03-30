#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -20

typedef int ElemType;

typedef enum {
    INFEASIBLE = -2,
    ERROR = -1,
    OK = 1
} Status;

// 线性表的双向链表存储结构
typedef struct Node {
    ElemType data;
    struct Node *prior, *next;
} Node, *LinkList;

// 带头结点的双向循环链表的基本操作(14个)
void InitList(LinkList *L) {
    // 产生空的双向循环链表L
    *L = (LinkList)malloc(sizeof(Node));
    if (*L)
        (*L)->next = (*L)->prior = *L;
    else
        exit(OVERFLOW);
}

void DestroyList(LinkList *L) {
    // 操作结果：销毁双向循环链表L
    LinkList q, p = (*L)->next; // p指向第一个结点
    while (p != *L) { // p没到表头
        q = p->next;
        free(p);
        p = q;
    }
    free(*L);
    *L = NULL;
}

void ClearList(LinkList L) { // 不改变L
    // 初始条件：L已存在。操作结果：将L重置为空表
    LinkList q, p = L->next; // p指向第一个结点
    while (p != L) { // p没到表头
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L; // 头结点的两个指针域均指向自身
}

int ListEmpty(LinkList L) {
    // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
    if (L->next == L && L->prior == L)
        return 1 ;
    else
        return 0;
}

int ListLength(LinkList L) {
    // 初始条件：L已存在。操作结果：返回L中数据元素个数
    int i = 0;
    LinkList p = L->next; // p指向第一个结点
    while (p != L) { // p没到表头
        i++;
        p = p->next;
    }
    return i;
}

Status GetElem(LinkList L, int i, ElemType *e) {
    // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    int j = 1; // j为计数器
    LinkList p = L->next; // p指向第一个结点
    while (p != L && j < i) { // 顺指针向后查找，直到p指向第i个元素或p指向头结点
        p = p->next;
        j++;
    }
    if (p == L || j > i) // 第i个元素不存在
        return ERROR;
    *e = p->data; // 取第i个元素
    return OK;
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    // 初始条件：L已存在，compare()是数据元素判定函数
    // 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
    // 若这样的数据元素不存在，则返回值为0
    int i = 0;
    LinkList p = L->next; // p指向第1个元素
    while (p != L) {
        i++;
        if (compare(p->data, e)) // 找到这样的数据元素
            return i;
        p = p->next;
    }
    return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e) {
    // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，
    // 否则操作失败，pre_e无定义
    LinkList p = L->next->next; // p指向第2个元素
    while (p != L) { // p没到表头
        if (p->data == cur_e) {
            *pre_e = p->prior->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
    // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，
    // 否则操作失败，next_e无定义
    LinkList p = L->next->next; // p指向第2个元素
    while (p != L) { // p没到表头
        if (p->prior->data == cur_e) {
            *next_e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

LinkList GetElemP(LinkList L, int i) { // 另加
    // 在双向链表L中返回第i个元素的地址。i为0，返回头结点的地址。若第i个元素不存在，
    // 返回NULL
    int j;
    LinkList p = L; // p指向头结点
    if (i < 0 || i > ListLength(L)) // i值不合法
        return NULL;
    for (j = 1; j <= i; j++)
        p = p->next;
    return p;
}

Status ListInsert(LinkList L, int i, ElemType e) {
    // 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1
    // 改进算法2.18，否则无法在第表长+1个结点之前插入元素
    LinkList p, s;
    if (i < 1 || i > ListLength(L) + 1) // i值不合法
        return ERROR;
    p = GetElemP(L, i - 1); // 在L中确定第i个元素前驱的位置指针p
    if (!p) // p=NULL,即第i个元素的前驱不存在(设头结点为第1个元素的前驱)
        return ERROR;
    s = (LinkList)malloc(sizeof(Node));
    if (!s)
        return OVERFLOW;
    s->data = e;
    s->prior = p; // 在第i-1个元素之后插入
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return OK;
}

Status ListDelete(LinkList L, int i, ElemType *e) {
    // 删除带头结点的双链循环线性表L的第i个元素，i的合法值为1≤i≤表长
    LinkList p;
    if (i < 1) // i值不合法
        return ERROR;
    p = GetElemP(L, i); // 在L中确定第i个元素的位置指针p
    if (!p) // p = NULL,即第i个元素不存在
        return ERROR;
    *e = p->data;
    p->prior->next = p->next; // 此处并没有考虑链表头，链表尾
    p->next->prior = p->prior;
    free(p);
    return OK;
}
