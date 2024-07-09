class Solution
{
public:
    vector<int> shortestPath(vector<vector<int>> &edges, int N, int M, int src)
    {
        // Adjacency list to store the graph
        vector<int> adj[N];

        // Construct the adjacency list from the edges
        for (auto it : edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        // Distance vector initialized to a large value (infinity)
        vector<int> dist(N, 1e9);
        // Distance to the source is 0
        dist[src] = 0;

        // Queue for BFS containing pairs of (node, distance)
        queue<pair<int, int>> q;
        q.push({src, 0});

        // BFS loop
        while (!q.empty())
        {
            int node = q.front().first;
            int distance = q.front().second;
            q.pop();

            // Explore all adjacent nodes
            for (auto it : adj[node])
            {
                // If a shorter path is found
                if (dist[it] > distance + 1)
                {
                    dist[it] = distance + 1;    // Update distance
                    q.push({it, distance + 1}); // Push the node with updated distance
                }
            }
        }

        // Replace all unreachable nodes' distances with -1
        for (int i = 0; i < dist.size(); i++)
        {
            if (dist[i] == 1e9)
            {
                dist[i] = -1;
            }
        }

        // Return the distance array
        return dist;
    }
};
