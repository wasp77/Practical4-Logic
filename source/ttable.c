#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int num = atoi(argv[1]);
  char formula[1001];
  strcpy(formula, argv[2]);
  ttable(num, formula);
  return 0;
}

int ttable(int num, char* formula) {
  int rows = 2;
  for (int n = 1; n < num; n++) {
    rows = rows * 2;
  }

  int** tabel = make_2DArray(rows);
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
  int columns;

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
    columns = num;

    for (int z = 0; formula[z] != '\0'; z++) {
      switch (formula[z]) {
        case '|':
          list[index - 1] = list[index - 1] | list[index];
          tabel[x][columns] = list[index - 1];
          printf("%d", tabel[x][columns]);
          columns++;
          index--;
          break;
        case '&':
          list[index - 1] = list[index - 1] & list[index];
          tabel[x][columns] = list[index - 1];
          printf("%d", tabel[x][columns]);
          columns++;
          index--;
          break;
        case '#':
          list[index - 1] = list[index - 1] ^ list[index];
          tabel[x][columns] = list[index - 1];
          printf("%d", tabel[x][columns]);
          columns++;
          index--;
          break;
        case '>':
          list[index - 1] = implication(list[index - 1], list[index]);
          tabel[x][columns] = list[index - 1];
          printf("%d", tabel[x][columns]);
          columns++;
          index--;
          break;
        case '=':
          list[index - 1] = equals(list[index - 1], list[index]);
          tabel[x][columns] = list[index - 1];
          printf("%d", tabel[x][columns]);
          columns++;
          index--;
          break;
        case '-':
          list[index] = negation(list[index]);
          tabel[x][columns] = list[index];
          printf("%d", tabel[x][columns]);
          columns++;
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
    printf(" :   %d\n", list[index]);
  }
}


int** make_2DArray(int length) { // Alocate the 2D array bearing in mind it is a pointer to a pointer
  int** the_array;
  the_array = malloc(length * sizeof(int*));
  for (int i = 0; i < 1500; i++) {
    the_array[i] = malloc(length * sizeof(int));
  }
  return the_array;
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
