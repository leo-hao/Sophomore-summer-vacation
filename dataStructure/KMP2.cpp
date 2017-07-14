//  Created by Leo on 17/7/14.
//  Copyright © 2017年 Leo. All rights reserved.
//  KMP 
#include<iostream>
#include<string>
using namespace std;

void get_nextval(string T,int nextval[])
{
   
    int i = 1;
    nextval[1] = 0;
    int j = 0;
    while(i < T.length())
    {
        if(j == 0 || T[i-1] == T[j-1])
        {
            i++;j++;
            if(T[i-1] != T[j-1]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }
        else j = nextval[j];
    }
    cout << "nextval[j]:";
    for(int t = 1; t <= T.length(); t++)
    {
        cout << nextval[t] << " ";
    }
    cout << endl;

}

int kmp(string S, string T, int nextval[])
{   
    int i = 1;
    int j = 1;
    get_nextval(T,nextval);
    while(i <= S.length() && j <= T.length())
    {
        if(j == 0|| S[i-1] == T[j-1])
        {
            i++;
            j++;
        }
        else j = nextval[j];
    }
    if(j > T.length())
    return i - T.length();
    else return 0;
}

int main()
{
    string s;string t;
    cin >> s >> t;
    int n;
    n = t.length();
    int *nextval =  new int [n+1];
    int pos;
    pos = kmp(s,t,nextval);
    cout << "从主字符串第"<< pos << "字符开始开始匹配" << "到主字符串的第" << n+pos<< "个字符结束匹配" << endl;
    delete [] nextval;
    return 0;
}