#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
struct sNode
{
    ElemType data;
    struct sNode *next; //栈顶指针
};

//1、初始化链栈为空

void InitStack(struct sNode **TP)
{ //top point栈顶指针
    *TP=NULL;
}

//2、入栈
void Push(struct sNode **TP, ElemType x)
{
    struct sNode *n = (struct sNode *)malloc(sizeof(struct sNode));
    if (n == NULL)
    {
        printf("内存动态空间用完，退出运行！\n");
        exit(1);
    }
    n->data = x;
    n->next = *TP;
    *TP = n;
}
//3、从链栈中删除栈顶元素并返回它
ElemType Pop(struct sNode **TP)
{
    struct sNode *p;
    ElemType temp;
    if (*TP == NULL)
    {
        printf("栈空无法删除！\n");
        exit(1);
    }
    p = *TP;        //把栈顶指针赋值给结构体p指针
    *TP = p->next;  //栈顶指针下移，原栈顶元素出栈
    temp = p->data; //获取栈顶元素的值
    free(p);        //释放内存空间
    return temp;
}

//4、读取栈顶元素
ElemType Peek(struct sNode **TP)
{
    if (*TP == NULL)
    {
        printf("栈空，无栈顶结点！\n");
        exit(1);
    }
    return (*TP)->data;
}

//5、检查链栈是否为空,0为空，1为非空
int EmptyStack(struct sNode **TP)
{
    return (*TP) == NULL ? 0 : 1;
}

//6、清除链栈为空栈
void ClearStack(struct sNode **TP)
{
    struct sNode *cp,*np;
    cp = *TP;
    while(cp!=NULL){
        np = cp->next;
        free(cp);
        cp = np;
    }
    *TP = NULL;
}
//主函数  
int main()  
{  
    struct sNode *a;  
    int x = 0;  
    int m[8] = {3, 8, 5, 17, 9, 30, 15, 22};  
    printf("当前序列：3,8,5,17,9,30,15,22\n");  
    InitStack(&a);  
    while (x != 8)  
    {  
        Push(&a, m[x]);  
        x++;  
    }  
    printf("逆序列为：");  
    while (!EmptyStack(&a))  
        printf("%d,", Pop(&a));  
    printf("\n");  
    ClearStack(&a);  
    getchar();
}  