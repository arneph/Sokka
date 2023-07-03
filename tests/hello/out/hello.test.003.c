#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char* itoa(int x) {
  char* a = malloc(20);
  sprintf(a, "%i", x);
  return a;
}

char* read(const char* path) {
  FILE* f = fopen(path, "rb");
  if (f == NULL) {
    printf("could not open file: %s\n", path);
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  int length = ftell(f);
  char* text = malloc(length + 1);
  fseek(f, 0, SEEK_SET);
  fread(text, 1, length, f);
  fclose(f);
  return text;
}

void write(const char* path, const char* text) {
  FILE *f = fopen(path, "w+");
  if (f == NULL) {
    printf("could not open file: %s\n", path);
    exit(1);
  }
  fprintf(f, "%s", text);
  fclose(f);
}

char* direntries(const char* path) {
  DIR *d;
  d = opendir(path);
  if (!d) {
    printf("could not open dir: %s\n", path);
    exit(1);
  }
  struct dirent *dir;
  char *entries = calloc(10000, sizeof(char));
  char* a = entries;
  while ((dir = readdir(d)) != NULL) {
    int c = strlen(dir->d_name);
    strncpy(a, dir->d_name, c);
    a += c;
    a[0] = ' ';
    a += 1;
  }
  a[-1] = 0;
  closedir(d);
  return entries;
}

int _main(char* args);

int main(int argc, char **argv) {
  int l = 0;
  for (int i = 1; i < argc; i++) {
    l += strlen(argv[i]) + 1;
  }
  char* args = calloc(l, sizeof(char));
  char* a = args;
  for (int i = 1; i < argc; i++) {
    int c = strlen(argv[i]);
    strncpy(a, argv[i], c);
    a += c;
    a[0] = ' ';
    a += 1;
  }
  args[l-1] = 0;
  return _main(args);
}

const bool evolution = true;
const int kHowdieStart = 16;

void myFunc(char* x, bool y);
int compA(int a, int b);
typedef struct {
  int result1;
  int result2;
} compB_results;
compB_results compB(int a, int b);
typedef struct {
  char* result1;
  char* result2;
} yolo_results;
yolo_results yolo(char* a, char* b);
bool boolTest();
bool precendenceTest();
void ifTest();
void forTest();
int four();
void substrTest();
void lenTest();
bool test();

void myFunc(char* x, bool y) {
  char* a = "xyz";
  int tmp_strlen2044 = strlen(a) + strlen(x) + 1;
  char* tmp_str2044 = calloc(tmp_strlen2044, sizeof(char));
  strcpy(tmp_str2044, a);
  strcat(tmp_str2044, x);
  printf("%s", tmp_str2044);
}

int compA(int a, int b) {
  return (a) + (b);
}

compB_results compB(int a, int b) {
  return (compB_results){(a) / (b), (a) % (b)};
}

yolo_results yolo(char* a, char* b) {
  int tmp_strlen1854 = strlen(a) + strlen(b) + 1;
  char* tmp_str1854 = calloc(tmp_strlen1854, sizeof(char));
  strcpy(tmp_str1854, a);
  strcat(tmp_str1854, b);
  int tmp_strlen1846 = strlen(b) + strlen(a) + 1;
  char* tmp_str1846 = calloc(tmp_strlen1846, sizeof(char));
  strcpy(tmp_str1846, b);
  strcat(tmp_str1846, a);
  return (yolo_results){tmp_str1854, tmp_str1846};
}

bool boolTest() {
  const bool a = false;
  bool b;
  bool c;
  bool d;
  return ((a) && (b)) || ((c) && (d));
}

bool precendenceTest() {
  int a;
  int b;
  int c;
  int d;
  int x;
  int y;
  int z;
  int t = ((1) + (2)) - (3);
  return ((strcmp("abc", "xyz") == 0)) || (((false) && ((((z) | ((y) ^ ((x) & ((a) + (((b) / (c)) % (d)))))) < (123)) == ((strcmp("123", "yo") != 0)))) && (true));
}

void ifTest() {
  printf("%s", "ifTest starting\n");
  if ((12) < (23)) {
    printf("%s", "12 is less than 23\n");
  } else {
    if ((23) < (34)) {
      printf("%s", "23 is less than 34\n");
    } else {
      printf("%s", "12 is not less than 23, which is not less than 34\n");
    }
  }
  if (false) {
    printf("%s", "This should never happen.\n");
  }
  printf("%s", "ifTest completed\n");
}

void forTest() {
  printf("%s", "forTest starting\n");
  int i = 1;
  char* s = "Hello!";
  while ((i) <= (10)) {
    if (((i) % (2)) == (0)) {
      int tmp_strlen993 = strlen(s) + strlen("!") + 1;
      char* tmp_str993 = calloc(tmp_strlen993, sizeof(char));
      strcpy(tmp_str993, s);
      strcat(tmp_str993, "!");
      s = tmp_str993;
      i = (i) + (1);
      continue;
    }
    int tmp_strlen936 = strlen(s) + strlen("\n") + 1;
    char* tmp_str936 = calloc(tmp_strlen936, sizeof(char));
    strcpy(tmp_str936, s);
    strcat(tmp_str936, "\n");
    printf("%s", tmp_str936);
    int tmp_strlen918 = strlen(s) + strlen("!") + 1;
    char* tmp_str918 = calloc(tmp_strlen918, sizeof(char));
    strcpy(tmp_str918, s);
    strcat(tmp_str918, "!");
    s = tmp_str918;
    i = (i) + (1);
  }
  s = "Bye!";
  i = 1;
  while (true) {
    int tmp_strlen851 = strlen(s) + strlen("\n") + 1;
    char* tmp_str851 = calloc(tmp_strlen851, sizeof(char));
    strcpy(tmp_str851, s);
    strcat(tmp_str851, "\n");
    printf("%s", tmp_str851);
    int tmp_strlen833 = strlen(s) + strlen("!") + 1;
    char* tmp_str833 = calloc(tmp_strlen833, sizeof(char));
    strcpy(tmp_str833, s);
    strcat(tmp_str833, "!");
    s = tmp_str833;
    i = (i) + (1);
    if ((i) > (5)) {
      break;
    }
  }
  printf("%s", "forTest completed\n");
}

int four() {
  return 4;
}

void substrTest() {
  char* s = "Yolo What's up? Howdie\n";
  int tmp_strlen616 = (four()) - (0) + 1;
  char* tmp_str616 = calloc(tmp_strlen616, sizeof(char));
  strncpy(tmp_str616, s + 0, tmp_strlen616 - 1);
  tmp_str616[tmp_strlen616 - 1] = 0;
  int tmp_strlen599 = strlen(tmp_str616) + strlen("\n") + 1;
  char* tmp_str599 = calloc(tmp_strlen599, sizeof(char));
  strcpy(tmp_str599, tmp_str616);
  strcat(tmp_str599, "\n");
  printf("%s", tmp_str599);
  int tmp_strlen588 = (15) - ((2) + (3)) + 1;
  char* tmp_str588 = calloc(tmp_strlen588, sizeof(char));
  strncpy(tmp_str588, s + (2) + (3), tmp_strlen588 - 1);
  tmp_str588[tmp_strlen588 - 1] = 0;
  int tmp_strlen572 = strlen(tmp_str588) + strlen("\n") + 1;
  char* tmp_str572 = calloc(tmp_strlen572, sizeof(char));
  strcpy(tmp_str572, tmp_str588);
  strcat(tmp_str572, "\n");
  printf("%s", tmp_str572);
  int tmp_strlen561 = (strlen(s)) - (kHowdieStart) + 1;
  char* tmp_str561 = calloc(tmp_strlen561, sizeof(char));
  strncpy(tmp_str561, s + kHowdieStart, tmp_strlen561 - 1);
  tmp_str561[tmp_strlen561 - 1] = 0;
  printf("%s", tmp_str561);
}

void lenTest() {
  char* s = "ABCDEFGHIJK";
  int tmp_strlen487 = (strlen("abc")) - (0) + 1;
  char* tmp_str487 = calloc(tmp_strlen487, sizeof(char));
  strncpy(tmp_str487, s + 0, tmp_strlen487 - 1);
  tmp_str487[tmp_strlen487 - 1] = 0;
  int tmp_strlen466 = strlen(tmp_str487) + strlen("\n") + 1;
  char* tmp_str466 = calloc(tmp_strlen466, sizeof(char));
  strcpy(tmp_str466, tmp_str487);
  strcat(tmp_str466, "\n");
  printf("%s", tmp_str466);
  int tmp_strlen455 = (strlen(s)) - (0) + 1;
  char* tmp_str455 = calloc(tmp_strlen455, sizeof(char));
  strncpy(tmp_str455, s + 0, tmp_strlen455 - 1);
  tmp_str455[tmp_strlen455 - 1] = 0;
  int tmp_strlen438 = strlen(tmp_str455) + strlen("\n") + 1;
  char* tmp_str438 = calloc(tmp_strlen438, sizeof(char));
  strcpy(tmp_str438, tmp_str455);
  strcat(tmp_str438, "\n");
  printf("%s", tmp_str438);
}

bool test() {
  bool _success = true;
  int tmp_strlen62 = strlen("abc") + strlen("\n") + 1;
  char* tmp_str62 = calloc(tmp_strlen62, sizeof(char));
  strcpy(tmp_str62, "abc");
  strcat(tmp_str62, "\n");
  char* x = tmp_str62;
  int y = (123) + (456);
  bool z = false;
  printf("%s", x);
  return _success;
}


bool expect(bool expectation, char* expectation_text);
bool expectIEq(int actual, int expected, char* expectation_text);

bool expect(bool expectation, char* expectation_text) {
  if (expectation) {
    return true;
  }
  int tmp_strlen281 = strlen(" Failed expect(") + strlen(expectation_text) + 1;
  char* tmp_str281 = calloc(tmp_strlen281, sizeof(char));
  strcpy(tmp_str281, " Failed expect(");
  strcat(tmp_str281, expectation_text);
  int tmp_strlen272 = strlen(tmp_str281) + strlen(")\n") + 1;
  char* tmp_str272 = calloc(tmp_strlen272, sizeof(char));
  strcpy(tmp_str272, tmp_str281);
  strcat(tmp_str272, ")\n");
  printf("%s", tmp_str272);
  return false;
}

bool expectIEq(int actual, int expected, char* expectation_text) {
  if ((actual) == (expected)) {
    return true;
  }
  int tmp_strlen69 = strlen(" Failed expectIEq(") + strlen(expectation_text) + 1;
  char* tmp_str69 = calloc(tmp_strlen69, sizeof(char));
  strcpy(tmp_str69, " Failed expectIEq(");
  strcat(tmp_str69, expectation_text);
  int tmp_strlen46 = strlen(tmp_str69) + strlen("), actual value: ") + 1;
  char* tmp_str46 = calloc(tmp_strlen46, sizeof(char));
  strcpy(tmp_str46, tmp_str69);
  strcat(tmp_str46, "), actual value: ");
  int tmp_strlen30 = strlen(tmp_str46) + strlen(itoa(actual)) + 1;
  char* tmp_str30 = calloc(tmp_strlen30, sizeof(char));
  strcpy(tmp_str30, tmp_str46);
  strcat(tmp_str30, itoa(actual));
  int tmp_strlen22 = strlen(tmp_str30) + strlen("\n") + 1;
  char* tmp_str22 = calloc(tmp_strlen22, sizeof(char));
  strcpy(tmp_str22, tmp_str30);
  strcat(tmp_str22, "\n");
  printf("%s", tmp_str22);
  return false;
}


int _main(char* args) {
  bool success = true;
  if ((success) == (false)) {
    exit(1);
  }
  return 0;
}


