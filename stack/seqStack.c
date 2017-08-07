
//栈又称堆栈，它是一种运算受限的线性表，其限制是仅允许在表的一端进行插入和删除运算。
//此例子是用顺序结构实现的线性栈

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType; //定义数据元素类型

//定义栈的顺序存储结构体
struct SeqStack
{
    ElemType *stack; //存放元素的数组指针
    int top;         //存放栈顶元素的下标位置
    int MaxSize;     //存放栈数组长度
};

//栈满需要重新分配更大空间 的情况
void againMalloc(struct SeqStack *S)
{
    ElemType *p = (ElemType *)realloc(S->stack, 2 * S->MaxSize * sizeof(ElemType)); //此处重新分配的空间为原来的2倍
    if (!p)                                                                         //重新分配失败
    {
        printf("存储空间用完！\n");
        exit(1);
    }
    S->stack = p; //使list指向新栈空间
    S->MaxSize = 2 * S->MaxSize;
    printf("存储空间已扩大为当前的2倍！\n"); //输出提示已扩充空间
}

//1初始化顺序栈，并设置空栈
void InitStack(struct SeqStack *S, int maxSize)
{
    if (maxSize < 0)
    {
        printf("maxSize的值非法");
        exit(1);
    }
    S->MaxSize = maxSize;
    S->stack = (ElemType *)malloc(maxSize * sizeof(ElemType));
    if (S->stack == NULL)
    { //当内存分配失败，退出应用
        printf("动态存储分配失败");
        exit(1);
    }
    S->top = -1; //值栈顶下标为-1表空栈
}

//2新元素进栈，插入栈顶
void Push(struct SeqStack *S, ElemType x)
{
    if (S->top == S->MaxSize - 1)
    {
        againMalloc(S);
    }
    S->top++;
    S->stack[S->top] = x;
}

//删除栈顶元素并返回
ElemType Pop(struct SeqStack *S)
{
    if (S->top == -1)
    {
        printf("空栈退出");
        exit(1);
    }
    S->top--;
    return S->stack[S->top + 1];
}

//获取栈顶元素的值(不出栈)
ElemType Peek(struct SeqStack *S)
{
    if (S->top == -1)
    {
        printf("空栈退出");
        exit(1);
    }
    return S->stack[S->top];
}

//判断栈是否为空栈，空位0；非空为1

int EmptyStack(struct SeqStack *S)
{
    return S->top == -1 ? 0 : 1;
}

//清除栈元素，并释放申请的内存空间
void ClearStack(struct SeqStack *S)
{
    if (S->stack)
    {
        free(S->stack); //释放该数据结构栈的内存
        S->top = -1;
        S->MaxSize = 0;
    }
}

int main()
{
    struct SeqStack s;
    int arr[10] = {2, 5, 16, 33, 64, 74, 12, 45, 42, 36};

    InitStack(&s, 6);
    for (int i = 0; i < 10; i++)
    {
        Push(&s, arr[i]);
    }

    printf("pop stack : %d \n", Pop(&s));
    printf("pop stack : %d \n", Pop(&s));
    Push(&s, 66);
    printf("Peek stack :%d \n", Peek(&s));
    printf("pop stack : %d \n", Pop(&s));

    printf("loop Pop Stack!!!\n");
    while (EmptyStack(&s) != 0)
        printf("pop stack : %d \n", Pop(&s));
    ClearStack(&s);
    getchar();
}