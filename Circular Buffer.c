//
//  Circular Buffer.c
//  Algorithm
//
//  Created by WenxuanWang on 2018/4/11.
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

#define MAX_QSIZE 5 // 最大队列长度+1
typedef struct {
    ElemType *base; // 初始化的动态分配存储空间
    int front; // 头指针，若队列不空，指向队列头元素
    int rear; // 尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

// 循环队列的基本操作(9个)
void InitQueue(SqQueue *Q) {
    // 构造一个空队列Q
    Q->base = malloc(MAX_QSIZE * sizeof(ElemType));
    if (!Q->base) // 存储分配失败
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
}

void DestroyQueue(SqQueue *Q) {
    // 销毁队列Q，Q不再存在
    if (Q->base)
        free(Q->base);
    Q->base = NULL;
    Q->front = Q->rear = 0;
}

void ClearQueue(SqQueue *Q) {
    // 将Q清为空队列
    Q->front = Q->rear = 0;
}

int QueueEmpty(SqQueue Q) {
    // 若队列Q为空队列，则返回TRUE；否则返回FALSE
    if (Q.front == Q.rear) // 队列空的标志
        return 1;
    else
        return 0;
}

int QueueLength(SqQueue Q) {
    // 返回Q的元素个数，即队列的长度
    return (Q.rear - Q.front + MAX_QSIZE) % MAX_QSIZE;
}

Status GetHead(SqQueue Q, ElemType *e) {
    // 若队列不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
    if (Q.front == Q.rear) // 队列空
        return ERROR;
    *e = Q.base[Q.front];
    return OK;
}

Status EnQueue(SqQueue *Q, ElemType e) {
    // 插入元素e为Q的新的队尾元素
    if ((Q->rear + 1) % MAX_QSIZE == Q->front) // 队列满
        return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_QSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, ElemType *e) {
    // 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
    if (Q->front == Q->rear) // 队列空
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAX_QSIZE;
    return OK;
}

void QueueTraverse(SqQueue Q, void(*vi)(ElemType)) {
    // 从队头到队尾依次对队列Q中每个元素调用函数vi()
    int i;
    i = Q.front;
    while (i != Q.rear) {
        vi(Q.base[i]);
        i = (i + 1) % MAX_QSIZE;
    }
    printf("\n");
}

