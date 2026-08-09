class Solution {
public:
    int dp[101][101];

    int solve(vector<int>& piles, int i, int M, vector<int>& suffix) {
        int n = piles.size();

        if (i >= n)
            return 0;

        if (dp[i][M] != -1)
            return dp[i][M];

        int total = suffix[i];
        int ans = 0;

        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            int nextM = max(M, X);

            int opponent = solve(
                piles,
                i + X,
                nextM,
                suffix
            );

            ans = max(ans, total - opponent);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        memset(dp, -1, sizeof(dp));

        return solve(piles, 0, 1, suffix);
    }
};