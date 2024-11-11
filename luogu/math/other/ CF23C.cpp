/**
 * @Time : 2024/2/10-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 苹果的重量用a表示，橘子用o表示
 * 将箱子按苹果的重量排序后，将前2n-2个箱子分为两个部分，奇数项和偶数项
 * 再分别都添加上a[2n-1]得到两个序列
 * 1. a1, a3, a5, .. a[2n-3], a[2n-1]
 * 2. a2, a4, a6, .. a[2n-2], a[2n-1]
 * 上述两个部分均有 (2n - 2) / 2 + 1 = n个箱子。是题目要求拿的箱子数量
 *
 * a3 >= a2, a5 >= a4,... a[2n - 1] >= a[2n - 2]
 * --> a3 + a5 + ... + a[2n-3] + a[2n-1] >= a2 + a4 + a6 + .. a[2n-2]
 * 不等式左边加上非负数a1
 * --> a1 + a3 + a5 + ... + a[2n-3] + a[2n-1] >= a2 + a4 + a6 + .. a[2n-2]
 * 且 a2 + a4 + a6 + .. a[2n-2] = aSum - (a1 + a3 + a5 + ... + a[2n-3] + a[2n-1])
 * --> 2 * (a1 + a3 + a5 + ... + a[2n-3] + a[2n-1]) >= aSum
 * --> a1 + a3 + a5 + ... + a[2n-3] + a[2n-1] >= aSum / 2
 * 也就是说分配方案1 满足了苹果的重量 >= aSum / 2
 *
 * 对于方案2：a2 >= a1, a4 >= a3, ... a[2n - 2] >= a[2n - 3]，且与方案1相比最后一项都是a[2n-1]
 * 说明方案2苹果重量 >= 方案1 >= aSum / 2
 *
 * 因此 两种方案 苹果重量都满足要求 下面讨论橘子重量
 * 方案1橘子重量为 ora1 + o[2n-1], 其中ora1 = o1 + o3 + o5 + ... + o[2n-3]
 * 方案2橘子重量为 ora2 + o[2n-1], 其中ora2 = o2 + o4 + o6 + ... + o[2n-2]
 * 两个方案中必定有一个方案的橘子重量 >= oSum / 2。
 * 可以使用反证法 如果两个方案的重量都 < oSum / 2
 * 那么 ora1 + ora2 + 2 * o[2n-1] < oSum
 * 代入展开后有
 * (o1 + o2 + o3 + o4 + ... + o[2n-3] + o[2n-2] + o[2n-1]) + o[2n-1] < oSum
 * oSum + o[2n-1] < oSum --> o[2n-1] < 0
 * 但是箱子中橘子的重量非负 矛盾了 因此结论 两个方案中必定有一个方案的橘子重量 >= oSum / 2。 成立
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll T, n, oSum;
vector<vector<int>> box;

void solve() {
    cout << "YES" << "\n";
    sort(box.begin(), box.end());
    // 方案1橘子重量的计算
    ll os1 = 0;
    vector<int> ans;
    for(int i = 0; i < 2 * n - 1; i += 2)
        os1 += box[i][1], ans.push_back(box[i][2]);
    if(os1 * 2 < oSum) { // 方案2才是合理方案
        ans = {box[2 * n - 2][2]};
        for(int i = 1; i < 2 * n - 1; i += 2)
            ans.push_back(box[i][2]);
    }
    sort(ans.begin(), ans.end());
    for(int i : ans)
        cout << i << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        oSum = 0, box = {};
        for(int i = 1, a, o; i <= 2 * n - 1; i++) {
            cin >> a >> o;
            box.push_back({a, o, i}), oSum += o;
        }
        solve();
    }
};