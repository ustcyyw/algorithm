/**
 * @Time : 2023/2/22-6:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i][s] 截止地i个人，拥有技能状态是s的最小人数
     */
    int m, n;
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        m = req_skills.size(), n = people.size();
        int u = (1 << m) - 1;
        vector<int> skills = format(req_skills, people);
        for(int i = 0; i < n; i++)
            if(skills[i] == u) return {i};
        vector<vector<int>> dp(n + 1, vector(u + 1, INT_MAX));
        // 记录状态的转移路径
        vector<vector<int>> p_path(n + 1, vector(u + 1, -1)), s_path(n + 1, vector(u + 1, -1));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            int sk = skills[i - 1];
            dp[i][0] = 0, dp[i][sk] = 1; // 特殊状态
            p_path[i][sk] = i, s_path[i][sk] = 0;
            for(int s = u; s; s = (s - 1) & u){ // 当前人不选的情况，继承前置状态
                if(s == sk || dp[i - 1][s] == INT_MAX) continue;
                dp[i][s] = dp[i - 1][s];
                p_path[i][s] = i - 1; s_path[i][s] = s;
            }
            for(int s = u; s; s = (s - 1) & u){ // 选择当前人，枚举截止上一个人的团队状态
                if(dp[i - 1][s] == INT_MAX) continue;
                int cur = s | sk;
                if(dp[i][cur] > dp[i - 1][s] + 1){
                    dp[i][cur] = dp[i - 1][s] + 1;
                    p_path[i][cur] = i - 1; s_path[i][cur] = s;
                }
            }
        }
        vector<int> res;
        int p = n, s = u;
        while (true){
            int pt = p_path[p][s], st = s_path[p][s];
            if(pt == -1) break;
            // 前后两个状态选的人数不一样，才说明在选人队伍中加入了人
            if(dp[pt][st] != dp[p][s]) res.push_back(p - 1);
            p = pt, s = st;
        }
        return res;
    }

    vector<int> format(vector<string>& req_skills, vector<vector<string>>& people){
        unordered_map<string, int> map;
        for(int i = 0; i < m; i++)
            map[req_skills[i]] = i;
        vector<int> res(n, 0);
        for(int i = 0; i < n; i++){
            for(string& skill : people[i])
                res[i] |= 1 << map[skill];
        }
        return res;
    }
};

int main(){
    Solution s;
//    vector<string> skills = {"algorithms","math","java","reactjs","csharp","aws"};
//    vector<vector<string>> p = {{"algorithms","math","java"},{"algorithms","math","reactjs"},{"java","csharp","aws"}
//    ,{"reactjs","csharp"},{"csharp","math"},{"aws","java"}};
    vector<string> skills = {"uhppib","mgdipkgt","vaostwmycy","bjwxnfbbubpnd"};
    vector<vector<string>> p = {{"vaostwmycy"},{"mgdipkgt"},{"bjwxnfbbubpnd"},{},{"uhppib"}};
    s.smallestSufficientTeam(skills, p);
    cout << 0 << endl;
}