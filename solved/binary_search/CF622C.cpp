/**
 * @Time : 2024/3/22-8:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, V = 1e6 + 5, MOD = 1e9 + 7;
int n, m;
vector<int> arrs[V]; // 按元素分组

int find(vector<int>& arr, int l, int r) {
    int lo = lower_bound(arr.begin(), arr.end(), l) - arr.begin();
    if(lo == arr.size() || arr[lo] > l) return l; // 没有查找到等于l的元素
    int hi = lower_bound(arr.begin(), arr.end(), r) - arr.begin();
    if(hi == arr.size() || arr[hi] > r) return r; // 没有查找到等于l的元素
    if(hi - lo == r - l) return -1; // [l,r]上每个元素都是x
    while(lo < hi && l < r) {
        int mid = (lo + hi) >> 1, b = arr[mid];
        if(b - l > mid - lo) r = b, hi = mid; // 左边元素填不满对应的区间 说明左边必然有一个数不是指定值
        else l = b + 1, lo = mid + 1;
    }
    return l;
}

void solve() {
    for(int i = 0, l, r, x; i < m; i++) {
        cin >> l >> r >> x;
        cout << find(arrs[x], l, r) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    memset(arrs, {}, sizeof(arrs));
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        arrs[num].push_back(i);
    }
    solve();
};