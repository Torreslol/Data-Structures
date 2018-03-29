//
//  Singly Linked List.c
//  Algorithm
//
//  Created by WenxuanWang on 28/03/2018.
//  Copyright © 2018 NTTDATA.INC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -20

typedef int ElemType;

typedef enum {
    INFEASIBLE = -2,
    ERROR = -1,
    OK = 1
} Status;


//定义链表节点
typedef struct Node {
    ElemType datap;
    struct Node *next;
}Node, *LinkList;

//带头结点的链表的初始化
void InitList(LinkList *L) {
    L = (LinkList *)malloc(sizeof(struct Node));
    if (*L)
        exit(OVERFLOW); //申请空间失败
    (*L)->next = NULL;
}

//销毁表
void DestroyList(LinkList *L) {
    //初始条件：线性表L已经存在
    LinkList q;
    while (*L) {
        q = (*L)->next;
        free(*L);
        *L = q;
    }
}

//清空表（保留头结点）
void ClearList(LinkList L) {
    //初始条件：线性表L已经存在
    LinkList p,q;
    p = L->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

//判断是否为空表
int IsListEmpty(LinkList L) {
    //初始条件： 线性表L已经存在
    return L->next == NULL;
}

//链表长度
int ListLength(LinkList L) {
    //初始条件： 线性表已经存在
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

//查询节点
Status GetElem(LinkList L, int i, ElemType *e) {
    int j = 1;
    LinkList p = L->next;
    while (p && j<i ) {
        j++;
        p = p->next;
    }
    //第i个元素不存在
    if (!p || j > i) {
        return ERROR;
    }
    *e = p->datap;
    return OK;
}

//定位数据位置
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    // 初始条件: 线性表L已存在，compare()是数据元素判定函数(满足为1，否则为0)
    // 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序
    // 若这样的数据元素不存在，则返回值为0
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        if (compare (e, p->datap))
            return i;
        p = p->next;
    }
    return 0;
}

//前驱
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e) {
    // 初始条件: 线性表L已存在
    // 操作结果: 若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，
    // 返回OK；否则操作失败，pre_e无定义，返回INFEASIBLE
    LinkList q, p = L->next; // p指向第一个结点
    while (p->next) { // p所指结点有后继
        q = p->next; // q为p的后继
        if (q->datap == cur_e) {
            *pre_e = p->datap;
            return OK;
        }
        p = q; // p向后移
    }
    return INFEASIBLE;
}

//后继
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
    // 初始条件：线性表L已存在
    // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，
    // 返回OK;否则操作失败，next_e无定义，返回INFEASIBLE
    LinkList p = L->next; // p指向第一个结点
    while (p->next) { // p所指结点有后继
        if (p->datap == cur_e) {
            *next_e = p->next->datap;
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}

//插入
Status ListInsert(LinkList L, int i, ElemType e) {
    // 算法2.9。不改变L
    // 在带头结点的单链线性表L中第i个位置之前插入元素e
    int j = 0;
    LinkList p = L, s;
    while (p && j < i - 1) { // 寻找第i-1个结点
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) // i小于1或者大于表长
        return ERROR;
    s = (LinkList)malloc(sizeof(struct Node)); // 生成新结点
    s->datap = e; // 插入L中
    s->next = p->next;
    p->next = s;
    return OK;
}

// 反转 (递归)
Node * ReverseListRecursion(Node *L) {
    if (L == NULL || L->next == NULL)
        return L;
    Node *new = ReverseListRecursion(L->next);
    L->next->next = L;
    L->next = NULL;
    return new;
}

//反转 (非递归)
Node * ReverseListIteration(Node *L) {
    if (L == NULL || L->next == NULL)
        return L;
    Node *pre = L;
    Node *cur = L->next;
    Node *temp = L->next->next;
    while (cur) {
        temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    L->next = NULL;
    return pre;
}





