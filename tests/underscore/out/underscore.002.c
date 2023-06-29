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

typedef struct {
  bool result1;
  int result2;
  char* result3;
} t_results;
t_results t();
int _main(char* args);

t_results t() {
  return (t_results){true, 42, "hello world"};
}

int _main(char* args) {
  bool a;
  int b;
  char* c;
  t_results tmp_results124 = t();
  a = tmp_results124.result1;
  t_results tmp_results106 = t();
  b = tmp_results106.result2;
  t_results tmp_results88 = t();
  c = tmp_results88.result3;
  t_results tmp_results70 = t();
  a = tmp_results70.result1;
  b = tmp_results70.result2;
  t_results tmp_results52 = t();
  a = tmp_results52.result1;
  c = tmp_results52.result3;
  t_results tmp_results34 = t();
  b = tmp_results34.result2;
  c = tmp_results34.result3;
  t_results tmp_results16 = t();
  a = tmp_results16.result1;
  b = tmp_results16.result2;
  c = tmp_results16.result3;
  return 0;
}


