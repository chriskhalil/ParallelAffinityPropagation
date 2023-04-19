#include <stdio.h>
#include "AffinityPropagation.h"

using namespace Clustering;

void AffinityPropagation::buildGraph(FILE* input) {
    cudaDeviceSynchronize();

    _graph = new Graph;
    fscanf_s(input, "%d", &_graph->n);
    _graph->outEdges = new Edges[_graph->n];
    _graph->inEdges = new Edges[_graph->n];
    vector<Edge>& edges = _graph->edges;

    
}