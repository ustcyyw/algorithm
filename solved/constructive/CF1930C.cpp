/**
 * @Time : 2024/5/29-9:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1930C 构造 贪心
 */
/*
  * 先将右边的删掉 不会影响左边 这样获得的数最大
  * 但是不允许出现重复数字 在有重复数字时 删掉最左边的一个即可避免重复
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
ll T, n;
map<int, int> mp;

void solve() {
    while(n-- > 0) {
        int last = mp.rbegin()->first;
        cout << last << " ";
        mp[last]--;
        if(mp[last] > 0)
            mp[last - 1] += mp[last];
        mp.erase(mp.find(last));
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        mp.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mp[num + i]++;
        }
        solve();
    }
};