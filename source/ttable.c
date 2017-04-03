#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static int alphabet_num = 26;

int main(int argc, char *argv[]) {
  int num = atoi(argv[1]);
  int length = strlen(argv[2]);
  char formula[length];
  if (strlen(argv[2]) > 1000) {
    printf("The formula is too long\n");
    return 4;
  }
  if (argc > 3) {
    printf("Too many arguements passed\n");
    return 4;
  }
  strcpy(formula, argv[2]);
  ttable(length, num, formula);
  return 0;
}

int ttable(int length, int num, char* formula) {
  int rows = 2;
  for (int n = 1; n < num; n++) {
    rows = rows * 2;
  }

  int tabel[rows][num];
  Letter letter_list[alphabet_num];

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

  char title[length + 11];
  strcpy(title, ": ");
  strcat(title, formula);
  strcat(title, " : Result");

  printf("%s\n", title);
  output_count = output_count + strlen(title);

  for (int j = 0; j < output_count; j++) {
    printf("=");
  }
  printf("\n");

  int list[length];

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
          for (int i = 0; i < alphabet_num; i++) {
            if (formula[z] == letter_list[i].designation) {
              index++;
              list[index] = letter_list[i].val;
              printf(" ");
              break;
            }
          }
      }
    }
    printf(" :   %d\n", list[index]);
  }
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
