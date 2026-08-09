class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = maximum number of characters from the
        // remaining suffix of word2 that can be matched
        // exactly using word1[i...].
        vector<int> suf(n + 1, 0);

        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            suf[i] = suf[i + 1];

            if (j >= 0 && word1[i] == word2[j]) {
                suf[i]++;
                j--;
            }
        }

        vector<int> ans;

        int j2 = 0;
        bool usedMismatch = false;

        for (int i = 0; i < n && j2 < m; i++) {

            // Exact match -> always prefer it.
            if (word1[i] == word2[j2]) {
                ans.push_back(i);
                j2++;
            }

            // Use our one allowed mismatch.
            else if (!usedMismatch) {

                // After choosing i, the remaining characters
                // must be matched exactly.
                int remaining = m - j2 - 1;

                if (suf[i + 1] >= remaining) {
                    ans.push_back(i);
                    j2++;
                    usedMismatch = true;
                }
            }
        }

        if (j2 != m)
            return {};

        return ans;
    }
};