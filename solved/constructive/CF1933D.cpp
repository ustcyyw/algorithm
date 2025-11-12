/**
 * @Time : 2024/11/17-11:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1933D 构造 1200
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N], val, cnt;

bool solve() {
    if(cnt == 1) return true; // 最小值只有一个 将元素直接排序即可
    // 查看是否有一个数能不被val整除 将这个数对val取mod得到唯一的新的最小数 将这个最小数放最前面即可
    for(int i = 1; i <= n; i++) {
        if(nums[i] % val != 0) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n;
        val = INT_MAX;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(nums[i] < val) val = nums[i], cnt = 0;
            if(nums[i] == val) cnt++;
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};