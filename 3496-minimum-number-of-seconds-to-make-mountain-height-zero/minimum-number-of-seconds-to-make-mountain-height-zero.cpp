class Solution {
public:
    long long mountainHeight;

    bool canFinish(long long time, vector<int>& workerTimes) {
        long long removed = 0;

        for (long long t : workerTimes) {
            // Find maximum x such that:
            // t * x * (x + 1) / 2 <= time

            long long x =
                (sqrt(1.0 + 8.0 * time / t) - 1) / 2;

            removed += x;

            if (removed >= mountainHeight)
                return true;
        }

        return false;
    }

    long long minNumberOfSeconds(int mountainHeight,
                                 vector<int>& workerTimes) {

        this->mountainHeight = mountainHeight;

        long long low = 0;

        long long fastest =
            *min_element(workerTimes.begin(), workerTimes.end());

        long long high =
            fastest * mountainHeight * (mountainHeight + 1LL) / 2;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (canFinish(mid, workerTimes))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};