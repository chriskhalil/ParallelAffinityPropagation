#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

using std::vector;
using std::max;
using std::min;
using std::swap;

namespace Clustering {
    struct Edge {
    public:
        int source;      // index of source
        int destination;      // index of destination
        double similarity;     // similarity s(src, dst)
        double responsability;     // responsibility r(src, dst)
        double availability;     // availability a(src, dst)

        Edge(int src, int dst, double s) : source(src), destination(dst), similarity(s), responsability(0), availability(0) {}
        bool operator<(const Edge& rhs) const { return similarity < rhs.similarity; }
    };

    typedef vector<Edge*> Edges;

    struct Graph {
    public:
        int n;                // the number of vertices
        Edges* outEdges;      // array of out edges of corresponding vertices
        Edges* inEdges;       // array of in edges of corresponding vertices
        vector<Edge> edges;   // all edges
    };

    class AffinityPropagation {
    private:
        Graph* _graph;
        double _damping;

        void buildGraph(FILE* input);
        inline void update(double& variable, double newValue);
        void updateResponsibilities();
        void updateAvailabilities();
        bool updateExamplars(vector<int>& examplar);

    public:
        AffinityPropagation(FILE*, double);
        vector<int> Run(int maxit, int convit);
        ~AffinityPropagation();

    };
}