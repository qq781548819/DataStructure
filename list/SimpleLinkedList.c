
/**在每个结点中除包含有数值域外，只设置一个指针域，用以指向其后继结点，这样构成的链接表被称为线性单向链接表，简称单向链表或单链表。
*/
//线性表-------------------单链表描述

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType; // 定义元素类型

struct eNode{
    ElemType data;  //存放链表的数据
    struct eNode* next; //指向下一个节点的指针
}


int main(){


}