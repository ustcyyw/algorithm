/**
 * @Time : 2025/3/17-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF845D 1800 模拟 栈
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 63;
ll T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        int cnt = 0, preS = 0;
        stack<int> speed, surpass;
        for(int i = 1, type, x; i <= n; i++) {
            cin >> type;
            if(type == 1 || type == 3)
                cin >> x;
            if(type == 1) { // 改变车速
                while(!speed.empty() && speed.top() < x)
                    speed.pop(), cnt++;
                preS = x;
            } else if(type == 3) { // 速度限制
                if(x < preS) cnt++;
                else speed.push(x);
            } else if(type == 5) { // 限制取消
                speed.push(INT_MAX);
            } else if(type == 2) { // 超车
                while(!surpass.empty() && surpass.top() == 0)
                    surpass.pop(), cnt++;
            } else if(type == 4) { // 允许超车
                surpass.push(1);
            } else surpass.push(0);
        }
        cout << cnt;
    }
}