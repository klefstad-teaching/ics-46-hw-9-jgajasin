#include "dijkstras.cpp"

int main()
{
    Graph G;
    file_to_graph("src/small.txt", G);

    int source = 0;
    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    vector<int> shortest_path;
    int total_cost;
    for (int i = 0; i < G.numVertices; ++i){
        shortest_path = extract_shortest_path(distances, previous, i);
        total_cost = distances[i];
        print_path(shortest_path, total_cost);
    }
    
    return 0;
}