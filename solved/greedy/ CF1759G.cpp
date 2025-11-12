/**
 * @Time : 2024/8/19-11:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1759G 贪心
 */
 /*
  * 倒序考虑 给出的b数组中没有出现的数都是待填数
  * 对于b中最后一个数 要选一个比他小的数配对 那肯定是放在其左边字典序更小
  * 并且比他小的所有待填数 应该选择最大的 这样将更小的数留着前面的位置放 一定能得到字典序更小
  * 以此类推
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
int T, n, b[N], marked[N];

bool solve() {
    set<int> set;
    for(int i = 1; i <= n; i++) {
        if(marked[i] > 1) return false; // 又一个数出现了两次
        if(!marked[i])
            set.insert(i);
    }
    for(int i = n; i >= 2; i -= 2) {
        auto it = set.lower_bound(b[i]);
        if(it == set.begin()) return false; // 没有比当前考虑的这个数更小的数
        b[i - 1] = *(--it);
        set.erase(b[i - 1]);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(marked, marked + n + 1, 0);
        for(int i = 2; i <= n; i += 2) {
            cin >> b[i];
            marked[b[i]]++;
        }
        if(!solve()) cout << "-1\n";
        else {
            for(int i = 1; i <= n; i++)
                cout << b[i] << " ";
            cout << "\n";
        }
    }
};