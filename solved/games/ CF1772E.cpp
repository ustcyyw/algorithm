/**
 * @Time : 2024/6/11-7:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1772E 博弈 + 贪心
 */
/*
 * 升序和降序与原序列进行对比
 * 二者都需要变化的位置数目为 common
 * 升序、降序独有需要变化的位置数目为 a、b
 * 贪心地想 要让自己先可以完成排序 肯定将机会先用于改变自己独有需要变化的位置
 * 然后才考虑去改变公共位置
 * 但是改变公共位置的时候 如果对方也有机会将自己独有的位置改变完
 * 那谁把最后一个公共位置改变 对方就会获胜
 *
 * 所以单方面获胜的条件就是 将自己独有的和公共的位置都改变完成后
 * 刚好轮到自的轮次 或者对方连自己独有的位置都没改变完
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, common, a, b;

string solve() {
    if(a + common <= b) return "First";
    if(b + common < a) return "Second";
    return "Tie";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        common = 0, a = 0, b = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(num != i && num != n - i + 1) common++;
            if(num != i) a++;
            if(num != n - i + 1) b++;
            a -= common, b -= common;
        }
        cout << solve() << "\n";
    }
};