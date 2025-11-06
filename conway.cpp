#include <iostream>
#include<vector>
using namespace std;

// matrix print
void mprint(vector<vector<int>>& matrix){
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix.size(); j++){
			// printf uses less resources than cout
			if (matrix[i][j]){
				printf("#");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	printf("\n");
}
// check whether the cell is in bounds
bool isValid(int row, int col, vector<vector<int>>& matrix){
	if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix.size()){
		return true;	
	} else {
		return false;
	}
}
// calculate the matrix for the next generation
void calculateGen(vector<vector<int>>& currmatrix, vector<vector<int>>& matrix, vector<vector<int>>& directions){
	int n = matrix.size();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			int alive = 0;
			// for each cell, go over neighbors and calculate n of live cells
			for (vector<int> direction : directions){
				int nrow = direction[0] + i;
				int ncol = direction[1] + j;
				if (isValid(nrow, ncol, matrix)){
					if (matrix[nrow][ncol] == 1){
						alive += 1;
					}
				}
			}
			// apply conway's game of life rules
			// for live cell
			if (matrix[i][j] == 1){
				// <2 death
				if (alive < 2) currmatrix[i][j] = 0;
				// ==2 ==3 lives
				if (alive == 2 || alive == 3) currmatrix[i][j] = 1;
				// >3 death
				if (alive > 3) currmatrix[i][j] = 0;
			// for dead cell
			} else {
				if (alive == 3) currmatrix[i][j] = 1;
			}
		}	
	}
	// copy currmatrix to matrix cell by cell
	// reset currmatrix to all zeros
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++ ){
			matrix[i][j] = currmatrix[i][j];
			currmatrix[i][j] = 0;
		}
	}
}
int main(){
	// matrix size
	int n = 10;
	vector<vector<int>> matrix(n, vector(n, 0)); 
	vector<vector<int>> currmatrix(n, vector(n, 0));
	vector<vector<int>> directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
	// painting glider
	matrix[3][3] = 1;
	matrix[3][4] = 1;
	matrix[3][5] = 1;
	matrix[2][5] = 1;
	matrix[1][4] = 1;

	int generations = 15;
	for (int i = 0; i < generations; i++){
		calculateGen(currmatrix, matrix, directions);
		cout << "Generation " << i << endl;
		mprint(matrix);
	}
	return 0;
}
