/**
 * @Time : 2023/12/4-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 方法一 逆向思维
 * 记第i组数是pair[i]
 * 能覆盖住所有pair的两个数 其中之一是pair[0][0]或者pair[0][1]
 * 就假定出现在pair[0]中的数是x， x = pair[0][0] or pair[0][1]
 * 查看x能覆盖住哪些数对，如果有不能覆盖的 找到任意一组没被覆盖的 那么y就应该在该组中产生
 * 同样y可能是该组的第一个数或者第二个数 查看y能否将剩余的数组进行覆盖
 * 于是最多遍历四次 如果没有发现能覆盖所有的x和y，就返回no
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, m, a[N], b[N];

bool checkY(vector<bool>& marked, int y) {
    for(int i = 1; i <= m; i++) {
        if(!marked[i] && y != a[i] && y != b[i])
            return false;
    }
    return true;
}

bool check(int x) {
    vector<bool> marked(n + 1, false);
    int y1 = -1, y2 = -1;
    for(int i = 1; i <= m; i++) {
        if(a[i] == x || b[i] == x) marked[i] = true;
        else y1 = a[i], y2 = b[i];
    }
    if(y1 == -1) return true;
    return checkY(marked, y1) || checkY(marked, y2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
    }
    if(check(a[1]) || check(b[1])) cout << "YES" << endl;
    else cout << "NO" << endl;
}

/*
 * 方法二
 * 从两个数是否有交集（出现在同一pair中）来进行分组 有交集的情况下
 * A + B - A交B = m 则说明可以覆盖
 *
 * 没有交集的情况下 A + B = m 则说明可以覆盖
 *
 * 可以用 对于每一pair，使用 key = a * N + b 存放在map中进行计数
 * map[key] > 0 说明有交集
 */
//int n, m, cnt[N];
//unordered_map<long long, int> mp;
//string solve1() {
//    // 有交集的两个数的判断
//    for(auto& pair : mp) {
//        long long key = pair.first;
//        int a = key / N, b = key % N;
//        if(cnt[a] + cnt[b] - mp[key] == m)
//            return "YES";
//    }
//    // 无交集的两个数的判断
//    vector<vector<int>> infos(m + 1, vector(0, 0));
//    for(int i = 1; i <= n; i++) {
//        if(cnt[i] == m) return "YES"; // 一个数出现了m次 一定是在m个组中出现 因为每个组中的2个数字不同
//        if(cnt[i] != 0) infos[cnt[i]].push_back(i);
//    }
//    for(int i = 1; i <= m / 2; i++) {
//        for(int a : infos[i]) {
//            // 无交集的两个数 覆盖的组数最多是m，要找可能完全覆盖的，其覆盖数就是m
//            for(int b : infos[m - i]) {
//                if(a > b) swap(a, b);
//                long long k1 = (long long)a * N + b;
//                if(a != b && !mp.count(k1)) return "YES";
//            }
//        }
//    }
//    return "NO";
//}
//
//int main1() {
//    memset(cnt, 0, sizeof(cnt));
//    mp.clear();
//    cin >> n >> m;
//    for(int i = 1, a, b; i <= m; i++) {
//        cin >> a >> b;
//        if(a > b) swap(a, b);
//        cnt[a]++, cnt[b]++;
//        long long key = (long long)a * N + b;
//        mp[key]++;
//    }
//    cout << solve1() << endl;
//}