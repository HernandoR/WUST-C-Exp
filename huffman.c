/*
 * @Author: Hernando
 * @Date: 2020-12-17 18:21:14
 * @LastEditors: Hernando
 * @LastEditTime: 2020-12-18 12:45:57
 * @FilePath: \C_EX\huffman.c
 */
#include <time.h>
#include "stdio.h"
#include <stdlib.h>

typedef struct
{
    unsigned int weight;
    unsigned int parent, LChild, RChild;
} HTNode, *HuffmanTree;

//HTNode T[100]; //预分配空间，避免指针越界

void select(HuffmanTree T, int range, int *goal);
int IsRChild(HuffmanTree H);

void CrtHuffmanTree(HuffmanTree T, int *input, int n) //*input存放用户输入的n个权值
{
    HuffmanTree vari;
    int m = 2 * n - 1, i = 0, s[2] = {0, 0}; //m是哈夫曼树的总结点数
    vari = T + 1;                            //指向哈夫曼树当前结点（1号结点）
    for (i = 1; i <= n; i++, vari++)         //每次初始化前需要移动哈夫曼树当前结点、用户输入的权值所在位置
    {
        vari->weight = 0;
        vari->weight = input[i - 1]; //将哈夫曼树的叶子结点初始化，并将父节点、左右孩子结点标识置0
        vari->parent = 0;
        vari->LChild = 0;
        vari->RChild = 0;
    }
    for (; i <= m; i++, vari++) //在叶子结点输入完毕的基础上继续移动，使所有非叶子结点置空
    {
        vari->weight = 0;
        vari->parent = 0;
        vari->LChild = 0;
        vari->RChild = 0;
    }
    for (i = n + 1; i <= m; i++) //开始布置非叶子结点
    {
        select(T, i - 1, s); //在前(i-1) 个结点中选择权值最小的两个结点，位置值通过s数组返回
        T[s[0]].parent = i;
        T[s[1]].parent = i;
        T[i].LChild = s[0];
        T[i].RChild = s[1];                            //选定结点的父结点等相关信息的更新
        T[i].weight = T[s[0]].weight + T[s[1]].weight; //父结点权值是两个选定结点的权值之和
    }
}
void select(HuffmanTree T, int range, int *goal) //将1-range中最小的两个结点位置值通过goal数组返回
{
    HTNode vari = T[1];
    int temp1 = 100, temp2 = 100, j = 1, k = 1;
    if (range <= 1) //如果给定的范围数不正常，返回0值
    {
        goal[0] = 0;
        goal[1] = 0;
        return;
    }
    for (j = 1; j <= range; j++)
    {
        vari = T[j];
        if (vari.parent == 0)
            temp1 = vari.weight < temp1 ? vari.weight : temp1; //遍历范围内结点，取最小权值记入temp1
    }
    for (j = 1; j <= range; j++)
    {
        vari = T[j];
        if (vari.weight == temp1 && vari.parent == 0)
            break; //找到最小值所在的位置
    }
    goal[0] = j; //找到最小值所在的位置
    for (k = 1; k <= range; k++)
    {
        vari = T[k];
        if (vari.parent == 0 && vari.weight >= temp1 && vari.weight < temp2 && (k != goal[0])) //遍历范围内当前权值比最小值大、比前面的结点值小，更新temp2
            temp2 = vari.weight;
    }
    for (k = 1; k <= range; k++)
    {
        vari = T[k];
        if (vari.weight == temp2 && vari.parent == 0 && (k != goal[0]))
            break;
    }
    goal[1] = k; //找到第二小值所在的位置
}
int IsRChild(HuffmanTree H)
{
    return (H == T + (T + (H->parent))->RChild);
}

void Swap(HTNode *a, HTNode *b)
{
    HTNode c = *a;
    *a = *b;
    *b = c;
}

void Perm(HTNode *TermNode, int k, int m)
{
    if (k == m)
    {
        for (int i = 1; i <= m; i++) //注意修改成「1，m」
        {
            int p = TermNode[i].weight;
            printf("%d ", p);
        }
        printf("\n");
        return;
    }
    for (int i = k; i <= m; i++) //第一次自己和自己换 //注意修改成「k，m」
    {
        Swap(TermNode + k, TermNode + i);
        Perm(TermNode, k + 1, m);
        Swap(TermNode + k, TermNode + i);
    }
}

void experiment() //测试单元
{
    int input[100] = {1, 2, 3, 4}; //测试例子
    int i, a = 0;
    i = 4;

    CrtHuffmanTree(T, input, i);

    Perm(T, 1, i);
}

int main() //无关紧要
{

    //freopen("test.out", "w", stdout);
    time_t begin, end;
    double ret;
    begin = clock();

    experiment();

    end = clock();
    ret = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;
    printf("\n runtime:%f", ret);

    //fclose(stdin);
    //fclose(stdout);
    return 0;
}