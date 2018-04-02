//
//  FIFO Queue.c
//  Algorithm
//
//  Created by WenxuanWang on 02/04/2018.
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

typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front, rear; // 队头、队尾指针
} LinkQueue;

// 链队列的基本操作(9个)
void InitQueue(LinkQueue *Q) {
    // 构造一个空队列Q
    Q->front = Q->rear = malloc(sizeof(QNode));
    if (!Q->front)
        exit(OVERFLOW);
    Q->front->next = NULL;
}

void DestroyQueue(LinkQueue *Q) {
    // 销毁队列Q(无论空否均可)
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

void ClearQueue(LinkQueue *Q) {
    // 将Q清为空队列
    QueuePtr p, q;
    Q->rear = Q->front;
    p = Q->front->next;
    Q->front->next = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
}

int QueueEmpty(LinkQueue Q) {
    // 若Q为空队列，则返回TRUE，否则返回FALSE
    if (Q.front->next == NULL)
        return 1;
    else
        return 0;
}

int QueueLength(LinkQueue Q) {
    // 求队列的长度
    int i = 0;
    QueuePtr p;
    p = Q.front;
    while (Q.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

Status GetHead_Q(LinkQueue Q, ElemType *e) {
    // 若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
    QueuePtr p;
    if (Q.front == Q.rear)
        return ERROR;
    p = Q.front->next;
    *e = p->data;
    return OK;
}

void EnQueue(LinkQueue *Q, ElemType e) {
    // 插入元素e为Q的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) // 存储分配失败
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

Status DeQueue(LinkQueue *Q, ElemType *e) {
    // 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR
    QueuePtr p;
    if (Q->front == Q->rear)
        return ERROR;
    p = Q->front->next; // 指向头结点
    *e = p->data;
    Q->front = p->next; // 摘下头节点
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

void QueueTraverse(LinkQueue Q, void(*vi)(ElemType)) {
    // 从队头到队尾依次对队列Q中每个元素调用函数vi()
    QueuePtr p;
    p = Q.front->next;
    while (p) {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}
