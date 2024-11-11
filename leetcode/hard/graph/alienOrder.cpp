/**
 * @Time : 2022/6/1-4:15 PM
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
     * 是否成环的检测与拓扑排序要分开
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：9.4 MB, 在所有 C++ 提交中击败了22.36%的用户
     */
    bool hasCycle = false;
    vector<unordered_set<int>> graph = vector(26, unordered_set<int>());
    string alienOrder(vector<string>& words) {
        unordered_set<int> chars; // 统计出现了的字母
        for(string& word : words){
            if(chars.size() == 26) break;
            for(char c : word) chars.insert(c - 'a');
        }
        build(words);
        // 检查是否有环存在
        vector<bool> marked = vector(26, false), onStack = vector(26, false);
        for(int c : chars){
            if(hasCycle) return "";
            checkCycle(marked, onStack, c);
        }
        if(hasCycle) return "";
        // 拓扑排序
        vector<int> order;
        marked.assign(26, false);
        for(int c : chars){
            if(!marked[c])
                dfs(order, marked, c);
        }
        string res;
        for(int i = order.size() - 1; i >= 0; i--)
            res.push_back((char)(order[i] + 'a'));
        return res;
    }

    void dfs(vector<int>& order, vector<bool>& marked, int v){
        marked[v] = true;
        for (int w : graph[v]) {
            if (!marked[w])
                dfs(order, marked, w);
        }
        order.push_back(v); // 逆后序
    }

    void checkCycle(vector<bool>& marked, vector<bool>& onStack, int v){
        if(hasCycle) return;
        marked[v] = true, onStack[v] = true;
        for(int w : graph[v]){
            if(!marked[w]) checkCycle(marked, onStack,w);
            else if(onStack[w]){
                hasCycle = true;
                break;
            }
        }
        onStack[v] = false;
    }

    void build(vector<string>& words){
        int n = words.size();
        for(int i = 0; i < n - 1; i++){
            for(int j = i + 1; j < n; j++)
                compare(words[i], words[j]);
        }
    }

    void compare(string word1, string word2){
        int n = min(word1.size(), word2.size());
        for(int i = 0; i < n; i++){
            int c1 = word1[i] - 'a', c2 = word2[i] - 'a';
            if(c1 != c2){
                graph[c1].insert(c2);
                break;
            } else if(i + 1 == n && word1.size() > word2.size())
                hasCycle = true; // 说明排序有错，直接设置flag为顺序不成立的情况
        }
    }
};

int main(){
    Solution s;
    vector<string> words = {"abcc"};
//    vector<string> words = {"dvpzu","bq","lwp","akiljwjdu","vnkauhh","ogjgdsfk","tnkmxnj","uvwa","zfe","dvgghw","yeyruhev","xymbbvo","m","n"};
    cout << s.alienOrder(words) << ends;
}