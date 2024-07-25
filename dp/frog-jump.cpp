#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

// Helper function to calculate minimum energy to reach index n
int helper(int n, vector<int> &heights, vector<int> &dp)
{
    // Base case: if at the starting point, no energy is required
    if (n == 0)
        return 0;

    // If the result is already computed, return it
    if (dp[n] != -1)
        return dp[n];

    // Calculate energy required for a jump from (n-1) to n
    int left = helper(n - 1, heights, dp) + abs(heights[n] - heights[n - 1]);

    // Initialize right jump energy as maximum possible value
    int right = INT_MAX;

    // If we can jump from (n-2) to n, calculate the energy required
    if (n > 1)
    {
        right = helper(n - 2, heights, dp) + abs(heights[n - 2] - heights[n]);
    }

    // Store the minimum energy required to reach index n in dp array
    return dp[n] = min(left, right);
}

// Main function to calculate minimum energy required for the frog to reach the last stone
int frogJump(int n, vector<int> &heights)
{
    // Initialize dp array with -1 to indicate uncalculated states
    vector<int> dp(n, -1);

    // Start the helper function from the last index (n-1)
    return helper(n - 1, heights, dp);
}