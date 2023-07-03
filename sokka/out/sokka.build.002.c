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
typedef struct {
  char* result1;
  char* result2;
} ReadSrc_results;
ReadSrc_results ReadSrc(char* src_dir, bool read_tests);
char* TranslateCode(char* src, bool testing);
char* TranslateProgram(char* src);
char* GenerateTestMainFn(char* tests);
char* TranslateTests(char* src, char* tests);
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
  bool result4;
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
char* Escape(char* text);

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen35183 = (strlen(src)) - (2) + 1;
      char* tmp_str35183 = calloc(tmp_strlen35183, sizeof(char));
      strncpy(tmp_str35183, src + 2, tmp_strlen35183 - 1);
      tmp_str35183[tmp_strlen35183 - 1] = 0;
      return (Next_results){tmp_str35183, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen35104 = (strlen(src)) - (2) + 1;
        char* tmp_str35104 = calloc(tmp_strlen35104, sizeof(char));
        strncpy(tmp_str35104, src + 2, tmp_strlen35104 - 1);
        tmp_str35104[tmp_strlen35104 - 1] = 0;
        return (Next_results){tmp_str35104, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen35028 = (strlen(src)) - (2) + 1;
          char* tmp_str35028 = calloc(tmp_strlen35028, sizeof(char));
          strncpy(tmp_str35028, src + 2, tmp_strlen35028 - 1);
          tmp_str35028[tmp_strlen35028 - 1] = 0;
          return (Next_results){tmp_str35028, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen34951 = (strlen(src)) - (2) + 1;
            char* tmp_str34951 = calloc(tmp_strlen34951, sizeof(char));
            strncpy(tmp_str34951, src + 2, tmp_strlen34951 - 1);
            tmp_str34951[tmp_strlen34951 - 1] = 0;
            return (Next_results){tmp_str34951, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen34876 = (strlen(src)) - (2) + 1;
              char* tmp_str34876 = calloc(tmp_strlen34876, sizeof(char));
              strncpy(tmp_str34876, src + 2, tmp_strlen34876 - 1);
              tmp_str34876[tmp_strlen34876 - 1] = 0;
              return (Next_results){tmp_str34876, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen34800 = (strlen(src)) - (2) + 1;
                char* tmp_str34800 = calloc(tmp_strlen34800, sizeof(char));
                strncpy(tmp_str34800, src + 2, tmp_strlen34800 - 1);
                tmp_str34800[tmp_strlen34800 - 1] = 0;
                return (Next_results){tmp_str34800, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen34724 = (strlen(src)) - (2) + 1;
                  char* tmp_str34724 = calloc(tmp_strlen34724, sizeof(char));
                  strncpy(tmp_str34724, src + 2, tmp_strlen34724 - 1);
                  tmp_str34724[tmp_strlen34724 - 1] = 0;
                  return (Next_results){tmp_str34724, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen34648 = (strlen(src)) - (2) + 1;
                    char* tmp_str34648 = calloc(tmp_strlen34648, sizeof(char));
                    strncpy(tmp_str34648, src + 2, tmp_strlen34648 - 1);
                    tmp_str34648[tmp_strlen34648 - 1] = 0;
                    return (Next_results){tmp_str34648, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen34569 = (strlen(src)) - (2) + 1;
                      char* tmp_str34569 = calloc(tmp_strlen34569, sizeof(char));
                      strncpy(tmp_str34569, src + 2, tmp_strlen34569 - 1);
                      tmp_str34569[tmp_strlen34569 - 1] = 0;
                      return (Next_results){tmp_str34569, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen34490 = (strlen(src)) - (3) + 1;
                        char* tmp_str34490 = calloc(tmp_strlen34490, sizeof(char));
                        strncpy(tmp_str34490, src + 3, tmp_strlen34490 - 1);
                        tmp_str34490[tmp_strlen34490 - 1] = 0;
                        return (Next_results){tmp_str34490, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen34410 = (strlen(src)) - (1) + 1;
                          char* tmp_str34410 = calloc(tmp_strlen34410, sizeof(char));
                          strncpy(tmp_str34410, src + 1, tmp_strlen34410 - 1);
                          tmp_str34410[tmp_strlen34410 - 1] = 0;
                          return (Next_results){tmp_str34410, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen34331 = (strlen(src)) - (1) + 1;
                            char* tmp_str34331 = calloc(tmp_strlen34331, sizeof(char));
                            strncpy(tmp_str34331, src + 1, tmp_strlen34331 - 1);
                            tmp_str34331[tmp_strlen34331 - 1] = 0;
                            return (Next_results){tmp_str34331, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen34254 = (strlen(src)) - (1) + 1;
                              char* tmp_str34254 = calloc(tmp_strlen34254, sizeof(char));
                              strncpy(tmp_str34254, src + 1, tmp_strlen34254 - 1);
                              tmp_str34254[tmp_strlen34254 - 1] = 0;
                              return (Next_results){tmp_str34254, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen34177 = (strlen(src)) - (1) + 1;
                                char* tmp_str34177 = calloc(tmp_strlen34177, sizeof(char));
                                strncpy(tmp_str34177, src + 1, tmp_strlen34177 - 1);
                                tmp_str34177[tmp_strlen34177 - 1] = 0;
                                return (Next_results){tmp_str34177, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen34098 = (strlen(src)) - (1) + 1;
                                  char* tmp_str34098 = calloc(tmp_strlen34098, sizeof(char));
                                  strncpy(tmp_str34098, src + 1, tmp_strlen34098 - 1);
                                  tmp_str34098[tmp_strlen34098 - 1] = 0;
                                  return (Next_results){tmp_str34098, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen34019 = (strlen(src)) - (1) + 1;
                                    char* tmp_str34019 = calloc(tmp_strlen34019, sizeof(char));
                                    strncpy(tmp_str34019, src + 1, tmp_strlen34019 - 1);
                                    tmp_str34019[tmp_strlen34019 - 1] = 0;
                                    return (Next_results){tmp_str34019, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen33942 = (strlen(src)) - (1) + 1;
                                      char* tmp_str33942 = calloc(tmp_strlen33942, sizeof(char));
                                      strncpy(tmp_str33942, src + 1, tmp_strlen33942 - 1);
                                      tmp_str33942[tmp_strlen33942 - 1] = 0;
                                      return (Next_results){tmp_str33942, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, "_")) {
                                        int tmp_strlen33865 = (strlen(src)) - (1) + 1;
                                        char* tmp_str33865 = calloc(tmp_strlen33865, sizeof(char));
                                        strncpy(tmp_str33865, src + 1, tmp_strlen33865 - 1);
                                        tmp_str33865[tmp_strlen33865 - 1] = 0;
                                        return (Next_results){tmp_str33865, TOK_UNDERSCORE, "_"};
                                      } else {
                                        if (StartsWith(src, ":")) {
                                          int tmp_strlen33784 = (strlen(src)) - (1) + 1;
                                          char* tmp_str33784 = calloc(tmp_strlen33784, sizeof(char));
                                          strncpy(tmp_str33784, src + 1, tmp_strlen33784 - 1);
                                          tmp_str33784[tmp_strlen33784 - 1] = 0;
                                          return (Next_results){tmp_str33784, TOK_COLON, ":"};
                                        } else {
                                          if (StartsWith(src, ",")) {
                                            int tmp_strlen33708 = (strlen(src)) - (1) + 1;
                                            char* tmp_str33708 = calloc(tmp_strlen33708, sizeof(char));
                                            strncpy(tmp_str33708, src + 1, tmp_strlen33708 - 1);
                                            tmp_str33708[tmp_strlen33708 - 1] = 0;
                                            return (Next_results){tmp_str33708, TOK_COMMA, ","};
                                          } else {
                                            if (StartsWith(src, "=")) {
                                              int tmp_strlen33632 = (strlen(src)) - (1) + 1;
                                              char* tmp_str33632 = calloc(tmp_strlen33632, sizeof(char));
                                              strncpy(tmp_str33632, src + 1, tmp_strlen33632 - 1);
                                              tmp_str33632[tmp_strlen33632 - 1] = 0;
                                              return (Next_results){tmp_str33632, TOK_ASSIGN, "="};
                                            } else {
                                              if (StartsWith(src, "!")) {
                                                int tmp_strlen33555 = (strlen(src)) - (1) + 1;
                                                char* tmp_str33555 = calloc(tmp_strlen33555, sizeof(char));
                                                strncpy(tmp_str33555, src + 1, tmp_strlen33555 - 1);
                                                tmp_str33555[tmp_strlen33555 - 1] = 0;
                                                return (Next_results){tmp_str33555, TOK_BNOT, "!"};
                                              } else {
                                                if (StartsWith(src, "+")) {
                                                  int tmp_strlen33480 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str33480 = calloc(tmp_strlen33480, sizeof(char));
                                                  strncpy(tmp_str33480, src + 1, tmp_strlen33480 - 1);
                                                  tmp_str33480[tmp_strlen33480 - 1] = 0;
                                                  return (Next_results){tmp_str33480, TOK_ADD, "+"};
                                                } else {
                                                  if (StartsWith(src, "-")) {
                                                    int tmp_strlen33406 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str33406 = calloc(tmp_strlen33406, sizeof(char));
                                                    strncpy(tmp_str33406, src + 1, tmp_strlen33406 - 1);
                                                    tmp_str33406[tmp_strlen33406 - 1] = 0;
                                                    return (Next_results){tmp_str33406, TOK_SUB, "-"};
                                                  } else {
                                                    if (StartsWith(src, "*")) {
                                                      int tmp_strlen33332 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str33332 = calloc(tmp_strlen33332, sizeof(char));
                                                      strncpy(tmp_str33332, src + 1, tmp_strlen33332 - 1);
                                                      tmp_str33332[tmp_strlen33332 - 1] = 0;
                                                      return (Next_results){tmp_str33332, TOK_MUL, "*"};
                                                    } else {
                                                      if (StartsWith(src, "/")) {
                                                        int tmp_strlen33258 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str33258 = calloc(tmp_strlen33258, sizeof(char));
                                                        strncpy(tmp_str33258, src + 1, tmp_strlen33258 - 1);
                                                        tmp_str33258[tmp_strlen33258 - 1] = 0;
                                                        return (Next_results){tmp_str33258, TOK_DIV, "/"};
                                                      } else {
                                                        if (StartsWith(src, "%")) {
                                                          int tmp_strlen33184 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str33184 = calloc(tmp_strlen33184, sizeof(char));
                                                          strncpy(tmp_str33184, src + 1, tmp_strlen33184 - 1);
                                                          tmp_str33184[tmp_strlen33184 - 1] = 0;
                                                          return (Next_results){tmp_str33184, TOK_REM, "%"};
                                                        } else {
                                                          if (StartsWith(src, "~")) {
                                                            int tmp_strlen33110 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str33110 = calloc(tmp_strlen33110, sizeof(char));
                                                            strncpy(tmp_str33110, src + 1, tmp_strlen33110 - 1);
                                                            tmp_str33110[tmp_strlen33110 - 1] = 0;
                                                            return (Next_results){tmp_str33110, TOK_INOT, "~"};
                                                          } else {
                                                            if (StartsWith(src, "|")) {
                                                              int tmp_strlen33035 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str33035 = calloc(tmp_strlen33035, sizeof(char));
                                                              strncpy(tmp_str33035, src + 1, tmp_strlen33035 - 1);
                                                              tmp_str33035[tmp_strlen33035 - 1] = 0;
                                                              return (Next_results){tmp_str33035, TOK_IOR, "|"};
                                                            } else {
                                                              if (StartsWith(src, "&")) {
                                                                int tmp_strlen32961 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str32961 = calloc(tmp_strlen32961, sizeof(char));
                                                                strncpy(tmp_str32961, src + 1, tmp_strlen32961 - 1);
                                                                tmp_str32961[tmp_strlen32961 - 1] = 0;
                                                                return (Next_results){tmp_str32961, TOK_IAND, "&"};
                                                              } else {
                                                                if (StartsWith(src, "^")) {
                                                                  int tmp_strlen32886 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str32886 = calloc(tmp_strlen32886, sizeof(char));
                                                                  strncpy(tmp_str32886, src + 1, tmp_strlen32886 - 1);
                                                                  tmp_str32886[tmp_strlen32886 - 1] = 0;
                                                                  return (Next_results){tmp_str32886, TOK_IXOR, "^"};
                                                                } else {
                                                                  if (StartsWith(src, "<")) {
                                                                    int tmp_strlen32811 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str32811 = calloc(tmp_strlen32811, sizeof(char));
                                                                    strncpy(tmp_str32811, src + 1, tmp_strlen32811 - 1);
                                                                    tmp_str32811[tmp_strlen32811 - 1] = 0;
                                                                    return (Next_results){tmp_str32811, TOK_LESS, "<"};
                                                                  } else {
                                                                    if (StartsWith(src, ">")) {
                                                                      int tmp_strlen32736 = (strlen(src)) - (1) + 1;
                                                                      char* tmp_str32736 = calloc(tmp_strlen32736, sizeof(char));
                                                                      strncpy(tmp_str32736, src + 1, tmp_strlen32736 - 1);
                                                                      tmp_str32736[tmp_strlen32736 - 1] = 0;
                                                                      return (Next_results){tmp_str32736, TOK_GREATER, ">"};
                                                                    } else {
                                                                      if (IsAlpha(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        i = (i) - (1);
                                                                        int tmp_strlen32505 = (i) - (0) + 1;
                                                                        char* tmp_str32505 = calloc(tmp_strlen32505, sizeof(char));
                                                                        strncpy(tmp_str32505, src + 0, tmp_strlen32505 - 1);
                                                                        tmp_str32505[tmp_strlen32505 - 1] = 0;
                                                                        char* ts = tmp_str32505;
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
                                                                        int tmp_strlen31713 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str31713 = calloc(tmp_strlen31713, sizeof(char));
                                                                        strncpy(tmp_str31713, src + i, tmp_strlen31713 - 1);
                                                                        tmp_str31713[tmp_strlen31713 - 1] = 0;
                                                                        return (Next_results){tmp_str31713, tt, ts};
                                                                      } else {
                                                                        if (IsNumeric(src[0])) {
                                                                          int i = 1;
                                                                          while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                            i = (i) + (1);
                                                                          }
                                                                          int tmp_strlen31545 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str31545 = calloc(tmp_strlen31545, sizeof(char));
                                                                          strncpy(tmp_str31545, src + i, tmp_strlen31545 - 1);
                                                                          tmp_str31545[tmp_strlen31545 - 1] = 0;
                                                                          int tmp_strlen31524 = (i) - (0) + 1;
                                                                          char* tmp_str31524 = calloc(tmp_strlen31524, sizeof(char));
                                                                          strncpy(tmp_str31524, src + 0, tmp_strlen31524 - 1);
                                                                          tmp_str31524[tmp_strlen31524 - 1] = 0;
                                                                          return (Next_results){tmp_str31545, TOK_INTLIT, tmp_str31524};
                                                                        } else {
                                                                          if (StartsWith(src, "\"")) {
                                                                            int i = 1;
                                                                            while (true) {
                                                                              int tmp_strlen31443 = ((i) + (1)) - (i) + 1;
                                                                              char* tmp_str31443 = calloc(tmp_strlen31443, sizeof(char));
                                                                              strncpy(tmp_str31443, src + i, tmp_strlen31443 - 1);
                                                                              tmp_str31443[tmp_strlen31443 - 1] = 0;
                                                                              if (!((strcmp(tmp_str31443, "\"") != 0))) break;
                                                                              i = (i) + (1);
                                                                              int tmp_strlen31384 = (i) - ((i) - (1)) + 1;
                                                                              char* tmp_str31384 = calloc(tmp_strlen31384, sizeof(char));
                                                                              strncpy(tmp_str31384, src + (i) - (1), tmp_strlen31384 - 1);
                                                                              tmp_str31384[tmp_strlen31384 - 1] = 0;
                                                                              if ((strcmp(tmp_str31384, "\\") == 0)) {
                                                                                i = (i) + (1);
                                                                              }
                                                                            }
                                                                            i = (i) + (1);
                                                                            int tmp_strlen31280 = (strlen(src)) - (i) + 1;
                                                                            char* tmp_str31280 = calloc(tmp_strlen31280, sizeof(char));
                                                                            strncpy(tmp_str31280, src + i, tmp_strlen31280 - 1);
                                                                            tmp_str31280[tmp_strlen31280 - 1] = 0;
                                                                            int tmp_strlen31259 = (i) - (0) + 1;
                                                                            char* tmp_str31259 = calloc(tmp_strlen31259, sizeof(char));
                                                                            strncpy(tmp_str31259, src + 0, tmp_strlen31259 - 1);
                                                                            tmp_str31259[tmp_strlen31259 - 1] = 0;
                                                                            return (Next_results){tmp_str31280, TOK_STRLIT, tmp_str31259};
                                                                          } else {
                                                                            int tmp_strlen31194 = (1) - (0) + 1;
                                                                            char* tmp_str31194 = calloc(tmp_strlen31194, sizeof(char));
                                                                            strncpy(tmp_str31194, src + 0, tmp_strlen31194 - 1);
                                                                            tmp_str31194[tmp_strlen31194 - 1] = 0;
                                                                            int tmp_strlen31190 = strlen("unexpected token start: ") + strlen(tmp_str31194) + 1;
                                                                            char* tmp_str31190 = calloc(tmp_strlen31190, sizeof(char));
                                                                            strcpy(tmp_str31190, "unexpected token start: ");
                                                                            strcat(tmp_str31190, tmp_str31194);
                                                                            printf("%s", tmp_str31190);
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
  Next_results tmp_results31078 = Next(src);
  tok = tmp_results31078.result2;
  tok_str = tmp_results31078.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results30894 = Next(src);
  src = tmp_results30894.result1;
  actual_tok = tmp_results30894.result2;
  actual_tok_str = tmp_results30894.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen30760 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str30760 = calloc(tmp_strlen30760, sizeof(char));
    strcpy(tmp_str30760, "expected token: ");
    strcat(tmp_str30760, itoa(expected_tok));
    int tmp_strlen30733 = strlen(tmp_str30760) + strlen(" got: ") + 1;
    char* tmp_str30733 = calloc(tmp_strlen30733, sizeof(char));
    strcpy(tmp_str30733, tmp_str30760);
    strcat(tmp_str30733, " got: ");
    int tmp_strlen30713 = strlen(tmp_str30733) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str30713 = calloc(tmp_strlen30713, sizeof(char));
    strcpy(tmp_str30713, tmp_str30733);
    strcat(tmp_str30713, itoa(actual_tok));
    int tmp_strlen30704 = strlen(tmp_str30713) + strlen(" \"") + 1;
    char* tmp_str30704 = calloc(tmp_strlen30704, sizeof(char));
    strcpy(tmp_str30704, tmp_str30713);
    strcat(tmp_str30704, " \"");
    int tmp_strlen30686 = strlen(tmp_str30704) + strlen(actual_tok_str) + 1;
    char* tmp_str30686 = calloc(tmp_strlen30686, sizeof(char));
    strcpy(tmp_str30686, tmp_str30704);
    strcat(tmp_str30686, actual_tok_str);
    int tmp_strlen30678 = strlen(tmp_str30686) + strlen("\"") + 1;
    char* tmp_str30678 = calloc(tmp_strlen30678, sizeof(char));
    strcpy(tmp_str30678, tmp_str30686);
    strcat(tmp_str30678, "\"");
    printf("%s", tmp_str30678);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results30510 = Next(src);
  src = tmp_results30510.result1;
  actual_tok = tmp_results30510.result2;
  actual_tok_str = tmp_results30510.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen30376 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str30376 = calloc(tmp_strlen30376, sizeof(char));
    strcpy(tmp_str30376, "expected ident, got: ");
    strcat(tmp_str30376, itoa(actual_tok));
    int tmp_strlen30367 = strlen(tmp_str30376) + strlen(" \"") + 1;
    char* tmp_str30367 = calloc(tmp_strlen30367, sizeof(char));
    strcpy(tmp_str30367, tmp_str30376);
    strcat(tmp_str30367, " \"");
    int tmp_strlen30349 = strlen(tmp_str30367) + strlen(actual_tok_str) + 1;
    char* tmp_str30349 = calloc(tmp_strlen30349, sizeof(char));
    strcpy(tmp_str30349, tmp_str30367);
    strcat(tmp_str30349, actual_tok_str);
    int tmp_strlen30341 = strlen(tmp_str30349) + strlen("\"") + 1;
    char* tmp_str30341 = calloc(tmp_strlen30341, sizeof(char));
    strcpy(tmp_str30341, tmp_str30349);
    strcat(tmp_str30341, "\"");
    printf("%s", tmp_str30341);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results30161 = Next(src);
  src = tmp_results30161.result1;
  actual_tok = tmp_results30161.result2;
  actual_tok_str = tmp_results30161.result3;
  if (((actual_tok) != (TOK_UNDERSCORE)) && ((actual_tok) != (TOK_IDENT))) {
    int tmp_strlen29981 = strlen("expected ident or underscore, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str29981 = calloc(tmp_strlen29981, sizeof(char));
    strcpy(tmp_str29981, "expected ident or underscore, got: ");
    strcat(tmp_str29981, itoa(actual_tok));
    int tmp_strlen29972 = strlen(tmp_str29981) + strlen(" \"") + 1;
    char* tmp_str29972 = calloc(tmp_strlen29972, sizeof(char));
    strcpy(tmp_str29972, tmp_str29981);
    strcat(tmp_str29972, " \"");
    int tmp_strlen29954 = strlen(tmp_str29972) + strlen(actual_tok_str) + 1;
    char* tmp_str29954 = calloc(tmp_strlen29954, sizeof(char));
    strcpy(tmp_str29954, tmp_str29972);
    strcat(tmp_str29954, actual_tok_str);
    int tmp_strlen29946 = strlen(tmp_str29954) + strlen("\"") + 1;
    char* tmp_str29946 = calloc(tmp_strlen29946, sizeof(char));
    strcpy(tmp_str29946, tmp_str29954);
    strcat(tmp_str29946, "\"");
    printf("%s", tmp_str29946);
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
                  int tmp_strlen27009 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str27009 = calloc(tmp_strlen27009, sizeof(char));
                  strcpy(tmp_str27009, "token has no defined precedence: ");
                  strcat(tmp_str27009, itoa(tok));
                  printf("%s", tmp_str27009);
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
  Next_results tmp_results26800 = Next(src);
  src = tmp_results26800.result1;
  tok = tmp_results26800.result2;
  tok_str = tmp_results26800.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen26503 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str26503 = calloc(tmp_strlen26503, sizeof(char));
        strcpy(tmp_str26503, "expected type, got: ");
        strcat(tmp_str26503, itoa(tok));
        int tmp_strlen26494 = strlen(tmp_str26503) + strlen(" \"") + 1;
        char* tmp_str26494 = calloc(tmp_strlen26494, sizeof(char));
        strcpy(tmp_str26494, tmp_str26503);
        strcat(tmp_str26494, " \"");
        int tmp_strlen26483 = strlen(tmp_str26494) + strlen(tok_str) + 1;
        char* tmp_str26483 = calloc(tmp_strlen26483, sizeof(char));
        strcpy(tmp_str26483, tmp_str26494);
        strcat(tmp_str26483, tok_str);
        int tmp_strlen26475 = strlen(tmp_str26483) + strlen("\"") + 1;
        char* tmp_str26475 = calloc(tmp_strlen26475, sizeof(char));
        strcpy(tmp_str26475, tmp_str26483);
        strcat(tmp_str26475, "\"");
        printf("%s", tmp_str26475);
        exit(1);
      }
    }
  }
}

ReadSrc_results ReadSrc(char* src_dir, bool read_tests) {
  char* src = "";
  char* tests = "";
  char* src_files = direntries(src_dir);
  char* src_file;
  Split_results tmp_results26251 = Split(src_files);
  src_file = tmp_results26251.result1;
  src_files = tmp_results26251.result2;
  while (((strlen(src_files)) > (0)) || ((strlen(src_file)) > (0))) {
    if (EndsWith(src_file, "_test.sk")) {
      if (read_tests) {
        int tmp_strlen26038 = strlen(src_dir) + strlen("/") + 1;
        char* tmp_str26038 = calloc(tmp_strlen26038, sizeof(char));
        strcpy(tmp_str26038, src_dir);
        strcat(tmp_str26038, "/");
        int tmp_strlen26026 = strlen(tmp_str26038) + strlen(src_file) + 1;
        char* tmp_str26026 = calloc(tmp_strlen26026, sizeof(char));
        strcpy(tmp_str26026, tmp_str26038);
        strcat(tmp_str26026, src_file);
        int tmp_strlen26025 = strlen(tests) + strlen(read(tmp_str26026)) + 1;
        char* tmp_str26025 = calloc(tmp_strlen26025, sizeof(char));
        strcpy(tmp_str26025, tests);
        strcat(tmp_str26025, read(tmp_str26026));
        int tmp_strlen26017 = strlen(tmp_str26025) + strlen("\n") + 1;
        char* tmp_str26017 = calloc(tmp_strlen26017, sizeof(char));
        strcpy(tmp_str26017, tmp_str26025);
        strcat(tmp_str26017, "\n");
        tests = tmp_str26017;
      }
    } else {
      if (EndsWith(src_file, ".sk")) {
        int tmp_strlen25912 = strlen(src_dir) + strlen("/") + 1;
        char* tmp_str25912 = calloc(tmp_strlen25912, sizeof(char));
        strcpy(tmp_str25912, src_dir);
        strcat(tmp_str25912, "/");
        int tmp_strlen25900 = strlen(tmp_str25912) + strlen(src_file) + 1;
        char* tmp_str25900 = calloc(tmp_strlen25900, sizeof(char));
        strcpy(tmp_str25900, tmp_str25912);
        strcat(tmp_str25900, src_file);
        int tmp_strlen25899 = strlen(src) + strlen(read(tmp_str25900)) + 1;
        char* tmp_str25899 = calloc(tmp_strlen25899, sizeof(char));
        strcpy(tmp_str25899, src);
        strcat(tmp_str25899, read(tmp_str25900));
        int tmp_strlen25891 = strlen(tmp_str25899) + strlen("\n") + 1;
        char* tmp_str25891 = calloc(tmp_strlen25891, sizeof(char));
        strcpy(tmp_str25891, tmp_str25899);
        strcat(tmp_str25891, "\n");
        src = tmp_str25891;
      }
    }
    Split_results tmp_results25872 = Split(src_files);
    src_file = tmp_results25872.result1;
    src_files = tmp_results25872.result2;
  }
  return (ReadSrc_results){src, tests};
}

char* TranslateCode(char* src, bool testing) {
  char* out = "";
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results25591 = Peek(src);
  tok = tmp_results25591.result1;
  tok_str = tmp_results25591.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results25497 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results25497.result1;
      Peek_results tmp_results25445 = Peek(src);
      tok = tmp_results25445.result1;
      tok_str = tmp_results25445.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results25317 = TranslateConstDecl(src, "");
        src = tmp_results25317.result1;
        const_decl = tmp_results25317.result2;
        int tmp_strlen25224 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str25224 = calloc(tmp_strlen25224, sizeof(char));
        strcpy(tmp_str25224, constants);
        strcat(tmp_str25224, const_decl);
        constants = tmp_str25224;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          bool is_main;
          TranslateFunc_results tmp_results25084 = TranslateFunc(src);
          src = tmp_results25084.result1;
          fn_decl = tmp_results25084.result2;
          fn_def = tmp_results25084.result3;
          is_main = tmp_results25084.result4;
          if ((testing) && (is_main)) {
            Peek_results tmp_results24981 = Peek(src);
            tok = tmp_results24981.result1;
            tok_str = tmp_results24981.result2;
            continue;
          }
          if ((is_main) == (false)) {
            int tmp_strlen24843 = strlen(decls) + strlen(fn_decl) + 1;
            char* tmp_str24843 = calloc(tmp_strlen24843, sizeof(char));
            strcpy(tmp_str24843, decls);
            strcat(tmp_str24843, fn_decl);
            decls = tmp_str24843;
          }
          int tmp_strlen24795 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str24795 = calloc(tmp_strlen24795, sizeof(char));
          strcpy(tmp_str24795, defs);
          strcat(tmp_str24795, fn_def);
          defs = tmp_str24795;
        } else {
          int tmp_strlen24716 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str24716 = calloc(tmp_strlen24716, sizeof(char));
          strcpy(tmp_str24716, "unexpected decl token, got: ");
          strcat(tmp_str24716, itoa(tok));
          int tmp_strlen24707 = strlen(tmp_str24716) + strlen(" \"") + 1;
          char* tmp_str24707 = calloc(tmp_strlen24707, sizeof(char));
          strcpy(tmp_str24707, tmp_str24716);
          strcat(tmp_str24707, " \"");
          int tmp_strlen24696 = strlen(tmp_str24707) + strlen(tok_str) + 1;
          char* tmp_str24696 = calloc(tmp_strlen24696, sizeof(char));
          strcpy(tmp_str24696, tmp_str24707);
          strcat(tmp_str24696, tok_str);
          int tmp_strlen24688 = strlen(tmp_str24696) + strlen("\"") + 1;
          char* tmp_str24688 = calloc(tmp_strlen24688, sizeof(char));
          strcpy(tmp_str24688, tmp_str24696);
          strcat(tmp_str24688, "\"");
          printf("%s", tmp_str24688);
          exit(1);
        }
      }
    }
    Peek_results tmp_results24648 = Peek(src);
    tok = tmp_results24648.result1;
    tok_str = tmp_results24648.result2;
  }
  ConsumeToken_results tmp_results24613 = ConsumeToken(src, TOK_EOF);
  src = tmp_results24613.result1;
  if ((strcmp(constants, "") != 0)) {
    int tmp_strlen24521 = strlen(out) + strlen(constants) + 1;
    char* tmp_str24521 = calloc(tmp_strlen24521, sizeof(char));
    strcpy(tmp_str24521, out);
    strcat(tmp_str24521, constants);
    int tmp_strlen24513 = strlen(tmp_str24521) + strlen("\n") + 1;
    char* tmp_str24513 = calloc(tmp_strlen24513, sizeof(char));
    strcpy(tmp_str24513, tmp_str24521);
    strcat(tmp_str24513, "\n");
    out = tmp_str24513;
  }
  if ((strcmp(decls, "") != 0)) {
    int tmp_strlen24458 = strlen(out) + strlen(decls) + 1;
    char* tmp_str24458 = calloc(tmp_strlen24458, sizeof(char));
    strcpy(tmp_str24458, out);
    strcat(tmp_str24458, decls);
    int tmp_strlen24450 = strlen(tmp_str24458) + strlen("\n") + 1;
    char* tmp_str24450 = calloc(tmp_strlen24450, sizeof(char));
    strcpy(tmp_str24450, tmp_str24458);
    strcat(tmp_str24450, "\n");
    out = tmp_str24450;
  }
  if ((strcmp(defs, "") != 0)) {
    int tmp_strlen24397 = strlen(out) + strlen(defs) + 1;
    char* tmp_str24397 = calloc(tmp_strlen24397, sizeof(char));
    strcpy(tmp_str24397, out);
    strcat(tmp_str24397, defs);
    int tmp_strlen24389 = strlen(tmp_str24397) + strlen("\n") + 1;
    char* tmp_str24389 = calloc(tmp_strlen24389, sizeof(char));
    strcpy(tmp_str24389, tmp_str24397);
    strcat(tmp_str24389, "\n");
    out = tmp_str24389;
  }
  return out;
}

char* TranslateProgram(char* src) {
  char* c_lib = read("clib/lib.c");
  char* src_out = TranslateCode(src, false);
  int tmp_strlen24197 = strlen(c_lib) + strlen(src_out) + 1;
  char* tmp_str24197 = calloc(tmp_strlen24197, sizeof(char));
  strcpy(tmp_str24197, c_lib);
  strcat(tmp_str24197, src_out);
  return tmp_str24197;
}

char* GenerateTestMainFn(char* tests) {
  int i = 0;
  int j = Find(tests, "\n");
  char* main = "fn main(args: string) {\n";
  int tmp_strlen24007 = strlen(main) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str24007 = calloc(tmp_strlen24007, sizeof(char));
  strcpy(tmp_str24007, main);
  strcat(tmp_str24007, SINGLE_INDENT);
  int tmp_strlen23975 = strlen(tmp_str24007) + strlen("var success: bool = true\n") + 1;
  char* tmp_str23975 = calloc(tmp_strlen23975, sizeof(char));
  strcpy(tmp_str23975, tmp_str24007);
  strcat(tmp_str23975, "var success: bool = true\n");
  main = tmp_str23975;
  while ((j) != (-(1))) {
    int tmp_strlen23924 = (j) - (i) + 1;
    char* tmp_str23924 = calloc(tmp_strlen23924, sizeof(char));
    strncpy(tmp_str23924, tests + i, tmp_strlen23924 - 1);
    tmp_str23924[tmp_strlen23924 - 1] = 0;
    char* line = tmp_str23924;
    if (StartsWith(line, "fn test")) {
      int k = Find(line, "(");
      int tmp_strlen23801 = (k) - (3) + 1;
      char* tmp_str23801 = calloc(tmp_strlen23801, sizeof(char));
      strncpy(tmp_str23801, line + 3, tmp_strlen23801 - 1);
      tmp_str23801[tmp_strlen23801 - 1] = 0;
      char* name = tmp_str23801;
      int tmp_strlen23755 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23755 = calloc(tmp_strlen23755, sizeof(char));
      strcpy(tmp_str23755, main);
      strcat(tmp_str23755, SINGLE_INDENT);
      int tmp_strlen23746 = strlen(tmp_str23755) + strlen("if ") + 1;
      char* tmp_str23746 = calloc(tmp_strlen23746, sizeof(char));
      strcpy(tmp_str23746, tmp_str23755);
      strcat(tmp_str23746, "if ");
      int tmp_strlen23738 = strlen(tmp_str23746) + strlen(name) + 1;
      char* tmp_str23738 = calloc(tmp_strlen23738, sizeof(char));
      strcpy(tmp_str23738, tmp_str23746);
      strcat(tmp_str23738, name);
      int tmp_strlen23717 = strlen(tmp_str23738) + strlen("() == false {\n") + 1;
      char* tmp_str23717 = calloc(tmp_strlen23717, sizeof(char));
      strcpy(tmp_str23717, tmp_str23738);
      strcat(tmp_str23717, "() == false {\n");
      main = tmp_str23717;
      int tmp_strlen23676 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23676 = calloc(tmp_strlen23676, sizeof(char));
      strcpy(tmp_str23676, main);
      strcat(tmp_str23676, SINGLE_INDENT);
      int tmp_strlen23659 = strlen(tmp_str23676) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23659 = calloc(tmp_strlen23659, sizeof(char));
      strcpy(tmp_str23659, tmp_str23676);
      strcat(tmp_str23659, SINGLE_INDENT);
      int tmp_strlen23636 = strlen(tmp_str23659) + strlen("success = false\n") + 1;
      char* tmp_str23636 = calloc(tmp_strlen23636, sizeof(char));
      strcpy(tmp_str23636, tmp_str23659);
      strcat(tmp_str23636, "success = false\n");
      main = tmp_str23636;
      int tmp_strlen23595 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23595 = calloc(tmp_strlen23595, sizeof(char));
      strcpy(tmp_str23595, main);
      strcat(tmp_str23595, SINGLE_INDENT);
      int tmp_strlen23578 = strlen(tmp_str23595) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23578 = calloc(tmp_strlen23578, sizeof(char));
      strcpy(tmp_str23578, tmp_str23595);
      strcat(tmp_str23578, SINGLE_INDENT);
      int tmp_strlen23557 = strlen(tmp_str23578) + strlen("print(\"[Fail] ") + 1;
      char* tmp_str23557 = calloc(tmp_strlen23557, sizeof(char));
      strcpy(tmp_str23557, tmp_str23578);
      strcat(tmp_str23557, "print(\"[Fail] ");
      int tmp_strlen23549 = strlen(tmp_str23557) + strlen(name) + 1;
      char* tmp_str23549 = calloc(tmp_strlen23549, sizeof(char));
      strcpy(tmp_str23549, tmp_str23557);
      strcat(tmp_str23549, name);
      int tmp_strlen23535 = strlen(tmp_str23549) + strlen("\\n\")\n") + 1;
      char* tmp_str23535 = calloc(tmp_strlen23535, sizeof(char));
      strcpy(tmp_str23535, tmp_str23549);
      strcat(tmp_str23535, "\\n\")\n");
      main = tmp_str23535;
      int tmp_strlen23494 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23494 = calloc(tmp_strlen23494, sizeof(char));
      strcpy(tmp_str23494, main);
      strcat(tmp_str23494, SINGLE_INDENT);
      int tmp_strlen23478 = strlen(tmp_str23494) + strlen("} else {\n") + 1;
      char* tmp_str23478 = calloc(tmp_strlen23478, sizeof(char));
      strcpy(tmp_str23478, tmp_str23494);
      strcat(tmp_str23478, "} else {\n");
      main = tmp_str23478;
      int tmp_strlen23437 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23437 = calloc(tmp_strlen23437, sizeof(char));
      strcpy(tmp_str23437, main);
      strcat(tmp_str23437, SINGLE_INDENT);
      int tmp_strlen23420 = strlen(tmp_str23437) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23420 = calloc(tmp_strlen23420, sizeof(char));
      strcpy(tmp_str23420, tmp_str23437);
      strcat(tmp_str23420, SINGLE_INDENT);
      int tmp_strlen23399 = strlen(tmp_str23420) + strlen("print(\"[ Ok ] ") + 1;
      char* tmp_str23399 = calloc(tmp_strlen23399, sizeof(char));
      strcpy(tmp_str23399, tmp_str23420);
      strcat(tmp_str23399, "print(\"[ Ok ] ");
      int tmp_strlen23391 = strlen(tmp_str23399) + strlen(name) + 1;
      char* tmp_str23391 = calloc(tmp_strlen23391, sizeof(char));
      strcpy(tmp_str23391, tmp_str23399);
      strcat(tmp_str23391, name);
      int tmp_strlen23377 = strlen(tmp_str23391) + strlen("\\n\")\n") + 1;
      char* tmp_str23377 = calloc(tmp_strlen23377, sizeof(char));
      strcpy(tmp_str23377, tmp_str23391);
      strcat(tmp_str23377, "\\n\")\n");
      main = tmp_str23377;
      int tmp_strlen23336 = strlen(main) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str23336 = calloc(tmp_strlen23336, sizeof(char));
      strcpy(tmp_str23336, main);
      strcat(tmp_str23336, SINGLE_INDENT);
      int tmp_strlen23327 = strlen(tmp_str23336) + strlen("}\n") + 1;
      char* tmp_str23327 = calloc(tmp_strlen23327, sizeof(char));
      strcpy(tmp_str23327, tmp_str23336);
      strcat(tmp_str23327, "}\n");
      main = tmp_str23327;
    }
    i = (j) + (1);
    int tmp_strlen23276 = (strlen(tests)) - (i) + 1;
    char* tmp_str23276 = calloc(tmp_strlen23276, sizeof(char));
    strncpy(tmp_str23276, tests + i, tmp_strlen23276 - 1);
    tmp_str23276[tmp_strlen23276 - 1] = 0;
    j = Find(tmp_str23276, "\n");
    if ((j) != (-(1))) {
      j = (i) + (j);
    }
  }
  int tmp_strlen23173 = strlen(main) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str23173 = calloc(tmp_strlen23173, sizeof(char));
  strcpy(tmp_str23173, main);
  strcat(tmp_str23173, SINGLE_INDENT);
  int tmp_strlen23144 = strlen(tmp_str23173) + strlen("if success == false {\n") + 1;
  char* tmp_str23144 = calloc(tmp_strlen23144, sizeof(char));
  strcpy(tmp_str23144, tmp_str23173);
  strcat(tmp_str23144, "if success == false {\n");
  main = tmp_str23144;
  int tmp_strlen23111 = strlen(main) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str23111 = calloc(tmp_strlen23111, sizeof(char));
  strcpy(tmp_str23111, main);
  strcat(tmp_str23111, SINGLE_INDENT);
  int tmp_strlen23094 = strlen(tmp_str23111) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str23094 = calloc(tmp_strlen23094, sizeof(char));
  strcpy(tmp_str23094, tmp_str23111);
  strcat(tmp_str23094, SINGLE_INDENT);
  int tmp_strlen23079 = strlen(tmp_str23094) + strlen("exit(1)\n") + 1;
  char* tmp_str23079 = calloc(tmp_strlen23079, sizeof(char));
  strcpy(tmp_str23079, tmp_str23094);
  strcat(tmp_str23079, "exit(1)\n");
  main = tmp_str23079;
  int tmp_strlen23046 = strlen(main) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str23046 = calloc(tmp_strlen23046, sizeof(char));
  strcpy(tmp_str23046, main);
  strcat(tmp_str23046, SINGLE_INDENT);
  int tmp_strlen23037 = strlen(tmp_str23046) + strlen("}\n") + 1;
  char* tmp_str23037 = calloc(tmp_strlen23037, sizeof(char));
  strcpy(tmp_str23037, tmp_str23046);
  strcat(tmp_str23037, "}\n");
  main = tmp_str23037;
  int tmp_strlen23012 = strlen(main) + strlen("}\n") + 1;
  char* tmp_str23012 = calloc(tmp_strlen23012, sizeof(char));
  strcpy(tmp_str23012, main);
  strcat(tmp_str23012, "}\n");
  main = tmp_str23012;
  int tmp_strlen22984 = strlen("main:\n") + strlen(main) + 1;
  char* tmp_str22984 = calloc(tmp_strlen22984, sizeof(char));
  strcpy(tmp_str22984, "main:\n");
  strcat(tmp_str22984, main);
  int tmp_strlen22973 = strlen(tmp_str22984) + strlen("---\n") + 1;
  char* tmp_str22973 = calloc(tmp_strlen22973, sizeof(char));
  strcpy(tmp_str22973, tmp_str22984);
  strcat(tmp_str22973, "---\n");
  printf("%s", tmp_str22973);
  return main;
}

char* TranslateTests(char* src, char* tests) {
  char* c_lib = read("clib/lib.c");
  char* src_out = TranslateCode(src, true);
  char* testing_lib;
  ReadSrc_results tmp_results22768 = ReadSrc("sklib/testing", false);
  testing_lib = tmp_results22768.result1;
  int tmp_strlen22657 = strlen(testing_lib) + strlen(tests) + 1;
  char* tmp_str22657 = calloc(tmp_strlen22657, sizeof(char));
  strcpy(tmp_str22657, testing_lib);
  strcat(tmp_str22657, tests);
  char* tests_out = TranslateCode(tmp_str22657, true);
  char* main = GenerateTestMainFn(tests);
  char* main_out = TranslateCode(main, false);
  int tmp_strlen22519 = strlen(c_lib) + strlen(src_out) + 1;
  char* tmp_str22519 = calloc(tmp_strlen22519, sizeof(char));
  strcpy(tmp_str22519, c_lib);
  strcat(tmp_str22519, src_out);
  int tmp_strlen22506 = strlen(tmp_str22519) + strlen(tests_out) + 1;
  char* tmp_str22506 = calloc(tmp_strlen22506, sizeof(char));
  strcpy(tmp_str22506, tmp_str22519);
  strcat(tmp_str22506, tests_out);
  int tmp_strlen22494 = strlen(tmp_str22506) + strlen(main_out) + 1;
  char* tmp_str22494 = calloc(tmp_strlen22494, sizeof(char));
  strcpy(tmp_str22494, tmp_str22506);
  strcat(tmp_str22494, main_out);
  return tmp_str22494;
}

int _main(char* args) {
  int i = Find(args, " ");
  int tmp_strlen22406 = (i) - (0) + 1;
  char* tmp_str22406 = calloc(tmp_strlen22406, sizeof(char));
  strncpy(tmp_str22406, args + 0, tmp_strlen22406 - 1);
  tmp_str22406[tmp_strlen22406 - 1] = 0;
  char* verb = tmp_str22406;
  bool test;
  if ((strcmp(verb, "build") == 0)) {
    test = false;
  } else {
    if ((strcmp(verb, "test") == 0)) {
      test = true;
    } else {
      printf("%s", "expected verb (build or test)\n");
      exit(1);
    }
  }
  int tmp_strlen22186 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str22186 = calloc(tmp_strlen22186, sizeof(char));
  strncpy(tmp_str22186, args + (i) + (1), tmp_strlen22186 - 1);
  tmp_str22186[tmp_strlen22186 - 1] = 0;
  args = tmp_str22186;
  i = Find(args, " ");
  int tmp_strlen22125 = (i) - (0) + 1;
  char* tmp_str22125 = calloc(tmp_strlen22125, sizeof(char));
  strncpy(tmp_str22125, args + 0, tmp_strlen22125 - 1);
  tmp_str22125[tmp_strlen22125 - 1] = 0;
  char* src_dir = tmp_str22125;
  char* src;
  char* tests;
  ReadSrc_results tmp_results22074 = ReadSrc(src_dir, test);
  src = tmp_results22074.result1;
  tests = tmp_results22074.result2;
  char* out;
  if ((test) == (false)) {
    out = TranslateProgram(src);
  } else {
    out = TranslateTests(src, tests);
  }
  int tmp_strlen21868 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str21868 = calloc(tmp_strlen21868, sizeof(char));
  strncpy(tmp_str21868, args + (i) + (1), tmp_strlen21868 - 1);
  tmp_str21868[tmp_strlen21868 - 1] = 0;
  char* out_file = tmp_str21868;
  write(out_file, out);
  return 0;
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  ConsumeToken_results tmp_results21756 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results21756.result1;
  Peek_results tmp_results21713 = Peek(src);
  tok = tmp_results21713.result1;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results21659 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results21659.result1;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results21564 = TranslateConstOrVar(src);
  src = tmp_results21564.result1;
  args = tmp_results21564.result2;
  Peek_results tmp_results21523 = Peek(src);
  tok = tmp_results21523.result1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results21469 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results21469.result1;
    char* arg;
    TranslateConstOrVar_results tmp_results21399 = TranslateConstOrVar(src);
    src = tmp_results21399.result1;
    arg = tmp_results21399.result2;
    int tmp_strlen21336 = strlen(args) + strlen(", ") + 1;
    char* tmp_str21336 = calloc(tmp_strlen21336, sizeof(char));
    strcpy(tmp_str21336, args);
    strcat(tmp_str21336, ", ");
    int tmp_strlen21329 = strlen(tmp_str21336) + strlen(arg) + 1;
    char* tmp_str21329 = calloc(tmp_strlen21329, sizeof(char));
    strcpy(tmp_str21329, tmp_str21336);
    strcat(tmp_str21329, arg);
    args = tmp_str21329;
    Peek_results tmp_results21320 = Peek(src);
    tok = tmp_results21320.result1;
  }
  ConsumeToken_results tmp_results21291 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results21291.result1;
  int tmp_strlen21225 = strlen("(") + strlen(args) + 1;
  char* tmp_str21225 = calloc(tmp_strlen21225, sizeof(char));
  strcpy(tmp_str21225, "(");
  strcat(tmp_str21225, args);
  int tmp_strlen21218 = strlen(tmp_str21225) + strlen(")") + 1;
  char* tmp_str21218 = calloc(tmp_strlen21218, sizeof(char));
  strcpy(tmp_str21218, tmp_str21225);
  strcat(tmp_str21218, ")");
  return (TranslateFuncArgs_results){src, tmp_str21218};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  Peek_results tmp_results21066 = Peek(src);
  tok = tmp_results21066.result1;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results21012 = TranslateType(src);
    src = tmp_results21012.result1;
    typ = tmp_results21012.result2;
    typ_str = tmp_results21012.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results20931 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results20931.result1;
  TranslateType_results tmp_results20888 = TranslateType(src);
  src = tmp_results20888.result1;
  typ = tmp_results20888.result2;
  typ_str = tmp_results20888.result3;
  Peek_results tmp_results20845 = Peek(src);
  tok = tmp_results20845.result1;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results20792 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results20792.result1;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen20657 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str20657 = calloc(tmp_strlen20657, sizeof(char));
  strcpy(tmp_str20657, "typedef struct {\n");
  strcat(tmp_str20657, SINGLE_INDENT);
  int tmp_strlen20646 = strlen(tmp_str20657) + strlen(typ_str) + 1;
  char* tmp_str20646 = calloc(tmp_strlen20646, sizeof(char));
  strcpy(tmp_str20646, tmp_str20657);
  strcat(tmp_str20646, typ_str);
  int tmp_strlen20629 = strlen(tmp_str20646) + strlen(" result1;\n") + 1;
  char* tmp_str20629 = calloc(tmp_strlen20629, sizeof(char));
  strcpy(tmp_str20629, tmp_str20646);
  strcat(tmp_str20629, " result1;\n");
  char* td = tmp_str20629;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results20566 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results20566.result1;
    TranslateType_results tmp_results20520 = TranslateType(src);
    src = tmp_results20520.result1;
    typ = tmp_results20520.result2;
    typ_str = tmp_results20520.result3;
    res_count = (res_count) + (1);
    int tmp_strlen20415 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str20415 = calloc(tmp_strlen20415, sizeof(char));
    strcpy(tmp_str20415, td);
    strcat(tmp_str20415, SINGLE_INDENT);
    int tmp_strlen20404 = strlen(tmp_str20415) + strlen(typ_str) + 1;
    char* tmp_str20404 = calloc(tmp_strlen20404, sizeof(char));
    strcpy(tmp_str20404, tmp_str20415);
    strcat(tmp_str20404, typ_str);
    int tmp_strlen20391 = strlen(tmp_str20404) + strlen(" result") + 1;
    char* tmp_str20391 = calloc(tmp_strlen20391, sizeof(char));
    strcpy(tmp_str20391, tmp_str20404);
    strcat(tmp_str20391, " result");
    int tmp_strlen20372 = strlen(tmp_str20391) + strlen(itoa(res_count)) + 1;
    char* tmp_str20372 = calloc(tmp_strlen20372, sizeof(char));
    strcpy(tmp_str20372, tmp_str20391);
    strcat(tmp_str20372, itoa(res_count));
    int tmp_strlen20363 = strlen(tmp_str20372) + strlen(";\n") + 1;
    char* tmp_str20363 = calloc(tmp_strlen20363, sizeof(char));
    strcpy(tmp_str20363, tmp_str20372);
    strcat(tmp_str20363, ";\n");
    td = tmp_str20363;
    Peek_results tmp_results20354 = Peek(src);
    tok = tmp_results20354.result1;
  }
  ConsumeToken_results tmp_results20325 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results20325.result1;
  int tmp_strlen20267 = strlen(td) + strlen("} ") + 1;
  char* tmp_str20267 = calloc(tmp_strlen20267, sizeof(char));
  strcpy(tmp_str20267, td);
  strcat(tmp_str20267, "} ");
  int tmp_strlen20254 = strlen(tmp_str20267) + strlen(func_name) + 1;
  char* tmp_str20254 = calloc(tmp_strlen20254, sizeof(char));
  strcpy(tmp_str20254, tmp_str20267);
  strcat(tmp_str20254, func_name);
  int tmp_strlen20237 = strlen(tmp_str20254) + strlen("_results;\n") + 1;
  char* tmp_str20237 = calloc(tmp_strlen20237, sizeof(char));
  strcpy(tmp_str20237, tmp_str20254);
  strcat(tmp_str20237, "_results;\n");
  td = tmp_str20237;
  int tmp_strlen20193 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str20193 = calloc(tmp_strlen20193, sizeof(char));
  strcpy(tmp_str20193, func_name);
  strcat(tmp_str20193, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str20193};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* name;
  ConsumeToken_results tmp_results20081 = ConsumeToken(src, TOK_FN);
  src = tmp_results20081.result1;
  ConsumeIdent_results tmp_results20042 = ConsumeIdent(src);
  src = tmp_results20042.result1;
  name = tmp_results20042.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  bool is_main = false;
  bool is_test = false;
  if ((strcmp(name, "main") == 0)) {
    is_main = true;
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  } else {
    if (StartsWith(name, "test")) {
      is_test = true;
      results_type_name = "bool";
    }
  }
  Peek_results tmp_results19600 = Peek(src);
  tok = tmp_results19600.result1;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results19546 = TranslateFuncArgs(src);
    src = tmp_results19546.result1;
    args = tmp_results19546.result2;
    Peek_results tmp_results19503 = Peek(src);
    tok = tmp_results19503.result1;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results19441 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results19441.result1;
      TranslateFuncResults_results tmp_results19390 = TranslateFuncResults(src, name);
      src = tmp_results19390.result1;
      results_type_def = tmp_results19390.result2;
      results_type_name = tmp_results19390.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results19269 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results19269.result1;
  int tmp_strlen19170 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str19170 = calloc(tmp_strlen19170, sizeof(char));
  strcpy(tmp_str19170, SINGLE_INDENT);
  strcat(tmp_str19170, "");
  TranslateStmts_results tmp_results19226 = TranslateStmts(src, tmp_str19170, name);
  src = tmp_results19226.result1;
  stmts_out = tmp_results19226.result2;
  ConsumeToken_results tmp_results19158 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results19158.result1;
  int tmp_strlen19074 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str19074 = calloc(tmp_strlen19074, sizeof(char));
  strcpy(tmp_str19074, results_type_name);
  strcat(tmp_str19074, " ");
  int tmp_strlen19066 = strlen(tmp_str19074) + strlen(name) + 1;
  char* tmp_str19066 = calloc(tmp_strlen19066, sizeof(char));
  strcpy(tmp_str19066, tmp_str19074);
  strcat(tmp_str19066, name);
  int tmp_strlen19058 = strlen(tmp_str19066) + strlen(args) + 1;
  char* tmp_str19058 = calloc(tmp_strlen19058, sizeof(char));
  strcpy(tmp_str19058, tmp_str19066);
  strcat(tmp_str19058, args);
  char* df = tmp_str19058;
  int tmp_strlen19012 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str19012 = calloc(tmp_strlen19012, sizeof(char));
  strcpy(tmp_str19012, results_type_def);
  strcat(tmp_str19012, df);
  int tmp_strlen19003 = strlen(tmp_str19012) + strlen(";\n") + 1;
  char* tmp_str19003 = calloc(tmp_strlen19003, sizeof(char));
  strcpy(tmp_str19003, tmp_str19012);
  strcat(tmp_str19003, ";\n");
  char* decl = tmp_str19003;
  int tmp_strlen18981 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str18981 = calloc(tmp_strlen18981, sizeof(char));
  strcpy(tmp_str18981, df);
  strcat(tmp_str18981, " {\n");
  df = tmp_str18981;
  if (is_test) {
    int tmp_strlen18931 = strlen(df) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str18931 = calloc(tmp_strlen18931, sizeof(char));
    strcpy(tmp_str18931, df);
    strcat(tmp_str18931, SINGLE_INDENT);
    int tmp_strlen18902 = strlen(tmp_str18931) + strlen("bool _success = true;\n") + 1;
    char* tmp_str18902 = calloc(tmp_strlen18902, sizeof(char));
    strcpy(tmp_str18902, tmp_str18931);
    strcat(tmp_str18902, "bool _success = true;\n");
    df = tmp_str18902;
  }
  int tmp_strlen18871 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str18871 = calloc(tmp_strlen18871, sizeof(char));
  strcpy(tmp_str18871, df);
  strcat(tmp_str18871, stmts_out);
  df = tmp_str18871;
  if (is_main) {
    int tmp_strlen18821 = strlen(df) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str18821 = calloc(tmp_strlen18821, sizeof(char));
    strcpy(tmp_str18821, df);
    strcat(tmp_str18821, SINGLE_INDENT);
    int tmp_strlen18804 = strlen(tmp_str18821) + strlen("return 0;\n") + 1;
    char* tmp_str18804 = calloc(tmp_strlen18804, sizeof(char));
    strcpy(tmp_str18804, tmp_str18821);
    strcat(tmp_str18804, "return 0;\n");
    df = tmp_str18804;
  } else {
    if (is_test) {
      int tmp_strlen18747 = strlen(df) + strlen(SINGLE_INDENT) + 1;
      char* tmp_str18747 = calloc(tmp_strlen18747, sizeof(char));
      strcpy(tmp_str18747, df);
      strcat(tmp_str18747, SINGLE_INDENT);
      int tmp_strlen18723 = strlen(tmp_str18747) + strlen("return _success;\n") + 1;
      char* tmp_str18723 = calloc(tmp_strlen18723, sizeof(char));
      strcpy(tmp_str18723, tmp_str18747);
      strcat(tmp_str18723, "return _success;\n");
      df = tmp_str18723;
    }
  }
  int tmp_strlen18694 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str18694 = calloc(tmp_strlen18694, sizeof(char));
  strcpy(tmp_str18694, df);
  strcat(tmp_str18694, "}\n\n");
  df = tmp_str18694;
  return (TranslateFunc_results){src, decl, df, is_main};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results18573 = ConsumeIdent(src);
  src = tmp_results18573.result1;
  name = tmp_results18573.result2;
  ConsumeToken_results tmp_results18539 = ConsumeToken(src, TOK_COLON);
  src = tmp_results18539.result1;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results18456 = TranslateType(src);
  src = tmp_results18456.result1;
  typ = tmp_results18456.result2;
  typ_str = tmp_results18456.result3;
  int tmp_strlen18381 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str18381 = calloc(tmp_strlen18381, sizeof(char));
  strcpy(tmp_str18381, typ_str);
  strcat(tmp_str18381, " ");
  int tmp_strlen18373 = strlen(tmp_str18381) + strlen(name) + 1;
  char* tmp_str18373 = calloc(tmp_strlen18373, sizeof(char));
  strcpy(tmp_str18373, tmp_str18381);
  strcat(tmp_str18373, name);
  char* out = tmp_str18373;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  ConsumeToken_results tmp_results18272 = ConsumeToken(src, TOK_LET);
  src = tmp_results18272.result1;
  char* out;
  TranslateConstOrVar_results tmp_results18212 = TranslateConstOrVar(src);
  src = tmp_results18212.result1;
  out = tmp_results18212.result2;
  int tmp_strlen18151 = strlen("const ") + strlen(out) + 1;
  char* tmp_str18151 = calloc(tmp_strlen18151, sizeof(char));
  strcpy(tmp_str18151, "const ");
  strcat(tmp_str18151, out);
  out = tmp_str18151;
  ConsumeToken_results tmp_results18146 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results18146.result1;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results18061 = TranslateExpr(src, indent);
  src = tmp_results18061.result1;
  setup = tmp_results18061.result2;
  val = tmp_results18061.result3;
  ConsumeToken_results tmp_results18012 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results18012.result1;
  int tmp_strlen17950 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str17950 = calloc(tmp_strlen17950, sizeof(char));
  strcpy(tmp_str17950, out);
  strcat(tmp_str17950, " = ");
  int tmp_strlen17943 = strlen(tmp_str17950) + strlen(val) + 1;
  char* tmp_str17943 = calloc(tmp_strlen17943, sizeof(char));
  strcpy(tmp_str17943, tmp_str17950);
  strcat(tmp_str17943, val);
  int tmp_strlen17934 = strlen(tmp_str17943) + strlen(";\n") + 1;
  char* tmp_str17934 = calloc(tmp_strlen17934, sizeof(char));
  strcpy(tmp_str17934, tmp_str17943);
  strcat(tmp_str17934, ";\n");
  out = tmp_str17934;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results17809 = TranslateConstDecl(src, indent);
  src = tmp_results17809.result1;
  out = tmp_results17809.result2;
  int tmp_strlen17737 = strlen(indent) + strlen(out) + 1;
  char* tmp_str17737 = calloc(tmp_strlen17737, sizeof(char));
  strcpy(tmp_str17737, indent);
  strcat(tmp_str17737, out);
  return (TranslateConstDeclStmt_results){src, tmp_str17737};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  ConsumeToken_results tmp_results17637 = ConsumeToken(src, TOK_VAR);
  src = tmp_results17637.result1;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results17530 = TranslateConstOrVar(src);
  src = tmp_results17530.result1;
  out = tmp_results17530.result2;
  Peek_results tmp_results17490 = Peek(src);
  tok = tmp_results17490.result1;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results17436 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results17436.result1;
    TranslateExpr_results tmp_results17389 = TranslateExpr(src, indent);
    src = tmp_results17389.result1;
    setup = tmp_results17389.result2;
    val = tmp_results17389.result3;
    ConsumeToken_results tmp_results17336 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results17336.result1;
    int tmp_strlen17270 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str17270 = calloc(tmp_strlen17270, sizeof(char));
    strcpy(tmp_str17270, out);
    strcat(tmp_str17270, " = ");
    int tmp_strlen17263 = strlen(tmp_str17270) + strlen(val) + 1;
    char* tmp_str17263 = calloc(tmp_strlen17263, sizeof(char));
    strcpy(tmp_str17263, tmp_str17270);
    strcat(tmp_str17263, val);
    out = tmp_str17263;
  }
  int tmp_strlen17231 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str17231 = calloc(tmp_strlen17231, sizeof(char));
  strcpy(tmp_str17231, setup);
  strcat(tmp_str17231, indent);
  int tmp_strlen17224 = strlen(tmp_str17231) + strlen(out) + 1;
  char* tmp_str17224 = calloc(tmp_strlen17224, sizeof(char));
  strcpy(tmp_str17224, tmp_str17231);
  strcat(tmp_str17224, out);
  int tmp_strlen17215 = strlen(tmp_str17224) + strlen(";\n") + 1;
  char* tmp_str17215 = calloc(tmp_strlen17215, sizeof(char));
  strcpy(tmp_str17215, tmp_str17224);
  strcat(tmp_str17215, ";\n");
  out = tmp_str17215;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen17060 = (x) - (0) + 1;
  char* tmp_str17060 = calloc(tmp_strlen17060, sizeof(char));
  strncpy(tmp_str17060, src + 0, tmp_strlen17060 - 1);
  tmp_str17060[tmp_strlen17060 - 1] = 0;
  char* lhs = tmp_str17060;
  int tmp_strlen17030 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str17030 = calloc(tmp_strlen17030, sizeof(char));
  strncpy(tmp_str17030, src + (x) + (1), tmp_strlen17030 - 1);
  tmp_str17030[tmp_strlen17030 - 1] = 0;
  char* rhs = tmp_str17030;
  char* lhs_ident;
  ConsumeIdentOrUnderscore_results tmp_results16993 = ConsumeIdentOrUnderscore(lhs);
  lhs = tmp_results16993.result1;
  lhs_ident = tmp_results16993.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results16865 = TranslateExpr(rhs, indent);
  rhs = tmp_results16865.result1;
  setup = tmp_results16865.result2;
  rhs_expr = tmp_results16865.result3;
  int lhs_tok;
  int rhs_tok;
  Peek_results tmp_results16769 = Peek(lhs);
  lhs_tok = tmp_results16769.result1;
  Peek_results tmp_results16742 = Peek(rhs);
  rhs_tok = tmp_results16742.result1;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results16627 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results16627.result1;
    func_name = tmp_results16627.result2;
    int tmp_strlen16519 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str16519 = calloc(tmp_strlen16519, sizeof(char));
    strcpy(tmp_str16519, "tmp_results");
    strcat(tmp_str16519, itoa(strlen(src)));
    char* tmp_results = tmp_str16519;
    char* out = setup;
    int tmp_strlen16459 = strlen(out) + strlen(indent) + 1;
    char* tmp_str16459 = calloc(tmp_strlen16459, sizeof(char));
    strcpy(tmp_str16459, out);
    strcat(tmp_str16459, indent);
    int tmp_strlen16446 = strlen(tmp_str16459) + strlen(func_name) + 1;
    char* tmp_str16446 = calloc(tmp_strlen16446, sizeof(char));
    strcpy(tmp_str16446, tmp_str16459);
    strcat(tmp_str16446, func_name);
    int tmp_strlen16431 = strlen(tmp_str16446) + strlen("_results ") + 1;
    char* tmp_str16431 = calloc(tmp_strlen16431, sizeof(char));
    strcpy(tmp_str16431, tmp_str16446);
    strcat(tmp_str16431, "_results ");
    int tmp_strlen16416 = strlen(tmp_str16431) + strlen(tmp_results) + 1;
    char* tmp_str16416 = calloc(tmp_strlen16416, sizeof(char));
    strcpy(tmp_str16416, tmp_str16431);
    strcat(tmp_str16416, tmp_results);
    int tmp_strlen16407 = strlen(tmp_str16416) + strlen(" = ") + 1;
    char* tmp_str16407 = calloc(tmp_strlen16407, sizeof(char));
    strcpy(tmp_str16407, tmp_str16416);
    strcat(tmp_str16407, " = ");
    int tmp_strlen16395 = strlen(tmp_str16407) + strlen(rhs_expr) + 1;
    char* tmp_str16395 = calloc(tmp_strlen16395, sizeof(char));
    strcpy(tmp_str16395, tmp_str16407);
    strcat(tmp_str16395, rhs_expr);
    int tmp_strlen16386 = strlen(tmp_str16395) + strlen(";\n") + 1;
    char* tmp_str16386 = calloc(tmp_strlen16386, sizeof(char));
    strcpy(tmp_str16386, tmp_str16395);
    strcat(tmp_str16386, ";\n");
    out = tmp_str16386;
    if ((strcmp(lhs_ident, "_") != 0)) {
      int tmp_strlen16323 = strlen(out) + strlen(indent) + 1;
      char* tmp_str16323 = calloc(tmp_strlen16323, sizeof(char));
      strcpy(tmp_str16323, out);
      strcat(tmp_str16323, indent);
      int tmp_strlen16310 = strlen(tmp_str16323) + strlen(lhs_ident) + 1;
      char* tmp_str16310 = calloc(tmp_strlen16310, sizeof(char));
      strcpy(tmp_str16310, tmp_str16323);
      strcat(tmp_str16310, lhs_ident);
      int tmp_strlen16301 = strlen(tmp_str16310) + strlen(" = ") + 1;
      char* tmp_str16301 = calloc(tmp_strlen16301, sizeof(char));
      strcpy(tmp_str16301, tmp_str16310);
      strcat(tmp_str16301, " = ");
      int tmp_strlen16286 = strlen(tmp_str16301) + strlen(tmp_results) + 1;
      char* tmp_str16286 = calloc(tmp_strlen16286, sizeof(char));
      strcpy(tmp_str16286, tmp_str16301);
      strcat(tmp_str16286, tmp_results);
      int tmp_strlen16269 = strlen(tmp_str16286) + strlen(".result1;\n") + 1;
      char* tmp_str16269 = calloc(tmp_strlen16269, sizeof(char));
      strcpy(tmp_str16269, tmp_str16286);
      strcat(tmp_str16269, ".result1;\n");
      out = tmp_str16269;
    }
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results16133 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results16133.result1;
      ConsumeIdentOrUnderscore_results tmp_results16083 = ConsumeIdentOrUnderscore(lhs);
      lhs = tmp_results16083.result1;
      lhs_ident = tmp_results16083.result2;
      if ((strcmp(lhs_ident, "_") != 0)) {
        int tmp_strlen15966 = strlen(out) + strlen(indent) + 1;
        char* tmp_str15966 = calloc(tmp_strlen15966, sizeof(char));
        strcpy(tmp_str15966, out);
        strcat(tmp_str15966, indent);
        int tmp_strlen15953 = strlen(tmp_str15966) + strlen(lhs_ident) + 1;
        char* tmp_str15953 = calloc(tmp_strlen15953, sizeof(char));
        strcpy(tmp_str15953, tmp_str15966);
        strcat(tmp_str15953, lhs_ident);
        int tmp_strlen15944 = strlen(tmp_str15953) + strlen(" = ") + 1;
        char* tmp_str15944 = calloc(tmp_strlen15944, sizeof(char));
        strcpy(tmp_str15944, tmp_str15953);
        strcat(tmp_str15944, " = ");
        int tmp_strlen15929 = strlen(tmp_str15944) + strlen(tmp_results) + 1;
        char* tmp_str15929 = calloc(tmp_strlen15929, sizeof(char));
        strcpy(tmp_str15929, tmp_str15944);
        strcat(tmp_str15929, tmp_results);
        int tmp_strlen15916 = strlen(tmp_str15929) + strlen(".result") + 1;
        char* tmp_str15916 = calloc(tmp_strlen15916, sizeof(char));
        strcpy(tmp_str15916, tmp_str15929);
        strcat(tmp_str15916, ".result");
        int tmp_strlen15894 = strlen(tmp_str15916) + strlen(itoa(result_count)) + 1;
        char* tmp_str15894 = calloc(tmp_strlen15894, sizeof(char));
        strcpy(tmp_str15894, tmp_str15916);
        strcat(tmp_str15894, itoa(result_count));
        int tmp_strlen15885 = strlen(tmp_str15894) + strlen(";\n") + 1;
        char* tmp_str15885 = calloc(tmp_strlen15885, sizeof(char));
        strcpy(tmp_str15885, tmp_str15894);
        strcat(tmp_str15885, ";\n");
        out = tmp_str15885;
      }
      Peek_results tmp_results15858 = Peek(lhs);
      lhs_tok = tmp_results15858.result1;
    }
    ConsumeToken_results tmp_results15817 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results15817.result1;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen15698 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str15698 = calloc(tmp_strlen15698, sizeof(char));
  strcpy(tmp_str15698, indent);
  strcat(tmp_str15698, lhs_ident);
  int tmp_strlen15689 = strlen(tmp_str15698) + strlen(" = ") + 1;
  char* tmp_str15689 = calloc(tmp_strlen15689, sizeof(char));
  strcpy(tmp_str15689, tmp_str15698);
  strcat(tmp_str15689, " = ");
  int tmp_strlen15677 = strlen(tmp_str15689) + strlen(rhs_expr) + 1;
  char* tmp_str15677 = calloc(tmp_strlen15677, sizeof(char));
  strcpy(tmp_str15677, tmp_str15689);
  strcat(tmp_str15677, rhs_expr);
  int tmp_strlen15668 = strlen(tmp_str15677) + strlen(";\n") + 1;
  char* tmp_str15668 = calloc(tmp_strlen15668, sizeof(char));
  strcpy(tmp_str15668, tmp_str15677);
  strcat(tmp_str15668, ";\n");
  char* assignments = tmp_str15668;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results15628 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results15628.result1;
    ConsumeToken_results tmp_results15582 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results15582.result1;
    ConsumeIdent_results tmp_results15536 = ConsumeIdent(lhs);
    lhs = tmp_results15536.result1;
    lhs_ident = tmp_results15536.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results15458 = TranslateExpr(rhs, indent);
    rhs = tmp_results15458.result1;
    rhs_expr_setup = tmp_results15458.result2;
    rhs_expr = tmp_results15458.result3;
    int tmp_strlen15360 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str15360 = calloc(tmp_strlen15360, sizeof(char));
    strcpy(tmp_str15360, setup);
    strcat(tmp_str15360, rhs_expr_setup);
    setup = tmp_str15360;
    int tmp_strlen15316 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str15316 = calloc(tmp_strlen15316, sizeof(char));
    strcpy(tmp_str15316, assignments);
    strcat(tmp_str15316, indent);
    int tmp_strlen15303 = strlen(tmp_str15316) + strlen(lhs_ident) + 1;
    char* tmp_str15303 = calloc(tmp_strlen15303, sizeof(char));
    strcpy(tmp_str15303, tmp_str15316);
    strcat(tmp_str15303, lhs_ident);
    int tmp_strlen15294 = strlen(tmp_str15303) + strlen(" = ") + 1;
    char* tmp_str15294 = calloc(tmp_strlen15294, sizeof(char));
    strcpy(tmp_str15294, tmp_str15303);
    strcat(tmp_str15294, " = ");
    int tmp_strlen15282 = strlen(tmp_str15294) + strlen(rhs_expr) + 1;
    char* tmp_str15282 = calloc(tmp_strlen15282, sizeof(char));
    strcpy(tmp_str15282, tmp_str15294);
    strcat(tmp_str15282, rhs_expr);
    int tmp_strlen15273 = strlen(tmp_str15282) + strlen(";\n") + 1;
    char* tmp_str15273 = calloc(tmp_strlen15273, sizeof(char));
    strcpy(tmp_str15273, tmp_str15282);
    strcat(tmp_str15273, ";\n");
    assignments = tmp_str15273;
    Peek_results tmp_results15264 = Peek(lhs);
    lhs_tok = tmp_results15264.result1;
  }
  ConsumeToken_results tmp_results15231 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results15231.result1;
  int tmp_strlen15155 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str15155 = calloc(tmp_strlen15155, sizeof(char));
  strcpy(tmp_str15155, setup);
  strcat(tmp_str15155, assignments);
  return (TranslateAssignStmt_results){src, tmp_str15155};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results15058 = ConsumeToken(src, TOK_IF);
  src = tmp_results15058.result1;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results14971 = TranslateExpr(src, indent);
  src = tmp_results14971.result1;
  cond_setup = tmp_results14971.result2;
  cond = tmp_results14971.result3;
  ConsumeToken_results tmp_results14916 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results14916.result1;
  char* out = cond_setup;
  int tmp_strlen14821 = strlen(out) + strlen(indent) + 1;
  char* tmp_str14821 = calloc(tmp_strlen14821, sizeof(char));
  strcpy(tmp_str14821, out);
  strcat(tmp_str14821, indent);
  int tmp_strlen14811 = strlen(tmp_str14821) + strlen("if (") + 1;
  char* tmp_str14811 = calloc(tmp_strlen14811, sizeof(char));
  strcpy(tmp_str14811, tmp_str14821);
  strcat(tmp_str14811, "if (");
  int tmp_strlen14803 = strlen(tmp_str14811) + strlen(cond) + 1;
  char* tmp_str14803 = calloc(tmp_strlen14803, sizeof(char));
  strcpy(tmp_str14803, tmp_str14811);
  strcat(tmp_str14803, cond);
  int tmp_strlen14792 = strlen(tmp_str14803) + strlen(") {\n") + 1;
  char* tmp_str14792 = calloc(tmp_strlen14792, sizeof(char));
  strcpy(tmp_str14792, tmp_str14803);
  strcat(tmp_str14792, ") {\n");
  out = tmp_str14792;
  char* body;
  int tmp_strlen14711 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str14711 = calloc(tmp_strlen14711, sizeof(char));
  strcpy(tmp_str14711, indent);
  strcat(tmp_str14711, SINGLE_INDENT);
  TranslateStmts_results tmp_results14766 = TranslateStmts(src, tmp_str14711, func_name);
  src = tmp_results14766.result1;
  body = tmp_results14766.result2;
  ConsumeToken_results tmp_results14694 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results14694.result1;
  int tmp_strlen14634 = strlen(out) + strlen(body) + 1;
  char* tmp_str14634 = calloc(tmp_strlen14634, sizeof(char));
  strcpy(tmp_str14634, out);
  strcat(tmp_str14634, body);
  out = tmp_str14634;
  int tmp_strlen14610 = strlen(out) + strlen(indent) + 1;
  char* tmp_str14610 = calloc(tmp_strlen14610, sizeof(char));
  strcpy(tmp_str14610, out);
  strcat(tmp_str14610, indent);
  int tmp_strlen14603 = strlen(tmp_str14610) + strlen("}") + 1;
  char* tmp_str14603 = calloc(tmp_strlen14603, sizeof(char));
  strcpy(tmp_str14603, tmp_str14610);
  strcat(tmp_str14603, "}");
  out = tmp_str14603;
  int tok;
  Peek_results tmp_results14581 = Peek(src);
  tok = tmp_results14581.result1;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen14506 = strlen(out) + strlen("\n") + 1;
    char* tmp_str14506 = calloc(tmp_strlen14506, sizeof(char));
    strcpy(tmp_str14506, out);
    strcat(tmp_str14506, "\n");
    return (TranslateIfStmt_results){src, tmp_str14506};
  }
  ConsumeToken_results tmp_results14495 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results14495.result1;
  Peek_results tmp_results14454 = Peek(src);
  tok = tmp_results14454.result1;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen14319 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str14319 = calloc(tmp_strlen14319, sizeof(char));
    strcpy(tmp_str14319, indent);
    strcat(tmp_str14319, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results14379 = TranslateIfStmt(src, tmp_str14319, func_name);
    src = tmp_results14379.result1;
    else_out = tmp_results14379.result2;
    int tmp_strlen14274 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str14274 = calloc(tmp_strlen14274, sizeof(char));
    strcpy(tmp_str14274, out);
    strcat(tmp_str14274, " else {\n");
    out = tmp_str14274;
    int tmp_strlen14244 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str14244 = calloc(tmp_strlen14244, sizeof(char));
    strcpy(tmp_str14244, out);
    strcat(tmp_str14244, else_out);
    out = tmp_str14244;
    int tmp_strlen14216 = strlen(out) + strlen(indent) + 1;
    char* tmp_str14216 = calloc(tmp_strlen14216, sizeof(char));
    strcpy(tmp_str14216, out);
    strcat(tmp_str14216, indent);
    int tmp_strlen14207 = strlen(tmp_str14216) + strlen("}\n") + 1;
    char* tmp_str14207 = calloc(tmp_strlen14207, sizeof(char));
    strcpy(tmp_str14207, tmp_str14216);
    strcat(tmp_str14207, "}\n");
    out = tmp_str14207;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results14172 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results14172.result1;
  int tmp_strlen14070 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str14070 = calloc(tmp_strlen14070, sizeof(char));
  strcpy(tmp_str14070, indent);
  strcat(tmp_str14070, SINGLE_INDENT);
  TranslateStmts_results tmp_results14129 = TranslateStmts(src, tmp_str14070, func_name);
  src = tmp_results14129.result1;
  else_out = tmp_results14129.result2;
  ConsumeToken_results tmp_results14053 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results14053.result1;
  int tmp_strlen13986 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str13986 = calloc(tmp_strlen13986, sizeof(char));
  strcpy(tmp_str13986, out);
  strcat(tmp_str13986, " else {\n");
  out = tmp_str13986;
  int tmp_strlen13960 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str13960 = calloc(tmp_strlen13960, sizeof(char));
  strcpy(tmp_str13960, out);
  strcat(tmp_str13960, else_out);
  out = tmp_str13960;
  int tmp_strlen13936 = strlen(out) + strlen(indent) + 1;
  char* tmp_str13936 = calloc(tmp_strlen13936, sizeof(char));
  strcpy(tmp_str13936, out);
  strcat(tmp_str13936, indent);
  int tmp_strlen13927 = strlen(tmp_str13936) + strlen("}\n") + 1;
  char* tmp_str13927 = calloc(tmp_strlen13927, sizeof(char));
  strcpy(tmp_str13927, tmp_str13936);
  strcat(tmp_str13927, "}\n");
  out = tmp_str13927;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  ConsumeToken_results tmp_results13792 = ConsumeToken(src, TOK_FOR);
  src = tmp_results13792.result1;
  Peek_results tmp_results13752 = Peek(src);
  tok = tmp_results13752.result1;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen13570 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str13570 = calloc(tmp_strlen13570, sizeof(char));
    strcpy(tmp_str13570, indent);
    strcat(tmp_str13570, SINGLE_INDENT);
    TranslateExpr_results tmp_results13636 = TranslateExpr(src, tmp_str13570);
    src = tmp_results13636.result1;
    cond_setup = tmp_results13636.result2;
    cond = tmp_results13636.result3;
  }
  ConsumeToken_results tmp_results13558 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results13558.result1;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen13440 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str13440 = calloc(tmp_strlen13440, sizeof(char));
    strcpy(tmp_str13440, indent);
    strcat(tmp_str13440, "while (");
    int tmp_strlen13432 = strlen(tmp_str13440) + strlen(cond) + 1;
    char* tmp_str13432 = calloc(tmp_strlen13432, sizeof(char));
    strcpy(tmp_str13432, tmp_str13440);
    strcat(tmp_str13432, cond);
    int tmp_strlen13421 = strlen(tmp_str13432) + strlen(") {\n") + 1;
    char* tmp_str13421 = calloc(tmp_strlen13421, sizeof(char));
    strcpy(tmp_str13421, tmp_str13432);
    strcat(tmp_str13421, ") {\n");
    out = tmp_str13421;
  } else {
    int tmp_strlen13365 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str13365 = calloc(tmp_strlen13365, sizeof(char));
    strcpy(tmp_str13365, indent);
    strcat(tmp_str13365, "while (true) {\n");
    out = tmp_str13365;
    int tmp_strlen13333 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str13333 = calloc(tmp_strlen13333, sizeof(char));
    strcpy(tmp_str13333, out);
    strcat(tmp_str13333, cond_setup);
    out = tmp_str13333;
    int tmp_strlen13305 = strlen(out) + strlen(indent) + 1;
    char* tmp_str13305 = calloc(tmp_strlen13305, sizeof(char));
    strcpy(tmp_str13305, out);
    strcat(tmp_str13305, indent);
    int tmp_strlen13288 = strlen(tmp_str13305) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str13288 = calloc(tmp_strlen13288, sizeof(char));
    strcpy(tmp_str13288, tmp_str13305);
    strcat(tmp_str13288, SINGLE_INDENT);
    int tmp_strlen13276 = strlen(tmp_str13288) + strlen("if (!(") + 1;
    char* tmp_str13276 = calloc(tmp_strlen13276, sizeof(char));
    strcpy(tmp_str13276, tmp_str13288);
    strcat(tmp_str13276, "if (!(");
    int tmp_strlen13268 = strlen(tmp_str13276) + strlen(cond) + 1;
    char* tmp_str13268 = calloc(tmp_strlen13268, sizeof(char));
    strcpy(tmp_str13268, tmp_str13276);
    strcat(tmp_str13268, cond);
    int tmp_strlen13251 = strlen(tmp_str13268) + strlen(")) break;\n") + 1;
    char* tmp_str13251 = calloc(tmp_strlen13251, sizeof(char));
    strcpy(tmp_str13251, tmp_str13268);
    strcat(tmp_str13251, ")) break;\n");
    out = tmp_str13251;
  }
  char* body;
  int tmp_strlen13164 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str13164 = calloc(tmp_strlen13164, sizeof(char));
  strcpy(tmp_str13164, indent);
  strcat(tmp_str13164, SINGLE_INDENT);
  TranslateStmts_results tmp_results13219 = TranslateStmts(src, tmp_str13164, func_name);
  src = tmp_results13219.result1;
  body = tmp_results13219.result2;
  ConsumeToken_results tmp_results13147 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results13147.result1;
  int tmp_strlen13087 = strlen(out) + strlen(body) + 1;
  char* tmp_str13087 = calloc(tmp_strlen13087, sizeof(char));
  strcpy(tmp_str13087, out);
  strcat(tmp_str13087, body);
  out = tmp_str13087;
  int tmp_strlen13063 = strlen(out) + strlen(indent) + 1;
  char* tmp_str13063 = calloc(tmp_strlen13063, sizeof(char));
  strcpy(tmp_str13063, out);
  strcat(tmp_str13063, indent);
  int tmp_strlen13054 = strlen(tmp_str13063) + strlen("}\n") + 1;
  char* tmp_str13054 = calloc(tmp_strlen13054, sizeof(char));
  strcpy(tmp_str13054, tmp_str13063);
  strcat(tmp_str13054, "}\n");
  out = tmp_str13054;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results12950 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results12950.result1;
  int tmp_strlen12872 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str12872 = calloc(tmp_strlen12872, sizeof(char));
  strcpy(tmp_str12872, indent);
  strcat(tmp_str12872, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str12872};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results12791 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results12791.result1;
  int tmp_strlen12719 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str12719 = calloc(tmp_strlen12719, sizeof(char));
  strcpy(tmp_str12719, indent);
  strcat(tmp_str12719, "break;");
  return (TranslateBreakStmt_results){src, tmp_str12719};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results12618 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results12618.result1;
  int tok;
  Peek_results tmp_results12558 = Peek(src);
  tok = tmp_results12558.result1;
  if ((tok) == (TOK_NEWLINE)) {
    ConsumeToken_results tmp_results12503 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results12503.result1;
    int tmp_strlen12422 = strlen(indent) + strlen("return;\n") + 1;
    char* tmp_str12422 = calloc(tmp_strlen12422, sizeof(char));
    strcpy(tmp_str12422, indent);
    strcat(tmp_str12422, "return;\n");
    return (TranslateReturnStmt_results){src, tmp_str12422};
  }
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results12331 = TranslateExprs(src, indent);
  src = tmp_results12331.result1;
  expr_count = tmp_results12331.result2;
  exprs_setup = tmp_results12331.result3;
  exprs_value = tmp_results12331.result4;
  ConsumeToken_results tmp_results12255 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results12255.result1;
  int tmp_strlen12172 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str12172 = calloc(tmp_strlen12172, sizeof(char));
  strcpy(tmp_str12172, exprs_setup);
  strcat(tmp_str12172, indent);
  int tmp_strlen12159 = strlen(tmp_str12172) + strlen("return ") + 1;
  char* tmp_str12159 = calloc(tmp_strlen12159, sizeof(char));
  strcpy(tmp_str12159, tmp_str12172);
  strcat(tmp_str12159, "return ");
  char* out = tmp_str12159;
  if ((expr_count) > (1)) {
    int tmp_strlen12110 = strlen(out) + strlen("(") + 1;
    char* tmp_str12110 = calloc(tmp_strlen12110, sizeof(char));
    strcpy(tmp_str12110, out);
    strcat(tmp_str12110, "(");
    int tmp_strlen12097 = strlen(tmp_str12110) + strlen(func_name) + 1;
    char* tmp_str12097 = calloc(tmp_strlen12097, sizeof(char));
    strcpy(tmp_str12097, tmp_str12110);
    strcat(tmp_str12097, func_name);
    int tmp_strlen12081 = strlen(tmp_str12097) + strlen("_results){") + 1;
    char* tmp_str12081 = calloc(tmp_strlen12081, sizeof(char));
    strcpy(tmp_str12081, tmp_str12097);
    strcat(tmp_str12081, "_results){");
    out = tmp_str12081;
  }
  int tmp_strlen12046 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str12046 = calloc(tmp_strlen12046, sizeof(char));
  strcpy(tmp_str12046, out);
  strcat(tmp_str12046, exprs_value);
  out = tmp_str12046;
  if ((expr_count) > (1)) {
    int tmp_strlen11996 = strlen(out) + strlen("}") + 1;
    char* tmp_str11996 = calloc(tmp_strlen11996, sizeof(char));
    strcpy(tmp_str11996, out);
    strcat(tmp_str11996, "}");
    out = tmp_str11996;
  }
  int tmp_strlen11967 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str11967 = calloc(tmp_strlen11967, sizeof(char));
  strcpy(tmp_str11967, out);
  strcat(tmp_str11967, ";\n");
  out = tmp_str11967;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results11811 = Peek(src);
  tok = tmp_results11811.result1;
  tok_str = tmp_results11811.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results11734 = TranslateConstDeclStmt(src, indent);
    src = tmp_results11734.result1;
    out = tmp_results11734.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results11624 = TranslateVarDeclStmt(src, indent);
      src = tmp_results11624.result1;
      out = tmp_results11624.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results11517 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results11517.result1;
        out = tmp_results11517.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results11403 = TranslateForStmt(src, indent, func_name);
          src = tmp_results11403.result1;
          out = tmp_results11403.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results11283 = TranslateContinueStmt(src, indent);
            src = tmp_results11283.result1;
            out = tmp_results11283.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results11172 = TranslateBreakStmt(src, indent);
              src = tmp_results11172.result1;
              out = tmp_results11172.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results11063 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results11063.result1;
                out = tmp_results11063.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if (((tok) == (TOK_IDENT)) || ((tok) == (TOK_UNDERSCORE))) {
                  char* first_ident;
                  ConsumeIdentOrUnderscore_results tmp_results10886 = ConsumeIdentOrUnderscore(src);
                  src = tmp_results10886.result1;
                  first_ident = tmp_results10886.result2;
                  Peek_results tmp_results10829 = Peek(src);
                  tok = tmp_results10829.result1;
                  int tmp_strlen10778 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str10778 = calloc(tmp_strlen10778, sizeof(char));
                  strcpy(tmp_str10778, first_ident);
                  strcat(tmp_str10778, src);
                  src = tmp_str10778;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results10714 = TranslateAssignStmt(src, indent);
                    src = tmp_results10714.result1;
                    out = tmp_results10714.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results10555 = TranslateExpr(src, indent);
                    src = tmp_results10555.result1;
                    setup = tmp_results10555.result2;
                    val = tmp_results10555.result3;
                    ConsumeToken_results tmp_results10498 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results10498.result1;
                    int tmp_strlen10425 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str10425 = calloc(tmp_strlen10425, sizeof(char));
                    strcpy(tmp_str10425, setup);
                    strcat(tmp_str10425, indent);
                    int tmp_strlen10418 = strlen(tmp_str10425) + strlen(val) + 1;
                    char* tmp_str10418 = calloc(tmp_strlen10418, sizeof(char));
                    strcpy(tmp_str10418, tmp_str10425);
                    strcat(tmp_str10418, val);
                    int tmp_strlen10409 = strlen(tmp_str10418) + strlen(";\n") + 1;
                    char* tmp_str10409 = calloc(tmp_strlen10409, sizeof(char));
                    strcpy(tmp_str10409, tmp_str10418);
                    strcat(tmp_str10409, ";\n");
                    out = tmp_str10409;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen10300 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str10300 = calloc(tmp_strlen10300, sizeof(char));
                  strcpy(tmp_str10300, "unexpected stmt token, got: ");
                  strcat(tmp_str10300, itoa(tok));
                  int tmp_strlen10291 = strlen(tmp_str10300) + strlen(" \"") + 1;
                  char* tmp_str10291 = calloc(tmp_strlen10291, sizeof(char));
                  strcpy(tmp_str10291, tmp_str10300);
                  strcat(tmp_str10291, " \"");
                  int tmp_strlen10280 = strlen(tmp_str10291) + strlen(tok_str) + 1;
                  char* tmp_str10280 = calloc(tmp_strlen10280, sizeof(char));
                  strcpy(tmp_str10280, tmp_str10291);
                  strcat(tmp_str10280, tok_str);
                  int tmp_strlen10272 = strlen(tmp_str10280) + strlen("\"") + 1;
                  char* tmp_str10272 = calloc(tmp_strlen10272, sizeof(char));
                  strcpy(tmp_str10272, tmp_str10280);
                  strcat(tmp_str10272, "\"");
                  printf("%s", tmp_str10272);
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
  Peek_results tmp_results10136 = Peek(src);
  tok = tmp_results10136.result1;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results10020 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results10020.result1;
      Peek_results tmp_results9968 = Peek(src);
      tok = tmp_results9968.result1;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results9881 = TranslateStmt(src, indent, func_name);
    src = tmp_results9881.result1;
    stmt_out = tmp_results9881.result2;
    int tmp_strlen9798 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str9798 = calloc(tmp_strlen9798, sizeof(char));
    strcpy(tmp_str9798, out);
    strcat(tmp_str9798, stmt_out);
    out = tmp_str9798;
    Peek_results tmp_results9789 = Peek(src);
    tok = tmp_results9789.result1;
  }
  return (TranslateStmts_results){src, out};
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results9637 = Next(src);
  src = tmp_results9637.result1;
  tok = tmp_results9637.result2;
  tok_str = tmp_results9637.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen9463 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str9463 = calloc(tmp_strlen9463, sizeof(char));
    strcpy(tmp_str9463, "expected false or true, got: ");
    strcat(tmp_str9463, itoa(tok));
    int tmp_strlen9454 = strlen(tmp_str9463) + strlen(" \"") + 1;
    char* tmp_str9454 = calloc(tmp_strlen9454, sizeof(char));
    strcpy(tmp_str9454, tmp_str9463);
    strcat(tmp_str9454, " \"");
    int tmp_strlen9443 = strlen(tmp_str9454) + strlen(tok_str) + 1;
    char* tmp_str9443 = calloc(tmp_strlen9443, sizeof(char));
    strcpy(tmp_str9443, tmp_str9454);
    strcat(tmp_str9443, tok_str);
    int tmp_strlen9435 = strlen(tmp_str9443) + strlen("\"") + 1;
    char* tmp_str9435 = calloc(tmp_strlen9435, sizeof(char));
    strcpy(tmp_str9435, tmp_str9443);
    strcat(tmp_str9435, "\"");
    printf("%s", tmp_str9435);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results9326 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results9326.result1;
  lit = tmp_results9326.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results9177 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results9177.result1;
  lit = tmp_results9177.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  ConsumeToken_results tmp_results9000 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results9000.result1;
  char* old_src = src;
  Peek_results tmp_results8927 = Peek(src);
  tok = tmp_results8927.result1;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results8781 = TranslateExprs(src, indent);
    src = tmp_results8781.result1;
    expr_count = tmp_results8781.result2;
    args_setup = tmp_results8781.result3;
    arg_values = tmp_results8781.result4;
  }
  int tmp_strlen8663 = ((strlen(old_src)) - (strlen(src))) - (0) + 1;
  char* tmp_str8663 = calloc(tmp_strlen8663, sizeof(char));
  strncpy(tmp_str8663, old_src + 0, tmp_strlen8663 - 1);
  tmp_str8663[tmp_strlen8663 - 1] = 0;
  char* expr_text = Escape(tmp_str8663);
  ConsumeToken_results tmp_results8633 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results8633.result1;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen8502 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str8502 = calloc(tmp_strlen8502, sizeof(char));
    strcpy(tmp_str8502, "printf(\"%s\", ");
    strcat(tmp_str8502, arg_values);
    int tmp_strlen8495 = strlen(tmp_str8502) + strlen(")") + 1;
    char* tmp_str8495 = calloc(tmp_strlen8495, sizeof(char));
    strcpy(tmp_str8495, tmp_str8502);
    strcat(tmp_str8495, ")");
    val = tmp_str8495;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen8425 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str8425 = calloc(tmp_strlen8425, sizeof(char));
      strcpy(tmp_str8425, "strlen(");
      strcat(tmp_str8425, arg_values);
      int tmp_strlen8418 = strlen(tmp_str8425) + strlen(")") + 1;
      char* tmp_str8418 = calloc(tmp_strlen8418, sizeof(char));
      strcpy(tmp_str8418, tmp_str8425);
      strcat(tmp_str8418, ")");
      val = tmp_str8418;
    } else {
      if (StartsWith(callee, "expect")) {
        int tmp_strlen8335 = strlen("_success = ") + strlen(callee) + 1;
        char* tmp_str8335 = calloc(tmp_strlen8335, sizeof(char));
        strcpy(tmp_str8335, "_success = ");
        strcat(tmp_str8335, callee);
        int tmp_strlen8328 = strlen(tmp_str8335) + strlen("(") + 1;
        char* tmp_str8328 = calloc(tmp_strlen8328, sizeof(char));
        strcpy(tmp_str8328, tmp_str8335);
        strcat(tmp_str8328, "(");
        int tmp_strlen8314 = strlen(tmp_str8328) + strlen(arg_values) + 1;
        char* tmp_str8314 = calloc(tmp_strlen8314, sizeof(char));
        strcpy(tmp_str8314, tmp_str8328);
        strcat(tmp_str8314, arg_values);
        int tmp_strlen8304 = strlen(tmp_str8314) + strlen(", \"") + 1;
        char* tmp_str8304 = calloc(tmp_strlen8304, sizeof(char));
        strcpy(tmp_str8304, tmp_str8314);
        strcat(tmp_str8304, ", \"");
        int tmp_strlen8291 = strlen(tmp_str8304) + strlen(expr_text) + 1;
        char* tmp_str8291 = calloc(tmp_strlen8291, sizeof(char));
        strcpy(tmp_str8291, tmp_str8304);
        strcat(tmp_str8291, expr_text);
        int tmp_strlen8270 = strlen(tmp_str8291) + strlen("\") && _success") + 1;
        char* tmp_str8270 = calloc(tmp_strlen8270, sizeof(char));
        strcpy(tmp_str8270, tmp_str8291);
        strcat(tmp_str8270, "\") && _success");
        val = tmp_str8270;
      } else {
        int tmp_strlen8229 = strlen(callee) + strlen("(") + 1;
        char* tmp_str8229 = calloc(tmp_strlen8229, sizeof(char));
        strcpy(tmp_str8229, callee);
        strcat(tmp_str8229, "(");
        int tmp_strlen8215 = strlen(tmp_str8229) + strlen(arg_values) + 1;
        char* tmp_str8215 = calloc(tmp_strlen8215, sizeof(char));
        strcpy(tmp_str8215, tmp_str8229);
        strcat(tmp_str8215, arg_values);
        int tmp_strlen8208 = strlen(tmp_str8215) + strlen(")") + 1;
        char* tmp_str8208 = calloc(tmp_strlen8208, sizeof(char));
        strcpy(tmp_str8208, tmp_str8215);
        strcat(tmp_str8208, ")");
        val = tmp_str8208;
      }
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  int p = strlen(src);
  ConsumeToken_results tmp_results8021 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results8021.result1;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen7839 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str7839 = calloc(tmp_strlen7839, sizeof(char));
  strcpy(tmp_str7839, "strlen(");
  strcat(tmp_str7839, strvar);
  int tmp_strlen7832 = strlen(tmp_str7839) + strlen(")") + 1;
  char* tmp_str7832 = calloc(tmp_strlen7832, sizeof(char));
  strcpy(tmp_str7832, tmp_str7839);
  strcat(tmp_str7832, ")");
  char* high_expr = tmp_str7832;
  Peek_results tmp_results7827 = Peek(src);
  tok = tmp_results7827.result1;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results7774 = ConsumeToken(src, TOK_COLON);
    src = tmp_results7774.result1;
    TranslateExpr_results tmp_results7728 = TranslateExpr(src, indent);
    src = tmp_results7728.result1;
    high_setup = tmp_results7728.result2;
    high_expr = tmp_results7728.result3;
    ConsumeToken_results tmp_results7664 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results7664.result1;
  } else {
    TranslateExpr_results tmp_results7602 = TranslateExpr(src, indent);
    src = tmp_results7602.result1;
    low_setup = tmp_results7602.result2;
    low_expr = tmp_results7602.result3;
    Peek_results tmp_results7540 = Peek(src);
    tok = tmp_results7540.result1;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results7476 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results7476.result1;
      int tmp_strlen7387 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str7387 = calloc(tmp_strlen7387, sizeof(char));
      strcpy(tmp_str7387, strvar);
      strcat(tmp_str7387, "[");
      int tmp_strlen7375 = strlen(tmp_str7387) + strlen(low_expr) + 1;
      char* tmp_str7375 = calloc(tmp_strlen7375, sizeof(char));
      strcpy(tmp_str7375, tmp_str7387);
      strcat(tmp_str7375, low_expr);
      int tmp_strlen7368 = strlen(tmp_str7375) + strlen("]") + 1;
      char* tmp_str7368 = calloc(tmp_strlen7368, sizeof(char));
      strcpy(tmp_str7368, tmp_str7375);
      strcat(tmp_str7368, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str7368};
    }
    ConsumeToken_results tmp_results7349 = ConsumeToken(src, TOK_COLON);
    src = tmp_results7349.result1;
    Peek_results tmp_results7303 = Peek(src);
    tok = tmp_results7303.result1;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results7239 = TranslateExpr(src, indent);
      src = tmp_results7239.result1;
      high_setup = tmp_results7239.result2;
      high_expr = tmp_results7239.result3;
    }
    ConsumeToken_results tmp_results7165 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results7165.result1;
  }
  int tmp_strlen7072 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str7072 = calloc(tmp_strlen7072, sizeof(char));
  strcpy(tmp_str7072, "tmp_str");
  strcat(tmp_str7072, itoa(p));
  char* tmp_str = tmp_str7072;
  int tmp_strlen7019 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str7019 = calloc(tmp_strlen7019, sizeof(char));
  strcpy(tmp_str7019, "tmp_strlen");
  strcat(tmp_str7019, itoa(p));
  char* tmp_strlen = tmp_str7019;
  int tmp_strlen6971 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str6971 = calloc(tmp_strlen6971, sizeof(char));
  strcpy(tmp_str6971, low_setup);
  strcat(tmp_str6971, high_setup);
  char* setup = tmp_str6971;
  int tmp_strlen6943 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6943 = calloc(tmp_strlen6943, sizeof(char));
  strcpy(tmp_str6943, setup);
  strcat(tmp_str6943, indent);
  int tmp_strlen6933 = strlen(tmp_str6943) + strlen("int ") + 1;
  char* tmp_str6933 = calloc(tmp_strlen6933, sizeof(char));
  strcpy(tmp_str6933, tmp_str6943);
  strcat(tmp_str6933, "int ");
  int tmp_strlen6919 = strlen(tmp_str6933) + strlen(tmp_strlen) + 1;
  char* tmp_str6919 = calloc(tmp_strlen6919, sizeof(char));
  strcpy(tmp_str6919, tmp_str6933);
  strcat(tmp_str6919, tmp_strlen);
  int tmp_strlen6909 = strlen(tmp_str6919) + strlen(" = (") + 1;
  char* tmp_str6909 = calloc(tmp_strlen6909, sizeof(char));
  strcpy(tmp_str6909, tmp_str6919);
  strcat(tmp_str6909, " = (");
  int tmp_strlen6896 = strlen(tmp_str6909) + strlen(high_expr) + 1;
  char* tmp_str6896 = calloc(tmp_strlen6896, sizeof(char));
  strcpy(tmp_str6896, tmp_str6909);
  strcat(tmp_str6896, high_expr);
  int tmp_strlen6885 = strlen(tmp_str6896) + strlen(") - (") + 1;
  char* tmp_str6885 = calloc(tmp_strlen6885, sizeof(char));
  strcpy(tmp_str6885, tmp_str6896);
  strcat(tmp_str6885, ") - (");
  int tmp_strlen6873 = strlen(tmp_str6885) + strlen(low_expr) + 1;
  char* tmp_str6873 = calloc(tmp_strlen6873, sizeof(char));
  strcpy(tmp_str6873, tmp_str6885);
  strcat(tmp_str6873, low_expr);
  int tmp_strlen6859 = strlen(tmp_str6873) + strlen(") + 1;\n") + 1;
  char* tmp_str6859 = calloc(tmp_strlen6859, sizeof(char));
  strcpy(tmp_str6859, tmp_str6873);
  strcat(tmp_str6859, ") + 1;\n");
  setup = tmp_str6859;
  int tmp_strlen6831 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6831 = calloc(tmp_strlen6831, sizeof(char));
  strcpy(tmp_str6831, setup);
  strcat(tmp_str6831, indent);
  int tmp_strlen6819 = strlen(tmp_str6831) + strlen("char* ") + 1;
  char* tmp_str6819 = calloc(tmp_strlen6819, sizeof(char));
  strcpy(tmp_str6819, tmp_str6831);
  strcat(tmp_str6819, "char* ");
  int tmp_strlen6808 = strlen(tmp_str6819) + strlen(tmp_str) + 1;
  char* tmp_str6808 = calloc(tmp_strlen6808, sizeof(char));
  strcpy(tmp_str6808, tmp_str6819);
  strcat(tmp_str6808, tmp_str);
  int tmp_strlen6792 = strlen(tmp_str6808) + strlen(" = calloc(") + 1;
  char* tmp_str6792 = calloc(tmp_strlen6792, sizeof(char));
  strcpy(tmp_str6792, tmp_str6808);
  strcat(tmp_str6792, " = calloc(");
  int tmp_strlen6778 = strlen(tmp_str6792) + strlen(tmp_strlen) + 1;
  char* tmp_str6778 = calloc(tmp_strlen6778, sizeof(char));
  strcpy(tmp_str6778, tmp_str6792);
  strcat(tmp_str6778, tmp_strlen);
  int tmp_strlen6754 = strlen(tmp_str6778) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str6754 = calloc(tmp_strlen6754, sizeof(char));
  strcpy(tmp_str6754, tmp_str6778);
  strcat(tmp_str6754, ", sizeof(char));\n");
  setup = tmp_str6754;
  int tmp_strlen6726 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6726 = calloc(tmp_strlen6726, sizeof(char));
  strcpy(tmp_str6726, setup);
  strcat(tmp_str6726, indent);
  int tmp_strlen6712 = strlen(tmp_str6726) + strlen("strncpy(") + 1;
  char* tmp_str6712 = calloc(tmp_strlen6712, sizeof(char));
  strcpy(tmp_str6712, tmp_str6726);
  strcat(tmp_str6712, "strncpy(");
  int tmp_strlen6701 = strlen(tmp_str6712) + strlen(tmp_str) + 1;
  char* tmp_str6701 = calloc(tmp_strlen6701, sizeof(char));
  strcpy(tmp_str6701, tmp_str6712);
  strcat(tmp_str6701, tmp_str);
  int tmp_strlen6693 = strlen(tmp_str6701) + strlen(", ") + 1;
  char* tmp_str6693 = calloc(tmp_strlen6693, sizeof(char));
  strcpy(tmp_str6693, tmp_str6701);
  strcat(tmp_str6693, ", ");
  int tmp_strlen6683 = strlen(tmp_str6693) + strlen(strvar) + 1;
  char* tmp_str6683 = calloc(tmp_strlen6683, sizeof(char));
  strcpy(tmp_str6683, tmp_str6693);
  strcat(tmp_str6683, strvar);
  int tmp_strlen6674 = strlen(tmp_str6683) + strlen(" + ") + 1;
  char* tmp_str6674 = calloc(tmp_strlen6674, sizeof(char));
  strcpy(tmp_str6674, tmp_str6683);
  strcat(tmp_str6674, " + ");
  int tmp_strlen6662 = strlen(tmp_str6674) + strlen(low_expr) + 1;
  char* tmp_str6662 = calloc(tmp_strlen6662, sizeof(char));
  strcpy(tmp_str6662, tmp_str6674);
  strcat(tmp_str6662, low_expr);
  int tmp_strlen6654 = strlen(tmp_str6662) + strlen(", ") + 1;
  char* tmp_str6654 = calloc(tmp_strlen6654, sizeof(char));
  strcpy(tmp_str6654, tmp_str6662);
  strcat(tmp_str6654, ", ");
  int tmp_strlen6640 = strlen(tmp_str6654) + strlen(tmp_strlen) + 1;
  char* tmp_str6640 = calloc(tmp_strlen6640, sizeof(char));
  strcpy(tmp_str6640, tmp_str6654);
  strcat(tmp_str6640, tmp_strlen);
  int tmp_strlen6626 = strlen(tmp_str6640) + strlen(" - 1);\n") + 1;
  char* tmp_str6626 = calloc(tmp_strlen6626, sizeof(char));
  strcpy(tmp_str6626, tmp_str6640);
  strcat(tmp_str6626, " - 1);\n");
  setup = tmp_str6626;
  int tmp_strlen6598 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str6598 = calloc(tmp_strlen6598, sizeof(char));
  strcpy(tmp_str6598, setup);
  strcat(tmp_str6598, indent);
  int tmp_strlen6587 = strlen(tmp_str6598) + strlen(tmp_str) + 1;
  char* tmp_str6587 = calloc(tmp_strlen6587, sizeof(char));
  strcpy(tmp_str6587, tmp_str6598);
  strcat(tmp_str6587, tmp_str);
  int tmp_strlen6580 = strlen(tmp_str6587) + strlen("[") + 1;
  char* tmp_str6580 = calloc(tmp_strlen6580, sizeof(char));
  strcpy(tmp_str6580, tmp_str6587);
  strcat(tmp_str6580, "[");
  int tmp_strlen6566 = strlen(tmp_str6580) + strlen(tmp_strlen) + 1;
  char* tmp_str6566 = calloc(tmp_strlen6566, sizeof(char));
  strcpy(tmp_str6566, tmp_str6580);
  strcat(tmp_str6566, tmp_strlen);
  int tmp_strlen6548 = strlen(tmp_str6566) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str6548 = calloc(tmp_strlen6548, sizeof(char));
  strcpy(tmp_str6548, tmp_str6566);
  strcat(tmp_str6548, " - 1] = 0;\n");
  setup = tmp_str6548;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6389 = Peek(src);
  tok = tmp_results6389.result1;
  tok_str = tmp_results6389.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results6279 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results6279.result1;
    TranslateExpr_results tmp_results6232 = TranslateExpr(src, indent);
    src = tmp_results6232.result1;
    setup = tmp_results6232.result2;
    val = tmp_results6232.result3;
    ConsumeToken_results tmp_results6179 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results6179.result1;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results6025 = TranslateBoolLiteral(src);
      src = tmp_results6025.result1;
      lit = tmp_results6025.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results5894 = TranslateIntLiteral(src);
        src = tmp_results5894.result1;
        lit = tmp_results5894.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results5764 = TranslateStringLiteral(src);
          src = tmp_results5764.result1;
          lit = tmp_results5764.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results5630 = ConsumeIdent(src);
            src = tmp_results5630.result1;
            ident = tmp_results5630.result2;
            Peek_results tmp_results5591 = Peek(src);
            tok = tmp_results5591.result1;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results5470 = TranslateCall(src, indent, ident);
              src = tmp_results5470.result1;
              setup = tmp_results5470.result2;
              expr = tmp_results5470.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results5270 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results5270.result1;
                setup = tmp_results5270.result2;
                expr = tmp_results5270.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen5050 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str5050 = calloc(tmp_strlen5050, sizeof(char));
            strcpy(tmp_str5050, "unexpected expr, got: ");
            strcat(tmp_str5050, itoa(tok));
            int tmp_strlen5041 = strlen(tmp_str5050) + strlen(" \"") + 1;
            char* tmp_str5041 = calloc(tmp_strlen5041, sizeof(char));
            strcpy(tmp_str5041, tmp_str5050);
            strcat(tmp_str5041, " \"");
            int tmp_strlen5030 = strlen(tmp_str5041) + strlen(tok_str) + 1;
            char* tmp_str5030 = calloc(tmp_strlen5030, sizeof(char));
            strcpy(tmp_str5030, tmp_str5041);
            strcat(tmp_str5030, tok_str);
            int tmp_strlen5022 = strlen(tmp_str5030) + strlen("\"") + 1;
            char* tmp_str5022 = calloc(tmp_strlen5022, sizeof(char));
            strcpy(tmp_str5022, tmp_str5030);
            strcat(tmp_str5022, "\"");
            printf("%s", tmp_str5022);
            exit(1);
          }
        }
      }
    }
  }
}

TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent) {
  int tok;
  Peek_results tmp_results4893 = Peek(src);
  tok = tmp_results4893.result1;
  if (IsUnaryOp(tok)) {
    char* tok_str;
    ConsumeToken_results tmp_results4814 = ConsumeToken(src, tok);
    src = tmp_results4814.result1;
    tok_str = tmp_results4814.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results4718 = TranslateExpr(src, indent);
    src = tmp_results4718.result1;
    setup = tmp_results4718.result2;
    val = tmp_results4718.result3;
    int tmp_strlen4645 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str4645 = calloc(tmp_strlen4645, sizeof(char));
    strcpy(tmp_str4645, tok_str);
    strcat(tmp_str4645, "(");
    int tmp_strlen4638 = strlen(tmp_str4645) + strlen(val) + 1;
    char* tmp_str4638 = calloc(tmp_strlen4638, sizeof(char));
    strcpy(tmp_str4638, tmp_str4645);
    strcat(tmp_str4638, val);
    int tmp_strlen4631 = strlen(tmp_str4638) + strlen(")") + 1;
    char* tmp_str4631 = calloc(tmp_strlen4631, sizeof(char));
    strcpy(tmp_str4631, tmp_str4638);
    strcat(tmp_str4631, ")");
    val = tmp_str4631;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results4527 = TranslateOperand(src, indent);
    src = tmp_results4527.result1;
    setup = tmp_results4527.result2;
    expr = tmp_results4527.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results4284 = TranslateUnaryExpr(src, indent);
  src = tmp_results4284.result1;
  setup = tmp_results4284.result2;
  val = tmp_results4284.result3;
  int op;
  char* op_str;
  Peek_results tmp_results4191 = Peek(src);
  op = tmp_results4191.result1;
  op_str = tmp_results4191.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results4104 = ConsumeToken(src, op);
    src = tmp_results4104.result1;
    op_str = tmp_results4104.result2;
    int tok;
    Peek_results tmp_results4039 = Peek(src);
    tok = tmp_results4039.result1;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results3975 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results3975.result1;
      Peek_results tmp_results3923 = Peek(src);
      tok = tmp_results3923.result1;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results3832 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results3832.result1;
    setup_b = tmp_results3832.result2;
    val_b = tmp_results3832.result3;
    int tmp_strlen3721 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str3721 = calloc(tmp_strlen3721, sizeof(char));
    strcpy(tmp_str3721, setup);
    strcat(tmp_str3721, setup_b);
    setup = tmp_str3721;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen3629 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str3629 = calloc(tmp_strlen3629, sizeof(char));
      strcpy(tmp_str3629, "tmp_str");
      strcat(tmp_str3629, itoa(strlen(src)));
      char* tmp_str = tmp_str3629;
      int tmp_strlen3561 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str3561 = calloc(tmp_strlen3561, sizeof(char));
      strcpy(tmp_str3561, "tmp_strlen");
      strcat(tmp_str3561, itoa(strlen(src)));
      char* tmp_strlen = tmp_str3561;
      int tmp_strlen3525 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3525 = calloc(tmp_strlen3525, sizeof(char));
      strcpy(tmp_str3525, setup);
      strcat(tmp_str3525, indent);
      int tmp_strlen3515 = strlen(tmp_str3525) + strlen("int ") + 1;
      char* tmp_str3515 = calloc(tmp_strlen3515, sizeof(char));
      strcpy(tmp_str3515, tmp_str3525);
      strcat(tmp_str3515, "int ");
      int tmp_strlen3501 = strlen(tmp_str3515) + strlen(tmp_strlen) + 1;
      char* tmp_str3501 = calloc(tmp_strlen3501, sizeof(char));
      strcpy(tmp_str3501, tmp_str3515);
      strcat(tmp_str3501, tmp_strlen);
      int tmp_strlen3485 = strlen(tmp_str3501) + strlen(" = strlen(") + 1;
      char* tmp_str3485 = calloc(tmp_strlen3485, sizeof(char));
      strcpy(tmp_str3485, tmp_str3501);
      strcat(tmp_str3485, " = strlen(");
      int tmp_strlen3478 = strlen(tmp_str3485) + strlen(val) + 1;
      char* tmp_str3478 = calloc(tmp_strlen3478, sizeof(char));
      strcpy(tmp_str3478, tmp_str3485);
      strcat(tmp_str3478, val);
      int tmp_strlen3461 = strlen(tmp_str3478) + strlen(") + strlen(") + 1;
      char* tmp_str3461 = calloc(tmp_strlen3461, sizeof(char));
      strcpy(tmp_str3461, tmp_str3478);
      strcat(tmp_str3461, ") + strlen(");
      int tmp_strlen3452 = strlen(tmp_str3461) + strlen(val_b) + 1;
      char* tmp_str3452 = calloc(tmp_strlen3452, sizeof(char));
      strcpy(tmp_str3452, tmp_str3461);
      strcat(tmp_str3452, val_b);
      int tmp_strlen3438 = strlen(tmp_str3452) + strlen(") + 1;\n") + 1;
      char* tmp_str3438 = calloc(tmp_strlen3438, sizeof(char));
      strcpy(tmp_str3438, tmp_str3452);
      strcat(tmp_str3438, ") + 1;\n");
      setup = tmp_str3438;
      int tmp_strlen3402 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3402 = calloc(tmp_strlen3402, sizeof(char));
      strcpy(tmp_str3402, setup);
      strcat(tmp_str3402, indent);
      int tmp_strlen3390 = strlen(tmp_str3402) + strlen("char* ") + 1;
      char* tmp_str3390 = calloc(tmp_strlen3390, sizeof(char));
      strcpy(tmp_str3390, tmp_str3402);
      strcat(tmp_str3390, "char* ");
      int tmp_strlen3379 = strlen(tmp_str3390) + strlen(tmp_str) + 1;
      char* tmp_str3379 = calloc(tmp_strlen3379, sizeof(char));
      strcpy(tmp_str3379, tmp_str3390);
      strcat(tmp_str3379, tmp_str);
      int tmp_strlen3363 = strlen(tmp_str3379) + strlen(" = calloc(") + 1;
      char* tmp_str3363 = calloc(tmp_strlen3363, sizeof(char));
      strcpy(tmp_str3363, tmp_str3379);
      strcat(tmp_str3363, " = calloc(");
      int tmp_strlen3349 = strlen(tmp_str3363) + strlen(tmp_strlen) + 1;
      char* tmp_str3349 = calloc(tmp_strlen3349, sizeof(char));
      strcpy(tmp_str3349, tmp_str3363);
      strcat(tmp_str3349, tmp_strlen);
      int tmp_strlen3325 = strlen(tmp_str3349) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str3325 = calloc(tmp_strlen3325, sizeof(char));
      strcpy(tmp_str3325, tmp_str3349);
      strcat(tmp_str3325, ", sizeof(char));\n");
      setup = tmp_str3325;
      int tmp_strlen3289 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3289 = calloc(tmp_strlen3289, sizeof(char));
      strcpy(tmp_str3289, setup);
      strcat(tmp_str3289, indent);
      int tmp_strlen3276 = strlen(tmp_str3289) + strlen("strcpy(") + 1;
      char* tmp_str3276 = calloc(tmp_strlen3276, sizeof(char));
      strcpy(tmp_str3276, tmp_str3289);
      strcat(tmp_str3276, "strcpy(");
      int tmp_strlen3265 = strlen(tmp_str3276) + strlen(tmp_str) + 1;
      char* tmp_str3265 = calloc(tmp_strlen3265, sizeof(char));
      strcpy(tmp_str3265, tmp_str3276);
      strcat(tmp_str3265, tmp_str);
      int tmp_strlen3257 = strlen(tmp_str3265) + strlen(", ") + 1;
      char* tmp_str3257 = calloc(tmp_strlen3257, sizeof(char));
      strcpy(tmp_str3257, tmp_str3265);
      strcat(tmp_str3257, ", ");
      int tmp_strlen3250 = strlen(tmp_str3257) + strlen(val) + 1;
      char* tmp_str3250 = calloc(tmp_strlen3250, sizeof(char));
      strcpy(tmp_str3250, tmp_str3257);
      strcat(tmp_str3250, val);
      int tmp_strlen3240 = strlen(tmp_str3250) + strlen(");\n") + 1;
      char* tmp_str3240 = calloc(tmp_strlen3240, sizeof(char));
      strcpy(tmp_str3240, tmp_str3250);
      strcat(tmp_str3240, ");\n");
      setup = tmp_str3240;
      int tmp_strlen3204 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str3204 = calloc(tmp_strlen3204, sizeof(char));
      strcpy(tmp_str3204, setup);
      strcat(tmp_str3204, indent);
      int tmp_strlen3191 = strlen(tmp_str3204) + strlen("strcat(") + 1;
      char* tmp_str3191 = calloc(tmp_strlen3191, sizeof(char));
      strcpy(tmp_str3191, tmp_str3204);
      strcat(tmp_str3191, "strcat(");
      int tmp_strlen3180 = strlen(tmp_str3191) + strlen(tmp_str) + 1;
      char* tmp_str3180 = calloc(tmp_strlen3180, sizeof(char));
      strcpy(tmp_str3180, tmp_str3191);
      strcat(tmp_str3180, tmp_str);
      int tmp_strlen3172 = strlen(tmp_str3180) + strlen(", ") + 1;
      char* tmp_str3172 = calloc(tmp_strlen3172, sizeof(char));
      strcpy(tmp_str3172, tmp_str3180);
      strcat(tmp_str3172, ", ");
      int tmp_strlen3163 = strlen(tmp_str3172) + strlen(val_b) + 1;
      char* tmp_str3163 = calloc(tmp_strlen3163, sizeof(char));
      strcpy(tmp_str3163, tmp_str3172);
      strcat(tmp_str3163, val_b);
      int tmp_strlen3153 = strlen(tmp_str3163) + strlen(");\n") + 1;
      char* tmp_str3153 = calloc(tmp_strlen3153, sizeof(char));
      strcpy(tmp_str3153, tmp_str3163);
      strcat(tmp_str3153, ");\n");
      setup = tmp_str3153;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen3055 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str3055 = calloc(tmp_strlen3055, sizeof(char));
        strcpy(tmp_str3055, "(strcmp(");
        strcat(tmp_str3055, val);
        int tmp_strlen3047 = strlen(tmp_str3055) + strlen(", ") + 1;
        char* tmp_str3047 = calloc(tmp_strlen3047, sizeof(char));
        strcpy(tmp_str3047, tmp_str3055);
        strcat(tmp_str3047, ", ");
        int tmp_strlen3038 = strlen(tmp_str3047) + strlen(val_b) + 1;
        char* tmp_str3038 = calloc(tmp_strlen3038, sizeof(char));
        strcpy(tmp_str3038, tmp_str3047);
        strcat(tmp_str3038, val_b);
        int tmp_strlen3025 = strlen(tmp_str3038) + strlen(") == 0)") + 1;
        char* tmp_str3025 = calloc(tmp_strlen3025, sizeof(char));
        strcpy(tmp_str3025, tmp_str3038);
        strcat(tmp_str3025, ") == 0)");
        val = tmp_str3025;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen2952 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str2952 = calloc(tmp_strlen2952, sizeof(char));
          strcpy(tmp_str2952, "(strcmp(");
          strcat(tmp_str2952, val);
          int tmp_strlen2944 = strlen(tmp_str2952) + strlen(", ") + 1;
          char* tmp_str2944 = calloc(tmp_strlen2944, sizeof(char));
          strcpy(tmp_str2944, tmp_str2952);
          strcat(tmp_str2944, ", ");
          int tmp_strlen2935 = strlen(tmp_str2944) + strlen(val_b) + 1;
          char* tmp_str2935 = calloc(tmp_strlen2935, sizeof(char));
          strcpy(tmp_str2935, tmp_str2944);
          strcat(tmp_str2935, val_b);
          int tmp_strlen2922 = strlen(tmp_str2935) + strlen(") != 0)") + 1;
          char* tmp_str2922 = calloc(tmp_strlen2922, sizeof(char));
          strcpy(tmp_str2922, tmp_str2935);
          strcat(tmp_str2922, ") != 0)");
          val = tmp_str2922;
        } else {
          int tmp_strlen2876 = strlen("(") + strlen(val) + 1;
          char* tmp_str2876 = calloc(tmp_strlen2876, sizeof(char));
          strcpy(tmp_str2876, "(");
          strcat(tmp_str2876, val);
          int tmp_strlen2868 = strlen(tmp_str2876) + strlen(") ") + 1;
          char* tmp_str2868 = calloc(tmp_strlen2868, sizeof(char));
          strcpy(tmp_str2868, tmp_str2876);
          strcat(tmp_str2868, ") ");
          int tmp_strlen2858 = strlen(tmp_str2868) + strlen(op_str) + 1;
          char* tmp_str2858 = calloc(tmp_strlen2858, sizeof(char));
          strcpy(tmp_str2858, tmp_str2868);
          strcat(tmp_str2858, op_str);
          int tmp_strlen2850 = strlen(tmp_str2858) + strlen(" (") + 1;
          char* tmp_str2850 = calloc(tmp_strlen2850, sizeof(char));
          strcpy(tmp_str2850, tmp_str2858);
          strcat(tmp_str2850, " (");
          int tmp_strlen2841 = strlen(tmp_str2850) + strlen(val_b) + 1;
          char* tmp_str2841 = calloc(tmp_strlen2841, sizeof(char));
          strcpy(tmp_str2841, tmp_str2850);
          strcat(tmp_str2841, val_b);
          int tmp_strlen2834 = strlen(tmp_str2841) + strlen(")") + 1;
          char* tmp_str2834 = calloc(tmp_strlen2834, sizeof(char));
          strcpy(tmp_str2834, tmp_str2841);
          strcat(tmp_str2834, ")");
          val = tmp_str2834;
        }
      }
    }
    Peek_results tmp_results2815 = Peek(src);
    op = tmp_results2815.result1;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results2638 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results2638.result1;
  setup = tmp_results2638.result2;
  expr = tmp_results2638.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results2404 = TranslateExpr(src, indent);
  src = tmp_results2404.result1;
  expr_setup = tmp_results2404.result2;
  expr_value = tmp_results2404.result3;
  int tok;
  Peek_results tmp_results2326 = Peek(src);
  tok = tmp_results2326.result1;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results2161 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results2161.result1;
    TranslateExpr_results tmp_results2115 = TranslateExpr(src, indent);
    src = tmp_results2115.result1;
    expr_setup = tmp_results2115.result2;
    expr_value = tmp_results2115.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen1973 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str1973 = calloc(tmp_strlen1973, sizeof(char));
    strcpy(tmp_str1973, exprs_setup);
    strcat(tmp_str1973, expr_setup);
    exprs_setup = tmp_str1973;
    int tmp_strlen1931 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str1931 = calloc(tmp_strlen1931, sizeof(char));
    strcpy(tmp_str1931, exprs_value);
    strcat(tmp_str1931, ", ");
    int tmp_strlen1917 = strlen(tmp_str1931) + strlen(expr_value) + 1;
    char* tmp_str1917 = calloc(tmp_strlen1917, sizeof(char));
    strcpy(tmp_str1917, tmp_str1931);
    strcat(tmp_str1917, expr_value);
    exprs_value = tmp_str1917;
    Peek_results tmp_results1908 = Peek(src);
    tok = tmp_results1908.result1;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

int Find(char* haystack, char* needle) {
  if ((strlen(haystack)) == (0)) {
    return -(1);
  }
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
      int tmp_strlen1452 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str1452 = calloc(tmp_strlen1452, sizeof(char));
      strncpy(tmp_str1452, haystack + i, tmp_strlen1452 - 1);
      tmp_str1452[tmp_strlen1452 - 1] = 0;
      if ((strcmp(tmp_str1452, needle) != 0)) {
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
      int tmp_strlen1117 = (strlen(prefix)) - (0) + 1;
      char* tmp_str1117 = calloc(tmp_strlen1117, sizeof(char));
      strncpy(tmp_str1117, text + 0, tmp_strlen1117 - 1);
      tmp_str1117[tmp_strlen1117 - 1] = 0;
      return (strcmp(tmp_str1117, prefix) == 0);
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
      int tmp_strlen874 = (strlen(text)) - ((strlen(text)) - (strlen(suffix))) + 1;
      char* tmp_str874 = calloc(tmp_strlen874, sizeof(char));
      strncpy(tmp_str874, text + (strlen(text)) - (strlen(suffix)), tmp_strlen874 - 1);
      tmp_str874[tmp_strlen874 - 1] = 0;
      return (strcmp(tmp_str874, suffix) == 0);
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
  int tmp_strlen653 = (i) - (0) + 1;
  char* tmp_str653 = calloc(tmp_strlen653, sizeof(char));
  strncpy(tmp_str653, s + 0, tmp_strlen653 - 1);
  tmp_str653[tmp_strlen653 - 1] = 0;
  int tmp_strlen646 = (strlen(s)) - ((i) + (1)) + 1;
  char* tmp_str646 = calloc(tmp_strlen646, sizeof(char));
  strncpy(tmp_str646, s + (i) + (1), tmp_strlen646 - 1);
  tmp_str646[tmp_strlen646 - 1] = 0;
  return (Split_results){tmp_str653, tmp_str646};
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
    int tmp_strlen276 = (strlen(text)) - (1) + 1;
    char* tmp_str276 = calloc(tmp_strlen276, sizeof(char));
    strncpy(tmp_str276, text + 1, tmp_strlen276 - 1);
    tmp_str276[tmp_strlen276 - 1] = 0;
    text = tmp_str276;
  }
  return text;
}

char* Escape(char* text) {
  int i = 0;
  while ((i) < (strlen(text))) {
    if (((text[i]) == (34)) || ((text[i]) == (92))) {
      int tmp_strlen100 = (i) - (0) + 1;
      char* tmp_str100 = calloc(tmp_strlen100, sizeof(char));
      strncpy(tmp_str100, text + 0, tmp_strlen100 - 1);
      tmp_str100[tmp_strlen100 - 1] = 0;
      int tmp_strlen88 = strlen(tmp_str100) + strlen("\\") + 1;
      char* tmp_str88 = calloc(tmp_strlen88, sizeof(char));
      strcpy(tmp_str88, tmp_str100);
      strcat(tmp_str88, "\\");
      int tmp_strlen80 = (strlen(text)) - (i) + 1;
      char* tmp_str80 = calloc(tmp_strlen80, sizeof(char));
      strncpy(tmp_str80, text + i, tmp_strlen80 - 1);
      tmp_str80[tmp_strlen80 - 1] = 0;
      int tmp_strlen76 = strlen(tmp_str88) + strlen(tmp_str80) + 1;
      char* tmp_str76 = calloc(tmp_strlen76, sizeof(char));
      strcpy(tmp_str76, tmp_str88);
      strcat(tmp_str76, tmp_str80);
      text = tmp_str76;
      i = (i) + (1);
    }
    i = (i) + (1);
  }
  return text;
}


