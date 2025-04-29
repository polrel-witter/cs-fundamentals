#include <stdio.h>

void merge(int src1[], int src2[], int dest[], int n);

int main(void)
{
    int src1[] = {1, 3, 5, 7};
    int src2[] = {2, 4, 6, 8};
    int dest[8];
    int n = 4;

    merge(src1, src2, dest, n);

    printf("Merged array: ");
    for(int i = 0; i < n*2; i++) {
      printf("%d ", dest[i]);
    }
    printf("\n");

    return 0;
}

void merge(int src1[], int src2[], int dest[], int n)
{
    int i1 = 0;
    int i2 = 0;
    int id = 0;
    while (i1 < n && i2 < n)
        // Ternary used to invoke a conditional move in assembly to avoid misprediction branching
        dest[id++] = src1[i1] < src2[i2] ? src1[i1++] : src2[i2++];
    while (i1 < n)
        dest[id++] = src1[i1++];
    while (i2 < n)
        dest[id++] = src2[i2++];
}
