
#include<iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

template <typename T> class Graph {
private:
    vector<T> values;
    vector<vector<int>> neighbours;

public:
    Graph(){
        neighbours.resize(10);
    }

    void addVertex(T k);
    void addEdge(int idx1, int idx2);
    void removeVertex(int idx);
    T getValue(int idx);
    bool containsValue(T k);
    int shortestPath(int idx1, int idx2);
    void print();
};

template <class T> void Graph<T>::addVertex(T k)
{
    values.push_back(k);
}

template <class T> void Graph<T>::addEdge(int idx1, int idx2)
{
    if (idx1 >= values.size() || idx2 >= values.size()) {
        cout << "Graph has no vertices with this indices";
        exit(3);
    }
    if (neighbours[idx1].size() > 0 && neighbours[idx2].size() > 0 && (neighbours[idx1][0] == -1 || neighbours[idx2][0] == -1)) {
        cout << "Some elements have been removed";
        exit(3);
    }
    neighbours[idx1].push_back(idx2);
}
template <class T> void Graph<T>::removeVertex(int idx)
{
    if (idx >= values.size()) {
        cout << "Graph has no vertices with this index";
        exit(3);
    }
    if (neighbours[idx].size() > 0 && neighbours[idx][0] == -1) {
        cout << "Element was removed";
        exit(3);
    }
    neighbours[idx].clear();
    neighbours.push_back(-1);
}

template <class T> T Graph<T>::getValue(int idx)
{
    if (idx >= values.size()) {
        cout << "Graph has no vertices with this index";
        exit(3);
    }
    if (neighbours[idx].size() > 0 && neighbours[idx][0] == -1) {
        cout << "Element was removed";
        exit(3);
    }
    return values[idx];
}

template <class T> bool Graph<T>::containsValue(T k)
{
    for (T value : values) {
        if (value == k) {
            return true;
        }
    }

    return false;
}

template <class T> int  Graph<T>::shortestPath(int idx1, int idx2)
{
    vector<bool> used(values.size());
    vector<int> dist(values.size());
    queue<int> nodes;
    nodes.push(idx1);
    used[idx1] = true;
    while (!nodes.empty() && !used[idx2]) {
        int curr = nodes.front();
        nodes.pop();
        for (int neighbour : neighbours[curr]) {
            if (!used[neighbour]) {
                nodes.push(neighbour);
                used[neighbour] = true;
                dist[neighbour] = dist[curr] + 1;
            }
        }
    }

    return dist[idx2];
}

template <class T> void Graph<T>::print()
{
    for (int i = 0; i < values.size(); i++) {
        cout << "Vertex #" << (i + 1) << " - value: " << values[i] << ", neighbours values: ";
        for (int j = 0; j < neighbours[i].size(); j++) {
            cout << values[neighbours[i][j]];
            if (j == neighbours[i].size() - 1) {
                cout << ".\n";
            }
            else {
                cout << ", ";
            }
        }
    }
}

template<typename T>
bool testContains(Graph<T> g, vector<T> contains, vector<bool> result) {

    for (int i = 0; i < result.size(); i++) {
        if (g.containsValue(contains[i]) != result[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool testShortestPath(Graph<T> g, vector<pair<int, int>> ids, vector<int> result) {

    for (int i = 0; i < result.size(); i++) {
        if (g.shortestPath(ids[i].first, ids[i].second) != result[i]) {
            return false;
        }
    }

    return true;
}


int main()
{

    Graph<int> g1;
    g1.addVertex(4);
    g1.addVertex(7);
    g1.addVertex(9);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);

    Graph<int> g2;
    g2.addVertex(1);
    g2.addVertex(2);
    g2.addVertex(3);
    g2.addVertex(4);
    g2.addVertex(5);
    g2.addVertex(5);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);

    Graph<string> g3;
    g3.addVertex("a");
    g3.addVertex("b");
    g3.addVertex("c");
    g3.addVertex("f");
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(2, 3);
    g3.addEdge(1, 3);

    Graph<string> g4;
    g4.addVertex("dfs");
    g4.addVertex("bfs");
    g4.addVertex("hello");
    g4.addVertex("g");
    g4.addVertex("mmm");
    g4.addEdge(0, 1);
    g4.addEdge(0, 2);
    g4.addEdge(1, 3);
    g4.addEdge(2, 4);
    g4.addEdge(3, 4);

    vector<int> contains1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<string> contains2 = { "a", "b", "c", "d", "e", "f", "g", "h", "dfs", "bfs", "hello", "mmm", "hi" };

    vector<bool> res11 = { false, false, false, false, true, false, false, true, false, true, false };
    vector<bool> res12 = { false, true, true, true, true, true, false, false, false, false, false };
    vector<bool> res13 = { true, true, true, false, false, true, false, false, false, false, false, false, false };
    vector<bool> res14 = { false, false, false, false, false, false, true, false, true, true, true, true, false };

    cout << (testContains(g1, contains1, res11) ? "PASSED\n" : "FAILED\n");
    cout << (testContains(g2, contains1, res12) ? "PASSED\n" : "FAILED\n");
    cout << "_________\n";
    cout << (testContains(g3, contains2, res13) ? "PASSED\n" : "FAILED\n");
    cout << (testContains(g4, contains2, res14) ? "PASSED\n" : "FAILED\n");
    cout << "_________\n";

    vector<pair<int, int>> dist1 = { {0, 1}, {0, 2} };
    vector<pair<int, int>> dist2 = { {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {3, 5}, {1, 1} };
    vector<pair<int, int>> dist3 = { {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3} };
    vector<pair<int, int>> dist4 = { {0, 4}, {0, 3}, {0, 2}, {0, 1}, {1, 3}, {1, 4} };


    vector<int> res21 = { 1, 1 };
    vector<int> res22 = { 1, 2, 3, 4, 5, 2, 0 };
    vector<int> res23 = { 1, 1, 2, 1, 1 };
    vector<int> res24 = { 2, 2, 1, 1, 1, 2 };

    cout << (testShortestPath(g1, dist1, res21) ? "PASSED\n" : "FAILED\n");
    cout << (testShortestPath(g2, dist2, res22) ? "PASSED\n" : "FAILED\n");
    cout << "_________\n";
    cout << (testShortestPath(g3, dist3, res23) ? "PASSED\n" : "FAILED\n");
    cout << (testShortestPath(g4, dist4, res24) ? "PASSED\n" : "FAILED\n");
    cout << "_________\n";
    

    return 0;
}