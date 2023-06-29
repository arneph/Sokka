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

const int TOK_NEWLINE = 0;
const int TOK_EOF = 1;
const int TOK_FN = 100;
const int TOK_LET = 101;
const int TOK_VAR = 102;
const int TOK_IF = 103;
const int TOK_ELSE = 104;
const int TOK_FOR = 105;
const int TOK_CONTINUE = 106;
const int TOK_BREAK = 107;
const int TOK_RETURN = 108;
const int TOK_BOOL = 110;
const int TOK_INT = 111;
const int TOK_STRING = 112;
const int TOK_FALSE = 120;
const int TOK_TRUE = 121;
const int TOK_LPAREN = 200;
const int TOK_RPAREN = 201;
const int TOK_LBRACKET = 202;
const int TOK_RBRACKET = 203;
const int TOK_LCURLY = 204;
const int TOK_RCURLY = 205;
const int TOK_UNDERSCORE = 210;
const int TOK_COLON = 211;
const int TOK_COMMA = 212;
const int TOK_ASSIGN = 213;
const int TOK_RARROW = 214;
const int TOK_BNOT = 220;
const int TOK_BOR = 221;
const int TOK_BAND = 222;
const int TOK_ADD = 230;
const int TOK_SUB = 231;
const int TOK_MUL = 232;
const int TOK_DIV = 233;
const int TOK_REM = 234;
const int TOK_INOT = 235;
const int TOK_IOR = 236;
const int TOK_IAND = 237;
const int TOK_IXOR = 238;
const int TOK_EQ = 240;
const int TOK_NEQ = 241;
const int TOK_LESS = 242;
const int TOK_LEQ = 243;
const int TOK_GEQ = 244;
const int TOK_GREATER = 245;
const int TOK_STRCAT = 250;
const int TOK_STREQ = 251;
const int TOK_STRNEQ = 252;
const int TOK_IDENT = 300;
const int TOK_INTLIT = 301;
const int TOK_STRLIT = 302;
const int TYPE_BOOL = 1000;
const int TYPE_INT = 1001;
const int TYPE_STRING = 1002;
const char* SINGLE_INDENT = "  ";

bool IsUnaryOp(int tok);
bool IsBinaryOp(int tok);
int Precedence(int tok);
int Find(char* haystack, char* needle);
bool StartsWith(char* text, char* prefix);
bool EndsWith(char* text, char* suffix);
typedef struct {
  char* result1;
  char* result2;
} Split_results;
Split_results Split(char* s);
bool IsNumeric(int c);
bool IsAlpha(int c);
bool IsAlphaNumeric(int c);
char* RemoveLeadingWhitespace(char* text);
typedef struct {
  char* result1;
  int result2;
  char* result3;
} Next_results;
Next_results Next(char* src);
typedef struct {
  int result1;
  char* result2;
} Peek_results;
Peek_results Peek(char* src);
typedef struct {
  char* result1;
  char* result2;
} ConsumeToken_results;
ConsumeToken_results ConsumeToken(char* src, int expected_tok);
typedef struct {
  char* result1;
  char* result2;
} ConsumeIdent_results;
ConsumeIdent_results ConsumeIdent(char* src);
typedef struct {
  char* result1;
  char* result2;
} ConsumeIdentOrUnderscore_results;
ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src);
typedef struct {
  char* result1;
  int result2;
  char* result3;
} TranslateType_results;
TranslateType_results TranslateType(char* src);
typedef struct {
  char* result1;
  char* result2;
} TranslateBoolLiteral_results;
TranslateBoolLiteral_results TranslateBoolLiteral(char* src);
typedef struct {
  char* result1;
  char* result2;
} TranslateIntLiteral_results;
TranslateIntLiteral_results TranslateIntLiteral(char* src);
typedef struct {
  char* result1;
  char* result2;
} TranslateStringLiteral_results;
TranslateStringLiteral_results TranslateStringLiteral(char* src);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateCall_results;
TranslateCall_results TranslateCall(char* src, char* indent, char* callee);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateSubstrExpr_results;
TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateOperand_results;
TranslateOperand_results TranslateOperand(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateUnaryExpr_results;
TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateExprWithPrecedence_results;
TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateExpr_results;
TranslateExpr_results TranslateExpr(char* src, char* indent);
typedef struct {
  char* result1;
  int result2;
  char* result3;
  char* result4;
} TranslateExprs_results;
TranslateExprs_results TranslateExprs(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateConstOrVar_results;
TranslateConstOrVar_results TranslateConstOrVar(char* src);
typedef struct {
  char* result1;
  char* result2;
} TranslateConstDecl_results;
TranslateConstDecl_results TranslateConstDecl(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateConstDeclStmt_results;
TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateVarDeclStmt_results;
TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateAssignStmt_results;
TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateIfStmt_results;
TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name);
typedef struct {
  char* result1;
  char* result2;
} TranslateForStmt_results;
TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name);
typedef struct {
  char* result1;
  char* result2;
} TranslateContinueStmt_results;
TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateBreakStmt_results;
TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent);
typedef struct {
  char* result1;
  char* result2;
} TranslateReturnStmt_results;
TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name);
typedef struct {
  char* result1;
  char* result2;
} TranslateStmt_results;
TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name);
typedef struct {
  char* result1;
  char* result2;
} TranslateStmts_results;
TranslateStmts_results TranslateStmts(char* src, char* indent, char* func_name);
typedef struct {
  char* result1;
  char* result2;
} TranslateFuncArgs_results;
TranslateFuncArgs_results TranslateFuncArgs(char* src);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateFuncResults_results;
TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name);
typedef struct {
  char* result1;
  char* result2;
  char* result3;
} TranslateFunc_results;
TranslateFunc_results TranslateFunc(char* src);
char* TranslateProgram(char* src);
char* ReadSrc(char* src_dir);
int _main(char* args);

bool IsUnaryOp(int tok) {
  return (((((((((((((((((((tok) == (TOK_BOR)) || ((tok) == (TOK_BAND))) || ((tok) == (TOK_ADD))) || ((tok) == (TOK_SUB))) || ((tok) == (TOK_MUL))) || ((tok) == (TOK_DIV))) || ((tok) == (TOK_REM))) || ((tok) == (TOK_IOR))) || ((tok) == (TOK_IAND))) || ((tok) == (TOK_IXOR))) || ((tok) == (TOK_EQ))) || ((tok) == (TOK_NEQ))) || ((tok) == (TOK_LESS))) || ((tok) == (TOK_LEQ))) || ((tok) == (TOK_GEQ))) || ((tok) == (TOK_GREATER))) || ((tok) == (TOK_STRCAT))) || ((tok) == (TOK_STREQ))) || ((tok) == (TOK_STRNEQ));
}

bool IsBinaryOp(int tok) {
  return (((((((((((((((((((tok) == (TOK_BOR)) || ((tok) == (TOK_BAND))) || ((tok) == (TOK_ADD))) || ((tok) == (TOK_SUB))) || ((tok) == (TOK_MUL))) || ((tok) == (TOK_DIV))) || ((tok) == (TOK_REM))) || ((tok) == (TOK_IOR))) || ((tok) == (TOK_IAND))) || ((tok) == (TOK_IXOR))) || ((tok) == (TOK_EQ))) || ((tok) == (TOK_NEQ))) || ((tok) == (TOK_LESS))) || ((tok) == (TOK_LEQ))) || ((tok) == (TOK_GEQ))) || ((tok) == (TOK_GREATER))) || ((tok) == (TOK_STRCAT))) || ((tok) == (TOK_STREQ))) || ((tok) == (TOK_STRNEQ));
}

int Precedence(int tok) {
  if ((tok) == (TOK_BOR)) {
    return 1;
  } else {
    if ((tok) == (TOK_BAND)) {
      return 2;
    } else {
      if (((((((((tok) == (TOK_EQ)) || ((tok) == (TOK_NEQ))) || ((tok) == (TOK_LESS))) || ((tok) == (TOK_LEQ))) || ((tok) == (TOK_GEQ))) || ((tok) == (TOK_GREATER))) || ((tok) == (TOK_STREQ))) || ((tok) == (TOK_STRNEQ))) {
        return 3;
      } else {
        if ((tok) == (TOK_IOR)) {
          return 4;
        } else {
          if ((tok) == (TOK_IXOR)) {
            return 5;
          } else {
            if ((tok) == (TOK_IAND)) {
              return 6;
            } else {
              if ((((tok) == (TOK_ADD)) || ((tok) == (TOK_SUB))) || ((tok) == (TOK_STRCAT))) {
                return 7;
              } else {
                if ((((tok) == (TOK_MUL)) || ((tok) == (TOK_DIV))) || ((tok) == (TOK_REM))) {
                  return 8;
                } else {
                  int tmp_strlen28583 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str28583 = calloc(tmp_strlen28583, sizeof(char));
                  strcpy(tmp_str28583, "token has no defined precedence: ");
                  strcat(tmp_str28583, itoa(tok));
                  printf("%s", tmp_str28583);
                  exit(1);
                }
              }
            }
          }
        }
      }
    }
  }
}

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
      int tmp_strlen28268 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str28268 = calloc(tmp_strlen28268, sizeof(char));
      strncpy(tmp_str28268, haystack + i, tmp_strlen28268 - 1);
      tmp_str28268[tmp_strlen28268 - 1] = 0;
      if ((strcmp(tmp_str28268, needle) != 0)) {
        i = (i) + (1);
        continue;
      }
    }
    return i;
  }
  return -(1);
}

bool StartsWith(char* text, char* prefix) {
  if ((strlen(text)) < (strlen(prefix))) {
    return false;
  } else {
    if ((strlen(text)) == (strlen(prefix))) {
      return (strcmp(text, prefix) == 0);
    } else {
      int tmp_strlen27933 = (strlen(prefix)) - (0) + 1;
      char* tmp_str27933 = calloc(tmp_strlen27933, sizeof(char));
      strncpy(tmp_str27933, text + 0, tmp_strlen27933 - 1);
      tmp_str27933[tmp_strlen27933 - 1] = 0;
      return (strcmp(tmp_str27933, prefix) == 0);
    }
  }
}

bool EndsWith(char* text, char* suffix) {
  if ((strlen(text)) < (strlen(suffix))) {
    return false;
  } else {
    if ((strlen(text)) == (strlen(suffix))) {
      return (strcmp(text, suffix) == 0);
    } else {
      int tmp_strlen27690 = (strlen(text)) - ((strlen(text)) - (strlen(suffix))) + 1;
      char* tmp_str27690 = calloc(tmp_strlen27690, sizeof(char));
      strncpy(tmp_str27690, text + (strlen(text)) - (strlen(suffix)), tmp_strlen27690 - 1);
      tmp_str27690[tmp_strlen27690 - 1] = 0;
      return (strcmp(tmp_str27690, suffix) == 0);
    }
  }
}

Split_results Split(char* s) {
  if ((strlen(s)) == (0)) {
    return (Split_results){"", ""};
  }
  const int i = Find(s, " ");
  if ((i) == (-(1))) {
    return (Split_results){s, ""};
  }
  int tmp_strlen27469 = (i) - (0) + 1;
  char* tmp_str27469 = calloc(tmp_strlen27469, sizeof(char));
  strncpy(tmp_str27469, s + 0, tmp_strlen27469 - 1);
  tmp_str27469[tmp_strlen27469 - 1] = 0;
  int tmp_strlen27462 = (strlen(s)) - ((i) + (1)) + 1;
  char* tmp_str27462 = calloc(tmp_strlen27462, sizeof(char));
  strncpy(tmp_str27462, s + (i) + (1), tmp_strlen27462 - 1);
  tmp_str27462[tmp_strlen27462 - 1] = 0;
  return (Split_results){tmp_str27469, tmp_str27462};
}

bool IsNumeric(int c) {
  return ((48) <= (c)) && ((c) <= (57));
}

bool IsAlpha(int c) {
  return (((65) <= (c)) && ((c) <= (90))) || (((97) <= (c)) && ((c) <= (122)));
}

bool IsAlphaNumeric(int c) {
  return (IsNumeric(c)) || (IsAlpha(c));
}

char* RemoveLeadingWhitespace(char* text) {
  while ((StartsWith(text, " ")) || (StartsWith(text, "\t"))) {
    int tmp_strlen27092 = (strlen(text)) - (1) + 1;
    char* tmp_str27092 = calloc(tmp_strlen27092, sizeof(char));
    strncpy(tmp_str27092, text + 1, tmp_strlen27092 - 1);
    tmp_str27092[tmp_strlen27092 - 1] = 0;
    text = tmp_str27092;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen26869 = (strlen(src)) - (2) + 1;
      char* tmp_str26869 = calloc(tmp_strlen26869, sizeof(char));
      strncpy(tmp_str26869, src + 2, tmp_strlen26869 - 1);
      tmp_str26869[tmp_strlen26869 - 1] = 0;
      return (Next_results){tmp_str26869, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen26790 = (strlen(src)) - (2) + 1;
        char* tmp_str26790 = calloc(tmp_strlen26790, sizeof(char));
        strncpy(tmp_str26790, src + 2, tmp_strlen26790 - 1);
        tmp_str26790[tmp_strlen26790 - 1] = 0;
        return (Next_results){tmp_str26790, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen26714 = (strlen(src)) - (2) + 1;
          char* tmp_str26714 = calloc(tmp_strlen26714, sizeof(char));
          strncpy(tmp_str26714, src + 2, tmp_strlen26714 - 1);
          tmp_str26714[tmp_strlen26714 - 1] = 0;
          return (Next_results){tmp_str26714, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen26637 = (strlen(src)) - (2) + 1;
            char* tmp_str26637 = calloc(tmp_strlen26637, sizeof(char));
            strncpy(tmp_str26637, src + 2, tmp_strlen26637 - 1);
            tmp_str26637[tmp_strlen26637 - 1] = 0;
            return (Next_results){tmp_str26637, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen26562 = (strlen(src)) - (2) + 1;
              char* tmp_str26562 = calloc(tmp_strlen26562, sizeof(char));
              strncpy(tmp_str26562, src + 2, tmp_strlen26562 - 1);
              tmp_str26562[tmp_strlen26562 - 1] = 0;
              return (Next_results){tmp_str26562, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen26486 = (strlen(src)) - (2) + 1;
                char* tmp_str26486 = calloc(tmp_strlen26486, sizeof(char));
                strncpy(tmp_str26486, src + 2, tmp_strlen26486 - 1);
                tmp_str26486[tmp_strlen26486 - 1] = 0;
                return (Next_results){tmp_str26486, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen26410 = (strlen(src)) - (2) + 1;
                  char* tmp_str26410 = calloc(tmp_strlen26410, sizeof(char));
                  strncpy(tmp_str26410, src + 2, tmp_strlen26410 - 1);
                  tmp_str26410[tmp_strlen26410 - 1] = 0;
                  return (Next_results){tmp_str26410, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen26334 = (strlen(src)) - (2) + 1;
                    char* tmp_str26334 = calloc(tmp_strlen26334, sizeof(char));
                    strncpy(tmp_str26334, src + 2, tmp_strlen26334 - 1);
                    tmp_str26334[tmp_strlen26334 - 1] = 0;
                    return (Next_results){tmp_str26334, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen26255 = (strlen(src)) - (2) + 1;
                      char* tmp_str26255 = calloc(tmp_strlen26255, sizeof(char));
                      strncpy(tmp_str26255, src + 2, tmp_strlen26255 - 1);
                      tmp_str26255[tmp_strlen26255 - 1] = 0;
                      return (Next_results){tmp_str26255, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen26176 = (strlen(src)) - (3) + 1;
                        char* tmp_str26176 = calloc(tmp_strlen26176, sizeof(char));
                        strncpy(tmp_str26176, src + 3, tmp_strlen26176 - 1);
                        tmp_str26176[tmp_strlen26176 - 1] = 0;
                        return (Next_results){tmp_str26176, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen26096 = (strlen(src)) - (1) + 1;
                          char* tmp_str26096 = calloc(tmp_strlen26096, sizeof(char));
                          strncpy(tmp_str26096, src + 1, tmp_strlen26096 - 1);
                          tmp_str26096[tmp_strlen26096 - 1] = 0;
                          return (Next_results){tmp_str26096, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen26017 = (strlen(src)) - (1) + 1;
                            char* tmp_str26017 = calloc(tmp_strlen26017, sizeof(char));
                            strncpy(tmp_str26017, src + 1, tmp_strlen26017 - 1);
                            tmp_str26017[tmp_strlen26017 - 1] = 0;
                            return (Next_results){tmp_str26017, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen25940 = (strlen(src)) - (1) + 1;
                              char* tmp_str25940 = calloc(tmp_strlen25940, sizeof(char));
                              strncpy(tmp_str25940, src + 1, tmp_strlen25940 - 1);
                              tmp_str25940[tmp_strlen25940 - 1] = 0;
                              return (Next_results){tmp_str25940, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen25863 = (strlen(src)) - (1) + 1;
                                char* tmp_str25863 = calloc(tmp_strlen25863, sizeof(char));
                                strncpy(tmp_str25863, src + 1, tmp_strlen25863 - 1);
                                tmp_str25863[tmp_strlen25863 - 1] = 0;
                                return (Next_results){tmp_str25863, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen25784 = (strlen(src)) - (1) + 1;
                                  char* tmp_str25784 = calloc(tmp_strlen25784, sizeof(char));
                                  strncpy(tmp_str25784, src + 1, tmp_strlen25784 - 1);
                                  tmp_str25784[tmp_strlen25784 - 1] = 0;
                                  return (Next_results){tmp_str25784, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen25705 = (strlen(src)) - (1) + 1;
                                    char* tmp_str25705 = calloc(tmp_strlen25705, sizeof(char));
                                    strncpy(tmp_str25705, src + 1, tmp_strlen25705 - 1);
                                    tmp_str25705[tmp_strlen25705 - 1] = 0;
                                    return (Next_results){tmp_str25705, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen25628 = (strlen(src)) - (1) + 1;
                                      char* tmp_str25628 = calloc(tmp_strlen25628, sizeof(char));
                                      strncpy(tmp_str25628, src + 1, tmp_strlen25628 - 1);
                                      tmp_str25628[tmp_strlen25628 - 1] = 0;
                                      return (Next_results){tmp_str25628, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, "_")) {
                                        int tmp_strlen25551 = (strlen(src)) - (1) + 1;
                                        char* tmp_str25551 = calloc(tmp_strlen25551, sizeof(char));
                                        strncpy(tmp_str25551, src + 1, tmp_strlen25551 - 1);
                                        tmp_str25551[tmp_strlen25551 - 1] = 0;
                                        return (Next_results){tmp_str25551, TOK_UNDERSCORE, "_"};
                                      } else {
                                        if (StartsWith(src, ":")) {
                                          int tmp_strlen25470 = (strlen(src)) - (1) + 1;
                                          char* tmp_str25470 = calloc(tmp_strlen25470, sizeof(char));
                                          strncpy(tmp_str25470, src + 1, tmp_strlen25470 - 1);
                                          tmp_str25470[tmp_strlen25470 - 1] = 0;
                                          return (Next_results){tmp_str25470, TOK_COLON, ":"};
                                        } else {
                                          if (StartsWith(src, ",")) {
                                            int tmp_strlen25394 = (strlen(src)) - (1) + 1;
                                            char* tmp_str25394 = calloc(tmp_strlen25394, sizeof(char));
                                            strncpy(tmp_str25394, src + 1, tmp_strlen25394 - 1);
                                            tmp_str25394[tmp_strlen25394 - 1] = 0;
                                            return (Next_results){tmp_str25394, TOK_COMMA, ","};
                                          } else {
                                            if (StartsWith(src, "=")) {
                                              int tmp_strlen25318 = (strlen(src)) - (1) + 1;
                                              char* tmp_str25318 = calloc(tmp_strlen25318, sizeof(char));
                                              strncpy(tmp_str25318, src + 1, tmp_strlen25318 - 1);
                                              tmp_str25318[tmp_strlen25318 - 1] = 0;
                                              return (Next_results){tmp_str25318, TOK_ASSIGN, "="};
                                            } else {
                                              if (StartsWith(src, "!")) {
                                                int tmp_strlen25241 = (strlen(src)) - (1) + 1;
                                                char* tmp_str25241 = calloc(tmp_strlen25241, sizeof(char));
                                                strncpy(tmp_str25241, src + 1, tmp_strlen25241 - 1);
                                                tmp_str25241[tmp_strlen25241 - 1] = 0;
                                                return (Next_results){tmp_str25241, TOK_BNOT, "!"};
                                              } else {
                                                if (StartsWith(src, "+")) {
                                                  int tmp_strlen25166 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str25166 = calloc(tmp_strlen25166, sizeof(char));
                                                  strncpy(tmp_str25166, src + 1, tmp_strlen25166 - 1);
                                                  tmp_str25166[tmp_strlen25166 - 1] = 0;
                                                  return (Next_results){tmp_str25166, TOK_ADD, "+"};
                                                } else {
                                                  if (StartsWith(src, "-")) {
                                                    int tmp_strlen25092 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str25092 = calloc(tmp_strlen25092, sizeof(char));
                                                    strncpy(tmp_str25092, src + 1, tmp_strlen25092 - 1);
                                                    tmp_str25092[tmp_strlen25092 - 1] = 0;
                                                    return (Next_results){tmp_str25092, TOK_SUB, "-"};
                                                  } else {
                                                    if (StartsWith(src, "*")) {
                                                      int tmp_strlen25018 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str25018 = calloc(tmp_strlen25018, sizeof(char));
                                                      strncpy(tmp_str25018, src + 1, tmp_strlen25018 - 1);
                                                      tmp_str25018[tmp_strlen25018 - 1] = 0;
                                                      return (Next_results){tmp_str25018, TOK_MUL, "*"};
                                                    } else {
                                                      if (StartsWith(src, "/")) {
                                                        int tmp_strlen24944 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str24944 = calloc(tmp_strlen24944, sizeof(char));
                                                        strncpy(tmp_str24944, src + 1, tmp_strlen24944 - 1);
                                                        tmp_str24944[tmp_strlen24944 - 1] = 0;
                                                        return (Next_results){tmp_str24944, TOK_DIV, "/"};
                                                      } else {
                                                        if (StartsWith(src, "%")) {
                                                          int tmp_strlen24870 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str24870 = calloc(tmp_strlen24870, sizeof(char));
                                                          strncpy(tmp_str24870, src + 1, tmp_strlen24870 - 1);
                                                          tmp_str24870[tmp_strlen24870 - 1] = 0;
                                                          return (Next_results){tmp_str24870, TOK_REM, "%"};
                                                        } else {
                                                          if (StartsWith(src, "~")) {
                                                            int tmp_strlen24796 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str24796 = calloc(tmp_strlen24796, sizeof(char));
                                                            strncpy(tmp_str24796, src + 1, tmp_strlen24796 - 1);
                                                            tmp_str24796[tmp_strlen24796 - 1] = 0;
                                                            return (Next_results){tmp_str24796, TOK_INOT, "~"};
                                                          } else {
                                                            if (StartsWith(src, "|")) {
                                                              int tmp_strlen24721 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str24721 = calloc(tmp_strlen24721, sizeof(char));
                                                              strncpy(tmp_str24721, src + 1, tmp_strlen24721 - 1);
                                                              tmp_str24721[tmp_strlen24721 - 1] = 0;
                                                              return (Next_results){tmp_str24721, TOK_IOR, "|"};
                                                            } else {
                                                              if (StartsWith(src, "&")) {
                                                                int tmp_strlen24647 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str24647 = calloc(tmp_strlen24647, sizeof(char));
                                                                strncpy(tmp_str24647, src + 1, tmp_strlen24647 - 1);
                                                                tmp_str24647[tmp_strlen24647 - 1] = 0;
                                                                return (Next_results){tmp_str24647, TOK_IAND, "&"};
                                                              } else {
                                                                if (StartsWith(src, "^")) {
                                                                  int tmp_strlen24572 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str24572 = calloc(tmp_strlen24572, sizeof(char));
                                                                  strncpy(tmp_str24572, src + 1, tmp_strlen24572 - 1);
                                                                  tmp_str24572[tmp_strlen24572 - 1] = 0;
                                                                  return (Next_results){tmp_str24572, TOK_IXOR, "^"};
                                                                } else {
                                                                  if (StartsWith(src, "<")) {
                                                                    int tmp_strlen24497 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str24497 = calloc(tmp_strlen24497, sizeof(char));
                                                                    strncpy(tmp_str24497, src + 1, tmp_strlen24497 - 1);
                                                                    tmp_str24497[tmp_strlen24497 - 1] = 0;
                                                                    return (Next_results){tmp_str24497, TOK_LESS, "<"};
                                                                  } else {
                                                                    if (StartsWith(src, ">")) {
                                                                      int tmp_strlen24422 = (strlen(src)) - (1) + 1;
                                                                      char* tmp_str24422 = calloc(tmp_strlen24422, sizeof(char));
                                                                      strncpy(tmp_str24422, src + 1, tmp_strlen24422 - 1);
                                                                      tmp_str24422[tmp_strlen24422 - 1] = 0;
                                                                      return (Next_results){tmp_str24422, TOK_GREATER, ">"};
                                                                    } else {
                                                                      if (IsAlpha(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        i = (i) - (1);
                                                                        int tmp_strlen24191 = (i) - (0) + 1;
                                                                        char* tmp_str24191 = calloc(tmp_strlen24191, sizeof(char));
                                                                        strncpy(tmp_str24191, src + 0, tmp_strlen24191 - 1);
                                                                        tmp_str24191[tmp_strlen24191 - 1] = 0;
                                                                        char* ts = tmp_str24191;
                                                                        int tt;
                                                                        if ((strcmp(ts, "fn") == 0)) {
                                                                          tt = TOK_FN;
                                                                        } else {
                                                                          if ((strcmp(ts, "let") == 0)) {
                                                                            tt = TOK_LET;
                                                                          } else {
                                                                            if ((strcmp(ts, "var") == 0)) {
                                                                              tt = TOK_VAR;
                                                                            } else {
                                                                              if ((strcmp(ts, "if") == 0)) {
                                                                                tt = TOK_IF;
                                                                              } else {
                                                                                if ((strcmp(ts, "else") == 0)) {
                                                                                  tt = TOK_ELSE;
                                                                                } else {
                                                                                  if ((strcmp(ts, "for") == 0)) {
                                                                                    tt = TOK_FOR;
                                                                                  } else {
                                                                                    if ((strcmp(ts, "return") == 0)) {
                                                                                      tt = TOK_RETURN;
                                                                                    } else {
                                                                                      if ((strcmp(ts, "bool") == 0)) {
                                                                                        tt = TOK_BOOL;
                                                                                      } else {
                                                                                        if ((strcmp(ts, "int") == 0)) {
                                                                                          tt = TOK_INT;
                                                                                        } else {
                                                                                          if ((strcmp(ts, "string") == 0)) {
                                                                                            tt = TOK_STRING;
                                                                                          } else {
                                                                                            if ((strcmp(ts, "false") == 0)) {
                                                                                              tt = TOK_FALSE;
                                                                                            } else {
                                                                                              if ((strcmp(ts, "true") == 0)) {
                                                                                                tt = TOK_TRUE;
                                                                                              } else {
                                                                                                tt = TOK_IDENT;
                                                                                              }
                                                                                            }
                                                                                          }
                                                                                        }
                                                                                      }
                                                                                    }
                                                                                  }
                                                                                }
                                                                              }
                                                                            }
                                                                          }
                                                                        }
                                                                        int tmp_strlen23399 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str23399 = calloc(tmp_strlen23399, sizeof(char));
                                                                        strncpy(tmp_str23399, src + i, tmp_strlen23399 - 1);
                                                                        tmp_str23399[tmp_strlen23399 - 1] = 0;
                                                                        return (Next_results){tmp_str23399, tt, ts};
                                                                      } else {
                                                                        if (IsNumeric(src[0])) {
                                                                          int i = 1;
                                                                          while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                            i = (i) + (1);
                                                                          }
                                                                          int tmp_strlen23231 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str23231 = calloc(tmp_strlen23231, sizeof(char));
                                                                          strncpy(tmp_str23231, src + i, tmp_strlen23231 - 1);
                                                                          tmp_str23231[tmp_strlen23231 - 1] = 0;
                                                                          int tmp_strlen23210 = (i) - (0) + 1;
                                                                          char* tmp_str23210 = calloc(tmp_strlen23210, sizeof(char));
                                                                          strncpy(tmp_str23210, src + 0, tmp_strlen23210 - 1);
                                                                          tmp_str23210[tmp_strlen23210 - 1] = 0;
                                                                          return (Next_results){tmp_str23231, TOK_INTLIT, tmp_str23210};
                                                                        } else {
                                                                          if (StartsWith(src, "\"")) {
                                                                            int i = 1;
                                                                            while (true) {
                                                                              int tmp_strlen23129 = ((i) + (1)) - (i) + 1;
                                                                              char* tmp_str23129 = calloc(tmp_strlen23129, sizeof(char));
                                                                              strncpy(tmp_str23129, src + i, tmp_strlen23129 - 1);
                                                                              tmp_str23129[tmp_strlen23129 - 1] = 0;
                                                                              if (!((strcmp(tmp_str23129, "\"") != 0))) break;
                                                                              i = (i) + (1);
                                                                              int tmp_strlen23070 = (i) - ((i) - (1)) + 1;
                                                                              char* tmp_str23070 = calloc(tmp_strlen23070, sizeof(char));
                                                                              strncpy(tmp_str23070, src + (i) - (1), tmp_strlen23070 - 1);
                                                                              tmp_str23070[tmp_strlen23070 - 1] = 0;
                                                                              if ((strcmp(tmp_str23070, "\\") == 0)) {
                                                                                i = (i) + (1);
                                                                              }
                                                                            }
                                                                            i = (i) + (1);
                                                                            int tmp_strlen22966 = (strlen(src)) - (i) + 1;
                                                                            char* tmp_str22966 = calloc(tmp_strlen22966, sizeof(char));
                                                                            strncpy(tmp_str22966, src + i, tmp_strlen22966 - 1);
                                                                            tmp_str22966[tmp_strlen22966 - 1] = 0;
                                                                            int tmp_strlen22945 = (i) - (0) + 1;
                                                                            char* tmp_str22945 = calloc(tmp_strlen22945, sizeof(char));
                                                                            strncpy(tmp_str22945, src + 0, tmp_strlen22945 - 1);
                                                                            tmp_str22945[tmp_strlen22945 - 1] = 0;
                                                                            return (Next_results){tmp_str22966, TOK_STRLIT, tmp_str22945};
                                                                          } else {
                                                                            int tmp_strlen22880 = (1) - (0) + 1;
                                                                            char* tmp_str22880 = calloc(tmp_strlen22880, sizeof(char));
                                                                            strncpy(tmp_str22880, src + 0, tmp_strlen22880 - 1);
                                                                            tmp_str22880[tmp_strlen22880 - 1] = 0;
                                                                            int tmp_strlen22876 = strlen("unexpected token start: ") + strlen(tmp_str22880) + 1;
                                                                            char* tmp_str22876 = calloc(tmp_strlen22876, sizeof(char));
                                                                            strcpy(tmp_str22876, "unexpected token start: ");
                                                                            strcat(tmp_str22876, tmp_str22880);
                                                                            printf("%s", tmp_str22876);
                                                                            exit(1);
                                                                          }
                                                                        }
                                                                      }
                                                                    }
                                                                  }
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

Peek_results Peek(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results22764 = Next(src);
  tok = tmp_results22764.result2;
  tok_str = tmp_results22764.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22580 = Next(src);
  src = tmp_results22580.result1;
  actual_tok = tmp_results22580.result2;
  actual_tok_str = tmp_results22580.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen22446 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str22446 = calloc(tmp_strlen22446, sizeof(char));
    strcpy(tmp_str22446, "expected token: ");
    strcat(tmp_str22446, itoa(expected_tok));
    int tmp_strlen22419 = strlen(tmp_str22446) + strlen(" got: ") + 1;
    char* tmp_str22419 = calloc(tmp_strlen22419, sizeof(char));
    strcpy(tmp_str22419, tmp_str22446);
    strcat(tmp_str22419, " got: ");
    int tmp_strlen22399 = strlen(tmp_str22419) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22399 = calloc(tmp_strlen22399, sizeof(char));
    strcpy(tmp_str22399, tmp_str22419);
    strcat(tmp_str22399, itoa(actual_tok));
    int tmp_strlen22390 = strlen(tmp_str22399) + strlen(" \"") + 1;
    char* tmp_str22390 = calloc(tmp_strlen22390, sizeof(char));
    strcpy(tmp_str22390, tmp_str22399);
    strcat(tmp_str22390, " \"");
    int tmp_strlen22372 = strlen(tmp_str22390) + strlen(actual_tok_str) + 1;
    char* tmp_str22372 = calloc(tmp_strlen22372, sizeof(char));
    strcpy(tmp_str22372, tmp_str22390);
    strcat(tmp_str22372, actual_tok_str);
    int tmp_strlen22364 = strlen(tmp_str22372) + strlen("\"") + 1;
    char* tmp_str22364 = calloc(tmp_strlen22364, sizeof(char));
    strcpy(tmp_str22364, tmp_str22372);
    strcat(tmp_str22364, "\"");
    printf("%s", tmp_str22364);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22196 = Next(src);
  src = tmp_results22196.result1;
  actual_tok = tmp_results22196.result2;
  actual_tok_str = tmp_results22196.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen22062 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22062 = calloc(tmp_strlen22062, sizeof(char));
    strcpy(tmp_str22062, "expected ident, got: ");
    strcat(tmp_str22062, itoa(actual_tok));
    int tmp_strlen22053 = strlen(tmp_str22062) + strlen(" \"") + 1;
    char* tmp_str22053 = calloc(tmp_strlen22053, sizeof(char));
    strcpy(tmp_str22053, tmp_str22062);
    strcat(tmp_str22053, " \"");
    int tmp_strlen22035 = strlen(tmp_str22053) + strlen(actual_tok_str) + 1;
    char* tmp_str22035 = calloc(tmp_strlen22035, sizeof(char));
    strcpy(tmp_str22035, tmp_str22053);
    strcat(tmp_str22035, actual_tok_str);
    int tmp_strlen22027 = strlen(tmp_str22035) + strlen("\"") + 1;
    char* tmp_str22027 = calloc(tmp_strlen22027, sizeof(char));
    strcpy(tmp_str22027, tmp_str22035);
    strcat(tmp_str22027, "\"");
    printf("%s", tmp_str22027);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results21847 = Next(src);
  src = tmp_results21847.result1;
  actual_tok = tmp_results21847.result2;
  actual_tok_str = tmp_results21847.result3;
  if (((actual_tok) != (TOK_UNDERSCORE)) && ((actual_tok) != (TOK_IDENT))) {
    int tmp_strlen21667 = strlen("expected ident or underscore, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str21667 = calloc(tmp_strlen21667, sizeof(char));
    strcpy(tmp_str21667, "expected ident or underscore, got: ");
    strcat(tmp_str21667, itoa(actual_tok));
    int tmp_strlen21658 = strlen(tmp_str21667) + strlen(" \"") + 1;
    char* tmp_str21658 = calloc(tmp_strlen21658, sizeof(char));
    strcpy(tmp_str21658, tmp_str21667);
    strcat(tmp_str21658, " \"");
    int tmp_strlen21640 = strlen(tmp_str21658) + strlen(actual_tok_str) + 1;
    char* tmp_str21640 = calloc(tmp_strlen21640, sizeof(char));
    strcpy(tmp_str21640, tmp_str21658);
    strcat(tmp_str21640, actual_tok_str);
    int tmp_strlen21632 = strlen(tmp_str21640) + strlen("\"") + 1;
    char* tmp_str21632 = calloc(tmp_strlen21632, sizeof(char));
    strcpy(tmp_str21632, tmp_str21640);
    strcat(tmp_str21632, "\"");
    printf("%s", tmp_str21632);
    exit(1);
  }
  return (ConsumeIdentOrUnderscore_results){src, actual_tok_str};
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21472 = Next(src);
  src = tmp_results21472.result1;
  tok = tmp_results21472.result2;
  tok_str = tmp_results21472.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen21175 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str21175 = calloc(tmp_strlen21175, sizeof(char));
        strcpy(tmp_str21175, "expected type, got: ");
        strcat(tmp_str21175, itoa(tok));
        int tmp_strlen21166 = strlen(tmp_str21175) + strlen(" \"") + 1;
        char* tmp_str21166 = calloc(tmp_strlen21166, sizeof(char));
        strcpy(tmp_str21166, tmp_str21175);
        strcat(tmp_str21166, " \"");
        int tmp_strlen21155 = strlen(tmp_str21166) + strlen(tok_str) + 1;
        char* tmp_str21155 = calloc(tmp_strlen21155, sizeof(char));
        strcpy(tmp_str21155, tmp_str21166);
        strcat(tmp_str21155, tok_str);
        int tmp_strlen21147 = strlen(tmp_str21155) + strlen("\"") + 1;
        char* tmp_str21147 = calloc(tmp_strlen21147, sizeof(char));
        strcpy(tmp_str21147, tmp_str21155);
        strcat(tmp_str21147, "\"");
        printf("%s", tmp_str21147);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21016 = Next(src);
  src = tmp_results21016.result1;
  tok = tmp_results21016.result2;
  tok_str = tmp_results21016.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen20842 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str20842 = calloc(tmp_strlen20842, sizeof(char));
    strcpy(tmp_str20842, "expected false or true, got: ");
    strcat(tmp_str20842, itoa(tok));
    int tmp_strlen20833 = strlen(tmp_str20842) + strlen(" \"") + 1;
    char* tmp_str20833 = calloc(tmp_strlen20833, sizeof(char));
    strcpy(tmp_str20833, tmp_str20842);
    strcat(tmp_str20833, " \"");
    int tmp_strlen20822 = strlen(tmp_str20833) + strlen(tok_str) + 1;
    char* tmp_str20822 = calloc(tmp_strlen20822, sizeof(char));
    strcpy(tmp_str20822, tmp_str20833);
    strcat(tmp_str20822, tok_str);
    int tmp_strlen20814 = strlen(tmp_str20822) + strlen("\"") + 1;
    char* tmp_str20814 = calloc(tmp_strlen20814, sizeof(char));
    strcpy(tmp_str20814, tmp_str20822);
    strcat(tmp_str20814, "\"");
    printf("%s", tmp_str20814);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results20705 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results20705.result1;
  lit = tmp_results20705.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results20556 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results20556.result1;
  lit = tmp_results20556.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  ConsumeToken_results tmp_results20379 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results20379.result1;
  Peek_results tmp_results20336 = Peek(src);
  tok = tmp_results20336.result1;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results20190 = TranslateExprs(src, indent);
    src = tmp_results20190.result1;
    expr_count = tmp_results20190.result2;
    args_setup = tmp_results20190.result3;
    arg_values = tmp_results20190.result4;
  }
  ConsumeToken_results tmp_results20110 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results20110.result1;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen19979 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str19979 = calloc(tmp_strlen19979, sizeof(char));
    strcpy(tmp_str19979, "printf(\"%s\", ");
    strcat(tmp_str19979, arg_values);
    int tmp_strlen19972 = strlen(tmp_str19979) + strlen(")") + 1;
    char* tmp_str19972 = calloc(tmp_strlen19972, sizeof(char));
    strcpy(tmp_str19972, tmp_str19979);
    strcat(tmp_str19972, ")");
    val = tmp_str19972;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen19902 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str19902 = calloc(tmp_strlen19902, sizeof(char));
      strcpy(tmp_str19902, "strlen(");
      strcat(tmp_str19902, arg_values);
      int tmp_strlen19895 = strlen(tmp_str19902) + strlen(")") + 1;
      char* tmp_str19895 = calloc(tmp_strlen19895, sizeof(char));
      strcpy(tmp_str19895, tmp_str19902);
      strcat(tmp_str19895, ")");
      val = tmp_str19895;
    } else {
      int tmp_strlen19854 = strlen(callee) + strlen("(") + 1;
      char* tmp_str19854 = calloc(tmp_strlen19854, sizeof(char));
      strcpy(tmp_str19854, callee);
      strcat(tmp_str19854, "(");
      int tmp_strlen19840 = strlen(tmp_str19854) + strlen(arg_values) + 1;
      char* tmp_str19840 = calloc(tmp_strlen19840, sizeof(char));
      strcpy(tmp_str19840, tmp_str19854);
      strcat(tmp_str19840, arg_values);
      int tmp_strlen19833 = strlen(tmp_str19840) + strlen(")") + 1;
      char* tmp_str19833 = calloc(tmp_strlen19833, sizeof(char));
      strcpy(tmp_str19833, tmp_str19840);
      strcat(tmp_str19833, ")");
      val = tmp_str19833;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  int p = strlen(src);
  ConsumeToken_results tmp_results19646 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results19646.result1;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen19464 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str19464 = calloc(tmp_strlen19464, sizeof(char));
  strcpy(tmp_str19464, "strlen(");
  strcat(tmp_str19464, strvar);
  int tmp_strlen19457 = strlen(tmp_str19464) + strlen(")") + 1;
  char* tmp_str19457 = calloc(tmp_strlen19457, sizeof(char));
  strcpy(tmp_str19457, tmp_str19464);
  strcat(tmp_str19457, ")");
  char* high_expr = tmp_str19457;
  Peek_results tmp_results19452 = Peek(src);
  tok = tmp_results19452.result1;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results19399 = ConsumeToken(src, TOK_COLON);
    src = tmp_results19399.result1;
    TranslateExpr_results tmp_results19353 = TranslateExpr(src, indent);
    src = tmp_results19353.result1;
    high_setup = tmp_results19353.result2;
    high_expr = tmp_results19353.result3;
    ConsumeToken_results tmp_results19289 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results19289.result1;
  } else {
    TranslateExpr_results tmp_results19227 = TranslateExpr(src, indent);
    src = tmp_results19227.result1;
    low_setup = tmp_results19227.result2;
    low_expr = tmp_results19227.result3;
    Peek_results tmp_results19165 = Peek(src);
    tok = tmp_results19165.result1;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results19101 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results19101.result1;
      int tmp_strlen19012 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str19012 = calloc(tmp_strlen19012, sizeof(char));
      strcpy(tmp_str19012, strvar);
      strcat(tmp_str19012, "[");
      int tmp_strlen19000 = strlen(tmp_str19012) + strlen(low_expr) + 1;
      char* tmp_str19000 = calloc(tmp_strlen19000, sizeof(char));
      strcpy(tmp_str19000, tmp_str19012);
      strcat(tmp_str19000, low_expr);
      int tmp_strlen18993 = strlen(tmp_str19000) + strlen("]") + 1;
      char* tmp_str18993 = calloc(tmp_strlen18993, sizeof(char));
      strcpy(tmp_str18993, tmp_str19000);
      strcat(tmp_str18993, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str18993};
    }
    ConsumeToken_results tmp_results18974 = ConsumeToken(src, TOK_COLON);
    src = tmp_results18974.result1;
    Peek_results tmp_results18928 = Peek(src);
    tok = tmp_results18928.result1;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results18864 = TranslateExpr(src, indent);
      src = tmp_results18864.result1;
      high_setup = tmp_results18864.result2;
      high_expr = tmp_results18864.result3;
    }
    ConsumeToken_results tmp_results18790 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results18790.result1;
  }
  int tmp_strlen18697 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str18697 = calloc(tmp_strlen18697, sizeof(char));
  strcpy(tmp_str18697, "tmp_str");
  strcat(tmp_str18697, itoa(p));
  char* tmp_str = tmp_str18697;
  int tmp_strlen18644 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str18644 = calloc(tmp_strlen18644, sizeof(char));
  strcpy(tmp_str18644, "tmp_strlen");
  strcat(tmp_str18644, itoa(p));
  char* tmp_strlen = tmp_str18644;
  int tmp_strlen18596 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str18596 = calloc(tmp_strlen18596, sizeof(char));
  strcpy(tmp_str18596, low_setup);
  strcat(tmp_str18596, high_setup);
  char* setup = tmp_str18596;
  int tmp_strlen18568 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18568 = calloc(tmp_strlen18568, sizeof(char));
  strcpy(tmp_str18568, setup);
  strcat(tmp_str18568, indent);
  int tmp_strlen18558 = strlen(tmp_str18568) + strlen("int ") + 1;
  char* tmp_str18558 = calloc(tmp_strlen18558, sizeof(char));
  strcpy(tmp_str18558, tmp_str18568);
  strcat(tmp_str18558, "int ");
  int tmp_strlen18544 = strlen(tmp_str18558) + strlen(tmp_strlen) + 1;
  char* tmp_str18544 = calloc(tmp_strlen18544, sizeof(char));
  strcpy(tmp_str18544, tmp_str18558);
  strcat(tmp_str18544, tmp_strlen);
  int tmp_strlen18534 = strlen(tmp_str18544) + strlen(" = (") + 1;
  char* tmp_str18534 = calloc(tmp_strlen18534, sizeof(char));
  strcpy(tmp_str18534, tmp_str18544);
  strcat(tmp_str18534, " = (");
  int tmp_strlen18521 = strlen(tmp_str18534) + strlen(high_expr) + 1;
  char* tmp_str18521 = calloc(tmp_strlen18521, sizeof(char));
  strcpy(tmp_str18521, tmp_str18534);
  strcat(tmp_str18521, high_expr);
  int tmp_strlen18510 = strlen(tmp_str18521) + strlen(") - (") + 1;
  char* tmp_str18510 = calloc(tmp_strlen18510, sizeof(char));
  strcpy(tmp_str18510, tmp_str18521);
  strcat(tmp_str18510, ") - (");
  int tmp_strlen18498 = strlen(tmp_str18510) + strlen(low_expr) + 1;
  char* tmp_str18498 = calloc(tmp_strlen18498, sizeof(char));
  strcpy(tmp_str18498, tmp_str18510);
  strcat(tmp_str18498, low_expr);
  int tmp_strlen18484 = strlen(tmp_str18498) + strlen(") + 1;\n") + 1;
  char* tmp_str18484 = calloc(tmp_strlen18484, sizeof(char));
  strcpy(tmp_str18484, tmp_str18498);
  strcat(tmp_str18484, ") + 1;\n");
  setup = tmp_str18484;
  int tmp_strlen18456 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18456 = calloc(tmp_strlen18456, sizeof(char));
  strcpy(tmp_str18456, setup);
  strcat(tmp_str18456, indent);
  int tmp_strlen18444 = strlen(tmp_str18456) + strlen("char* ") + 1;
  char* tmp_str18444 = calloc(tmp_strlen18444, sizeof(char));
  strcpy(tmp_str18444, tmp_str18456);
  strcat(tmp_str18444, "char* ");
  int tmp_strlen18433 = strlen(tmp_str18444) + strlen(tmp_str) + 1;
  char* tmp_str18433 = calloc(tmp_strlen18433, sizeof(char));
  strcpy(tmp_str18433, tmp_str18444);
  strcat(tmp_str18433, tmp_str);
  int tmp_strlen18417 = strlen(tmp_str18433) + strlen(" = calloc(") + 1;
  char* tmp_str18417 = calloc(tmp_strlen18417, sizeof(char));
  strcpy(tmp_str18417, tmp_str18433);
  strcat(tmp_str18417, " = calloc(");
  int tmp_strlen18403 = strlen(tmp_str18417) + strlen(tmp_strlen) + 1;
  char* tmp_str18403 = calloc(tmp_strlen18403, sizeof(char));
  strcpy(tmp_str18403, tmp_str18417);
  strcat(tmp_str18403, tmp_strlen);
  int tmp_strlen18379 = strlen(tmp_str18403) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str18379 = calloc(tmp_strlen18379, sizeof(char));
  strcpy(tmp_str18379, tmp_str18403);
  strcat(tmp_str18379, ", sizeof(char));\n");
  setup = tmp_str18379;
  int tmp_strlen18351 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18351 = calloc(tmp_strlen18351, sizeof(char));
  strcpy(tmp_str18351, setup);
  strcat(tmp_str18351, indent);
  int tmp_strlen18337 = strlen(tmp_str18351) + strlen("strncpy(") + 1;
  char* tmp_str18337 = calloc(tmp_strlen18337, sizeof(char));
  strcpy(tmp_str18337, tmp_str18351);
  strcat(tmp_str18337, "strncpy(");
  int tmp_strlen18326 = strlen(tmp_str18337) + strlen(tmp_str) + 1;
  char* tmp_str18326 = calloc(tmp_strlen18326, sizeof(char));
  strcpy(tmp_str18326, tmp_str18337);
  strcat(tmp_str18326, tmp_str);
  int tmp_strlen18318 = strlen(tmp_str18326) + strlen(", ") + 1;
  char* tmp_str18318 = calloc(tmp_strlen18318, sizeof(char));
  strcpy(tmp_str18318, tmp_str18326);
  strcat(tmp_str18318, ", ");
  int tmp_strlen18308 = strlen(tmp_str18318) + strlen(strvar) + 1;
  char* tmp_str18308 = calloc(tmp_strlen18308, sizeof(char));
  strcpy(tmp_str18308, tmp_str18318);
  strcat(tmp_str18308, strvar);
  int tmp_strlen18299 = strlen(tmp_str18308) + strlen(" + ") + 1;
  char* tmp_str18299 = calloc(tmp_strlen18299, sizeof(char));
  strcpy(tmp_str18299, tmp_str18308);
  strcat(tmp_str18299, " + ");
  int tmp_strlen18287 = strlen(tmp_str18299) + strlen(low_expr) + 1;
  char* tmp_str18287 = calloc(tmp_strlen18287, sizeof(char));
  strcpy(tmp_str18287, tmp_str18299);
  strcat(tmp_str18287, low_expr);
  int tmp_strlen18279 = strlen(tmp_str18287) + strlen(", ") + 1;
  char* tmp_str18279 = calloc(tmp_strlen18279, sizeof(char));
  strcpy(tmp_str18279, tmp_str18287);
  strcat(tmp_str18279, ", ");
  int tmp_strlen18265 = strlen(tmp_str18279) + strlen(tmp_strlen) + 1;
  char* tmp_str18265 = calloc(tmp_strlen18265, sizeof(char));
  strcpy(tmp_str18265, tmp_str18279);
  strcat(tmp_str18265, tmp_strlen);
  int tmp_strlen18251 = strlen(tmp_str18265) + strlen(" - 1);\n") + 1;
  char* tmp_str18251 = calloc(tmp_strlen18251, sizeof(char));
  strcpy(tmp_str18251, tmp_str18265);
  strcat(tmp_str18251, " - 1);\n");
  setup = tmp_str18251;
  int tmp_strlen18223 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18223 = calloc(tmp_strlen18223, sizeof(char));
  strcpy(tmp_str18223, setup);
  strcat(tmp_str18223, indent);
  int tmp_strlen18212 = strlen(tmp_str18223) + strlen(tmp_str) + 1;
  char* tmp_str18212 = calloc(tmp_strlen18212, sizeof(char));
  strcpy(tmp_str18212, tmp_str18223);
  strcat(tmp_str18212, tmp_str);
  int tmp_strlen18205 = strlen(tmp_str18212) + strlen("[") + 1;
  char* tmp_str18205 = calloc(tmp_strlen18205, sizeof(char));
  strcpy(tmp_str18205, tmp_str18212);
  strcat(tmp_str18205, "[");
  int tmp_strlen18191 = strlen(tmp_str18205) + strlen(tmp_strlen) + 1;
  char* tmp_str18191 = calloc(tmp_strlen18191, sizeof(char));
  strcpy(tmp_str18191, tmp_str18205);
  strcat(tmp_str18191, tmp_strlen);
  int tmp_strlen18173 = strlen(tmp_str18191) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str18173 = calloc(tmp_strlen18173, sizeof(char));
  strcpy(tmp_str18173, tmp_str18191);
  strcat(tmp_str18173, " - 1] = 0;\n");
  setup = tmp_str18173;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results18014 = Peek(src);
  tok = tmp_results18014.result1;
  tok_str = tmp_results18014.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results17904 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results17904.result1;
    TranslateExpr_results tmp_results17857 = TranslateExpr(src, indent);
    src = tmp_results17857.result1;
    setup = tmp_results17857.result2;
    val = tmp_results17857.result3;
    ConsumeToken_results tmp_results17804 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results17804.result1;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results17650 = TranslateBoolLiteral(src);
      src = tmp_results17650.result1;
      lit = tmp_results17650.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results17519 = TranslateIntLiteral(src);
        src = tmp_results17519.result1;
        lit = tmp_results17519.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results17389 = TranslateStringLiteral(src);
          src = tmp_results17389.result1;
          lit = tmp_results17389.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results17255 = ConsumeIdent(src);
            src = tmp_results17255.result1;
            ident = tmp_results17255.result2;
            Peek_results tmp_results17216 = Peek(src);
            tok = tmp_results17216.result1;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results17095 = TranslateCall(src, indent, ident);
              src = tmp_results17095.result1;
              setup = tmp_results17095.result2;
              expr = tmp_results17095.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results16895 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results16895.result1;
                setup = tmp_results16895.result2;
                expr = tmp_results16895.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen16675 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str16675 = calloc(tmp_strlen16675, sizeof(char));
            strcpy(tmp_str16675, "unexpected expr, got: ");
            strcat(tmp_str16675, itoa(tok));
            int tmp_strlen16666 = strlen(tmp_str16675) + strlen(" \"") + 1;
            char* tmp_str16666 = calloc(tmp_strlen16666, sizeof(char));
            strcpy(tmp_str16666, tmp_str16675);
            strcat(tmp_str16666, " \"");
            int tmp_strlen16655 = strlen(tmp_str16666) + strlen(tok_str) + 1;
            char* tmp_str16655 = calloc(tmp_strlen16655, sizeof(char));
            strcpy(tmp_str16655, tmp_str16666);
            strcat(tmp_str16655, tok_str);
            int tmp_strlen16647 = strlen(tmp_str16655) + strlen("\"") + 1;
            char* tmp_str16647 = calloc(tmp_strlen16647, sizeof(char));
            strcpy(tmp_str16647, tmp_str16655);
            strcat(tmp_str16647, "\"");
            printf("%s", tmp_str16647);
            exit(1);
          }
        }
      }
    }
  }
}

TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent) {
  int tok;
  Peek_results tmp_results16518 = Peek(src);
  tok = tmp_results16518.result1;
  if (IsUnaryOp(tok)) {
    char* tok_str;
    ConsumeToken_results tmp_results16439 = ConsumeToken(src, tok);
    src = tmp_results16439.result1;
    tok_str = tmp_results16439.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results16343 = TranslateExpr(src, indent);
    src = tmp_results16343.result1;
    setup = tmp_results16343.result2;
    val = tmp_results16343.result3;
    int tmp_strlen16270 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str16270 = calloc(tmp_strlen16270, sizeof(char));
    strcpy(tmp_str16270, tok_str);
    strcat(tmp_str16270, "(");
    int tmp_strlen16263 = strlen(tmp_str16270) + strlen(val) + 1;
    char* tmp_str16263 = calloc(tmp_strlen16263, sizeof(char));
    strcpy(tmp_str16263, tmp_str16270);
    strcat(tmp_str16263, val);
    int tmp_strlen16256 = strlen(tmp_str16263) + strlen(")") + 1;
    char* tmp_str16256 = calloc(tmp_strlen16256, sizeof(char));
    strcpy(tmp_str16256, tmp_str16263);
    strcat(tmp_str16256, ")");
    val = tmp_str16256;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results16152 = TranslateOperand(src, indent);
    src = tmp_results16152.result1;
    setup = tmp_results16152.result2;
    expr = tmp_results16152.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results15909 = TranslateUnaryExpr(src, indent);
  src = tmp_results15909.result1;
  setup = tmp_results15909.result2;
  val = tmp_results15909.result3;
  int op;
  char* op_str;
  Peek_results tmp_results15816 = Peek(src);
  op = tmp_results15816.result1;
  op_str = tmp_results15816.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results15729 = ConsumeToken(src, op);
    src = tmp_results15729.result1;
    op_str = tmp_results15729.result2;
    int tok;
    Peek_results tmp_results15664 = Peek(src);
    tok = tmp_results15664.result1;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results15600 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results15600.result1;
      Peek_results tmp_results15548 = Peek(src);
      tok = tmp_results15548.result1;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results15457 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results15457.result1;
    setup_b = tmp_results15457.result2;
    val_b = tmp_results15457.result3;
    int tmp_strlen15346 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str15346 = calloc(tmp_strlen15346, sizeof(char));
    strcpy(tmp_str15346, setup);
    strcat(tmp_str15346, setup_b);
    setup = tmp_str15346;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen15254 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15254 = calloc(tmp_strlen15254, sizeof(char));
      strcpy(tmp_str15254, "tmp_str");
      strcat(tmp_str15254, itoa(strlen(src)));
      char* tmp_str = tmp_str15254;
      int tmp_strlen15186 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15186 = calloc(tmp_strlen15186, sizeof(char));
      strcpy(tmp_str15186, "tmp_strlen");
      strcat(tmp_str15186, itoa(strlen(src)));
      char* tmp_strlen = tmp_str15186;
      int tmp_strlen15150 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15150 = calloc(tmp_strlen15150, sizeof(char));
      strcpy(tmp_str15150, setup);
      strcat(tmp_str15150, indent);
      int tmp_strlen15140 = strlen(tmp_str15150) + strlen("int ") + 1;
      char* tmp_str15140 = calloc(tmp_strlen15140, sizeof(char));
      strcpy(tmp_str15140, tmp_str15150);
      strcat(tmp_str15140, "int ");
      int tmp_strlen15126 = strlen(tmp_str15140) + strlen(tmp_strlen) + 1;
      char* tmp_str15126 = calloc(tmp_strlen15126, sizeof(char));
      strcpy(tmp_str15126, tmp_str15140);
      strcat(tmp_str15126, tmp_strlen);
      int tmp_strlen15110 = strlen(tmp_str15126) + strlen(" = strlen(") + 1;
      char* tmp_str15110 = calloc(tmp_strlen15110, sizeof(char));
      strcpy(tmp_str15110, tmp_str15126);
      strcat(tmp_str15110, " = strlen(");
      int tmp_strlen15103 = strlen(tmp_str15110) + strlen(val) + 1;
      char* tmp_str15103 = calloc(tmp_strlen15103, sizeof(char));
      strcpy(tmp_str15103, tmp_str15110);
      strcat(tmp_str15103, val);
      int tmp_strlen15086 = strlen(tmp_str15103) + strlen(") + strlen(") + 1;
      char* tmp_str15086 = calloc(tmp_strlen15086, sizeof(char));
      strcpy(tmp_str15086, tmp_str15103);
      strcat(tmp_str15086, ") + strlen(");
      int tmp_strlen15077 = strlen(tmp_str15086) + strlen(val_b) + 1;
      char* tmp_str15077 = calloc(tmp_strlen15077, sizeof(char));
      strcpy(tmp_str15077, tmp_str15086);
      strcat(tmp_str15077, val_b);
      int tmp_strlen15063 = strlen(tmp_str15077) + strlen(") + 1;\n") + 1;
      char* tmp_str15063 = calloc(tmp_strlen15063, sizeof(char));
      strcpy(tmp_str15063, tmp_str15077);
      strcat(tmp_str15063, ") + 1;\n");
      setup = tmp_str15063;
      int tmp_strlen15027 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15027 = calloc(tmp_strlen15027, sizeof(char));
      strcpy(tmp_str15027, setup);
      strcat(tmp_str15027, indent);
      int tmp_strlen15015 = strlen(tmp_str15027) + strlen("char* ") + 1;
      char* tmp_str15015 = calloc(tmp_strlen15015, sizeof(char));
      strcpy(tmp_str15015, tmp_str15027);
      strcat(tmp_str15015, "char* ");
      int tmp_strlen15004 = strlen(tmp_str15015) + strlen(tmp_str) + 1;
      char* tmp_str15004 = calloc(tmp_strlen15004, sizeof(char));
      strcpy(tmp_str15004, tmp_str15015);
      strcat(tmp_str15004, tmp_str);
      int tmp_strlen14988 = strlen(tmp_str15004) + strlen(" = calloc(") + 1;
      char* tmp_str14988 = calloc(tmp_strlen14988, sizeof(char));
      strcpy(tmp_str14988, tmp_str15004);
      strcat(tmp_str14988, " = calloc(");
      int tmp_strlen14974 = strlen(tmp_str14988) + strlen(tmp_strlen) + 1;
      char* tmp_str14974 = calloc(tmp_strlen14974, sizeof(char));
      strcpy(tmp_str14974, tmp_str14988);
      strcat(tmp_str14974, tmp_strlen);
      int tmp_strlen14950 = strlen(tmp_str14974) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str14950 = calloc(tmp_strlen14950, sizeof(char));
      strcpy(tmp_str14950, tmp_str14974);
      strcat(tmp_str14950, ", sizeof(char));\n");
      setup = tmp_str14950;
      int tmp_strlen14914 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14914 = calloc(tmp_strlen14914, sizeof(char));
      strcpy(tmp_str14914, setup);
      strcat(tmp_str14914, indent);
      int tmp_strlen14901 = strlen(tmp_str14914) + strlen("strcpy(") + 1;
      char* tmp_str14901 = calloc(tmp_strlen14901, sizeof(char));
      strcpy(tmp_str14901, tmp_str14914);
      strcat(tmp_str14901, "strcpy(");
      int tmp_strlen14890 = strlen(tmp_str14901) + strlen(tmp_str) + 1;
      char* tmp_str14890 = calloc(tmp_strlen14890, sizeof(char));
      strcpy(tmp_str14890, tmp_str14901);
      strcat(tmp_str14890, tmp_str);
      int tmp_strlen14882 = strlen(tmp_str14890) + strlen(", ") + 1;
      char* tmp_str14882 = calloc(tmp_strlen14882, sizeof(char));
      strcpy(tmp_str14882, tmp_str14890);
      strcat(tmp_str14882, ", ");
      int tmp_strlen14875 = strlen(tmp_str14882) + strlen(val) + 1;
      char* tmp_str14875 = calloc(tmp_strlen14875, sizeof(char));
      strcpy(tmp_str14875, tmp_str14882);
      strcat(tmp_str14875, val);
      int tmp_strlen14865 = strlen(tmp_str14875) + strlen(");\n") + 1;
      char* tmp_str14865 = calloc(tmp_strlen14865, sizeof(char));
      strcpy(tmp_str14865, tmp_str14875);
      strcat(tmp_str14865, ");\n");
      setup = tmp_str14865;
      int tmp_strlen14829 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14829 = calloc(tmp_strlen14829, sizeof(char));
      strcpy(tmp_str14829, setup);
      strcat(tmp_str14829, indent);
      int tmp_strlen14816 = strlen(tmp_str14829) + strlen("strcat(") + 1;
      char* tmp_str14816 = calloc(tmp_strlen14816, sizeof(char));
      strcpy(tmp_str14816, tmp_str14829);
      strcat(tmp_str14816, "strcat(");
      int tmp_strlen14805 = strlen(tmp_str14816) + strlen(tmp_str) + 1;
      char* tmp_str14805 = calloc(tmp_strlen14805, sizeof(char));
      strcpy(tmp_str14805, tmp_str14816);
      strcat(tmp_str14805, tmp_str);
      int tmp_strlen14797 = strlen(tmp_str14805) + strlen(", ") + 1;
      char* tmp_str14797 = calloc(tmp_strlen14797, sizeof(char));
      strcpy(tmp_str14797, tmp_str14805);
      strcat(tmp_str14797, ", ");
      int tmp_strlen14788 = strlen(tmp_str14797) + strlen(val_b) + 1;
      char* tmp_str14788 = calloc(tmp_strlen14788, sizeof(char));
      strcpy(tmp_str14788, tmp_str14797);
      strcat(tmp_str14788, val_b);
      int tmp_strlen14778 = strlen(tmp_str14788) + strlen(");\n") + 1;
      char* tmp_str14778 = calloc(tmp_strlen14778, sizeof(char));
      strcpy(tmp_str14778, tmp_str14788);
      strcat(tmp_str14778, ");\n");
      setup = tmp_str14778;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen14680 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str14680 = calloc(tmp_strlen14680, sizeof(char));
        strcpy(tmp_str14680, "(strcmp(");
        strcat(tmp_str14680, val);
        int tmp_strlen14672 = strlen(tmp_str14680) + strlen(", ") + 1;
        char* tmp_str14672 = calloc(tmp_strlen14672, sizeof(char));
        strcpy(tmp_str14672, tmp_str14680);
        strcat(tmp_str14672, ", ");
        int tmp_strlen14663 = strlen(tmp_str14672) + strlen(val_b) + 1;
        char* tmp_str14663 = calloc(tmp_strlen14663, sizeof(char));
        strcpy(tmp_str14663, tmp_str14672);
        strcat(tmp_str14663, val_b);
        int tmp_strlen14650 = strlen(tmp_str14663) + strlen(") == 0)") + 1;
        char* tmp_str14650 = calloc(tmp_strlen14650, sizeof(char));
        strcpy(tmp_str14650, tmp_str14663);
        strcat(tmp_str14650, ") == 0)");
        val = tmp_str14650;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen14577 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str14577 = calloc(tmp_strlen14577, sizeof(char));
          strcpy(tmp_str14577, "(strcmp(");
          strcat(tmp_str14577, val);
          int tmp_strlen14569 = strlen(tmp_str14577) + strlen(", ") + 1;
          char* tmp_str14569 = calloc(tmp_strlen14569, sizeof(char));
          strcpy(tmp_str14569, tmp_str14577);
          strcat(tmp_str14569, ", ");
          int tmp_strlen14560 = strlen(tmp_str14569) + strlen(val_b) + 1;
          char* tmp_str14560 = calloc(tmp_strlen14560, sizeof(char));
          strcpy(tmp_str14560, tmp_str14569);
          strcat(tmp_str14560, val_b);
          int tmp_strlen14547 = strlen(tmp_str14560) + strlen(") != 0)") + 1;
          char* tmp_str14547 = calloc(tmp_strlen14547, sizeof(char));
          strcpy(tmp_str14547, tmp_str14560);
          strcat(tmp_str14547, ") != 0)");
          val = tmp_str14547;
        } else {
          int tmp_strlen14501 = strlen("(") + strlen(val) + 1;
          char* tmp_str14501 = calloc(tmp_strlen14501, sizeof(char));
          strcpy(tmp_str14501, "(");
          strcat(tmp_str14501, val);
          int tmp_strlen14493 = strlen(tmp_str14501) + strlen(") ") + 1;
          char* tmp_str14493 = calloc(tmp_strlen14493, sizeof(char));
          strcpy(tmp_str14493, tmp_str14501);
          strcat(tmp_str14493, ") ");
          int tmp_strlen14483 = strlen(tmp_str14493) + strlen(op_str) + 1;
          char* tmp_str14483 = calloc(tmp_strlen14483, sizeof(char));
          strcpy(tmp_str14483, tmp_str14493);
          strcat(tmp_str14483, op_str);
          int tmp_strlen14475 = strlen(tmp_str14483) + strlen(" (") + 1;
          char* tmp_str14475 = calloc(tmp_strlen14475, sizeof(char));
          strcpy(tmp_str14475, tmp_str14483);
          strcat(tmp_str14475, " (");
          int tmp_strlen14466 = strlen(tmp_str14475) + strlen(val_b) + 1;
          char* tmp_str14466 = calloc(tmp_strlen14466, sizeof(char));
          strcpy(tmp_str14466, tmp_str14475);
          strcat(tmp_str14466, val_b);
          int tmp_strlen14459 = strlen(tmp_str14466) + strlen(")") + 1;
          char* tmp_str14459 = calloc(tmp_strlen14459, sizeof(char));
          strcpy(tmp_str14459, tmp_str14466);
          strcat(tmp_str14459, ")");
          val = tmp_str14459;
        }
      }
    }
    Peek_results tmp_results14440 = Peek(src);
    op = tmp_results14440.result1;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results14263 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results14263.result1;
  setup = tmp_results14263.result2;
  expr = tmp_results14263.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results14029 = TranslateExpr(src, indent);
  src = tmp_results14029.result1;
  expr_setup = tmp_results14029.result2;
  expr_value = tmp_results14029.result3;
  int tok;
  Peek_results tmp_results13951 = Peek(src);
  tok = tmp_results13951.result1;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results13786 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results13786.result1;
    TranslateExpr_results tmp_results13740 = TranslateExpr(src, indent);
    src = tmp_results13740.result1;
    expr_setup = tmp_results13740.result2;
    expr_value = tmp_results13740.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen13598 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str13598 = calloc(tmp_strlen13598, sizeof(char));
    strcpy(tmp_str13598, exprs_setup);
    strcat(tmp_str13598, expr_setup);
    exprs_setup = tmp_str13598;
    int tmp_strlen13556 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str13556 = calloc(tmp_strlen13556, sizeof(char));
    strcpy(tmp_str13556, exprs_value);
    strcat(tmp_str13556, ", ");
    int tmp_strlen13542 = strlen(tmp_str13556) + strlen(expr_value) + 1;
    char* tmp_str13542 = calloc(tmp_strlen13542, sizeof(char));
    strcpy(tmp_str13542, tmp_str13556);
    strcat(tmp_str13542, expr_value);
    exprs_value = tmp_str13542;
    Peek_results tmp_results13533 = Peek(src);
    tok = tmp_results13533.result1;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results13368 = ConsumeIdent(src);
  src = tmp_results13368.result1;
  name = tmp_results13368.result2;
  ConsumeToken_results tmp_results13334 = ConsumeToken(src, TOK_COLON);
  src = tmp_results13334.result1;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results13251 = TranslateType(src);
  src = tmp_results13251.result1;
  typ = tmp_results13251.result2;
  typ_str = tmp_results13251.result3;
  int tmp_strlen13176 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str13176 = calloc(tmp_strlen13176, sizeof(char));
  strcpy(tmp_str13176, typ_str);
  strcat(tmp_str13176, " ");
  int tmp_strlen13168 = strlen(tmp_str13176) + strlen(name) + 1;
  char* tmp_str13168 = calloc(tmp_strlen13168, sizeof(char));
  strcpy(tmp_str13168, tmp_str13176);
  strcat(tmp_str13168, name);
  char* out = tmp_str13168;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  ConsumeToken_results tmp_results13067 = ConsumeToken(src, TOK_LET);
  src = tmp_results13067.result1;
  char* out;
  TranslateConstOrVar_results tmp_results13007 = TranslateConstOrVar(src);
  src = tmp_results13007.result1;
  out = tmp_results13007.result2;
  int tmp_strlen12946 = strlen("const ") + strlen(out) + 1;
  char* tmp_str12946 = calloc(tmp_strlen12946, sizeof(char));
  strcpy(tmp_str12946, "const ");
  strcat(tmp_str12946, out);
  out = tmp_str12946;
  ConsumeToken_results tmp_results12941 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results12941.result1;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results12856 = TranslateExpr(src, indent);
  src = tmp_results12856.result1;
  setup = tmp_results12856.result2;
  val = tmp_results12856.result3;
  ConsumeToken_results tmp_results12807 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results12807.result1;
  int tmp_strlen12745 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str12745 = calloc(tmp_strlen12745, sizeof(char));
  strcpy(tmp_str12745, out);
  strcat(tmp_str12745, " = ");
  int tmp_strlen12738 = strlen(tmp_str12745) + strlen(val) + 1;
  char* tmp_str12738 = calloc(tmp_strlen12738, sizeof(char));
  strcpy(tmp_str12738, tmp_str12745);
  strcat(tmp_str12738, val);
  int tmp_strlen12729 = strlen(tmp_str12738) + strlen(";\n") + 1;
  char* tmp_str12729 = calloc(tmp_strlen12729, sizeof(char));
  strcpy(tmp_str12729, tmp_str12738);
  strcat(tmp_str12729, ";\n");
  out = tmp_str12729;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results12604 = TranslateConstDecl(src, indent);
  src = tmp_results12604.result1;
  out = tmp_results12604.result2;
  int tmp_strlen12532 = strlen(indent) + strlen(out) + 1;
  char* tmp_str12532 = calloc(tmp_strlen12532, sizeof(char));
  strcpy(tmp_str12532, indent);
  strcat(tmp_str12532, out);
  return (TranslateConstDeclStmt_results){src, tmp_str12532};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  ConsumeToken_results tmp_results12432 = ConsumeToken(src, TOK_VAR);
  src = tmp_results12432.result1;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results12325 = TranslateConstOrVar(src);
  src = tmp_results12325.result1;
  out = tmp_results12325.result2;
  Peek_results tmp_results12285 = Peek(src);
  tok = tmp_results12285.result1;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results12231 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results12231.result1;
    TranslateExpr_results tmp_results12184 = TranslateExpr(src, indent);
    src = tmp_results12184.result1;
    setup = tmp_results12184.result2;
    val = tmp_results12184.result3;
    ConsumeToken_results tmp_results12131 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results12131.result1;
    int tmp_strlen12065 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str12065 = calloc(tmp_strlen12065, sizeof(char));
    strcpy(tmp_str12065, out);
    strcat(tmp_str12065, " = ");
    int tmp_strlen12058 = strlen(tmp_str12065) + strlen(val) + 1;
    char* tmp_str12058 = calloc(tmp_strlen12058, sizeof(char));
    strcpy(tmp_str12058, tmp_str12065);
    strcat(tmp_str12058, val);
    out = tmp_str12058;
  }
  int tmp_strlen12026 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str12026 = calloc(tmp_strlen12026, sizeof(char));
  strcpy(tmp_str12026, setup);
  strcat(tmp_str12026, indent);
  int tmp_strlen12019 = strlen(tmp_str12026) + strlen(out) + 1;
  char* tmp_str12019 = calloc(tmp_strlen12019, sizeof(char));
  strcpy(tmp_str12019, tmp_str12026);
  strcat(tmp_str12019, out);
  int tmp_strlen12010 = strlen(tmp_str12019) + strlen(";\n") + 1;
  char* tmp_str12010 = calloc(tmp_strlen12010, sizeof(char));
  strcpy(tmp_str12010, tmp_str12019);
  strcat(tmp_str12010, ";\n");
  out = tmp_str12010;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen11855 = (x) - (0) + 1;
  char* tmp_str11855 = calloc(tmp_strlen11855, sizeof(char));
  strncpy(tmp_str11855, src + 0, tmp_strlen11855 - 1);
  tmp_str11855[tmp_strlen11855 - 1] = 0;
  char* lhs = tmp_str11855;
  int tmp_strlen11825 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str11825 = calloc(tmp_strlen11825, sizeof(char));
  strncpy(tmp_str11825, src + (x) + (1), tmp_strlen11825 - 1);
  tmp_str11825[tmp_strlen11825 - 1] = 0;
  char* rhs = tmp_str11825;
  char* lhs_ident;
  ConsumeIdentOrUnderscore_results tmp_results11788 = ConsumeIdentOrUnderscore(lhs);
  lhs = tmp_results11788.result1;
  lhs_ident = tmp_results11788.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results11660 = TranslateExpr(rhs, indent);
  rhs = tmp_results11660.result1;
  setup = tmp_results11660.result2;
  rhs_expr = tmp_results11660.result3;
  int lhs_tok;
  int rhs_tok;
  Peek_results tmp_results11564 = Peek(lhs);
  lhs_tok = tmp_results11564.result1;
  Peek_results tmp_results11537 = Peek(rhs);
  rhs_tok = tmp_results11537.result1;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results11422 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results11422.result1;
    func_name = tmp_results11422.result2;
    int tmp_strlen11314 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str11314 = calloc(tmp_strlen11314, sizeof(char));
    strcpy(tmp_str11314, "tmp_results");
    strcat(tmp_str11314, itoa(strlen(src)));
    char* tmp_results = tmp_str11314;
    char* out = setup;
    int tmp_strlen11254 = strlen(out) + strlen(indent) + 1;
    char* tmp_str11254 = calloc(tmp_strlen11254, sizeof(char));
    strcpy(tmp_str11254, out);
    strcat(tmp_str11254, indent);
    int tmp_strlen11241 = strlen(tmp_str11254) + strlen(func_name) + 1;
    char* tmp_str11241 = calloc(tmp_strlen11241, sizeof(char));
    strcpy(tmp_str11241, tmp_str11254);
    strcat(tmp_str11241, func_name);
    int tmp_strlen11226 = strlen(tmp_str11241) + strlen("_results ") + 1;
    char* tmp_str11226 = calloc(tmp_strlen11226, sizeof(char));
    strcpy(tmp_str11226, tmp_str11241);
    strcat(tmp_str11226, "_results ");
    int tmp_strlen11211 = strlen(tmp_str11226) + strlen(tmp_results) + 1;
    char* tmp_str11211 = calloc(tmp_strlen11211, sizeof(char));
    strcpy(tmp_str11211, tmp_str11226);
    strcat(tmp_str11211, tmp_results);
    int tmp_strlen11202 = strlen(tmp_str11211) + strlen(" = ") + 1;
    char* tmp_str11202 = calloc(tmp_strlen11202, sizeof(char));
    strcpy(tmp_str11202, tmp_str11211);
    strcat(tmp_str11202, " = ");
    int tmp_strlen11190 = strlen(tmp_str11202) + strlen(rhs_expr) + 1;
    char* tmp_str11190 = calloc(tmp_strlen11190, sizeof(char));
    strcpy(tmp_str11190, tmp_str11202);
    strcat(tmp_str11190, rhs_expr);
    int tmp_strlen11181 = strlen(tmp_str11190) + strlen(";\n") + 1;
    char* tmp_str11181 = calloc(tmp_strlen11181, sizeof(char));
    strcpy(tmp_str11181, tmp_str11190);
    strcat(tmp_str11181, ";\n");
    out = tmp_str11181;
    if ((strcmp(lhs_ident, "_") != 0)) {
      int tmp_strlen11118 = strlen(out) + strlen(indent) + 1;
      char* tmp_str11118 = calloc(tmp_strlen11118, sizeof(char));
      strcpy(tmp_str11118, out);
      strcat(tmp_str11118, indent);
      int tmp_strlen11105 = strlen(tmp_str11118) + strlen(lhs_ident) + 1;
      char* tmp_str11105 = calloc(tmp_strlen11105, sizeof(char));
      strcpy(tmp_str11105, tmp_str11118);
      strcat(tmp_str11105, lhs_ident);
      int tmp_strlen11096 = strlen(tmp_str11105) + strlen(" = ") + 1;
      char* tmp_str11096 = calloc(tmp_strlen11096, sizeof(char));
      strcpy(tmp_str11096, tmp_str11105);
      strcat(tmp_str11096, " = ");
      int tmp_strlen11081 = strlen(tmp_str11096) + strlen(tmp_results) + 1;
      char* tmp_str11081 = calloc(tmp_strlen11081, sizeof(char));
      strcpy(tmp_str11081, tmp_str11096);
      strcat(tmp_str11081, tmp_results);
      int tmp_strlen11064 = strlen(tmp_str11081) + strlen(".result1;\n") + 1;
      char* tmp_str11064 = calloc(tmp_strlen11064, sizeof(char));
      strcpy(tmp_str11064, tmp_str11081);
      strcat(tmp_str11064, ".result1;\n");
      out = tmp_str11064;
    }
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results10928 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results10928.result1;
      ConsumeIdentOrUnderscore_results tmp_results10878 = ConsumeIdentOrUnderscore(lhs);
      lhs = tmp_results10878.result1;
      lhs_ident = tmp_results10878.result2;
      if ((strcmp(lhs_ident, "_") != 0)) {
        int tmp_strlen10761 = strlen(out) + strlen(indent) + 1;
        char* tmp_str10761 = calloc(tmp_strlen10761, sizeof(char));
        strcpy(tmp_str10761, out);
        strcat(tmp_str10761, indent);
        int tmp_strlen10748 = strlen(tmp_str10761) + strlen(lhs_ident) + 1;
        char* tmp_str10748 = calloc(tmp_strlen10748, sizeof(char));
        strcpy(tmp_str10748, tmp_str10761);
        strcat(tmp_str10748, lhs_ident);
        int tmp_strlen10739 = strlen(tmp_str10748) + strlen(" = ") + 1;
        char* tmp_str10739 = calloc(tmp_strlen10739, sizeof(char));
        strcpy(tmp_str10739, tmp_str10748);
        strcat(tmp_str10739, " = ");
        int tmp_strlen10724 = strlen(tmp_str10739) + strlen(tmp_results) + 1;
        char* tmp_str10724 = calloc(tmp_strlen10724, sizeof(char));
        strcpy(tmp_str10724, tmp_str10739);
        strcat(tmp_str10724, tmp_results);
        int tmp_strlen10711 = strlen(tmp_str10724) + strlen(".result") + 1;
        char* tmp_str10711 = calloc(tmp_strlen10711, sizeof(char));
        strcpy(tmp_str10711, tmp_str10724);
        strcat(tmp_str10711, ".result");
        int tmp_strlen10689 = strlen(tmp_str10711) + strlen(itoa(result_count)) + 1;
        char* tmp_str10689 = calloc(tmp_strlen10689, sizeof(char));
        strcpy(tmp_str10689, tmp_str10711);
        strcat(tmp_str10689, itoa(result_count));
        int tmp_strlen10680 = strlen(tmp_str10689) + strlen(";\n") + 1;
        char* tmp_str10680 = calloc(tmp_strlen10680, sizeof(char));
        strcpy(tmp_str10680, tmp_str10689);
        strcat(tmp_str10680, ";\n");
        out = tmp_str10680;
      }
      Peek_results tmp_results10653 = Peek(lhs);
      lhs_tok = tmp_results10653.result1;
    }
    ConsumeToken_results tmp_results10612 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results10612.result1;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen10493 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str10493 = calloc(tmp_strlen10493, sizeof(char));
  strcpy(tmp_str10493, indent);
  strcat(tmp_str10493, lhs_ident);
  int tmp_strlen10484 = strlen(tmp_str10493) + strlen(" = ") + 1;
  char* tmp_str10484 = calloc(tmp_strlen10484, sizeof(char));
  strcpy(tmp_str10484, tmp_str10493);
  strcat(tmp_str10484, " = ");
  int tmp_strlen10472 = strlen(tmp_str10484) + strlen(rhs_expr) + 1;
  char* tmp_str10472 = calloc(tmp_strlen10472, sizeof(char));
  strcpy(tmp_str10472, tmp_str10484);
  strcat(tmp_str10472, rhs_expr);
  int tmp_strlen10463 = strlen(tmp_str10472) + strlen(";\n") + 1;
  char* tmp_str10463 = calloc(tmp_strlen10463, sizeof(char));
  strcpy(tmp_str10463, tmp_str10472);
  strcat(tmp_str10463, ";\n");
  char* assignments = tmp_str10463;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results10423 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results10423.result1;
    ConsumeToken_results tmp_results10377 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results10377.result1;
    ConsumeIdent_results tmp_results10331 = ConsumeIdent(lhs);
    lhs = tmp_results10331.result1;
    lhs_ident = tmp_results10331.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results10253 = TranslateExpr(rhs, indent);
    rhs = tmp_results10253.result1;
    rhs_expr_setup = tmp_results10253.result2;
    rhs_expr = tmp_results10253.result3;
    int tmp_strlen10155 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str10155 = calloc(tmp_strlen10155, sizeof(char));
    strcpy(tmp_str10155, setup);
    strcat(tmp_str10155, rhs_expr_setup);
    setup = tmp_str10155;
    int tmp_strlen10111 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str10111 = calloc(tmp_strlen10111, sizeof(char));
    strcpy(tmp_str10111, assignments);
    strcat(tmp_str10111, indent);
    int tmp_strlen10098 = strlen(tmp_str10111) + strlen(lhs_ident) + 1;
    char* tmp_str10098 = calloc(tmp_strlen10098, sizeof(char));
    strcpy(tmp_str10098, tmp_str10111);
    strcat(tmp_str10098, lhs_ident);
    int tmp_strlen10089 = strlen(tmp_str10098) + strlen(" = ") + 1;
    char* tmp_str10089 = calloc(tmp_strlen10089, sizeof(char));
    strcpy(tmp_str10089, tmp_str10098);
    strcat(tmp_str10089, " = ");
    int tmp_strlen10077 = strlen(tmp_str10089) + strlen(rhs_expr) + 1;
    char* tmp_str10077 = calloc(tmp_strlen10077, sizeof(char));
    strcpy(tmp_str10077, tmp_str10089);
    strcat(tmp_str10077, rhs_expr);
    int tmp_strlen10068 = strlen(tmp_str10077) + strlen(";\n") + 1;
    char* tmp_str10068 = calloc(tmp_strlen10068, sizeof(char));
    strcpy(tmp_str10068, tmp_str10077);
    strcat(tmp_str10068, ";\n");
    assignments = tmp_str10068;
    Peek_results tmp_results10059 = Peek(lhs);
    lhs_tok = tmp_results10059.result1;
  }
  ConsumeToken_results tmp_results10026 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results10026.result1;
  int tmp_strlen9950 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str9950 = calloc(tmp_strlen9950, sizeof(char));
  strcpy(tmp_str9950, setup);
  strcat(tmp_str9950, assignments);
  return (TranslateAssignStmt_results){src, tmp_str9950};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results9853 = ConsumeToken(src, TOK_IF);
  src = tmp_results9853.result1;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results9766 = TranslateExpr(src, indent);
  src = tmp_results9766.result1;
  cond_setup = tmp_results9766.result2;
  cond = tmp_results9766.result3;
  ConsumeToken_results tmp_results9711 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results9711.result1;
  char* out = cond_setup;
  int tmp_strlen9616 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9616 = calloc(tmp_strlen9616, sizeof(char));
  strcpy(tmp_str9616, out);
  strcat(tmp_str9616, indent);
  int tmp_strlen9606 = strlen(tmp_str9616) + strlen("if (") + 1;
  char* tmp_str9606 = calloc(tmp_strlen9606, sizeof(char));
  strcpy(tmp_str9606, tmp_str9616);
  strcat(tmp_str9606, "if (");
  int tmp_strlen9598 = strlen(tmp_str9606) + strlen(cond) + 1;
  char* tmp_str9598 = calloc(tmp_strlen9598, sizeof(char));
  strcpy(tmp_str9598, tmp_str9606);
  strcat(tmp_str9598, cond);
  int tmp_strlen9587 = strlen(tmp_str9598) + strlen(") {\n") + 1;
  char* tmp_str9587 = calloc(tmp_strlen9587, sizeof(char));
  strcpy(tmp_str9587, tmp_str9598);
  strcat(tmp_str9587, ") {\n");
  out = tmp_str9587;
  char* body;
  int tmp_strlen9506 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str9506 = calloc(tmp_strlen9506, sizeof(char));
  strcpy(tmp_str9506, indent);
  strcat(tmp_str9506, SINGLE_INDENT);
  TranslateStmts_results tmp_results9561 = TranslateStmts(src, tmp_str9506, func_name);
  src = tmp_results9561.result1;
  body = tmp_results9561.result2;
  ConsumeToken_results tmp_results9489 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results9489.result1;
  int tmp_strlen9429 = strlen(out) + strlen(body) + 1;
  char* tmp_str9429 = calloc(tmp_strlen9429, sizeof(char));
  strcpy(tmp_str9429, out);
  strcat(tmp_str9429, body);
  out = tmp_str9429;
  int tmp_strlen9405 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9405 = calloc(tmp_strlen9405, sizeof(char));
  strcpy(tmp_str9405, out);
  strcat(tmp_str9405, indent);
  int tmp_strlen9398 = strlen(tmp_str9405) + strlen("}") + 1;
  char* tmp_str9398 = calloc(tmp_strlen9398, sizeof(char));
  strcpy(tmp_str9398, tmp_str9405);
  strcat(tmp_str9398, "}");
  out = tmp_str9398;
  int tok;
  Peek_results tmp_results9376 = Peek(src);
  tok = tmp_results9376.result1;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen9301 = strlen(out) + strlen("\n") + 1;
    char* tmp_str9301 = calloc(tmp_strlen9301, sizeof(char));
    strcpy(tmp_str9301, out);
    strcat(tmp_str9301, "\n");
    return (TranslateIfStmt_results){src, tmp_str9301};
  }
  ConsumeToken_results tmp_results9290 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results9290.result1;
  Peek_results tmp_results9249 = Peek(src);
  tok = tmp_results9249.result1;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen9114 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str9114 = calloc(tmp_strlen9114, sizeof(char));
    strcpy(tmp_str9114, indent);
    strcat(tmp_str9114, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results9174 = TranslateIfStmt(src, tmp_str9114, func_name);
    src = tmp_results9174.result1;
    else_out = tmp_results9174.result2;
    int tmp_strlen9069 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str9069 = calloc(tmp_strlen9069, sizeof(char));
    strcpy(tmp_str9069, out);
    strcat(tmp_str9069, " else {\n");
    out = tmp_str9069;
    int tmp_strlen9039 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str9039 = calloc(tmp_strlen9039, sizeof(char));
    strcpy(tmp_str9039, out);
    strcat(tmp_str9039, else_out);
    out = tmp_str9039;
    int tmp_strlen9011 = strlen(out) + strlen(indent) + 1;
    char* tmp_str9011 = calloc(tmp_strlen9011, sizeof(char));
    strcpy(tmp_str9011, out);
    strcat(tmp_str9011, indent);
    int tmp_strlen9002 = strlen(tmp_str9011) + strlen("}\n") + 1;
    char* tmp_str9002 = calloc(tmp_strlen9002, sizeof(char));
    strcpy(tmp_str9002, tmp_str9011);
    strcat(tmp_str9002, "}\n");
    out = tmp_str9002;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results8967 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8967.result1;
  int tmp_strlen8865 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str8865 = calloc(tmp_strlen8865, sizeof(char));
  strcpy(tmp_str8865, indent);
  strcat(tmp_str8865, SINGLE_INDENT);
  TranslateStmts_results tmp_results8924 = TranslateStmts(src, tmp_str8865, func_name);
  src = tmp_results8924.result1;
  else_out = tmp_results8924.result2;
  ConsumeToken_results tmp_results8848 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results8848.result1;
  int tmp_strlen8781 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str8781 = calloc(tmp_strlen8781, sizeof(char));
  strcpy(tmp_str8781, out);
  strcat(tmp_str8781, " else {\n");
  out = tmp_str8781;
  int tmp_strlen8755 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str8755 = calloc(tmp_strlen8755, sizeof(char));
  strcpy(tmp_str8755, out);
  strcat(tmp_str8755, else_out);
  out = tmp_str8755;
  int tmp_strlen8731 = strlen(out) + strlen(indent) + 1;
  char* tmp_str8731 = calloc(tmp_strlen8731, sizeof(char));
  strcpy(tmp_str8731, out);
  strcat(tmp_str8731, indent);
  int tmp_strlen8722 = strlen(tmp_str8731) + strlen("}\n") + 1;
  char* tmp_str8722 = calloc(tmp_strlen8722, sizeof(char));
  strcpy(tmp_str8722, tmp_str8731);
  strcat(tmp_str8722, "}\n");
  out = tmp_str8722;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  ConsumeToken_results tmp_results8587 = ConsumeToken(src, TOK_FOR);
  src = tmp_results8587.result1;
  Peek_results tmp_results8547 = Peek(src);
  tok = tmp_results8547.result1;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen8365 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8365 = calloc(tmp_strlen8365, sizeof(char));
    strcpy(tmp_str8365, indent);
    strcat(tmp_str8365, SINGLE_INDENT);
    TranslateExpr_results tmp_results8431 = TranslateExpr(src, tmp_str8365);
    src = tmp_results8431.result1;
    cond_setup = tmp_results8431.result2;
    cond = tmp_results8431.result3;
  }
  ConsumeToken_results tmp_results8353 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8353.result1;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen8235 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str8235 = calloc(tmp_strlen8235, sizeof(char));
    strcpy(tmp_str8235, indent);
    strcat(tmp_str8235, "while (");
    int tmp_strlen8227 = strlen(tmp_str8235) + strlen(cond) + 1;
    char* tmp_str8227 = calloc(tmp_strlen8227, sizeof(char));
    strcpy(tmp_str8227, tmp_str8235);
    strcat(tmp_str8227, cond);
    int tmp_strlen8216 = strlen(tmp_str8227) + strlen(") {\n") + 1;
    char* tmp_str8216 = calloc(tmp_strlen8216, sizeof(char));
    strcpy(tmp_str8216, tmp_str8227);
    strcat(tmp_str8216, ") {\n");
    out = tmp_str8216;
  } else {
    int tmp_strlen8160 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str8160 = calloc(tmp_strlen8160, sizeof(char));
    strcpy(tmp_str8160, indent);
    strcat(tmp_str8160, "while (true) {\n");
    out = tmp_str8160;
    int tmp_strlen8128 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str8128 = calloc(tmp_strlen8128, sizeof(char));
    strcpy(tmp_str8128, out);
    strcat(tmp_str8128, cond_setup);
    out = tmp_str8128;
    int tmp_strlen8100 = strlen(out) + strlen(indent) + 1;
    char* tmp_str8100 = calloc(tmp_strlen8100, sizeof(char));
    strcpy(tmp_str8100, out);
    strcat(tmp_str8100, indent);
    int tmp_strlen8083 = strlen(tmp_str8100) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8083 = calloc(tmp_strlen8083, sizeof(char));
    strcpy(tmp_str8083, tmp_str8100);
    strcat(tmp_str8083, SINGLE_INDENT);
    int tmp_strlen8071 = strlen(tmp_str8083) + strlen("if (!(") + 1;
    char* tmp_str8071 = calloc(tmp_strlen8071, sizeof(char));
    strcpy(tmp_str8071, tmp_str8083);
    strcat(tmp_str8071, "if (!(");
    int tmp_strlen8063 = strlen(tmp_str8071) + strlen(cond) + 1;
    char* tmp_str8063 = calloc(tmp_strlen8063, sizeof(char));
    strcpy(tmp_str8063, tmp_str8071);
    strcat(tmp_str8063, cond);
    int tmp_strlen8046 = strlen(tmp_str8063) + strlen(")) break;\n") + 1;
    char* tmp_str8046 = calloc(tmp_strlen8046, sizeof(char));
    strcpy(tmp_str8046, tmp_str8063);
    strcat(tmp_str8046, ")) break;\n");
    out = tmp_str8046;
  }
  char* body;
  int tmp_strlen7959 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str7959 = calloc(tmp_strlen7959, sizeof(char));
  strcpy(tmp_str7959, indent);
  strcat(tmp_str7959, SINGLE_INDENT);
  TranslateStmts_results tmp_results8014 = TranslateStmts(src, tmp_str7959, func_name);
  src = tmp_results8014.result1;
  body = tmp_results8014.result2;
  ConsumeToken_results tmp_results7942 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results7942.result1;
  int tmp_strlen7882 = strlen(out) + strlen(body) + 1;
  char* tmp_str7882 = calloc(tmp_strlen7882, sizeof(char));
  strcpy(tmp_str7882, out);
  strcat(tmp_str7882, body);
  out = tmp_str7882;
  int tmp_strlen7858 = strlen(out) + strlen(indent) + 1;
  char* tmp_str7858 = calloc(tmp_strlen7858, sizeof(char));
  strcpy(tmp_str7858, out);
  strcat(tmp_str7858, indent);
  int tmp_strlen7849 = strlen(tmp_str7858) + strlen("}\n") + 1;
  char* tmp_str7849 = calloc(tmp_strlen7849, sizeof(char));
  strcpy(tmp_str7849, tmp_str7858);
  strcat(tmp_str7849, "}\n");
  out = tmp_str7849;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results7745 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results7745.result1;
  int tmp_strlen7667 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str7667 = calloc(tmp_strlen7667, sizeof(char));
  strcpy(tmp_str7667, indent);
  strcat(tmp_str7667, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str7667};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results7586 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results7586.result1;
  int tmp_strlen7514 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str7514 = calloc(tmp_strlen7514, sizeof(char));
  strcpy(tmp_str7514, indent);
  strcat(tmp_str7514, "break;");
  return (TranslateBreakStmt_results){src, tmp_str7514};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results7413 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results7413.result1;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results7290 = TranslateExprs(src, indent);
  src = tmp_results7290.result1;
  expr_count = tmp_results7290.result2;
  exprs_setup = tmp_results7290.result3;
  exprs_value = tmp_results7290.result4;
  ConsumeToken_results tmp_results7214 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results7214.result1;
  int tmp_strlen7131 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str7131 = calloc(tmp_strlen7131, sizeof(char));
  strcpy(tmp_str7131, exprs_setup);
  strcat(tmp_str7131, indent);
  int tmp_strlen7118 = strlen(tmp_str7131) + strlen("return ") + 1;
  char* tmp_str7118 = calloc(tmp_strlen7118, sizeof(char));
  strcpy(tmp_str7118, tmp_str7131);
  strcat(tmp_str7118, "return ");
  char* out = tmp_str7118;
  if ((expr_count) > (1)) {
    int tmp_strlen7069 = strlen(out) + strlen("(") + 1;
    char* tmp_str7069 = calloc(tmp_strlen7069, sizeof(char));
    strcpy(tmp_str7069, out);
    strcat(tmp_str7069, "(");
    int tmp_strlen7056 = strlen(tmp_str7069) + strlen(func_name) + 1;
    char* tmp_str7056 = calloc(tmp_strlen7056, sizeof(char));
    strcpy(tmp_str7056, tmp_str7069);
    strcat(tmp_str7056, func_name);
    int tmp_strlen7040 = strlen(tmp_str7056) + strlen("_results){") + 1;
    char* tmp_str7040 = calloc(tmp_strlen7040, sizeof(char));
    strcpy(tmp_str7040, tmp_str7056);
    strcat(tmp_str7040, "_results){");
    out = tmp_str7040;
  }
  int tmp_strlen7005 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str7005 = calloc(tmp_strlen7005, sizeof(char));
  strcpy(tmp_str7005, out);
  strcat(tmp_str7005, exprs_value);
  out = tmp_str7005;
  if ((expr_count) > (1)) {
    int tmp_strlen6955 = strlen(out) + strlen("}") + 1;
    char* tmp_str6955 = calloc(tmp_strlen6955, sizeof(char));
    strcpy(tmp_str6955, out);
    strcat(tmp_str6955, "}");
    out = tmp_str6955;
  }
  int tmp_strlen6926 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str6926 = calloc(tmp_strlen6926, sizeof(char));
  strcpy(tmp_str6926, out);
  strcat(tmp_str6926, ";\n");
  out = tmp_str6926;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6770 = Peek(src);
  tok = tmp_results6770.result1;
  tok_str = tmp_results6770.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results6693 = TranslateConstDeclStmt(src, indent);
    src = tmp_results6693.result1;
    out = tmp_results6693.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results6583 = TranslateVarDeclStmt(src, indent);
      src = tmp_results6583.result1;
      out = tmp_results6583.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results6476 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results6476.result1;
        out = tmp_results6476.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results6362 = TranslateForStmt(src, indent, func_name);
          src = tmp_results6362.result1;
          out = tmp_results6362.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results6242 = TranslateContinueStmt(src, indent);
            src = tmp_results6242.result1;
            out = tmp_results6242.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results6131 = TranslateBreakStmt(src, indent);
              src = tmp_results6131.result1;
              out = tmp_results6131.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results6022 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results6022.result1;
                out = tmp_results6022.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if (((tok) == (TOK_IDENT)) || ((tok) == (TOK_UNDERSCORE))) {
                  char* first_ident;
                  ConsumeIdentOrUnderscore_results tmp_results5845 = ConsumeIdentOrUnderscore(src);
                  src = tmp_results5845.result1;
                  first_ident = tmp_results5845.result2;
                  Peek_results tmp_results5788 = Peek(src);
                  tok = tmp_results5788.result1;
                  int tmp_strlen5737 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str5737 = calloc(tmp_strlen5737, sizeof(char));
                  strcpy(tmp_str5737, first_ident);
                  strcat(tmp_str5737, src);
                  src = tmp_str5737;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results5673 = TranslateAssignStmt(src, indent);
                    src = tmp_results5673.result1;
                    out = tmp_results5673.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results5514 = TranslateExpr(src, indent);
                    src = tmp_results5514.result1;
                    setup = tmp_results5514.result2;
                    val = tmp_results5514.result3;
                    ConsumeToken_results tmp_results5457 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results5457.result1;
                    int tmp_strlen5384 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str5384 = calloc(tmp_strlen5384, sizeof(char));
                    strcpy(tmp_str5384, setup);
                    strcat(tmp_str5384, indent);
                    int tmp_strlen5377 = strlen(tmp_str5384) + strlen(val) + 1;
                    char* tmp_str5377 = calloc(tmp_strlen5377, sizeof(char));
                    strcpy(tmp_str5377, tmp_str5384);
                    strcat(tmp_str5377, val);
                    int tmp_strlen5368 = strlen(tmp_str5377) + strlen(";\n") + 1;
                    char* tmp_str5368 = calloc(tmp_strlen5368, sizeof(char));
                    strcpy(tmp_str5368, tmp_str5377);
                    strcat(tmp_str5368, ";\n");
                    out = tmp_str5368;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen5259 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str5259 = calloc(tmp_strlen5259, sizeof(char));
                  strcpy(tmp_str5259, "unexpected stmt token, got: ");
                  strcat(tmp_str5259, itoa(tok));
                  int tmp_strlen5250 = strlen(tmp_str5259) + strlen(" \"") + 1;
                  char* tmp_str5250 = calloc(tmp_strlen5250, sizeof(char));
                  strcpy(tmp_str5250, tmp_str5259);
                  strcat(tmp_str5250, " \"");
                  int tmp_strlen5239 = strlen(tmp_str5250) + strlen(tok_str) + 1;
                  char* tmp_str5239 = calloc(tmp_strlen5239, sizeof(char));
                  strcpy(tmp_str5239, tmp_str5250);
                  strcat(tmp_str5239, tok_str);
                  int tmp_strlen5231 = strlen(tmp_str5239) + strlen("\"") + 1;
                  char* tmp_str5231 = calloc(tmp_strlen5231, sizeof(char));
                  strcpy(tmp_str5231, tmp_str5239);
                  strcat(tmp_str5231, "\"");
                  printf("%s", tmp_str5231);
                  exit(1);
                }
              }
            }
          }
        }
      }
    }
  }
}

TranslateStmts_results TranslateStmts(char* src, char* indent, char* func_name) {
  int tok;
  Peek_results tmp_results5095 = Peek(src);
  tok = tmp_results5095.result1;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results4979 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results4979.result1;
      Peek_results tmp_results4927 = Peek(src);
      tok = tmp_results4927.result1;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results4840 = TranslateStmt(src, indent, func_name);
    src = tmp_results4840.result1;
    stmt_out = tmp_results4840.result2;
    int tmp_strlen4757 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str4757 = calloc(tmp_strlen4757, sizeof(char));
    strcpy(tmp_str4757, out);
    strcat(tmp_str4757, stmt_out);
    out = tmp_str4757;
    Peek_results tmp_results4748 = Peek(src);
    tok = tmp_results4748.result1;
  }
  return (TranslateStmts_results){src, out};
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  ConsumeToken_results tmp_results4623 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results4623.result1;
  Peek_results tmp_results4580 = Peek(src);
  tok = tmp_results4580.result1;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results4526 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results4526.result1;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results4431 = TranslateConstOrVar(src);
  src = tmp_results4431.result1;
  args = tmp_results4431.result2;
  Peek_results tmp_results4390 = Peek(src);
  tok = tmp_results4390.result1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results4336 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results4336.result1;
    char* arg;
    TranslateConstOrVar_results tmp_results4266 = TranslateConstOrVar(src);
    src = tmp_results4266.result1;
    arg = tmp_results4266.result2;
    int tmp_strlen4203 = strlen(args) + strlen(", ") + 1;
    char* tmp_str4203 = calloc(tmp_strlen4203, sizeof(char));
    strcpy(tmp_str4203, args);
    strcat(tmp_str4203, ", ");
    int tmp_strlen4196 = strlen(tmp_str4203) + strlen(arg) + 1;
    char* tmp_str4196 = calloc(tmp_strlen4196, sizeof(char));
    strcpy(tmp_str4196, tmp_str4203);
    strcat(tmp_str4196, arg);
    args = tmp_str4196;
    Peek_results tmp_results4187 = Peek(src);
    tok = tmp_results4187.result1;
  }
  ConsumeToken_results tmp_results4158 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results4158.result1;
  int tmp_strlen4092 = strlen("(") + strlen(args) + 1;
  char* tmp_str4092 = calloc(tmp_strlen4092, sizeof(char));
  strcpy(tmp_str4092, "(");
  strcat(tmp_str4092, args);
  int tmp_strlen4085 = strlen(tmp_str4092) + strlen(")") + 1;
  char* tmp_str4085 = calloc(tmp_strlen4085, sizeof(char));
  strcpy(tmp_str4085, tmp_str4092);
  strcat(tmp_str4085, ")");
  return (TranslateFuncArgs_results){src, tmp_str4085};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  Peek_results tmp_results3933 = Peek(src);
  tok = tmp_results3933.result1;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results3879 = TranslateType(src);
    src = tmp_results3879.result1;
    typ = tmp_results3879.result2;
    typ_str = tmp_results3879.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results3798 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results3798.result1;
  TranslateType_results tmp_results3755 = TranslateType(src);
  src = tmp_results3755.result1;
  typ = tmp_results3755.result2;
  typ_str = tmp_results3755.result3;
  Peek_results tmp_results3712 = Peek(src);
  tok = tmp_results3712.result1;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results3659 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results3659.result1;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen3524 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str3524 = calloc(tmp_strlen3524, sizeof(char));
  strcpy(tmp_str3524, "typedef struct {\n");
  strcat(tmp_str3524, SINGLE_INDENT);
  int tmp_strlen3513 = strlen(tmp_str3524) + strlen(typ_str) + 1;
  char* tmp_str3513 = calloc(tmp_strlen3513, sizeof(char));
  strcpy(tmp_str3513, tmp_str3524);
  strcat(tmp_str3513, typ_str);
  int tmp_strlen3496 = strlen(tmp_str3513) + strlen(" result1;\n") + 1;
  char* tmp_str3496 = calloc(tmp_strlen3496, sizeof(char));
  strcpy(tmp_str3496, tmp_str3513);
  strcat(tmp_str3496, " result1;\n");
  char* td = tmp_str3496;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results3433 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results3433.result1;
    TranslateType_results tmp_results3387 = TranslateType(src);
    src = tmp_results3387.result1;
    typ = tmp_results3387.result2;
    typ_str = tmp_results3387.result3;
    res_count = (res_count) + (1);
    int tmp_strlen3282 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str3282 = calloc(tmp_strlen3282, sizeof(char));
    strcpy(tmp_str3282, td);
    strcat(tmp_str3282, SINGLE_INDENT);
    int tmp_strlen3271 = strlen(tmp_str3282) + strlen(typ_str) + 1;
    char* tmp_str3271 = calloc(tmp_strlen3271, sizeof(char));
    strcpy(tmp_str3271, tmp_str3282);
    strcat(tmp_str3271, typ_str);
    int tmp_strlen3258 = strlen(tmp_str3271) + strlen(" result") + 1;
    char* tmp_str3258 = calloc(tmp_strlen3258, sizeof(char));
    strcpy(tmp_str3258, tmp_str3271);
    strcat(tmp_str3258, " result");
    int tmp_strlen3239 = strlen(tmp_str3258) + strlen(itoa(res_count)) + 1;
    char* tmp_str3239 = calloc(tmp_strlen3239, sizeof(char));
    strcpy(tmp_str3239, tmp_str3258);
    strcat(tmp_str3239, itoa(res_count));
    int tmp_strlen3230 = strlen(tmp_str3239) + strlen(";\n") + 1;
    char* tmp_str3230 = calloc(tmp_strlen3230, sizeof(char));
    strcpy(tmp_str3230, tmp_str3239);
    strcat(tmp_str3230, ";\n");
    td = tmp_str3230;
    Peek_results tmp_results3221 = Peek(src);
    tok = tmp_results3221.result1;
  }
  ConsumeToken_results tmp_results3192 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results3192.result1;
  int tmp_strlen3134 = strlen(td) + strlen("} ") + 1;
  char* tmp_str3134 = calloc(tmp_strlen3134, sizeof(char));
  strcpy(tmp_str3134, td);
  strcat(tmp_str3134, "} ");
  int tmp_strlen3121 = strlen(tmp_str3134) + strlen(func_name) + 1;
  char* tmp_str3121 = calloc(tmp_strlen3121, sizeof(char));
  strcpy(tmp_str3121, tmp_str3134);
  strcat(tmp_str3121, func_name);
  int tmp_strlen3104 = strlen(tmp_str3121) + strlen("_results;\n") + 1;
  char* tmp_str3104 = calloc(tmp_strlen3104, sizeof(char));
  strcpy(tmp_str3104, tmp_str3121);
  strcat(tmp_str3104, "_results;\n");
  td = tmp_str3104;
  int tmp_strlen3060 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str3060 = calloc(tmp_strlen3060, sizeof(char));
  strcpy(tmp_str3060, func_name);
  strcat(tmp_str3060, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str3060};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* name;
  ConsumeToken_results tmp_results2954 = ConsumeToken(src, TOK_FN);
  src = tmp_results2954.result1;
  ConsumeIdent_results tmp_results2915 = ConsumeIdent(src);
  src = tmp_results2915.result1;
  name = tmp_results2915.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  }
  Peek_results tmp_results2655 = Peek(src);
  tok = tmp_results2655.result1;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results2601 = TranslateFuncArgs(src);
    src = tmp_results2601.result1;
    args = tmp_results2601.result2;
    Peek_results tmp_results2558 = Peek(src);
    tok = tmp_results2558.result1;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results2496 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results2496.result1;
      TranslateFuncResults_results tmp_results2445 = TranslateFuncResults(src, name);
      src = tmp_results2445.result1;
      results_type_def = tmp_results2445.result2;
      results_type_name = tmp_results2445.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results2324 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results2324.result1;
  int tmp_strlen2225 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str2225 = calloc(tmp_strlen2225, sizeof(char));
  strcpy(tmp_str2225, SINGLE_INDENT);
  strcat(tmp_str2225, "");
  TranslateStmts_results tmp_results2281 = TranslateStmts(src, tmp_str2225, name);
  src = tmp_results2281.result1;
  stmts_out = tmp_results2281.result2;
  ConsumeToken_results tmp_results2213 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results2213.result1;
  int tmp_strlen2129 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str2129 = calloc(tmp_strlen2129, sizeof(char));
  strcpy(tmp_str2129, results_type_name);
  strcat(tmp_str2129, " ");
  int tmp_strlen2121 = strlen(tmp_str2129) + strlen(name) + 1;
  char* tmp_str2121 = calloc(tmp_strlen2121, sizeof(char));
  strcpy(tmp_str2121, tmp_str2129);
  strcat(tmp_str2121, name);
  int tmp_strlen2113 = strlen(tmp_str2121) + strlen(args) + 1;
  char* tmp_str2113 = calloc(tmp_strlen2113, sizeof(char));
  strcpy(tmp_str2113, tmp_str2121);
  strcat(tmp_str2113, args);
  char* df = tmp_str2113;
  int tmp_strlen2067 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str2067 = calloc(tmp_strlen2067, sizeof(char));
  strcpy(tmp_str2067, results_type_def);
  strcat(tmp_str2067, df);
  int tmp_strlen2058 = strlen(tmp_str2067) + strlen(";\n") + 1;
  char* tmp_str2058 = calloc(tmp_strlen2058, sizeof(char));
  strcpy(tmp_str2058, tmp_str2067);
  strcat(tmp_str2058, ";\n");
  char* decl = tmp_str2058;
  int tmp_strlen2036 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str2036 = calloc(tmp_strlen2036, sizeof(char));
  strcpy(tmp_str2036, df);
  strcat(tmp_str2036, " {\n");
  df = tmp_str2036;
  int tmp_strlen2011 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str2011 = calloc(tmp_strlen2011, sizeof(char));
  strcpy(tmp_str2011, df);
  strcat(tmp_str2011, stmts_out);
  df = tmp_str2011;
  if ((strcmp(name, "_main") == 0)) {
    int tmp_strlen1951 = strlen(df) + strlen("  return 0;\n") + 1;
    char* tmp_str1951 = calloc(tmp_strlen1951, sizeof(char));
    strcpy(tmp_str1951, df);
    strcat(tmp_str1951, "  return 0;\n");
    df = tmp_str1951;
  }
  int tmp_strlen1922 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str1922 = calloc(tmp_strlen1922, sizeof(char));
  strcpy(tmp_str1922, df);
  strcat(tmp_str1922, "}\n\n");
  df = tmp_str1922;
  return (TranslateFunc_results){src, decl, df};
}

char* TranslateProgram(char* src) {
  char* out = read("clib/lib.c");
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results1678 = Peek(src);
  tok = tmp_results1678.result1;
  tok_str = tmp_results1678.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results1584 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results1584.result1;
      Peek_results tmp_results1532 = Peek(src);
      tok = tmp_results1532.result1;
      tok_str = tmp_results1532.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results1404 = TranslateConstDecl(src, "");
        src = tmp_results1404.result1;
        const_decl = tmp_results1404.result2;
        int tmp_strlen1311 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str1311 = calloc(tmp_strlen1311, sizeof(char));
        strcpy(tmp_str1311, constants);
        strcat(tmp_str1311, const_decl);
        constants = tmp_str1311;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          TranslateFunc_results tmp_results1201 = TranslateFunc(src);
          src = tmp_results1201.result1;
          fn_decl = tmp_results1201.result2;
          fn_def = tmp_results1201.result3;
          int tmp_strlen1123 = strlen(decls) + strlen(fn_decl) + 1;
          char* tmp_str1123 = calloc(tmp_strlen1123, sizeof(char));
          strcpy(tmp_str1123, decls);
          strcat(tmp_str1123, fn_decl);
          decls = tmp_str1123;
          int tmp_strlen1089 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str1089 = calloc(tmp_strlen1089, sizeof(char));
          strcpy(tmp_str1089, defs);
          strcat(tmp_str1089, fn_def);
          defs = tmp_str1089;
        } else {
          int tmp_strlen1010 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str1010 = calloc(tmp_strlen1010, sizeof(char));
          strcpy(tmp_str1010, "unexpected decl token, got: ");
          strcat(tmp_str1010, itoa(tok));
          int tmp_strlen1001 = strlen(tmp_str1010) + strlen(" \"") + 1;
          char* tmp_str1001 = calloc(tmp_strlen1001, sizeof(char));
          strcpy(tmp_str1001, tmp_str1010);
          strcat(tmp_str1001, " \"");
          int tmp_strlen990 = strlen(tmp_str1001) + strlen(tok_str) + 1;
          char* tmp_str990 = calloc(tmp_strlen990, sizeof(char));
          strcpy(tmp_str990, tmp_str1001);
          strcat(tmp_str990, tok_str);
          int tmp_strlen982 = strlen(tmp_str990) + strlen("\"") + 1;
          char* tmp_str982 = calloc(tmp_strlen982, sizeof(char));
          strcpy(tmp_str982, tmp_str990);
          strcat(tmp_str982, "\"");
          printf("%s", tmp_str982);
          exit(1);
        }
      }
    }
    Peek_results tmp_results942 = Peek(src);
    tok = tmp_results942.result1;
    tok_str = tmp_results942.result2;
  }
  ConsumeToken_results tmp_results907 = ConsumeToken(src, TOK_EOF);
  src = tmp_results907.result1;
  if ((strcmp(constants, "") != 0)) {
    int tmp_strlen815 = strlen(out) + strlen(constants) + 1;
    char* tmp_str815 = calloc(tmp_strlen815, sizeof(char));
    strcpy(tmp_str815, out);
    strcat(tmp_str815, constants);
    int tmp_strlen807 = strlen(tmp_str815) + strlen("\n") + 1;
    char* tmp_str807 = calloc(tmp_strlen807, sizeof(char));
    strcpy(tmp_str807, tmp_str815);
    strcat(tmp_str807, "\n");
    out = tmp_str807;
  }
  if ((strcmp(decls, "") != 0)) {
    int tmp_strlen752 = strlen(out) + strlen(decls) + 1;
    char* tmp_str752 = calloc(tmp_strlen752, sizeof(char));
    strcpy(tmp_str752, out);
    strcat(tmp_str752, decls);
    int tmp_strlen744 = strlen(tmp_str752) + strlen("\n") + 1;
    char* tmp_str744 = calloc(tmp_strlen744, sizeof(char));
    strcpy(tmp_str744, tmp_str752);
    strcat(tmp_str744, "\n");
    out = tmp_str744;
  }
  if ((strcmp(defs, "") != 0)) {
    int tmp_strlen691 = strlen(out) + strlen(defs) + 1;
    char* tmp_str691 = calloc(tmp_strlen691, sizeof(char));
    strcpy(tmp_str691, out);
    strcat(tmp_str691, defs);
    int tmp_strlen683 = strlen(tmp_str691) + strlen("\n") + 1;
    char* tmp_str683 = calloc(tmp_strlen683, sizeof(char));
    strcpy(tmp_str683, tmp_str691);
    strcat(tmp_str683, "\n");
    out = tmp_str683;
  }
  return out;
}

char* ReadSrc(char* src_dir) {
  char* src = "";
  char* src_files = direntries(src_dir);
  char* src_file;
  Split_results tmp_results516 = Split(src_files);
  src_file = tmp_results516.result1;
  src_files = tmp_results516.result2;
  while (((strlen(src_files)) > (0)) || ((strlen(src_file)) > (0))) {
    if (EndsWith(src_file, ".sk")) {
      int tmp_strlen344 = strlen(src_dir) + strlen("/") + 1;
      char* tmp_str344 = calloc(tmp_strlen344, sizeof(char));
      strcpy(tmp_str344, src_dir);
      strcat(tmp_str344, "/");
      int tmp_strlen332 = strlen(tmp_str344) + strlen(src_file) + 1;
      char* tmp_str332 = calloc(tmp_strlen332, sizeof(char));
      strcpy(tmp_str332, tmp_str344);
      strcat(tmp_str332, src_file);
      int tmp_strlen331 = strlen(src) + strlen(read(tmp_str332)) + 1;
      char* tmp_str331 = calloc(tmp_strlen331, sizeof(char));
      strcpy(tmp_str331, src);
      strcat(tmp_str331, read(tmp_str332));
      int tmp_strlen323 = strlen(tmp_str331) + strlen("\n") + 1;
      char* tmp_str323 = calloc(tmp_strlen323, sizeof(char));
      strcpy(tmp_str323, tmp_str331);
      strcat(tmp_str323, "\n");
      src = tmp_str323;
    }
    Split_results tmp_results304 = Split(src_files);
    src_file = tmp_results304.result1;
    src_files = tmp_results304.result2;
  }
  return src;
}

int _main(char* args) {
  int i = Find(args, " ");
  int tmp_strlen154 = (i) - (0) + 1;
  char* tmp_str154 = calloc(tmp_strlen154, sizeof(char));
  strncpy(tmp_str154, args + 0, tmp_strlen154 - 1);
  tmp_str154[tmp_strlen154 - 1] = 0;
  char* src_dir = tmp_str154;
  char* src = ReadSrc(src_dir);
  char* out = TranslateProgram(src);
  int tmp_strlen35 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str35 = calloc(tmp_strlen35, sizeof(char));
  strncpy(tmp_str35, args + (i) + (1), tmp_strlen35 - 1);
  tmp_str35[tmp_strlen35 - 1] = 0;
  char* out_file = tmp_str35;
  write(out_file, out);
  return 0;
}


