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
const int N = 2e5 + 5, full = (1ll << 31) - 1;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        multiset<int> set;
        int cnt = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(set.count(full ^ num)) {
                set.erase(set.find(full ^ num));
                cnt++;
            }
            else set.insert(num);
        }
        cout << cnt + set.size() << "\n";
    }
};