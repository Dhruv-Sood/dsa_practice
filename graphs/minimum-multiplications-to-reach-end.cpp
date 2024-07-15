class Solution
{
public:
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        // Step 1: Initialize the distance array and set the distance of the starting node to 0
        vector<int> distance(100000, 1e9);
        distance[start] = 0;

        // Create a queue to store pairs of {steps, node}
        queue<pair<int, int>> q;
        q.push({0, start}); // {steps, node}

        // Step 2: Process the queue until it's empty
        while (!q.empty())
        {
            int node = q.front().second; // current node
            int steps = q.front().first; // number of steps taken to reach this node
            q.pop();

            // Apply a for loop to multiply the node with each element in the array
            for (int i = 0; i < arr.size(); i++)
            {
                int nextNode = (node * arr[i]) % 100000; // calculate the next node
                // If the distance to the next node is greater than the current steps + 1
                if (distance[nextNode] > steps + 1)
                {
                    distance[nextNode] = steps + 1;         // update the distance
                    q.push({distance[nextNode], nextNode}); // push the next node with updated steps
                }
            }
        }

        // Step 3: Check the final distance to the end node
        if (distance[end] == 1e9)
            return -1;        // if end node is not reachable
        return distance[end]; // return the minimum steps to reach the end node
    }
};
