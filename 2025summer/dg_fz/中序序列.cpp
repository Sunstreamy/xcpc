#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int 二叉树节点数量
     * @param pre intvector 前序序列
     * @param suf intvector 后序序列
     * @return intvector
     */
    
    vector<int>ans;
    map<int,int>idx;
    
    // 递归辅助函数
    // pre_l, pre_r: 当前子树在前序序列中的索引范围 [inclusive, inclusive]
    // suf_l, suf_r: 当前子树在后序序列中的索引范围 [inclusive, inclusive]
    void build(const vector<int>& pre,int pre_l,int pre_r,int suf_l,int suf_r){
        if(pre_l>pre_r) return;
        int root=pre[pre_l];
        if(pre_l==pre_r){
            ans.push_back(root); // 将叶子节点加入答案
             return;              // 必须返回！
        }
         // 关键：左子树的根是前序序列的第二个元素
        int root_val_lsub = pre[pre_l + 1];
        
        // 在后序序列中找到左子树的根，以确定左子树的大小
        int root_idx_lsub_suf = idx[root_val_lsub];
        int sz_lsub = root_idx_lsub_suf - suf_l + 1;
        
        // 1. 递归构建左子树的中序遍历
        // 左子树在前序中的范围: [pre_l + 1, pre_l + left_subtree_size]
        // 左子树在后序中的范围: [suf_l, left_root_idx_in_suf]
        build(pre, pre_l + 1, pre_l + sz_lsub, suf_l, root_idx_lsub_suf);
        
        // 2. 将根节点加入结果 (中序：左-根-右)
        ans.push_back(root);

        // 3. 递归构建右子树的中序遍历
        // 右子树在前序中的范围: [pre_l + left_subtree_size + 1, pre_r]
        // 右子树在后序中的范围: [left_root_idx_in_suf + 1, suf_r - 1] (suf_r是根)
        build(pre, pre_l + sz_lsub + 1, pre_r, root_idx_lsub_suf + 1, suf_r - 1);
        
    }
    
    vector<int> solve(int n, vector<int>& pre, vector<int>& suf) {
        // write code here
       if(n==0)return{};
        
        for(int i=0;i<n;i++){
            idx[suf[i]]=i;
        }
        build(pre, 0, n - 1, 0, n - 1);
        
        return ans;
    }
};

int main() {
    // 创建 Solution 类的一个实例
    Solution solution_instance;

    // 准备测试数据 (来自题目示例)
    vector<int> pre = {3, 2, 1, 4, 5};
    vector<int> suf = {1, 5, 4, 2, 3};
    int n = 5;

    // 调用 solve 方法
    vector<int> result = solution_instance.solve(n, pre, suf);

    // 打印结果以验证
    cout << "The inorder traversal is: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : ",");
    }
    cout << "]" << endl;

    // 期望输出: [1,2,5,4,3]
    
    return 0;
}