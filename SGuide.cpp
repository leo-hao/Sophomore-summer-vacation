//Created by Leo on 16/12/9.
//Copyright ? 2016年 Leo. All rights reserved.
#include<iostream>
#include<String>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<cstdlib>
using namespace std;
#define MaxInt 30000
#define MVNum 100
#define OK 1
#define ERROW 0
typedef double ArcType;
typedef int Status;

typedef struct
{
	string name;
	int x;
	int y;
	string introduction;
}VerTex;

typedef struct
{
	VerTex vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum,arcnum;
}AMGraph;

Status CreateUDN(AMGraph &G);
void ShortestPath_Floyd(AMGraph G,double **D,int **Path);
void shortestPath(AMGraph G,double **D,int **Path);
int wenjiandaoru(AMGraph &G);
void inquirescenery(AMGraph G);


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

void shortestPath(AMGraph G,double **D,int **Path)
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

int wenjiandaoru(AMGraph &G)
{
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

void inquirescenery(AMGraph G)
{
	int i;
	cout<<"请输入查询景点的编号(1-10):";
	cin>>i;
	i--;
	
	cout<<"编号："<<i+1<<endl;
	cout<<"名称："<<G.vexs[i].name<<endl;
	cout<<"坐标："<<"("<<G.vexs[i].x<<","<<G.vexs[i].y<<")"<<endl;
	cout<<"介绍："<<G.vexs[i].introduction<<endl;
}

int main()
{

	AMGraph G;
	wenjiandaoru(G);

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
		cout<<"3 退出"<<endl;
		cout <<("************************\n"); 
		cout<<"请输入需要进行的操作:";
		cin>>k;
		if(k==1)
		{
			inquirescenery(G);
		}
		if(k==2)
		{
			shortestPath(G,D,Path);
		}
		if(k==3) break;
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
