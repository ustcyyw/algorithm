/**
 * @Time : 2023/5/6-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */

/*
 * 注意每一行都以m为周期
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
int T, n, m, sum[N], cnt[N];
deque<int> dq;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    string s;
    for(int t = 1; t <= T; t++) {
        cin >> n >> m;
        cin >> s;
        dq.clear();
        for(int i = 0; i < s.size(); i++) {
            sum[i + 1] = sum[i] + (s[i] - '0');
            if(i < m) cnt[i] = sum[i + 1] > 0;
            else cnt[i] = cnt[i - m] + (sum[i + 1] - sum[i - m + 1] > 0);
            if(s[i] == '1' && dq.size() != m)
                dq.push_front(i);
            if(!dq.empty()) {
                int& temp = dq.back();
                if((i - temp) % m == 0 && i != temp) {
                    dq.pop_back();
                    if(dq.empty() || temp % m != dq.front() % m)
                        dq.push_front(temp);
                }
            }
            cout << dq.size() + cnt[i] << " ";
        }
        cout << "" << endl;
    }
}