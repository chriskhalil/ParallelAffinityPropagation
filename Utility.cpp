#include "Utility.h"


float inline NegativeEuclidenDistance(Point p1, Point p2) {
	return (-1) * (p2.x - p1.x) * (p2.y - p1.y);
}

vector<Edge> SparseSimilarityMatrix(Point ptr[],const int size, float (*distance) (Point, Point)) {
   // Create the similarity matrix with a user defined distance measure
    vector<Edge> items{};
    int p{ 0 };
    for (int i{ 0 }; i < size; i++)
        for (int j{ i + 1 }; j < size; j++)
        {
            items[p] =Edge(i, j, distance(ptr[i], ptr[j]));
            items[p + 1] =Edge(j, i, distance(ptr[i], ptr[j]));
            p += 2;
        }
    return items;
}

