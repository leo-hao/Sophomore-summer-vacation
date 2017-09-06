//  Created by Leo on 17/7/15.
//  Copyright © 2017年 Leo. All rights reserved.
//  float
#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    float a,b,c;
    cin >> a >> b;
    c = a/b;
    if(abs(c) < 1e-6)
    {
        cout << "=0" << endl;
    }
    else cout << "!=0" << endl;
    return 0;
}