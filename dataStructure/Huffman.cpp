//  Created by Leo on 17/7/12.
//  Copyright © 2017年 Leo. All rights reserved.
//  Huffman
#include<iostream>
using namepace std;
typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;
void Select(HuffmanTree &HT,int k, int &s1 ,int &s2)
{
    int temp1 = HT[1].weight;
    int temp2 = HT[1].weight;
    int index1 = 1;
    int index2 = 1;
    for(int i = 2; i <= k; i++)
    {
        if(temp1 > HT[i].weight)
        {
        index1 = i;
        temp1 = HT[i].weight;
        }
    }
    int j = 2;
    while(index2 != index1 && j <= k)
    {
       if(temp2 > HT[j].weight)
       {
        index2 = j;
        temp2 = HT[j].weight;
       }
    }
    s1 = index1;
    s2 = index2;

}

void CreateHuffmanTree(HuffmanTree &HT,int n)
{
    if(n < 1) return;
    int m = 2*n - 1;
    HT = new HTNode[m+1];
    int i;
    for(i = 1; i <= m; i++)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i = 1; i <= m; i++)
    {
        cin >> HT[i].weight;
    }
    for(i = n + 1; i <= m; i++)
    {   
        int s1,s2;
        Select(HT,i-1,s1,s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

typedef char **HuffmanCode;
void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n)
{
    HC = new char *[n+1];
    char * cd;
    cd = new char[n];
    cd[n-1] = '\0';
    int i;
    for(i = 1; i <= n; i++)
    {
        int start = n-1;
        int c = i;
        int f = HT[i].parent;
        while(f!=0)
        {
            --start;
            if(HT[f].lchild == c)
            cd[start]='0';
            esle cd[start] = '1';
            c = f; f = HT[f].parent;
        }
        HC[i] = new char[n-start];
        strcpy(HC[i],&cd[start]);
    }
    delete []cd;
    
}