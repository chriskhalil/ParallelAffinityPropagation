#include <cstdio>
#include <cstdlib>
#include <vector>
#include "AffinityPropagation.h"
#include <fstream>

using namespace std;

int main() {
	FILE* myfile;
	fopen_s(&myfile, "./sim.txt", "r");
	if (myfile !=nullptr){
		AffinityPropagation af(myfile, 0.9);
	std::vector<int> examplar = af.Run(1000,50) ;
	for (size_t i = 0; i < examplar.size(); ++i) {
		printf("%d ", examplar[i]);
	}
	
	}
	return 0;
}