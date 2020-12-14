#include "binaryTreeConstruction.h"

using namespace std;

/*void findAllCombinations(int* arr, int size, int reqLen, vector<vector<int>> &allCombinations, int start, int currLen, vector<bool> check){

	if(currLen > reqLen){
		return;
	}

 	if (currLen == reqLen){
        allCombinations.push_back({});
        int index = allCombinations.size() - 1;
		for(int i = 0; i < size; i++){
			if(check[i]){
				allCombinations[index].push_back(arr[i]);
			}
		}
		return;
	}

	if (start == size){
		return;
	}

	// For every index we have two options.
	// First is, we select it, means put true in check[] and increment currLen and start.
	check[start] = true;
	findAllCombinations(arr, size, reqLen, allCombinations, start + 1, currLen + 1, check);

	// Second is, we don't select it, means put false in check[] and only start incremented.
	check[start] = false;
	findAllCombinations(arr, size, reqLen, allCombinations, start + 1, currLen, check);
}

void joinOperationPowerSet(vector<vector<int>> &combinationsSoFar, int* primesOfRoot, int n, map<vector<int>, int> &freqTable, unsigned int qty){

    // Find all the combinations of the new node.
    vector<vector<int>> allCombinations;
    for(int i = 1; i <= n; i++){
        vector<bool> check(n);
        findAllCombinations(primesOfRoot, n, i, allCombinations, 0, 0, check);
    }

    // Main Join operation algo
    int combinationsSoFarSize = combinationsSoFar.size();
    vector<int> newCombination;
    for(int i = 0; i < combinationsSoFarSize; i++){
        for(int j = 0; j < allCombinations.size(); j++){

            newCombination = combinationsSoFar[i];
            newCombination.insert(newCombination.end(), allCombinations[j].begin(), allCombinations[j].end());

            sort(newCombination.begin(), newCombination.end());

            combinationsSoFar.push_back(newCombination);
            freqTable[newCombination] += qty;
        }
    }

    // All basic factors as well
    for(int i = 0; i < allCombinations.size(); i++){
        combinationsSoFar.push_back(allCombinations[i]);
        freqTable[allCombinations[i]] += qty;
    }
}

void mineTree(NODE root, vector<vector<int>> combinationsSoFar, map<vector<int>, int> &freqTable){

    if(!root){
        return;
    }

    int n = 0;
    int *primesOfRoot = (int*) malloc(sizeof(int) * MAX_LIMIT);
    findFactorsNode(primesOfRoot, &n, root);
    sort(primesOfRoot, n);

    // Mine the right node
    if(root -> flag == 'r'){
        mineTree(findRightMost(root) -> RIGHT, combinationsSoFar, freqTable);
    }
    else{
        mineTree(root -> RIGHT, combinationsSoFar, freqTable);
    }

    // Find the ultimate powerset + add to the freqTable
    joinOperationPowerSet(combinationsSoFar, primesOfRoot, n, freqTable, root -> qty);

    // Mine the child
    mineTree(root -> CHILD, combinationsSoFar, freqTable);

    free(primesOfRoot);
}
*/

void MemCalculate(NODE root){

}
