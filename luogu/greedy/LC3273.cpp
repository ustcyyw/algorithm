/**
 * @Time : 2025/1/9-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3273 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    /*
     * 现有一个消灭敌人的顺序 现在考虑第i个敌人和j=i+1个敌人的位置是否应该换
     * 交换i和j不影响[0,i-1]、[j+1,n-1]上的伤害
     * 先消灭i 这两个敌人的伤害为 ti * di + (ti + tj) * dj
     * 先消灭j 这两个敌人的伤害为 tj * dj + (ti + tj) * di
     * 将i排在前面的条件是
     * ti * di + (ti + tj) * dj - tj * dj - (ti + tj) * di < 0
     * ti * dj - tj * di < 0
     */
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size();
        vector<vector<int>> infos;
        for(int i = 0; i < n; i++) {
            int h = health[i], d = damage[i];
            int time = h % power == 0 ? h / power : h / power + 1;
            infos.push_back({d, time});
        }
        sort(infos.begin(), infos.end(), [](auto& a, auto& b) -> bool {
            return a[1] * b[0] - b[1] * a[0] < 0;
        });
        ll sumT = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            sumT += infos[i][1];
            ans += sumT * infos[i][0];
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}