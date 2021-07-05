/*
In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one with a different size r x c keeping its original data.
You are given an m x n matrix mat and two integers r and c representing the row number and column number of the wanted reshaped matrix.
The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.
If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

Example 1:

Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]
Example 2:

Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
-1000 <= mat[i][j] <= 1000
1 <= r, c <= 300

Solution : Store all elements in 1-D matrix & repopulate the new matrix. Before that, make sure r * c == number of elements in original matrix,
else return original matrix.
*/

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        vector<vector<int>> res(r, vector<int> (c, 0));
        int rowsize = mat.size(), colsize = mat[0].size(), i = 0, j = 0;
        vector<int> temp;
        
        for (i = 0; i < rowsize; i++) {
            for (j = 0; j < colsize; j++) {
                temp.push_back(mat[i][j]);
            }
        }
        
        i = 0;
        j = 0;
        //cout<<"lll";
        if (temp.size() != r * c)
            return mat;
        for (int k = 0; k < temp.size(); k++) {
            res[i][j] = temp[k];
            j++;
            if (j == c) {
                j = 0;
                i++;
            }
            //cout<<i<<" "<<j<<endl;
        }
        
        return res;
    }
};
