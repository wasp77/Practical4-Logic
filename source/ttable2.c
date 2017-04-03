#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int num = atoi(argv[1]);
  char formula[1001];
  char formula2[1001];
  if (strlen(argv[2]) > 1000) {
    printf("The formula is too long\n");
    return 4;
  }

  if (argc == 4) {
    strcpy(formula, argv[2]);
    strcpy(formula2, argv[3]);
    compare(formula, formula2);
  } else if (argc > 4) {
    printf("Too many arguements passed\n");
    return 4;
  } else {
    strcpy(formula, argv[2]);
    ttable(num, formula);
  }
  return 0;
}

int ttable(int num, char* formula) {
  int rows = 2;
  for (int n = 1; n < num; n++) {
    rows = rows * 2;
  }

  int tabel[rows][num];
  Letter letter_list[26];

  int count = 0;
  int output_count = 0;

  for (char c = 'a'; c <= 'z'; c++) {
    letter_list[count].designation = c;
    if (count < num) {
      printf("%c ", c);
      output_count = output_count + 2;
    }
    count++;
  }

  char title[1050];
  strcpy(title, ": ");
  strcat(title, formula);
  strcat(title, " : Result");
  printf("%s\n", title);

  output_count = output_count + strlen(title);

  for (int j = 0; j < output_count; j++) {
    printf("=");
  }
  printf("\n");

  int list[1001];
  int results[rows];

  for (int x = 0; x < rows; x++) {
    int counter = 0;
    for (int t = num - 1; t >= 0; t--) {
      tabel[x][counter] = ((x >> t) & 1);
      letter_list[counter].val = tabel[x][counter];
      counter++;
    }

    for (int column = 0; column < num; column++) {
      printf("%d ", tabel[x][column]);
    }
    printf(": ");

    int index = -1;

    for (int z = 0; formula[z] != '\0'; z++) {
      switch (formula[z]) {
        case '|':
          list[index - 1] = list[index - 1] | list[index];
          printf("%d", list[index - 1]);
          index--;
          break;
        case '&':
          list[index - 1] = list[index - 1] & list[index];
          printf("%d", list[index - 1]);
          index--;
          break;
        case '#':
          list[index - 1] = list[index - 1] ^ list[index];
          printf("%d", list[index - 1]);
          index--;
          break;
        case '>':
          list[index - 1] = implication(list[index - 1], list[index]);
          printf("%d", list[index - 1]);
          index--;
          break;
        case '=':
          list[index - 1] = equals(list[index - 1], list[index]);
          printf("%d", list[index - 1]);
          index--;
          break;
        case '-':
          list[index] = negation(list[index]);
          printf("%d", list[index]);
          break;
        case '1':
          index++;
          list[index] = 1;
          printf(" ");
          break;
        case '0':
          index++;
          list[index] = 0;
          printf(" ");
          break;
        default :
          for (int i = 0; i < 26; i++) {
            if (formula[z] == letter_list[i].designation) {
              index++;
              list[index] = letter_list[i].val;
              printf(" ");
              break;
            }
          }
      }
    }
    results[x] = list[index];
    printf(" :   %d\n", list[index]);
  }

  status(results, rows);
}

int implication(int num1, int num2) {
  if (num1 == 0 && num2 == 0) {
    return 1;
  } else if (num1 == 0 && num2 == 1) {
    return 1;
  } else if (num1 == 1 && num2 == 0) {
    return 0;
  } else {
    return 1;
  }
}

int equals(int num1, int num2) {
  if (num1 == num2) {
    return 1;
  } else {
    return 0;
  }
}

int negation(int num) {
  if (num == 1) {
    return 0;
  } else {
    return 1;
  }
}

void status(int* results, int length) {
  int true_count = 0;
  int false_count = 0;

  for (int i = 0; i < length; i++) {
    if (results[i] == 1) {
      true_count++;
    } else {
      false_count++;
    }
  }

  if (false_count > 0 && true_count == 0) {
    printf("The formula is invalid and unsatisfiable\n");
  } else if (false_count > 0 && true_count > 0) {
    printf("The formula is invalid and satisfiable\n");
  } else {
    printf("The formula is valid\n");
  }

}

int compare(char* str1, char* str2) {
  int length1 = strlen(str1);
  int length2 = strlen(str2);

  if (length1 == length2) {
    for (int n = 0; n < length1; n++) {
      if (str1[n] != str2[n]) {
        printf("Input strings are not equivalent\n");
        return 0;
      }
    }
    printf("Input strings are equivalent\n");
  } else {
    printf("Input strings are not equivalent\n");
    return 0;
  }
  
  return 1;
}
