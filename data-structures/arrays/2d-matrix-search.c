// https://leetcode.com/problems/search-a-2d-matrix/?envType=problem-list-v2&envId=array
//
// Problem:
// - Search for an integer within a matrix within O(log(m * n)) time; i.e. the set should get exponentially smaller with each new iteration
// - Each row is in increasing order
// - The first integer of each row is larger than the integer of the previous row
//
// Approach:
// - Because each row is in increasing order and each new row contains integers larger than the previous, we can check the input against the beginning and end of each row
// - If the input is not >= the first integer and <= last integer move to the next row and run the same check
// - Once it's in range, binary search on the row to see if the integer is there.
// - Produce true if yes, an false if no
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void freeMatrix(int** matrix, int* matrixColSize, int m);
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target);

int main(void)
{
    int m, n;
    printf("Enter matrix dimensions (m n): ");
    if (scanf("%d %d", &m, &n) != 2) {
        printf("Error: Invalid dimensions\n");
        return 1;
    }

    // Allocate matrix
    int** matrix = (int**)malloc(m * sizeof(int*));
    int* matrixColSize = (int*)malloc(m * sizeof(int));
    if (!matrix || !matrixColSize) {
        printf("Error: Memory allocation failed\n");
        freeMatrix(matrix, matrixColSize, 0);
        return 1;
    }

    // Allocate each row and initialize matrixColSize
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (!matrix[i]) {
            printf("Error: Memory allocation failed\n");
            freeMatrix(matrix, matrixColSize, i);
            return 1;
        }
        matrixColSize[i] = n;
    }

    // Read matrix values
    printf("Enter matrix values row by row (each row must be sorted):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Error: Invalid input\n");
                freeMatrix(matrix, matrixColSize, m);
                return 1;
            }
            // Verify row is sorted
            if (j > 0 && matrix[i][j] <= matrix[i][j-1]) {
                printf("Error: Row must be in strictly increasing order\n");
                freeMatrix(matrix, matrixColSize, m);
                return 1;
            }
        }
        // Verify first element is greater than last element of previous row
        if (i > 0 && matrix[i][0] <= matrix[i-1][n-1]) {
            printf("Error: First element of row must be greater than last element of previous row\n");
            freeMatrix(matrix, matrixColSize, m);
            return 1;
        }
    }

    int target;
    printf("Enter target value to search for: ");
    if (scanf("%d", &target) != 1) {
        printf("Error: Invalid target\n");
        freeMatrix(matrix, matrixColSize, m);
        return 1;
    }

    bool found = searchMatrix(matrix, m, matrixColSize, target);
    printf("Target %d was %sfound in matrix\n", target, found ? "" : "not ");
    freeMatrix(matrix, matrixColSize, m);

    return 0;
}

// Memory cleanup
void freeMatrix(int** matrix, int* matrixColSize, int m) {
    if (matrix) {
        for (int i = 0; i < m; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    free(matrixColSize);
}

// O(log(m * n)) matrix search
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    if (!matrixSize || !matrixColSize[0]) return false;

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int left = 0;
    int right = (rows * cols) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / cols;  // Get row index from 1D position
        int col = mid % cols;  // Get column index from 1D position

        if (matrix[row][col] == target) {
            return true;
        }
        if (matrix[row][col] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}
