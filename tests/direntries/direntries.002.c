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

int Find(char* haystack, char* needle);
typedef struct {
  char* result1;
  char* result2;
} Split_results;
Split_results Split(char* s);
bool EndsWith(char* text, char* suffix);
int _main(char* args);

int Find(char* haystack, char* needle) {
  if ((strlen(needle)) == (0)) {
    return 0;
  }
  int c = needle[0];
  int i = 0;
  while ((i) <= ((strlen(haystack)) - (strlen(needle)))) {
    if ((haystack[i]) != (c)) {
      i = (i) + (1);
      continue;
    } else {
      int tmp_strlen800 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str800 = calloc(tmp_strlen800, sizeof(char));
      strncpy(tmp_str800, haystack + i, tmp_strlen800 - 1);
      tmp_str800[tmp_strlen800 - 1] = 0;
      if ((strcmp(tmp_str800, needle) != 0)) {
        i = (i) + (1);
        continue;
      }
    }
    return i;
  }
  return -(1);
}

Split_results Split(char* s) {
  const int i = Find(s, " ");
  if ((i) == (-(1))) {
    return (Split_results){s, ""};
  }
  int tmp_strlen548 = (i) - (0) + 1;
  char* tmp_str548 = calloc(tmp_strlen548, sizeof(char));
  strncpy(tmp_str548, s + 0, tmp_strlen548 - 1);
  tmp_str548[tmp_strlen548 - 1] = 0;
  int tmp_strlen541 = (strlen(s)) - ((i) + (1)) + 1;
  char* tmp_str541 = calloc(tmp_strlen541, sizeof(char));
  strncpy(tmp_str541, s + (i) + (1), tmp_strlen541 - 1);
  tmp_str541[tmp_strlen541 - 1] = 0;
  return (Split_results){tmp_str548, tmp_str541};
}

bool EndsWith(char* text, char* suffix) {
  if ((strlen(text)) < (strlen(suffix))) {
    return false;
  } else {
    if ((strlen(text)) == (strlen(suffix))) {
      return (strcmp(text, suffix) == 0);
    } else {
      int tmp_strlen322 = (strlen(text)) - ((strlen(text)) - (strlen(suffix))) + 1;
      char* tmp_str322 = calloc(tmp_strlen322, sizeof(char));
      strncpy(tmp_str322, text + (strlen(text)) - (strlen(suffix)), tmp_strlen322 - 1);
      tmp_str322[tmp_strlen322 - 1] = 0;
      return (strcmp(tmp_str322, suffix) == 0);
    }
  }
}

int _main(char* args) {
  char* entries = direntries(".");
  char* entry;
  Split_results tmp_results186 = Split(entries);
  entry = tmp_results186.result1;
  entries = tmp_results186.result2;
  while ((strlen(entries)) > (0)) {
    if (EndsWith(entry, ".txt")) {
      int tmp_strlen59 = strlen(entry) + strlen("\n") + 1;
      char* tmp_str59 = calloc(tmp_strlen59, sizeof(char));
      strcpy(tmp_str59, entry);
      strcat(tmp_str59, "\n");
      printf("%s", tmp_str59);
    }
    Split_results tmp_results39 = Split(entries);
    entry = tmp_results39.result1;
    entries = tmp_results39.result2;
  }
  return 0;
}


