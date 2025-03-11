/**
 * @Time : 2025/3/10-9:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF863C 1800 模拟
 */
 /*
  * 选的点数的情况一共只有9种 按选数规则很快就会出现循环
  * 找到循环的起点，计算一次循环的得分情况
  * 中间部分是多次循环，再计算一头一尾就出答案
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, P = 13331;
ll k, a, b, A[4][4], B[4][4];

void cal(int num1, int num2, int& c1, int& c2) {
    if((num1 == 3 && num2 == 2) || (num1 == 2 && num2 == 1) || (num1 == 1 && num2 == 3))
        c1++;
    if((num1 == 2 && num2 == 3) || (num1 == 1 && num2 == 2) || (num1 == 3 && num2 == 1))
        c2++;
}

vector<ll> solve() {
    // 找循环出现的第一对数
    set<int> set;
    int num1 = a, num2 = b;
    while(true) {
        int key = num1 * 10 + num2;
        if(set.count(key)) break;
        set.insert(key);
        int nxt1 = A[num1][num2], nxt2 = B[num1][num2];
        num1 = nxt1, num2 = nxt2;
    }
    // 计算从起点到循环出现的第一对数之间的比赛
    int ca0 = 0, cb0 = 0, curA = a, curB = b;
    while(k > 0 && (curA != num1 || curB != num2)) {
        cal(curA, curB, ca0, cb0);
        k--;
        int nxt1 = A[curA][curB], nxt2 = B[curA][curB];
        curA = nxt1, curB = nxt2;
    }
    if(k == 0) return {ca0, cb0};
    // 计算一次循环中的比赛的得分及轮数 并且这里已经比了一轮 或者 还不到一轮就结束了
    int ca1 = 0, cb1 = 0, len = 0, f = 0;
    while(k > 0) {
        if(curA == num1 && curB == num2) {
            if(f == 0) f++;
            else break;
        }
        cal(curA, curB, ca1, cb1);
        len++, k--;
        int nxt1 = A[curA][curB], nxt2 = B[curA][curB];
        curA = nxt1, curB = nxt2;
    }
    if(k == 0) return {ca0 + ca1, cb0 + cb1};
    ll cnt = k / len, mod = k % len;
    // 计算多轮后还需要比赛的得分
    int ca2 = 0, cb2 = 0;
    while(mod-- > 0) {
        cal(curA, curB, ca2, cb2);
        int nxt1 = A[curA][curB], nxt2 = B[curA][curB];
        curA = nxt1, curB = nxt2;
    }
    return {ca0 + ca1 * (cnt + 1) + ca2, cb0 + cb1 * (cnt + 1) + cb2};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> k >> a >> b;
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            cin >> A[i][j];
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            cin >> B[i][j];
    vector<ll> ans = solve();
    cout << ans[0] << " " << ans[1];
}