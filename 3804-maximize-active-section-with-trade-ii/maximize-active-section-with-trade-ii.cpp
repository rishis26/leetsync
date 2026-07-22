class SparseTable {
public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;
        int LOG = 32 - __builtin_clz(n);
        st.assign(LOG + 1, vector<int>());
        st[0] = nums;
        for (int k = 1; k <= LOG; ++k) {
            int half = 1 << (k - 1);
            int len = 1 << k;
            if (n - len + 1 <= 0) break;
            st[k].resize(n - len + 1);
            for (int j = 0; j + len <= n; ++j)
                st[k][j] = max(st[k - 1][j], st[k - 1][j + half]);
        }
    }
    int query(int l, int r) const {  // max(nums[l..r]), caller ensures l<=r
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
private:
    int n;
    vector<vector<int>> st;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int ones = count(s.begin(), s.end(), '1');

        vector<pair<int,int>> zero_runs;   // {start, length}
        vector<int> zgi(n);                // zero-group index per position
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') zero_runs.back().second++;
                else zero_runs.push_back({i, 1});
            }
            zgi[i] = (int)zero_runs.size() - 1;
        }
        if (zero_runs.empty()) return vector<int>(queries.size(), ones);

        vector<int> merge(zero_runs.size() - 1);
        for (size_t i = 0; i + 1 < zero_runs.size(); ++i)
            merge[i] = zero_runs[i].second + zero_runs[i + 1].second;
        SparseTable st(merge);

        auto partialLeft = [&](int l) {
            if (zgi[l] == -1) return -1;
            auto& [start, len] = zero_runs[zgi[l]];
            return len - (l - start);
        };
        auto partialRight = [&](int r) {
            if (zgi[r] == -1) return -1;
            auto& [start, len] = zero_runs[zgi[r]];
            return r - start + 1;
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            int left = partialLeft(l), right = partialRight(r);
            int startIdx = zgi[l] + 1;
            int endIdx = (s[r] == '1') ? zgi[r] : zgi[r] - 1;

            int best = ones;
            if (s[l] == '0' && s[r] == '0' && zgi[l] + 1 == zgi[r]) {
                best = max(best, ones + left + right);
            } else if (startIdx <= endIdx - 1) {
                best = max(best, ones + st.query(startIdx, endIdx - 1));
            }
            if (s[l] == '0' && startIdx <= endIdx)
                best = max(best, ones + left + zero_runs[startIdx].second);
            if (s[r] == '0' && zgi[l] < zgi[r] - 1)
                best = max(best, ones + right + zero_runs[zgi[r] - 1].second);

            ans.push_back(best);
        }
        return ans;
    }
};