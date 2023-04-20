#include <stdio.h>
#include "AffinityPropagation.h"

void AffinityPropagation::update(double& variable, double newValue) {
    variable = _damping * variable + (1.0 - _damping) * newValue;
}


void AffinityPropagation::updateAvailabilities(){
    // for (int k{ 0 }; k < _graph->n; ++k) {
    //     Edges& edges{ _graph->inEdges[k] };
    //     size_t m{ edges.size() };
    //     // calculate sum of positive responsibilities
    //     auto sum{ 0.0 };
    //     for (int i{ 0 }; i < m - 1; ++i) {
    //         sum += max(0.0, edges[i]->responsability);
    //     }
    //     // calculate availabilities
    //     auto rkk{ edges[m - 1]->responsability };
    //     for (int i{ 0 }; i < m - 1; ++i) {
    //         update(edges[i]->availability, min(0.0, rkk + sum - max(0.0, edges[i]->responsability)));
    //     }
    //     // calculate self-availability
    //     update(edges[m - 1]->availability, sum);
    // }
    

        Edges* inEdges { _graph->inEdges }
        
    updateAvailabilities_GPU(inEdges);
}


void AffinityPropagation::updateResponsibilities() {
    // for (int i{ 0 }; i < _graph->n; ++i) {
    //     Edges& edges = _graph->outEdges[i];
    //     size_t m{ edges.size() };
    //     double max1{ -DBL_MAX }, max2{ -DBL_MAX };
    //     double argmax1{ -1 };
    //     for (int k{ 0 }; k < m; ++k) {
    //         double value{ edges[k]->similarity + edges[k]->availability };
    //         if (value > max1) { swap(max1, value); argmax1 = k; }
    //         if (value > max2) { max2 = value; }
    //     }
    //     // update responsibilities
    //     for (int k{ 0 }; k < m; ++k) {
    //         if (k != argmax1) {
    //             update(edges[k]->responsability, edges[k]->similarity - max1);
    //         }
    //         else {
    //             update(edges[k]->responsability, edges[k]->similarity - max2);
    //         }
    //     }
    // }

    cudaDeviceSynchronize();
    // Edges& edges = _graph->outEdges[0];
    
}


// to do
void AffinityPropagation::buildGraph(FILE* input) {
    cudaDeviceSynchronize();

    _graph = new Graph;
    fscanf_s(input, "%d", &_graph->n);
    _graph->outEdges = new Edges[_graph->n];
    _graph->inEdges = new Edges[_graph->n];
    vector<Edge>& edges = _graph->edges;

}