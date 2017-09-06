// Created by Leo on 7/21/2017
// Copyright © 2017年 Leo. All rights reserved.
// Sort

#include<iostream>
using namespace std;
#define Max 3
typedef struct
{
    int key;
    string name;
}SqList[Max+1];

void StraightInsertSort(SqList S)
{
    int i,j;
    for(i = 2; i < Max+1; i++)
    {
        if(S[i].key < S[i-1].key)
        {
            S[0] = S[i];
            S[i] = S[i-1];
        }
        for(j = i-2; S[j].key > S[0].key; j--)
        {
            S[j+1] = S[j];
        }
        S[j+1] = S[0];
    }
}
void BinaryInsertSort(SqList S)
{
    int low, high, k, i, j;
    for(i = 2; i < Max+1; i++)
    {
        S[0] = S[i];
        low = 1;
        high = i - 1;
        while(low <= high)
        {
            k = (low + high)/2;
            if(S[0].key < S[k].key)
            high = k - 1;
            else low = k + 1;
        }
        for(j = i - 1; j >= high + 1; j--)
       {
            S[j+1] = S[j];
       }
        S[high+1] = S[0];
    }
}

void ShellInsert(SqList S, int dk)
{
    int i,j;
    for(i = dk + 1; i < m + 1; i++)
    {
        if(S[i].key < S[i-dk].key)
        {
            S[0].key = S[i].key;
            for(j = i - dk; j > 0 && S[0].key < S[j].key; j-=dk)
            {
                S[j+dk] = S[j];
            }
            S[j+dk] = S[0];
        }
    }
}
void ShellSort(SqList S , int dt[],int t)
{
    int k;
    for(k = 0; k < t; k++)
    {
        ShellInsert(S,dt[k]);
    }
}

void BubbleSort(SqList S)
{
    int i, j;
    int m = Max - 1;
    int flag = 1;
    while((m > 0)&&(flag == 1))
    {
        flag = 0;
        for(j = 1; j <= m; j++)
            if(S[j].key > S[j+1].key)
            {
                flag =1;
                S[0] = S[j];
                S[j] = S[j+1];
                S[j+1] = S[0];
            }
            --m;
    }
}
int Partition(SqList L, int low, int high)
{
    L[0] = L[low];
    int pivotkey =L[low].key;
    while(high > low)
    {
        while(low < high && L[high].key >=pivtkey) --high;
        L[low] = L[high];
        while(low < high && L[low].key <= pivotkey) ++low;
        L[high] = L[low];
    }
    L[low] = L[0];
    return low;
}

void QSort(SqList L,int low, int high)
{
    if(low < high)
    {
        int pivotloc = Partition(L,low,high);
        QSort(L,low,pivotloc-1);
        QSort(L,pivotloc+1,high);
    }
}
void QuickSort(SqList L)
{
    QSort(L,1,m);
}
int main()
{
    SqList S;
    S[1].key=4;
    S[1].name = "c";
    S[2].key = 1;
    S[2].name = "a";
    S[3].key = 3;
    S[3].name = "b";
    //StraightInsertSort(S);
    BinaryInsertSort(S);
    for(int i = 1; i < m+1; i++)
    cout << S[i].name <<" ";
    cout <<endl;
    return 0;
}
