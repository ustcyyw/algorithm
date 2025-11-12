/**
 * @Time : 2024/12/7-10:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1352F 1500 构造 模拟
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n1, n2, n3;

string get_str(char c, int n) {
    if(n == 0) return "";
    string res(1, c);
    while(n-- > 0)
        res.push_back(c);
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n1 >> n2 >> n3;
        string t1 = get_str('0', n1), t2 = get_str('1', n3);
        string res = t1 + t2;
        if(t1.size() == 0) n2++;
        if(t2.size() == 0) n2++;
        // 默认是先放0后放1，所以接下来该按0，1的顺序放置
        // 但是如果1序列长度为0，就应该先放1
        int flag = t2.size() == 0 ? 1 : 0;
        for(; n2 > 1; n2--, flag = (flag + 1) % 2) {
            char c = (char)(flag + '0');
            res.push_back(c);
        }
        cout << res << "\n";
    };
};