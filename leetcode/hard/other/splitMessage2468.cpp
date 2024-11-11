/**
 * @Time : 2022/11/21-11:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    const int infos[4] = {9, 180, 2700, 36000};
    vector<string> splitMessage(string message, int limit) {
        if(limit <= 5) return {};
        n = message.size();
        int group = group_num(limit);
        if(group == -1) return {};
        string g_str = to_string(group);
        int base = 3 + g_str.size();
        vector<string> res;
        for(int i = 0, start = 0; i < group; i++){
            string id = to_string(i + 1);
            int len = limit - id.size() - base;
            string content = message.substr(start, min(len, n - start));
            start += len;
            res.push_back(content.append("<").append(id).append( "/" ).append(g_str).append(">"));
        }
        return res;
    }

    // 计算要分成多少组
    int group_num(int limit){
        for(int i = 1; i <= 1e4; i++){
            int total = limit * i, id_len = ids_len(i);
            int base = (3 + to_string(i).size()) * i; // 每一组的固定长度 < /组别数>
            if(total >= id_len + n + base)
                return i;
        }
        return -1;
    }

    // 计算num个分组的情况下，id一共要占据多少长度
    int ids_len(int num){
        int m = to_string(num).size();
        int res = 0;
        for(int i = 0; i < m - 1; i++)
            res += infos[i];
        return res + (num - pow(10, m - 1) + 1) * m;
    }
};

int main(){
    Solution s;
    s.splitMessage("this is really a very awesome message", 9);
    cout << 0 << endl;
}