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
    int MaxConnection(vector<vector<int>> &grid)
    {
        // code here
        int rows = grid.size();
        int cols = grid[0].size();

        DisjointSet ds(rows * cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int boxNumber = i * cols + j;

                int delRow[] = {0, 1, 0, -1};
                int delCol[] = {-1, 0, 1, 0};

                for (int x = 0; x < 4; x++)
                {
                    int nRow = i + delRow[x];
                    int nCol = j + delCol[x];

                    if (nRow >= 0 && nRow < rows && nCol >= 0 && nCol < cols && grid[nRow][nCol] == 1)
                    {
                        int nextBoxNumber = nRow * cols + nCol;
                        ds.unionBySize(boxNumber, nextBoxNumber);
                    }
                }
            }
        }

        int ans = 0;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 0)
                {
                    int delRow[] = {0, 1, 0, -1};
                    int delCol[] = {-1, 0, 1, 0};

                    set<int> st;

                    for (int x = 0; x < 4; x++)
                    {
                        int nRow = i + delRow[x];
                        int nCol = j + delCol[x];

                        if (nRow >= 0 && nRow < rows && nCol >= 0 && nCol < cols && grid[nRow][nCol] == 1)
                        {
                            st.insert(ds.findUltimateParent(nRow * cols + nCol));
                        }
                    }
                    int possibleNextAns = 1;
                    for (auto it : st)
                    {
                        possibleNextAns += ds.size[it];
                    }
                    ans = max(ans, possibleNextAns);
                }
            }
        }

        return ans;
    }
};