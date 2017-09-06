//  Created by Leo on 7/16/2017
//  Copyright © 2017年 Leo. All rights reserved.
//  prim

#include<iostream>
#include<string>
using namespace std;
#define MaxInt 32767
#define MVNum 100
typedef string VerTexType;
typedef int ArcType;
typedef struct
{
    VerTexType adjvex;
    ArcType lowcost;
}close;
typedef struct 
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AMGraph;



int LocateVex(AMGraph G,string v)
{   
    int i;
    for( i = 0; i < G.vexnum; i++)
    {
        if(v == G.vexs[i])
        return i;
    }
    return -1;
}

void CreateUDN(AMGraph &G)
{
    cout << "please input the vexnum and arcnum:";
    cin >> G.vexnum >> G.arcnum;
    int i,j;
    cout << "please input the vexs[i]:" << endl;
    for(i = 0; i < G.vexnum; i++)
        cin >> G.vexs[i];
    for(i = 0; i < G.vexnum; i++)
        for(j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MaxInt;
    for(int k = 0; k < G.arcnum; k++)
    {
        string v1,v2;
        int weight;
        cout << "please input v1 , v2 and weight:";
            cin >> v1 >> v2 >> weight;
        int i,j;
        i = LocateVex(G,v1);
        j = LocateVex(G,v2);
        G.arcs[i][j] = weight;
        G.arcs[j][i] = G.arcs[i][j];
        
        
    }
}

int Min(close closedge[],AMGraph G)
{   
    int m = closedge[0].lowcost;
    for(int i = 1; i < G.vexnum; i++)
    {
        if(m > closedge[i].lowcost)
        m = closedge[i].lowcost;
    }
    return m;
}
void MiniSpanTree_prim(AMGraph G,VerTexType u)
{   
    close closedge[MVNum];
    int k = LocateVex(G,u);
    int j,i;
    for(j = 0; j < G.vexnum; j++)
    {
        if(j != k) 
       {
        closedge[j].adjvex = u;//我想写：从k点到其它最短的一点p；
        closedge[j].lowcost = G.arcs[k][j];//再从k和p中选择最短的一未知点t；但不是kp，或是kt，或是pt；
        //再从k、p、t中选距离最短的未知点r，但不是已经存在直线，或是kr，或是pr，或是tr
        //再从k、p、t、r中选择距离最短的
        
       }
    }
    for(i = 1; i < G.vexnum; i++)
    {
        k = Min(closedge ,G);
        string u0 = closedge[k].adjvex;
        string v0 = G.vexs[k];
        cout << u0 << "," << v0 << endl;
        closedge[k].lowcost = 0;
        for(j = 0; j < G.vexnum; j++)
           {
                if(G.arcs[k][j] < closedge[j].lowcost)
              {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j];
              }

           }
    }
}
int main()
{   
    AMGraph G;
    CreateUDN(G);
    VerTexType u;
    cout << "please input u:";
    cin >> u;
    MiniSpanTree_prim(G,u);
    
    return 0;
}