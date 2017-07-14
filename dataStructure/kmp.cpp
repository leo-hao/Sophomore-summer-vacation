//  Created by Leo on 17/7/12.
//  Copyright © 2017年 Leo. All rights reserved.
//  KMP 

#include<iostream>
#include<string>
using namespace std;

 void GetNextval(string p, int next[])  
{  
    int pLen = p.length();  
    next[0] = -1;  
    int k = -1;  
    int j = 0;  
    while (j < pLen - 1)  
    {  
        //p[k]表示前缀，p[j]表示后缀    
        if (k == -1 || p[j] == p[k])  
        {  
            ++j;  
            ++k;  
            //较之前next数组求法，改动在下面4行  
            if (p[j] != p[k])  
                next[j] = k;   //之前只有这一行  
            else  
                //因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]  
                next[j] = next[k];  
        }  
        else  
        {  
            k = next[k];  
        }  
    }  
}  

int KmpSearch(string s, string p)  
{  
    int i = 0;  
    int j = 0;  
    int sLen = s.length();
    int pLen = p.length();  
    int *next = new int[pLen];
    GetNextval(p, next);
    for(int t = 0; t < pLen; t++)
    {
        cout << next[t] << " ";
    }
    cout << endl;
    while (i < sLen && j < pLen)  
    {  
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++      
        if (j == -1 || s[i] == p[j])  
        {  
            i++;  
            j++;  
        }  
        else  
        {  
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]      
            //next[j]即为j所对应的next值        
            j = next[j];  
        }  
    }  
    delete [] next;
    if (j == pLen)  
        return i - j;  
    else  
        return -1;  
}  

int main()
{   
    string s,p;
    cin >> s >> p;
    int pos;
    pos = KmpSearch(s,p);
    cout << pos << endl;
    
    return 0;
}