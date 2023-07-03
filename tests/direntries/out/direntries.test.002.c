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

int Find(char* haystack, char* needle);
typedef struct {
  char* result1;
  char* result2;
} Split_results;
Split_results Split(char* s);
bool EndsWith(char* text, char* suffix);

int Find(char* haystack, char* needle) {
  if ((strlen(needle)) == (0)) {
    return 0;
  }
  if ((strlen(haystack)) < (strlen(needle))) {
    return -(1);
  }
  int c = needle[0];
  int i = 0;
  while ((i) <= ((strlen(haystack)) - (strlen(needle)))) {
    if ((haystack[i]) != (c)) {
      i = (i) + (1);
      continue;
    } else {
      int tmp_strlen801 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str801 = calloc(tmp_strlen801, sizeof(char));
      strncpy(tmp_str801, haystack + i, tmp_strlen801 - 1);
      tmp_str801[tmp_strlen801 - 1] = 0;
      if ((strcmp(tmp_str801, needle) != 0)) {
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
  int tmp_strlen549 = (i) - (0) + 1;
  char* tmp_str549 = calloc(tmp_strlen549, sizeof(char));
  strncpy(tmp_str549, s + 0, tmp_strlen549 - 1);
  tmp_str549[tmp_strlen549 - 1] = 0;
  int tmp_strlen542 = (strlen(s)) - ((i) + (1)) + 1;
  char* tmp_str542 = calloc(tmp_strlen542, sizeof(char));
  strncpy(tmp_str542, s + (i) + (1), tmp_strlen542 - 1);
  tmp_str542[tmp_strlen542 - 1] = 0;
  return (Split_results){tmp_str549, tmp_str542};
}

bool EndsWith(char* text, char* suffix) {
  if ((strlen(text)) < (strlen(suffix))) {
    return false;
  } else {
    if ((strlen(text)) == (strlen(suffix))) {
      return (strcmp(text, suffix) == 0);
    } else {
      int tmp_strlen323 = (strlen(text)) - ((strlen(text)) - (strlen(suffix))) + 1;
      char* tmp_str323 = calloc(tmp_strlen323, sizeof(char));
      strncpy(tmp_str323, text + (strlen(text)) - (strlen(suffix)), tmp_strlen323 - 1);
      tmp_str323[tmp_strlen323 - 1] = 0;
      return (strcmp(tmp_str323, suffix) == 0);
    }
  }
}


bool expect(bool expectation, char* expectation_text);
bool expectIEq(int actual, int expected, char* expectation_text);
bool testFind();
bool testSplit();

bool expect(bool expectation, char* expectation_text) {
  if (expectation) {
    return true;
  }
  int tmp_strlen808 = strlen(" Failed expect(") + strlen(expectation_text) + 1;
  char* tmp_str808 = calloc(tmp_strlen808, sizeof(char));
  strcpy(tmp_str808, " Failed expect(");
  strcat(tmp_str808, expectation_text);
  int tmp_strlen799 = strlen(tmp_str808) + strlen(")\n") + 1;
  char* tmp_str799 = calloc(tmp_strlen799, sizeof(char));
  strcpy(tmp_str799, tmp_str808);
  strcat(tmp_str799, ")\n");
  printf("%s", tmp_str799);
  return false;
}

bool expectIEq(int actual, int expected, char* expectation_text) {
  if ((actual) == (expected)) {
    return true;
  }
  int tmp_strlen596 = strlen(" Failed expectIEq(") + strlen(expectation_text) + 1;
  char* tmp_str596 = calloc(tmp_strlen596, sizeof(char));
  strcpy(tmp_str596, " Failed expectIEq(");
  strcat(tmp_str596, expectation_text);
  int tmp_strlen573 = strlen(tmp_str596) + strlen("), actual value: ") + 1;
  char* tmp_str573 = calloc(tmp_strlen573, sizeof(char));
  strcpy(tmp_str573, tmp_str596);
  strcat(tmp_str573, "), actual value: ");
  int tmp_strlen557 = strlen(tmp_str573) + strlen(itoa(actual)) + 1;
  char* tmp_str557 = calloc(tmp_strlen557, sizeof(char));
  strcpy(tmp_str557, tmp_str573);
  strcat(tmp_str557, itoa(actual));
  int tmp_strlen549 = strlen(tmp_str557) + strlen("\n") + 1;
  char* tmp_str549 = calloc(tmp_strlen549, sizeof(char));
  strcpy(tmp_str549, tmp_str557);
  strcat(tmp_str549, "\n");
  printf("%s", tmp_str549);
  return false;
}

bool testFind() {
  bool _success = true;
  _success = expectIEq(Find("", ""), 0, "Find(\"\", \"\"), 0") && _success;
  _success = expectIEq(Find("abc", ""), 0, "Find(\"abc\", \"\"), 0") && _success;
  _success = expectIEq(Find("", "abc"), -(1), "Find(\"\", \"abc\"), -1") && _success;
  _success = expectIEq(Find("abc", "x"), -(1), "Find(\"abc\", \"x\"), -1") && _success;
  _success = expectIEq(Find("a", "xyz"), -(1), "Find(\"a\", \"xyz\"), -1") && _success;
  _success = expectIEq(Find("abc", "a"), 0, "Find(\"abc\", \"a\"), 0") && _success;
  _success = expectIEq(Find("abc", "b"), 1, "Find(\"abc\", \"b\"), 1") && _success;
  _success = expectIEq(Find("abc", "c"), 2, "Find(\"abc\", \"c\"), 2") && _success;
  _success = expectIEq(Find("abc", "ab"), 0, "Find(\"abc\", \"ab\"), 0") && _success;
  _success = expectIEq(Find("abc", "bc"), 1, "Find(\"abc\", \"bc\"), 1") && _success;
  _success = expectIEq(Find("abc", "abc"), 0, "Find(\"abc\", \"abc\"), 0") && _success;
  return _success;
}

bool testSplit() {
  bool _success = true;
  char* x;
  char* y;
  Split_results tmp_results65 = Split("a c");
  x = tmp_results65.result1;
  y = tmp_results65.result2;
  _success = expect((strcmp(x, "a") == 0), "x <> \"a\"") && _success;
  _success = expect((strcmp(y, "c") == 0), "y <> \"c\"") && _success;
  return _success;
}


int _main(char* args) {
  bool success = true;
  if ((testFind()) == (false)) {
    success = false;
    printf("%s", "[Fail] testFind\n");
  } else {
    printf("%s", "[ Ok ] testFind\n");
  }
  if ((testSplit()) == (false)) {
    success = false;
    printf("%s", "[Fail] testSplit\n");
  } else {
    printf("%s", "[ Ok ] testSplit\n");
  }
  if ((success) == (false)) {
    exit(1);
  }
  return 0;
}


