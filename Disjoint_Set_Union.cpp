#include<bits/stdc++.h>
using namespace std;
#define nl "\n" // Defining a newline character shortcut

class Disjoint_Set_Union
{
public:
    // Vectors to store parent, size, and rank of each element
    vector<int>parents, size, rank;

    // Function to initialize the disjoint set
    void Initialize(int n){
        // Initialize n elements with themselves as their own parent
        for (int i = 0; i <= n; i++){
            parents.push_back(i);  // Initially, each element is its own parent (self-loop)
            size.push_back(1);     // Each set initially has a size of 1
            rank.push_back(0);     // Each element has an initial rank of 0 (for union by rank)
        }
    }

    // Function to find the root (leader) of the set containing 'u'
    // Uses path compression to optimize future queries
    int find(int u){
        if(parents[u] == u) return u; // If 'u' is its own parent, return it as the root
        return parents[u] = find(parents[u]); // Path compression by recursively finding the root and updating the parent
    }

    // Function to union two sets based on size heuristic
    void union_by_size(int u, int v){
        int root_u = find(u); // Find the root of set containing 'u'
        int root_v = find(v); // Find the root of set containing 'v'
        if(root_u == root_v) return; // If they are already in the same set, do nothing

        // Always attach the smaller tree under the larger one
        if(size[root_u] < size[root_v])
            swap(root_u, root_v); // Swap so that root_u always refers to the larger set
        parents[root_v] = root_u; // Make root_u the parent of root_v
        size[root_u] += size[root_v]; // Update the size of the combined set
    }

    // Function to union two sets based on rank heuristic
    void union_by_rank(int u, int v){
        int root_u = find(u); // Find the root of set containing 'u'
        int root_v = find(v); // Find the root of set containing 'v'
        if(root_u == root_v) return; // If they are already in the same set, do nothing

        // Attach the tree with lower rank under the tree with higher rank
        if(rank[root_u] < rank[root_v])
            swap(root_u, root_v); // Swap to ensure root_u has equal or higher rank
        parents[root_v] = root_u; // Make root_u the parent of root_v

        // If both roots have the same rank, increment the rank of root_u
        if(rank[root_u] == rank[root_v])
            rank[u]++;
    }
};

int main()
{
    Disjoint_Set_Union dsu;
    dsu.Initialize(10); // Initialize 11 elements (0 to 10)

    // Creating connections between all even nodes using union_by_size
    dsu.union_by_size(0, 2);
    dsu.union_by_size(2, 4);
    dsu.union_by_size(4, 6);
    dsu.union_by_size(6, 8);
    dsu.union_by_size(8, 10);

    // Creating connections between all odd nodes using union_by_size
    dsu.union_by_size(1, 3);
    dsu.union_by_size(3, 5);
    dsu.union_by_size(5, 7);
    dsu.union_by_size(7, 9);

    // Output connected even nodes
    cout << "All Even Connected Nodes :" << nl;
    int even_root = dsu.find(10); // Find the root of the set containing 10
    for (int i = 0; i < dsu.parents.size(); i++){
        if(dsu.find(i) == even_root) cout << i << nl; // Print all nodes in the set rooted at even_root
    }

    // Output connected odd nodes
    cout << "All Odd Connected Nodes :" << nl;
    int odd_root = dsu.find(9); // Find the root of the set containing 9
    for (int i = 0; i < dsu.parents.size(); i++){
        if(dsu.find(i) == odd_root) cout << i << nl; // Print all nodes in the set rooted at odd_root
    }

    return 0; // End of program
}
