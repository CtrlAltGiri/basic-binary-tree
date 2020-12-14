#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include "structures.h"

using namespace std;

template<std::size_t N>
bool operator<(const std::bitset<N>& x, const std::bitset<N>& y)
{
    for (int i = N-1; i >= 0; i--) {
        if (x[i] ^ y[i]) return y[i];
    }
    return false;
}

NODE createNode(bitset<NO_BITS> bitValue, int qty, NODE child, NODE right){
	NODE newNode = new node;
	newNode -> val = bitValue;
	newNode -> qty = qty;
	newNode -> child = child;
	newNode -> right = right;

	return newNode;
}

int isDivisible(bitset<NO_BITS> bitValue, NODE root){
	bitset<NO_BITS> tempValue = root -> val & bitValue;
	if(tempValue == root -> val || tempValue == bitValue){
		if(bitValue == root -> val){
			// Equal case
			return -1;
		}
		else{

			if(bitValue < root -> val)
				// root -> val > bitValue
				return 2;
			else
				// bitValue > root -> val
				return 1;
		}
	}
	else{
		// Not divisible
		return 0;
	}
}

void moveNonFactorsright(NODE newNode, NODE traverse, bitset<NO_BITS> bitValue){

	NODE prev = traverse, newNodeRights = newNode;
	traverse = traverse -> right;
	while(traverse){
		if(!isDivisible(bitValue, traverse)){
			prev -> right = traverse -> right;
			newNodeRights -> right = traverse;
			traverse -> right = NULL;
			newNodeRights = traverse;
			traverse = prev -> right;
			// prev remains the same
		}
		else{
			prev = prev -> right;
			traverse = traverse -> right;
		}
	}
}

void insertIntoTree(NODE root, bitset<NO_BITS> bitValue, vector<int>values, int count){

	// FIRST NODE
	if(root -> child == NULL){
		NODE newNode = createNode(bitValue, 1, NULL, NULL);
		root -> child = newNode;
	}

	else{
		NODE traverse = root -> child, prev = root;
		int complete = 0, divisible;

		while(!complete){
			divisible = isDivisible(bitValue, traverse);

			// case 1 - is Divisible
			if(divisible){

				if(divisible == -1){
					traverse -> qty++;
					complete = 1;
					return;
				}

				else if(divisible == 1 && traverse -> child != NULL){
					// IMP - removeFactorsArray(&values, &traverse, &count, 1);
					prev -> child = traverse;
					prev = traverse;
					traverse -> qty++;
					traverse = traverse -> child;
					continue;
				}

				NODE newNode;
			 	if(divisible == 1){
					// IMP - removeFactorsArray(&values, &traverse, &count,1);	// remove from values.
					prev -> child = traverse;
					newNode = createNode(bitValue, 1, NULL, NULL);
					traverse -> child = newNode;
					traverse -> qty++;
					complete = 1;
				}

				else{
					// IMP - removeFactorsArray(&values,&traverse,&count,2);	 // remove from traverse.
					newNode = createNode(bitValue, traverse -> qty + 1, traverse, NULL);
					prev -> child = newNode;
					moveNonFactorsright(newNode, traverse, bitValue);
					complete = 1;
				}
			}

			//case 2 - not divisible
			else{
				int flag = -1;
				NODE travTemp;

				while(flag == -1){

					travTemp = traverse -> right;

					if(travTemp == NULL)
						break;

					else{ // if encountered is r.
						int x = isDivisible(bitValue, travTemp);
						if(x == -1){
							travTemp -> qty++;
							return;
						}
						else if(x){
							flag = (x == 1)? 2 : 1;
						}
						else{
							traverse = travTemp; // this is alright i think - can optimize
						}
					}
				}

				if(flag){
					NODE newNode;
					switch(flag){
						case -1:
							newNode = createNode(bitValue, 1, NULL, NULL);
							traverse -> right = newNode;
							return;

						case 1:
							newNode = createNode(bitValue, 1, NULL, NULL);
							newNode -> qty += travTemp -> qty;
							traverse -> right = newNode;

							// IMP - removeCommonFactorsNodes(&travTemp, newNode);
							newNode -> child = travTemp;

							moveNonFactorsright(newNode, travTemp, bitValue);
							return;

						case 2:
							travTemp -> qty++;
							if(travTemp -> child == NULL){
								newNode = createNode(bitValue, 1, NULL, NULL); // create and add here.
								// IMP - removeCommonFactorsNodes(&newNode, travTemp);
								travTemp -> child = newNode;
								return;
							}
							else{
								prev = travTemp;
								// IMP - removeFactorsArray(&values, &travTemp, &count, 1);
								traverse = travTemp-> child;
								continue;
							}
							break;
					}
				}
			}
		} // close of while(!complete) loop
	} // else close (main else)
}


NODE PWCTreeConstruction(int rows, int &insertedRows){

	NODE root;
	root = (NODE)malloc(sizeof(struct node));
	root -> val = bitset<NO_BITS>(0);
	root -> qty = 0;
	root -> child = root -> right = NULL;

	// Reading the data
	vector<int> data(MAX_LIMIT);
	int cols;
	FILE* stream = fopen(fileName, "r");
    char *line = (char*)malloc(sizeof(char) * 10000);

	unsigned int greaterThanPrev;
	for(int i = 0; i < rows; i++){

		if(fgets(line, 10000, stream) == NULL)
			break;

		cols = 0;
		char* tmp = strdup(line);

		const char* tok = strtok(tmp, ",");
		greaterThanPrev = 1;
		for (; tok && *tok; tok = strtok(NULL, ",\n")){
			data[cols++] = atoi(tok);
			if(greaterThanPrev){
				if(greaterThanPrev < data[cols - 1])
					greaterThanPrev = data[cols - 1];
				else
					greaterThanPrev = 0;
			}
		}

		bitset<NO_BITS> bitValue;
		for(int i = 0; i < cols; i++){
			bitValue.set(data[i]);
		}

		if(i % 100 == 0){
			cout << i << ',';
		}

		insertIntoTree(root, bitValue, data, cols);

	}
	free(line);
	fclose(stream);

	return root;
}
