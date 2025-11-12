/**
 * @Time : 2024/6/11-10:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1772F 构造 思维
 */
/*
 * 四周不同颜色的点 但凡被涂色一次 其周围的四个点将不再可能被涂色
 * 不会使得更多的点能被涂色 只要涂色一个点 剩下可涂色的点一定是减少的
 * 所以按可涂色的点的数目来排序 最大的就是原始图片
 * 然后比较相邻两个图片 找差别就是要进行涂色的地方 每次涂色完成都进行一次复制
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 105, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k, cnt[N];
string temp;
vector<string> photos[N];
vector<int> ids;

int cal(vector<string> &grid) {
    int res = 0;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            char t = grid[i][j];
            if (grid[i - 1][j] != t && grid[i + 1][j] != t &&
                grid[i][j - 1] != t && grid[i][j - 1] != t)
                res++;
        }
    }
    return res;
}
// 不止一次操作
void find(vector<vector<int>>& ope, vector<string> &grid1, vector<string> &grid2) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if(grid1[i][j] != grid2[i][j])
                ope.push_back({1, i + 1, j + 1});
        }
    }
}

void solve() {
    cout << ids.back() << "\n"; // 初始图片编号
    vector<vector<int>> opes;
    for(int i = k - 1; i >= 0; i--) {
        int id = ids[i], pid = ids[i + 1];
        if(cnt[id] != cnt[pid]) { // 不相同的时候需要找到变化的点
            find(opes, photos[pid], photos[id]);
        }
        opes.push_back({2, id});
    }
    cout << opes.size() << "\n";
    for(auto& t : opes) {
        for(int num : t)
            cout << num << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for (int i = 1; i <= k + 1; i++) {
        vector<string> photo;
        for (int j = 0; j < n; j++) {
            cin >> temp;
            photo.push_back(temp);
        }
        photos[i] = photo;
        cnt[i] = cal(photo);
        ids.push_back(i);
    }
    sort(ids.begin(), ids.end(), [&](auto& a, auto& b) -> bool {
        return cnt[a] < cnt[b];
    });
    solve();
};