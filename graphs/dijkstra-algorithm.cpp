class Solution
{
public:
    // Function to find the shortest distance of all the vertices from the source vertex S.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Step 1: Initialize the distance array with infinity and set the source distance to 0
        vector<int> distance(V, 1e9);
        distance[S] = 0;

        //Create a min-heap (priority queue) to store <distance, node>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        //Push the source node with distance 0 into the priority queue
        pq.push({0, S});

        // Step 2: Run the loop until the priority queue is empty
        while (!pq.empty())
        {

            int node = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            //Iterate through all connected nodes (neighbors) of the current node
            for (auto it : adj[node])
            {
                int connectedNode = it[0];
                int edgeWeight = it[1];

                //If the new calculated distance is smaller, update the distance array
                if (distance[connectedNode] > dist + edgeWeight)
                {
                    distance[connectedNode] = dist + edgeWeight;
                    //Push the updated distance and node into the priority queue
                    pq.push({dist + edgeWeight, connectedNode});
                }
            }
        }
        // Step 3: Return the distance array containing the shortest distance to all nodes from the source
        return distance;
    }
};
