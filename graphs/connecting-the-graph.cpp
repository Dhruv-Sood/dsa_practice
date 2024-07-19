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
    int Solve(int n, vector<vector<int>> &edge)
    {
        // Step:1 Initialize the DisjointSet with 'n' elements
        DisjointSet ds(n);

        // Initialize 'extras' to 0 to keep track of extra edges
        int extras = 0;

        // Initialize 'count' to 0 to keep track of the number of components
        int count = 0;

        // Step:2 Iterate through the edges
        for (auto it : edge)
        {
            int u = it[0];
            int v = it[1];

            // If u and v have the same ultimate parent, increment 'extras'
            if (ds.findUltimateParent(u) == ds.findUltimateParent(v))
            {
                extras++;
            }

            // Perform union by rank on u and v
            ds.unionByRank(u, v);
        }

       

        // Step:3 Iterate through each node to find the number of components
        for (int i = 0; i < n; i++)
        {
            // If the ultimate parent of i is i itself, it's a component
            if (ds.findUltimateParent(i) == i)
            {
                count++;
            }
        }

        // If the number of extra edges is greater than or equal to the number of components minus one, return the number of components minus one
        if (extras >= count - 1)
        {
            return count - 1;
        }

        // Otherwise, return -1
        return -1;
    }
};
