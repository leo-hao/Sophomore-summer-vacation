//  最短路径，关键路径,平衡二叉树
//  Created by Leo on 17/7/1.
//  Copyright © 2017年 Leo. All rights reserved.
#include<iostream>
#include<iomanip>
using namespace std;
#define MaxInt 32767                        //表示极大值，无穷
#define MVNum 100                           //最大顶点数
#define MAX_SIZE 100  
typedef char VerTexType;                    //顶点的数据类型为字符型
typedef int ArcType;                        //边的权值为整型
typedef struct{
    VerTexType vexs[MVNum];                 //顶点表
    ArcType arcs[MVNum][MVNum];             //邻接矩阵
    int vexnum,arcnum;                      //图当前点数和边数
}AMGraph;

typedef struct ArcNode{
    int adjvex;                             //该边所指向的顶点的位置
    struct ArcNode * nextarc;               //指向下一条边的指针
    int weight;                             //边的权值
}ArcNode;                                   //边结点

typedef struct VNode{
    VerTexType data;
    ArcNode *firstarc;                      //指向第一条依附该顶点的边结点
    int indegree;                           //入度
}VNode,AdjList[MVNum];                      //AdjList表示邻接表类型

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;                      //图的当前顶点数和边数
}ALGraph;

typedef struct{
    int *base;                              //栈底指针
    int *top;                               //栈顶指针
    int stacksize;                          //栈可用最大容量
}SqStack;

void InitStack(SqStack &S)                  //初始化
{//构造一个空栈
    S.base = new int [1000];               //为顺序栈动态分配一个最大容量为MVNum的数组空间
    if(!S.base) exit(1);                    //存储分配失败
    S.top = S.base;                         //top初始为base，空栈
    S.stacksize = 1000;                    //stacksize置为栈的最大容量MVNum
}

void Push(SqStack &S, int e)                //入栈
{//插入元素e为新的栈顶元素
    if(S.top - S.base == S.stacksize) 
    {cout << "Stack Overflow!";  exit(1);}  //栈满
    *S.top++ = e;                           //元素e压入栈顶，栈顶指针加一
}

void Pop(SqStack &S, int &e)                //出栈
{//删除栈顶元素，用e返回其值
    if(S.top == S.base) 
    { cout<<"Stack Empty!"; exit(1);}       //栈空
    e = *--S.top;                           //栈顶指针减一，将栈顶元素赋给e
}

void CreateALGraph(ALGraph &G)
{//采用邻接表表示方法，创建有向图G
    int i,j,k;
    cout << "input vertex number: ";
    cin >> G.vexnum;
    cout << "input edge number: ";
    cin >> G.arcnum;                         //输入总顶点数，总边数
    for(i = 0; i < G.vexnum; i++)            //输入各点，构造表头节点表
    {
        cout << "input vertex(" << i << "): ";
        cin >> G.vertices[i].data;          //输入顶点值
        G.vertices[i].firstarc = NULL;      //初始化表头结点的指针域为NULL
    }
    int w;
    for(k = 0; k < G.arcnum; k++)           //输入各边，构造邻接表
    {
        cout << "输入v1，v2的位置i,j，和权值w：";
        cin >> i >> j >> w;                 //输入边依附的两个顶点及权值
        ArcNode *p;
        p = new ArcNode;                    //生成一个新的边结点*p
        p->adjvex=j;                        //邻接点序号为j
        p->weight=w;                        //边权值为w
        p->nextarc=G.vertices[i].firstarc;  
        G.vertices[i].firstarc=p;          //将*p插入顶点vi的边表头部
        
    }

}
int TopologicalSort(ALGraph &G, int topo[]) //拓扑排序
{//有向图G采用邻接表存储结构
//若G无回路，则生成一个拓扑排序topo[]
    SqStack S;
    InitStack(S);                             //栈S初始化为空
    ArcNode *p;
    int i;
    for(i = 0; i < G.vexnum; i++)    
        G.vertices[i].indegree = 0;          //结点入度初始化为0    
    for(i = 0; i < G.vexnum; i++)             //计算各个顶点的入度 
    {   
        p=G.vertices[i].firstarc;            //p指向vi第一个邻接点
        while(p)    
       {    
            G.vertices[p->adjvex].indegree++;    
            p=p->nextarc;    
        }    
    }    
    for(i = 0; i < G.vexnum; i++)              //入度为0入栈
        if(G.vertices[i].indegree == 0)
            Push(S,i);
    int m = 0;                                 //对输出顶点计数，初始为0
    int k;
    while(S.top != S.base)                     //栈S非空
    {
        Pop(S,i);                              //将栈顶顶点vi出栈
        topo[m] = i;                           //将vi保存到拓扑数组topo中
        ++m;                                   //对输出顶点计数
        p = G.vertices[i].firstarc;            //p指向vi第一个邻接点
        while(p != NULL)
        {
            k = p->adjvex;                     //vk为vi的邻接点
            --G.vertices[k].indegree;          //vi的每个邻接点的入度减一
            if(G.vertices[k].indegree == 0)    //若入度减为0，则入栈
            Push(S,k);
            p = p->nextarc;                    //p指向vi的下一个邻接点
        }
    }
    if(m < G.vexnum)
    {
        cout << "该有向图有回路！" << endl;
        return 0;
    }
    else cout << "该图是AOE网" << endl;
    return 1;
}

void CriticalPath(ALGraph &G)
{//G为邻接表存储的有向网，输出G的各项关键活动
    cout << "关键活动:" ;
    int topo[G.vexnum];
    if(!TopologicalSort(G,topo))
    {
        cout << "调用失败" << endl;
        exit(1);
    }
    int n = G.vexnum;                       //n为顶点数
    int i,j,k;
    int ve[n],vl[n],e,l;
    ArcNode *p;
    p = new ArcNode;                        //生成一个新的边结点*p
    for(i = 0; i < n; i++)                  //给每个事件的最早发生事件置为0
        ve[i] = 0;
    /*按拓扑排序算法求每个时间的最早发生时间*/
    for(i = 0; i < n; i++)
    {
        k = topo[i];                        //取得拓扑排序中顶点序号k
        p = G.vertices[k].firstarc;         //p指向k的第一个邻接顶点
        while(p != NULL)
        {//依次更新k的所有邻接顶点的最早发生时间
            j = p->adjvex;                  //j为邻接顶点的序号
            if(ve[j] < ve[k] + p->weight)   //更新顶点j的最早发生时间ve[j]
                ve[j] = ve[k] + p->weight;
            p = p->nextarc;                 //p指向k的下一个邻接顶点
        }
    }
    for(i = 0; i < n; i++)                  //给每个事件的最迟发生时间置初值ve[n-1]
        vl[i] = ve[n-1];
    /*按拓扑排序求每个事件最迟发生时间*/
    for(i = n-1; i >= 0; i--)
    {
        k = topo[i];                        //取得拓扑排序中顶点序号k
        p = G.vertices[k].firstarc;         //p指向k的第一个邻接顶点
        while(p != NULL)
        {//根据k的邻接点，更新k的最迟发生时间
            j = p->adjvex;                  //j为邻接顶点的序号
            if(vl[k] > vl[j] - p->weight)   //更新顶点k最迟发生时间vl[k]
                vl[k] = vl[j] - p->weight;
            p = p->nextarc;                 //p指向k的下一个邻接顶点
        }
    }
    /*判断每一活动是否为关键活动*/
    for(i = 0; i < n; i++)
    {//每次循环针对vi为活动开始点的所有活动
        p = G.vertices[i].firstarc;        //p指向i的第一个邻接顶点
        while(p != NULL)
        {
            j = p->adjvex;                 //j为i的邻接顶点的序号
            e = ve[i];                     //计算活动<vi,vj>的最早开始时间
            l = vl[j] - p->weight;         //计算活动<vi,vj>的最迟开始时间
            if(e == l)                     //若为关键活动，则输出<vi,vj>
                cout << "(" << G.vertices[i].data << "," << G.vertices[j].data << ")" << p->weight << " ";
            p = p->nextarc;                //p指向i的下一个邻接顶点
        }
    }
    cout << endl;
}
int LocateVex(AMGraph G, char v)
{//确定v在G中的位置，即顶点数组的下标
    int i;
    for(i = 0; i < G.vexnum; i++)
        if(G.vexs[i] == v)
            return i;
return -1;
}
void CreateGraph(AMGraph &G)
{
    //采用邻接矩阵表示法，创建有向图G
    cout << "input vertex number: ";
    cin >> G.vexnum;
    cout << "input edge number: ";
    cin >> G.arcnum;                         //输入总顶点数，总边数
    if(G.vexnum < 1|| G.arcnum <1|| (G.arcnum > G.vexnum*(G.vexnum-1)))//判断输入的合理性
    {
        cout << "input error: invalid parameters!" << endl;
        return ;
    }
    for(int i = 0; i < G.vexnum; i++)       //依次输入点的信息
        {
            cout << "input vertex(" << i << "): ";
            cin >> G.vexs[i];
            
        }
    for(int i = 0; i < G.vexnum; i++)       //初始化邻接矩阵，边的权值为最大值MaxInt
        for(int j = 0; j < G.vexnum; j++)
            if (i==j)
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = MaxInt;
            
    int w;
    char v1, v2;
     int i, j;
    for(int k = 0; k < G.arcnum; k++)       //构造邻接矩阵
    {   cout << "input edge(" << i << ") vextex1 and vextex2 and weight :";
        cin >> v1 >> v2 >> w;               //输入一条边的顶点和权值
                          
        i = LocateVex(G, v1);               //确定v1在G中的位置，即顶点数组的下标
        j = LocateVex(G, v2);               //确定v2在G中的位置，即顶点数组的下标
        G.arcs[i][j] = w;                   //边<v1,v2>的权值置为w
    }
     for(int i = 0; i < G.vexnum; i++)
        cout << setw(7) << G.vexs[i] << "  " ;
        cout << endl;
     for(int i = 0; i < G.vexnum; i++)      //显示邻接矩阵
       {cout << G.vexs[i] << "  ";
         for(int j = 0; j < G.vexnum; j++)
            cout << setw(7) << G.arcs[i][j] << "  ";
        cout << endl ;
       }
    
}

void DestroyGraph(AMGraph &G)
{
    for(int i = 0; i < G.vexnum; i++)       //销毁邻接矩阵，边的权值为最大值MaxInt
        for(int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MaxInt;
}


void ShortestPath_Floyd(AMGraph G)
{//用Floyd算法求有向图G中各对顶点i和j之间的最短路径
    int n = G.vexnum;
    int D[n][n],Path[n][n];
    for(int i = 0; i < G.vexnum; i++)       //各对结点之间初始已知路径即距离
        for(int j = 0; j < G.vexnum; j++)
        {
            D[i][j] = G.arcs[i][j]; 
            if(D[i][j] < MaxInt) 
                Path[i][j] = i;             //如果i和j之间有弧，则将j的前驱置为i
            else Path[i][j] = -1;           //如果i和j之间没有弧，则将j的前驱置为-1
        }
    for(int k = 0; k < G.vexnum; k++)
        for(int i = 0; i < G.vexnum; i++)     
             for(int j = 0; j < G.vexnum; j++)
                if(D[i][k] + D[k][j] < D[i][j])//从i经k到j的一条路径更短
                {
                    D[i][j] = D[i][k] + D[k][j];//更新D[i][j]
                    Path[i][j] = Path[k][j];    //更改j的前驱为k 
                }
   
    cout << "Floyd: " << endl;                   // 打印floyd最短路径的结果
    cout << endl ;
    int temp;
   // SqStack S;
   // InitStack(S);                             //栈S初始化为空
    int array[MVNum];
   
    int v;
    for (int i = 0; i < G.vexnum; i++)
    {    
        for (int j = 0; j < G.vexnum; j++)
           {    
                //Push(S,j);                  //将最后一个结点压入栈
                int index = 0;
                array[index] = j;
                temp = Path[i][j];          //j的前驱赋给temp
                if(temp == -1)
                {
                    break;
                }
                cout << "ShortestPath : ";
                while (temp != i)           
                {
                     //Push(S,temp);          //将temp结点压入栈中
                     index++;
                     array[index] = temp;
                     temp = Path[i][temp];  //将temp前一个结点赋给temp
                 }
                 cout << G.vexs[i];
                 if(i == j && i == 0)
                 {
                     cout << "-->" <<G.vexs[i];
                 }
                 while(v != j)
                 {
                     v = array[index];
                     index--;
                     cout << "-->" << G.vexs[v] ;
                     
                 }
                    cout << "  "<< D[i][j] << endl;
           }
        cout << endl;
    }
               
}


void ShortestPath_DIJ(AMGraph G, char v0)
{//用Dijkstra算法求有向图G的v0顶点到其余顶点的最短路径
    int n;
    n = G.vexnum;                           //n为G的顶点个数
    bool S[n];                              //true表示源点v0到"顶点i"的最短路径已经获得
    int D[n];                               //表示源点v0到"顶点i"的最短路径
    int Path[n];                            //"顶点i"的前驱
    int t = LocateVex(G,v0);
    for(int v = 0; v < n; v++)              //n个顶点依次初始化
    {
        S[v] = false;                       //S初始为空集
        D[v] = G.arcs[t][v];                //将v0到各个终点的最短路径长度初始化为弧上的权值
        Path[v] = 0;                        //将v的前驱置为0
    }
   // 对源点v0自身进行初始化
    S[t] = true;                            //将v0加入S
    D[t] = 0;                               //源点到源点的距离为0 
    /*初始化结束，开始主循环，每次求得的v0到某个顶点的v的最短路径，将v加到S集*/
    int min;
    int v;
    for(int i = 1; i < n; i++)              //对其余n-1个顶点，依次进行计算
    {
        min = MaxInt;
        for(int w = 0; w < n; w++)
            if(!S[w] && D[w] < min)         //选择一条当前的最短路径，终点为v
            { 
              v = w;
              min = D[w];
            }
        S[v] = true;                        //将v加入S
        for(int w = 0; w < n; w++)          //更新从v0出发到集合 V-S上的所有点的最短路径长度
            if(!S[w] && (D[v] + G.arcs[v][w] < D[w]))
            {
                D[w] = D[v] + G.arcs[v][w]; //更新D[w]
                Path[w] = v;                //更改w的前驱为v
            }
    }
    cout << "Dijkstra:" << endl;
    int array[MVNum];
    int temp;
    cout << v0 << "->" << G.vexs[t] << " shortest path is " << D[t] << endl;
    for(int i = 1; i < n; i++)
    {   
        int index = 0;
        temp = Path[i];
        array[index] = i;
        while(temp != t)
        {
            index++;
            array[index] = temp;
            temp = Path[temp];  //将temp前驱赋给temp
        }
        cout << v0 ;
        while(array[index] != i)
        {
             cout << "->" << G.vexs[array[index]] ;
             index--;
        }
        cout << "--> " << G.vexs[i] << " shortest path is " << D[i] << endl;
    }
}
typedef struct AVLNode{  
      
        int data;    
        int bf;  //平衡因子    
        struct AVLNode *lchild;    
        struct AVLNode *rchild;    
      
    }AVLNode;  
      
    AVLNode* SetAVLNode(int data){  
        AVLNode* root = new AVLNode;  
        root->bf = 0;  
        root->data = data;  
        root->lchild = NULL;  
        root->rchild = NULL;  
        return root;  
    }  
      
    void printDataInfo(int i){  
        cout << i << " ";  
    }  
      
      
    AVLNode* LL_Rotate( AVLNode *a ){//LL(顺时针)型调整   
      
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b = a->lchild;//b指向a的左子树根结点    
        a->lchild = b->rchild; //b的右子树挂在a的左子树上    
        b->rchild = a;  
      
        a->bf = b->bf = 0;  
        return b;  
    }       
    AVLNode* RR_Rotate( AVLNode *a ){ //RR(逆时针)型调整    
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b = a->rchild;//b指向a的右子树根结点    
        a->rchild = b->lchild; //b的左子树挂在a的右子树上    
        b->lchild = a;  
      
        a->bf = b->bf = 0;  
        return b;  
      
    }      
    AVLNode* LR_Rotate( AVLNode *a ){//LR(先逆后顺)型调整   
        if (a == NULL){  
            return NULL;  
        }  
        AVLNode *b = a->lchild;//b指向a的左子树根结点    
        AVLNode *c = b->rchild;//c指向b的右子树的根节点  
      
        a->lchild = c->rchild;  
        b->rchild = c->lchild;  
      
        c->lchild = a;  
        c->rchild = b;  
      
        if (c->bf == 1){  
            a->bf = -1;  
            b->bf = 0;  
        } else if (c->bf == -1){  
            a->bf = 0;    
            b->bf = 1;   
        } else {  
            b->bf = a->bf = 0;    
        }  
        c ->bf = 0;  
      
        return c;  
      
    }        
    AVLNode* RL_Rotate( AVLNode *a ){//RL(先顺后逆)型调整    
        if (a == NULL){  
            return NULL;  
        }  
      
        AVLNode *b, *c;    
        b = a->rchild;    
        c = b->lchild;    
        a->rchild = c->lchild;    
        b->lchild = c->rchild;    
        c->lchild = a;    
        c->rchild = b;    
      
        //调整平衡因子    
        if( c->bf == 1 ) {    
            a->bf = 0;    
            b->bf = -1;    
        } else if( c->bf == -1 ) {    
            a->bf = 1;    
            b->bf = 0;    
        } else  {    
            a->bf = b->bf = 0;    
        }    
        c->bf = 0;    
        return c;    
    }      
      
    /************************************************************************/  
    /* 1、找到要插入的位置，同时找到平衡因子为1的结点，因为这个结点修改之后肯定最先变为2 
    2、从平衡因子不为0的结点到插入结点，开始修改平衡因子 
    3、找到平衡因子大于等于2的根节点修改即可。 
    4、修改头结点的指针 
    */  
    /************************************************************************/  
    void insertAVL(AVLNode **root,int data){  
        AVLNode *f, *a, *b, *p, *q;  
      
        AVLNode *s = SetAVLNode(data);  
        //printDataInfo(data);  
        //头结点  
        if ((*root) == NULL){  
            (*root) = s;  
            return;  
        }  
        a=p=(*root) ;     /* a指向离s最近且平衡因子不为0的结点 */  
      
        f=q=NULL ;      /*   f指向a的父结点,q指向p父结点  */   
      
      
        //寻找插入点位置及最小不平衡树的子树    
        while( p != NULL ) {    
            if( p->data == s->data ){  
                //AVL中已经存在关键字    
                return;    
            }  
      
            if( p->bf != 0 ){   //寻找最小不平衡子树   
                a = p;    
                f = q;    
            }    
            q = p;  //q指向p父结点   
            if( s->data < p->data ){  
                p = p->lchild;   
            }else {  
                p = p->rchild;    
            }  
        }    
      
        if( s->data < q->data ){  
            q->lchild = s;   
        }  else  {     //将结点*s插入到合适的位置上去    
            q->rchild = s;    
        }  
      
        p = a; //从不为0 的结点开始修改   
        while( p != s ){    //插入结点后修改相应的平衡因子    
      
            if( s->data < p->data ) {   
      
                p->bf++;    
                p = p->lchild;    
            } else {  
      
                p->bf--;    
                p = p->rchild;    
            }    
        }    
        if( a->bf > -2 && a->bf < 2 ) {//插入结点后没有破坏平衡树    
            return;    
        }   
        if( a->bf == 2 ){   
      
            b = a->lchild;    
            if( b->bf == 1 )           //结点插在*a的左孩子的左子树中    
                p = LL_Rotate( a );    //LL型调整    
            else                       //结点插在*a的左孩子的右子树中    
                p = LR_Rotate( a );    //LR型调整    
        } else {  
            b = a->rchild;    
            if( b->bf == 1 )          //结点插在*a的右孩子的左子树中    
                p = RL_Rotate( a );   //RL型调整    
            else                      //结点插在*a的右孩子的右子树中    
                p = RR_Rotate( a );   //RR型调整    
        }    
        if( f == NULL )               //原*a是AVL树的根    
            (*root) = p;    
        else if( f->lchild == a )     //将新子树链到原结点*a的双亲结点上    
            f->lchild = p;    
        else     
            f->rchild = p;    
    }  
      
    AVLNode* createAVL(){  
        int i = 0;  
        AVLNode *root = NULL;  
        int e;
        cout << "请输入(int)数据,0为结束:";
        cin >> e;
        while (e != 0) //将0作为接受标志
        {
            insertAVL(&root, e); 
            cout << "请输入(int)数据,0为结束:"; 
            cin >> e;
        }  
        return root;  
      
    }  
      
      
    void inOrderTraverseAVL(AVLNode* root){  
        AVLNode* stack[MAX_SIZE];  
        int top = -1;  
      
        AVLNode* p = root;  
        while(p != NULL || top> -1){  
            while ( p!= NULL){  
                stack[++top] = p;  
                p = p->lchild;  
            }  
      
            p = stack[top--];  
            printDataInfo(p->data);  
            p = p->rchild;  
        }  
      
    }  
void  PreOrderTraverseAVL(AVLNode* root)
{
    if(root)
    {
        cout << root->data << " ";
        PreOrderTraverseAVL(root->lchild);
        PreOrderTraverseAVL(root->rchild);
    }
}
void PostOrderTraverseAVL(AVLNode *root)
{
    if(root)
    {
        PostOrderTraverseAVL(root->lchild);
        PostOrderTraverseAVL(root->rchild);
        cout << root->data << " ";
    }
}
      

int main()
{   
    AMGraph G;
    char ch;
    cout << "ShortestPath_Floyd" << endl;
    CreateGraph(G);
    ShortestPath_Floyd(G);
    cout << endl;
    cout << "ShortestPath_DIJ" << endl;
    cout << "input the first vextex for Dijkstra：" ;
    cin >> ch;
    ShortestPath_DIJ(G,ch);
    cout << endl;
    cout << "CriticalPath" << endl;
    ALGraph G2;
    CreateALGraph(G2);
    CriticalPath(G2);
    cout << endl;
    cout << "AVL" << endl;
    AVLNode* root = createAVL();  
    cout << "中序遍历:";
    inOrderTraverseAVL(root);
    cout << endl;
    cout << "先序遍历:";
    PreOrderTraverseAVL(root);
    cout << endl;
    cout << "后序遍历:";
    PostOrderTraverseAVL(root);
    cout << endl;
    return 0;
}