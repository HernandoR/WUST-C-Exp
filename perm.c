/*
 * @Author: Hernando
 * @Date: 2020-12-17 19:53:41
 * @LastEditors: Hernando
 * @LastEditTime: 2020-12-17 20:25:13
 * @FilePath: \C语言实验d:\Downloads\perm.c
 */
#include <stdio.h>

void perm(int list[], int k, int m)
{
    if (k == m)
    {
        for (int i = 0; i < m; i++)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        return;
    }
    for (int i = k; i < m; i++) //第一次自己和自己换
    {
        swap(list + k, list + i);
        perm(list, k + 1, m);
        swap(list + k, list + i);
    }
}
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int main()
{
    int List[] = {1, 2, 3, 4};
    perm(List, 0, sizeof(List) / sizeof(int));
    return 0;
}