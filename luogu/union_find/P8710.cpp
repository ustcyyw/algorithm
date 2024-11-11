/**
 * @Time : 2023/5/19-3:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 并查集
 * 方法一：路径压缩 + 启发式合并 + tag懒更新
 */
//#include<bits/stdc++.h>
//
//using namespace std;
//const int N = 1e4 + 5;
//int n, m, nums[N], id[N], tag[N];
//vector<vector<int>> nodes;
//
//int find(int p) {
//    if (id[p] == p) return p;
//    return id[p] = find(id[p]);
//}
//
//void connect(int p, int q) {
//    p = find(p), q = find(q);
//    if (p == q) return;
//    int n1 = nodes[p].size(), n2 = nodes[q].size();
//    if (n1 > n2) {
//        for (int v: nodes[q]) {
//            nodes[p].push_back(v);
//            nums[v] = nums[v] - tag[p] + tag[q];
//        }
//        id[q] = p;
//        nodes[q].clear();
//    } else {
//        for (int v: nodes[p]) {
//            nodes[q].push_back(v);
//            nums[v] = nums[v] - tag[q] + tag[p];
//        }
//        id[p] = q;
//        nodes[p].clear();
//    }
//}
//
//int main() {
//    ios_base::sync_with_stdio(0);
//    cin.tie(0); // 加速cin, cout
//    cin >> n >> m;
//    nodes.assign(n + 1, {});
//    fill(nums, nums + n + 1, 0), fill(tag, tag + n + 1, 0);
//    for (int i = 1; i <= n; i++) {
//        id[i] = i;
//        nodes[i].push_back(i);
//    }
//    for (int i = 1, t, a, b; i <= m; i++) {
//        cin >> t >> a >> b;
//        if (t == 1) connect(a, b);
//        else tag[find(a)] += b;
//    }
//    for (int i = 1; i <= n; i++) {
//        if(!nodes[i].empty() && tag[i] != 0) {
//            for(int v : nodes[i])
//                nums[v] += tag[i];
//        }
//    }
//    for (int i = 1; i <= n - 1; i++)
//        cout << nums[i] << " ";
//    cout << nums[n] << endl;
//}

/*
 * 方法二：
 * 1.并查集不压缩路径而进行按秩序合并，保留路径
 * 2.使用tag懒更新
 * 3.在合并的时候类似于差分的思想
 * 如果a合并到b中
 * 之后发送的信息，他们作为一个整体都保存信息，信息的大小在祖先结点处更新
 * 要计算某个点的信息大小，就向上查找并累加。
 * 但是b中的元素不会增加a的信息，反之也一样
 * 因此要在a的头结点处减掉b中存储的信息(-tag[b])，那么a子树中向上查找到b的头结点时，再加上tag[b]，刚好抵消
 * 而b中的子树，向上查找的过程中不会走a中的路径，不会加上tag[a]
 * 这样就保证了结果的正确性
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4 + 5;
int n, m, id[N], sz[N], tag[N];
vector<vector<int>> nodes;

int find(int p) {
    if (id[p] == p) return p;
    return find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if (p == q) return;
    if(sz[p] > sz[q]) swap(p, q); // 保证p是小的集合
    sz[q] += sz[p];
    tag[p] -= tag[q];
    id[p] = q;
}

int get_data(int p) {
    int ans = tag[p];
    while (p != id[p]) {
        p = id[p];
        ans += tag[p];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    nodes.assign(n + 1, {});
    fill(sz, sz + n + 1, 1), fill(tag, tag + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        id[i] = i;
        nodes[i].push_back(i);
    }
    for (int i = 1, t, a, b; i <= m; i++) {
        cin >> t >> a >> b;
        if (t == 1) connect(a, b);
        else tag[find(a)] += b;
    }
    for (int i = 1; i <= n - 1; i++)
        cout << get_data(i) << " ";
    cout << get_data(n) << endl;
}