/**
 * @Time : 2023/12/14-8:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 两堆球的合并 并且还有问球现在处于哪一堆 看起来像并查集
 * 但是存在一个新增加球到特定盒子的操作
 * 如果新增球i到盒子x时，之前盒子x中的球已经被移动到其它盒子中了。
 * 直接让球i指向x 不合理 因为这样就使得i在跟着之前的操作一起移动到别的盒子中了
 *
 * 因此在移动盒子y到盒子x 后，应该让y对应到新到并查集结点上
 * box[i]: 表示盒子对应的并查集结点编号
 * ans[i]: 表示编号为i的并查集结点对应的真实盒子编号
 * ball[i]: 表示编号为i的球 放在哪个并查集结点上
 *
 * 动态增加结点的并查集
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;

int n, Q, type, x, y, t, id[2 * N], box[N], ans[2 * N], ball[2 * N];

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(id, 0, sizeof(id));
    cin >> n >> Q;
    t = n + 1;
    for(int i = 1; i <= n; i++)
        id[i] = box[i] = ans[i] = ball[i] = i; // 初始时刻 盒子与并查集id都是相同的
    while(Q-- > 0) {
        cin >> type >> x;
        if(type == 1) {
            cin >> y;
            // 盒子y对应的并查集结点编号 设置为盒子x对应的并查集结点编号
            // 并查集是的合并操作，可以表示盒子y中球全放盒子x中
            id[find(box[y])] = find(box[x]);
            t++;  // 盒子y现在是空的 为其新建一个并查集结点
            id[t] = t, box[y] = t, ans[t] = y;
        } else if(type == 2)
            ball[++n] = box[x];
        else {
            // ball[x] : 球x对应的并查集结点编号
            // find(ball[x]) 找到其最终属于哪个分量就是合并到的最终的结点
            // ans[find(ball[x])] 由最终结点编号得到真实盒子的编号
            cout << ans[find(ball[x])] << endl;
        }
    }
};