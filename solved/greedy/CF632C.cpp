/**
 * @Time : 2024/4/9-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 5e4 + 5;
int n;
string words[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> words[i];
    sort(words + 1, words + n + 1, [](auto& a, auto& b) -> bool {
        string t1 = a + b, t2 = b + a;
        return t1 < t2;
    });
    string ans;
    for(int i = 1; i <= n; i++)
        ans.append(words[i]);
    cout << ans;
};