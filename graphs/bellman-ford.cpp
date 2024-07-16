class Solution
{
public:
    /*  Function to implement Bellman Ford
     *   edges: vector of vectors which represents the graph
     *   S: source vertex to start traversing graph with
     *   V: number of vertices
     */
    vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S)
    {
        // Step 1: Initialize the distance array
        vector<int> distance(V, 1e8);
        distance[S] = 0;

        // Step 2: Perform N-1 relaxations (where N is the number of vertices)
        for (int i = 0; i < V - 1; i++)
        {
            // Relaxation:
            for (auto it : edges)
            {
                int u = it[0];    // Start vertex of the edge
                int v = it[1];    // End vertex of the edge
                int dist = it[2]; // Weight of the edge

                
                if (distance[u] != 1e8 && distance[v] > dist + distance[u])
                {
                    distance[v] = dist + distance[u]; 
                }
            }
        }

        // Step 3: Check for negative weight cycles by performing one more relaxation
        for (auto it : edges)
        {                     
            int u = it[0];    // Start vertex of the edge
            int v = it[1];    // End vertex of the edge
            int dist = it[2]; // Weight of the edge

            // If we can still relax an edge, it means there's a negative cycle
            if (distance[u] != 1e8 && distance[v] > dist + distance[u])
            {
                return {-1}; // Return {-1} indicating a negative weight cycle is present
            }
        }

        // If no negative cycle, return the distance array
        return distance;
    }
};
