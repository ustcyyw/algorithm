/**
 * @Time : 2024/4/22-10:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 必须先走 max(x, y)小的坐标 同一个等级的点 分布在同一条横线/竖线上 这两条线共同构成折线
  * 假设当前等级为k 折线的两个端点分别是 左上端点(r, y) 右下端点(x, r)
  * 要走完某一个等级的点 有4种方案 假设上一个等级的终点为pre
  * 1. 从pre到某个中间点mid然后先到端点a 再从a到端点b
  * 2. 从pre到端点a 再从a到端点b
  * 3和4 类似1和2 只不过先到b再到a
  * 先分析1和2
  * pre到端点a的距离 <= 从pre走到mid的距离 + mid到a的距离
  * 如果a和mid相对pre的位置在两侧 那么是上面不等式取小于号，如果同侧 取等号
  * 因此前半段的距离 是线路2更好
  * 后一半都是从a到b 距离都是 r - x + r - y
  * 3和4类似 因此更好不论上一等级的终点是哪个点 就当前等级来说都是先到一个端点 然后到另外一个端点
  * 每一层都如此 那么就没必要走到端点后再移动到别的点 直接考虑从上一层端点选择先到下一层哪个端点
  *
  * dp[i][0]:第i层以左上端点为终点的最短路程
  * dp[i][1]:第i层以右下端点为终点的最短路程
  * 这两个状态都可以由上一层的两个端点转移而来
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n, dp[N][2];
map<int, vector<vector<int>>> nodes; // 存储每一层的点

int dis(vector<int>& p1, vector<int>& p2) {
    int x1 = p1[0], y1 = p1[1], x2 = p2[0], y2 = p2[1];
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> y >> x;
        int k = max(x, y);
        nodes[k].push_back({x, y});
    }
    int m = nodes.size(), i = 1;
    vector<int> pl = {0, 0}, pr = {0, 0};
    for(auto& p : nodes) {
        vector<vector<int>>& arr = p.second;
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> int {
            if(a[1] != b[1]) return a[1] < b[1];
            return a[0] > b[0];
        });
        vector<int> left = arr[0], right = arr.back();
        int d = dis(left, right);
        // 从pre左上到cur左上 然后走到cur右下；pre右下到cur左上 然后走到cur右下
        dp[i][1] = min(dp[i - 1][0] + dis(pl, left),
                       dp[i - 1][1] + dis(pr, left)) + d;
        // pre左上走到cur右下 然后走到cur左上； ...
        dp[i][0] = min(dp[i - 1][0] + dis(pl, right),
                       dp[i - 1][1] + dis(pr, right)) + d;
        swap(pl, left), swap(pr, right);
        i++;
    }
    cout << min(dp[m][0], dp[m][1]);
};