#include "dijkstras.cpp"

int main()
{
    Graph G;
    file_to_graph("src/small.txt", G);

    int source = 0;
    //int destination = 3;

    //std::cout << "1\n";
    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    //std::cout << "2\n"
    vector<int> path;
    int total_cost;
    for (int i = 0; i < G.numVertices; ++i){
        path = extract_shortest_path(distances, previous, i);
        total_cost = distances[i];
        print_path(path, total_cost);
    }
    //std::cout << "3\n";
    
    return 0;
}