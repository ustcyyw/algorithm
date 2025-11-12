/**
 * @Time : 2024/3/4-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e6 + 5;
int n, cnt[N];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    n = s.size();
    for(int i = 0, j = 0, last = 0; i < n; ) {
        while(i < n && s[i] == 'o') cnt[i++] = last;
        j = i;
        while(j < n && s[j] == 'v') j++;
        if(j != n) {
            last += max(0, j - i - 1);
            cnt[j] = last;
        }
        i = j;
    }
    ll res = 0;
    for(int i = n - 1, j = n - 1, last = 0; i >= 0; ) {
        while(i >= 0 && s[i] == 'o') res += (ll)last * cnt[i--];
        j = i;
        while(j >= 0 && s[j] == 'v') j--;
        if(j != -1) last += max(0, i - j - 1);
        i = j;
    }
    cout << res << "\n";
};