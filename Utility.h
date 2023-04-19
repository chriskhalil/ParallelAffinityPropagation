#pragma once
#include "AffinityPropagation.h"


struct Point {
public:
	float x{ 0 };
	float y{ 0 };
    Point(float x, float y) :x{ x }, y{ y } {};
};

float inline NegativeEuclidenDistance(Point x, Point y);

vector<Edge> SparseSimilarityMatrix(Point ptr[],const int size, float (*distance) (Point, Point));



//toy dataset for verification
class ToyDataset
{
public:
    vector<int> Centers()
    {
        return { 2, 2, 2, 2, 2, 2, 6, 6, 6, 6, 2, 6, 2, 6, 6, 19, 19, 19, 19, 19, 19, 2, 19, 19, 6 };
    }

    vector<Point> DataSet()
    {
        vector<Point> data;
        data.push_back(Point(-2.3415f, 3.6968f));
        data.push_back(Point(-1.1092f, 3.1117f));
        data.push_back(Point(-1.5669f, 1.8351f));
        data.push_back(Point(-2.6585f, 0.6649f));
        data.push_back(Point(-4.0317f, 2.8457f));
        data.push_back(Point(-3.081f, 2.1011f));
        data.push_back(Point(2.588f, 1.7819f));
        data.push_back(Point(3.2923f, 3.0585f));
        data.push_back(Point(4.0317f, 1.6223f));
        data.push_back(Point(3.081f, -0.6117f));
        data.push_back(Point(0.2641f, 0.3989f));
        data.push_back(Point(1.3204f, 2.2074f));
        data.push_back(Point(0.1937f, 3.6436f));
        data.push_back(Point(1.9542f, -0.5053f));
        data.push_back(Point(1.6373f, 1.4096f));
        data.push_back(Point(-0.1232f, -1.516f));
        data.push_back(Point(-1.3556f, -3.0585f));
        data.push_back(Point(0.0176f, -4.016f));
        data.push_back(Point(1.0035f, -3.5904f));
        data.push_back(Point(0.0176f, -2.4202f));
        data.push_back(Point(-1.5317f, -0.9309f));
        data.push_back(Point(-1.1444f, 0.5053f));
        data.push_back(Point(0.6162f, -1.516f));
        data.push_back(Point(1.7077f, -2.2074f));
        data.push_back(Point(2.0951f, 3.4309f));

        return data;
    }
};