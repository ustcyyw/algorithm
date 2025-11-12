/**
 * @Time : 2024/1/24-11:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 按题意模拟即可
 */
#include<bits/stdc++.h>
using namespace std;
const int T = 3e7 + 5;
int k, n1, n2, n3, t1, t2, t3;
// 有等待的衣服 并且机器上限未达到 将该衣服加入机器 并且记录时间戳
void add(int time, int& wait, int limit, deque<int>& dq) {
    while(wait > 0 && dq.size() < limit) {
        dq.push_back(time);
        wait--;
    }
}
// 有执行时间达到要求的衣服 将其从机器中拿出 并让下一阶段的等待数量+1
void end(int time, int& nextWait, int dur, deque<int>& dq) {
    while(!dq.empty() && time - dq.front() + 1 == dur) {
        dq.pop_front();
        nextWait++;
    }
}

void solve() {
    // wait表示等待执行该步骤的衣服
    int time = 0, cnt = 0, wait0 = k, wait1 = 0, wait2 = 0;
    deque<int> wash, dry, iron;
    while(cnt < k) { // 先将当前机器中执行完成的移除 然后再补新的进来
        end(time, wait1, t1, wash);
        add(time + 1, wait0, n1, wash); // 当前时间完成 那么添加时间记为time + 1
        end(time, wait2, t2, dry);
        add(time + 1, wait1, n2, dry);
        end(time, cnt, t3, iron);
        add(time + 1, wait2, n3, iron);
        time++;
    }
    cout << time - 1 << endl;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> k >> n1 >> n2 >> n3 >> t1 >> t2 >> t3;
    solve();
}