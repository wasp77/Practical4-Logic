typedef struct Letter {
  char designation;
  int val;
} Letter;

int** make_2DArray(int length);
int ttable(int length, int num, char* formula);
int implication(int num1, int num2);
int equals(int num1, int num2);
int negation(int num);
void status(int* results, int length);
int compare(char* str1, char* str2);
