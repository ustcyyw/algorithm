/**
 * @Time : 2024/7/17-1:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1690G 主要是复杂度分析
 */
 /*
  * 原本火车速度值 可以分为连续的线段 每个线段速度一致
  * 单次修改
  * 1. 如果修改后的最高速度 >= 当前运行速度 无影响
  * 2. 如果修改后的最高速度 < 当前运行速度 会将对应的线段分成左边部分 右边部分
  * 左边部分运行速度保持 而右边部分速度变为修改后的速度 并且会将更右边速度大的线段合并
  * 因此单次查询最多添加一条新线段 因此即便所有线段都被添加和删除一次 均摊下来也是o(m)的
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, nums[N];
map<int, int> mp;

void init() {
    mp = {};
    for(int i = 1, j; i <= n; ) {
        j = i + 1;
        while(j <= n && nums[j] >= nums[i]) j++;
        mp[i] = j - 1;
        i = j;
    }
}

void update(int idx, int d) {
    auto it = (--mp.upper_bound(idx));
    int lo = it->first, hi = it->second;
    if(nums[idx] - d >= nums[lo]) {
        nums[idx] -= d;
        return;
    } else {
        nums[idx] -= d;
        if(idx - 1 >= lo) mp[lo] = idx - 1;
        while(mp.count(hi + 1) && nums[hi + 1] >= nums[idx]) {
            int temp = mp[hi + 1];
            mp.erase(hi + 1);
            hi = temp;
        }
        mp[idx] = hi;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        init();
        for(int q = 1, idx, d; q <= m; q++) {
            cin >> idx >> d;
            update(idx, d);
            cout << mp.size() << " ";
        }
        cout << "\n";
    }
};