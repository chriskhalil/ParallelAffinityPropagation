#include "AffinityPropagation.h"

using namespace Clustering;

void AffinityPropagation::update(double& variable, double newValue) {
    variable = _damping * variable + (1.0 - _damping) * newValue;
}

void AffinityPropagation::updateResponsibilities() {
    for (int i{ 0 }; i < _graph->n; ++i) {
        Edges& edges = _graph->outEdges[i];
        size_t m{ edges.size() };
        double max1{ -DBL_MAX }, max2{ -DBL_MAX };
        double argmax1{ -1 };
        for (int k{ 0 }; k < m; ++k) {
            double value{ edges[k]->similarity + edges[k]->availability };
            if (value > max1) { swap(max1, value); argmax1 = k; }
            if (value > max2) { max2 = value; }
        }
        // update responsibilities
        for (int k{ 0 }; k < m; ++k) {
            if (k != argmax1) {
                update(edges[k]->responsability, edges[k]->similarity - max1);
            }
            else {
                update(edges[k]->responsability, edges[k]->similarity - max2);
            }
        }
    }
}
void AffinityPropagation::updateAvailabilities() {
    for (int k{ 0 }; k < _graph->n; ++k) {
        Edges& edges{ _graph->inEdges[k] };
        size_t m{ edges.size() };
        // calculate sum of positive responsibilities
        auto sum{ 0.0 };
        for (int i{ 0 }; i < m - 1; ++i) {
            sum += max(0.0, edges[i]->responsability);
        }
        // calculate availabilities
        auto rkk{ edges[m - 1]->responsability };
        for (int i{ 0 }; i < m - 1; ++i) {
            update(edges[i]->availability, min(0.0, rkk + sum - max(0.0, edges[i]->responsability)));
        }
        // calculate self-availability
        update(edges[m - 1]->availability, sum);
    }
}
bool AffinityPropagation::updateExamplars(vector<int>& examplar) {
    auto changed{ false };
    for (int i{ 0 }; i < _graph->n; ++i) {
        Edges& edges{ _graph->outEdges[i] };
        size_t m{ edges.size() };
        double maxValue{ -HUGE_VAL };
        int argmax{ i };
        for (int k{ 0 }; k < m; ++k) {
            double value{ edges[k]->availability + edges[k]->responsability };
            if (value > maxValue) {
                maxValue = value;
                argmax = edges[k]->destination;
            }
        }
        if (examplar[i] != argmax) {
            examplar[i] = argmax;
            changed = true;
        }
    }
    return changed;
}


void AffinityPropagation::buildGraph(FILE* input) {

    //this build graph will create a graph from a sparce similarity matrix in 
    // COO format (do you recall COO ? COOL)

    //input must in the following format 
    // line1: 1 number that define the matrix size
    // then every line must contain 3 entries of the form  x y z (separated by space)
    //
    // where x: row index i
    // where j: column index j
    // where z: similarity(i,j)

    //build graph will run with noexcept flag on for optimization and will not check for errors in the provided file


    _graph = new Graph;
    fscanf_s(input, "%d", &_graph->n);
    _graph->outEdges = new Edges[_graph->n];
    _graph->inEdges = new Edges[_graph->n];
    vector<Edge>& edges = _graph->edges;

    // read similarity matrix
    int i{ 0 }, j{ 0 };
    double s = { 0 }, pref{ 0 };
    while (fscanf_s(input, "%d%d%lf", &i, &j, &s) != EOF) {
        if (i == j) { continue; }
        edges.push_back(Edge(i, j, s));
    }

    // calculate preferences
    // using the min - (max -min) of simlarities pref
    double minValue = min_element(edges.begin(), edges.end())->similarity;
    double maxValue = max_element(edges.begin(), edges.end())->similarity;
    pref = 2 * minValue - maxValue;

    for (int i{ 0 }; i < _graph->n; ++i) {
        edges.push_back(Edge(i, i, pref));
    }

    for (size_t i = 0; i < edges.size(); ++i) {
        Edge* p = &edges[i];
        // add small noise to avoid degeneracies
        p->similarity += (1e-16 * p->similarity + 1e-300) * (rand() / (RAND_MAX + 1.0));
        // add out/in edges to vertices
        _graph->outEdges[p->source].push_back(p);
        _graph->inEdges[p->destination].push_back(p);
    }
}

vector<int> AffinityPropagation::Run(int maxit = 500, int convit = 10) {
    vector<int> examplar(_graph->n, -1);
    for (int i = 0, nochange = 0; i < maxit && nochange < convit; ++i, ++nochange) {
        updateResponsibilities();
        updateAvailabilities();
        if (updateExamplars(examplar)) { nochange = 0; }
    }
    return examplar;
}

AffinityPropagation::AffinityPropagation(FILE* input, double damping = 0.7) {
    buildGraph(input);
    // The damping factor. (0.5 <= damping < 1.0)
    _damping = damping;
}
AffinityPropagation::~AffinityPropagation() {
    delete[] _graph->outEdges;
    delete[] _graph->inEdges;
    delete _graph;
}