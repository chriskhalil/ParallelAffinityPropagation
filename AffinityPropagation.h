#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>

using std::vector;
using std::max;
using std::min;
using std::swap;

struct Edge {
    public:
        int source;      // index of source
        int destination;      // index of destination
        double similarity;     // similarity s(src, dst)
        double responsability;     // responsibility r(src, dst)
        double availability;     // availability a(src, dst)
        Edge() :source{ 0 }, destination{ 0 }, similarity{ 0 }, responsability{ 0 }, availability{ 0 } {}
        Edge(int src, int dst, double s) : source(src), destination(dst), similarity(s), responsability(0), availability(0) {}
        Edge(const Edge& x) {
            source = x.source;
            destination = x.destination;
            similarity = x.similarity;
            responsability = x.responsability;
            availability = x.availability;

        }
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

struct d_Graph {
    public:
        int Vertices;         // the number of vertices
        Edge*** outEdges;      // array of out edges of corresponding vertices
        Edge*** inEdges;       // array of in edges of corresponding vertices
        Edge** edges;   // all edges
        size_t EdgesCount;
        d_Graph(int number_of_vertices) {
            Vertices = number_of_vertices < 0 ? 0 : number_of_vertices;

            outEdges = new Edge**[Vertices];
            inEdges  = new Edge**[Vertices];
            edges = new Edge*[((Vertices - 1) * Vertices) + Vertices];

            EdgesCount = ((Vertices - 1) * Vertices) + Vertices;
            for (int i{ 0 }; i < Vertices; ++i) {
                outEdges[i] = new Edge*[Vertices];
                inEdges[i] = new Edge*[Vertices];
            }
        }
        ~d_Graph() {
            for (int i{ 0 }; i < Vertices; ++i) {
                delete [] outEdges[i];
                delete [] inEdges[i];
            }
            for (int i{ 0 }; i < Vertices * Vertices; ++i)
                delete edges[i];
            delete outEdges;
            delete inEdges;
            delete[] edges;
        }
 };

    class AffinityPropagation {
    private:
        Graph* _graph;
        d_Graph* _d_graph;
        double _damping;

        void buildGraph(FILE* input);
        inline void update(double& variable, double newValue);
        void updateResponsibilities();
        void updateAvailabilities();
        bool updateExamplars(vector<int>& examplar);
        void build_d_graph();

    public:
        AffinityPropagation(FILE*, double);
        vector<int> Run(int maxit, int convit);
        ~AffinityPropagation();

    };