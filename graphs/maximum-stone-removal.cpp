class DisjointSet
{
public:
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
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

    void unionBySize(int u, int v)
    {
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        if (ulp_u == ulp_v)
            return;

        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution
{
public:
    int maxRemove(vector<vector<int>> &stones, int n)
    {
        // Code here

        // Step 1: Initialize maximum row and column variables
        int maxRow = 0;
        int maxCol = 0;

        // Step 2: Find the maximum row and column indices from the stones
        for (auto it : stones)
        {
            maxRow = max(maxRow, it[0]);
            maxCol = max(maxCol, it[1]);
        }

        // Step 3: Create a DisjointSet object with size based on maxRow and maxCol
        DisjointSet ds(maxRow + maxCol + 1);

        // Step 4: Initialize a set to keep track of all unique stone lines (rows and columns)
        set<int> stoneLines;

        // Step 5: Iterate through each stone and perform union operations
        for (auto it : stones)
        {
            int row = it[0];
            int col = maxRow + it[1] + 1;

            // Step 6: Union the row and column to group connected stones
            ds.unionBySize(row, col);

            // Step 7: Insert the row and column into the stoneLines set
            stoneLines.insert(row);
            stoneLines.insert(col);
        }

        // Step 8: Initialize a counter for the number of unique connected components
        int count = 0;

        // Step 9: Iterate through each unique line in stoneLines
        for (auto it : stoneLines)
        {
            // Step 10: If the current line is its own ultimate parent, increment the count
            if (ds.findUltimateParent(it) == it)
            {
                count++;
            }
        }

        // Step 11: The result is the total number of stones minus the number of unique connected components
        return n - count;
    }
};
