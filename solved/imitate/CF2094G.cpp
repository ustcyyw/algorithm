/**
 * @Time : 2025/4/16-10:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2094G 1752 模拟 数据结构 双端队列
 */
/*
 * type3:

(a1 + 2a2 + 3a3) + 4a4
(3a1 + 2a2 + a3) + (a1 + a2 + a3) + a4

type2:
翻转 a1,a2,a3 变为 a3,a2,a1
交换指针即可

type1 位移
a1,a2,a3 -> a3,a1,a2
(a1 + 2a2 + 3a3) + (a1 + a2 + a3) - 3a3
逆向 a2 + 2a1 + 3a3
3a1 + 2a2 + a3 - (a1 + a2 + a3) + 3a3
2a1 + a2 + 3a3
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, M = 30;
ll T, q, sum, sumR, base, flag;
deque<int> dq;

void type1() {
    int last = flag ? dq.back() : dq.front();
    sum = sum + base - (ll)last * dq.size();
    sumR = sumR - base + (ll)last * dq.size();
    if(flag) {
        dq.pop_back(), dq.push_front(last);
    } else {
        dq.pop_front(), dq.push_back(last);
    }
}

void type2() {
    flag = !flag;
    swap(sum, sumR);
}

void type3(ll x) {
    base += x;
    if(flag) dq.push_back(x);
    else dq.push_front(x);
    sum += x * dq.size(), sumR += base;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> q;
        dq.clear(), sum = sumR = base = 0, flag = 1;
        for(int i = 1, t, x; i <= q; i++) {
            cin >> t;
            if(t == 3) {
                cin >> x;
                type3(x);
            } else if(t == 2) type2();
            else type1();
            cout << sum << "\n";
        }
    }
}