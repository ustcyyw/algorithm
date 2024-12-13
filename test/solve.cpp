#include<bits/stdc++.h>
/*
 * 每次最多有2个元素的频次变了 如果窗口左边出去的和右边进来的元素相同 和保持不变
 *
 * 要用一个指针标识出第k大的键 key
 * 移除一个值 先找到对应的键kr 通过key定位上一个键pre
 * 1. 如果 kr < key 那么删除 修改 再放回 不影响和
 * 2. kr == key，改动kr后 查看kr与pre的关系
 *      2.1 如果kr还是大于pre 那么key变为改动后对kr
 *      2.2 如果kr < pre 那么key变为pre
 * 3. kr > key，改动kr后 查看kr与key的关系
 *      3.1 kr > key, 保持key不变
 *      3.2 kr < key, 的看kr和pre哪个大 大的那个就成为了key
 *
 * 添加一个值 先找到对应的键ka 通过key定位下一个键suf
 * 1. 如果ka > key 那么删除 修改 再放回 和变化
 * 2. 如果ka == key，改动ka后 查看ka与suf的关系
 * 3. 如果ka < key，改动ka后 查看ka与key的关系
 */
using namespace std;
typedef long long ll;
const ll N = 1e10;

class Solution {
public:
    ll key = -1;
    int x, k;
    set<ll> set;
    unordered_map<int, int> map;
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        this->x = x, this->k = k;
        ll sum = init(nums);
        vector<ll> ans = {sum};
        for(int lo = 0, hi = k; hi < nums.size(); ) {
            remove(sum, nums[lo++]);
            add(sum, nums[hi++]);
            ans.push_back(sum);
        }
        return ans;
    }

    void remove(ll& sum, int num) {
        ll kr = map[num] * N + num, nk = (map[num] - 1) * N + num;
        map[num]--;
        set.erase(kr);
        if(map[num] > 0) set.insert(nk);
        if(kr < key) return;
        ll pre = *(--set.lower_bound(key));
        if(!set.count(key)) { // 是key刚好等于kr的情况 现在要找新的边界了
            if(pre == nk) sum -= num; // 新的边界依旧是这个数的统计结果
            else sum = sum - get_val(kr) + get_val(pre);
            key = pre;
        } else {
            if(nk > key) sum -= num;
            else {
                sum = sum - get_val(kr) + get_val(pre);
                key = pre;
            }
        }
    }

    void add(ll& sum, int num) {
        ll ka = map[num] * N + num, nk = (map[num] + 1) * N + num;
        map[num]++;
        set.erase(ka), set.insert(nk);
        if(ka > key) {
            sum += num;
            if(map[num] == 1 && set.size() - 2 > x)
                key = *set.upper_bound(key);
            return;
        }
        ll suf = *set.upper_bound(key);
        if(!set.count(key)) { // key刚好等于ka的情况 需要找新的边界
            sum += num, key = suf;
        } else { // ka < key的情况
            if(nk > key) {
                sum = sum - get_val(key) + get_val(nk);
                key = suf;
            }
        }
    }

    ll get_val(ll kk) {
        return kk / N * (kk % N);
    }

    ll init(vector<int>& nums) {
        for(int i = 0; i < k; i++)
            map[nums[i]]++;
        for(auto& [t, cnt] : map)
            set.insert(cnt * N + t);
        for(int i = k; i < nums.size(); i++)
            set.insert(nums[k]);
        ll sum = 0, cnt = 0;
        for(auto it = set.rbegin(); it != set.rend() && cnt < x; cnt++, it++) {
            ll v = *it, num = v % N, c = v / N;
            sum += c * num;
            if(cnt + 1 == x) key = v;
        }
        set.insert(0), set.insert((1e5 + 1) * N + 2e9); // 哨兵
        if(key == -1) key = 0;
        return sum;
    }
};

int main() {
    vector<int> arr1 = {283643418,539892409,942041613,103866146,539892409,539892409,885393673,453859905,942041613,103866146};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    s.findXSum(arr1, 5, 5);
}
