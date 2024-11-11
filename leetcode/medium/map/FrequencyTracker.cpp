/**
 * @Time : 2023/5/7-11:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 2;
class FrequencyTracker {
public:
    vector<int> cnt, freq;
    FrequencyTracker() {
        cnt = vector(N, 0), freq = vector(N, 0);
    }

    void add(int number) {
        freq[cnt[number]]--;
        cnt[number]++;
        freq[cnt[number]]++;
    }

    void deleteOne(int number) {
        if(cnt[number] == 0) return;
        freq[cnt[number]]--;
        cnt[number]--;
        freq[cnt[number]]++;
    }

    bool hasFrequency(int frequency) {
        return freq[frequency] > 0;
    }
};


int main(){

    cout << 0 << endl;
}