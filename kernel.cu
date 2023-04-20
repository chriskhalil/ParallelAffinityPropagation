#include "AffinityPropagation.h"

__global__ void availabilities_kernel(){

}

void updateAvailabilities_GPU(Edges* inEdges){


    // availabilities_kernel <<< numBlocks, numThreadsPerBlock >>> (A_d, B_d, C_d, M, N, K);
}