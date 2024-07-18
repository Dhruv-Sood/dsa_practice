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
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // Step 1: Implement a DisjointSet class
        // Make an edges vector out of adj list and sort it in terms of weight
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++)
        {
            for (auto it : adj[i])
            {
                int v = it[0];
                int wt = it[1];

                edges.push_back({wt, {i, v}});
            }
        }

        sort(edges.begin(), edges.end());

        // Create a DistjointSet ds
        DisjointSet ds(V);
        // Create a Sum variable and initialise it with 0
        int sum = 0;

        // Step 2: Iterate over the edges
        for (auto it : edges)
        {
            int u = it.second.first;
            int v = it.second.second;
            int wt = it.first;
            // For every edge, if ultimate_parent_of_u == ultimate_parent_of_v, skip the iteration
            if (ds.findUltimateParent(u) == ds.findUltimateParent(v))
                continue;

            // Else perform unionByRank for both u and v and also add wt to sum
            ds.unionByRank(u, v);
            sum += wt;
        }
        // Step 3: After the loop ends, return Sum
        return sum;
    }
};
