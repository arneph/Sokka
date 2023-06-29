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
int _main(char* args);
void test();

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

int _main(char* args) {
  int tmp_strlen393 = strlen("Hello world!") + strlen("\n") + 1;
  char* tmp_str393 = calloc(tmp_strlen393, sizeof(char));
  strcpy(tmp_str393, "Hello world!");
  strcat(tmp_str393, "\n");
  printf("%s", tmp_str393);
  substrTest();
  lenTest();
  test();
  myFunc("??\n", false);
  char* a;
  char* b;
  yolo_results tmp_results297 = yolo("!", "?");
  a = tmp_results297.result1;
  b = tmp_results297.result2;
  int tmp_strlen258 = strlen(a) + strlen("\n") + 1;
  char* tmp_str258 = calloc(tmp_strlen258, sizeof(char));
  strcpy(tmp_str258, a);
  strcat(tmp_str258, "\n");
  printf("%s", tmp_str258);
  int tmp_strlen239 = strlen(b) + strlen("\n") + 1;
  char* tmp_str239 = calloc(tmp_strlen239, sizeof(char));
  strcpy(tmp_str239, b);
  strcat(tmp_str239, "\n");
  printf("%s", tmp_str239);
  char* tmp;
  tmp = b;
  b = a;
  a = tmp;
  int tmp_strlen178 = strlen(a) + strlen("\n") + 1;
  char* tmp_str178 = calloc(tmp_strlen178, sizeof(char));
  strcpy(tmp_str178, a);
  strcat(tmp_str178, "\n");
  printf("%s", tmp_str178);
  int tmp_strlen159 = strlen(b) + strlen("\n") + 1;
  char* tmp_str159 = calloc(tmp_strlen159, sizeof(char));
  strcpy(tmp_str159, b);
  strcat(tmp_str159, "\n");
  printf("%s", tmp_str159);
  ifTest();
  forTest();
  printf("%s", "Goodbye world!\n");
  return 0;
}

void test() {
  int tmp_strlen62 = strlen("abc") + strlen("\n") + 1;
  char* tmp_str62 = calloc(tmp_strlen62, sizeof(char));
  strcpy(tmp_str62, "abc");
  strcat(tmp_str62, "\n");
  char* x = tmp_str62;
  int y = (123) + (456);
  bool z = false;
  printf("%s", x);
}


