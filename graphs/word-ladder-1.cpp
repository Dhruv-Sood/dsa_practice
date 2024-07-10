class Solution
{
public:
    int wordLadderLength(string startWord, string targetWord, vector<string> &wordList)
    {
        // Step 1: Make a queue of pair <word,length_of_sequence> and enter <first_word,1>
        // Copy the elements of word list in set for faster searching
        unordered_set<string> st(wordList.begin(), wordList.end());

        queue<pair<string, int>> q;
        q.push({startWord, 1});

        st.erase(startWord);

        // Step 2: Execute the queue in loop till empty
        while (!q.empty())
        {
            // Take out the front pair
            string curWord = q.front().first;
            int length = q.front().second;
            q.pop();

            // As soon as you get the end desired word, stop and return length_of_sequence
            if (curWord == targetWord)
                return length;

            // Take the word and start changing each letter of word from a-z
            for (int i = 0; i < curWord.size(); i++)
            {
                string wordCopy = curWord;
                for (char x = 'a'; x <= 'z'; x++)
                {
                    wordCopy[i] = x;
                    // if they appear in set, add the <newWord,length_of_sequence +1> in queue
                    if (st.find(wordCopy) != st.end())
                    {
                        st.erase(wordCopy); // Remove the newWord from set to avoid future occurrences
                        q.push({wordCopy, length + 1});
                    }
                }
            }
        }

        // If you do not get the desired word and set gets empty, return 0
        return 0;
    }
};