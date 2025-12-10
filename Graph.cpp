#include "Graph.hpp"

namespace VertexCover {
/**
 * @brief Reads the contents of a flight table
 * as specified by the filename , into an undirected
 * Graph .
 *
 * @param filename ( a const . string reference ) The filename of the file to be read
 * @return ( Graph ) The resultant Graph object described by the file 's contents .
 *
 * @throws ( std :: runtime_error ) If the file cannot be opened for some reason
 */
Graph readFromFile(const std::string& filename) {
    // Opens the file 
    std::ifstream in(filename);

    // If the file cannot be opened , throw an error
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    Graph g;
    std::string line;

    // Read each line of the file
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        //Find first dash to locate the deporting airport
        std::size_t firstDash = line.find(" - ");
        if (firstDash == std::string::npos) {
            continue; 
        }
        Vertex from = line.substr(firstDash + 3, 3);

        //Find second dash to locate the arriving airport
        std::size_t pipePos = line.find('|', firstDash);
        if (pipePos == std::string::npos) { 
            continue;
        }
        std::size_t secondDash = line.find(" - ", pipePos);
        if (secondDash == std::string::npos) {
            continue;
        }
        Vertex to = line.substr(secondDash + 3, 3);

        // Add the edge to the graph ( undirected )
        g[from].insert(to);
        g[to].insert(from);
    }

    return g;
}

/**
 * @brief Generates a sub-optimal minimumum vertex cover
 * by repeatedly choosing the largest degree vertex & 
 * adding it to the cover set.
 *
 * @param g (Graph) The graph object 
 * for which to generate a vertex cover. 
 * NOTE: This is NOT a const. reference
 *
 * @return (std::unordered_set<Vertex>) The set of vertices 
 * that forms a vertex cover of the graph.
 */
std::unordered_set<Vertex> cover_graph(Graph g) {
    std::unordered_set<Vertex> cover;

    while (true) {
        Vertex bestVertex;            
        std::size_t bestDegree = 0;     
        bool hasEdges = false;          

        for (const auto &entry : g) {
            const Vertex &v = entry.first;
            const Neighbors &neighbors = entry.second;

            if (!neighbors.empty()) {          
                hasEdges = true;
                if (neighbors.size() > bestDegree) {
                    bestDegree = neighbors.size();
                    bestVertex = v;
                }
            }
        }

        if (!hasEdges) {
            break;
        }

        cover.insert(bestVertex);

        Neighbors neighborsCopy = g[bestVertex];
        for (const Vertex &n : neighborsCopy) {
            g[n].erase(bestVertex);    
        }


        g[bestVertex].clear();
    }

    return cover;
}
}