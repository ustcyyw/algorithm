/**
 * @Time : 2024/4/23-11:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 枚举所有可能的第一场竞赛的问题数范围[1,n]
 * 当前竞赛题目数要求为val 每次都取题目数量 >= val且数量最少的主题
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n;
map<int, int> cnt;

int cal(multiset<int>& set, int val) {
    int ans = 0;
    multiset<int> removed;
    while(true) {
        auto it = set.lower_bound(val);
        if(it == set.end()) break;
        removed.insert(*it), set.erase(it);
        ans += val;
        val *= 2;
    }
    for(int num : removed)
        set.insert(num);
    return ans;
}

void solve() {
    multiset<int> set;
    for(auto& p : cnt) {
        set.insert(p.second);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) // 枚举第一场比赛的问题数
        ans = max(ans, cal(set, i));
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[num]++;
    }
    solve();
};