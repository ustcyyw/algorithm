/**
 * @Time : 2024/3/16-3:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 但凡在数组中能找到另外一个数 相加为2的幂 那么这两个数都不应该删除
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int T = 2e5, N = 2e5 + 5;
int n, m, nums[N];
vector<ll> p;

int init = []() -> int {
    ll temp = 1;
    for(int i = 0; i <= 32; i++) {
        temp *= 2;
        p.push_back(temp);
    }
    return 0;
}();

bool check(multiset<ll>& set, int num) {
    set.erase(set.find(num));
    bool flag = false;
    for(ll pow : p) {
        if(set.count(pow - num)) {
            flag = true;
            break;
        }
    }
    set.insert(num);
    return flag;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    int cnt = 0;
    multiset<ll> set;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        set.insert(nums[i]);
    }
    for (int i = 1; i <= n; i++) {
        if(check(set, nums[i]))
            cnt++;
    }
    cout << (n - cnt) << "\n";
};