//队列的链接存储结构和操作实现

//因为链式，所以不用考虑循环队列的实现，链队无需考虑内存空间的大小。

//链式队列使用两个烧饼指针front、rear，分别指向队首、与队尾

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;  
//定义结点
struct sNode
{
    ElemType data;      //链式队列的数据元素
    struct sNode *next; // 链接指针域
};

struct QueueLk
{
    struct sNode * front; //指向队首的指针
    struct sNode * rear;  //指向队尾的指针
};

//1初始化链队
void InitQueue(struct QueueLk *HQ)
{
    HQ->front = HQ->rear = NULL;
}

//2向链队插入元素
void EnQueue(struct QueueLk *HQ, ElemType x)
{
    struct sNode *newp;
    newp = (struct sNode *)malloc(sizeof(struct sNode));
    if (newp == NULL)
    {
        printf("内存动态空间用完，退出运行！\n");
        exit(1);
    }
    newp->data = x;
    newp->next = NULL;
    if (HQ->front == NULL)
    {
        //若链队为空，则新节点既是队首结点又是队尾结点
        HQ->front = HQ->rear = newp;
    }
    else
    {
        HQ->rear->next = newp;
        HQ->rear = newp;
    }
}

//3从队列删除元素并返回
ElemType OutQueue(struct QueueLk *HQ)
{
    struct sNode *p;
    if (HQ->front == NULL)
    {
        printf("队列为空，无法删除！\n");
        exit(1);
    }
    ElemType temp;
    temp = HQ->front->data;
    p = HQ->front;
    HQ->front = p->next;   //使队首指针指向下一个节点
    if (HQ->front == NULL) //若删除后对空，则队尾指针也置空
        HQ->rear = NULL;
    free(p);
    return temp;
}

//4读取队首元素，不改变队列状态
ElemType PeekQueue(struct QueueLk *HQ)
{
    if (HQ->front == NULL)
    {
        printf("队列已空，无法读取！\n");
        exit(1);
    }
    return HQ->front->data;
}

//5检查一个链队是否为空，若是则返回1，否则返回0
int EmptyQueue(struct QueueLk *HQ)
{
    return (HQ->front == NULL) ? 1 : 0;
}

//6清除链队为空，释放动态存储空间
void ClearQueue(struct QueueLk *HQ)
{
    struct sNode *q = HQ->front;
    while (q != NULL) //依次删除队列中的每一个结点，循环结束后队首指针已变为空
    {
        HQ->front = q->next;
        free(q);
        q = HQ->front;
    }
    HQ->rear = NULL; //置队尾指针为空
}

//主函数
int main()
{
    struct QueueLk q;
    int a[8] = {3, 8, 5, 17, 9, 30, 15, 22};
    int i;
    InitQueue(&q);
    for (i = 0; i < 8; i++)
        EnQueue(&q, a[i]);
    printf("%d ", OutQueue(&q));
    printf("%d \n", OutQueue(&q));
    EnQueue(&q, 68);
    printf("%d ", PeekQueue(&q));
    printf("%d \n", OutQueue(&q));
    while (!EmptyQueue(&q))
        printf("%d ", OutQueue(&q));
    printf("\n");
    ClearQueue(&q);
    getchar();
}