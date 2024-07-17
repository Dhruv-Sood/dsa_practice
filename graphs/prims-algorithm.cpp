class Solution
{
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // Step 1: Declare a min_heap (priority_queue) and initialize it with {0,0}
        // {distance, src}. Not storing parent as MST is not asked, only sum is asked
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});

        // Initialize the visited array with 0
        vector<int> vis(V, 0);

        // Declare a sum variable and set it to zero (It will store the path sums)
        int sum = 0;

        // Step 2: Run a loop till min_heap is empty
        while (!pq.empty())
        {
            int node = pq.top().second;
            int wt = pq.top().first;
            pq.pop();

            // If vis[node] == 1 skip the iteration
            if (vis[node] == 1)
                continue;

            // Mark vis[node] as 1
            vis[node] = 1;

            // Add wt to the sum variable
            sum += wt;

            // Apply BFS, if the nextNode is not visited, push them into min_heap
            // along with parent and newWt but do not mark them as visited
            for (auto it : adj[node])
            {
                int nextNode = it[0];
                int nextWt = it[1];

                if (!vis[nextNode])
                {
                    pq.push({nextWt, nextNode});
                }
            }
        }

        // Step 3: When the loop is over return the sum (as required in question)
        return sum;
    }
};
