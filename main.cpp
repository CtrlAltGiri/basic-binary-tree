#include "mining.h"

int main(){

    int rows, rareThreshold, freqThreshold, insertedRows = 0;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the rare threshold: ";
    cin >> rareThreshold;
    cout << "Enter the frequent threshold: ";
    cin >> freqThreshold;

    clock_t start, end;
    double cpu_time_used;
	start = clock();

    // STEP 1: CREATE THE TREE
    NODE root = PWCTreeConstruction(rows, insertedRows);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nINSERTION = %lf seconds\n", cpu_time_used);

    // STEP 2: MINE THE TREE
    map<vector<int>, int> freqTable;
    int rareRows = (rareThreshold * insertedRows) / 100;
    int freqRows = (freqThreshold * insertedRows) / 100;
    mineTree(root -> child, vector<vector<int>>(), freqTable);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("INSERTION + MINING = %lf seconds\n", cpu_time_used);

    // STEP 3: MEMORY CALCULATIONS
    printf("\nTotal Inserted Rows: %u\n", insertedRows);
	MemCalculate(root -> child);
	printf("Total Memory Usage: %lu bytes\n", MemUsage);

    // STEP 4: PICK THE FREQUENT AND RARE ITEMSETS
    ofstream frequent, rare;
    frequent.open("./output/frequent.txt");
    rare.open("./output/rare.txt");

    int primePos;
    for(auto i : freqTable){
        if(i.second > freqRows){
            for(int j = 0; j < i.first.size(); j++){
                // isPrime(i.first[j], &primePos);
                frequent << i.first[j] << ',';
            }
            frequent << "COUNT = " << i.second << endl;
        }

        else if(i.second > rareRows && i.second < freqRows){
            for(int j = 0; j < i.first.size(); j++){
                // isPrime(i.first[j], &primePos);
                rare << i.first[j] << ',';
            }
            rare << "COUNT = " << i.second << endl;
        }
    }
    cout << endl << "Frequent and Rare Itemsets are generated in the output folder." << endl << endl;
}
