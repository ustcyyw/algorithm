/**
 * @Time : 2022/9/6-1:18 AM
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
     * 首先考虑两个立方体(a,b,c)和(x,y,z)，后者放在前者之下
     * 我们并不知道假设就是a,b,c和x,y,z对应，z >= c, y >= b, x >= a
     * 由于我们并没有假设a,b,c这三维的大小关系，也没有假设x,y,z这三维的大小关系
     * 因此这一组对应关系，已经可以包括6*6中立方体的旋转摆放方式
     *
     * 想要堆的更高，就把最大的边都立起来当作高，如何保证可以堆叠在一起的立方体
     * 将其双双将最大边当作高，仍然能立起来
     *
     * 接下来就任意举36种中的1种堆叠方式
     * 比如 c <= a <= b, x <= y <= z
     * 要将最大边都作为高，那就是 z和b 去比较
     * z >= y, y >= b，因此 z >= b，高这个维度满足要求
     * 还剩下 c，a，x，y
     * x >= a, a >= c, 也就是说x和a，c去对应都可以
     * y >= x,那y和a，c也都可以对应
     * 那就让x和c对应，y和a对应。这样就使得最短，中等，最长的三边分别对应
     *
     * 再举一个堆叠方式，如 b <= a <= c, z <= x <= y
     * 要将最大边都作为高，那就是 y和c 去比较
     * y >= z, z >= c，因此 y >= c，高这个维度满足要求
     * 还剩下 a,b,x,z
     * z >= c >= a >= b, z和a，b对应都可以
     * x >= z，同样x和a，b对应都可以
     * 让z和b对应，x和a对应。这样就使得最短，中等，最长的三边分别对应
     *
     * 于是发现通过不等式的传递性可以证明，
     * 方块1在方块2之上，那么方块1和2都将最长边作为高，这两个方块还是能保持堆叠，并且最短，中等，最长的三边分别对应
     *
     * 如果有一个堆叠方式中一共使用了x个立方体
     * 堆叠的方式从下到上是 (a1,b1,c1),(a2,b2,c2),...,(ax,bx,cx)
     * (a1,b1,c1)和(a2,b2,c2)，可以将最长边作为高，继续堆叠，且最短，中等，最长的三边分别对应
     * 由于(a2,b2,c2)变了，(a3,b3,c3)相应的也将最长边作为高，然后变换长和宽，依旧能堆叠
     * 以此类推，整个堆叠方式变换之后，每个立方体最长边作为高
     * 仍然保持堆叠，且最短，中等，最长的三边分别对应，高度增加或者至少不变
     *
     * 于是任意堆叠方式，最后都是每个立方体最长边作为高，
     * 最短，中等的边作为宽和长。所以我们先将每个立方体通过选择调整三边，让最短，中等，最长的三边分别为宽长高
     * 最小的立方体放上面，等价于将大的长方体放置在小的长方体下面
     * 这个过程就是线性dp，只要保证考虑某一个长方体的放置情况时，能叠在其上面的长方体已经被考虑过即可
     * （大佬的讲法 保证枚举关系的拓扑性即可）
     *
     * 执行用时：8 ms, 在所有 C++ 提交中击败了92.47%的用户
     * 内存消耗：8.9 MB, 在所有 C++ 提交中击败了29.03%的用户
     */
    int maxHeight(vector<vector<int>> &cuboids) {
        for(auto& cuboid : cuboids)
            sort(cuboid.begin(), cuboid.end());
        sort(cuboids.begin(), cuboids.end());
        int n = cuboids.size();
        vector<int> dp(n, 0);
        dp[0] = cuboids[0][2];
        int res = dp[0];
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++)
                if(cuboids[i][1] >= cuboids[j][1] && cuboids[i][2] >= cuboids[j][2])
                    dp[i] = max(dp[i], dp[j]);
            dp[i] += cuboids[i][2];
            res = max(res, dp[i]);
        }
        return res;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}