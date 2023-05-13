#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char* text = malloc(length);
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

const bool evolution = true;
const int kHowdieStart = 16;

void myFunc(char* x, bool y);
int compA(int a, int b);
typedef struct {
    int result1;
    int result2;
}compB_results;
compB_results compB(int a, int b);
typedef struct {
    char* result1;
    char* result2;
}yolo_results;
yolo_results yolo(char* a, char* b);
bool boolTest();
bool precendenceTest();
void ifTest();
void forTest();
int four();
void substrTest();
void lenTest();
int main();
void test();

void myFunc(char* x, bool y) {
    char* a = "xyz";
    int tmp_strlen2043 = strlen(a) + strlen(x);
    char* tmp_str2043 = calloc(tmp_strlen2043, sizeof(char));
    strcat(tmp_str2043, a);
    strcat(tmp_str2043, x);
    printf("%s", tmp_str2043);
}

int compA(int a, int b) {
    return (a) + (b);
}

compB_results compB(int a, int b) {
    return (compB_results){(a) / (b), (a) % (b)};
}

yolo_results yolo(char* a, char* b) {
    int tmp_strlen1853 = strlen(a) + strlen(b);
    char* tmp_str1853 = calloc(tmp_strlen1853, sizeof(char));
    strcat(tmp_str1853, a);
    strcat(tmp_str1853, b);
    int tmp_strlen1845 = strlen(b) + strlen(a);
    char* tmp_str1845 = calloc(tmp_strlen1845, sizeof(char));
    strcat(tmp_str1845, b);
    strcat(tmp_str1845, a);
    return (yolo_results){tmp_str1853, tmp_str1845};
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
            int tmp_strlen992 = strlen(s) + strlen("!");
            char* tmp_str992 = calloc(tmp_strlen992, sizeof(char));
            strcat(tmp_str992, s);
            strcat(tmp_str992, "!");
            s = tmp_str992;
            i = (i) + (1);
            continue;
        }
        int tmp_strlen935 = strlen(s) + strlen("\n");
        char* tmp_str935 = calloc(tmp_strlen935, sizeof(char));
        strcat(tmp_str935, s);
        strcat(tmp_str935, "\n");
        printf("%s", tmp_str935);
        int tmp_strlen917 = strlen(s) + strlen("!");
        char* tmp_str917 = calloc(tmp_strlen917, sizeof(char));
        strcat(tmp_str917, s);
        strcat(tmp_str917, "!");
        s = tmp_str917;
        i = (i) + (1);
    }
    s = "Bye!";
    i = 1;
    while (true) {
        int tmp_strlen850 = strlen(s) + strlen("\n");
        char* tmp_str850 = calloc(tmp_strlen850, sizeof(char));
        strcat(tmp_str850, s);
        strcat(tmp_str850, "\n");
        printf("%s", tmp_str850);
        int tmp_strlen832 = strlen(s) + strlen("!");
        char* tmp_str832 = calloc(tmp_strlen832, sizeof(char));
        strcat(tmp_str832, s);
        strcat(tmp_str832, "!");
        s = tmp_str832;
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
    int tmp_strlen615 = (four()) - (0) + 1;
    char* tmp_str615 = calloc(tmp_strlen615, sizeof(char));
    strncpy(tmp_str615, s + 0, tmp_strlen615 - 1);
    tmp_str615[tmp_strlen615 - 1] = 0;
    int tmp_strlen598 = strlen(tmp_str615) + strlen("\n");
    char* tmp_str598 = calloc(tmp_strlen598, sizeof(char));
    strcat(tmp_str598, tmp_str615);
    strcat(tmp_str598, "\n");
    printf("%s", tmp_str598);
    int tmp_strlen587 = (15) - ((2) + (3)) + 1;
    char* tmp_str587 = calloc(tmp_strlen587, sizeof(char));
    strncpy(tmp_str587, s + (2) + (3), tmp_strlen587 - 1);
    tmp_str587[tmp_strlen587 - 1] = 0;
    int tmp_strlen571 = strlen(tmp_str587) + strlen("\n");
    char* tmp_str571 = calloc(tmp_strlen571, sizeof(char));
    strcat(tmp_str571, tmp_str587);
    strcat(tmp_str571, "\n");
    printf("%s", tmp_str571);
    int tmp_strlen560 = (strlen(s)) - (kHowdieStart) + 1;
    char* tmp_str560 = calloc(tmp_strlen560, sizeof(char));
    strncpy(tmp_str560, s + kHowdieStart, tmp_strlen560 - 1);
    tmp_str560[tmp_strlen560 - 1] = 0;
    printf("%s", tmp_str560);
}

void lenTest() {
    char* s = "ABCDEFGHIJK";
    int tmp_strlen486 = (strlen("abc")) - (0) + 1;
    char* tmp_str486 = calloc(tmp_strlen486, sizeof(char));
    strncpy(tmp_str486, s + 0, tmp_strlen486 - 1);
    tmp_str486[tmp_strlen486 - 1] = 0;
    int tmp_strlen465 = strlen(tmp_str486) + strlen("\n");
    char* tmp_str465 = calloc(tmp_strlen465, sizeof(char));
    strcat(tmp_str465, tmp_str486);
    strcat(tmp_str465, "\n");
    printf("%s", tmp_str465);
    int tmp_strlen454 = (strlen(s)) - (0) + 1;
    char* tmp_str454 = calloc(tmp_strlen454, sizeof(char));
    strncpy(tmp_str454, s + 0, tmp_strlen454 - 1);
    tmp_str454[tmp_strlen454 - 1] = 0;
    int tmp_strlen437 = strlen(tmp_str454) + strlen("\n");
    char* tmp_str437 = calloc(tmp_strlen437, sizeof(char));
    strcat(tmp_str437, tmp_str454);
    strcat(tmp_str437, "\n");
    printf("%s", tmp_str437);
}

int main() {
    int tmp_strlen392 = strlen("Hello world!") + strlen("\n");
    char* tmp_str392 = calloc(tmp_strlen392, sizeof(char));
    strcat(tmp_str392, "Hello world!");
    strcat(tmp_str392, "\n");
    printf("%s", tmp_str392);
    substrTest();
    lenTest();
    test();
    myFunc("??\n", false);
    char* a;
    char* b;
    yolo_results tmp_results296 = yolo("!", "?");
    a = tmp_results296.result1;
    b = tmp_results296.result2;
    int tmp_strlen257 = strlen(a) + strlen("\n");
    char* tmp_str257 = calloc(tmp_strlen257, sizeof(char));
    strcat(tmp_str257, a);
    strcat(tmp_str257, "\n");
    printf("%s", tmp_str257);
    int tmp_strlen238 = strlen(b) + strlen("\n");
    char* tmp_str238 = calloc(tmp_strlen238, sizeof(char));
    strcat(tmp_str238, b);
    strcat(tmp_str238, "\n");
    printf("%s", tmp_str238);
    char* tmp;
    tmp = b;
    b = a;
    a = tmp;
    int tmp_strlen177 = strlen(a) + strlen("\n");
    char* tmp_str177 = calloc(tmp_strlen177, sizeof(char));
    strcat(tmp_str177, a);
    strcat(tmp_str177, "\n");
    printf("%s", tmp_str177);
    int tmp_strlen158 = strlen(b) + strlen("\n");
    char* tmp_str158 = calloc(tmp_strlen158, sizeof(char));
    strcat(tmp_str158, b);
    strcat(tmp_str158, "\n");
    printf("%s", tmp_str158);
    ifTest();
    forTest();
    printf("%s", "Goodbye world!\n");
}

void test() {
    int tmp_strlen61 = strlen("abc") + strlen("\n");
    char* tmp_str61 = calloc(tmp_strlen61, sizeof(char));
    strcat(tmp_str61, "abc");
    strcat(tmp_str61, "\n");
    char* x = tmp_str61;
    int y = (123) + (456);
    bool z = false;
    printf("%s", x);
}


