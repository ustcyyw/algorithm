/**
 * @Time : 2024/7/13-6:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1579F 思维 广度优先
 */
 /*
  * 一开始是0的位置 移动后会让另外一个地方变为0 而且原本是0的地方保持不变
  * 每一次操作 只有新出现的0有意义 因为旧的0还是变到同一个位置
  * 所以就是0不断将新位置变为0的传递过程 可以用bfs来计算最迟0访问完所有位置
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, d, cnt, marked[N];
queue<int> q;

void add(int x) {
    q.push(x), cnt++, marked[x] = 1;
}

int solve() {
    if(cnt == n) return 0;
    int step = 1;
    while(!q.empty()) {
        int sz = q.size();
        while(sz-- > 0) {
            int i = q.front(), j = (i + d) % n; q.pop();
            if(!marked[j]) {
                add(j);
                if(cnt == n) return step;
            }
        }
        step++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> d;
        cnt = 0, q = {};
        fill(marked, marked + n + 1, 0);
        for(int i = 0, num; i < n; i++) {
            cin >> num;
            if(num == 0) add(i);
        }
        cout << solve() << "\n";
    }
};