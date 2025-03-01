/**
 * @Time : 2025/2/28-11:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF818C 2000 双指针
 */
 /*
  * 找某个沙发左边有多少个沙发的时候 用其右边的位置和别的沙发的左边位置比
  * 将左边界和右边界坐标放在两个组中 排序后双指针
  * 其它3个维度类似做法即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll T, d, n, m, base[4], cnt[N][4], pos[N][4];
vector<vector<int>> px1, px2, py1, py2;

void init(vector<vector<int>>& p1, vector<vector<int>>& p2, int idx1, int idx2) {
    sort(p1.begin(), p1.end()), sort(p2.begin(), p2.end());
    for(int i = 0, j = 0; i < d; i++) {
        while(j < d && p1[j][0] < p2[i][0]) j++;
        int id = p2[i][1];
        cnt[id][idx1] = j;
        if(pos[id][idx1] != pos[id][idx2]) cnt[id][idx1]--;
    }
    for(int i = d - 1, j = d - 1; i >= 0; i--) {
        while(j >= 0 && p2[j][0] > p1[i][0]) j--;
        int id = p1[i][1];
        cnt[id][idx2] = d - (j + 1);
        if(pos[id][idx1] != pos[id][idx2]) cnt[id][idx2]--;
    }
}

int solve() {
    init(px1, px2, 0, 1);
    init(py1, py2, 2, 3);
    for(int i = 1; i <= d; i++) {
        bool flag = true;
        for(int j = 0; j < 4; j++)
            if(cnt[i][j] != base[j]) flag = false;
        if(flag) return i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> d >> n >> m;
    for(int i = 1, x1, y1, x2, y2; i <= d; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        px1.push_back({x1, i}), px2.push_back({x2, i});
        py1.push_back({y1, i}), py2.push_back({y2, i});
        pos[i][0] = x1, pos[i][1] = x2, pos[i][2] = y1, pos[i][3] = y2;
    }
    cin >> base[0] >> base[1] >> base[2] >> base[3];
    cout << solve() << "\n";
}