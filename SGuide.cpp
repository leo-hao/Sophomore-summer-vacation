//Created by Leo on 16/12/9.
//Copyright ? 2016年 Leo. All rights reserved.
#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<cstdlib>
using namespace std;
#define MaxInt 3333             //表示极大值，无穷
#define MVNum 100               //最大顶点数
#define OK 1
#define ERROW 0
typedef double ArcType;        //边的权值为double
typedef int Status;

typedef struct
{
	string name;                 //地点名字
	int x;                       //坐标x                         
	int y;                       //坐标y
	string introduction;         //地点简介
}VerTex;                         //顶点结构体

typedef struct
{
	VerTex vexs[MVNum];             //顶点表
	ArcType arcs[MVNum][MVNum];     //邻接矩阵
	int vexnum,arcnum;              //结点数，边数
}AMGraph;                           //图

Status CreateUDN(AMGraph &G);       //创建无向图
void ShortestPath_Floyd(AMGraph G,double **D,int **Path);       //最短路径floyd
void ShortestPath(AMGraph G,double **D,int **Path);             //最短路径
int FileIn(AMGraph &G);                                         //文件导入
void SelectSite(AMGraph G);                                     //查询地点
void DFS_AM(AMGraph G,int v);//深度优先遍历

void ShortestPath_Floyd(AMGraph G,double **D,int **Path)
{
	int i,j,k;

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			D[i][j]=G.arcs[i][j];
			if(D[i][j]<MaxInt&&i!=j) Path[i][j]=i;
			else Path[i][j]=-1;
		}
	}
	for(k=0;k<G.vexnum;k++)
	{
		for(i=0;i<G.vexnum;i++)
		{
			for(j=0;j<G.vexnum;j++)
			{
				if(D[i][k]+D[k][j]<D[i][j])
				{
					D[i][j]=D[i][k]+D[k][j];
					Path[i][j]=Path[k][j];
				}
			}
		}
	}
}

void ShortestPath(AMGraph G,double **D,int **Path)
{
	int i,j;
    cout<<"请输入路径的起始景点:";
	cin>>i;
	cout<<"请输入终止景点的编号:";
	cin>>j;
	i--;
	j--;

	cout<<"路径的最短路径长度为："<<D[i][j];
	int biao[20],d=0;
	biao[d++]=j+1;
	while(Path[i][j]!=-1)
	{
		biao[d++]=Path[i][j]+1;
		j=Path[i][j];
	}
	cout<<"，最短路径为：";
	for(i=d-1;i>0;i--)
	{
		cout<<"景点"<<biao[i]<<"->";
	}
	cout<<"景点"<<biao[i]<<endl;
}

int FileIn(AMGraph &G)
 {	
 	string array[10][10];
 	for(int k = 0; k < 10; k++)
 		for(int t = 0; t < 10; t++)
 		{
 			array[k][t] =" ";
 		}
	
	ifstream infile;
	infile.open("scenery.txt",ios::in);
	if(!infile)
	{
		clog<<"open errow!"<<endl;
		exit(1);
	}
	int i,j;
	G.vexnum=10;
	for(i=0;i<G.vexnum;i++)
	{
		infile>>G.vexs[i].name>>G.vexs[i].x>>G.vexs[i].y>>G.vexs[i].introduction;
		array[G.vexs[i].x][G.vexs[i].y] = G.vexs[i].name;

	}
	for(int k = 0; k < G.vexnum; k++)
		{
		for(int t = 0; t < G.vexnum; t++)
		{
			cout <<setw(7)<< array[k][t] << "*";
		}
		cout << endl;
		}
	infile.close();

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(i==j) G.arcs[i][j]=0;
			else G.arcs[i][j]=MaxInt;
		}
	}

	infile.open("path.txt",ios::in);
	if(!infile)
	{
		clog<<"open errow!"<<endl;
		exit(1);
	}
	G.arcnum=11;
	int k;
	for(k=0;k<G.arcnum;k++)
	{
		infile>>i>>j;
		i--;
		j--;
		double length=sqrt(double((G.vexs[i].x-G.vexs[j].x)*(G.vexs[i].x-G.vexs[j].x)+(G.vexs[i].y-G.vexs[j].y)*(G.vexs[i].y-G.vexs[j].y)));
		G.arcs[i][j]=length;
		G.arcs[j][i]=length;
	}
	infile.close();
	

	return 0;
}

void SelectSite(AMGraph G)
{
	for(int j = 0; j < G.vexnum; j++)
	{
	cout<<"编号："<<j+1;
	cout<<"名称："<<G.vexs[j].name<<endl;
	} 
	int i;
	cout<<"请输入查询景点的编号(1-10):";
	cin>>i;
	i--;
	
	cout<<"编号："<<i+1<<endl;
	cout<<"名称："<<G.vexs[i].name<<endl;
	cout<<"坐标："<<"("<<G.vexs[i].x<<","<<G.vexs[i].y<<")"<<endl;
	cout<<"介绍："<<G.vexs[i].introduction<<endl;
}
void DFS_AM(AMGraph G, int v)
{
	int n = G.vexnum;
	int visited[n];
	int i;
	for(i = 0; i < n; i++)
		visited[i] = 0;
	visited[v] = 1;
	cout << G.vexs[v].name << " ";
	for(i = 0; i < n; i++)
		if((G.arcs[v][i]!=0)&&(G.arcs[v][i]!=MaxInt)&&(!visited[i]))
		DFS_AM(G,i);
}
int main()
{

	AMGraph G;
	FileIn(G);

	double **D;
	D=new double*[G.vexnum];
	for(int i=0;i<G.vexnum;i++)
	{
		*(D+i)=new double[G.vexnum];
	}
	int **Path;
	Path=new int*[G.vexnum];
	for(int i=0;i<G.vexnum;i++)
	{
		*(Path+i)=new int[G.vexnum];
	}
	ShortestPath_Floyd(G,D,Path);

	while(true)
	{   
		int k;
		cout <<("\n石家庄铁道大学导游图\n"); 
	    cout <<("************************\n");
		cout<<"1 查寻景点信息:"<<endl;
		cout<<"2 查找最短路径"<<endl;
		cout<<"3 从公园出发选一条最佳路线"<<endl;
		cout<<"4 不重复地浏览各景点,最后回到出口"<<endl;
		cout<<"5 退出"<<endl;
		cout <<("************************\n"); 
		cout<<"请输入需要进行的操作:";
		cin>>k;
		if(k==1)
		{
			SelectSite(G);
		}
		if(k==2)
		{
			ShortestPath(G,D,Path);
		}
		if(k==3)
		{
			
		}
		if(k==4)
		{	
			int v;
			cout << "请输入起点下标:" ;
			cin >> v;
			cout << "游览路线为：";
			DFS_AM(G,v);
		}
		if(k==5) break;
	}

	for(int i=0;i<G.vexnum;i++)
	{
		delete []D[i];
	}
	delete []D;
	for(int i=0;i<G.vexnum;i++)
	{
		delete []Path[i];
	}
	delete []Path;
    system("pause");
    return 0;
}
