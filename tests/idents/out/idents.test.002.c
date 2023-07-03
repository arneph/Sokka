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

void f();
void g();

void f() {
}

void g() {
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


