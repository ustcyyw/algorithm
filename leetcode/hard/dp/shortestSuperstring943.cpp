/**
 * @Time : 2023/1/4-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * cache[s][k]: 字符选取状态为s时，以第k个单词结尾的拼接字符串最短长度
     * path则是记录拼接的过程，其值都是 info = s_pre * 100 + k_pre。
     * path[s][k]: 表示转移到(s,k)这个状态的上一个状态对应的状态为info,可以映射为(s_pre, k_pre)
     * lens[i][j]: words[i] + words[j]进行拼接时 中间的公共部分
     */
    int n;
    vector<string> words;
    vector<vector<int>> lens, cache, path;
    string shortestSuperstring(vector<string>& words) {
        n = words.size();
        this->words = words;
        int u = (1 << n) - 1;
        cache = vector(u + 1, vector(n, 0));
        path = vector(u + 1, vector(n, 0));
        // 预处理两个字符串首位可以共享的长度
        lens = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                lens[i][j] = longestCommon(words[i], words[j]);
                lens[j][i] = longestCommon(words[j], words[i]);
            }
        }
        int min_len = INT_MAX, p = 0;
        for(int i = 0; i < n; i++){
            int cur_len = shortestCombine(u, i);
            if(cur_len < min_len){
                min_len = cur_len;
                p = u * 100 + i;
            }
        }
        return superstring(p);
    }
    // 通过最终状态 倒推出转移路径 并同时根据路径拼接字符串 p是最终状态
    string superstring(int p){
        string res = words[p % 100];
        while (true){
            int s = p / 100, k = p % 100;
            p = path[s][k]; // 获取上一个状态
            if(p == 0) break;
            int pre = p % 100;
            // 上一个字符串不取公共部分
            res = words[pre].substr(0, words[pre].size() - lens[pre][k]).append(res);
        }
        return res;
    }

    // 选定字符串的状态为s且以第k个字符为最后一个字符时，最短组合长度
    int shortestCombine(int s, int k){
        if(cache[s][k] != 0) return cache[s][k];
        if(bit_count(s) == 1) return (int)words[k].size();
        int res = INT_MAX, l = (int)words[k].size(), t = 1 << k;
        for(int i = 0; i < n; i++){ // 枚举上一个结尾的字符
            if(i == k) continue; // 上一个结尾的字符不能是其本身
            if(((1 << i) & s) > 0){
                // 拼接出来的字符串长度 = 前面一段长度 + 当前字符长度 - 重叠部分长度
                int cur_len = shortestCombine(s ^ t, i) + l - lens[i][k];
                if(cur_len < res){
                    res = cur_len;
                    path[s][k] = (s ^ t) * 100 + i;
                }
            }
        }
        cache[s][k] = res;
        return res;
    }

    int longestCommon(string& s1, string& s2){
        int n1 = s1.size(), n2 = s2.size(), len = min(n1, n2);
        while (len > 0){
            if(check(s1, n1 - len, s2)) return len;
            len--;
        }
        return 0;
    }

    bool check(string& s1, int lo, string& s2){
        for(int i = lo, j = 0; i < s1.size(); i++, j++)
            if(s1[i] != s2[j]) return false;
        return true;
    }

    int bit_count(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        i = (i + (i >> 4)) & 0x0f0f0f0f;
        i = i + (i >> 8);
        i = i + (i >> 16);
        return i & 0x3f;
    }
};

int main(){
    Solution s;
    vector<string> arr = {"alex","loves","algorithm"};
    s.shortestSuperstring(arr);
    cout << 0 << endl;
}