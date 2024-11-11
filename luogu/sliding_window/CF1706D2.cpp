/**
 * @Time : 2024/6/5-10:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 遇到min{最大值 - 最小值} 也就是极差最小 考虑滑动窗口
 * 本题另外一个关键在于 所取数据范围下
 * 根据 "整除分块" 可知 每个数对应的 ai/pi最多有 sqrt(ai)个值
 * 可以将这些值全部预处理出来 在数轴上记录相应的值可以由哪些数取得（记录id的集合）
 * 然后通过滑动窗口来计算 需要保证窗口中出现的id的数量为n
 *
 * 但是由于空间限制 不能记录这么多信息 就只好在滑动的过程中不断清楚缓存
 * 对于左端点 要将接下来可能出现的值 以及对应的id记录下来
 * 对于右端点 要将处于窗口中的值 以及对应的id记录下来
 * 处理完端点后 该端点的信息不再需要 就进行移除
 *
 * pl, pr分别记录左、右端点上对应的pi
 * idL, idR左、右端点上对应的数的id
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, k, cnt[N], pl[N], pr[N], nums[N];
map<int, int> mp;
vector<vector<int>> idL, idR;

// 整除分块 找下一个ai/pi对应的p
int get_p(int id, int* ps) {
    int num = nums[id], p = ps[id];
    return p > num ? num + 1 : num / (num / p) + 1;
}

void solve() {
    int mv = mp.rbegin()->first, lo = mv, hi = mv, s = 0, ans = INT_MAX;
    while (lo >= 0) { // 从右往左滑窗口 相应地取值范围逐渐减小 p在不断增大
        for(int id : idL[lo]) {
            if (++cnt[id] == 1) s++;
            // 编号为id的数 下一个可取的ai/pi是val（对应pi=p）
            int p = get_p(id, pl), val = nums[id] / p;
            // 那么val这个值对应的数编号集合中 应该放入id
            pl[id] = p;
            if(lo != 0 && val >= 0 && p <= k) idL[val].push_back(id);
        }
        vector<int>().swap(idL[lo]); // 及时清理缓存
        while (s == n) {
            ans = min(ans, hi - lo);
            for (int id: idR[hi]) {
                if (--cnt[id] == 0) s--;
                // 编号为id的数 下一个可取的ai/pi是val（对应pi=p）
                int p = get_p(id, pr), val = nums[id] / p;
                // 并且val这个值还在区间[lo,hi]上 还要在这个值对应的数编号集合中放入id
                // 以便窗口右端移动时 将之前计算过的id移除
                pr[id] = p;
                if(hi != 0 && val >= 0 && p <= k) idR[val].push_back(id);
            }
            vector<int>().swap(idR[hi]);// 及时清理缓存
            hi--;
        }
        lo--;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        idL.assign(N, {}), idR.assign(N, {}), mp = {};
        for (int i = 1, num; i <= n; i++) {
            cin >> num;
            if (!mp.count(num)) mp[num] = mp.size();
        }
        n = mp.size();
        for (auto &pair: mp) {
            int num = pair.first, id = pair.second;
            nums[id] = num, cnt[id] = 0;
            pl[id] = pr[id] = 1; // 开始时p都取1 随着p增大 ai/pi减小
            idL[num].push_back(id), idR[num].push_back(id);
        }
        solve();
    }
};