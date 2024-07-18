class DisjointSet
{
    vector<int> rank;
    vector<int> parent;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);

        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int findUltimateParent(int u)
    {
        if (parent[u] == u)
        {
            return u;
        }

        return parent[u] = findUltimateParent(parent[u]);
    }

    void unionByRank(int u, int v)
    {
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        if (ulp_v == ulp_u)
        {
            return;
        }

        if (rank[ulp_u] > rank[ulp_v])
        {
            parent[ulp_v] = ulp_u;
        }
        else if (rank[ulp_v] > rank[ulp_u])
        {
            parent[ulp_u] = ulp_v;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

class Solution
{
public:
    int numProvinces(vector<vector<int>> adj, int V)
    {
        // Step 1: Implement a DisjointSet class and create a DisjointSet instance
        DisjointSet ds(V);

        // Step 2: Iterate over the adjacency matrix
        // For every connection, perform a unionByRank operation
        for (int i = 0; i < adj.size(); i++)
        {
            for (int j = 0; j < adj[0].size(); j++)
            {
                if (adj[i][j] == 1)
                {
                    ds.unionByRank(i, j);
                }
            }
        }

        // Step 3: Initialize count variable and set it to 0
        int count = 0;

        // Run a loop till the size (V)
        // Check if the ultimate parent of i is i
        // If yes, increment count
        for (int i = 0; i < V; i++)
        {
            if (ds.findUltimateParent(i) == i)
            {
                count++;
            }
        }

        // Return the count
        return count;
    }
};