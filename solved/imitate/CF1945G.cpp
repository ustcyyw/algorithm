/**
 * @Time : 2024/3/20-9:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 按题目要求模拟
 * 一些要注意的点
 * 0. 虽然只有一个排队队列，但是没有吃过的人是按原始顺序排着 和优先级无关
 * 吃过的人要根据优先级插队，两类人排队规则不同，因此用一次排队队列和二次排队队列进行区分
 * 2. 同时存在一次排队队列和二次排队队列时。
 *      1队队首的人及其后面的人 如果存在优先级 >= 2队队首的人优先级
 *      那么2队的人实际上是都排在某个1队的人之后的 此时就让1队的人先吃饭
 *      因此用rk[i]记录原始1队第i个位置后面最大的优先级
 * 3. 吃过一次后的人 按照优先级从大到小排列 并且在优先级一致时 按加入队列的时间升序
 * 所以可用一个优先队列表示二次排队的队列，要记录入队时间和其id，通过id查找优先级
 * 如果优先级和入队时间都相同，就比较入队时的先后顺序（可以用入队时候队列的元素个数替代）
 * 4. 同一秒 先安排人吃饭 再查看有哪些人在这一秒吃完了。吃完了的就放入二次排队的队列
 * 5. 同一秒吃完饭的人 进入二次排队的顺序也有要求 是按照其s的大小从小到达依次进入
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, D, k[N], s[N], marked[N], rk[N];

struct cmp1 {
    bool operator()(pair<int, int> &a, pair<int, int> &b) {
        if (a.first != b.first) return a.first > b.first;
        return s[a.second] > s[b.second];
    }
};

struct cmp2 {
    bool operator()(vector<int> &a, vector<int> &b) {
        int i = a[1], j = b[1];
        if (k[i] != k[j]) return k[i] < k[j]; // 优先级是越高越好
        if(a[0] != b[0]) return a[0] > b[0]; // 时间越早越好
        return a[2] > b[2]; // 入队时的序号 越早越好
    }
};

int solve() {
    rk[n] = k[n];
    for(int i = n - 1; i >= 1; i--)
        rk[i] = max(rk[i + 1], k[i]);
    // 正在吃东西的队列 吃完东西的时间time,id
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp1> eating;
    // 二次排队的队列 进入队列的time, id, order
    priority_queue<vector<int>, vector<vector<int>>, cmp2> queue;
    int cnt = 0; // 标记有多少学生已经吃过东西了
    function<void(int, int)> add = [&](int time, int id) -> void {
        eating.push({time + s[id], id});
        if (!marked[id]) cnt++, marked[id] = 1;
    };
    for (int time = 1, lo = 1; time <= D; time++) {
        if(queue.empty() || (lo <= n && rk[lo] >= k[queue.top()[1]])) {
            add(time, lo++);
        } else if(!queue.empty()) {
            int id = queue.top()[1];
            queue.pop();
            add(time, id);
        }
        if (cnt == n) return time;
        // 查看有没有已经吃完的人
        while (!eating.empty() && eating.top().first <= time) {
            int id = eating.top().second;
            eating.pop();
            queue.push({time, id, (int)queue.size()});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> D;
        memset(marked, 0, sizeof(marked));
        for (int i = 1; i <= n; i++)
            cin >> k[i] >> s[i];
        cout << solve() << "\n";
    }
};