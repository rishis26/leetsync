class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string first = "";
        char mid = '\0';

        for (int i = 0; i < 26; i++) {
            first.append(freq[i] / 2, char('a' + i));
            if (freq[i] % 2)
                mid = char('a' + i);
        }

        string second = first;
        reverse(second.begin(), second.end());

        if (mid != '\0')
            return first + mid + second;

        return first + second;
    }
};