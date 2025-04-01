// https://leetcode.com/problems/container-with-most-water/description/?envType=problem-list-v2&envId=array

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int size;
    printf("Enter the number of heights: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size\n");
        return;
    }

    // Dynamically allocate array
    int* height = (int*)malloc(size * sizeof(int));
    if (height == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Get height values
    printf("Enter %d heights:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &height[i]) != 1) {
            printf("Invalid input\n");
            free(height);
            return;
        }
    }

    // Calculate and print result
    int result = maxArea(height, size);
    printf("Maximum water container area: %d\n", result);

    // Free allocated memory
    free(height);
}

int maxArea(int* height, int heightSize) {
  int left = 0;
  int right = heightSize - 1;
  int maxWater = 0;

  while (left < right) {
      // Calculate width between lines
      int width = right - left;
      // Calculate height (limited by shorter line)
      int h = height[left] < height[right] ? height[left] : height[right];
      // Calculate and update max area if larger
      int area = width * h;
      if (area > maxWater) {
          maxWater = area;
      }

      // Move pointer of smaller height inward
      if (height[left] < height[right]) {
          left++;
      } else {
          right--;
      }
  }

  return maxWater;
}
