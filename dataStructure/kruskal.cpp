//  Created by Leo on 7/18/2017
//  Copyright © 2017年 Leo. All rights reserved.
//  kruskal

#include<iostream>
#include<string>
using namespace std;
#define MVNum 100
typedef string VerTexType;
typedef int ArcType;
typedef struct {
    VerTexType Head;
    VerTexType Tail;
    ArcType lowcost;
}Edge[arcnum];
int Vexset[MVNum];
void MiniSpanTree_Kruskal(AMGraph G)
{
    Sort(Edge);
    int i,j,v1,v2;
    int vs1,vs2;
    for(i = 0; i < G.vexnum; i++)
        Vexset[i] = i;
    for(i = 0; i <G.arcnum; i++)
    {
        v1 = LocateVex(G,Edge[i].Head);
        v2 = LocateVex(G,Edge[i].Tail);
        vs1 = Vexset[v1];
        vs2 = Vexset[v2];
        if(vs1 != vs2)
        {
            cout << Edge[i].Head << Edge[i].Tail;
            for(j = 0; j < G.vexnum; j++)
            if(Vexset[j] == vs2) Vexset[j] = vs1;
        }
    }
}