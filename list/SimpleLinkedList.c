
/**在每个结点中除包含有数值域外，只设置一个指针域，用以指向其后继结点，这样构成的链接表被称为线性单向链接表，简称单向链表或单链表。
*/
//线性表-------------------单链表描述


#include<stdio.h>  
#include<stdlib.h>  
#define NN 12  
#define MM 20  
typedef int ElemType;  //定义元素类型  
struct sNode           //定义单链表结点类型  
{  
    ElemType data;  
    struct sNode* next;  
};  
  
//1、初始化线性表，即置单链表的表头指针为空  
void InitList(struct sNode** HL)  
{  
    *HL = NULL;  
}
  
//2、清除线性表L的所有元素，即释放单链表的所有结点，使之成为空表  
void ClearList(struct sNode** HL)  
{  
    struct sNode *cp, *np;  //定义两个相邻结点的指针  
    cp = *HL;               //头指针赋给cp  
    while (cp != NULL)  
    {  
        np = cp->next;      //用np保存下一个结点的指针  
        free(cp);           //释放cp指向的结点  
        cp = np;            //使下一个结点成为当前结点  
    }  
    *HL = NULL;             //置单链表的表头指针为空  
}  
  
//3、返回单链表的长度  
int SizeList(struct sNode* HL)  
{  
    int i = 0;  
    while (HL != NULL)  
    {  
        i++;  
        HL = HL->next;  
    }  
    return i;  
}  
  
//4、检查单链表是否为空，若为空则返回1否则返回0  
int EmptyList(struct sNode* HL)  
{  
    if (HL == NULL)  
        return 1;  
    else  
        return 0;  
}  
  
//5、返回单链表中第pos个结点的元素，若pos超出范围，则停止程序运行  
ElemType GetElem(struct sNode* HL, int pos)  
{  
    int i = 0;  
    if (pos < 1)  
    {  
        printf("pos值非法，退出运行！\n");  
        exit(1);  
    }  
    while (HL != NULL)  
    {  
        i++;  
        if (i == pos)  
            break;  
        HL = HL->next;  
    }  
    if (HL != NULL)  
        return HL->data;  
    else  
    {  
        printf("pos值非法，退出运行！\n");  
        exit(1);  
    }  
}  
  
//6、遍历一个单链表  
void TraverseList(struct sNode* HL)  
{  
    while (HL != NULL)  
    {  
        printf("%d,", HL->data);  
        HL = HL->next;  
    }  
    printf("\n");  
}  
  
//7、从单链表中查找具有给定值x的第一个元素的，成功返回结点data域的存储地址，否则返回NULL  
ElemType* FindList(struct sNode* HL, ElemType x)  
{  
    while (HL != NULL)  
    {  
        if (HL->data == x)  
            return &HL->data;  
        else  
            HL = HL->next;  
    }  
    return NULL;  
}  
  
//8、修改单链表中第pos个结点的值为x，成功返回1失败返回0  
int UpdatePosList(struct sNode* HL, int pos, ElemType x)  
{  
    int i = 0;  
    struct sNode* p = HL;  
    while (p != NULL)  
    {  
        i++;  
        if (pos == i)  
            break;  
        else  
            p = p->next;  
    }  
    if (pos == i)  
    {  
        p->data = x;  
        return 1;  
    }  
    else  
        return 0;  
}  
  
//9、向单链表表头插入一个元素  
void InsertFirstList(struct sNode** HL, ElemType x)  
{  
    struct sNode *newp;  
    newp = (sNode *)malloc(sizeof(struct sNode));  
    if (newp == NULL)  
    {  
        printf("内存动态空间用完，退出运行！\n");  
        exit(1);  
    }  
    newp->data = x;  
    newp->next = *HL;  
    *HL = newp;          //把新节点作为新的表头结点  
}  
  
//10、向单链表的末尾添加一个元素  
void InsertLastList(struct sNode** HL, ElemType x)  
{  
    struct sNode *newp;  
    newp = (sNode *)malloc(sizeof(struct sNode));  
    if (newp == NULL)  
    {  
        printf("动态内存空间用完，退出运行！\n");  
        exit(1);  
    }  
    newp->data = x;  
    newp->next = NULL;  
    if (*HL == NULL)   //若原表为空  
        *HL = newp;  
    else  
    {  
        struct sNode* p = *HL;  
        while (p->next != NULL)  
            p = p->next;  
        p->next = newp;  
    }  
}  
  
//11、向单链表中第pos个结点位置插入元素x，成功返回1失败返回0  
int InsertPosList(struct sNode** HL, int pos, ElemType x)  
{  
    int i = 0;  
    struct sNode *newp;  
    struct sNode *cp = *HL, *ap = NULL;  
    if (pos <= 0)  
    {  
        printf("pos值不正确，返回0表示插入失败！\n");  
        return 0;  
    }  
    while (cp != NULL)  
    {  
        i++;  
        if (pos == i)  
            break;  
        else  
        {  
            ap = cp;  
            cp = cp->next;  
        }  
    }  
    newp = (sNode *)malloc(sizeof(struct sNode));  
    if (newp == NULL)  
    {  
        printf("内存动态空间用完，无法插入！\n");  
        return 0;  
    }  
    newp->data = x;  
    if (ap == NULL)    //插入表头的情况  
    {  
        newp->next = cp;  
        *HL = newp;  
    }  
    else              //插入到ap与cp之间的情况  
    {  
        newp->next = cp;  
        ap->next = newp;  
    }  
    return 1;  
}  
  
//12、向有序单链表中插入元素x，使得插入之后仍然有序  
void InsertOrderList(struct sNode** HL, ElemType x)  
{  
    struct sNode* cp = *HL, *ap = NULL;  
    struct sNode *newp;  
    newp = (sNode *)malloc(sizeof(struct sNode));  
    if (newp == NULL)  
    {  
        printf("内存动态空间用完，退出运行！\n");  
        exit(1);  
    }  
    newp->data = x;  
    if (cp == NULL || x < cp->data)   //把新结点插入到表头  
    {  
        newp->next = cp;  
        *HL = newp;  
        return;  
    }  
    while (cp != NULL)  
    {  
        if (x < cp->data)  
            break;  
        else  
        {  
            ap = cp;  
            cp = cp->next;  
        }  
    }  
    newp->next = cp;  //把x结点插入到ap与cp之间  
    ap->next = newp;  
}  
  
//13、从单链表中删除头结点，并返回结点值，失败则停止程序运行  
ElemType DeleteFirstList(struct sNode** HL)  
{  
    ElemType temp;  
    struct sNode* p = *HL;    //暂存表头结点指针  
    if (*HL == NULL)  
    {  
        printf("单链表为空，无表头删除，退出运行！\n");  
        exit(1);  
    }  
    *HL = (*HL)->next;  
    temp = p->data;           //暂存表头元素  
    free(p);  
    return temp;  
}  
  
//14、从单链表中删除尾结点并返回它的值，失败则停止程序运行  
ElemType DeleteLastList(struct sNode** HL)  
{  
    ElemType temp;  
    struct sNode* cp = *HL;  
    struct sNode* ap = NULL;  
    if (cp == NULL)  
    {  
        printf("单链表为空，无表尾删除，退出运行！\n");  
        exit(1);  
    }  
    while (cp->next != NULL)  
    {  
        ap = cp;  
        cp = cp->next;  
    }  
    if (ap == NULL)  //若单链表只有一个结点  
        *HL = (*HL)->next;  
    else  
        ap->next = NULL;  
    temp = cp->data;  
    free(cp);  
    return temp; //把新节点作为新的表头结点  
}  
  
//15、从单链表删除第pos个结点并返回它的值，失败则停止程序运行  
ElemType DeletePosList(struct sNode** HL, int pos)  
{  
    int i = 0;  
    ElemType temp;  
    struct sNode* cp = *HL;  
    struct sNode* ap = NULL;  
    if (cp == NULL || pos <= 0)  
    {  
        printf("单链表为空或pos值不正确，退出运行！\n");  
        exit(1);  
    }  
    while (cp != NULL)  
    {  
        i++;  
        if (i == pos)  
            break;  
        ap = cp;  
        cp = cp->next;  
    }  
    if (cp == NULL)    //单链表中没有第pos个结点  
    {  
        printf("pos值不正确，退出运行！\n");  
        exit(1);  
    }  
    if (pos == 1)   //删除表头结点  
        *HL = (*HL)->next;   //或：*HL = cp->next;  
    else  
        ap->next = cp->next;  
    temp = cp->data;  
    free(cp);  
    return temp;  
}  
  
//16、从单链表中删除值为x的第一个结点，成功返回1失败返回0  
int DeleteValueList(struct sNode** HL, ElemType x)  
{  
    struct sNode* cp = *HL;  
    struct sNode* ap = NULL;  
    while (cp != NULL)  
    {  
        if (cp->data == x)  
            break;  
        ap = cp;  
        cp = cp->next;  
    }  
    if (cp == NULL)    //单链表中不存在值为x的结点  
        return 0;  
    if (ap == NULL)    //在表头位置  
        *HL = (*HL)->next;   //或：*HL = cp->next;  
    else  
        ap->next = cp->next;  
    free(cp);  
    return 1;  
}  
  
  
//主函数  
int main()  
{   
    int a[NN];  
    int i;  
    struct sNode *p, *h, *s;  
    InitList(&p);                   //初始化，置单链表表头为空  
    for (i = 0; i < NN; i++)        //产生12个随机数  
        a[i] = rand() % MM;  
    printf("随机数序列：");  
    for (i = 0; i < NN; i++)  
        printf("%d,",a[i]);  
    printf("\n");  
    printf("随机数逆序：");  
    for (i = 0; i < NN; i++)  
        InsertFirstList(&p, a[i]);  //将a[i]倒序插入单链表  
    TraverseList(p);                //遍历  
    printf("单链表长度：%d\n", SizeList(p)); //输出单链表长度  
    for (h = p; h != NULL; h = h->next)      //每个元素循环与后面的元素进行比较，删除重复数  
        while (DeleteValueList(&(h->next), h->data));  
    printf("去除重复数：");  
    TraverseList(p);                         //遍历  
    printf("单链表长度：%d\n", SizeList(p)); //输出单链表长度  
    h = NULL;  
    for (s = p; s != NULL; s = s->next)//将上面的单链表的值依次插入新的一个空单链表，每步插入后都有序  
        InsertOrderList(&h, s->data);  
    printf("有序表序列：");  
    TraverseList(h);                   //遍历  
    ClearList(&p);                     //清除单链表  
    getchar();
}  