/**
 * @Time : 2024/6/7-11:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1714E 数学 找规律
 */
 /*
  * 发现除了能被5整除的数要么不变 要么只能+5
  * 其余的数都有周期性 +2 +4 +8 +6 ... 一个周期为20
  * 因此只要找到一个周期内会出现哪些数即可 并且只用看最后2位数 并且超过20都减去20
  * 这样子两个数变换后的集合有交集 就说明可以通过操作让两个数相等。
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, a[N], flag;
set<int> st;

bool check5() {
    for(int i = 1; i <= n; i++) {
        int num = a[i];
        if(num % 5 != 0) return false;
        if(num % 10 != 0) a[i] += 5;
    }
    for(int i = 2; i <= n; i++) {
        if(a[i] != a[1]) return false;
    }
    return true;
}

set<int> cal(int num) {
    set<int> set;
    set.insert((num > 20 ? num - 20 : num));
    while(true) {
        num += num % 10;
        int t = num % 100;
        if(t >= 20) t -= 20;
        if(set.count(t)) break;
        set.insert(t);
    }
    return set;
}

bool check(set<int>& s1, set<int>& s2) {
    for(int num : s2) {
        if(s1.count(num)) return true;
    }
    return false;
}

bool solve() {
    if(st.size() == 1) return true;
    if(flag) return check5();
    set<int> base = cal(*st.begin());
    for(int num : st) {
        set<int> temp = cal(num);
        if(!check(base, temp)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        st.clear(), flag = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            a[i] = num, st.insert(num);
            if(num % 5 == 0) flag = 1;
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};