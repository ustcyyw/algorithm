/**
 * @Time : 2024/5/20-9:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1234B2 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
ll T, n, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    deque<int> deque;
    set<int> set;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(set.count(num)) continue;
        deque.push_front(num);
        set.insert(num);
        if(deque.size() > k) {
            set.erase(set.find(deque.back()));
            deque.pop_back();
        }
    }
    cout << deque.size() << "\n";
    for(int num : deque)
        cout << num << " ";
};