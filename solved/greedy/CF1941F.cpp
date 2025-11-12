/**
 * @Time : 2024/4/2-5:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 首先找到原本距离最远的两个 不处理的话 他们就是最大值 所以必须处理他们
  * 处理完后再看谁最大，当然有可能原本第二大的间距现在成最大的了
  * 那显然应该找到这两个元素中点 尽可能插入到中点处 (a[i] + a[j]) / 2
  * 将d和f排序 双指针
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, k, a[N], d[N], f[N];

void solve() {
    sort(d, d + m + 1), sort(f, f + k + 1);
    // 找到最大间距和次大间距
    int idx1 = -1, v1 = -1, idx2 = -1, v2 = -1;
    for(int i = 1; i < n; i++) {
        int diff = a[i + 1] - a[i];
        if(diff >= v1) {
            v2 = v1, idx2 = idx1;
            v1 = diff, idx1 = i;
        } else if(diff > v2) v2 = diff, idx2 = i;
    }
    int left = a[idx1], right = a[idx1 + 1]; // 最大间距的左右两个点
    int ans = v1, target = (right - left) / 2 + left, sd = a[idx2 + 1] - a[idx2];
    function<int(int, int)> cal = [&](int p1, int p2) -> int {
        int pos = d[p1] + f[p2];
        return max({pos - left, right - pos, sd});
    };
    for(int i = 1, j = k; i <= m; i++) {
        while(j >= 1 && f[j] + d[i] >= target) j--;
        if(j + 1 <= k) ans = min(ans, cal(i, j + 1));
        if(j >= 1) ans = min(ans, cal(i, j));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= m; i++)
            cin >> d[i];
        for(int i = 1; i <= k; i++)
            cin >> f[i];
        solve();
    }
};