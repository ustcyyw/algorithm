/**
 * @Time : 2024/3/14-8:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 没有指定输入多少个数字的标准输入
    void std_in() {
        int num;
        while(cin >> num) {

        }
    }
};

/*
 * 快读模版
 * @return
 */
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
// n = read(), arr[i] = read()

int main(){
    Solution s;
    
    cout << 0 << endl;
}