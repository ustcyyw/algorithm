/**
 * @Time : 2024/5/11-8:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1157F 贪心 + 双指针
 */
 /*
  * 枚举最大值 判断最小值的可取情况
  * 1.相邻两个数不能相差 > 1
  * 2.除了最大数以外不能有只出现一次的数（除非是构造只有两个元素的序列）
  * 最优构造方案是 将最大数放在中间 左边和右边依次递减
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, cnt[N];

void solve() {
    vector<vector<int>> arr;
    for(int i = 1; i < N; i++)
        if(cnt[i] > 0) arr.push_back({i, cnt[i]});
    int m = arr.size(), ans = 0, i = -1, j = -1;
    for(int lo = 0, hi = 0, sum = 0; hi < m; hi++) {
        sum += arr[hi][1];
        if((hi > 0 && arr[hi - 1][0] + 1 != arr[hi][0]))
            sum = arr[hi][1], lo = hi;
        if(ans < sum)
            ans = sum, i = lo, j = hi;
        if(arr[hi][1] == 1)
            sum = arr[hi][1], lo = hi;
    }
    cout << ans << "\n";
    deque<int> aux;
    for(int k = j; k >= i; k--) {
        int c = arr[k][1], num = arr[k][0];
        while(c > 0) {
            if(c-- > 0) aux.push_back(num);
            if(c-- > 0) aux.push_front(num);
        }
    }
    for(int num : aux)
        cout << num << " ";
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