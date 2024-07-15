class Solution
{
public:
    int CheapestFLight(int n, vector<vector<int>> &flights, int src, int dst, int K)
    {
        // Step 1: Create a graph from the flights array
        vector<pair<int, int>> adj[n];
        for (auto it : flights)
        {
            adj[it[0]].push_back({it[1], it[2]});
        }

        // Initialize the distance array with infinity
        vector<int> distance(n, 1e9);
        distance[src] = 0;

        // Create a queue and initialize it with the source node
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}}); // {stops, {node, distance}}

        // Step 2: Run a loop until the queue is empty
        while (!q.empty())
        {
            int node = q.front().second.first;
            int dist = q.front().second.second;
            int stops = q.front().first;

            q.pop();

            // If the number of stops is greater than K, skip this iteration
            if (stops > K)
                continue;

            // Apply BFS
            for (auto it : adj[node])
            {
                int nextNode = it.first;
                int nextDist = it.second;

                // If a shorter path to the next node is found and stops are within limit
                if (distance[nextNode] > dist + nextDist && stops <= K)
                {
                    // Update the distance array and push the next node to the queue
                    distance[nextNode] = dist + nextDist;
                    q.push({stops + 1, {nextNode, distance[nextNode]}});
                }
            }
        }

        // Step 3: If the destination is unreachable, return -1, otherwise return the distance to the destination
        if (distance[dst] == 1e9)
            return -1;

        return distance[dst];
    }
};
