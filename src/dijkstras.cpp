#include "dijkstras.h"
#include <algorithm>
#include <functional>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    const int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);

    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<>> pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (dist > distances[u])
            continue;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;
    int cur = destination;
    while (cur != -1) {
        path.push_back(cur);
        cur = previous[cur];
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}

string get_arg(int argc, char *argv[], string def) {
    if (argc > 1) {
        return string(argv[1]);
    }
    return def;
}

/*
int main(int argc, char *argv[])
{
    string filename = get_arg(argc, argv, "small.txt");
    Graph G;
    file_to_graph(filename, G);

    return 0;
}
*/