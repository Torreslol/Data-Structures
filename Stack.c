//
//  Stack.c
//  Algorithm
//
//  Created by WenxuanWang on 2018/4/11.
//  Copyright © 2018 NTTDATA.INC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define stack struct Stack
#define STACK_POP_ERR 42

// 堆栈数据结构
struct Stack {
    int val[10]; // 数据
    int top;     // 栈顶
};
// 是否为空栈
bool empty(stack *stk) {
    return stk->top == 0;
}
// 入栈
void push(stack *stk, int x) {
    stk->top = stk->top + 1;
    stk->val[stk->top] = x;
}
// 出栈并返回数据
int pop(stack *stk) {
    if (empty(stk))
        return STACK_POP_ERR; // 不能彈出
    else {
        stk->top = stk->top - 1;
        return stk->val[stk->top + 1];
    }
}
