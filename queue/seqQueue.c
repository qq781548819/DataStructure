
/**
    概念：队列是一种运算受限的线性表，其限制是仅允许在表的一端进行插入（队尾），在表的另一端进行删除（队首）。

    因为概念，队列是一种仅允许在一端插入，一端删除，所以通常考虑队列为循环队列，

    队列经常用两个哨兵简化实现方式

    顺序实现：
    即队列front指向当前队列头的元素、队列尾rear指向队列队尾的下一个位置

    做约定，
    1》当空队列时：Q.front = Q.rear = 0;
    2》入队一个元素，尾指针后移一次，出队一个元素，头指针后移一次。
    3》 队列满时：( Q.rear + 1 ) % MaxSize == Q.front 
*/

//顺序循环队列实现

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
struct QueueSq
{
    ElemType *queue; //指向存储队列的数组空间
    int front, rear; //队首下标、队尾下标
    int MaxSize;     //queue数组长度
};
//扩展循环队列空间
void againMalloc(struct QueueSq *Q)
{
    ElemType *p;
    p = (ElemType *)realloc(Q->queue, 2 * Q->MaxSize * sizeof(ElemType));
    if (!p)
    {
        printf("存储空间用完！\n");
        exit(1);
    }
    Q->queue = p; //把新分配的数组指针赋予原队列数组
    if (Q->rear != Q->MaxSize - 1)
    { //如果队列数组出队过，需要重置队尾数组的重新排位
        int i;
        for (int i = 0; i < Q->rear; i++)
        {
            Q->queue[i + Q->MaxSize] = Q->queue[i]; //元队列的尾部内容后移maxSize个位置
        }
        Q->rear += Q->MaxSize; //队尾指针后移maxSize个位置
    }
    Q->MaxSize = 2 * Q->MaxSize; //队列空间修改为原来的2倍
    printf("存储空间已为当前2倍！\n");
}
//1初始化队列
void InitQueue(struct QueueSq *Q, int ms)
{
    if (ms <= 0)
    {
        printf("最大数组长度非法！\n");
        exit(1);
    }
    Q->MaxSize = ms;
    Q->queue = (ElemType *)malloc(ms * sizeof(ElemType)); //分配队列的内存空间
    if (!Q->queue)
    {
        printf("内存空间用完！\n");
        exit(1);
    }
    Q->front = Q->rear = 0; // 置空队列
}

//2向队列插入元素
void EnQueue(struct QueueSq *Q, ElemType x)
{
    //判断是否队列已满，满申请扩充队列
    if ((Q->rear + 1) % (Q->MaxSize) == Q->front) //队列满
        againMalloc(Q);
    Q->queue[Q->rear] = x;              // 进队
    Q->rear = (Q->rear + 1) % (Q->MaxSize); // 循环队列队尾往下移动
}

//3从队列出队并返回该出队元素
ElemType OutQueue(struct QueueSq *Q)
{
    //判断是否为空队列
    if (Q->front == Q->rear)
    {
        printf("队列已空，无法删除！\n");
        exit(1);
    }
    ElemType temp;
    temp = Q->queue[Q->front];             //获取队头元素
    Q->front = (Q->front + 1) % (Q->MaxSize); //队头下表指向下一个元素，表出队成功;
    return temp;
}

//4获取队首元素信息，不出队
ElemType PeekQueue(struct QueueSq *Q)
{
    //判断是否为空队列
    if (Q->front == Q->rear)
    {
        printf("队列已空，无法删除！\n");
        exit(1);
    }
    return Q->queue[Q->front];
}

//5清除一个队列为空，释放动态存储空间
void ClearQueue(struct QueueSq *Q)
{
    if (Q->queue != NULL)
    {
        free(Q->queue);
        Q->front = Q->rear = 0;
        Q->queue = 0;
        Q->MaxSize = 0;
    }
}

//6检查一个队列是否为空，若是则返回1，否则返回0
int EmptyQueue(struct QueueSq *Q)
{
    if (Q->front == Q->rear)
        return 1;
    else
        return 0;
}



//主函数
int main()
{
    struct QueueSq q;  
    struct QueueSq* p = &q;  
    int a[5] = {3,8,5,17,9};  
    int i;  
    InitQueue(&q, 6);  
    for (i = 0; i < 5; i++)  
        EnQueue(&q, a[i]);  
    printf("%d ", OutQueue(&q));  
    printf("%d ", OutQueue(&q));  
    printf("%d \n", OutQueue(&q));  
    EnQueue(&q, 67);  
    printf("插入了67！\n");  
    EnQueue(&q, 68);  
    printf("插入了68！\n");  
    EnQueue(&q, 69);  
    printf("插入了69！\n");  
    EnQueue(&q, 100);  
    printf("插入了100！\n");  
    printf("%d ", PeekQueue(&q));          //显示队头元素  
    printf("\n");  
    for (i = 0; i < 12; i++)  
        printf("%d ,", p->queue[i]);     //显示所有元素  
    printf("\n");  
    while (!EmptyQueue(&q))  
        printf("%d ", OutQueue(&q));  
    printf("\n");  
    ClearQueue(&q);  
    getchar();
}
