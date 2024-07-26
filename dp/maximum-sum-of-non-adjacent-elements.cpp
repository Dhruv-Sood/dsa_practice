#include <bits/stdc++.h>

// Recursive function to find the maximum non-adjacent sum
int f(vector<int> &nums, int ind, vector<int> &dp)
{
    // Base case: if index is 0, return the first element as it's the only one we can pick
    if (ind == 0)
        return nums[0];

    // Edge case: if index is negative, return 0 since we can't pick elements out of bounds
    if (ind < 0)
        return 0;

    // If this subproblem has already been solved, return the stored result
    if (dp[ind] != -1)
        return dp[ind];

    // Option 1: Pick the current element and solve the subproblem for (ind-2)
    int pick = nums[ind] + f(nums, ind - 2, dp);

    // Option 2: Do not pick the current element and solve the subproblem for (ind-1)
    int nonPick = f(nums, ind - 1, dp);

    // Store the maximum of the two choices in dp array and return it
    return dp[ind] = max(pick, nonPick);
}

// Main function to find the maximum sum of non-adjacent elements
int maximumNonAdjacentSum(vector<int> &nums)
{
    // Create a dp array initialized to -1 to store the results of subproblems
    vector<int> dp(nums.size(), -1);

    // Call the recursive function starting from the last index
    return f(nums, nums.size() - 1, dp);
}
