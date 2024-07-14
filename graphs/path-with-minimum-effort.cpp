class Solution
{
public:
    int MinimumEffort(int rows, int cols, vector<vector<int>> &heights)
    {
        // Step 1: Create a min-heap and initialize the distance array
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>>
            pq;

        // Initialize with the source node
        pq.push({0, {0, 0}});

        // Initialize the distance array with infinity, except the source
        vector<vector<int>> distance(rows, vector<int>(cols, 1e9));
        distance[0][0] = 0; // source node distance is 0

        // Step 2: Loop until the min-heap is empty
        while (!pq.empty())
        {
            int diff = pq.top().first;
            int curRow = pq.top().second.first;
            int curCol = pq.top().second.second;
            pq.pop();

            // If we reached the bottom-right corner, return the effort
            if (curRow == rows - 1 && curCol == cols - 1)
                return diff;

            // Directions for moving up, down, left, right
            int delRow[] = {0, 1, 0, -1};
            int delCol[] = {-1, 0, 1, 0};

            // Check all 4 possible directions
            for (int i = 0; i < 4; i++)
            {
                int nextRow = curRow + delRow[i];
                int nextCol = curCol + delCol[i];

                // Ensure the next cell is within the grid bounds
                if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols)
                {
                    // Calculate new effort required to move to the next cell
                    int newDiff = max(diff, abs(heights[curRow][curCol] - heights[nextRow][nextCol]));

                    // Only push to the heap if the new effort is less than the recorded effort in the distance array
                    if (newDiff < distance[nextRow][nextCol])
                    {
                        distance[nextRow][nextCol] = newDiff;
                        pq.push({newDiff, {nextRow, nextCol}});
                    }
                }
            }
        }

        return -1; // This return is never reached as per problem constraints
    }
};
