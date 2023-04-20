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

int qpartition(Edge arr[], int low, int high)
{
    Edge temp;
    Edge pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].similarity <= pivot.similarity)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}
// Implementation of QuickSelect
float* k2thSmallest(Edge a[], int left, int right, int k)
{

    float* s = new float[2];
    int temp = 0;
    while (left <= right)
    {

        // Partition a[left..right] around a pivot
        // and find the position of the pivot
        int pivotIndex = qpartition(a, left, right);

        // If pivot itself is the k-th smallest element
        if (pivotIndex == k - 1)
        {
            s[1] = a[pivotIndex].similarity;
            s[0] = a[temp].similarity;

            return s;
        }

        // If there are more than k-1 elements on
        // left of pivot, then k-th smallest must be
        // on left side.
        else if (pivotIndex > k - 1)
            right = pivotIndex - 1;

        // Else k-th smallest is on right side.
        else
            left = pivotIndex + 1;

        temp = pivotIndex;
    }
    return nullptr;
}