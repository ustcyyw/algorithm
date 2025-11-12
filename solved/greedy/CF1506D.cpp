/**
 * @Time : 2024/11/25-10:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1506D 贪心 结论 1400
 */
 /*
  * 这种不同类东西的配对问题 就是一个结论性质
  * 看最多的那类 如果他没有绝对多（一类就超过其它所有类）
  * 那么总有办法通过复杂的配对 使得所有东西都匹配上（当然总数是奇数的情况剩一个）
  * 否则就是其它所有类都拿去和最多的匹配，最终剩下一些最多的那类物品
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        map<int, int> map;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            map[num]++;
        }
        vector<int> nums;
        for(auto& p : map)
            nums.push_back(p.second);
        sort(nums.begin(), nums.end());
        if(nums.back() >= n - nums.back())
            cout << nums.back() - (n - nums.back()) << "\n";
        else cout << n % 2 << "\n";
    };
};