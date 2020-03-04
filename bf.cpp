/**
 * Template program for Bellman-Ford algorithm. Implement the body of the 
 * bellmanFord() function, using OpenMP to parallelize the process. 
 */
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include "Edge.h"
#include "Graph.h"

/**
 * Bellman-Ford single-source shortest-path algorithm. 
 * 
 * \param graph Reference to the Graph object containing the graph vertices
 * and edges.
 * \param src Integer identifier of the source vertex.
 * \return Array of integers, of size graph.V, containing minimum weight of a 
 * path from src to every other vertex, or std::numeric_limits<int>::max() if
 * there is no path from src to that vertex.
 */
int* bellmanFord(const Graph& graph, int src) {
    //*************************************************************************
    //* WRITE YOUR PARALLEL BELLMAN-FORD CODE HERE
    //*************************************************************************

    //initialize new graph
    int V = graph.V;
    int E = graph.E;

    int arrD[V];
    int *D;
    D = arrD;

    int infinity = std::numeric_limits<int>::max();

    for (int i = 0; i < V; i++)
    {
        arrD[i] = infinity;
    }

    arrD[src] = 0;

    // for loop 1, iterate vertices
    // for i in [0, |V| - 1]
    for (int i = 0; i < V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            // get weight
            int u = graph.edges[j].u;
            int w = graph.edges[j].w;
            int v = graph.edges[j].v;

            if(arrD[u] != infinity && arrD[v] > arrD[u] + w)
            {
                arrD[v] = arrD[u] + w;
            }
        }
    }
    
    // return D
    return D;
}

/**
 * Application entry point. Usage:
 *
 *     ./bf v e
 *
 * where v is the number of vertices and e the number of edges in a randomly-
 * created graph. 
 *
 * \param argc Number of command-line arguments.
 * \param argv Array of strings holding command-line arguments.
 * \return EXIT_SUCCESS if the program exeuctes correctly; EXIT_FAILURE 
 * otherwise
 */
int main(int argc, char** argv) {
    using namespace std;

    int V, E;   // number of vertices and edges

    // sanity check on command-line arguments: make sure user provided number
    // of vertices and edges, and that the numbers make sense.
    if (argc != 3) {
        fprintf(stderr, "usage: ./bf v e\n");
        return EXIT_FAILURE;
    } else {
        V = atoi(argv[1]);
        E = atoi(argv[2]);
        if (V <= 0 || E <= 0) {
            fprintf(stderr, "V and E must be > 0\n");
            return EXIT_FAILURE;
        }
    }

    // Mersenne Twister pseudo-random number generator, seeded with system time
    mt19937 prng(time(0));

    // Distribution objects to provide pseudo-random numbers for weights and 
    // vertices
    std::uniform_int_distribution<int> weightDistr(1, 100);
    std::uniform_int_distribution<int> vertexDistr(0, V - 1);

    // Create a graph with V vertices and E edges, with randomly created edges
    Graph g(V, E);
    for (int i = 0; i < E; i++) {
        int s = vertexDistr(prng);
        int d = vertexDistr(prng);
        // make sure source and destination are different
        while (d == s) {
            d = vertexDistr(prng);
        }

        g.edges[i].setEdge(s, d, weightDistr(prng));
    }

    // Execute the Bellman-Ford algorithm
    chrono::high_resolution_clock::time_point t1 = 
        chrono::high_resolution_clock::now();
    int* d = bellmanFord(g, 0);
	chrono::high_resolution_clock::time_point t2 =
		chrono::high_resolution_clock::now();

	// compute and print the elapsed time
	chrono::duration<double> time_span =
		chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    
    // print out resulting distance array
    if (d == 0) {
        cout << "bellmanFord() not implemented" << endl;
    } else {
        for (int i = 0; i < V; i++) {
            cout << i << ":";
            if (d[i] != std::numeric_limits<int>::max()) {
                cout << d[i] << endl;
            }
            else {
                // output infinity symbol for unreachable vertices
                cout << "\u221E" << endl;
            }
        }

        // free array returned by bellmanFord() 
        delete[] d;
    }

    cout << "Elapsed time: " << time_span.count() << endl;

    return EXIT_SUCCESS;
}
