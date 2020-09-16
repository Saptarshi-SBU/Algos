/*
 *  Equal SubSet Partitioning :
 *  Dynamic Programming : break down to find subset with given sum
 *  Space Complexity : O(N*SUM)
 *
 *  Ref : https://www.youtube.com/watch?v=s6FhG--P7z0
 *  https://leetcode.com/submissions/detail/396385669/
 */

#include <set>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

static bool find_partition_with_sum_memoization(vector<int>& vec,
        int index,
        unsigned long dest_sum,
        vector<vector<unsigned int>>& dp) {
    if (dest_sum == 0)
        return true;

    if ((index >= vec.size()) || (dp[index][dest_sum] < 0)) 
        return false;

    if (dp[index][dest_sum] == 1) {
        return true;
    } else if ((dest_sum >= vec[index]) &&
            (find_partition_with_sum_memoization(vec, index + 1, dest_sum - vec[index], dp))) {
        dp[index][dest_sum] = 1;
        return true;
    } else {
        dp[index][dest_sum] = -1; 
        return find_partition_with_sum_memoization(vec, index + 1, dest_sum, dp);
    }   
}

static void load_subset_memo(vector<int> &arr,
        vector<vector<unsigned int>> &dp,
        vector<int> &result,
        unsigned long sum) {
    for (size_t pos = 0; pos < dp.size(); pos++) {
        if (dp[pos][sum] <= 0)
            continue;
        if (dp[pos][sum] == 1) {
            result.push_back(pos);
            sum -= arr[pos];
        }

        assert (sum >= 0);
        if (sum == 0)
            break;
    }
}

static bool find_partition_with_sum_dp(vector<int>& vec,
        unsigned long dest_sum,
        vector<vector<unsigned int>>& dp) {
    // dp table : for elements starting from i to j, does there exist
    // any sub-set possible with the expected sum

    // zero sum has an empty subset
    for (size_t i = 0; i < vec.size(); i++) {
        dp[i][0] = 1;
    }

    // for each interval i->j, check what sums are possible
    for (size_t i = 0; i < vec.size(); i++) {
        for (unsigned long s = 0; s <= dest_sum; s++) {
            if (s == vec[i]) {
                dp[i][s] = 1;
                continue;
            }

            if (i > 0) {
                if (s > vec[i])
                    dp[i][s] = dp[i - 1][s - vec[i]];
                dp[i][s] = dp[i][s] || dp[i - 1][s];
            }
        }
    }

#if DEBUG
    for (size_t i = 0; i < vec.size(); i++) {
        for (unsigned long s = 0; s <= dest_sum; s++) {
            std::cout << dp[i][s] << " ";
        }
        std::cout << std::endl;
    }
#endif

    return dp[vec.size() - 1][dest_sum];
} 

static void load_subset_dp(vector<unsigned int> &arr,
        vector<vector<unsigned int>> &dp,
        vector<unsigned int> &result,
        unsigned long sum) {
    for (size_t pos = 0; pos < dp.size(); pos++) {
        if (dp[pos][sum] <= 0)
            continue;
        if (dp[pos][sum] == 1) {
            result.push_back(pos);
            sum -= arr[pos];
        }

        assert (sum >= 0); 
        if (sum == 0)
            break;
    }   
}

static bool run_test(vector<unsigned int> a) {
    vector<unsigned int> resulta, resultb;
    vector<vector<unsigned int>> dp (a.size());
    unsigned long sum = static_cast<unsigned long>(std::accumulate(a.begin(), a.end(), 0));
    for (size_t i = 0; i < dp.size(); i++)
        dp[i] = vector<unsigned int>(sum + 1, 0);

    if (sum % 2 == 0) {
#ifdef NODP
        if (find_partition_with_sum_memoization(a, 0, sum/2, resulta)) {
            load_subset_memo(a, dp, resulta, sum/2);
#else
        if (find_partition_with_sum_dp(a, sum/2, dp) >= 0) {
            load_subset_dp(a, dp, resulta, sum/2);
#endif    
            for (auto& r : resulta)
                std::cout << a[r] << " ";
            std::cout << endl;

            for (size_t i = 0; i < a.size(); i++) {
                if (std::find(resulta.begin(), resulta.end(), i) == resulta.end())
                    resultb.push_back(i);
            }

            for (auto& r : resultb)
                std::cout << a[r] << " ";
            std::cout << endl;
            return resulta.size() && resultb.size();
        }
    }
    return false;
}

#define CPP_TEST(vec, exp) \
    (void) assert(run_test((vec)) == (exp))

int main(void) {
    CPP_TEST((vector<unsigned int> {5, 1, 11, 5}), true);
    CPP_TEST((vector<unsigned int> {1, 5, 11, 5, 1, 1}), true);
    CPP_TEST((vector<unsigned int> {2, 5, 3, 3, 6, 1}), true);
    CPP_TEST((vector<unsigned int> {2, 2}), true);
    CPP_TEST((vector<unsigned int> {1}), false);
    CPP_TEST((vector<unsigned int> {2}), false);
    CPP_TEST((vector<unsigned int> {1,2,5}), false);
    //CPP_TEST((vector<unsigned int> {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100}), true);
    return 0;
}
