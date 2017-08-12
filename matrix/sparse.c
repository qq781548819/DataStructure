/**
稀疏矩阵概念：稀疏矩阵是矩阵中的一种特殊情况，
其非零元素个数远小于零元素个数。

稀疏矩阵的存储结构
稀疏矩阵的存储结构分为顺序存储和链接存储，
链接存储又分为带行指针向量的链接存储与十字链接存储。

*/

#include <stdio.h>
#include <stdlib.h>
#define MaxTerms 10 //非零元素的最大值
#define MaxRows 10  //行数最大值
#define MaxColumns 10
typedef ElemType int; // 定义稀疏矩阵存储元素类型
//1顺序存储，按数组下表存储
//因为稀疏矩阵由行（row） 列（col） 值（val）决定的
//结构定义如下
struct Triple //三元组结构定义,存储非0
{
    int row;      //行号
    int col;      //列号
    ElemType val; //对应矩阵值
};

struct SMatrix //稀疏矩阵定义
{
    int m, n, t;                    //表行数，列数、非零元素个数
    struct Triple sm[MaxTerms + 1]; // 存储三元组的数组，下标从1开始
};

//2带行指针向量的链接存储
struct TripleNode //三元组结点类型定义
{
    int row, col;            //行号、列号
    ElemType val;            //元素值
    struct TripleNode *next; //指向同一行的下一个结点
};
struct LMatrix //带行指针向量的链接存储类型定义
{
    int m, n, t;                        //行数、列数、非零元素个数
    struct TripleNode *lm[MaxRows + 1]; //存储行单链表的数组指针，下标从1开始
};

//3十字链接存储
struct CrossNode //结点类型定义
{
    int row, col;                   //行号， 列号
    ElemType val;                   //元素值
    struct CrossNode *down, *right; //指向同一列下一个结点的指针，指向同一行下一个结点的指针
};
struct CLMatrix //十字链接存储类型定义
{
    int m, n, t;                          //行数、列数、非零元素个数
    struct CrossNode *rm[MaxRows + 1];    //存储行单链表的数组指针，下标从1开始
    struct CrossNode *cm[MaxColumns + 1]; //存储列单链表的数组指针，下标从1开始
};

//1、稀疏矩阵初始化
void InitMatrix_S(struct SMatrix *M) //对SMatrix类型初始化
{
    M->m = 0;
    M->n = 0;
    M->t = 0;
}

void InitMatrix_L(struct LMatrix *M) //对LMatrix类型初始化
{
    int i;
    M->m = 0;
    M->n = 0;
    M->t = 0;
    for (i = 1; i <= MaxRows; i++)
    {
        M->lm[i] = NULL;
    }
}

void InitMatrix_CL(struct CLMatrix *M) //对CLMatrix类型初始化
{
    int i;
    M->m = 0;
    M->n = 0;
    M->t = 0;
    for (i = 1; i < MaxRows; i++)
    {
        M->rm[i] = NULL;
    }
    for (i = 1; i <= MaxColumns; i++)
    {
        M->cm[i] = NULL;
    }
}

//2稀疏矩阵的建立
void InputMatri_S(struct SMatrix *M, int m, int n) //采用SMatrix存储类型的稀疏矩阵建立
{
    int k = 0;
    int row, col;
    ElemType val;
    M->m = m; //行数
    M->n = n; //列数
    printf("依次输入每个三元组，每个三元组格式为：元素,元素,元素+回车\n并最后输入(0,0,0)作为结束：\n");
    scanf("%d,%d,%d", &row, &col, &val);
    while (row != 0)
    { //以输入一个特殊的三元组（0,0,0）结束整个输入过程
        k++;
        M->sm[k].row = row;
        M->sm[k].col = col;
        M->sm[k].val = val;
        scanf("%d,%d,%d", &row, &col, &val); //输入下一个三元组
    }
    M->t = k; // 非零元素个数
}

