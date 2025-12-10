#include "Graph.hpp"a

#include <iostream>
#include <vector>
#include <algorithm> // for std::sort

// Helper to pretty-print the graph (optional)
void printGraph(const Graph &g) {
    std::cout << "Graph adjacency list:\n";
    for (const auto &entry : g) {
        const Vertex &v = entry.first;
        const Neighbors &neighbors = entry.second;

        std::cout << "  " << v << " : { ";
        for (const auto &n : neighbors) {
            std::cout << n << " ";
        }
        std::cout << "}\n";
    }
    std::cout << '\n';
}

// Helper to print the cover set in sorted order
void printCover(const std::unordered_set<Vertex> &cover) {
    std::vector<Vertex> verts(cover.begin(), cover.end());
    std::sort(verts.begin(), verts.end());

    std::cout << "Vertex cover (size = " << verts.size() << "):\n";
    for (const auto &v : verts) {
        std::cout << "  " << v << "\n";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Get filename from command line or ask user
    std::string filename;
    if (argc >= 2) {
        filename = argv[1];
    } else {
        std::cout << "Enter flight table filename (e.g., sm_flights.txt): ";
        std::cin >> filename;
    }

    try {
        // 1. Read graph from file
        Graph g = VertexCover::readFromFile(filename);

        std::cout << "Loaded graph from '" << filename << "'.\n\n";

        // 2. Print the graph so you can see it
        printGraph(g);

        // 3. Compute a greedy vertex cover
        auto cover = VertexCover::cover_graph(g);

        // 4. Print the cover
        printCover(cover);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

