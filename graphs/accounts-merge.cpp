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
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        DisjointSet ds(accounts.size());
        unordered_map<string, int> mapMailNode;

        // Traverse each account to map each email to a unique account index
        for (int i = 0; i < accounts.size(); i++)
        {
            for (int j = 1; j < accounts[i].size(); j++)
            {
                string mail = accounts[i][j];
                if (mapMailNode.find(mail) == mapMailNode.end())
                {
                    mapMailNode[mail] = i;
                }
                else
                {
                    ds.unionByRank(i, mapMailNode[mail]);
                }
            }
        }

        // Create a list to store merged emails for each unique parent
        vector<string> mergedMail[accounts.size()];
        for (auto it : mapMailNode)
        {
            int node = it.second;
            string mail = it.first;
            mergedMail[ds.findUltimateParent(node)].push_back(mail);
        }

        vector<vector<string>> ans;

        // Traverse each account to sort and add the merged emails to the result
        for (int i = 0; i < accounts.size(); i++)
        {
            if (mergedMail[i].size() == 0)
                continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            copy(mergedMail[i].begin(), mergedMail[i].end(), back_inserter(temp));
            ans.push_back(temp);
        }

        return ans;
    }
};