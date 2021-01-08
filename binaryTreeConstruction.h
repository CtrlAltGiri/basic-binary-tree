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
cout<<"\nCHeck: "<<tempValue<<"<-"<<root -> val<<" & "<<bitValue;
	if(tempValue == root -> val || tempValue == bitValue){
		if(bitValue == root -> val){
			// Equal case
			cout<<": Return -1\n";
			return -1;
		}
		else{

			if(bitValue < root -> val){
				// root -> val > bitValue
				cout<<": Return 2\n";
				return 2;
			}
			else{

				// bitValue > root -> val
				cout<<": Return 1\n";
				return 1;
			}
		}
	}
	else{

		// Not divisible
		cout<<": Return 0\n";
		return 0;
	}
}

void moveNonFactorsright(NODE newNode, NODE traverse, bitset<NO_BITS> bitValue){

	NODE prev = traverse, newNodeRights = newNode, childlist=traverse;
	traverse = traverse -> right;
	
	while(traverse){
		if(!isDivisible(bitValue, traverse)){
			prev -> right = traverse -> right;
			newNodeRights -> right = traverse;
			traverse -> right = NULL;
			newNodeRights = traverse;
			traverse = prev -> right;
		}
		else{
			prev = prev -> right;
			traverse -> val= traverse -> val ^ bitValue;
			newNode->qty+=traverse ->qty;
			traverse = traverse -> right;
		}
	}
	//newNode->child=childlist;
		
}

void insertIntoTree(NODE root, bitset<NO_BITS> bitValue){
static int noCount=0;
noCount++;
cout<<"\n insert transaction "<<noCount<<endl;
	// FIRST NODE
	if(root -> child == NULL){
		NODE newNode = createNode(bitValue, 1, NULL, NULL);
		root -> child = newNode;
		
		printf("\nthe first node bit is %d ",(int)(bitValue.to_ulong()));

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
					cout<<"\n 111:::"<<traverse -> val <<"^"<< bitValue;
					bitValue= traverse -> val ^ bitValue;	
					cout<<"===="<<bitValue<<endl;			//Added by SR
					// CHECK - prev -> child = traverse;
					prev = traverse;
					traverse -> qty++;
					traverse = traverse -> child;
					continue;
				}

				NODE newNode;
			 	if(divisible == 1){
					// IMP - removeFactorsArray(&values, &traverse, &count,1);	// remove from values.
					//printf("\nthe node bit is %d ",(int)(bitValue.to_ulong()));
					bitValue = traverse -> val ^ bitValue;				//Added by SR
					prev -> child = traverse;
					newNode = createNode(bitValue, 1, NULL, NULL);
					traverse -> child = newNode;

					cout<<"\n("<<bitValue<<")"<<"Child ("<<traverse->val<<")";

					traverse -> qty++;
					complete = 1;

				}

				else{
					// IMP - removeFactorsArray(&values,&traverse,&count,2);	 // remove from traverse.
					traverse -> val= traverse -> val ^ bitValue;				//Added by SR
					newNode = createNode(bitValue, traverse -> qty + 1, traverse, NULL);

					prev -> child = newNode;
	
cout<<"\n("<<bitValue<<")"<<"Child ("<<prev->val<<")";
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

							cout<<"\n("<<bitValue<<")"<<"Right ("<<traverse->val<<")";
							return;

						case 1:
							newNode = createNode(bitValue, 1, NULL, NULL);
							newNode -> qty += travTemp -> qty;
							traverse -> right = newNode;
							
							cout<<"\n("<<bitValue<<")"<<"Right ("<<traverse->val<<")";

							//traverse -> val = traverse -> val ^ bitValue;				//added by SR
							// IMP - removeCommonFactorsNodes(&travTemp, newNode);
							travTemp->val=newNode->val^travTemp->val;
							newNode -> child = travTemp;
							cout<<" Child is "<<travTemp->val;

							moveNonFactorsright(newNode, travTemp, bitValue);

							return;

						case 2:
							travTemp -> qty++;
							if(travTemp -> child == NULL){
								bitValue = travTemp -> val ^ bitValue;
								cout<<"\n("<<bitValue<<") to";	//added by SR
								newNode = createNode(bitValue, 1, NULL, NULL); // create and add here.
								// IMP - removeCommonFactorsNodes(&newNode, travTemp);
								travTemp -> child = newNode;

								cout<<" Transaction ("<<bitValue<<")"<<"Child ("<<travTemp->val<<")";
								return;
							}
							else{
								prev = travTemp;
								bitValue = travTemp -> val ^ bitValue;					//added by SR
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

	for(int i = 0; i < rows; i++){

		if(fgets(line, 10000, stream) == NULL)
			break;

		cols = 0;
		char* tmp = strdup(line);

		const char* tok = strtok(tmp, ",");
		
		for (; tok && *tok; tok = strtok(NULL, ",\n")){
			data[cols++] = atoi(tok);
		}

		bitset<NO_BITS> bitValue;

		for(int k = 0; k < cols; k++){
			bitValue.set(data[k]);
		}
if(i==3195)
		cout<<bitValue.size();
		/*if(i % 100 == 0){
			cout << i << ',';
		}*/

		insertIntoTree(root, bitValue);
        insertedRows++;

	}
	free(line);
	fclose(stream);

	return root;
}
