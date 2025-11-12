/**
 * @Time : 2024/4/16-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 前面要进行字母切换x-1次 然后把剩余的一种字母全消耗完 再消耗另外一种字母这里贡献最后一次切换
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5, M = 1e5 + 5;
int a, b, x;

void fill(string& s, int cnt, char c) {
    for(int i = 0; i < cnt; i++)
        s.push_back(c);
}

void solve() {
    char c1 = '0', c2 = '1';
    if(a < b) swap(a, b), swap(c1, c2);
    string res;
    a--, res.push_back(c1);
    bool flag = false; // flag为1表示要添加第一个字母
    for(int i = 0; i < x - 1; i++) {
        if(flag) a--, res.push_back(c1);
        else b--, res.push_back(c2);
        flag = !flag;
    }
    // 该添第一个字母 说明上一个字母是第二个字母
    if(flag) fill(res, b, c2), fill(res, a, c1); // 最后结尾的是第二个字母
    else fill(res, a, c1), fill(res, b, c2);
    cout << res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b >> x;
    solve();
};