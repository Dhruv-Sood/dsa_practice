#include <algorithm>

class Solution
{
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        // Step 1: Create adjacency list
        vector<pair<int, int>> adj[n + 1];
        for (auto &it : edges)
        {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }

        // Min-heap priority queue
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});

        vector<int> distance(n + 1, 1e9);
        distance[1] = 0;
        vector<int> parent(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }

        // Step 2: Loop till min_heap is empty
        while (!pq.empty())
        {
            int node = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            // Apply BFS
            for (auto &it : adj[node])
            {
                int adjNode = it.first;
                int adjDist = it.second;

                // Update distance and parent if a shorter path is found
                if (distance[adjNode] > adjDist + dist)
                {
                    distance[adjNode] = adjDist + dist;
                    pq.push({adjDist + dist, adjNode});
                    parent[adjNode] = node;
                }
            }
        }

        // Step 3: Return the result path and distance
        if (distance[n] == 1e9)
            return {-1};

        vector<int> sol;
        int node = n;
        sol.push_back(node);

        // Construct the path from parent array
        while (parent[node] != node)
        {
            sol.push_back(parent[node]);
            node = parent[node];
        }
        sol.push_back(1);
        sol.push_back(distance[n]); // Added as per question description
        reverse(sol.begin(), sol.end());

        return sol;
    }
};
