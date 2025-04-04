// https://leetcode.com/problems/find-the-difference/?envType=problem-list-v2&envId=string
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char findTheDifference(char* s, char* t);
void generateSecondString(char* s, char* t);

int main()
{
    char s[1000], t[1001];  // t is one char longer than s

    printf("Enter first string (s): ");
    scanf("%s", s);

    generateSecondString(s, t);
	printf("Generated string (t): %s\n", t);

    char diff = findTheDifference(s, t);
    printf("The different character is: %c\n", diff);

    return 0;
}

void generateSecondString(char* s, char* t) {
	int len = strlen(s);

	// Copy s into t
	strcpy(t, s);

	// Initialize random seed
	srand(time(NULL));

	// Generate random character to insert
	char randomChar = 'a' + (rand() % 26);

	// Pick random position to insert the character (0 to len inclusive)
	int insertPos = rand() % (len + 1);

	// Shift characters to make space for new char
	for (int i = len; i >= insertPos; i--) {
		t[i + 1] = t[i];
	}

	// Insert random char
	t[insertPos] = randomChar;

	// Shuffle the entire string (Fisher-Yates algorithm)
	len = len + 1; // New length after insertion
	for (int i = len - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char temp = t[i];
		t[i] = t[j];
		t[j] = temp;
	}

	t[len] = '\0';
}

char findTheDifference(char* s, char* t) {
  char result = 0;
  int i = 0;

  // XOR all chars in s
  while (s[i]) {
      result ^= s[i];
      i++;
  }

  // XOR all chars in t
  i = 0;
  while (t[i]) {
      result ^= t[i];
      i++;
  }

  return result;
}
