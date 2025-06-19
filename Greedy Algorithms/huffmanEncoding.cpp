#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

class Node
{
public:
    char data; // For storing character
    int freq;  // For storing frequency
    Node *left, *right;

    Node(char d, int f)
    {
        this->data = d;
        this->freq = f;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

class Solution
{
public:
    void traverse(Node *root, unordered_map<char, string> &ans, string temp)
    {
        if (root == nullptr)
            return;

        // If it's a leaf node, store the character and its encoding.
        if (root->left == nullptr && root->right == nullptr)
        {
            ans[root->data] = temp;
        }

        // Traverse the left and right child with updated string
        traverse(root->left, ans, temp + '0');
        traverse(root->right, ans, temp + '1');
    }

    unordered_map<char, string> huffmanEncoding(string s, vector<int> f, int n)
    {
        priority_queue<Node *, vector<Node *>, Compare> pq;

        // Create the priority queue from the frequencies
        for (int i = 0; i < n; i++)
        {
            pq.push(new Node(s[i], f[i]));
        }

        // Build the Huffman Tree
        while (pq.size() > 1)
        {
            Node *left = pq.top();
            pq.pop();

            Node *right = pq.top();
            pq.pop();

            Node *newNode = new Node('$', left->freq + right->freq); // '$' is a placeholder
            newNode->left = left;
            newNode->right = right;

            pq.push(newNode);
        }

        // The root node of the Huffman Tree
        Node *root = pq.top();

        unordered_map<char, string> ans;
        traverse(root, ans, "");

        return ans;
    }
};

int main()
{
    // Sample input
    string s = "DATSRUCE";
    vector<int> f = {18,37,29,50,17,30,6,13};
    int n = s.size();

    Solution solution;
    unordered_map<char, string> result = solution.huffmanEncoding(s, f, n);

    // Output the Huffman codes
    for (auto &p : result)
    {
        cout << p.first << ": " << p.second << endl;
    }

    return EXIT_SUCCESS;
}
