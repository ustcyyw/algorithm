/**
 * @Time : 2023/4/13-1:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int aux[] = {1,1,2,6,24,120,720};
class Solution {
public:
    int n, total;
    vector<int> suf;
    double getProbability(vector<int>& balls) {
        n = balls.size(), total = accumulate(balls.begin(), balls.end(), 0);
        suf = vector(n, 0);
        suf[n - 1] = balls[n - 1];
        for(int i = n - 2; i >= 0; i--)
            suf[i] = suf[i + 1] + balls[i];
        long double cnt = mul(balls);
        vector<int> pick(n, 0);
        return backTrack(balls, pick, 0, 0) / cnt;
    }

    long double mul(vector<int>& arr){
        long double ans = 1.0;
        for(int i = 0, j = 1; i < arr.size(); i++){
            for(int k = 0; k < arr[i]; k++, j++)
                ans *= j;
            ans = ans / aux[arr[i]];
        }
        return ans;
    }

    long double backTrack(vector<int>& balls, vector<int>& pick, int sum, int cur){
        if(n == cur) {
            if(sum == total / 2 && check(balls, pick)) {
                vector<int> other(n, 0);
                for (int i = 0; i < n; i++)
                    other[i] = balls[i] - pick[i];
                return mul(pick) * mul(other);
            }
            return 0;
        }
        if(sum + suf[cur] < total / 2) return 0;
        long double res = 0;
        for(int i = 0; i <= balls[cur]; i++){
            if(sum + i > total / 2) break;
            pick[cur] = i;
            res += backTrack(balls, pick, sum + i, cur + 1);
        }
        return res;
    }

    bool check(vector<int>& balls, vector<int>& pick){
        int cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < n; i++){
            if(pick[i]) cnt1++;
            if(balls[i] - pick[i]) cnt2++;
        }
        return cnt1 == cnt2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}