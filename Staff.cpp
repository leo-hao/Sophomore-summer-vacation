//  员工管理系统
//  Created by Leo on 17/7/5.
//  Copyright © 2017年 Leo. All rights reserved.

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
typedef struct Worker{
    //编号、姓名、性别、出生年月、学历、职务、电话、住址
    int num;
    string name,sex,birth,edu,position,tel,address;
}Worker;

typedef struct LNode{
    Worker data;  //结点的数据域
    int length;
    struct LNode *next; //结点的指针域
}LNode,*LinkList;//LinkList为指向结构体LNode的指针类型
void add(LinkList &L);
void ModifyElem(LinkList &L);
void ListDelete(LinkList &L);
void GetElem(LinkList L);
void Sort(LinkList  L);
void show(LinkList L);
void save(LinkList L);
void InitList(LinkList &L) //单链表的初始化
{//构造一个空的单链表W
    L = new LNode;  //生成新结点作为头结点，用头指针W指向头结点
    L->length = 0;
    L->next = NULL;  //头结点的指针结点域置空
}
void menu(LinkList &L)  //显示菜单
{   
    
    cout<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"** 员工信息管理系统主菜单  **"<<endl;
    cout<<"**  1.员工信息查询   **"<<endl;
    cout<<"**  2.员工信息更新   **"<<endl;
    cout<<"**  3.员工信息插入   **"<<endl;
    cout<<"**  4.员工信息删除   **"<<endl;
    cout<<"**  5.员工信息排序   **"<<endl;
    cout<<"**  6.员工信息显示   **"<<endl;
    cout<<"**  7.员工信息保存   **"<<endl;
    cout<<"**  0.退出    **"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<endl;
    int i;
    cout<<"请选择数字编号0~7:";
    cin >> i;
    while(i<0||i>7)
    {
        cout<<"输入有误，请重新输入："<<endl;
        cin>>i;
    }
    switch(i)
    {
        case 1:GetElem(L);break;
        case 2:ModifyElem(L);break;
        case 3:add(L);break;
        case 4:ListDelete(L);break;
        case 5:Sort(L);break;
        case 6:show(L);break;
        case 7:save(L);break;
        case 0:cout<<"系统退出！！"<<endl;
        exit(0);
        default:
        break;
    }
}


void GetElem(LinkList L) //查询
{
    LinkList p = new LNode;
    p = L->next; //初始化，p指向首元结点
    cout<<"***********************************************"<<endl;
    cout<<"**  请选择查找方式：  **"<<endl;
    cout<<"**  1.按工号查找   **"<<endl;
    cout<<"**  2.按姓名查找   **"<<endl;
    cout<<"**  0.返回主菜单   **"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<endl;
    cout<<"请选择数字编号0~2："<<endl;
    int i;
    cin>>i;
    while(i<0||i>2)
    {
    cout<<"输入有误，请重新输入："<<endl;
    cin>>i;
    }
    if(i == 1)
    { 
    int num2;
    cout<<"请输入要查询的员工的工号："<<endl;
    cin>>num2;
    while (p && (p->data.num != num2))
        // 顺链域向后扫描，直到p为空或p所指的结点的数据域等于num2
         p = p->next;
    
    }
    else if(i == 2)
    {
        string name2;
        cout<<"请输入要查询的员工的姓名："<<endl;
        cin>>name2;
        while (p && (p->data.name != name2))
            // 顺链域向后扫描，直到p为空或p所指的结点的数据域等于num2
            p = p->next;
    }
    else menu(L);
    if(p == NULL)
    {
        cout<<"没有员工信息存入，系统将返回主菜单"<<endl;
        menu(L);
    }
     else
     {
        cout<<"查询的员工信息如下："<<endl;
        cout<<"***********************************************"<<endl;
        cout<<" 编号:"<<p->data.num<<endl;
        cout<<" 姓名:"<<p->data.name<<endl;
        cout<<" 性别:"<<p->data.sex<<endl;
        cout<<" 生日:"<<p->data.birth<<endl;
        cout<<" 学历:"<<p->data.edu<<endl;
        cout<<" 职务:"<<p->data.position<<endl;
        cout<<" 电话:"<<p->data.tel<<endl;
        cout<<" 住址址:"<<p->data.address<<endl;
        cout<<"***********************************************"<<endl;
        GetElem(L);
     }
}

void ModifyElem(LinkList &L)//修改
{   
    LinkList p = new LNode;
    p = L->next; //初始化，p指向首元结点
    int num2;
    cout << "请输入你需要修改的员工编号：";
    cin >> num2;
    while (p && (p->data.num != num2))
        // 顺链域向后扫描，直到p为空或p所指的结点的数据域等于num2
        p = p->next;
     if(p == NULL)
    {
        cout<<"没有员工信息存入，系统将返回主菜单"<<endl;
        menu(L);
    }
     else
     {
        cout<<"查询的员工信息如下："<<endl;
        cout<<" 编号:"<<p->data.num<<endl;
        cout<<" 姓名:"<<p->data.name<<endl;
        cout<<" 性别:"<<p->data.sex<<endl;
        cout<<" 生日:"<<p->data.birth<<endl;
        cout<<" 学历:"<<p->data.edu<<endl;
        cout<<" 职务:"<<p->data.position<<endl;
        cout<<" 电话:"<<p->data.tel<<endl;
        cout<<" 住址:"<<p->data.address<<endl;
     }
     int i;
     cout<<"***********************************************"<<endl;
     cout<<"**  1.修改编号   **"<<endl;
     cout<<"**  2.修改姓名   **"<<endl;
     cout<<"**  3.修改性别   **"<<endl;
     cout<<"**  4.修改出生日期**"<<endl;
     cout<<"**  5.修改学历   **"<<endl;
     cout<<"**  6.修改职务   **"<<endl;
     cout<<"**  7.修改电话   **"<<endl;
     cout<<"**  8.修改住址  **"<<endl;
     cout<<"**  0.返回主菜单   **"<<endl;
     cout<<"***********************************************"<<endl;
     cout<<endl;
     cout<<"请选择数字编号0~8："<<endl;
     cin >> i;
     while(i<0||i>8)
     {
      cout<<"输入有误，请重新输入："<<endl;
      cin>>i;
      }
      string x;
      int y;
     switch(i)
     {
        case 1:
                cout<<"请输入新的员工编号:";
                cin>>y;
                p->data.num = y;
                break;
        case 2:
                cout<<"请输入新的员工姓名:";
                cin>>x;
                p->data.name = x;
                break;
        case 3:
                cout<<"请输入新的员工性别:";
                cin>>x;
                p->data.sex = x;
                break;
        case 4:
                cout<<"请输入新的员工出生日期:";
                cin>>x;
                p->data.birth = x;
                break;
        case 5:
                cout<<"请输入新的员工学历:";
                cin>>x;
                p->data.edu = x;
                break;
        case 6:
                cout<<"请输入新的员工职务:";
                cin>>x;
                p->data.position = x;
                break;
        case 7:
                cout<<"请输入新的员工电话:";
                cin>>x;
                p->data.tel = x;
                break;
        case 8:
                cout<<"请输入新的员工住址:";
                cin>>x;
                p->data.address = x;
                break;
        case 0: 
                cout<<"返回主菜单！"<<endl;
                menu(L);
                break;
     }
     cout<<"修改信息已保存！"<<endl;
     string k;
     cout << "是否继续修改？(1:继续;其它退回主菜单)";
     cin >> k;
     if(k == "1")
         ModifyElem(L);
     else
        menu(L); 
}

void add(LinkList &L)//插入
{
    LinkList p = new LNode;
    p = L->next; //初始化，p指向首元结点
    int num2;
    cout << "请输入你需要插入的员工编号：";
    cin >> num2;
    while (p && (p->data.num != num2))
        // 顺链域向后扫描，直到p为空或p所指的结点的数据域等于num2
        p = p->next;
     if(p == NULL)
    {   
        LinkList s = new LNode;
        s->data.num = num2;
        cout<<"姓名:";cin>>s->data.name;
        cout<<"性别:";cin>>s->data.sex;
        cout<<"出生日期:";cin>>s->data.birth;
        cout<<"学历:";cin>>s->data.edu;
        cout<<"职务:";cin>>s->data.position;
        cout<<"电话:";cin>>s->data.tel;
        cout<<"住址:";cin>>s->data.address;
        s->next = L->next;
        L->next = s;
        cout<<"员工信息存入，系统将返回主菜单"<<endl;
        L->length++;
        menu(L);
    }
    else
    {
        cout<<"此员工编号已存在！"<<endl;
        cout << "继续插入请按1" ;
        string x;
        cin >> x;
        if(x == "1")
        {
            add(L);
        }
        else menu(L);
    }
}
void ListDelete(LinkList &L)
{
    LinkList p = new LNode;
    p = L->next; //初始化，p指向首元结点
    LinkList q = new LNode;
    q = L;
    int num2;
    cout << "请输入你需要删除的员工编号：";
    cin >> num2;
    while (p && (p->data.num != num2))
     { // 顺链域向后扫描，直到p为空或p所指的结点的数据域等于num2
        p = p->next;
        q = q->next;
     }
     if(p == NULL)
     {
        cout<<"此员工编号不存在，系统将返回菜单！"<<endl;
        menu(L);
     }
     else
     {
         q->next = p->next;
         delete p;
         L->length--;
         cout<<"员工信息删除完成，系统将返回主菜单"<<endl;
         menu(L);
     }
}
void Sort(LinkList L)//排序
{
    LinkList i,j,k;
    LinkList p ;
    p = L->next;
    LinkList q ;
    q = p->next;
    LinkList t = new LNode;

   
    
    for(i = p; i != NULL; i++,i = i->next)
    {   
        k = i;
        for(j = i->next; j != NULL; j++,j = j->next)
            if(j->data.num < k->data.num) k = j;
        if( k != i)
        {
            t->data.num = p->data.num;
            t->data.name = p->data.name;
            t->data.sex = p->data.sex;
            t->data.birth = p->data.birth;
            t->data.edu = p->data.edu;
            t->data.position = p->data.position;
            t->data.tel = p->data.tel;
            t->data.address = p->data.address;
            p->data.num = q->data.num;
            p->data.name = q->data.name;
            p->data.sex = q->data.sex;
            p->data.birth = q->data.birth;
            p->data.edu = q->data.edu;
            p->data.position = q->data.position;
            p->data.tel = q->data.tel;
            p->data.address = q->data.address;
            q->data.num = t->data.num;
            q->data.name = t->data.name;
            q->data.sex = t->data.sex;
            q->data.birth = t->data.birth;
            q->data.edu = t->data.edu;
            q->data.position = t->data.position;
            q->data.tel = t->data.tel;
            q->data.address = t->data.address;
        }
    }
    cout << "按编号排序：" << endl;
    int a;
    for(a = 0,p = L->next; a < L->length; a++,p = p->next)
    {
        cout<<"***********************************************"<<endl;
        cout<<" 编号:"<<p->data.num<<endl;
        cout<<" 姓名:"<<p->data.name<<endl;
        cout<<" 性别:"<<p->data.sex<<endl;
        cout<<" 生日:"<<p->data.birth<<endl;
        cout<<" 学历:"<<p->data.edu<<endl;
        cout<<" 职务:"<<p->data.position<<endl;
        cout<<" 电话:"<<p->data.tel<<endl;
        cout<<" 住址:"<<p->data.address<<endl;
        cout<<"***********************************************"<<endl;
    }
    cout<<"系统返回主菜单："<<endl;
    menu(L);
}
void show(LinkList L)
{
    LinkList p = new LNode;
    int i;
    for(i = 0,p = L->next; i < L->length; i++,p = p->next)
    {
        cout<<"***********************************************"<<endl;
        cout<<" 编号:"<<p->data.num<<endl;
        cout<<" 姓名:"<<p->data.name<<endl;
        cout<<" 性别:"<<p->data.sex<<endl;
        cout<<" 生日:"<<p->data.birth<<endl;
        cout<<" 学历:"<<p->data.edu<<endl;
        cout<<" 职务:"<<p->data.position<<endl;
        cout<<" 电话:"<<p->data.tel<<endl;
        cout<<" 住址:"<<p->data.address<<endl;
        cout<<"***********************************************"<<endl;
    }
    cout<<"系统返回主菜单："<<endl;
    menu(L);
}
void save(LinkList L)
{   
    LinkList p = new LNode;
    ofstream fout;
    fout.open("/Users/Leo/GitHub/Sophomore-summer-vacation/staff.txt",ios::out);
    cout<<"文件正在保存......请稍候！！"<<endl;
    cout<<"数据保存成功！！！"<<endl;
    fout<<"已保存员工信息如下："<<endl;
    int i;
    for(i = 0,p = L->next; i < L->length; i++,p = p->next)
    {
        fout<<"***********************************************"<<endl;
        fout<<" 编号:"<<p->data.num<<endl;
        fout<<" 姓名:"<<p->data.name<<endl;
        fout<<" 性别:"<<p->data.sex<<endl;
        fout<<" 生日:"<<p->data.birth<<endl;
        fout<<" 学历:"<<p->data.edu<<endl;
        fout<<" 职务:"<<p->data.position<<endl;
        fout<<" 电话:"<<p->data.tel<<endl;
        fout<<" 住址:"<<p->data.address<<endl;
        fout<<"***********************************************"<<endl;
    }
    fout.close();
    cout<<"系统返回主菜单："<<endl;
    menu(L);

}
int main()
{
    LinkList L;
    InitList(L);
    menu(L);
    return 0;
}