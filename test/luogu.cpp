/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m;
vector<int> zero, one, two;
string s;

void fill(int c0) {
    for(int i = 0; i < n; i++) {
        if(s[i] != '.') continue;
        if(c0 < m) s[i] = '0', c0++;
        else s[i] = '1';
    }
}

void fillAt(vector<int>& arr) {
    for(int idx : arr)
        s[idx] = '0';
}

int solve() {
    // 判断z是否可以为0
    if(zero.size() <= m) {
        fillAt(zero), fill(zero.size());
        return 0;
    }
    if(zero.empty()) {
        fill(0);
        return 1;
    }
    if(one.size() + two.size() <= m) {
        fillAt(one),  fillAt(two);
        fill(one.size() + two.size());
        return 2;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        m = n / 2;
        zero = {}; one = {}; two = {}; s.assign(n, '.');
        for(int i = 0, num; i < n; i++) {
            cin >> num;
            if(num % 3 == 0) zero.push_back(i);
            else if(num % 3 == 1) one.push_back(i);
            else two.push_back(i);
        }
        int flag = solve();
        cout << flag << "\n";
        if(flag != -1) cout << s;
    }
};