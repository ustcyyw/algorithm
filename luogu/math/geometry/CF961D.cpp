/**
 * @Time : 2025/3/25-11:24 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF961D 2000 数学 计算几何
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
int T = 1e9 + 10, n;
set<ll> st;
vector<vector<int>> pos;

string get_key(int dx, int dy) {
    int g = gcd(dx, dy);
    dy /= g, dx /= g;
    if(dx * dy >= 0) dx = abs(dx), dy = abs(dy);
    else dx = -abs(dx), dy = abs(dy);
    return to_string(dx) + "-" + to_string(dy);
}

bool check(vector<int>& arr, int flag) {
    if(arr.size() <= 2) return true;
    set<string> st;
    int x1 = pos[arr[0]][0], y1 = pos[arr[0]][1];
    for(int i = 1; i < arr.size(); i++) {
        int x2 = pos[arr[i]][0], y2 = pos[arr[i]][1];
        int dy = y1 - y2, dx = x1 - x2;
        string key;
        if(dx == 0) key = "inf";
        else key = get_key(dx, dy);
        st.insert(key);
    }
    if(st.size() == 1) return true;
    if(st.size() > 2) return false;
    return flag == 0;
}

bool solve(int idx) {
    if(pos.size() <= 2) return true;
    map<string, vector<int>> mp;
    int x1 = pos[idx][0], y1 = pos[idx][1];
    for(int i = 0; i < pos.size(); i++) {
        if(i == idx) continue;
        int x2 = pos[i][0], y2 = pos[i][1];
        int dy = y1 - y2, dx = x1 - x2;
        string key;
        if(dx == 0) key = "inf";
        else key = get_key(dx, dy);
        mp[key].push_back(i);
    }
    if(mp.size() <= 2) return true; // 只有一条直线 或者 刚好pos[0]就是两条直线的交点
    int cnt3 = 0; // cnt3计算有多少条直线至少有3个点
    vector<int> arr;
    for(auto& p : mp) {
        int cnt = p.second.size();
        if(cnt == 1) arr.push_back(p.second[0]);
        else cnt3++;
    }
    if(cnt3 > 2 || (cnt3 == 2 && !arr.empty())) return false;
    return check(arr, cnt3);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        ll key = (ll)x * T + y;
        if(!st.count(key)) {
            pos.push_back({x, y});
            st.insert(key);
        }
    }
    cout << (solve(0) || solve(1) || solve(2) ? "YES" : "NO");
}