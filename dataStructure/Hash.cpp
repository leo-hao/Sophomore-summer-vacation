//  Created by Leo on 7/20/2017
//  Copyright © 2017年 Leo. All rights reserved.
//  hash
#include<iostram>
using namespace std;
#define m 20
typedef struct{
    int key;
    string name;
}HashTable;

int SearchHash(HashTable HT, int k)
{
    int h0,i;
    h0 = k % 19;
    if(HT[h0].key == 0) return -1;
    else if (HT[h0].key == k) return h0;
    else
    {   
        int hi;
        for(i = 0; i < m; i++)
        {
            hi = (h0+i)%m;
            if(HT[hi].key == 0) return -1;
            else if(HT[hi].key == k) return hi;
        }
        return -1;
    }
}