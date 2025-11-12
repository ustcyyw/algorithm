/**
 * @Time : 2023/5/18-4:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 为了避免棍子碰撞 下面一点的棍子需要先移动，于是就有了先后次序 拓扑
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 5e3 + 5;
int n, degree[N], pos[N][4];
vector<vector<int>> graph;

vector<int> topol_sort() {
    vector<int> ans;
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        ans.push_back(v);
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return ans;
}
void parse_line(int x1, int y1, int x2, int y2, double& k, double& b) {
    k = (y2 - y1) * 1.0 / (x2 - x1);
    b = y1 - k * x1;
}
// 返回相对靠下的棍子
int check_down(int i, int j) {
    int* p1 = pos[i]; int* p2 = pos[j];
    int x1 = p1[0], y1 = p1[1], x2 = p1[2], y2 = p1[3];
    int a1 = p2[0], b1 = p2[1], a2 = p2[2], b2 = p2[3];
    if(x1 > a2 || x2 < a1) return -1;
    if(x1 == x2 && a1 == a2 && a1 == x1)
        return y1 > b1 ? j : i;
    double k1, c1, k2, c2;
    if(x1 != x2) parse_line(x1, y1, x2, y2, k1, c1);
    if(a1 != a2) parse_line(a1, b1, a2, b2, k2, c2);
    if(x1 == x2) {
        double yt = k2 * x1 + c2;
        return yt > y1 ? i : j;
    }
    if(a1 == a2) {
        double yt = k1 * a1 + c1;
        return yt > b1 ? j : i;
    }
    int x;
    if(x1 >= a1 && x1 <= a2) x = x1;
    if(x2 >= a1 && x2 <= a2) x = x2;
    if(x1 <= a1 && x2 >= a2) x = a1;
    if(x1 >= a1 && x2 <= a2) x = x1;
    double yt1 = k1 * x + c1, yt2 = k2 * x + c2;
    return yt1 > yt2 ? j : i;
}

string arr_to_string(vector<int>& arr) {
    string res;
    for(int i = 0, m = (int)arr.size(); i < arr.size(); i++){
        res += to_string(arr[i]);
        if(i != m - 1) res += " ";
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n;
    for (int i = 1, x1, y1, x2, y2; i <= n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) {
            swap(x1, x2), swap(y1, y2);
        }
        pos[i][0] = x1, pos[i][1] = y1, pos[i][2] = x2, pos[i][3] = y2;
    }
    fill(degree, degree + n + 1, 0);
    graph.assign(n + 1, {});
    for (int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            int v = check_down(i, j);
            if(v == -1) continue;
            int w = v == i ? j : i;
            graph[v].push_back(w), degree[w]++;
        }
    }
    vector<int> order = topol_sort();
    cout << arr_to_string(order) << endl;
}