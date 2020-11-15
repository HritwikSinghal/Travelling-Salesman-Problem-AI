#include <bits/stdc++.h>

#define vi vector<int>
#define pii pair<int, int>


using namespace std;

void prim_MST(const vector<vector<pii>> &adj, int n, vector<pii > &MST, vi &pre_order) {

    vi visited(n, 0);
    vi cost(n, INT_MAX);
    vi parent(n, -1);

    cost[0] = 0;
    parent[0] = 0;
    priority_queue<pii, vector<pii >, greater<>> tree;
    tree.emplace(make_pair(cost[0], 0));
    for (int i = 1; i < n; ++i)
        tree.emplace(make_pair(INT_MAX, i));


    while (!tree.empty()) {
        int curr_vertex = tree.top().second;

        if (visited[curr_vertex]) {
            tree.pop();
            continue;
        }

        tree.pop();
        visited[curr_vertex] = 1;
        pre_order.push_back(curr_vertex);

        MST.emplace_back(curr_vertex, parent[curr_vertex]);

        // to prevent selecting edges that cause cycles, we mark the vertex as visited when we visit it
        // and then skip that vertex when we check which neighbour to visit from another vertex.
        for (auto neighbour: adj[curr_vertex]) {
            if (!visited[neighbour.first] && cost[neighbour.first] > neighbour.second) {
                cost[neighbour.first] = neighbour.second;
                parent[neighbour.first] = curr_vertex;
                tree.emplace(make_pair(neighbour.second, neighbour.first));
            }
        }
    }


}

void print_MST(const vector<pair<int, int>> &MST) {
    // Print MST
    // starting vertex = 0

    cout << "Below are the edges between pair of vertices in MST\n";
    for (auto edge: MST) {
        if (edge.first == 0)
            continue;
        cout << edge.second << " <--> " << edge.first << "\n";
    }
}


// Driver code
int main() {
    /*
        Initial State: Agent in the start city and has not visited any other city
        Goal State: Agent has visited all the cities and reached the start city again
        Successor Function: Generates all cities that have not yet visited
        Edge-cost = g(n): distance between the cities.
    */


    // n vertices, m edges
    int n, m;
    cin >> n >> m;

    // creating adj list
    vector<vector<pii>> adj(n, vector<pii >());
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;

        // makes pair of (dest, cost)
        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));

    }

    // for printing adj list
    cout << "Printing Adj List of graph\n";
    cout << "----------------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        cout << i << "-> ";

        for (auto j : adj[i]) {
            cout << "(" << j.first << "," << j.second << ")" << "-> ";
        }
        cout << "\n";
    }
    cout << "----------------------------------------------\n";

    // creating and filling MST
    vector<pii > MST;
    vi pre_order;
    prim_MST(adj, n, MST, pre_order);

    // printing MST
    print_MST(MST);

    // printing the TSP path
    cout << "\nTSP Path = ";
    for (auto x: pre_order) {
        cout << x << "->";
    }
    cout << "0\n";

    return 0;
}
