/**
 * @Time : 2024/12/29-4:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2020C 位运算 逐位考虑
 */
/*
  * 从高位开始考虑

d是1
b和c都是1 那么a的这一位应该取0 把c的这一位抹除
b和c都是0 那么a的这一位取1 将b这一位变成1
b是1 c是0 那么a这一位取什么都行
b是0 c是1 那么a这一位取0 两个数都会被变0 是否可以让后面某一位上b是0 c是1
         然后通过相减少让这一位b退位而从0变1 但关键a没法让b是0的同时c还保持1
         a取1 让b也变成1 相减这一位还是0
         所以不可行

d是0
b和c都是1  取a是1
b和c都是0  取a是0
b是1 c是0  直接这一位调整不行 是否可以让后面某一位上b是0 c是1 通过退位让这一位变0
          但关键a没法让b是0的同时c还保持1 所以是不行的
b是0 c是1  取a是1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, a, b, c, d;

ll solve() {
    for(int i = 61; i >= 0; i--) {
        ll t = 1ll << i;
        if(d & t) {
            if((b & t) == 0 && (c & t) == 0)
                a |= t;
            if((b & t) == 0 && (c & t))
                return -1;
        } else {
            if((b & t) && (c & t))
                a |= t;
            if((b & t) == 0 && (c & t))
                a |= t;
            if((b & t) && (c & t) == 0)
                return -1;
        }
    }
    return a;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        a = 0;
        cin >> b >> c >> d;
        cout << solve() << "\n";
    }
};