/**
 * @Time : 2025/2/1-11:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF31D 2000 模拟
 */
 /*
  * 题目的关键在于有n次切割，保证只出现n+1个部分 并且每个部分内部都没有切割痕迹
  * 也就是题目中所说的 每次切割刚好让其中一块变成2块更小的
  * 那么每次切割肯定是刚好从一个边切到了对边 但是让巧克力一分为二的切割不知道先是哪个
  * 因此要暴力枚举 一轮一轮尝试
  * 记录现有的矩形 枚举他们是否能被当前的切割刚好一分为二
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 300 + 5, M = 2 * N;
int w, h, n, curId = 0;

unordered_map<int, vector<int>> mp, line;

bool split(int w1, int h1, int w2, int h2) {
    int remove = -1;
    vector<int> a1, a2;
    for(auto& [id, rac] : mp) {
        if(h1 == h2) { // 同一高度 横着切
            if(rac[0] == w1 && rac[2] == w2 && h1 > rac[1] && h1 < rac[3]) {
                remove = id;
                a1 = {w1, rac[1], w2, h1};
                a2 = {w1, h1, w2, rac[3]};
            }
        } else { // 同一宽度 竖着切
            if(w1 > rac[0] && w1 < rac[2] && h1 == rac[1] && h2 == rac[3]) {
                remove = id;
                a1 = {rac[0], h1, w1, h2};
                a2 = {w1, h1, rac[2], h2};
            }
        }
    }
    if(remove != -1) {
        mp[++curId] = a1, mp[++curId] = a2;
        mp.erase(remove);
    }
    return remove != -1;
}

void solve() {
    while(!line.empty()) {
        for(auto& [i, rac] : line) {
            bool flag = split(rac[0], rac[1], rac[2], rac[3]);
            if(flag) {
                line.erase(i);
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> w >> h >> n;
    mp[curId] = {0, 0, w, h};
    for(int i = 1, w1, h1, w2, h2; i <= n; i++) {
        cin >> w1 >> h1 >> w2 >> h2;
        line[i] = {w1, h1, w2, h2};
    }
    solve();
    vector<int> ss;
    for(auto& [id, rac] : mp) {
        int dx = rac[2] - rac[0], dy = rac[3] - rac[1];
        ss.push_back(dx * dy);
    }
    sort(ss.begin(), ss.end());
    for(int s : ss)
        cout << s << " ";
};