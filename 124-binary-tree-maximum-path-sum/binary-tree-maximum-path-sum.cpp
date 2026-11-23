/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    int ans = INT_MIN;
    int solve(TreeNode* root) {
        if (!root) return 0;

        int maxL = max(0, solve(root->left));
        int maxR = max(0, solve(root->right));

        // Complete path passing through current node
        ans = max(ans, root->val + maxL + maxR);

        // Return one branch to parent
        return root->val + max(maxL, maxR);
    }

    int maxPathSum(TreeNode* root) {
        solve(root);
        return ans;
    }
};
