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
  FILE *f = fopen(path, "w");
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

int _main(char* args);
int factorial(int i);

int _main(char* args) {
  int i = 1;
  while ((i) <= (10)) {
    int tmp_strlen162 = strlen(itoa(i)) + strlen("! = ") + 1;
    char* tmp_str162 = calloc(tmp_strlen162, sizeof(char));
    strcpy(tmp_str162, itoa(i));
    strcat(tmp_str162, "! = ");
    int tmp_strlen139 = strlen(tmp_str162) + strlen(itoa(factorial(10))) + 1;
    char* tmp_str139 = calloc(tmp_strlen139, sizeof(char));
    strcpy(tmp_str139, tmp_str162);
    strcat(tmp_str139, itoa(factorial(10)));
    int tmp_strlen131 = strlen(tmp_str139) + strlen("\n") + 1;
    char* tmp_str131 = calloc(tmp_strlen131, sizeof(char));
    strcpy(tmp_str131, tmp_str139);
    strcat(tmp_str131, "\n");
    printf("%s", tmp_str131);
    i = (i) + (1);
  }
  return 0;
}

int factorial(int i) {
  if ((i) == (1)) {
    return 1;
  }
  return (i) * (factorial((i) - (1)));
}


