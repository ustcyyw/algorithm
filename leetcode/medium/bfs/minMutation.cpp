/**
 * @Time : 2022/5/7-10:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<char> base = {'A', 'C', 'G', 'T'};
    int minMutation(string start, string end, vector<string> &bank) {
        if (start == end) return 0;
        unordered_set<string> marked, set;
        marked.insert(start);
        for (string &dna: bank)
            set.insert(dna);
        if (set.find(end) == set.end()) return -1;
        deque<string> queue;
        queue.push_front(start);
        int step = 0;
        while (!queue.empty()) {
            step++;
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                string cur = queue.front();
                queue.pop_front();
                if (check(cur, end, queue, marked, set)) return step;
            }
        }
        return -1;
    }

    bool check(string cur, string end, deque<string> &queue,
               unordered_set<string> &marked, unordered_set<string> &set) {
        int count = 0;
        for (int i = 0; i < cur.size(); i++) {
            char temp = cur[i];
            for(char &c : base){
                if(c == temp) continue;
                cur[i] = c;
                string next = cur;
                if(marked.find(next) == marked.end() && set.find(next) != set.end()){
                    marked.insert(next);
                    queue.push_back(next);
                }
            }
            cur[i] = temp;
            if (cur[i] != end[i]) count++;
        }
        return count == 1;
    }
};

int main() {
    vector<string> bank = {"AACCGGTA","AACCGCTA","AAACGGTA"};
    Solution s;
    s.minMutation("AACCGGTT", "AAACGGTA", bank);
}