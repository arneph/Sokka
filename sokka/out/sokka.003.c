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
bool IsUnaryOp(int tok);
bool IsBinaryOp(int tok);
int Precedence(int tok);
typedef struct {
  char* result1;
  int result2;
  char* result3;
} TranslateType_results;
TranslateType_results TranslateType(char* src);
char* ReadSrc(char* src_dir);
char* TranslateProgram(char* src);
int _main(char* args);
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

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen31383 = (strlen(src)) - (2) + 1;
      char* tmp_str31383 = calloc(tmp_strlen31383, sizeof(char));
      strncpy(tmp_str31383, src + 2, tmp_strlen31383 - 1);
      tmp_str31383[tmp_strlen31383 - 1] = 0;
      return (Next_results){tmp_str31383, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen31304 = (strlen(src)) - (2) + 1;
        char* tmp_str31304 = calloc(tmp_strlen31304, sizeof(char));
        strncpy(tmp_str31304, src + 2, tmp_strlen31304 - 1);
        tmp_str31304[tmp_strlen31304 - 1] = 0;
        return (Next_results){tmp_str31304, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen31228 = (strlen(src)) - (2) + 1;
          char* tmp_str31228 = calloc(tmp_strlen31228, sizeof(char));
          strncpy(tmp_str31228, src + 2, tmp_strlen31228 - 1);
          tmp_str31228[tmp_strlen31228 - 1] = 0;
          return (Next_results){tmp_str31228, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen31151 = (strlen(src)) - (2) + 1;
            char* tmp_str31151 = calloc(tmp_strlen31151, sizeof(char));
            strncpy(tmp_str31151, src + 2, tmp_strlen31151 - 1);
            tmp_str31151[tmp_strlen31151 - 1] = 0;
            return (Next_results){tmp_str31151, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen31076 = (strlen(src)) - (2) + 1;
              char* tmp_str31076 = calloc(tmp_strlen31076, sizeof(char));
              strncpy(tmp_str31076, src + 2, tmp_strlen31076 - 1);
              tmp_str31076[tmp_strlen31076 - 1] = 0;
              return (Next_results){tmp_str31076, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen31000 = (strlen(src)) - (2) + 1;
                char* tmp_str31000 = calloc(tmp_strlen31000, sizeof(char));
                strncpy(tmp_str31000, src + 2, tmp_strlen31000 - 1);
                tmp_str31000[tmp_strlen31000 - 1] = 0;
                return (Next_results){tmp_str31000, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen30924 = (strlen(src)) - (2) + 1;
                  char* tmp_str30924 = calloc(tmp_strlen30924, sizeof(char));
                  strncpy(tmp_str30924, src + 2, tmp_strlen30924 - 1);
                  tmp_str30924[tmp_strlen30924 - 1] = 0;
                  return (Next_results){tmp_str30924, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen30848 = (strlen(src)) - (2) + 1;
                    char* tmp_str30848 = calloc(tmp_strlen30848, sizeof(char));
                    strncpy(tmp_str30848, src + 2, tmp_strlen30848 - 1);
                    tmp_str30848[tmp_strlen30848 - 1] = 0;
                    return (Next_results){tmp_str30848, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen30769 = (strlen(src)) - (2) + 1;
                      char* tmp_str30769 = calloc(tmp_strlen30769, sizeof(char));
                      strncpy(tmp_str30769, src + 2, tmp_strlen30769 - 1);
                      tmp_str30769[tmp_strlen30769 - 1] = 0;
                      return (Next_results){tmp_str30769, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen30690 = (strlen(src)) - (3) + 1;
                        char* tmp_str30690 = calloc(tmp_strlen30690, sizeof(char));
                        strncpy(tmp_str30690, src + 3, tmp_strlen30690 - 1);
                        tmp_str30690[tmp_strlen30690 - 1] = 0;
                        return (Next_results){tmp_str30690, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen30610 = (strlen(src)) - (1) + 1;
                          char* tmp_str30610 = calloc(tmp_strlen30610, sizeof(char));
                          strncpy(tmp_str30610, src + 1, tmp_strlen30610 - 1);
                          tmp_str30610[tmp_strlen30610 - 1] = 0;
                          return (Next_results){tmp_str30610, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen30531 = (strlen(src)) - (1) + 1;
                            char* tmp_str30531 = calloc(tmp_strlen30531, sizeof(char));
                            strncpy(tmp_str30531, src + 1, tmp_strlen30531 - 1);
                            tmp_str30531[tmp_strlen30531 - 1] = 0;
                            return (Next_results){tmp_str30531, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen30454 = (strlen(src)) - (1) + 1;
                              char* tmp_str30454 = calloc(tmp_strlen30454, sizeof(char));
                              strncpy(tmp_str30454, src + 1, tmp_strlen30454 - 1);
                              tmp_str30454[tmp_strlen30454 - 1] = 0;
                              return (Next_results){tmp_str30454, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen30377 = (strlen(src)) - (1) + 1;
                                char* tmp_str30377 = calloc(tmp_strlen30377, sizeof(char));
                                strncpy(tmp_str30377, src + 1, tmp_strlen30377 - 1);
                                tmp_str30377[tmp_strlen30377 - 1] = 0;
                                return (Next_results){tmp_str30377, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen30298 = (strlen(src)) - (1) + 1;
                                  char* tmp_str30298 = calloc(tmp_strlen30298, sizeof(char));
                                  strncpy(tmp_str30298, src + 1, tmp_strlen30298 - 1);
                                  tmp_str30298[tmp_strlen30298 - 1] = 0;
                                  return (Next_results){tmp_str30298, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen30219 = (strlen(src)) - (1) + 1;
                                    char* tmp_str30219 = calloc(tmp_strlen30219, sizeof(char));
                                    strncpy(tmp_str30219, src + 1, tmp_strlen30219 - 1);
                                    tmp_str30219[tmp_strlen30219 - 1] = 0;
                                    return (Next_results){tmp_str30219, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen30142 = (strlen(src)) - (1) + 1;
                                      char* tmp_str30142 = calloc(tmp_strlen30142, sizeof(char));
                                      strncpy(tmp_str30142, src + 1, tmp_strlen30142 - 1);
                                      tmp_str30142[tmp_strlen30142 - 1] = 0;
                                      return (Next_results){tmp_str30142, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, "_")) {
                                        int tmp_strlen30065 = (strlen(src)) - (1) + 1;
                                        char* tmp_str30065 = calloc(tmp_strlen30065, sizeof(char));
                                        strncpy(tmp_str30065, src + 1, tmp_strlen30065 - 1);
                                        tmp_str30065[tmp_strlen30065 - 1] = 0;
                                        return (Next_results){tmp_str30065, TOK_UNDERSCORE, "_"};
                                      } else {
                                        if (StartsWith(src, ":")) {
                                          int tmp_strlen29984 = (strlen(src)) - (1) + 1;
                                          char* tmp_str29984 = calloc(tmp_strlen29984, sizeof(char));
                                          strncpy(tmp_str29984, src + 1, tmp_strlen29984 - 1);
                                          tmp_str29984[tmp_strlen29984 - 1] = 0;
                                          return (Next_results){tmp_str29984, TOK_COLON, ":"};
                                        } else {
                                          if (StartsWith(src, ",")) {
                                            int tmp_strlen29908 = (strlen(src)) - (1) + 1;
                                            char* tmp_str29908 = calloc(tmp_strlen29908, sizeof(char));
                                            strncpy(tmp_str29908, src + 1, tmp_strlen29908 - 1);
                                            tmp_str29908[tmp_strlen29908 - 1] = 0;
                                            return (Next_results){tmp_str29908, TOK_COMMA, ","};
                                          } else {
                                            if (StartsWith(src, "=")) {
                                              int tmp_strlen29832 = (strlen(src)) - (1) + 1;
                                              char* tmp_str29832 = calloc(tmp_strlen29832, sizeof(char));
                                              strncpy(tmp_str29832, src + 1, tmp_strlen29832 - 1);
                                              tmp_str29832[tmp_strlen29832 - 1] = 0;
                                              return (Next_results){tmp_str29832, TOK_ASSIGN, "="};
                                            } else {
                                              if (StartsWith(src, "!")) {
                                                int tmp_strlen29755 = (strlen(src)) - (1) + 1;
                                                char* tmp_str29755 = calloc(tmp_strlen29755, sizeof(char));
                                                strncpy(tmp_str29755, src + 1, tmp_strlen29755 - 1);
                                                tmp_str29755[tmp_strlen29755 - 1] = 0;
                                                return (Next_results){tmp_str29755, TOK_BNOT, "!"};
                                              } else {
                                                if (StartsWith(src, "+")) {
                                                  int tmp_strlen29680 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str29680 = calloc(tmp_strlen29680, sizeof(char));
                                                  strncpy(tmp_str29680, src + 1, tmp_strlen29680 - 1);
                                                  tmp_str29680[tmp_strlen29680 - 1] = 0;
                                                  return (Next_results){tmp_str29680, TOK_ADD, "+"};
                                                } else {
                                                  if (StartsWith(src, "-")) {
                                                    int tmp_strlen29606 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str29606 = calloc(tmp_strlen29606, sizeof(char));
                                                    strncpy(tmp_str29606, src + 1, tmp_strlen29606 - 1);
                                                    tmp_str29606[tmp_strlen29606 - 1] = 0;
                                                    return (Next_results){tmp_str29606, TOK_SUB, "-"};
                                                  } else {
                                                    if (StartsWith(src, "*")) {
                                                      int tmp_strlen29532 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str29532 = calloc(tmp_strlen29532, sizeof(char));
                                                      strncpy(tmp_str29532, src + 1, tmp_strlen29532 - 1);
                                                      tmp_str29532[tmp_strlen29532 - 1] = 0;
                                                      return (Next_results){tmp_str29532, TOK_MUL, "*"};
                                                    } else {
                                                      if (StartsWith(src, "/")) {
                                                        int tmp_strlen29458 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str29458 = calloc(tmp_strlen29458, sizeof(char));
                                                        strncpy(tmp_str29458, src + 1, tmp_strlen29458 - 1);
                                                        tmp_str29458[tmp_strlen29458 - 1] = 0;
                                                        return (Next_results){tmp_str29458, TOK_DIV, "/"};
                                                      } else {
                                                        if (StartsWith(src, "%")) {
                                                          int tmp_strlen29384 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str29384 = calloc(tmp_strlen29384, sizeof(char));
                                                          strncpy(tmp_str29384, src + 1, tmp_strlen29384 - 1);
                                                          tmp_str29384[tmp_strlen29384 - 1] = 0;
                                                          return (Next_results){tmp_str29384, TOK_REM, "%"};
                                                        } else {
                                                          if (StartsWith(src, "~")) {
                                                            int tmp_strlen29310 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str29310 = calloc(tmp_strlen29310, sizeof(char));
                                                            strncpy(tmp_str29310, src + 1, tmp_strlen29310 - 1);
                                                            tmp_str29310[tmp_strlen29310 - 1] = 0;
                                                            return (Next_results){tmp_str29310, TOK_INOT, "~"};
                                                          } else {
                                                            if (StartsWith(src, "|")) {
                                                              int tmp_strlen29235 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str29235 = calloc(tmp_strlen29235, sizeof(char));
                                                              strncpy(tmp_str29235, src + 1, tmp_strlen29235 - 1);
                                                              tmp_str29235[tmp_strlen29235 - 1] = 0;
                                                              return (Next_results){tmp_str29235, TOK_IOR, "|"};
                                                            } else {
                                                              if (StartsWith(src, "&")) {
                                                                int tmp_strlen29161 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str29161 = calloc(tmp_strlen29161, sizeof(char));
                                                                strncpy(tmp_str29161, src + 1, tmp_strlen29161 - 1);
                                                                tmp_str29161[tmp_strlen29161 - 1] = 0;
                                                                return (Next_results){tmp_str29161, TOK_IAND, "&"};
                                                              } else {
                                                                if (StartsWith(src, "^")) {
                                                                  int tmp_strlen29086 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str29086 = calloc(tmp_strlen29086, sizeof(char));
                                                                  strncpy(tmp_str29086, src + 1, tmp_strlen29086 - 1);
                                                                  tmp_str29086[tmp_strlen29086 - 1] = 0;
                                                                  return (Next_results){tmp_str29086, TOK_IXOR, "^"};
                                                                } else {
                                                                  if (StartsWith(src, "<")) {
                                                                    int tmp_strlen29011 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str29011 = calloc(tmp_strlen29011, sizeof(char));
                                                                    strncpy(tmp_str29011, src + 1, tmp_strlen29011 - 1);
                                                                    tmp_str29011[tmp_strlen29011 - 1] = 0;
                                                                    return (Next_results){tmp_str29011, TOK_LESS, "<"};
                                                                  } else {
                                                                    if (StartsWith(src, ">")) {
                                                                      int tmp_strlen28936 = (strlen(src)) - (1) + 1;
                                                                      char* tmp_str28936 = calloc(tmp_strlen28936, sizeof(char));
                                                                      strncpy(tmp_str28936, src + 1, tmp_strlen28936 - 1);
                                                                      tmp_str28936[tmp_strlen28936 - 1] = 0;
                                                                      return (Next_results){tmp_str28936, TOK_GREATER, ">"};
                                                                    } else {
                                                                      if (IsAlpha(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        i = (i) - (1);
                                                                        int tmp_strlen28705 = (i) - (0) + 1;
                                                                        char* tmp_str28705 = calloc(tmp_strlen28705, sizeof(char));
                                                                        strncpy(tmp_str28705, src + 0, tmp_strlen28705 - 1);
                                                                        tmp_str28705[tmp_strlen28705 - 1] = 0;
                                                                        char* ts = tmp_str28705;
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
                                                                        int tmp_strlen27913 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str27913 = calloc(tmp_strlen27913, sizeof(char));
                                                                        strncpy(tmp_str27913, src + i, tmp_strlen27913 - 1);
                                                                        tmp_str27913[tmp_strlen27913 - 1] = 0;
                                                                        return (Next_results){tmp_str27913, tt, ts};
                                                                      } else {
                                                                        if (IsNumeric(src[0])) {
                                                                          int i = 1;
                                                                          while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                            i = (i) + (1);
                                                                          }
                                                                          int tmp_strlen27745 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str27745 = calloc(tmp_strlen27745, sizeof(char));
                                                                          strncpy(tmp_str27745, src + i, tmp_strlen27745 - 1);
                                                                          tmp_str27745[tmp_strlen27745 - 1] = 0;
                                                                          int tmp_strlen27724 = (i) - (0) + 1;
                                                                          char* tmp_str27724 = calloc(tmp_strlen27724, sizeof(char));
                                                                          strncpy(tmp_str27724, src + 0, tmp_strlen27724 - 1);
                                                                          tmp_str27724[tmp_strlen27724 - 1] = 0;
                                                                          return (Next_results){tmp_str27745, TOK_INTLIT, tmp_str27724};
                                                                        } else {
                                                                          if (StartsWith(src, "\"")) {
                                                                            int i = 1;
                                                                            while (true) {
                                                                              int tmp_strlen27643 = ((i) + (1)) - (i) + 1;
                                                                              char* tmp_str27643 = calloc(tmp_strlen27643, sizeof(char));
                                                                              strncpy(tmp_str27643, src + i, tmp_strlen27643 - 1);
                                                                              tmp_str27643[tmp_strlen27643 - 1] = 0;
                                                                              if (!((strcmp(tmp_str27643, "\"") != 0))) break;
                                                                              i = (i) + (1);
                                                                              int tmp_strlen27584 = (i) - ((i) - (1)) + 1;
                                                                              char* tmp_str27584 = calloc(tmp_strlen27584, sizeof(char));
                                                                              strncpy(tmp_str27584, src + (i) - (1), tmp_strlen27584 - 1);
                                                                              tmp_str27584[tmp_strlen27584 - 1] = 0;
                                                                              if ((strcmp(tmp_str27584, "\\") == 0)) {
                                                                                i = (i) + (1);
                                                                              }
                                                                            }
                                                                            i = (i) + (1);
                                                                            int tmp_strlen27480 = (strlen(src)) - (i) + 1;
                                                                            char* tmp_str27480 = calloc(tmp_strlen27480, sizeof(char));
                                                                            strncpy(tmp_str27480, src + i, tmp_strlen27480 - 1);
                                                                            tmp_str27480[tmp_strlen27480 - 1] = 0;
                                                                            int tmp_strlen27459 = (i) - (0) + 1;
                                                                            char* tmp_str27459 = calloc(tmp_strlen27459, sizeof(char));
                                                                            strncpy(tmp_str27459, src + 0, tmp_strlen27459 - 1);
                                                                            tmp_str27459[tmp_strlen27459 - 1] = 0;
                                                                            return (Next_results){tmp_str27480, TOK_STRLIT, tmp_str27459};
                                                                          } else {
                                                                            int tmp_strlen27394 = (1) - (0) + 1;
                                                                            char* tmp_str27394 = calloc(tmp_strlen27394, sizeof(char));
                                                                            strncpy(tmp_str27394, src + 0, tmp_strlen27394 - 1);
                                                                            tmp_str27394[tmp_strlen27394 - 1] = 0;
                                                                            int tmp_strlen27390 = strlen("unexpected token start: ") + strlen(tmp_str27394) + 1;
                                                                            char* tmp_str27390 = calloc(tmp_strlen27390, sizeof(char));
                                                                            strcpy(tmp_str27390, "unexpected token start: ");
                                                                            strcat(tmp_str27390, tmp_str27394);
                                                                            printf("%s", tmp_str27390);
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
  Next_results tmp_results27278 = Next(src);
  tok = tmp_results27278.result2;
  tok_str = tmp_results27278.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results27094 = Next(src);
  src = tmp_results27094.result1;
  actual_tok = tmp_results27094.result2;
  actual_tok_str = tmp_results27094.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen26960 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str26960 = calloc(tmp_strlen26960, sizeof(char));
    strcpy(tmp_str26960, "expected token: ");
    strcat(tmp_str26960, itoa(expected_tok));
    int tmp_strlen26933 = strlen(tmp_str26960) + strlen(" got: ") + 1;
    char* tmp_str26933 = calloc(tmp_strlen26933, sizeof(char));
    strcpy(tmp_str26933, tmp_str26960);
    strcat(tmp_str26933, " got: ");
    int tmp_strlen26913 = strlen(tmp_str26933) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str26913 = calloc(tmp_strlen26913, sizeof(char));
    strcpy(tmp_str26913, tmp_str26933);
    strcat(tmp_str26913, itoa(actual_tok));
    int tmp_strlen26904 = strlen(tmp_str26913) + strlen(" \"") + 1;
    char* tmp_str26904 = calloc(tmp_strlen26904, sizeof(char));
    strcpy(tmp_str26904, tmp_str26913);
    strcat(tmp_str26904, " \"");
    int tmp_strlen26886 = strlen(tmp_str26904) + strlen(actual_tok_str) + 1;
    char* tmp_str26886 = calloc(tmp_strlen26886, sizeof(char));
    strcpy(tmp_str26886, tmp_str26904);
    strcat(tmp_str26886, actual_tok_str);
    int tmp_strlen26878 = strlen(tmp_str26886) + strlen("\"") + 1;
    char* tmp_str26878 = calloc(tmp_strlen26878, sizeof(char));
    strcpy(tmp_str26878, tmp_str26886);
    strcat(tmp_str26878, "\"");
    printf("%s", tmp_str26878);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results26710 = Next(src);
  src = tmp_results26710.result1;
  actual_tok = tmp_results26710.result2;
  actual_tok_str = tmp_results26710.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen26576 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str26576 = calloc(tmp_strlen26576, sizeof(char));
    strcpy(tmp_str26576, "expected ident, got: ");
    strcat(tmp_str26576, itoa(actual_tok));
    int tmp_strlen26567 = strlen(tmp_str26576) + strlen(" \"") + 1;
    char* tmp_str26567 = calloc(tmp_strlen26567, sizeof(char));
    strcpy(tmp_str26567, tmp_str26576);
    strcat(tmp_str26567, " \"");
    int tmp_strlen26549 = strlen(tmp_str26567) + strlen(actual_tok_str) + 1;
    char* tmp_str26549 = calloc(tmp_strlen26549, sizeof(char));
    strcpy(tmp_str26549, tmp_str26567);
    strcat(tmp_str26549, actual_tok_str);
    int tmp_strlen26541 = strlen(tmp_str26549) + strlen("\"") + 1;
    char* tmp_str26541 = calloc(tmp_strlen26541, sizeof(char));
    strcpy(tmp_str26541, tmp_str26549);
    strcat(tmp_str26541, "\"");
    printf("%s", tmp_str26541);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results26361 = Next(src);
  src = tmp_results26361.result1;
  actual_tok = tmp_results26361.result2;
  actual_tok_str = tmp_results26361.result3;
  if (((actual_tok) != (TOK_UNDERSCORE)) && ((actual_tok) != (TOK_IDENT))) {
    int tmp_strlen26181 = strlen("expected ident or underscore, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str26181 = calloc(tmp_strlen26181, sizeof(char));
    strcpy(tmp_str26181, "expected ident or underscore, got: ");
    strcat(tmp_str26181, itoa(actual_tok));
    int tmp_strlen26172 = strlen(tmp_str26181) + strlen(" \"") + 1;
    char* tmp_str26172 = calloc(tmp_strlen26172, sizeof(char));
    strcpy(tmp_str26172, tmp_str26181);
    strcat(tmp_str26172, " \"");
    int tmp_strlen26154 = strlen(tmp_str26172) + strlen(actual_tok_str) + 1;
    char* tmp_str26154 = calloc(tmp_strlen26154, sizeof(char));
    strcpy(tmp_str26154, tmp_str26172);
    strcat(tmp_str26154, actual_tok_str);
    int tmp_strlen26146 = strlen(tmp_str26154) + strlen("\"") + 1;
    char* tmp_str26146 = calloc(tmp_strlen26146, sizeof(char));
    strcpy(tmp_str26146, tmp_str26154);
    strcat(tmp_str26146, "\"");
    printf("%s", tmp_str26146);
    exit(1);
  }
  return (ConsumeIdentOrUnderscore_results){src, actual_tok_str};
}

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
                  int tmp_strlen23209 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str23209 = calloc(tmp_strlen23209, sizeof(char));
                  strcpy(tmp_str23209, "token has no defined precedence: ");
                  strcat(tmp_str23209, itoa(tok));
                  printf("%s", tmp_str23209);
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

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results23000 = Next(src);
  src = tmp_results23000.result1;
  tok = tmp_results23000.result2;
  tok_str = tmp_results23000.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen22703 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str22703 = calloc(tmp_strlen22703, sizeof(char));
        strcpy(tmp_str22703, "expected type, got: ");
        strcat(tmp_str22703, itoa(tok));
        int tmp_strlen22694 = strlen(tmp_str22703) + strlen(" \"") + 1;
        char* tmp_str22694 = calloc(tmp_strlen22694, sizeof(char));
        strcpy(tmp_str22694, tmp_str22703);
        strcat(tmp_str22694, " \"");
        int tmp_strlen22683 = strlen(tmp_str22694) + strlen(tok_str) + 1;
        char* tmp_str22683 = calloc(tmp_strlen22683, sizeof(char));
        strcpy(tmp_str22683, tmp_str22694);
        strcat(tmp_str22683, tok_str);
        int tmp_strlen22675 = strlen(tmp_str22683) + strlen("\"") + 1;
        char* tmp_str22675 = calloc(tmp_strlen22675, sizeof(char));
        strcpy(tmp_str22675, tmp_str22683);
        strcat(tmp_str22675, "\"");
        printf("%s", tmp_str22675);
        exit(1);
      }
    }
  }
}

char* ReadSrc(char* src_dir) {
  char* src = "";
  char* src_files = direntries(src_dir);
  char* src_file;
  Split_results tmp_results22506 = Split(src_files);
  src_file = tmp_results22506.result1;
  src_files = tmp_results22506.result2;
  while (((strlen(src_files)) > (0)) || ((strlen(src_file)) > (0))) {
    if (EndsWith(src_file, ".sk")) {
      int tmp_strlen22334 = strlen(src_dir) + strlen("/") + 1;
      char* tmp_str22334 = calloc(tmp_strlen22334, sizeof(char));
      strcpy(tmp_str22334, src_dir);
      strcat(tmp_str22334, "/");
      int tmp_strlen22322 = strlen(tmp_str22334) + strlen(src_file) + 1;
      char* tmp_str22322 = calloc(tmp_strlen22322, sizeof(char));
      strcpy(tmp_str22322, tmp_str22334);
      strcat(tmp_str22322, src_file);
      int tmp_strlen22321 = strlen(src) + strlen(read(tmp_str22322)) + 1;
      char* tmp_str22321 = calloc(tmp_strlen22321, sizeof(char));
      strcpy(tmp_str22321, src);
      strcat(tmp_str22321, read(tmp_str22322));
      int tmp_strlen22313 = strlen(tmp_str22321) + strlen("\n") + 1;
      char* tmp_str22313 = calloc(tmp_strlen22313, sizeof(char));
      strcpy(tmp_str22313, tmp_str22321);
      strcat(tmp_str22313, "\n");
      src = tmp_str22313;
    }
    Split_results tmp_results22294 = Split(src_files);
    src_file = tmp_results22294.result1;
    src_files = tmp_results22294.result2;
  }
  return src;
}

char* TranslateProgram(char* src) {
  char* out = read("clib/lib.c");
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results22016 = Peek(src);
  tok = tmp_results22016.result1;
  tok_str = tmp_results22016.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results21922 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results21922.result1;
      Peek_results tmp_results21870 = Peek(src);
      tok = tmp_results21870.result1;
      tok_str = tmp_results21870.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results21742 = TranslateConstDecl(src, "");
        src = tmp_results21742.result1;
        const_decl = tmp_results21742.result2;
        int tmp_strlen21649 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str21649 = calloc(tmp_strlen21649, sizeof(char));
        strcpy(tmp_str21649, constants);
        strcat(tmp_str21649, const_decl);
        constants = tmp_str21649;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          TranslateFunc_results tmp_results21539 = TranslateFunc(src);
          src = tmp_results21539.result1;
          fn_decl = tmp_results21539.result2;
          fn_def = tmp_results21539.result3;
          int tmp_strlen21461 = strlen(decls) + strlen(fn_decl) + 1;
          char* tmp_str21461 = calloc(tmp_strlen21461, sizeof(char));
          strcpy(tmp_str21461, decls);
          strcat(tmp_str21461, fn_decl);
          decls = tmp_str21461;
          int tmp_strlen21427 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str21427 = calloc(tmp_strlen21427, sizeof(char));
          strcpy(tmp_str21427, defs);
          strcat(tmp_str21427, fn_def);
          defs = tmp_str21427;
        } else {
          int tmp_strlen21348 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str21348 = calloc(tmp_strlen21348, sizeof(char));
          strcpy(tmp_str21348, "unexpected decl token, got: ");
          strcat(tmp_str21348, itoa(tok));
          int tmp_strlen21339 = strlen(tmp_str21348) + strlen(" \"") + 1;
          char* tmp_str21339 = calloc(tmp_strlen21339, sizeof(char));
          strcpy(tmp_str21339, tmp_str21348);
          strcat(tmp_str21339, " \"");
          int tmp_strlen21328 = strlen(tmp_str21339) + strlen(tok_str) + 1;
          char* tmp_str21328 = calloc(tmp_strlen21328, sizeof(char));
          strcpy(tmp_str21328, tmp_str21339);
          strcat(tmp_str21328, tok_str);
          int tmp_strlen21320 = strlen(tmp_str21328) + strlen("\"") + 1;
          char* tmp_str21320 = calloc(tmp_strlen21320, sizeof(char));
          strcpy(tmp_str21320, tmp_str21328);
          strcat(tmp_str21320, "\"");
          printf("%s", tmp_str21320);
          exit(1);
        }
      }
    }
    Peek_results tmp_results21280 = Peek(src);
    tok = tmp_results21280.result1;
    tok_str = tmp_results21280.result2;
  }
  ConsumeToken_results tmp_results21245 = ConsumeToken(src, TOK_EOF);
  src = tmp_results21245.result1;
  if ((strcmp(constants, "") != 0)) {
    int tmp_strlen21153 = strlen(out) + strlen(constants) + 1;
    char* tmp_str21153 = calloc(tmp_strlen21153, sizeof(char));
    strcpy(tmp_str21153, out);
    strcat(tmp_str21153, constants);
    int tmp_strlen21145 = strlen(tmp_str21153) + strlen("\n") + 1;
    char* tmp_str21145 = calloc(tmp_strlen21145, sizeof(char));
    strcpy(tmp_str21145, tmp_str21153);
    strcat(tmp_str21145, "\n");
    out = tmp_str21145;
  }
  if ((strcmp(decls, "") != 0)) {
    int tmp_strlen21090 = strlen(out) + strlen(decls) + 1;
    char* tmp_str21090 = calloc(tmp_strlen21090, sizeof(char));
    strcpy(tmp_str21090, out);
    strcat(tmp_str21090, decls);
    int tmp_strlen21082 = strlen(tmp_str21090) + strlen("\n") + 1;
    char* tmp_str21082 = calloc(tmp_strlen21082, sizeof(char));
    strcpy(tmp_str21082, tmp_str21090);
    strcat(tmp_str21082, "\n");
    out = tmp_str21082;
  }
  if ((strcmp(defs, "") != 0)) {
    int tmp_strlen21029 = strlen(out) + strlen(defs) + 1;
    char* tmp_str21029 = calloc(tmp_strlen21029, sizeof(char));
    strcpy(tmp_str21029, out);
    strcat(tmp_str21029, defs);
    int tmp_strlen21021 = strlen(tmp_str21029) + strlen("\n") + 1;
    char* tmp_str21021 = calloc(tmp_strlen21021, sizeof(char));
    strcpy(tmp_str21021, tmp_str21029);
    strcat(tmp_str21021, "\n");
    out = tmp_str21021;
  }
  return out;
}

int _main(char* args) {
  int i = Find(args, " ");
  int tmp_strlen20909 = (i) - (0) + 1;
  char* tmp_str20909 = calloc(tmp_strlen20909, sizeof(char));
  strncpy(tmp_str20909, args + 0, tmp_strlen20909 - 1);
  tmp_str20909[tmp_strlen20909 - 1] = 0;
  char* src_dir = tmp_str20909;
  char* src = ReadSrc(src_dir);
  char* out = TranslateProgram(src);
  int tmp_strlen20790 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str20790 = calloc(tmp_strlen20790, sizeof(char));
  strncpy(tmp_str20790, args + (i) + (1), tmp_strlen20790 - 1);
  tmp_str20790[tmp_strlen20790 - 1] = 0;
  char* out_file = tmp_str20790;
  write(out_file, out);
  return 0;
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  ConsumeToken_results tmp_results20678 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results20678.result1;
  Peek_results tmp_results20635 = Peek(src);
  tok = tmp_results20635.result1;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results20581 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results20581.result1;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results20486 = TranslateConstOrVar(src);
  src = tmp_results20486.result1;
  args = tmp_results20486.result2;
  Peek_results tmp_results20445 = Peek(src);
  tok = tmp_results20445.result1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results20391 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results20391.result1;
    char* arg;
    TranslateConstOrVar_results tmp_results20321 = TranslateConstOrVar(src);
    src = tmp_results20321.result1;
    arg = tmp_results20321.result2;
    int tmp_strlen20258 = strlen(args) + strlen(", ") + 1;
    char* tmp_str20258 = calloc(tmp_strlen20258, sizeof(char));
    strcpy(tmp_str20258, args);
    strcat(tmp_str20258, ", ");
    int tmp_strlen20251 = strlen(tmp_str20258) + strlen(arg) + 1;
    char* tmp_str20251 = calloc(tmp_strlen20251, sizeof(char));
    strcpy(tmp_str20251, tmp_str20258);
    strcat(tmp_str20251, arg);
    args = tmp_str20251;
    Peek_results tmp_results20242 = Peek(src);
    tok = tmp_results20242.result1;
  }
  ConsumeToken_results tmp_results20213 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results20213.result1;
  int tmp_strlen20147 = strlen("(") + strlen(args) + 1;
  char* tmp_str20147 = calloc(tmp_strlen20147, sizeof(char));
  strcpy(tmp_str20147, "(");
  strcat(tmp_str20147, args);
  int tmp_strlen20140 = strlen(tmp_str20147) + strlen(")") + 1;
  char* tmp_str20140 = calloc(tmp_strlen20140, sizeof(char));
  strcpy(tmp_str20140, tmp_str20147);
  strcat(tmp_str20140, ")");
  return (TranslateFuncArgs_results){src, tmp_str20140};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  Peek_results tmp_results19988 = Peek(src);
  tok = tmp_results19988.result1;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results19934 = TranslateType(src);
    src = tmp_results19934.result1;
    typ = tmp_results19934.result2;
    typ_str = tmp_results19934.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results19853 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results19853.result1;
  TranslateType_results tmp_results19810 = TranslateType(src);
  src = tmp_results19810.result1;
  typ = tmp_results19810.result2;
  typ_str = tmp_results19810.result3;
  Peek_results tmp_results19767 = Peek(src);
  tok = tmp_results19767.result1;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results19714 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results19714.result1;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen19579 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str19579 = calloc(tmp_strlen19579, sizeof(char));
  strcpy(tmp_str19579, "typedef struct {\n");
  strcat(tmp_str19579, SINGLE_INDENT);
  int tmp_strlen19568 = strlen(tmp_str19579) + strlen(typ_str) + 1;
  char* tmp_str19568 = calloc(tmp_strlen19568, sizeof(char));
  strcpy(tmp_str19568, tmp_str19579);
  strcat(tmp_str19568, typ_str);
  int tmp_strlen19551 = strlen(tmp_str19568) + strlen(" result1;\n") + 1;
  char* tmp_str19551 = calloc(tmp_strlen19551, sizeof(char));
  strcpy(tmp_str19551, tmp_str19568);
  strcat(tmp_str19551, " result1;\n");
  char* td = tmp_str19551;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results19488 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results19488.result1;
    TranslateType_results tmp_results19442 = TranslateType(src);
    src = tmp_results19442.result1;
    typ = tmp_results19442.result2;
    typ_str = tmp_results19442.result3;
    res_count = (res_count) + (1);
    int tmp_strlen19337 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str19337 = calloc(tmp_strlen19337, sizeof(char));
    strcpy(tmp_str19337, td);
    strcat(tmp_str19337, SINGLE_INDENT);
    int tmp_strlen19326 = strlen(tmp_str19337) + strlen(typ_str) + 1;
    char* tmp_str19326 = calloc(tmp_strlen19326, sizeof(char));
    strcpy(tmp_str19326, tmp_str19337);
    strcat(tmp_str19326, typ_str);
    int tmp_strlen19313 = strlen(tmp_str19326) + strlen(" result") + 1;
    char* tmp_str19313 = calloc(tmp_strlen19313, sizeof(char));
    strcpy(tmp_str19313, tmp_str19326);
    strcat(tmp_str19313, " result");
    int tmp_strlen19294 = strlen(tmp_str19313) + strlen(itoa(res_count)) + 1;
    char* tmp_str19294 = calloc(tmp_strlen19294, sizeof(char));
    strcpy(tmp_str19294, tmp_str19313);
    strcat(tmp_str19294, itoa(res_count));
    int tmp_strlen19285 = strlen(tmp_str19294) + strlen(";\n") + 1;
    char* tmp_str19285 = calloc(tmp_strlen19285, sizeof(char));
    strcpy(tmp_str19285, tmp_str19294);
    strcat(tmp_str19285, ";\n");
    td = tmp_str19285;
    Peek_results tmp_results19276 = Peek(src);
    tok = tmp_results19276.result1;
  }
  ConsumeToken_results tmp_results19247 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results19247.result1;
  int tmp_strlen19189 = strlen(td) + strlen("} ") + 1;
  char* tmp_str19189 = calloc(tmp_strlen19189, sizeof(char));
  strcpy(tmp_str19189, td);
  strcat(tmp_str19189, "} ");
  int tmp_strlen19176 = strlen(tmp_str19189) + strlen(func_name) + 1;
  char* tmp_str19176 = calloc(tmp_strlen19176, sizeof(char));
  strcpy(tmp_str19176, tmp_str19189);
  strcat(tmp_str19176, func_name);
  int tmp_strlen19159 = strlen(tmp_str19176) + strlen("_results;\n") + 1;
  char* tmp_str19159 = calloc(tmp_strlen19159, sizeof(char));
  strcpy(tmp_str19159, tmp_str19176);
  strcat(tmp_str19159, "_results;\n");
  td = tmp_str19159;
  int tmp_strlen19115 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str19115 = calloc(tmp_strlen19115, sizeof(char));
  strcpy(tmp_str19115, func_name);
  strcat(tmp_str19115, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str19115};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* name;
  ConsumeToken_results tmp_results19009 = ConsumeToken(src, TOK_FN);
  src = tmp_results19009.result1;
  ConsumeIdent_results tmp_results18970 = ConsumeIdent(src);
  src = tmp_results18970.result1;
  name = tmp_results18970.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  }
  Peek_results tmp_results18710 = Peek(src);
  tok = tmp_results18710.result1;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results18656 = TranslateFuncArgs(src);
    src = tmp_results18656.result1;
    args = tmp_results18656.result2;
    Peek_results tmp_results18613 = Peek(src);
    tok = tmp_results18613.result1;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results18551 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results18551.result1;
      TranslateFuncResults_results tmp_results18500 = TranslateFuncResults(src, name);
      src = tmp_results18500.result1;
      results_type_def = tmp_results18500.result2;
      results_type_name = tmp_results18500.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results18379 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results18379.result1;
  int tmp_strlen18280 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str18280 = calloc(tmp_strlen18280, sizeof(char));
  strcpy(tmp_str18280, SINGLE_INDENT);
  strcat(tmp_str18280, "");
  TranslateStmts_results tmp_results18336 = TranslateStmts(src, tmp_str18280, name);
  src = tmp_results18336.result1;
  stmts_out = tmp_results18336.result2;
  ConsumeToken_results tmp_results18268 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results18268.result1;
  int tmp_strlen18184 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str18184 = calloc(tmp_strlen18184, sizeof(char));
  strcpy(tmp_str18184, results_type_name);
  strcat(tmp_str18184, " ");
  int tmp_strlen18176 = strlen(tmp_str18184) + strlen(name) + 1;
  char* tmp_str18176 = calloc(tmp_strlen18176, sizeof(char));
  strcpy(tmp_str18176, tmp_str18184);
  strcat(tmp_str18176, name);
  int tmp_strlen18168 = strlen(tmp_str18176) + strlen(args) + 1;
  char* tmp_str18168 = calloc(tmp_strlen18168, sizeof(char));
  strcpy(tmp_str18168, tmp_str18176);
  strcat(tmp_str18168, args);
  char* df = tmp_str18168;
  int tmp_strlen18122 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str18122 = calloc(tmp_strlen18122, sizeof(char));
  strcpy(tmp_str18122, results_type_def);
  strcat(tmp_str18122, df);
  int tmp_strlen18113 = strlen(tmp_str18122) + strlen(";\n") + 1;
  char* tmp_str18113 = calloc(tmp_strlen18113, sizeof(char));
  strcpy(tmp_str18113, tmp_str18122);
  strcat(tmp_str18113, ";\n");
  char* decl = tmp_str18113;
  int tmp_strlen18091 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str18091 = calloc(tmp_strlen18091, sizeof(char));
  strcpy(tmp_str18091, df);
  strcat(tmp_str18091, " {\n");
  df = tmp_str18091;
  int tmp_strlen18066 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str18066 = calloc(tmp_strlen18066, sizeof(char));
  strcpy(tmp_str18066, df);
  strcat(tmp_str18066, stmts_out);
  df = tmp_str18066;
  if ((strcmp(name, "_main") == 0)) {
    int tmp_strlen18006 = strlen(df) + strlen("  return 0;\n") + 1;
    char* tmp_str18006 = calloc(tmp_strlen18006, sizeof(char));
    strcpy(tmp_str18006, df);
    strcat(tmp_str18006, "  return 0;\n");
    df = tmp_str18006;
  }
  int tmp_strlen17977 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str17977 = calloc(tmp_strlen17977, sizeof(char));
  strcpy(tmp_str17977, df);
  strcat(tmp_str17977, "}\n\n");
  df = tmp_str17977;
  return (TranslateFunc_results){src, decl, df};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results17865 = ConsumeIdent(src);
  src = tmp_results17865.result1;
  name = tmp_results17865.result2;
  ConsumeToken_results tmp_results17831 = ConsumeToken(src, TOK_COLON);
  src = tmp_results17831.result1;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results17748 = TranslateType(src);
  src = tmp_results17748.result1;
  typ = tmp_results17748.result2;
  typ_str = tmp_results17748.result3;
  int tmp_strlen17673 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str17673 = calloc(tmp_strlen17673, sizeof(char));
  strcpy(tmp_str17673, typ_str);
  strcat(tmp_str17673, " ");
  int tmp_strlen17665 = strlen(tmp_str17673) + strlen(name) + 1;
  char* tmp_str17665 = calloc(tmp_strlen17665, sizeof(char));
  strcpy(tmp_str17665, tmp_str17673);
  strcat(tmp_str17665, name);
  char* out = tmp_str17665;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  ConsumeToken_results tmp_results17564 = ConsumeToken(src, TOK_LET);
  src = tmp_results17564.result1;
  char* out;
  TranslateConstOrVar_results tmp_results17504 = TranslateConstOrVar(src);
  src = tmp_results17504.result1;
  out = tmp_results17504.result2;
  int tmp_strlen17443 = strlen("const ") + strlen(out) + 1;
  char* tmp_str17443 = calloc(tmp_strlen17443, sizeof(char));
  strcpy(tmp_str17443, "const ");
  strcat(tmp_str17443, out);
  out = tmp_str17443;
  ConsumeToken_results tmp_results17438 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results17438.result1;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results17353 = TranslateExpr(src, indent);
  src = tmp_results17353.result1;
  setup = tmp_results17353.result2;
  val = tmp_results17353.result3;
  ConsumeToken_results tmp_results17304 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results17304.result1;
  int tmp_strlen17242 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str17242 = calloc(tmp_strlen17242, sizeof(char));
  strcpy(tmp_str17242, out);
  strcat(tmp_str17242, " = ");
  int tmp_strlen17235 = strlen(tmp_str17242) + strlen(val) + 1;
  char* tmp_str17235 = calloc(tmp_strlen17235, sizeof(char));
  strcpy(tmp_str17235, tmp_str17242);
  strcat(tmp_str17235, val);
  int tmp_strlen17226 = strlen(tmp_str17235) + strlen(";\n") + 1;
  char* tmp_str17226 = calloc(tmp_strlen17226, sizeof(char));
  strcpy(tmp_str17226, tmp_str17235);
  strcat(tmp_str17226, ";\n");
  out = tmp_str17226;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results17101 = TranslateConstDecl(src, indent);
  src = tmp_results17101.result1;
  out = tmp_results17101.result2;
  int tmp_strlen17029 = strlen(indent) + strlen(out) + 1;
  char* tmp_str17029 = calloc(tmp_strlen17029, sizeof(char));
  strcpy(tmp_str17029, indent);
  strcat(tmp_str17029, out);
  return (TranslateConstDeclStmt_results){src, tmp_str17029};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  ConsumeToken_results tmp_results16929 = ConsumeToken(src, TOK_VAR);
  src = tmp_results16929.result1;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results16822 = TranslateConstOrVar(src);
  src = tmp_results16822.result1;
  out = tmp_results16822.result2;
  Peek_results tmp_results16782 = Peek(src);
  tok = tmp_results16782.result1;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results16728 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results16728.result1;
    TranslateExpr_results tmp_results16681 = TranslateExpr(src, indent);
    src = tmp_results16681.result1;
    setup = tmp_results16681.result2;
    val = tmp_results16681.result3;
    ConsumeToken_results tmp_results16628 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results16628.result1;
    int tmp_strlen16562 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str16562 = calloc(tmp_strlen16562, sizeof(char));
    strcpy(tmp_str16562, out);
    strcat(tmp_str16562, " = ");
    int tmp_strlen16555 = strlen(tmp_str16562) + strlen(val) + 1;
    char* tmp_str16555 = calloc(tmp_strlen16555, sizeof(char));
    strcpy(tmp_str16555, tmp_str16562);
    strcat(tmp_str16555, val);
    out = tmp_str16555;
  }
  int tmp_strlen16523 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str16523 = calloc(tmp_strlen16523, sizeof(char));
  strcpy(tmp_str16523, setup);
  strcat(tmp_str16523, indent);
  int tmp_strlen16516 = strlen(tmp_str16523) + strlen(out) + 1;
  char* tmp_str16516 = calloc(tmp_strlen16516, sizeof(char));
  strcpy(tmp_str16516, tmp_str16523);
  strcat(tmp_str16516, out);
  int tmp_strlen16507 = strlen(tmp_str16516) + strlen(";\n") + 1;
  char* tmp_str16507 = calloc(tmp_strlen16507, sizeof(char));
  strcpy(tmp_str16507, tmp_str16516);
  strcat(tmp_str16507, ";\n");
  out = tmp_str16507;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen16352 = (x) - (0) + 1;
  char* tmp_str16352 = calloc(tmp_strlen16352, sizeof(char));
  strncpy(tmp_str16352, src + 0, tmp_strlen16352 - 1);
  tmp_str16352[tmp_strlen16352 - 1] = 0;
  char* lhs = tmp_str16352;
  int tmp_strlen16322 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str16322 = calloc(tmp_strlen16322, sizeof(char));
  strncpy(tmp_str16322, src + (x) + (1), tmp_strlen16322 - 1);
  tmp_str16322[tmp_strlen16322 - 1] = 0;
  char* rhs = tmp_str16322;
  char* lhs_ident;
  ConsumeIdentOrUnderscore_results tmp_results16285 = ConsumeIdentOrUnderscore(lhs);
  lhs = tmp_results16285.result1;
  lhs_ident = tmp_results16285.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results16157 = TranslateExpr(rhs, indent);
  rhs = tmp_results16157.result1;
  setup = tmp_results16157.result2;
  rhs_expr = tmp_results16157.result3;
  int lhs_tok;
  int rhs_tok;
  Peek_results tmp_results16061 = Peek(lhs);
  lhs_tok = tmp_results16061.result1;
  Peek_results tmp_results16034 = Peek(rhs);
  rhs_tok = tmp_results16034.result1;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results15919 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results15919.result1;
    func_name = tmp_results15919.result2;
    int tmp_strlen15811 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str15811 = calloc(tmp_strlen15811, sizeof(char));
    strcpy(tmp_str15811, "tmp_results");
    strcat(tmp_str15811, itoa(strlen(src)));
    char* tmp_results = tmp_str15811;
    char* out = setup;
    int tmp_strlen15751 = strlen(out) + strlen(indent) + 1;
    char* tmp_str15751 = calloc(tmp_strlen15751, sizeof(char));
    strcpy(tmp_str15751, out);
    strcat(tmp_str15751, indent);
    int tmp_strlen15738 = strlen(tmp_str15751) + strlen(func_name) + 1;
    char* tmp_str15738 = calloc(tmp_strlen15738, sizeof(char));
    strcpy(tmp_str15738, tmp_str15751);
    strcat(tmp_str15738, func_name);
    int tmp_strlen15723 = strlen(tmp_str15738) + strlen("_results ") + 1;
    char* tmp_str15723 = calloc(tmp_strlen15723, sizeof(char));
    strcpy(tmp_str15723, tmp_str15738);
    strcat(tmp_str15723, "_results ");
    int tmp_strlen15708 = strlen(tmp_str15723) + strlen(tmp_results) + 1;
    char* tmp_str15708 = calloc(tmp_strlen15708, sizeof(char));
    strcpy(tmp_str15708, tmp_str15723);
    strcat(tmp_str15708, tmp_results);
    int tmp_strlen15699 = strlen(tmp_str15708) + strlen(" = ") + 1;
    char* tmp_str15699 = calloc(tmp_strlen15699, sizeof(char));
    strcpy(tmp_str15699, tmp_str15708);
    strcat(tmp_str15699, " = ");
    int tmp_strlen15687 = strlen(tmp_str15699) + strlen(rhs_expr) + 1;
    char* tmp_str15687 = calloc(tmp_strlen15687, sizeof(char));
    strcpy(tmp_str15687, tmp_str15699);
    strcat(tmp_str15687, rhs_expr);
    int tmp_strlen15678 = strlen(tmp_str15687) + strlen(";\n") + 1;
    char* tmp_str15678 = calloc(tmp_strlen15678, sizeof(char));
    strcpy(tmp_str15678, tmp_str15687);
    strcat(tmp_str15678, ";\n");
    out = tmp_str15678;
    if ((strcmp(lhs_ident, "_") != 0)) {
      int tmp_strlen15615 = strlen(out) + strlen(indent) + 1;
      char* tmp_str15615 = calloc(tmp_strlen15615, sizeof(char));
      strcpy(tmp_str15615, out);
      strcat(tmp_str15615, indent);
      int tmp_strlen15602 = strlen(tmp_str15615) + strlen(lhs_ident) + 1;
      char* tmp_str15602 = calloc(tmp_strlen15602, sizeof(char));
      strcpy(tmp_str15602, tmp_str15615);
      strcat(tmp_str15602, lhs_ident);
      int tmp_strlen15593 = strlen(tmp_str15602) + strlen(" = ") + 1;
      char* tmp_str15593 = calloc(tmp_strlen15593, sizeof(char));
      strcpy(tmp_str15593, tmp_str15602);
      strcat(tmp_str15593, " = ");
      int tmp_strlen15578 = strlen(tmp_str15593) + strlen(tmp_results) + 1;
      char* tmp_str15578 = calloc(tmp_strlen15578, sizeof(char));
      strcpy(tmp_str15578, tmp_str15593);
      strcat(tmp_str15578, tmp_results);
      int tmp_strlen15561 = strlen(tmp_str15578) + strlen(".result1;\n") + 1;
      char* tmp_str15561 = calloc(tmp_strlen15561, sizeof(char));
      strcpy(tmp_str15561, tmp_str15578);
      strcat(tmp_str15561, ".result1;\n");
      out = tmp_str15561;
    }
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results15425 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results15425.result1;
      ConsumeIdentOrUnderscore_results tmp_results15375 = ConsumeIdentOrUnderscore(lhs);
      lhs = tmp_results15375.result1;
      lhs_ident = tmp_results15375.result2;
      if ((strcmp(lhs_ident, "_") != 0)) {
        int tmp_strlen15258 = strlen(out) + strlen(indent) + 1;
        char* tmp_str15258 = calloc(tmp_strlen15258, sizeof(char));
        strcpy(tmp_str15258, out);
        strcat(tmp_str15258, indent);
        int tmp_strlen15245 = strlen(tmp_str15258) + strlen(lhs_ident) + 1;
        char* tmp_str15245 = calloc(tmp_strlen15245, sizeof(char));
        strcpy(tmp_str15245, tmp_str15258);
        strcat(tmp_str15245, lhs_ident);
        int tmp_strlen15236 = strlen(tmp_str15245) + strlen(" = ") + 1;
        char* tmp_str15236 = calloc(tmp_strlen15236, sizeof(char));
        strcpy(tmp_str15236, tmp_str15245);
        strcat(tmp_str15236, " = ");
        int tmp_strlen15221 = strlen(tmp_str15236) + strlen(tmp_results) + 1;
        char* tmp_str15221 = calloc(tmp_strlen15221, sizeof(char));
        strcpy(tmp_str15221, tmp_str15236);
        strcat(tmp_str15221, tmp_results);
        int tmp_strlen15208 = strlen(tmp_str15221) + strlen(".result") + 1;
        char* tmp_str15208 = calloc(tmp_strlen15208, sizeof(char));
        strcpy(tmp_str15208, tmp_str15221);
        strcat(tmp_str15208, ".result");
        int tmp_strlen15186 = strlen(tmp_str15208) + strlen(itoa(result_count)) + 1;
        char* tmp_str15186 = calloc(tmp_strlen15186, sizeof(char));
        strcpy(tmp_str15186, tmp_str15208);
        strcat(tmp_str15186, itoa(result_count));
        int tmp_strlen15177 = strlen(tmp_str15186) + strlen(";\n") + 1;
        char* tmp_str15177 = calloc(tmp_strlen15177, sizeof(char));
        strcpy(tmp_str15177, tmp_str15186);
        strcat(tmp_str15177, ";\n");
        out = tmp_str15177;
      }
      Peek_results tmp_results15150 = Peek(lhs);
      lhs_tok = tmp_results15150.result1;
    }
    ConsumeToken_results tmp_results15109 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results15109.result1;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen14990 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str14990 = calloc(tmp_strlen14990, sizeof(char));
  strcpy(tmp_str14990, indent);
  strcat(tmp_str14990, lhs_ident);
  int tmp_strlen14981 = strlen(tmp_str14990) + strlen(" = ") + 1;
  char* tmp_str14981 = calloc(tmp_strlen14981, sizeof(char));
  strcpy(tmp_str14981, tmp_str14990);
  strcat(tmp_str14981, " = ");
  int tmp_strlen14969 = strlen(tmp_str14981) + strlen(rhs_expr) + 1;
  char* tmp_str14969 = calloc(tmp_strlen14969, sizeof(char));
  strcpy(tmp_str14969, tmp_str14981);
  strcat(tmp_str14969, rhs_expr);
  int tmp_strlen14960 = strlen(tmp_str14969) + strlen(";\n") + 1;
  char* tmp_str14960 = calloc(tmp_strlen14960, sizeof(char));
  strcpy(tmp_str14960, tmp_str14969);
  strcat(tmp_str14960, ";\n");
  char* assignments = tmp_str14960;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results14920 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results14920.result1;
    ConsumeToken_results tmp_results14874 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results14874.result1;
    ConsumeIdent_results tmp_results14828 = ConsumeIdent(lhs);
    lhs = tmp_results14828.result1;
    lhs_ident = tmp_results14828.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results14750 = TranslateExpr(rhs, indent);
    rhs = tmp_results14750.result1;
    rhs_expr_setup = tmp_results14750.result2;
    rhs_expr = tmp_results14750.result3;
    int tmp_strlen14652 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str14652 = calloc(tmp_strlen14652, sizeof(char));
    strcpy(tmp_str14652, setup);
    strcat(tmp_str14652, rhs_expr_setup);
    setup = tmp_str14652;
    int tmp_strlen14608 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str14608 = calloc(tmp_strlen14608, sizeof(char));
    strcpy(tmp_str14608, assignments);
    strcat(tmp_str14608, indent);
    int tmp_strlen14595 = strlen(tmp_str14608) + strlen(lhs_ident) + 1;
    char* tmp_str14595 = calloc(tmp_strlen14595, sizeof(char));
    strcpy(tmp_str14595, tmp_str14608);
    strcat(tmp_str14595, lhs_ident);
    int tmp_strlen14586 = strlen(tmp_str14595) + strlen(" = ") + 1;
    char* tmp_str14586 = calloc(tmp_strlen14586, sizeof(char));
    strcpy(tmp_str14586, tmp_str14595);
    strcat(tmp_str14586, " = ");
    int tmp_strlen14574 = strlen(tmp_str14586) + strlen(rhs_expr) + 1;
    char* tmp_str14574 = calloc(tmp_strlen14574, sizeof(char));
    strcpy(tmp_str14574, tmp_str14586);
    strcat(tmp_str14574, rhs_expr);
    int tmp_strlen14565 = strlen(tmp_str14574) + strlen(";\n") + 1;
    char* tmp_str14565 = calloc(tmp_strlen14565, sizeof(char));
    strcpy(tmp_str14565, tmp_str14574);
    strcat(tmp_str14565, ";\n");
    assignments = tmp_str14565;
    Peek_results tmp_results14556 = Peek(lhs);
    lhs_tok = tmp_results14556.result1;
  }
  ConsumeToken_results tmp_results14523 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results14523.result1;
  int tmp_strlen14447 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str14447 = calloc(tmp_strlen14447, sizeof(char));
  strcpy(tmp_str14447, setup);
  strcat(tmp_str14447, assignments);
  return (TranslateAssignStmt_results){src, tmp_str14447};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results14350 = ConsumeToken(src, TOK_IF);
  src = tmp_results14350.result1;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results14263 = TranslateExpr(src, indent);
  src = tmp_results14263.result1;
  cond_setup = tmp_results14263.result2;
  cond = tmp_results14263.result3;
  ConsumeToken_results tmp_results14208 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results14208.result1;
  char* out = cond_setup;
  int tmp_strlen14113 = strlen(out) + strlen(indent) + 1;
  char* tmp_str14113 = calloc(tmp_strlen14113, sizeof(char));
  strcpy(tmp_str14113, out);
  strcat(tmp_str14113, indent);
  int tmp_strlen14103 = strlen(tmp_str14113) + strlen("if (") + 1;
  char* tmp_str14103 = calloc(tmp_strlen14103, sizeof(char));
  strcpy(tmp_str14103, tmp_str14113);
  strcat(tmp_str14103, "if (");
  int tmp_strlen14095 = strlen(tmp_str14103) + strlen(cond) + 1;
  char* tmp_str14095 = calloc(tmp_strlen14095, sizeof(char));
  strcpy(tmp_str14095, tmp_str14103);
  strcat(tmp_str14095, cond);
  int tmp_strlen14084 = strlen(tmp_str14095) + strlen(") {\n") + 1;
  char* tmp_str14084 = calloc(tmp_strlen14084, sizeof(char));
  strcpy(tmp_str14084, tmp_str14095);
  strcat(tmp_str14084, ") {\n");
  out = tmp_str14084;
  char* body;
  int tmp_strlen14003 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str14003 = calloc(tmp_strlen14003, sizeof(char));
  strcpy(tmp_str14003, indent);
  strcat(tmp_str14003, SINGLE_INDENT);
  TranslateStmts_results tmp_results14058 = TranslateStmts(src, tmp_str14003, func_name);
  src = tmp_results14058.result1;
  body = tmp_results14058.result2;
  ConsumeToken_results tmp_results13986 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results13986.result1;
  int tmp_strlen13926 = strlen(out) + strlen(body) + 1;
  char* tmp_str13926 = calloc(tmp_strlen13926, sizeof(char));
  strcpy(tmp_str13926, out);
  strcat(tmp_str13926, body);
  out = tmp_str13926;
  int tmp_strlen13902 = strlen(out) + strlen(indent) + 1;
  char* tmp_str13902 = calloc(tmp_strlen13902, sizeof(char));
  strcpy(tmp_str13902, out);
  strcat(tmp_str13902, indent);
  int tmp_strlen13895 = strlen(tmp_str13902) + strlen("}") + 1;
  char* tmp_str13895 = calloc(tmp_strlen13895, sizeof(char));
  strcpy(tmp_str13895, tmp_str13902);
  strcat(tmp_str13895, "}");
  out = tmp_str13895;
  int tok;
  Peek_results tmp_results13873 = Peek(src);
  tok = tmp_results13873.result1;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen13798 = strlen(out) + strlen("\n") + 1;
    char* tmp_str13798 = calloc(tmp_strlen13798, sizeof(char));
    strcpy(tmp_str13798, out);
    strcat(tmp_str13798, "\n");
    return (TranslateIfStmt_results){src, tmp_str13798};
  }
  ConsumeToken_results tmp_results13787 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results13787.result1;
  Peek_results tmp_results13746 = Peek(src);
  tok = tmp_results13746.result1;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen13611 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str13611 = calloc(tmp_strlen13611, sizeof(char));
    strcpy(tmp_str13611, indent);
    strcat(tmp_str13611, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results13671 = TranslateIfStmt(src, tmp_str13611, func_name);
    src = tmp_results13671.result1;
    else_out = tmp_results13671.result2;
    int tmp_strlen13566 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str13566 = calloc(tmp_strlen13566, sizeof(char));
    strcpy(tmp_str13566, out);
    strcat(tmp_str13566, " else {\n");
    out = tmp_str13566;
    int tmp_strlen13536 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str13536 = calloc(tmp_strlen13536, sizeof(char));
    strcpy(tmp_str13536, out);
    strcat(tmp_str13536, else_out);
    out = tmp_str13536;
    int tmp_strlen13508 = strlen(out) + strlen(indent) + 1;
    char* tmp_str13508 = calloc(tmp_strlen13508, sizeof(char));
    strcpy(tmp_str13508, out);
    strcat(tmp_str13508, indent);
    int tmp_strlen13499 = strlen(tmp_str13508) + strlen("}\n") + 1;
    char* tmp_str13499 = calloc(tmp_strlen13499, sizeof(char));
    strcpy(tmp_str13499, tmp_str13508);
    strcat(tmp_str13499, "}\n");
    out = tmp_str13499;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results13464 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results13464.result1;
  int tmp_strlen13362 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str13362 = calloc(tmp_strlen13362, sizeof(char));
  strcpy(tmp_str13362, indent);
  strcat(tmp_str13362, SINGLE_INDENT);
  TranslateStmts_results tmp_results13421 = TranslateStmts(src, tmp_str13362, func_name);
  src = tmp_results13421.result1;
  else_out = tmp_results13421.result2;
  ConsumeToken_results tmp_results13345 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results13345.result1;
  int tmp_strlen13278 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str13278 = calloc(tmp_strlen13278, sizeof(char));
  strcpy(tmp_str13278, out);
  strcat(tmp_str13278, " else {\n");
  out = tmp_str13278;
  int tmp_strlen13252 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str13252 = calloc(tmp_strlen13252, sizeof(char));
  strcpy(tmp_str13252, out);
  strcat(tmp_str13252, else_out);
  out = tmp_str13252;
  int tmp_strlen13228 = strlen(out) + strlen(indent) + 1;
  char* tmp_str13228 = calloc(tmp_strlen13228, sizeof(char));
  strcpy(tmp_str13228, out);
  strcat(tmp_str13228, indent);
  int tmp_strlen13219 = strlen(tmp_str13228) + strlen("}\n") + 1;
  char* tmp_str13219 = calloc(tmp_strlen13219, sizeof(char));
  strcpy(tmp_str13219, tmp_str13228);
  strcat(tmp_str13219, "}\n");
  out = tmp_str13219;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  ConsumeToken_results tmp_results13084 = ConsumeToken(src, TOK_FOR);
  src = tmp_results13084.result1;
  Peek_results tmp_results13044 = Peek(src);
  tok = tmp_results13044.result1;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen12862 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str12862 = calloc(tmp_strlen12862, sizeof(char));
    strcpy(tmp_str12862, indent);
    strcat(tmp_str12862, SINGLE_INDENT);
    TranslateExpr_results tmp_results12928 = TranslateExpr(src, tmp_str12862);
    src = tmp_results12928.result1;
    cond_setup = tmp_results12928.result2;
    cond = tmp_results12928.result3;
  }
  ConsumeToken_results tmp_results12850 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results12850.result1;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen12732 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str12732 = calloc(tmp_strlen12732, sizeof(char));
    strcpy(tmp_str12732, indent);
    strcat(tmp_str12732, "while (");
    int tmp_strlen12724 = strlen(tmp_str12732) + strlen(cond) + 1;
    char* tmp_str12724 = calloc(tmp_strlen12724, sizeof(char));
    strcpy(tmp_str12724, tmp_str12732);
    strcat(tmp_str12724, cond);
    int tmp_strlen12713 = strlen(tmp_str12724) + strlen(") {\n") + 1;
    char* tmp_str12713 = calloc(tmp_strlen12713, sizeof(char));
    strcpy(tmp_str12713, tmp_str12724);
    strcat(tmp_str12713, ") {\n");
    out = tmp_str12713;
  } else {
    int tmp_strlen12657 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str12657 = calloc(tmp_strlen12657, sizeof(char));
    strcpy(tmp_str12657, indent);
    strcat(tmp_str12657, "while (true) {\n");
    out = tmp_str12657;
    int tmp_strlen12625 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str12625 = calloc(tmp_strlen12625, sizeof(char));
    strcpy(tmp_str12625, out);
    strcat(tmp_str12625, cond_setup);
    out = tmp_str12625;
    int tmp_strlen12597 = strlen(out) + strlen(indent) + 1;
    char* tmp_str12597 = calloc(tmp_strlen12597, sizeof(char));
    strcpy(tmp_str12597, out);
    strcat(tmp_str12597, indent);
    int tmp_strlen12580 = strlen(tmp_str12597) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str12580 = calloc(tmp_strlen12580, sizeof(char));
    strcpy(tmp_str12580, tmp_str12597);
    strcat(tmp_str12580, SINGLE_INDENT);
    int tmp_strlen12568 = strlen(tmp_str12580) + strlen("if (!(") + 1;
    char* tmp_str12568 = calloc(tmp_strlen12568, sizeof(char));
    strcpy(tmp_str12568, tmp_str12580);
    strcat(tmp_str12568, "if (!(");
    int tmp_strlen12560 = strlen(tmp_str12568) + strlen(cond) + 1;
    char* tmp_str12560 = calloc(tmp_strlen12560, sizeof(char));
    strcpy(tmp_str12560, tmp_str12568);
    strcat(tmp_str12560, cond);
    int tmp_strlen12543 = strlen(tmp_str12560) + strlen(")) break;\n") + 1;
    char* tmp_str12543 = calloc(tmp_strlen12543, sizeof(char));
    strcpy(tmp_str12543, tmp_str12560);
    strcat(tmp_str12543, ")) break;\n");
    out = tmp_str12543;
  }
  char* body;
  int tmp_strlen12456 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str12456 = calloc(tmp_strlen12456, sizeof(char));
  strcpy(tmp_str12456, indent);
  strcat(tmp_str12456, SINGLE_INDENT);
  TranslateStmts_results tmp_results12511 = TranslateStmts(src, tmp_str12456, func_name);
  src = tmp_results12511.result1;
  body = tmp_results12511.result2;
  ConsumeToken_results tmp_results12439 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results12439.result1;
  int tmp_strlen12379 = strlen(out) + strlen(body) + 1;
  char* tmp_str12379 = calloc(tmp_strlen12379, sizeof(char));
  strcpy(tmp_str12379, out);
  strcat(tmp_str12379, body);
  out = tmp_str12379;
  int tmp_strlen12355 = strlen(out) + strlen(indent) + 1;
  char* tmp_str12355 = calloc(tmp_strlen12355, sizeof(char));
  strcpy(tmp_str12355, out);
  strcat(tmp_str12355, indent);
  int tmp_strlen12346 = strlen(tmp_str12355) + strlen("}\n") + 1;
  char* tmp_str12346 = calloc(tmp_strlen12346, sizeof(char));
  strcpy(tmp_str12346, tmp_str12355);
  strcat(tmp_str12346, "}\n");
  out = tmp_str12346;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results12242 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results12242.result1;
  int tmp_strlen12164 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str12164 = calloc(tmp_strlen12164, sizeof(char));
  strcpy(tmp_str12164, indent);
  strcat(tmp_str12164, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str12164};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results12083 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results12083.result1;
  int tmp_strlen12011 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str12011 = calloc(tmp_strlen12011, sizeof(char));
  strcpy(tmp_str12011, indent);
  strcat(tmp_str12011, "break;");
  return (TranslateBreakStmt_results){src, tmp_str12011};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results11910 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results11910.result1;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results11787 = TranslateExprs(src, indent);
  src = tmp_results11787.result1;
  expr_count = tmp_results11787.result2;
  exprs_setup = tmp_results11787.result3;
  exprs_value = tmp_results11787.result4;
  ConsumeToken_results tmp_results11711 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results11711.result1;
  int tmp_strlen11628 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str11628 = calloc(tmp_strlen11628, sizeof(char));
  strcpy(tmp_str11628, exprs_setup);
  strcat(tmp_str11628, indent);
  int tmp_strlen11615 = strlen(tmp_str11628) + strlen("return ") + 1;
  char* tmp_str11615 = calloc(tmp_strlen11615, sizeof(char));
  strcpy(tmp_str11615, tmp_str11628);
  strcat(tmp_str11615, "return ");
  char* out = tmp_str11615;
  if ((expr_count) > (1)) {
    int tmp_strlen11566 = strlen(out) + strlen("(") + 1;
    char* tmp_str11566 = calloc(tmp_strlen11566, sizeof(char));
    strcpy(tmp_str11566, out);
    strcat(tmp_str11566, "(");
    int tmp_strlen11553 = strlen(tmp_str11566) + strlen(func_name) + 1;
    char* tmp_str11553 = calloc(tmp_strlen11553, sizeof(char));
    strcpy(tmp_str11553, tmp_str11566);
    strcat(tmp_str11553, func_name);
    int tmp_strlen11537 = strlen(tmp_str11553) + strlen("_results){") + 1;
    char* tmp_str11537 = calloc(tmp_strlen11537, sizeof(char));
    strcpy(tmp_str11537, tmp_str11553);
    strcat(tmp_str11537, "_results){");
    out = tmp_str11537;
  }
  int tmp_strlen11502 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str11502 = calloc(tmp_strlen11502, sizeof(char));
  strcpy(tmp_str11502, out);
  strcat(tmp_str11502, exprs_value);
  out = tmp_str11502;
  if ((expr_count) > (1)) {
    int tmp_strlen11452 = strlen(out) + strlen("}") + 1;
    char* tmp_str11452 = calloc(tmp_strlen11452, sizeof(char));
    strcpy(tmp_str11452, out);
    strcat(tmp_str11452, "}");
    out = tmp_str11452;
  }
  int tmp_strlen11423 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str11423 = calloc(tmp_strlen11423, sizeof(char));
  strcpy(tmp_str11423, out);
  strcat(tmp_str11423, ";\n");
  out = tmp_str11423;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results11267 = Peek(src);
  tok = tmp_results11267.result1;
  tok_str = tmp_results11267.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results11190 = TranslateConstDeclStmt(src, indent);
    src = tmp_results11190.result1;
    out = tmp_results11190.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results11080 = TranslateVarDeclStmt(src, indent);
      src = tmp_results11080.result1;
      out = tmp_results11080.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results10973 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results10973.result1;
        out = tmp_results10973.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results10859 = TranslateForStmt(src, indent, func_name);
          src = tmp_results10859.result1;
          out = tmp_results10859.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results10739 = TranslateContinueStmt(src, indent);
            src = tmp_results10739.result1;
            out = tmp_results10739.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results10628 = TranslateBreakStmt(src, indent);
              src = tmp_results10628.result1;
              out = tmp_results10628.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results10519 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results10519.result1;
                out = tmp_results10519.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if (((tok) == (TOK_IDENT)) || ((tok) == (TOK_UNDERSCORE))) {
                  char* first_ident;
                  ConsumeIdentOrUnderscore_results tmp_results10342 = ConsumeIdentOrUnderscore(src);
                  src = tmp_results10342.result1;
                  first_ident = tmp_results10342.result2;
                  Peek_results tmp_results10285 = Peek(src);
                  tok = tmp_results10285.result1;
                  int tmp_strlen10234 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str10234 = calloc(tmp_strlen10234, sizeof(char));
                  strcpy(tmp_str10234, first_ident);
                  strcat(tmp_str10234, src);
                  src = tmp_str10234;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results10170 = TranslateAssignStmt(src, indent);
                    src = tmp_results10170.result1;
                    out = tmp_results10170.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results10011 = TranslateExpr(src, indent);
                    src = tmp_results10011.result1;
                    setup = tmp_results10011.result2;
                    val = tmp_results10011.result3;
                    ConsumeToken_results tmp_results9954 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results9954.result1;
                    int tmp_strlen9881 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str9881 = calloc(tmp_strlen9881, sizeof(char));
                    strcpy(tmp_str9881, setup);
                    strcat(tmp_str9881, indent);
                    int tmp_strlen9874 = strlen(tmp_str9881) + strlen(val) + 1;
                    char* tmp_str9874 = calloc(tmp_strlen9874, sizeof(char));
                    strcpy(tmp_str9874, tmp_str9881);
                    strcat(tmp_str9874, val);
                    int tmp_strlen9865 = strlen(tmp_str9874) + strlen(";\n") + 1;
                    char* tmp_str9865 = calloc(tmp_strlen9865, sizeof(char));
                    strcpy(tmp_str9865, tmp_str9874);
                    strcat(tmp_str9865, ";\n");
                    out = tmp_str9865;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen9756 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str9756 = calloc(tmp_strlen9756, sizeof(char));
                  strcpy(tmp_str9756, "unexpected stmt token, got: ");
                  strcat(tmp_str9756, itoa(tok));
                  int tmp_strlen9747 = strlen(tmp_str9756) + strlen(" \"") + 1;
                  char* tmp_str9747 = calloc(tmp_strlen9747, sizeof(char));
                  strcpy(tmp_str9747, tmp_str9756);
                  strcat(tmp_str9747, " \"");
                  int tmp_strlen9736 = strlen(tmp_str9747) + strlen(tok_str) + 1;
                  char* tmp_str9736 = calloc(tmp_strlen9736, sizeof(char));
                  strcpy(tmp_str9736, tmp_str9747);
                  strcat(tmp_str9736, tok_str);
                  int tmp_strlen9728 = strlen(tmp_str9736) + strlen("\"") + 1;
                  char* tmp_str9728 = calloc(tmp_strlen9728, sizeof(char));
                  strcpy(tmp_str9728, tmp_str9736);
                  strcat(tmp_str9728, "\"");
                  printf("%s", tmp_str9728);
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
  Peek_results tmp_results9592 = Peek(src);
  tok = tmp_results9592.result1;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results9476 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results9476.result1;
      Peek_results tmp_results9424 = Peek(src);
      tok = tmp_results9424.result1;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results9337 = TranslateStmt(src, indent, func_name);
    src = tmp_results9337.result1;
    stmt_out = tmp_results9337.result2;
    int tmp_strlen9254 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str9254 = calloc(tmp_strlen9254, sizeof(char));
    strcpy(tmp_str9254, out);
    strcat(tmp_str9254, stmt_out);
    out = tmp_str9254;
    Peek_results tmp_results9245 = Peek(src);
    tok = tmp_results9245.result1;
  }
  return (TranslateStmts_results){src, out};
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results9093 = Next(src);
  src = tmp_results9093.result1;
  tok = tmp_results9093.result2;
  tok_str = tmp_results9093.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen8919 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str8919 = calloc(tmp_strlen8919, sizeof(char));
    strcpy(tmp_str8919, "expected false or true, got: ");
    strcat(tmp_str8919, itoa(tok));
    int tmp_strlen8910 = strlen(tmp_str8919) + strlen(" \"") + 1;
    char* tmp_str8910 = calloc(tmp_strlen8910, sizeof(char));
    strcpy(tmp_str8910, tmp_str8919);
    strcat(tmp_str8910, " \"");
    int tmp_strlen8899 = strlen(tmp_str8910) + strlen(tok_str) + 1;
    char* tmp_str8899 = calloc(tmp_strlen8899, sizeof(char));
    strcpy(tmp_str8899, tmp_str8910);
    strcat(tmp_str8899, tok_str);
    int tmp_strlen8891 = strlen(tmp_str8899) + strlen("\"") + 1;
    char* tmp_str8891 = calloc(tmp_strlen8891, sizeof(char));
    strcpy(tmp_str8891, tmp_str8899);
    strcat(tmp_str8891, "\"");
    printf("%s", tmp_str8891);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results8782 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results8782.result1;
  lit = tmp_results8782.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results8633 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results8633.result1;
  lit = tmp_results8633.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  ConsumeToken_results tmp_results8456 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results8456.result1;
  Peek_results tmp_results8413 = Peek(src);
  tok = tmp_results8413.result1;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results8267 = TranslateExprs(src, indent);
    src = tmp_results8267.result1;
    expr_count = tmp_results8267.result2;
    args_setup = tmp_results8267.result3;
    arg_values = tmp_results8267.result4;
  }
  ConsumeToken_results tmp_results8187 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results8187.result1;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen8056 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str8056 = calloc(tmp_strlen8056, sizeof(char));
    strcpy(tmp_str8056, "printf(\"%s\", ");
    strcat(tmp_str8056, arg_values);
    int tmp_strlen8049 = strlen(tmp_str8056) + strlen(")") + 1;
    char* tmp_str8049 = calloc(tmp_strlen8049, sizeof(char));
    strcpy(tmp_str8049, tmp_str8056);
    strcat(tmp_str8049, ")");
    val = tmp_str8049;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen7979 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str7979 = calloc(tmp_strlen7979, sizeof(char));
      strcpy(tmp_str7979, "strlen(");
      strcat(tmp_str7979, arg_values);
      int tmp_strlen7972 = strlen(tmp_str7979) + strlen(")") + 1;
      char* tmp_str7972 = calloc(tmp_strlen7972, sizeof(char));
      strcpy(tmp_str7972, tmp_str7979);
      strcat(tmp_str7972, ")");
      val = tmp_str7972;
    } else {
      int tmp_strlen7931 = strlen(callee) + strlen("(") + 1;
      char* tmp_str7931 = calloc(tmp_strlen7931, sizeof(char));
      strcpy(tmp_str7931, callee);
      strcat(tmp_str7931, "(");
      int tmp_strlen7917 = strlen(tmp_str7931) + strlen(arg_values) + 1;
      char* tmp_str7917 = calloc(tmp_strlen7917, sizeof(char));
      strcpy(tmp_str7917, tmp_str7931);
      strcat(tmp_str7917, arg_values);
      int tmp_strlen7910 = strlen(tmp_str7917) + strlen(")") + 1;
      char* tmp_str7910 = calloc(tmp_strlen7910, sizeof(char));
      strcpy(tmp_str7910, tmp_str7917);
      strcat(tmp_str7910, ")");
      val = tmp_str7910;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  int p = strlen(src);
  ConsumeToken_results tmp_results7723 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results7723.result1;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen7541 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str7541 = calloc(tmp_strlen7541, sizeof(char));
  strcpy(tmp_str7541, "strlen(");
  strcat(tmp_str7541, strvar);
  int tmp_strlen7534 = strlen(tmp_str7541) + strlen(")") + 1;
  char* tmp_str7534 = calloc(tmp_strlen7534, sizeof(char));
  strcpy(tmp_str7534, tmp_str7541);
  strcat(tmp_str7534, ")");
  char* high_expr = tmp_str7534;
  Peek_results tmp_results7529 = Peek(src);
  tok = tmp_results7529.result1;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results7476 = ConsumeToken(src, TOK_COLON);
    src = tmp_results7476.result1;
    TranslateExpr_results tmp_results7430 = TranslateExpr(src, indent);
    src = tmp_results7430.result1;
    high_setup = tmp_results7430.result2;
    high_expr = tmp_results7430.result3;
    ConsumeToken_results tmp_results7366 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results7366.result1;
  } else {
    TranslateExpr_results tmp_results7304 = TranslateExpr(src, indent);
    src = tmp_results7304.result1;
    low_setup = tmp_results7304.result2;
    low_expr = tmp_results7304.result3;
    Peek_results tmp_results7242 = Peek(src);
    tok = tmp_results7242.result1;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results7178 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results7178.result1;
      int tmp_strlen7089 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str7089 = calloc(tmp_strlen7089, sizeof(char));
      strcpy(tmp_str7089, strvar);
      strcat(tmp_str7089, "[");
      int tmp_strlen7077 = strlen(tmp_str7089) + strlen(low_expr) + 1;
      char* tmp_str7077 = calloc(tmp_strlen7077, sizeof(char));
      strcpy(tmp_str7077, tmp_str7089);
      strcat(tmp_str7077, low_expr);
      int tmp_strlen7070 = strlen(tmp_str7077) + strlen("]") + 1;
      char* tmp_str7070 = calloc(tmp_strlen7070, sizeof(char));
      strcpy(tmp_str7070, tmp_str7077);
      strcat(tmp_str7070, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str7070};
    }
    ConsumeToken_results tmp_results7051 = ConsumeToken(src, TOK_COLON);
    src = tmp_results7051.result1;
    Peek_results tmp_results7005 = Peek(src);
    tok = tmp_results7005.result1;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results6941 = TranslateExpr(src, indent);
      src = tmp_results6941.result1;
      high_setup = tmp_results6941.result2;
      high_expr = tmp_results6941.result3;
    }
    ConsumeToken_results tmp_results6867 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results6867.result1;
  }
  int tmp_strlen6774 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str6774 = calloc(tmp_strlen6774, sizeof(char));
  strcpy(tmp_str6774, "tmp_str");
  strcat(tmp_str6774, itoa(p));
  char* tmp_str = tmp_str6774;
  int tmp_strlen6721 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str6721 = calloc(tmp_strlen6721, sizeof(char));
  strcpy(tmp_str6721, "tmp_strlen");
  strcat(tmp_str6721, itoa(p));
  char* tmp_strlen = tmp_str6721;
  int tmp_strlen6673 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str6673 = calloc(tmp_strlen6673, sizeof(char));
  strcpy(tmp_str6673, low_setup);
  strcat(tmp_str6673, high_setup);
  char* setup = tmp_str6673;
  int tmp_strlen6645 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6645 = calloc(tmp_strlen6645, sizeof(char));
  strcpy(tmp_str6645, setup);
  strcat(tmp_str6645, indent);
  int tmp_strlen6635 = strlen(tmp_str6645) + strlen("int ") + 1;
  char* tmp_str6635 = calloc(tmp_strlen6635, sizeof(char));
  strcpy(tmp_str6635, tmp_str6645);
  strcat(tmp_str6635, "int ");
  int tmp_strlen6621 = strlen(tmp_str6635) + strlen(tmp_strlen) + 1;
  char* tmp_str6621 = calloc(tmp_strlen6621, sizeof(char));
  strcpy(tmp_str6621, tmp_str6635);
  strcat(tmp_str6621, tmp_strlen);
  int tmp_strlen6611 = strlen(tmp_str6621) + strlen(" = (") + 1;
  char* tmp_str6611 = calloc(tmp_strlen6611, sizeof(char));
  strcpy(tmp_str6611, tmp_str6621);
  strcat(tmp_str6611, " = (");
  int tmp_strlen6598 = strlen(tmp_str6611) + strlen(high_expr) + 1;
  char* tmp_str6598 = calloc(tmp_strlen6598, sizeof(char));
  strcpy(tmp_str6598, tmp_str6611);
  strcat(tmp_str6598, high_expr);
  int tmp_strlen6587 = strlen(tmp_str6598) + strlen(") - (") + 1;
  char* tmp_str6587 = calloc(tmp_strlen6587, sizeof(char));
  strcpy(tmp_str6587, tmp_str6598);
  strcat(tmp_str6587, ") - (");
  int tmp_strlen6575 = strlen(tmp_str6587) + strlen(low_expr) + 1;
  char* tmp_str6575 = calloc(tmp_strlen6575, sizeof(char));
  strcpy(tmp_str6575, tmp_str6587);
  strcat(tmp_str6575, low_expr);
  int tmp_strlen6561 = strlen(tmp_str6575) + strlen(") + 1;\n") + 1;
  char* tmp_str6561 = calloc(tmp_strlen6561, sizeof(char));
  strcpy(tmp_str6561, tmp_str6575);
  strcat(tmp_str6561, ") + 1;\n");
  setup = tmp_str6561;
  int tmp_strlen6533 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6533 = calloc(tmp_strlen6533, sizeof(char));
  strcpy(tmp_str6533, setup);
  strcat(tmp_str6533, indent);
  int tmp_strlen6521 = strlen(tmp_str6533) + strlen("char* ") + 1;
  char* tmp_str6521 = calloc(tmp_strlen6521, sizeof(char));
  strcpy(tmp_str6521, tmp_str6533);
  strcat(tmp_str6521, "char* ");
  int tmp_strlen6510 = strlen(tmp_str6521) + strlen(tmp_str) + 1;
  char* tmp_str6510 = calloc(tmp_strlen6510, sizeof(char));
  strcpy(tmp_str6510, tmp_str6521);
  strcat(tmp_str6510, tmp_str);
  int tmp_strlen6494 = strlen(tmp_str6510) + strlen(" = calloc(") + 1;
  char* tmp_str6494 = calloc(tmp_strlen6494, sizeof(char));
  strcpy(tmp_str6494, tmp_str6510);
  strcat(tmp_str6494, " = calloc(");
  int tmp_strlen6480 = strlen(tmp_str6494) + strlen(tmp_strlen) + 1;
  char* tmp_str6480 = calloc(tmp_strlen6480, sizeof(char));
  strcpy(tmp_str6480, tmp_str6494);
  strcat(tmp_str6480, tmp_strlen);
  int tmp_strlen6456 = strlen(tmp_str6480) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str6456 = calloc(tmp_strlen6456, sizeof(char));
  strcpy(tmp_str6456, tmp_str6480);
  strcat(tmp_str6456, ", sizeof(char));\n");
  setup = tmp_str6456;
  int tmp_strlen6428 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6428 = calloc(tmp_strlen6428, sizeof(char));
  strcpy(tmp_str6428, setup);
  strcat(tmp_str6428, indent);
  int tmp_strlen6414 = strlen(tmp_str6428) + strlen("strncpy(") + 1;
  char* tmp_str6414 = calloc(tmp_strlen6414, sizeof(char));
  strcpy(tmp_str6414, tmp_str6428);
  strcat(tmp_str6414, "strncpy(");
  int tmp_strlen6403 = strlen(tmp_str6414) + strlen(tmp_str) + 1;
  char* tmp_str6403 = calloc(tmp_strlen6403, sizeof(char));
  strcpy(tmp_str6403, tmp_str6414);
  strcat(tmp_str6403, tmp_str);
  int tmp_strlen6395 = strlen(tmp_str6403) + strlen(", ") + 1;
  char* tmp_str6395 = calloc(tmp_strlen6395, sizeof(char));
  strcpy(tmp_str6395, tmp_str6403);
  strcat(tmp_str6395, ", ");
  int tmp_strlen6385 = strlen(tmp_str6395) + strlen(strvar) + 1;
  char* tmp_str6385 = calloc(tmp_strlen6385, sizeof(char));
  strcpy(tmp_str6385, tmp_str6395);
  strcat(tmp_str6385, strvar);
  int tmp_strlen6376 = strlen(tmp_str6385) + strlen(" + ") + 1;
  char* tmp_str6376 = calloc(tmp_strlen6376, sizeof(char));
  strcpy(tmp_str6376, tmp_str6385);
  strcat(tmp_str6376, " + ");
  int tmp_strlen6364 = strlen(tmp_str6376) + strlen(low_expr) + 1;
  char* tmp_str6364 = calloc(tmp_strlen6364, sizeof(char));
  strcpy(tmp_str6364, tmp_str6376);
  strcat(tmp_str6364, low_expr);
  int tmp_strlen6356 = strlen(tmp_str6364) + strlen(", ") + 1;
  char* tmp_str6356 = calloc(tmp_strlen6356, sizeof(char));
  strcpy(tmp_str6356, tmp_str6364);
  strcat(tmp_str6356, ", ");
  int tmp_strlen6342 = strlen(tmp_str6356) + strlen(tmp_strlen) + 1;
  char* tmp_str6342 = calloc(tmp_strlen6342, sizeof(char));
  strcpy(tmp_str6342, tmp_str6356);
  strcat(tmp_str6342, tmp_strlen);
  int tmp_strlen6328 = strlen(tmp_str6342) + strlen(" - 1);\n") + 1;
  char* tmp_str6328 = calloc(tmp_strlen6328, sizeof(char));
  strcpy(tmp_str6328, tmp_str6342);
  strcat(tmp_str6328, " - 1);\n");
  setup = tmp_str6328;
  int tmp_strlen6300 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6300 = calloc(tmp_strlen6300, sizeof(char));
  strcpy(tmp_str6300, setup);
  strcat(tmp_str6300, indent);
  int tmp_strlen6289 = strlen(tmp_str6300) + strlen(tmp_str) + 1;
  char* tmp_str6289 = calloc(tmp_strlen6289, sizeof(char));
  strcpy(tmp_str6289, tmp_str6300);
  strcat(tmp_str6289, tmp_str);
  int tmp_strlen6282 = strlen(tmp_str6289) + strlen("[") + 1;
  char* tmp_str6282 = calloc(tmp_strlen6282, sizeof(char));
  strcpy(tmp_str6282, tmp_str6289);
  strcat(tmp_str6282, "[");
  int tmp_strlen6268 = strlen(tmp_str6282) + strlen(tmp_strlen) + 1;
  char* tmp_str6268 = calloc(tmp_strlen6268, sizeof(char));
  strcpy(tmp_str6268, tmp_str6282);
  strcat(tmp_str6268, tmp_strlen);
  int tmp_strlen6250 = strlen(tmp_str6268) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str6250 = calloc(tmp_strlen6250, sizeof(char));
  strcpy(tmp_str6250, tmp_str6268);
  strcat(tmp_str6250, " - 1] = 0;\n");
  setup = tmp_str6250;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6091 = Peek(src);
  tok = tmp_results6091.result1;
  tok_str = tmp_results6091.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results5981 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results5981.result1;
    TranslateExpr_results tmp_results5934 = TranslateExpr(src, indent);
    src = tmp_results5934.result1;
    setup = tmp_results5934.result2;
    val = tmp_results5934.result3;
    ConsumeToken_results tmp_results5881 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results5881.result1;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results5727 = TranslateBoolLiteral(src);
      src = tmp_results5727.result1;
      lit = tmp_results5727.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results5596 = TranslateIntLiteral(src);
        src = tmp_results5596.result1;
        lit = tmp_results5596.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results5466 = TranslateStringLiteral(src);
          src = tmp_results5466.result1;
          lit = tmp_results5466.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results5332 = ConsumeIdent(src);
            src = tmp_results5332.result1;
            ident = tmp_results5332.result2;
            Peek_results tmp_results5293 = Peek(src);
            tok = tmp_results5293.result1;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results5172 = TranslateCall(src, indent, ident);
              src = tmp_results5172.result1;
              setup = tmp_results5172.result2;
              expr = tmp_results5172.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results4972 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results4972.result1;
                setup = tmp_results4972.result2;
                expr = tmp_results4972.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen4752 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str4752 = calloc(tmp_strlen4752, sizeof(char));
            strcpy(tmp_str4752, "unexpected expr, got: ");
            strcat(tmp_str4752, itoa(tok));
            int tmp_strlen4743 = strlen(tmp_str4752) + strlen(" \"") + 1;
            char* tmp_str4743 = calloc(tmp_strlen4743, sizeof(char));
            strcpy(tmp_str4743, tmp_str4752);
            strcat(tmp_str4743, " \"");
            int tmp_strlen4732 = strlen(tmp_str4743) + strlen(tok_str) + 1;
            char* tmp_str4732 = calloc(tmp_strlen4732, sizeof(char));
            strcpy(tmp_str4732, tmp_str4743);
            strcat(tmp_str4732, tok_str);
            int tmp_strlen4724 = strlen(tmp_str4732) + strlen("\"") + 1;
            char* tmp_str4724 = calloc(tmp_strlen4724, sizeof(char));
            strcpy(tmp_str4724, tmp_str4732);
            strcat(tmp_str4724, "\"");
            printf("%s", tmp_str4724);
            exit(1);
          }
        }
      }
    }
  }
}

TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent) {
  int tok;
  Peek_results tmp_results4595 = Peek(src);
  tok = tmp_results4595.result1;
  if (IsUnaryOp(tok)) {
    char* tok_str;
    ConsumeToken_results tmp_results4516 = ConsumeToken(src, tok);
    src = tmp_results4516.result1;
    tok_str = tmp_results4516.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results4420 = TranslateExpr(src, indent);
    src = tmp_results4420.result1;
    setup = tmp_results4420.result2;
    val = tmp_results4420.result3;
    int tmp_strlen4347 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str4347 = calloc(tmp_strlen4347, sizeof(char));
    strcpy(tmp_str4347, tok_str);
    strcat(tmp_str4347, "(");
    int tmp_strlen4340 = strlen(tmp_str4347) + strlen(val) + 1;
    char* tmp_str4340 = calloc(tmp_strlen4340, sizeof(char));
    strcpy(tmp_str4340, tmp_str4347);
    strcat(tmp_str4340, val);
    int tmp_strlen4333 = strlen(tmp_str4340) + strlen(")") + 1;
    char* tmp_str4333 = calloc(tmp_strlen4333, sizeof(char));
    strcpy(tmp_str4333, tmp_str4340);
    strcat(tmp_str4333, ")");
    val = tmp_str4333;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results4229 = TranslateOperand(src, indent);
    src = tmp_results4229.result1;
    setup = tmp_results4229.result2;
    expr = tmp_results4229.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results3986 = TranslateUnaryExpr(src, indent);
  src = tmp_results3986.result1;
  setup = tmp_results3986.result2;
  val = tmp_results3986.result3;
  int op;
  char* op_str;
  Peek_results tmp_results3893 = Peek(src);
  op = tmp_results3893.result1;
  op_str = tmp_results3893.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results3806 = ConsumeToken(src, op);
    src = tmp_results3806.result1;
    op_str = tmp_results3806.result2;
    int tok;
    Peek_results tmp_results3741 = Peek(src);
    tok = tmp_results3741.result1;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results3677 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results3677.result1;
      Peek_results tmp_results3625 = Peek(src);
      tok = tmp_results3625.result1;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results3534 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results3534.result1;
    setup_b = tmp_results3534.result2;
    val_b = tmp_results3534.result3;
    int tmp_strlen3423 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str3423 = calloc(tmp_strlen3423, sizeof(char));
    strcpy(tmp_str3423, setup);
    strcat(tmp_str3423, setup_b);
    setup = tmp_str3423;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen3331 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str3331 = calloc(tmp_strlen3331, sizeof(char));
      strcpy(tmp_str3331, "tmp_str");
      strcat(tmp_str3331, itoa(strlen(src)));
      char* tmp_str = tmp_str3331;
      int tmp_strlen3263 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str3263 = calloc(tmp_strlen3263, sizeof(char));
      strcpy(tmp_str3263, "tmp_strlen");
      strcat(tmp_str3263, itoa(strlen(src)));
      char* tmp_strlen = tmp_str3263;
      int tmp_strlen3227 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3227 = calloc(tmp_strlen3227, sizeof(char));
      strcpy(tmp_str3227, setup);
      strcat(tmp_str3227, indent);
      int tmp_strlen3217 = strlen(tmp_str3227) + strlen("int ") + 1;
      char* tmp_str3217 = calloc(tmp_strlen3217, sizeof(char));
      strcpy(tmp_str3217, tmp_str3227);
      strcat(tmp_str3217, "int ");
      int tmp_strlen3203 = strlen(tmp_str3217) + strlen(tmp_strlen) + 1;
      char* tmp_str3203 = calloc(tmp_strlen3203, sizeof(char));
      strcpy(tmp_str3203, tmp_str3217);
      strcat(tmp_str3203, tmp_strlen);
      int tmp_strlen3187 = strlen(tmp_str3203) + strlen(" = strlen(") + 1;
      char* tmp_str3187 = calloc(tmp_strlen3187, sizeof(char));
      strcpy(tmp_str3187, tmp_str3203);
      strcat(tmp_str3187, " = strlen(");
      int tmp_strlen3180 = strlen(tmp_str3187) + strlen(val) + 1;
      char* tmp_str3180 = calloc(tmp_strlen3180, sizeof(char));
      strcpy(tmp_str3180, tmp_str3187);
      strcat(tmp_str3180, val);
      int tmp_strlen3163 = strlen(tmp_str3180) + strlen(") + strlen(") + 1;
      char* tmp_str3163 = calloc(tmp_strlen3163, sizeof(char));
      strcpy(tmp_str3163, tmp_str3180);
      strcat(tmp_str3163, ") + strlen(");
      int tmp_strlen3154 = strlen(tmp_str3163) + strlen(val_b) + 1;
      char* tmp_str3154 = calloc(tmp_strlen3154, sizeof(char));
      strcpy(tmp_str3154, tmp_str3163);
      strcat(tmp_str3154, val_b);
      int tmp_strlen3140 = strlen(tmp_str3154) + strlen(") + 1;\n") + 1;
      char* tmp_str3140 = calloc(tmp_strlen3140, sizeof(char));
      strcpy(tmp_str3140, tmp_str3154);
      strcat(tmp_str3140, ") + 1;\n");
      setup = tmp_str3140;
      int tmp_strlen3104 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3104 = calloc(tmp_strlen3104, sizeof(char));
      strcpy(tmp_str3104, setup);
      strcat(tmp_str3104, indent);
      int tmp_strlen3092 = strlen(tmp_str3104) + strlen("char* ") + 1;
      char* tmp_str3092 = calloc(tmp_strlen3092, sizeof(char));
      strcpy(tmp_str3092, tmp_str3104);
      strcat(tmp_str3092, "char* ");
      int tmp_strlen3081 = strlen(tmp_str3092) + strlen(tmp_str) + 1;
      char* tmp_str3081 = calloc(tmp_strlen3081, sizeof(char));
      strcpy(tmp_str3081, tmp_str3092);
      strcat(tmp_str3081, tmp_str);
      int tmp_strlen3065 = strlen(tmp_str3081) + strlen(" = calloc(") + 1;
      char* tmp_str3065 = calloc(tmp_strlen3065, sizeof(char));
      strcpy(tmp_str3065, tmp_str3081);
      strcat(tmp_str3065, " = calloc(");
      int tmp_strlen3051 = strlen(tmp_str3065) + strlen(tmp_strlen) + 1;
      char* tmp_str3051 = calloc(tmp_strlen3051, sizeof(char));
      strcpy(tmp_str3051, tmp_str3065);
      strcat(tmp_str3051, tmp_strlen);
      int tmp_strlen3027 = strlen(tmp_str3051) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str3027 = calloc(tmp_strlen3027, sizeof(char));
      strcpy(tmp_str3027, tmp_str3051);
      strcat(tmp_str3027, ", sizeof(char));\n");
      setup = tmp_str3027;
      int tmp_strlen2991 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str2991 = calloc(tmp_strlen2991, sizeof(char));
      strcpy(tmp_str2991, setup);
      strcat(tmp_str2991, indent);
      int tmp_strlen2978 = strlen(tmp_str2991) + strlen("strcpy(") + 1;
      char* tmp_str2978 = calloc(tmp_strlen2978, sizeof(char));
      strcpy(tmp_str2978, tmp_str2991);
      strcat(tmp_str2978, "strcpy(");
      int tmp_strlen2967 = strlen(tmp_str2978) + strlen(tmp_str) + 1;
      char* tmp_str2967 = calloc(tmp_strlen2967, sizeof(char));
      strcpy(tmp_str2967, tmp_str2978);
      strcat(tmp_str2967, tmp_str);
      int tmp_strlen2959 = strlen(tmp_str2967) + strlen(", ") + 1;
      char* tmp_str2959 = calloc(tmp_strlen2959, sizeof(char));
      strcpy(tmp_str2959, tmp_str2967);
      strcat(tmp_str2959, ", ");
      int tmp_strlen2952 = strlen(tmp_str2959) + strlen(val) + 1;
      char* tmp_str2952 = calloc(tmp_strlen2952, sizeof(char));
      strcpy(tmp_str2952, tmp_str2959);
      strcat(tmp_str2952, val);
      int tmp_strlen2942 = strlen(tmp_str2952) + strlen(");\n") + 1;
      char* tmp_str2942 = calloc(tmp_strlen2942, sizeof(char));
      strcpy(tmp_str2942, tmp_str2952);
      strcat(tmp_str2942, ");\n");
      setup = tmp_str2942;
      int tmp_strlen2906 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str2906 = calloc(tmp_strlen2906, sizeof(char));
      strcpy(tmp_str2906, setup);
      strcat(tmp_str2906, indent);
      int tmp_strlen2893 = strlen(tmp_str2906) + strlen("strcat(") + 1;
      char* tmp_str2893 = calloc(tmp_strlen2893, sizeof(char));
      strcpy(tmp_str2893, tmp_str2906);
      strcat(tmp_str2893, "strcat(");
      int tmp_strlen2882 = strlen(tmp_str2893) + strlen(tmp_str) + 1;
      char* tmp_str2882 = calloc(tmp_strlen2882, sizeof(char));
      strcpy(tmp_str2882, tmp_str2893);
      strcat(tmp_str2882, tmp_str);
      int tmp_strlen2874 = strlen(tmp_str2882) + strlen(", ") + 1;
      char* tmp_str2874 = calloc(tmp_strlen2874, sizeof(char));
      strcpy(tmp_str2874, tmp_str2882);
      strcat(tmp_str2874, ", ");
      int tmp_strlen2865 = strlen(tmp_str2874) + strlen(val_b) + 1;
      char* tmp_str2865 = calloc(tmp_strlen2865, sizeof(char));
      strcpy(tmp_str2865, tmp_str2874);
      strcat(tmp_str2865, val_b);
      int tmp_strlen2855 = strlen(tmp_str2865) + strlen(");\n") + 1;
      char* tmp_str2855 = calloc(tmp_strlen2855, sizeof(char));
      strcpy(tmp_str2855, tmp_str2865);
      strcat(tmp_str2855, ");\n");
      setup = tmp_str2855;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen2757 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str2757 = calloc(tmp_strlen2757, sizeof(char));
        strcpy(tmp_str2757, "(strcmp(");
        strcat(tmp_str2757, val);
        int tmp_strlen2749 = strlen(tmp_str2757) + strlen(", ") + 1;
        char* tmp_str2749 = calloc(tmp_strlen2749, sizeof(char));
        strcpy(tmp_str2749, tmp_str2757);
        strcat(tmp_str2749, ", ");
        int tmp_strlen2740 = strlen(tmp_str2749) + strlen(val_b) + 1;
        char* tmp_str2740 = calloc(tmp_strlen2740, sizeof(char));
        strcpy(tmp_str2740, tmp_str2749);
        strcat(tmp_str2740, val_b);
        int tmp_strlen2727 = strlen(tmp_str2740) + strlen(") == 0)") + 1;
        char* tmp_str2727 = calloc(tmp_strlen2727, sizeof(char));
        strcpy(tmp_str2727, tmp_str2740);
        strcat(tmp_str2727, ") == 0)");
        val = tmp_str2727;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen2654 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str2654 = calloc(tmp_strlen2654, sizeof(char));
          strcpy(tmp_str2654, "(strcmp(");
          strcat(tmp_str2654, val);
          int tmp_strlen2646 = strlen(tmp_str2654) + strlen(", ") + 1;
          char* tmp_str2646 = calloc(tmp_strlen2646, sizeof(char));
          strcpy(tmp_str2646, tmp_str2654);
          strcat(tmp_str2646, ", ");
          int tmp_strlen2637 = strlen(tmp_str2646) + strlen(val_b) + 1;
          char* tmp_str2637 = calloc(tmp_strlen2637, sizeof(char));
          strcpy(tmp_str2637, tmp_str2646);
          strcat(tmp_str2637, val_b);
          int tmp_strlen2624 = strlen(tmp_str2637) + strlen(") != 0)") + 1;
          char* tmp_str2624 = calloc(tmp_strlen2624, sizeof(char));
          strcpy(tmp_str2624, tmp_str2637);
          strcat(tmp_str2624, ") != 0)");
          val = tmp_str2624;
        } else {
          int tmp_strlen2578 = strlen("(") + strlen(val) + 1;
          char* tmp_str2578 = calloc(tmp_strlen2578, sizeof(char));
          strcpy(tmp_str2578, "(");
          strcat(tmp_str2578, val);
          int tmp_strlen2570 = strlen(tmp_str2578) + strlen(") ") + 1;
          char* tmp_str2570 = calloc(tmp_strlen2570, sizeof(char));
          strcpy(tmp_str2570, tmp_str2578);
          strcat(tmp_str2570, ") ");
          int tmp_strlen2560 = strlen(tmp_str2570) + strlen(op_str) + 1;
          char* tmp_str2560 = calloc(tmp_strlen2560, sizeof(char));
          strcpy(tmp_str2560, tmp_str2570);
          strcat(tmp_str2560, op_str);
          int tmp_strlen2552 = strlen(tmp_str2560) + strlen(" (") + 1;
          char* tmp_str2552 = calloc(tmp_strlen2552, sizeof(char));
          strcpy(tmp_str2552, tmp_str2560);
          strcat(tmp_str2552, " (");
          int tmp_strlen2543 = strlen(tmp_str2552) + strlen(val_b) + 1;
          char* tmp_str2543 = calloc(tmp_strlen2543, sizeof(char));
          strcpy(tmp_str2543, tmp_str2552);
          strcat(tmp_str2543, val_b);
          int tmp_strlen2536 = strlen(tmp_str2543) + strlen(")") + 1;
          char* tmp_str2536 = calloc(tmp_strlen2536, sizeof(char));
          strcpy(tmp_str2536, tmp_str2543);
          strcat(tmp_str2536, ")");
          val = tmp_str2536;
        }
      }
    }
    Peek_results tmp_results2517 = Peek(src);
    op = tmp_results2517.result1;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results2340 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results2340.result1;
  setup = tmp_results2340.result2;
  expr = tmp_results2340.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results2106 = TranslateExpr(src, indent);
  src = tmp_results2106.result1;
  expr_setup = tmp_results2106.result2;
  expr_value = tmp_results2106.result3;
  int tok;
  Peek_results tmp_results2028 = Peek(src);
  tok = tmp_results2028.result1;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results1863 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results1863.result1;
    TranslateExpr_results tmp_results1817 = TranslateExpr(src, indent);
    src = tmp_results1817.result1;
    expr_setup = tmp_results1817.result2;
    expr_value = tmp_results1817.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen1675 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str1675 = calloc(tmp_strlen1675, sizeof(char));
    strcpy(tmp_str1675, exprs_setup);
    strcat(tmp_str1675, expr_setup);
    exprs_setup = tmp_str1675;
    int tmp_strlen1633 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str1633 = calloc(tmp_strlen1633, sizeof(char));
    strcpy(tmp_str1633, exprs_value);
    strcat(tmp_str1633, ", ");
    int tmp_strlen1619 = strlen(tmp_str1633) + strlen(expr_value) + 1;
    char* tmp_str1619 = calloc(tmp_strlen1619, sizeof(char));
    strcpy(tmp_str1619, tmp_str1633);
    strcat(tmp_str1619, expr_value);
    exprs_value = tmp_str1619;
    Peek_results tmp_results1610 = Peek(src);
    tok = tmp_results1610.result1;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
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
      int tmp_strlen1206 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str1206 = calloc(tmp_strlen1206, sizeof(char));
      strncpy(tmp_str1206, haystack + i, tmp_strlen1206 - 1);
      tmp_str1206[tmp_strlen1206 - 1] = 0;
      if ((strcmp(tmp_str1206, needle) != 0)) {
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
      int tmp_strlen871 = (strlen(prefix)) - (0) + 1;
      char* tmp_str871 = calloc(tmp_strlen871, sizeof(char));
      strncpy(tmp_str871, text + 0, tmp_strlen871 - 1);
      tmp_str871[tmp_strlen871 - 1] = 0;
      return (strcmp(tmp_str871, prefix) == 0);
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
      int tmp_strlen628 = (strlen(text)) - ((strlen(text)) - (strlen(suffix))) + 1;
      char* tmp_str628 = calloc(tmp_strlen628, sizeof(char));
      strncpy(tmp_str628, text + (strlen(text)) - (strlen(suffix)), tmp_strlen628 - 1);
      tmp_str628[tmp_strlen628 - 1] = 0;
      return (strcmp(tmp_str628, suffix) == 0);
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
  int tmp_strlen407 = (i) - (0) + 1;
  char* tmp_str407 = calloc(tmp_strlen407, sizeof(char));
  strncpy(tmp_str407, s + 0, tmp_strlen407 - 1);
  tmp_str407[tmp_strlen407 - 1] = 0;
  int tmp_strlen400 = (strlen(s)) - ((i) + (1)) + 1;
  char* tmp_str400 = calloc(tmp_strlen400, sizeof(char));
  strncpy(tmp_str400, s + (i) + (1), tmp_strlen400 - 1);
  tmp_str400[tmp_strlen400 - 1] = 0;
  return (Split_results){tmp_str407, tmp_str400};
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
    int tmp_strlen30 = (strlen(text)) - (1) + 1;
    char* tmp_str30 = calloc(tmp_strlen30, sizeof(char));
    strncpy(tmp_str30, text + 1, tmp_strlen30 - 1);
    tmp_str30[tmp_strlen30 - 1] = 0;
    text = tmp_str30;
  }
  return text;
}


