/*-------------------------------------------------------
 *
 * Maximum size square sub-matrix
 * Date : 03/13/2016
 * -----------------------------------------------------*/

#include <iostream>

#define M 2
#define N 2
#define min(a, b, c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

using namespace std;

class Solution {
	
	int sub[M][N];

	public :

	int maximum_sub_matrix(int data[][N]) {

		int i;
		int j;

		for (i = 0; i < M; i++) 
			sub[i][0] = data[i][0];

		for (i = 0; i < N; i++) 
			sub[0][i] = data[0][i];

		for (i = 1; i < M; i++)
			for (j = 1; j < N; j++) {
				if (data[i][j]) 
					sub[i][j] = min(sub[i-1][j-1], sub[i][j-1], sub[i-1][j]) + 1;
				else
					sub[i][j] = data[i][j];
			}
		
		int max   = -1;
		int i_max = -1;
		int j_max = -1;

		for (i = 0; i < M; i++) {
			for (j = 0; j < N; j++) {
				if (max < sub[i][j]) {
					max = sub[i][j];
					i_max = i;
					j_max = j;
				}
			}
		}

		cout << max << " " << i_max << " " << j_max << endl;
	
		for (i = i_max; i > (i_max - max); i--) {
			for (j = j_max; j > (j_max - max); j--) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}	
	}
	
};

int main(void) {
/*
	int data[M][N] = { {1, 1, 1, 1},
			   {1, 1, 1, 1},
			   {1, 1, 1, 1},
			   {1, 1, 1, 1},
		         };
*/	
/*	
	int data[M][N] = { {1, 1, 1},
			   {1, 1, 1},
			   {1, 1, 1},
			   {1, 1, 1},
		         };
*/		
/*
	int data[M][N] = { {0, 0, 0},
			   {1, 0, 0},
			   {1, 1, 1},
			   {1, 1, 1},
		         };
*/		
/*
	int data[M][N] = { {0, 0, 0},
			   {0, 0, 0},
			   {0, 0, 0},
			   {0, 0, 1},
			 };
*/
	int data[M][N] = { {0, 0},
			   {0, 0}
			 };
	
	Solution *sol = new Solution();
	sol->maximum_sub_matrix(data);
	delete sol;	
	return 0;
}

