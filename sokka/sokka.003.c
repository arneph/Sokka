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
const int TOK_COLON = 210;
const int TOK_COMMA = 211;
const int TOK_ASSIGN = 212;
const int TOK_RARROW = 213;
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
                  int tmp_strlen30316 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str30316 = calloc(tmp_strlen30316, sizeof(char));
                  strcpy(tmp_str30316, "token has no defined precedence: ");
                  strcat(tmp_str30316, itoa(tok));
                  printf("%s", tmp_str30316);
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
      int tmp_strlen30001 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str30001 = calloc(tmp_strlen30001, sizeof(char));
      strncpy(tmp_str30001, haystack + i, tmp_strlen30001 - 1);
      tmp_str30001[tmp_strlen30001 - 1] = 0;
      if ((strcmp(tmp_str30001, needle) != 0)) {
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
      int tmp_strlen29666 = (strlen(prefix)) - (0) + 1;
      char* tmp_str29666 = calloc(tmp_strlen29666, sizeof(char));
      strncpy(tmp_str29666, text + 0, tmp_strlen29666 - 1);
      tmp_str29666[tmp_strlen29666 - 1] = 0;
      return (strcmp(tmp_str29666, prefix) == 0);
    }
  }
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
    int tmp_strlen29272 = (strlen(text)) - (1) + 1;
    char* tmp_str29272 = calloc(tmp_strlen29272, sizeof(char));
    strncpy(tmp_str29272, text + 1, tmp_strlen29272 - 1);
    tmp_str29272[tmp_strlen29272 - 1] = 0;
    text = tmp_str29272;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen29049 = (strlen(src)) - (2) + 1;
      char* tmp_str29049 = calloc(tmp_strlen29049, sizeof(char));
      strncpy(tmp_str29049, src + 2, tmp_strlen29049 - 1);
      tmp_str29049[tmp_strlen29049 - 1] = 0;
      return (Next_results){tmp_str29049, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen28970 = (strlen(src)) - (2) + 1;
        char* tmp_str28970 = calloc(tmp_strlen28970, sizeof(char));
        strncpy(tmp_str28970, src + 2, tmp_strlen28970 - 1);
        tmp_str28970[tmp_strlen28970 - 1] = 0;
        return (Next_results){tmp_str28970, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen28894 = (strlen(src)) - (2) + 1;
          char* tmp_str28894 = calloc(tmp_strlen28894, sizeof(char));
          strncpy(tmp_str28894, src + 2, tmp_strlen28894 - 1);
          tmp_str28894[tmp_strlen28894 - 1] = 0;
          return (Next_results){tmp_str28894, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen28817 = (strlen(src)) - (2) + 1;
            char* tmp_str28817 = calloc(tmp_strlen28817, sizeof(char));
            strncpy(tmp_str28817, src + 2, tmp_strlen28817 - 1);
            tmp_str28817[tmp_strlen28817 - 1] = 0;
            return (Next_results){tmp_str28817, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen28742 = (strlen(src)) - (2) + 1;
              char* tmp_str28742 = calloc(tmp_strlen28742, sizeof(char));
              strncpy(tmp_str28742, src + 2, tmp_strlen28742 - 1);
              tmp_str28742[tmp_strlen28742 - 1] = 0;
              return (Next_results){tmp_str28742, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen28666 = (strlen(src)) - (2) + 1;
                char* tmp_str28666 = calloc(tmp_strlen28666, sizeof(char));
                strncpy(tmp_str28666, src + 2, tmp_strlen28666 - 1);
                tmp_str28666[tmp_strlen28666 - 1] = 0;
                return (Next_results){tmp_str28666, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen28590 = (strlen(src)) - (2) + 1;
                  char* tmp_str28590 = calloc(tmp_strlen28590, sizeof(char));
                  strncpy(tmp_str28590, src + 2, tmp_strlen28590 - 1);
                  tmp_str28590[tmp_strlen28590 - 1] = 0;
                  return (Next_results){tmp_str28590, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen28514 = (strlen(src)) - (2) + 1;
                    char* tmp_str28514 = calloc(tmp_strlen28514, sizeof(char));
                    strncpy(tmp_str28514, src + 2, tmp_strlen28514 - 1);
                    tmp_str28514[tmp_strlen28514 - 1] = 0;
                    return (Next_results){tmp_str28514, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen28435 = (strlen(src)) - (2) + 1;
                      char* tmp_str28435 = calloc(tmp_strlen28435, sizeof(char));
                      strncpy(tmp_str28435, src + 2, tmp_strlen28435 - 1);
                      tmp_str28435[tmp_strlen28435 - 1] = 0;
                      return (Next_results){tmp_str28435, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen28356 = (strlen(src)) - (3) + 1;
                        char* tmp_str28356 = calloc(tmp_strlen28356, sizeof(char));
                        strncpy(tmp_str28356, src + 3, tmp_strlen28356 - 1);
                        tmp_str28356[tmp_strlen28356 - 1] = 0;
                        return (Next_results){tmp_str28356, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen28276 = (strlen(src)) - (1) + 1;
                          char* tmp_str28276 = calloc(tmp_strlen28276, sizeof(char));
                          strncpy(tmp_str28276, src + 1, tmp_strlen28276 - 1);
                          tmp_str28276[tmp_strlen28276 - 1] = 0;
                          return (Next_results){tmp_str28276, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen28197 = (strlen(src)) - (1) + 1;
                            char* tmp_str28197 = calloc(tmp_strlen28197, sizeof(char));
                            strncpy(tmp_str28197, src + 1, tmp_strlen28197 - 1);
                            tmp_str28197[tmp_strlen28197 - 1] = 0;
                            return (Next_results){tmp_str28197, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen28120 = (strlen(src)) - (1) + 1;
                              char* tmp_str28120 = calloc(tmp_strlen28120, sizeof(char));
                              strncpy(tmp_str28120, src + 1, tmp_strlen28120 - 1);
                              tmp_str28120[tmp_strlen28120 - 1] = 0;
                              return (Next_results){tmp_str28120, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen28043 = (strlen(src)) - (1) + 1;
                                char* tmp_str28043 = calloc(tmp_strlen28043, sizeof(char));
                                strncpy(tmp_str28043, src + 1, tmp_strlen28043 - 1);
                                tmp_str28043[tmp_strlen28043 - 1] = 0;
                                return (Next_results){tmp_str28043, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen27964 = (strlen(src)) - (1) + 1;
                                  char* tmp_str27964 = calloc(tmp_strlen27964, sizeof(char));
                                  strncpy(tmp_str27964, src + 1, tmp_strlen27964 - 1);
                                  tmp_str27964[tmp_strlen27964 - 1] = 0;
                                  return (Next_results){tmp_str27964, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen27885 = (strlen(src)) - (1) + 1;
                                    char* tmp_str27885 = calloc(tmp_strlen27885, sizeof(char));
                                    strncpy(tmp_str27885, src + 1, tmp_strlen27885 - 1);
                                    tmp_str27885[tmp_strlen27885 - 1] = 0;
                                    return (Next_results){tmp_str27885, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen27808 = (strlen(src)) - (1) + 1;
                                      char* tmp_str27808 = calloc(tmp_strlen27808, sizeof(char));
                                      strncpy(tmp_str27808, src + 1, tmp_strlen27808 - 1);
                                      tmp_str27808[tmp_strlen27808 - 1] = 0;
                                      return (Next_results){tmp_str27808, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, ":")) {
                                        int tmp_strlen27731 = (strlen(src)) - (1) + 1;
                                        char* tmp_str27731 = calloc(tmp_strlen27731, sizeof(char));
                                        strncpy(tmp_str27731, src + 1, tmp_strlen27731 - 1);
                                        tmp_str27731[tmp_strlen27731 - 1] = 0;
                                        return (Next_results){tmp_str27731, TOK_COLON, ":"};
                                      } else {
                                        if (StartsWith(src, ",")) {
                                          int tmp_strlen27655 = (strlen(src)) - (1) + 1;
                                          char* tmp_str27655 = calloc(tmp_strlen27655, sizeof(char));
                                          strncpy(tmp_str27655, src + 1, tmp_strlen27655 - 1);
                                          tmp_str27655[tmp_strlen27655 - 1] = 0;
                                          return (Next_results){tmp_str27655, TOK_COMMA, ","};
                                        } else {
                                          if (StartsWith(src, "=")) {
                                            int tmp_strlen27579 = (strlen(src)) - (1) + 1;
                                            char* tmp_str27579 = calloc(tmp_strlen27579, sizeof(char));
                                            strncpy(tmp_str27579, src + 1, tmp_strlen27579 - 1);
                                            tmp_str27579[tmp_strlen27579 - 1] = 0;
                                            return (Next_results){tmp_str27579, TOK_ASSIGN, "="};
                                          } else {
                                            if (StartsWith(src, "!")) {
                                              int tmp_strlen27502 = (strlen(src)) - (1) + 1;
                                              char* tmp_str27502 = calloc(tmp_strlen27502, sizeof(char));
                                              strncpy(tmp_str27502, src + 1, tmp_strlen27502 - 1);
                                              tmp_str27502[tmp_strlen27502 - 1] = 0;
                                              return (Next_results){tmp_str27502, TOK_BNOT, "!"};
                                            } else {
                                              if (StartsWith(src, "+")) {
                                                int tmp_strlen27427 = (strlen(src)) - (1) + 1;
                                                char* tmp_str27427 = calloc(tmp_strlen27427, sizeof(char));
                                                strncpy(tmp_str27427, src + 1, tmp_strlen27427 - 1);
                                                tmp_str27427[tmp_strlen27427 - 1] = 0;
                                                return (Next_results){tmp_str27427, TOK_ADD, "+"};
                                              } else {
                                                if (StartsWith(src, "-")) {
                                                  int tmp_strlen27353 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str27353 = calloc(tmp_strlen27353, sizeof(char));
                                                  strncpy(tmp_str27353, src + 1, tmp_strlen27353 - 1);
                                                  tmp_str27353[tmp_strlen27353 - 1] = 0;
                                                  return (Next_results){tmp_str27353, TOK_SUB, "-"};
                                                } else {
                                                  if (StartsWith(src, "*")) {
                                                    int tmp_strlen27279 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str27279 = calloc(tmp_strlen27279, sizeof(char));
                                                    strncpy(tmp_str27279, src + 1, tmp_strlen27279 - 1);
                                                    tmp_str27279[tmp_strlen27279 - 1] = 0;
                                                    return (Next_results){tmp_str27279, TOK_MUL, "*"};
                                                  } else {
                                                    if (StartsWith(src, "/")) {
                                                      int tmp_strlen27205 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str27205 = calloc(tmp_strlen27205, sizeof(char));
                                                      strncpy(tmp_str27205, src + 1, tmp_strlen27205 - 1);
                                                      tmp_str27205[tmp_strlen27205 - 1] = 0;
                                                      return (Next_results){tmp_str27205, TOK_DIV, "/"};
                                                    } else {
                                                      if (StartsWith(src, "%")) {
                                                        int tmp_strlen27131 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str27131 = calloc(tmp_strlen27131, sizeof(char));
                                                        strncpy(tmp_str27131, src + 1, tmp_strlen27131 - 1);
                                                        tmp_str27131[tmp_strlen27131 - 1] = 0;
                                                        return (Next_results){tmp_str27131, TOK_REM, "%"};
                                                      } else {
                                                        if (StartsWith(src, "~")) {
                                                          int tmp_strlen27057 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str27057 = calloc(tmp_strlen27057, sizeof(char));
                                                          strncpy(tmp_str27057, src + 1, tmp_strlen27057 - 1);
                                                          tmp_str27057[tmp_strlen27057 - 1] = 0;
                                                          return (Next_results){tmp_str27057, TOK_INOT, "~"};
                                                        } else {
                                                          if (StartsWith(src, "|")) {
                                                            int tmp_strlen26982 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str26982 = calloc(tmp_strlen26982, sizeof(char));
                                                            strncpy(tmp_str26982, src + 1, tmp_strlen26982 - 1);
                                                            tmp_str26982[tmp_strlen26982 - 1] = 0;
                                                            return (Next_results){tmp_str26982, TOK_IOR, "|"};
                                                          } else {
                                                            if (StartsWith(src, "&")) {
                                                              int tmp_strlen26908 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str26908 = calloc(tmp_strlen26908, sizeof(char));
                                                              strncpy(tmp_str26908, src + 1, tmp_strlen26908 - 1);
                                                              tmp_str26908[tmp_strlen26908 - 1] = 0;
                                                              return (Next_results){tmp_str26908, TOK_IAND, "&"};
                                                            } else {
                                                              if (StartsWith(src, "^")) {
                                                                int tmp_strlen26833 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str26833 = calloc(tmp_strlen26833, sizeof(char));
                                                                strncpy(tmp_str26833, src + 1, tmp_strlen26833 - 1);
                                                                tmp_str26833[tmp_strlen26833 - 1] = 0;
                                                                return (Next_results){tmp_str26833, TOK_IXOR, "^"};
                                                              } else {
                                                                if (StartsWith(src, "<")) {
                                                                  int tmp_strlen26758 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str26758 = calloc(tmp_strlen26758, sizeof(char));
                                                                  strncpy(tmp_str26758, src + 1, tmp_strlen26758 - 1);
                                                                  tmp_str26758[tmp_strlen26758 - 1] = 0;
                                                                  return (Next_results){tmp_str26758, TOK_LESS, "<"};
                                                                } else {
                                                                  if (StartsWith(src, ">")) {
                                                                    int tmp_strlen26683 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str26683 = calloc(tmp_strlen26683, sizeof(char));
                                                                    strncpy(tmp_str26683, src + 1, tmp_strlen26683 - 1);
                                                                    tmp_str26683[tmp_strlen26683 - 1] = 0;
                                                                    return (Next_results){tmp_str26683, TOK_GREATER, ">"};
                                                                  } else {
                                                                    if (IsAlpha(src[0])) {
                                                                      int i = 1;
                                                                      while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                        i = (i) + (1);
                                                                      }
                                                                      i = (i) - (1);
                                                                      int tmp_strlen26452 = (i) - (0) + 1;
                                                                      char* tmp_str26452 = calloc(tmp_strlen26452, sizeof(char));
                                                                      strncpy(tmp_str26452, src + 0, tmp_strlen26452 - 1);
                                                                      tmp_str26452[tmp_strlen26452 - 1] = 0;
                                                                      char* ts = tmp_str26452;
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
                                                                      int tmp_strlen25660 = (strlen(src)) - (i) + 1;
                                                                      char* tmp_str25660 = calloc(tmp_strlen25660, sizeof(char));
                                                                      strncpy(tmp_str25660, src + i, tmp_strlen25660 - 1);
                                                                      tmp_str25660[tmp_strlen25660 - 1] = 0;
                                                                      return (Next_results){tmp_str25660, tt, ts};
                                                                    } else {
                                                                      if (IsNumeric(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        int tmp_strlen25492 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str25492 = calloc(tmp_strlen25492, sizeof(char));
                                                                        strncpy(tmp_str25492, src + i, tmp_strlen25492 - 1);
                                                                        tmp_str25492[tmp_strlen25492 - 1] = 0;
                                                                        int tmp_strlen25471 = (i) - (0) + 1;
                                                                        char* tmp_str25471 = calloc(tmp_strlen25471, sizeof(char));
                                                                        strncpy(tmp_str25471, src + 0, tmp_strlen25471 - 1);
                                                                        tmp_str25471[tmp_strlen25471 - 1] = 0;
                                                                        return (Next_results){tmp_str25492, TOK_INTLIT, tmp_str25471};
                                                                      } else {
                                                                        if (StartsWith(src, "\"")) {
                                                                          int i = 1;
                                                                          while (true) {
                                                                            int tmp_strlen25390 = ((i) + (1)) - (i) + 1;
                                                                            char* tmp_str25390 = calloc(tmp_strlen25390, sizeof(char));
                                                                            strncpy(tmp_str25390, src + i, tmp_strlen25390 - 1);
                                                                            tmp_str25390[tmp_strlen25390 - 1] = 0;
                                                                            if (!((strcmp(tmp_str25390, "\"") != 0))) break;
                                                                            i = (i) + (1);
                                                                            int tmp_strlen25331 = (i) - ((i) - (1)) + 1;
                                                                            char* tmp_str25331 = calloc(tmp_strlen25331, sizeof(char));
                                                                            strncpy(tmp_str25331, src + (i) - (1), tmp_strlen25331 - 1);
                                                                            tmp_str25331[tmp_strlen25331 - 1] = 0;
                                                                            if ((strcmp(tmp_str25331, "\\") == 0)) {
                                                                              i = (i) + (1);
                                                                            }
                                                                          }
                                                                          i = (i) + (1);
                                                                          int tmp_strlen25227 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str25227 = calloc(tmp_strlen25227, sizeof(char));
                                                                          strncpy(tmp_str25227, src + i, tmp_strlen25227 - 1);
                                                                          tmp_str25227[tmp_strlen25227 - 1] = 0;
                                                                          int tmp_strlen25206 = (i) - (0) + 1;
                                                                          char* tmp_str25206 = calloc(tmp_strlen25206, sizeof(char));
                                                                          strncpy(tmp_str25206, src + 0, tmp_strlen25206 - 1);
                                                                          tmp_str25206[tmp_strlen25206 - 1] = 0;
                                                                          return (Next_results){tmp_str25227, TOK_STRLIT, tmp_str25206};
                                                                        } else {
                                                                          int tmp_strlen25141 = (1) - (0) + 1;
                                                                          char* tmp_str25141 = calloc(tmp_strlen25141, sizeof(char));
                                                                          strncpy(tmp_str25141, src + 0, tmp_strlen25141 - 1);
                                                                          tmp_str25141[tmp_strlen25141 - 1] = 0;
                                                                          int tmp_strlen25137 = strlen("unexpected token start: ") + strlen(tmp_str25141) + 1;
                                                                          char* tmp_str25137 = calloc(tmp_strlen25137, sizeof(char));
                                                                          strcpy(tmp_str25137, "unexpected token start: ");
                                                                          strcat(tmp_str25137, tmp_str25141);
                                                                          printf("%s", tmp_str25137);
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

Peek_results Peek(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results25025 = Next(src);
  src = tmp_results25025.result1;
  tok = tmp_results25025.result2;
  tok_str = tmp_results25025.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results24839 = Next(src);
  src = tmp_results24839.result1;
  actual_tok = tmp_results24839.result2;
  actual_tok_str = tmp_results24839.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen24705 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str24705 = calloc(tmp_strlen24705, sizeof(char));
    strcpy(tmp_str24705, "expected token: ");
    strcat(tmp_str24705, itoa(expected_tok));
    int tmp_strlen24678 = strlen(tmp_str24705) + strlen(" got: ") + 1;
    char* tmp_str24678 = calloc(tmp_strlen24678, sizeof(char));
    strcpy(tmp_str24678, tmp_str24705);
    strcat(tmp_str24678, " got: ");
    int tmp_strlen24658 = strlen(tmp_str24678) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str24658 = calloc(tmp_strlen24658, sizeof(char));
    strcpy(tmp_str24658, tmp_str24678);
    strcat(tmp_str24658, itoa(actual_tok));
    int tmp_strlen24649 = strlen(tmp_str24658) + strlen(" \"") + 1;
    char* tmp_str24649 = calloc(tmp_strlen24649, sizeof(char));
    strcpy(tmp_str24649, tmp_str24658);
    strcat(tmp_str24649, " \"");
    int tmp_strlen24631 = strlen(tmp_str24649) + strlen(actual_tok_str) + 1;
    char* tmp_str24631 = calloc(tmp_strlen24631, sizeof(char));
    strcpy(tmp_str24631, tmp_str24649);
    strcat(tmp_str24631, actual_tok_str);
    int tmp_strlen24623 = strlen(tmp_str24631) + strlen("\"") + 1;
    char* tmp_str24623 = calloc(tmp_strlen24623, sizeof(char));
    strcpy(tmp_str24623, tmp_str24631);
    strcat(tmp_str24623, "\"");
    printf("%s", tmp_str24623);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results24455 = Next(src);
  src = tmp_results24455.result1;
  actual_tok = tmp_results24455.result2;
  actual_tok_str = tmp_results24455.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen24321 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str24321 = calloc(tmp_strlen24321, sizeof(char));
    strcpy(tmp_str24321, "expected ident, got: ");
    strcat(tmp_str24321, itoa(actual_tok));
    int tmp_strlen24312 = strlen(tmp_str24321) + strlen(" \"") + 1;
    char* tmp_str24312 = calloc(tmp_strlen24312, sizeof(char));
    strcpy(tmp_str24312, tmp_str24321);
    strcat(tmp_str24312, " \"");
    int tmp_strlen24294 = strlen(tmp_str24312) + strlen(actual_tok_str) + 1;
    char* tmp_str24294 = calloc(tmp_strlen24294, sizeof(char));
    strcpy(tmp_str24294, tmp_str24312);
    strcat(tmp_str24294, actual_tok_str);
    int tmp_strlen24286 = strlen(tmp_str24294) + strlen("\"") + 1;
    char* tmp_str24286 = calloc(tmp_strlen24286, sizeof(char));
    strcpy(tmp_str24286, tmp_str24294);
    strcat(tmp_str24286, "\"");
    printf("%s", tmp_str24286);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results24126 = Next(src);
  src = tmp_results24126.result1;
  tok = tmp_results24126.result2;
  tok_str = tmp_results24126.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen23829 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str23829 = calloc(tmp_strlen23829, sizeof(char));
        strcpy(tmp_str23829, "expected type, got: ");
        strcat(tmp_str23829, itoa(tok));
        int tmp_strlen23820 = strlen(tmp_str23829) + strlen(" \"") + 1;
        char* tmp_str23820 = calloc(tmp_strlen23820, sizeof(char));
        strcpy(tmp_str23820, tmp_str23829);
        strcat(tmp_str23820, " \"");
        int tmp_strlen23809 = strlen(tmp_str23820) + strlen(tok_str) + 1;
        char* tmp_str23809 = calloc(tmp_strlen23809, sizeof(char));
        strcpy(tmp_str23809, tmp_str23820);
        strcat(tmp_str23809, tok_str);
        int tmp_strlen23801 = strlen(tmp_str23809) + strlen("\"") + 1;
        char* tmp_str23801 = calloc(tmp_strlen23801, sizeof(char));
        strcpy(tmp_str23801, tmp_str23809);
        strcat(tmp_str23801, "\"");
        printf("%s", tmp_str23801);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results23670 = Next(src);
  src = tmp_results23670.result1;
  tok = tmp_results23670.result2;
  tok_str = tmp_results23670.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen23496 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str23496 = calloc(tmp_strlen23496, sizeof(char));
    strcpy(tmp_str23496, "expected false or true, got: ");
    strcat(tmp_str23496, itoa(tok));
    int tmp_strlen23487 = strlen(tmp_str23496) + strlen(" \"") + 1;
    char* tmp_str23487 = calloc(tmp_strlen23487, sizeof(char));
    strcpy(tmp_str23487, tmp_str23496);
    strcat(tmp_str23487, " \"");
    int tmp_strlen23476 = strlen(tmp_str23487) + strlen(tok_str) + 1;
    char* tmp_str23476 = calloc(tmp_strlen23476, sizeof(char));
    strcpy(tmp_str23476, tmp_str23487);
    strcat(tmp_str23476, tok_str);
    int tmp_strlen23468 = strlen(tmp_str23476) + strlen("\"") + 1;
    char* tmp_str23468 = calloc(tmp_strlen23468, sizeof(char));
    strcpy(tmp_str23468, tmp_str23476);
    strcat(tmp_str23468, "\"");
    printf("%s", tmp_str23468);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results23359 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results23359.result1;
  lit = tmp_results23359.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results23210 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results23210.result1;
  lit = tmp_results23210.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results23009 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results23009.result1;
  tok_str = tmp_results23009.result2;
  Peek_results tmp_results22960 = Peek(src);
  tok = tmp_results22960.result1;
  tok_str = tmp_results22960.result2;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results22808 = TranslateExprs(src, indent);
    src = tmp_results22808.result1;
    expr_count = tmp_results22808.result2;
    args_setup = tmp_results22808.result3;
    arg_values = tmp_results22808.result4;
  }
  ConsumeToken_results tmp_results22728 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results22728.result1;
  tok_str = tmp_results22728.result2;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen22591 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str22591 = calloc(tmp_strlen22591, sizeof(char));
    strcpy(tmp_str22591, "printf(\"%s\", ");
    strcat(tmp_str22591, arg_values);
    int tmp_strlen22584 = strlen(tmp_str22591) + strlen(")") + 1;
    char* tmp_str22584 = calloc(tmp_strlen22584, sizeof(char));
    strcpy(tmp_str22584, tmp_str22591);
    strcat(tmp_str22584, ")");
    val = tmp_str22584;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen22514 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str22514 = calloc(tmp_strlen22514, sizeof(char));
      strcpy(tmp_str22514, "strlen(");
      strcat(tmp_str22514, arg_values);
      int tmp_strlen22507 = strlen(tmp_str22514) + strlen(")") + 1;
      char* tmp_str22507 = calloc(tmp_strlen22507, sizeof(char));
      strcpy(tmp_str22507, tmp_str22514);
      strcat(tmp_str22507, ")");
      val = tmp_str22507;
    } else {
      int tmp_strlen22466 = strlen(callee) + strlen("(") + 1;
      char* tmp_str22466 = calloc(tmp_strlen22466, sizeof(char));
      strcpy(tmp_str22466, callee);
      strcat(tmp_str22466, "(");
      int tmp_strlen22452 = strlen(tmp_str22466) + strlen(arg_values) + 1;
      char* tmp_str22452 = calloc(tmp_strlen22452, sizeof(char));
      strcpy(tmp_str22452, tmp_str22466);
      strcat(tmp_str22452, arg_values);
      int tmp_strlen22445 = strlen(tmp_str22452) + strlen(")") + 1;
      char* tmp_str22445 = calloc(tmp_strlen22445, sizeof(char));
      strcpy(tmp_str22445, tmp_str22452);
      strcat(tmp_str22445, ")");
      val = tmp_str22445;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  char* tok_str;
  int p = strlen(src);
  ConsumeToken_results tmp_results22234 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results22234.result1;
  tok_str = tmp_results22234.result2;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen22046 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str22046 = calloc(tmp_strlen22046, sizeof(char));
  strcpy(tmp_str22046, "strlen(");
  strcat(tmp_str22046, strvar);
  int tmp_strlen22039 = strlen(tmp_str22046) + strlen(")") + 1;
  char* tmp_str22039 = calloc(tmp_strlen22039, sizeof(char));
  strcpy(tmp_str22039, tmp_str22046);
  strcat(tmp_str22039, ")");
  char* high_expr = tmp_str22039;
  Peek_results tmp_results22034 = Peek(src);
  tok = tmp_results22034.result1;
  tok_str = tmp_results22034.result2;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results21975 = ConsumeToken(src, TOK_COLON);
    src = tmp_results21975.result1;
    tok_str = tmp_results21975.result2;
    TranslateExpr_results tmp_results21923 = TranslateExpr(src, indent);
    src = tmp_results21923.result1;
    high_setup = tmp_results21923.result2;
    high_expr = tmp_results21923.result3;
    ConsumeToken_results tmp_results21859 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results21859.result1;
    tok_str = tmp_results21859.result2;
  } else {
    TranslateExpr_results tmp_results21791 = TranslateExpr(src, indent);
    src = tmp_results21791.result1;
    low_setup = tmp_results21791.result2;
    low_expr = tmp_results21791.result3;
    Peek_results tmp_results21729 = Peek(src);
    tok = tmp_results21729.result1;
    tok_str = tmp_results21729.result2;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results21659 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results21659.result1;
      tok_str = tmp_results21659.result2;
      int tmp_strlen21564 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str21564 = calloc(tmp_strlen21564, sizeof(char));
      strcpy(tmp_str21564, strvar);
      strcat(tmp_str21564, "[");
      int tmp_strlen21552 = strlen(tmp_str21564) + strlen(low_expr) + 1;
      char* tmp_str21552 = calloc(tmp_strlen21552, sizeof(char));
      strcpy(tmp_str21552, tmp_str21564);
      strcat(tmp_str21552, low_expr);
      int tmp_strlen21545 = strlen(tmp_str21552) + strlen("]") + 1;
      char* tmp_str21545 = calloc(tmp_strlen21545, sizeof(char));
      strcpy(tmp_str21545, tmp_str21552);
      strcat(tmp_str21545, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str21545};
    }
    ConsumeToken_results tmp_results21526 = ConsumeToken(src, TOK_COLON);
    src = tmp_results21526.result1;
    tok_str = tmp_results21526.result2;
    Peek_results tmp_results21474 = Peek(src);
    tok = tmp_results21474.result1;
    tok_str = tmp_results21474.result2;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results21404 = TranslateExpr(src, indent);
      src = tmp_results21404.result1;
      high_setup = tmp_results21404.result2;
      high_expr = tmp_results21404.result3;
    }
    ConsumeToken_results tmp_results21330 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results21330.result1;
    tok_str = tmp_results21330.result2;
  }
  int tmp_strlen21231 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str21231 = calloc(tmp_strlen21231, sizeof(char));
  strcpy(tmp_str21231, "tmp_str");
  strcat(tmp_str21231, itoa(p));
  char* tmp_str = tmp_str21231;
  int tmp_strlen21178 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str21178 = calloc(tmp_strlen21178, sizeof(char));
  strcpy(tmp_str21178, "tmp_strlen");
  strcat(tmp_str21178, itoa(p));
  char* tmp_strlen = tmp_str21178;
  int tmp_strlen21130 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str21130 = calloc(tmp_strlen21130, sizeof(char));
  strcpy(tmp_str21130, low_setup);
  strcat(tmp_str21130, high_setup);
  char* setup = tmp_str21130;
  int tmp_strlen21102 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str21102 = calloc(tmp_strlen21102, sizeof(char));
  strcpy(tmp_str21102, setup);
  strcat(tmp_str21102, indent);
  int tmp_strlen21092 = strlen(tmp_str21102) + strlen("int ") + 1;
  char* tmp_str21092 = calloc(tmp_strlen21092, sizeof(char));
  strcpy(tmp_str21092, tmp_str21102);
  strcat(tmp_str21092, "int ");
  int tmp_strlen21078 = strlen(tmp_str21092) + strlen(tmp_strlen) + 1;
  char* tmp_str21078 = calloc(tmp_strlen21078, sizeof(char));
  strcpy(tmp_str21078, tmp_str21092);
  strcat(tmp_str21078, tmp_strlen);
  int tmp_strlen21068 = strlen(tmp_str21078) + strlen(" = (") + 1;
  char* tmp_str21068 = calloc(tmp_strlen21068, sizeof(char));
  strcpy(tmp_str21068, tmp_str21078);
  strcat(tmp_str21068, " = (");
  int tmp_strlen21055 = strlen(tmp_str21068) + strlen(high_expr) + 1;
  char* tmp_str21055 = calloc(tmp_strlen21055, sizeof(char));
  strcpy(tmp_str21055, tmp_str21068);
  strcat(tmp_str21055, high_expr);
  int tmp_strlen21044 = strlen(tmp_str21055) + strlen(") - (") + 1;
  char* tmp_str21044 = calloc(tmp_strlen21044, sizeof(char));
  strcpy(tmp_str21044, tmp_str21055);
  strcat(tmp_str21044, ") - (");
  int tmp_strlen21032 = strlen(tmp_str21044) + strlen(low_expr) + 1;
  char* tmp_str21032 = calloc(tmp_strlen21032, sizeof(char));
  strcpy(tmp_str21032, tmp_str21044);
  strcat(tmp_str21032, low_expr);
  int tmp_strlen21018 = strlen(tmp_str21032) + strlen(") + 1;\n") + 1;
  char* tmp_str21018 = calloc(tmp_strlen21018, sizeof(char));
  strcpy(tmp_str21018, tmp_str21032);
  strcat(tmp_str21018, ") + 1;\n");
  setup = tmp_str21018;
  int tmp_strlen20990 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str20990 = calloc(tmp_strlen20990, sizeof(char));
  strcpy(tmp_str20990, setup);
  strcat(tmp_str20990, indent);
  int tmp_strlen20978 = strlen(tmp_str20990) + strlen("char* ") + 1;
  char* tmp_str20978 = calloc(tmp_strlen20978, sizeof(char));
  strcpy(tmp_str20978, tmp_str20990);
  strcat(tmp_str20978, "char* ");
  int tmp_strlen20967 = strlen(tmp_str20978) + strlen(tmp_str) + 1;
  char* tmp_str20967 = calloc(tmp_strlen20967, sizeof(char));
  strcpy(tmp_str20967, tmp_str20978);
  strcat(tmp_str20967, tmp_str);
  int tmp_strlen20951 = strlen(tmp_str20967) + strlen(" = calloc(") + 1;
  char* tmp_str20951 = calloc(tmp_strlen20951, sizeof(char));
  strcpy(tmp_str20951, tmp_str20967);
  strcat(tmp_str20951, " = calloc(");
  int tmp_strlen20937 = strlen(tmp_str20951) + strlen(tmp_strlen) + 1;
  char* tmp_str20937 = calloc(tmp_strlen20937, sizeof(char));
  strcpy(tmp_str20937, tmp_str20951);
  strcat(tmp_str20937, tmp_strlen);
  int tmp_strlen20913 = strlen(tmp_str20937) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str20913 = calloc(tmp_strlen20913, sizeof(char));
  strcpy(tmp_str20913, tmp_str20937);
  strcat(tmp_str20913, ", sizeof(char));\n");
  setup = tmp_str20913;
  int tmp_strlen20885 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str20885 = calloc(tmp_strlen20885, sizeof(char));
  strcpy(tmp_str20885, setup);
  strcat(tmp_str20885, indent);
  int tmp_strlen20871 = strlen(tmp_str20885) + strlen("strncpy(") + 1;
  char* tmp_str20871 = calloc(tmp_strlen20871, sizeof(char));
  strcpy(tmp_str20871, tmp_str20885);
  strcat(tmp_str20871, "strncpy(");
  int tmp_strlen20860 = strlen(tmp_str20871) + strlen(tmp_str) + 1;
  char* tmp_str20860 = calloc(tmp_strlen20860, sizeof(char));
  strcpy(tmp_str20860, tmp_str20871);
  strcat(tmp_str20860, tmp_str);
  int tmp_strlen20852 = strlen(tmp_str20860) + strlen(", ") + 1;
  char* tmp_str20852 = calloc(tmp_strlen20852, sizeof(char));
  strcpy(tmp_str20852, tmp_str20860);
  strcat(tmp_str20852, ", ");
  int tmp_strlen20842 = strlen(tmp_str20852) + strlen(strvar) + 1;
  char* tmp_str20842 = calloc(tmp_strlen20842, sizeof(char));
  strcpy(tmp_str20842, tmp_str20852);
  strcat(tmp_str20842, strvar);
  int tmp_strlen20833 = strlen(tmp_str20842) + strlen(" + ") + 1;
  char* tmp_str20833 = calloc(tmp_strlen20833, sizeof(char));
  strcpy(tmp_str20833, tmp_str20842);
  strcat(tmp_str20833, " + ");
  int tmp_strlen20821 = strlen(tmp_str20833) + strlen(low_expr) + 1;
  char* tmp_str20821 = calloc(tmp_strlen20821, sizeof(char));
  strcpy(tmp_str20821, tmp_str20833);
  strcat(tmp_str20821, low_expr);
  int tmp_strlen20813 = strlen(tmp_str20821) + strlen(", ") + 1;
  char* tmp_str20813 = calloc(tmp_strlen20813, sizeof(char));
  strcpy(tmp_str20813, tmp_str20821);
  strcat(tmp_str20813, ", ");
  int tmp_strlen20799 = strlen(tmp_str20813) + strlen(tmp_strlen) + 1;
  char* tmp_str20799 = calloc(tmp_strlen20799, sizeof(char));
  strcpy(tmp_str20799, tmp_str20813);
  strcat(tmp_str20799, tmp_strlen);
  int tmp_strlen20785 = strlen(tmp_str20799) + strlen(" - 1);\n") + 1;
  char* tmp_str20785 = calloc(tmp_strlen20785, sizeof(char));
  strcpy(tmp_str20785, tmp_str20799);
  strcat(tmp_str20785, " - 1);\n");
  setup = tmp_str20785;
  int tmp_strlen20757 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str20757 = calloc(tmp_strlen20757, sizeof(char));
  strcpy(tmp_str20757, setup);
  strcat(tmp_str20757, indent);
  int tmp_strlen20746 = strlen(tmp_str20757) + strlen(tmp_str) + 1;
  char* tmp_str20746 = calloc(tmp_strlen20746, sizeof(char));
  strcpy(tmp_str20746, tmp_str20757);
  strcat(tmp_str20746, tmp_str);
  int tmp_strlen20739 = strlen(tmp_str20746) + strlen("[") + 1;
  char* tmp_str20739 = calloc(tmp_strlen20739, sizeof(char));
  strcpy(tmp_str20739, tmp_str20746);
  strcat(tmp_str20739, "[");
  int tmp_strlen20725 = strlen(tmp_str20739) + strlen(tmp_strlen) + 1;
  char* tmp_str20725 = calloc(tmp_strlen20725, sizeof(char));
  strcpy(tmp_str20725, tmp_str20739);
  strcat(tmp_str20725, tmp_strlen);
  int tmp_strlen20707 = strlen(tmp_str20725) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str20707 = calloc(tmp_strlen20707, sizeof(char));
  strcpy(tmp_str20707, tmp_str20725);
  strcat(tmp_str20707, " - 1] = 0;\n");
  setup = tmp_str20707;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results20548 = Peek(src);
  tok = tmp_results20548.result1;
  tok_str = tmp_results20548.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results20438 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results20438.result1;
    tok_str = tmp_results20438.result2;
    TranslateExpr_results tmp_results20385 = TranslateExpr(src, indent);
    src = tmp_results20385.result1;
    setup = tmp_results20385.result2;
    val = tmp_results20385.result3;
    ConsumeToken_results tmp_results20332 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results20332.result1;
    tok_str = tmp_results20332.result2;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results20172 = TranslateBoolLiteral(src);
      src = tmp_results20172.result1;
      lit = tmp_results20172.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results20041 = TranslateIntLiteral(src);
        src = tmp_results20041.result1;
        lit = tmp_results20041.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results19911 = TranslateStringLiteral(src);
          src = tmp_results19911.result1;
          lit = tmp_results19911.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results19777 = ConsumeIdent(src);
            src = tmp_results19777.result1;
            ident = tmp_results19777.result2;
            Peek_results tmp_results19738 = Peek(src);
            tok = tmp_results19738.result1;
            tok_str = tmp_results19738.result2;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results19611 = TranslateCall(src, indent, ident);
              src = tmp_results19611.result1;
              setup = tmp_results19611.result2;
              expr = tmp_results19611.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results19411 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results19411.result1;
                setup = tmp_results19411.result2;
                expr = tmp_results19411.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen19191 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str19191 = calloc(tmp_strlen19191, sizeof(char));
            strcpy(tmp_str19191, "unexpected expr, got: ");
            strcat(tmp_str19191, itoa(tok));
            int tmp_strlen19182 = strlen(tmp_str19191) + strlen(" \"") + 1;
            char* tmp_str19182 = calloc(tmp_strlen19182, sizeof(char));
            strcpy(tmp_str19182, tmp_str19191);
            strcat(tmp_str19182, " \"");
            int tmp_strlen19171 = strlen(tmp_str19182) + strlen(tok_str) + 1;
            char* tmp_str19171 = calloc(tmp_strlen19171, sizeof(char));
            strcpy(tmp_str19171, tmp_str19182);
            strcat(tmp_str19171, tok_str);
            int tmp_strlen19163 = strlen(tmp_str19171) + strlen("\"") + 1;
            char* tmp_str19163 = calloc(tmp_strlen19163, sizeof(char));
            strcpy(tmp_str19163, tmp_str19171);
            strcat(tmp_str19163, "\"");
            printf("%s", tmp_str19163);
            exit(1);
          }
        }
      }
    }
  }
}

TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results19010 = Peek(src);
  tok = tmp_results19010.result1;
  tok_str = tmp_results19010.result2;
  if (IsUnaryOp(tok)) {
    ConsumeToken_results tmp_results18953 = ConsumeToken(src, tok);
    src = tmp_results18953.result1;
    tok_str = tmp_results18953.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results18857 = TranslateExpr(src, indent);
    src = tmp_results18857.result1;
    setup = tmp_results18857.result2;
    val = tmp_results18857.result3;
    int tmp_strlen18784 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str18784 = calloc(tmp_strlen18784, sizeof(char));
    strcpy(tmp_str18784, tok_str);
    strcat(tmp_str18784, "(");
    int tmp_strlen18777 = strlen(tmp_str18784) + strlen(val) + 1;
    char* tmp_str18777 = calloc(tmp_strlen18777, sizeof(char));
    strcpy(tmp_str18777, tmp_str18784);
    strcat(tmp_str18777, val);
    int tmp_strlen18770 = strlen(tmp_str18777) + strlen(")") + 1;
    char* tmp_str18770 = calloc(tmp_strlen18770, sizeof(char));
    strcpy(tmp_str18770, tmp_str18777);
    strcat(tmp_str18770, ")");
    val = tmp_str18770;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results18666 = TranslateOperand(src, indent);
    src = tmp_results18666.result1;
    setup = tmp_results18666.result2;
    expr = tmp_results18666.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results18423 = TranslateUnaryExpr(src, indent);
  src = tmp_results18423.result1;
  setup = tmp_results18423.result2;
  val = tmp_results18423.result3;
  int op;
  char* op_str;
  Peek_results tmp_results18330 = Peek(src);
  op = tmp_results18330.result1;
  op_str = tmp_results18330.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results18243 = ConsumeToken(src, op);
    src = tmp_results18243.result1;
    op_str = tmp_results18243.result2;
    int tok;
    char* tok_str;
    Peek_results tmp_results18150 = Peek(src);
    tok = tmp_results18150.result1;
    tok_str = tmp_results18150.result2;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results18080 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results18080.result1;
      tok_str = tmp_results18080.result2;
      Peek_results tmp_results18022 = Peek(src);
      tok = tmp_results18022.result1;
      tok_str = tmp_results18022.result2;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results17925 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results17925.result1;
    setup_b = tmp_results17925.result2;
    val_b = tmp_results17925.result3;
    int tmp_strlen17814 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str17814 = calloc(tmp_strlen17814, sizeof(char));
    strcpy(tmp_str17814, setup);
    strcat(tmp_str17814, setup_b);
    setup = tmp_str17814;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen17722 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str17722 = calloc(tmp_strlen17722, sizeof(char));
      strcpy(tmp_str17722, "tmp_str");
      strcat(tmp_str17722, itoa(strlen(src)));
      char* tmp_str = tmp_str17722;
      int tmp_strlen17654 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str17654 = calloc(tmp_strlen17654, sizeof(char));
      strcpy(tmp_str17654, "tmp_strlen");
      strcat(tmp_str17654, itoa(strlen(src)));
      char* tmp_strlen = tmp_str17654;
      int tmp_strlen17618 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str17618 = calloc(tmp_strlen17618, sizeof(char));
      strcpy(tmp_str17618, setup);
      strcat(tmp_str17618, indent);
      int tmp_strlen17608 = strlen(tmp_str17618) + strlen("int ") + 1;
      char* tmp_str17608 = calloc(tmp_strlen17608, sizeof(char));
      strcpy(tmp_str17608, tmp_str17618);
      strcat(tmp_str17608, "int ");
      int tmp_strlen17594 = strlen(tmp_str17608) + strlen(tmp_strlen) + 1;
      char* tmp_str17594 = calloc(tmp_strlen17594, sizeof(char));
      strcpy(tmp_str17594, tmp_str17608);
      strcat(tmp_str17594, tmp_strlen);
      int tmp_strlen17578 = strlen(tmp_str17594) + strlen(" = strlen(") + 1;
      char* tmp_str17578 = calloc(tmp_strlen17578, sizeof(char));
      strcpy(tmp_str17578, tmp_str17594);
      strcat(tmp_str17578, " = strlen(");
      int tmp_strlen17571 = strlen(tmp_str17578) + strlen(val) + 1;
      char* tmp_str17571 = calloc(tmp_strlen17571, sizeof(char));
      strcpy(tmp_str17571, tmp_str17578);
      strcat(tmp_str17571, val);
      int tmp_strlen17554 = strlen(tmp_str17571) + strlen(") + strlen(") + 1;
      char* tmp_str17554 = calloc(tmp_strlen17554, sizeof(char));
      strcpy(tmp_str17554, tmp_str17571);
      strcat(tmp_str17554, ") + strlen(");
      int tmp_strlen17545 = strlen(tmp_str17554) + strlen(val_b) + 1;
      char* tmp_str17545 = calloc(tmp_strlen17545, sizeof(char));
      strcpy(tmp_str17545, tmp_str17554);
      strcat(tmp_str17545, val_b);
      int tmp_strlen17531 = strlen(tmp_str17545) + strlen(") + 1;\n") + 1;
      char* tmp_str17531 = calloc(tmp_strlen17531, sizeof(char));
      strcpy(tmp_str17531, tmp_str17545);
      strcat(tmp_str17531, ") + 1;\n");
      setup = tmp_str17531;
      int tmp_strlen17495 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str17495 = calloc(tmp_strlen17495, sizeof(char));
      strcpy(tmp_str17495, setup);
      strcat(tmp_str17495, indent);
      int tmp_strlen17483 = strlen(tmp_str17495) + strlen("char* ") + 1;
      char* tmp_str17483 = calloc(tmp_strlen17483, sizeof(char));
      strcpy(tmp_str17483, tmp_str17495);
      strcat(tmp_str17483, "char* ");
      int tmp_strlen17472 = strlen(tmp_str17483) + strlen(tmp_str) + 1;
      char* tmp_str17472 = calloc(tmp_strlen17472, sizeof(char));
      strcpy(tmp_str17472, tmp_str17483);
      strcat(tmp_str17472, tmp_str);
      int tmp_strlen17456 = strlen(tmp_str17472) + strlen(" = calloc(") + 1;
      char* tmp_str17456 = calloc(tmp_strlen17456, sizeof(char));
      strcpy(tmp_str17456, tmp_str17472);
      strcat(tmp_str17456, " = calloc(");
      int tmp_strlen17442 = strlen(tmp_str17456) + strlen(tmp_strlen) + 1;
      char* tmp_str17442 = calloc(tmp_strlen17442, sizeof(char));
      strcpy(tmp_str17442, tmp_str17456);
      strcat(tmp_str17442, tmp_strlen);
      int tmp_strlen17418 = strlen(tmp_str17442) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str17418 = calloc(tmp_strlen17418, sizeof(char));
      strcpy(tmp_str17418, tmp_str17442);
      strcat(tmp_str17418, ", sizeof(char));\n");
      setup = tmp_str17418;
      int tmp_strlen17382 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str17382 = calloc(tmp_strlen17382, sizeof(char));
      strcpy(tmp_str17382, setup);
      strcat(tmp_str17382, indent);
      int tmp_strlen17369 = strlen(tmp_str17382) + strlen("strcpy(") + 1;
      char* tmp_str17369 = calloc(tmp_strlen17369, sizeof(char));
      strcpy(tmp_str17369, tmp_str17382);
      strcat(tmp_str17369, "strcpy(");
      int tmp_strlen17358 = strlen(tmp_str17369) + strlen(tmp_str) + 1;
      char* tmp_str17358 = calloc(tmp_strlen17358, sizeof(char));
      strcpy(tmp_str17358, tmp_str17369);
      strcat(tmp_str17358, tmp_str);
      int tmp_strlen17350 = strlen(tmp_str17358) + strlen(", ") + 1;
      char* tmp_str17350 = calloc(tmp_strlen17350, sizeof(char));
      strcpy(tmp_str17350, tmp_str17358);
      strcat(tmp_str17350, ", ");
      int tmp_strlen17343 = strlen(tmp_str17350) + strlen(val) + 1;
      char* tmp_str17343 = calloc(tmp_strlen17343, sizeof(char));
      strcpy(tmp_str17343, tmp_str17350);
      strcat(tmp_str17343, val);
      int tmp_strlen17333 = strlen(tmp_str17343) + strlen(");\n") + 1;
      char* tmp_str17333 = calloc(tmp_strlen17333, sizeof(char));
      strcpy(tmp_str17333, tmp_str17343);
      strcat(tmp_str17333, ");\n");
      setup = tmp_str17333;
      int tmp_strlen17297 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str17297 = calloc(tmp_strlen17297, sizeof(char));
      strcpy(tmp_str17297, setup);
      strcat(tmp_str17297, indent);
      int tmp_strlen17284 = strlen(tmp_str17297) + strlen("strcat(") + 1;
      char* tmp_str17284 = calloc(tmp_strlen17284, sizeof(char));
      strcpy(tmp_str17284, tmp_str17297);
      strcat(tmp_str17284, "strcat(");
      int tmp_strlen17273 = strlen(tmp_str17284) + strlen(tmp_str) + 1;
      char* tmp_str17273 = calloc(tmp_strlen17273, sizeof(char));
      strcpy(tmp_str17273, tmp_str17284);
      strcat(tmp_str17273, tmp_str);
      int tmp_strlen17265 = strlen(tmp_str17273) + strlen(", ") + 1;
      char* tmp_str17265 = calloc(tmp_strlen17265, sizeof(char));
      strcpy(tmp_str17265, tmp_str17273);
      strcat(tmp_str17265, ", ");
      int tmp_strlen17256 = strlen(tmp_str17265) + strlen(val_b) + 1;
      char* tmp_str17256 = calloc(tmp_strlen17256, sizeof(char));
      strcpy(tmp_str17256, tmp_str17265);
      strcat(tmp_str17256, val_b);
      int tmp_strlen17246 = strlen(tmp_str17256) + strlen(");\n") + 1;
      char* tmp_str17246 = calloc(tmp_strlen17246, sizeof(char));
      strcpy(tmp_str17246, tmp_str17256);
      strcat(tmp_str17246, ");\n");
      setup = tmp_str17246;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen17148 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str17148 = calloc(tmp_strlen17148, sizeof(char));
        strcpy(tmp_str17148, "(strcmp(");
        strcat(tmp_str17148, val);
        int tmp_strlen17140 = strlen(tmp_str17148) + strlen(", ") + 1;
        char* tmp_str17140 = calloc(tmp_strlen17140, sizeof(char));
        strcpy(tmp_str17140, tmp_str17148);
        strcat(tmp_str17140, ", ");
        int tmp_strlen17131 = strlen(tmp_str17140) + strlen(val_b) + 1;
        char* tmp_str17131 = calloc(tmp_strlen17131, sizeof(char));
        strcpy(tmp_str17131, tmp_str17140);
        strcat(tmp_str17131, val_b);
        int tmp_strlen17118 = strlen(tmp_str17131) + strlen(") == 0)") + 1;
        char* tmp_str17118 = calloc(tmp_strlen17118, sizeof(char));
        strcpy(tmp_str17118, tmp_str17131);
        strcat(tmp_str17118, ") == 0)");
        val = tmp_str17118;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen17045 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str17045 = calloc(tmp_strlen17045, sizeof(char));
          strcpy(tmp_str17045, "(strcmp(");
          strcat(tmp_str17045, val);
          int tmp_strlen17037 = strlen(tmp_str17045) + strlen(", ") + 1;
          char* tmp_str17037 = calloc(tmp_strlen17037, sizeof(char));
          strcpy(tmp_str17037, tmp_str17045);
          strcat(tmp_str17037, ", ");
          int tmp_strlen17028 = strlen(tmp_str17037) + strlen(val_b) + 1;
          char* tmp_str17028 = calloc(tmp_strlen17028, sizeof(char));
          strcpy(tmp_str17028, tmp_str17037);
          strcat(tmp_str17028, val_b);
          int tmp_strlen17015 = strlen(tmp_str17028) + strlen(") != 0)") + 1;
          char* tmp_str17015 = calloc(tmp_strlen17015, sizeof(char));
          strcpy(tmp_str17015, tmp_str17028);
          strcat(tmp_str17015, ") != 0)");
          val = tmp_str17015;
        } else {
          int tmp_strlen16969 = strlen("(") + strlen(val) + 1;
          char* tmp_str16969 = calloc(tmp_strlen16969, sizeof(char));
          strcpy(tmp_str16969, "(");
          strcat(tmp_str16969, val);
          int tmp_strlen16961 = strlen(tmp_str16969) + strlen(") ") + 1;
          char* tmp_str16961 = calloc(tmp_strlen16961, sizeof(char));
          strcpy(tmp_str16961, tmp_str16969);
          strcat(tmp_str16961, ") ");
          int tmp_strlen16951 = strlen(tmp_str16961) + strlen(op_str) + 1;
          char* tmp_str16951 = calloc(tmp_strlen16951, sizeof(char));
          strcpy(tmp_str16951, tmp_str16961);
          strcat(tmp_str16951, op_str);
          int tmp_strlen16943 = strlen(tmp_str16951) + strlen(" (") + 1;
          char* tmp_str16943 = calloc(tmp_strlen16943, sizeof(char));
          strcpy(tmp_str16943, tmp_str16951);
          strcat(tmp_str16943, " (");
          int tmp_strlen16934 = strlen(tmp_str16943) + strlen(val_b) + 1;
          char* tmp_str16934 = calloc(tmp_strlen16934, sizeof(char));
          strcpy(tmp_str16934, tmp_str16943);
          strcat(tmp_str16934, val_b);
          int tmp_strlen16927 = strlen(tmp_str16934) + strlen(")") + 1;
          char* tmp_str16927 = calloc(tmp_strlen16927, sizeof(char));
          strcpy(tmp_str16927, tmp_str16934);
          strcat(tmp_str16927, ")");
          val = tmp_str16927;
        }
      }
    }
    Peek_results tmp_results16908 = Peek(src);
    op = tmp_results16908.result1;
    tok_str = tmp_results16908.result2;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results16725 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results16725.result1;
  setup = tmp_results16725.result2;
  expr = tmp_results16725.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results16491 = TranslateExpr(src, indent);
  src = tmp_results16491.result1;
  expr_setup = tmp_results16491.result2;
  expr_value = tmp_results16491.result3;
  int tok;
  char* tok_str;
  Peek_results tmp_results16389 = Peek(src);
  tok = tmp_results16389.result1;
  tok_str = tmp_results16389.result2;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results16218 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results16218.result1;
    tok_str = tmp_results16218.result2;
    TranslateExpr_results tmp_results16166 = TranslateExpr(src, indent);
    src = tmp_results16166.result1;
    expr_setup = tmp_results16166.result2;
    expr_value = tmp_results16166.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen16024 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str16024 = calloc(tmp_strlen16024, sizeof(char));
    strcpy(tmp_str16024, exprs_setup);
    strcat(tmp_str16024, expr_setup);
    exprs_setup = tmp_str16024;
    int tmp_strlen15982 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str15982 = calloc(tmp_strlen15982, sizeof(char));
    strcpy(tmp_str15982, exprs_value);
    strcat(tmp_str15982, ", ");
    int tmp_strlen15968 = strlen(tmp_str15982) + strlen(expr_value) + 1;
    char* tmp_str15968 = calloc(tmp_strlen15968, sizeof(char));
    strcpy(tmp_str15968, tmp_str15982);
    strcat(tmp_str15968, expr_value);
    exprs_value = tmp_str15968;
    Peek_results tmp_results15959 = Peek(src);
    tok = tmp_results15959.result1;
    tok_str = tmp_results15959.result2;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results15788 = ConsumeIdent(src);
  src = tmp_results15788.result1;
  name = tmp_results15788.result2;
  char* tok_str;
  ConsumeToken_results tmp_results15730 = ConsumeToken(src, TOK_COLON);
  src = tmp_results15730.result1;
  tok_str = tmp_results15730.result2;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results15641 = TranslateType(src);
  src = tmp_results15641.result1;
  typ = tmp_results15641.result2;
  typ_str = tmp_results15641.result3;
  int tmp_strlen15566 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str15566 = calloc(tmp_strlen15566, sizeof(char));
  strcpy(tmp_str15566, typ_str);
  strcat(tmp_str15566, " ");
  int tmp_strlen15558 = strlen(tmp_str15566) + strlen(name) + 1;
  char* tmp_str15558 = calloc(tmp_strlen15558, sizeof(char));
  strcpy(tmp_str15558, tmp_str15566);
  strcat(tmp_str15558, name);
  char* out = tmp_str15558;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results15433 = ConsumeToken(src, TOK_LET);
  src = tmp_results15433.result1;
  tok_str = tmp_results15433.result2;
  char* out;
  TranslateConstOrVar_results tmp_results15367 = TranslateConstOrVar(src);
  src = tmp_results15367.result1;
  out = tmp_results15367.result2;
  int tmp_strlen15306 = strlen("const ") + strlen(out) + 1;
  char* tmp_str15306 = calloc(tmp_strlen15306, sizeof(char));
  strcpy(tmp_str15306, "const ");
  strcat(tmp_str15306, out);
  out = tmp_str15306;
  ConsumeToken_results tmp_results15301 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results15301.result1;
  tok_str = tmp_results15301.result2;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results15210 = TranslateExpr(src, indent);
  src = tmp_results15210.result1;
  setup = tmp_results15210.result2;
  val = tmp_results15210.result3;
  ConsumeToken_results tmp_results15161 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results15161.result1;
  tok_str = tmp_results15161.result2;
  int tmp_strlen15093 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str15093 = calloc(tmp_strlen15093, sizeof(char));
  strcpy(tmp_str15093, out);
  strcat(tmp_str15093, " = ");
  int tmp_strlen15086 = strlen(tmp_str15093) + strlen(val) + 1;
  char* tmp_str15086 = calloc(tmp_strlen15086, sizeof(char));
  strcpy(tmp_str15086, tmp_str15093);
  strcat(tmp_str15086, val);
  int tmp_strlen15077 = strlen(tmp_str15086) + strlen(";\n") + 1;
  char* tmp_str15077 = calloc(tmp_strlen15077, sizeof(char));
  strcpy(tmp_str15077, tmp_str15086);
  strcat(tmp_str15077, ";\n");
  out = tmp_str15077;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results14952 = TranslateConstDecl(src, indent);
  src = tmp_results14952.result1;
  out = tmp_results14952.result2;
  int tmp_strlen14880 = strlen(indent) + strlen(out) + 1;
  char* tmp_str14880 = calloc(tmp_strlen14880, sizeof(char));
  strcpy(tmp_str14880, indent);
  strcat(tmp_str14880, out);
  return (TranslateConstDeclStmt_results){src, tmp_str14880};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results14756 = ConsumeToken(src, TOK_VAR);
  src = tmp_results14756.result1;
  tok_str = tmp_results14756.result2;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results14643 = TranslateConstOrVar(src);
  src = tmp_results14643.result1;
  out = tmp_results14643.result2;
  Peek_results tmp_results14603 = Peek(src);
  tok = tmp_results14603.result1;
  tok_str = tmp_results14603.result2;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results14543 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results14543.result1;
    tok_str = tmp_results14543.result2;
    TranslateExpr_results tmp_results14490 = TranslateExpr(src, indent);
    src = tmp_results14490.result1;
    setup = tmp_results14490.result2;
    val = tmp_results14490.result3;
    ConsumeToken_results tmp_results14437 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results14437.result1;
    tok_str = tmp_results14437.result2;
    int tmp_strlen14365 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str14365 = calloc(tmp_strlen14365, sizeof(char));
    strcpy(tmp_str14365, out);
    strcat(tmp_str14365, " = ");
    int tmp_strlen14358 = strlen(tmp_str14365) + strlen(val) + 1;
    char* tmp_str14358 = calloc(tmp_strlen14358, sizeof(char));
    strcpy(tmp_str14358, tmp_str14365);
    strcat(tmp_str14358, val);
    out = tmp_str14358;
  }
  int tmp_strlen14326 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str14326 = calloc(tmp_strlen14326, sizeof(char));
  strcpy(tmp_str14326, setup);
  strcat(tmp_str14326, indent);
  int tmp_strlen14319 = strlen(tmp_str14326) + strlen(out) + 1;
  char* tmp_str14319 = calloc(tmp_strlen14319, sizeof(char));
  strcpy(tmp_str14319, tmp_str14326);
  strcat(tmp_str14319, out);
  int tmp_strlen14310 = strlen(tmp_str14319) + strlen(";\n") + 1;
  char* tmp_str14310 = calloc(tmp_strlen14310, sizeof(char));
  strcpy(tmp_str14310, tmp_str14319);
  strcat(tmp_str14310, ";\n");
  out = tmp_str14310;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen14155 = (x) - (0) + 1;
  char* tmp_str14155 = calloc(tmp_strlen14155, sizeof(char));
  strncpy(tmp_str14155, src + 0, tmp_strlen14155 - 1);
  tmp_str14155[tmp_strlen14155 - 1] = 0;
  char* lhs = tmp_str14155;
  int tmp_strlen14125 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str14125 = calloc(tmp_strlen14125, sizeof(char));
  strncpy(tmp_str14125, src + (x) + (1), tmp_strlen14125 - 1);
  tmp_str14125[tmp_strlen14125 - 1] = 0;
  char* rhs = tmp_str14125;
  char* lhs_ident;
  ConsumeIdent_results tmp_results14088 = ConsumeIdent(lhs);
  lhs = tmp_results14088.result1;
  lhs_ident = tmp_results14088.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results13972 = TranslateExpr(rhs, indent);
  rhs = tmp_results13972.result1;
  setup = tmp_results13972.result2;
  rhs_expr = tmp_results13972.result3;
  int lhs_tok;
  char* lhs_tok_str;
  int rhs_tok;
  char* rhs_tok_str;
  Peek_results tmp_results13820 = Peek(lhs);
  lhs_tok = tmp_results13820.result1;
  lhs_tok_str = tmp_results13820.result2;
  Peek_results tmp_results13783 = Peek(rhs);
  rhs_tok = tmp_results13783.result1;
  rhs_tok_str = tmp_results13783.result2;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results13658 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results13658.result1;
    func_name = tmp_results13658.result2;
    int tmp_strlen13550 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str13550 = calloc(tmp_strlen13550, sizeof(char));
    strcpy(tmp_str13550, "tmp_results");
    strcat(tmp_str13550, itoa(strlen(src)));
    char* tmp_results = tmp_str13550;
    char* out = setup;
    int tmp_strlen13490 = strlen(out) + strlen(indent) + 1;
    char* tmp_str13490 = calloc(tmp_strlen13490, sizeof(char));
    strcpy(tmp_str13490, out);
    strcat(tmp_str13490, indent);
    int tmp_strlen13477 = strlen(tmp_str13490) + strlen(func_name) + 1;
    char* tmp_str13477 = calloc(tmp_strlen13477, sizeof(char));
    strcpy(tmp_str13477, tmp_str13490);
    strcat(tmp_str13477, func_name);
    int tmp_strlen13462 = strlen(tmp_str13477) + strlen("_results ") + 1;
    char* tmp_str13462 = calloc(tmp_strlen13462, sizeof(char));
    strcpy(tmp_str13462, tmp_str13477);
    strcat(tmp_str13462, "_results ");
    int tmp_strlen13447 = strlen(tmp_str13462) + strlen(tmp_results) + 1;
    char* tmp_str13447 = calloc(tmp_strlen13447, sizeof(char));
    strcpy(tmp_str13447, tmp_str13462);
    strcat(tmp_str13447, tmp_results);
    int tmp_strlen13438 = strlen(tmp_str13447) + strlen(" = ") + 1;
    char* tmp_str13438 = calloc(tmp_strlen13438, sizeof(char));
    strcpy(tmp_str13438, tmp_str13447);
    strcat(tmp_str13438, " = ");
    int tmp_strlen13426 = strlen(tmp_str13438) + strlen(rhs_expr) + 1;
    char* tmp_str13426 = calloc(tmp_strlen13426, sizeof(char));
    strcpy(tmp_str13426, tmp_str13438);
    strcat(tmp_str13426, rhs_expr);
    int tmp_strlen13417 = strlen(tmp_str13426) + strlen(";\n") + 1;
    char* tmp_str13417 = calloc(tmp_strlen13417, sizeof(char));
    strcpy(tmp_str13417, tmp_str13426);
    strcat(tmp_str13417, ";\n");
    out = tmp_str13417;
    int tmp_strlen13389 = strlen(out) + strlen(indent) + 1;
    char* tmp_str13389 = calloc(tmp_strlen13389, sizeof(char));
    strcpy(tmp_str13389, out);
    strcat(tmp_str13389, indent);
    int tmp_strlen13376 = strlen(tmp_str13389) + strlen(lhs_ident) + 1;
    char* tmp_str13376 = calloc(tmp_strlen13376, sizeof(char));
    strcpy(tmp_str13376, tmp_str13389);
    strcat(tmp_str13376, lhs_ident);
    int tmp_strlen13367 = strlen(tmp_str13376) + strlen(" = ") + 1;
    char* tmp_str13367 = calloc(tmp_strlen13367, sizeof(char));
    strcpy(tmp_str13367, tmp_str13376);
    strcat(tmp_str13367, " = ");
    int tmp_strlen13352 = strlen(tmp_str13367) + strlen(tmp_results) + 1;
    char* tmp_str13352 = calloc(tmp_strlen13352, sizeof(char));
    strcpy(tmp_str13352, tmp_str13367);
    strcat(tmp_str13352, tmp_results);
    int tmp_strlen13335 = strlen(tmp_str13352) + strlen(".result1;\n") + 1;
    char* tmp_str13335 = calloc(tmp_strlen13335, sizeof(char));
    strcpy(tmp_str13335, tmp_str13352);
    strcat(tmp_str13335, ".result1;\n");
    out = tmp_str13335;
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results13209 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results13209.result1;
      lhs_tok_str = tmp_results13209.result2;
      ConsumeIdent_results tmp_results13149 = ConsumeIdent(lhs);
      lhs = tmp_results13149.result1;
      lhs_ident = tmp_results13149.result2;
      int tmp_strlen13083 = strlen(out) + strlen(indent) + 1;
      char* tmp_str13083 = calloc(tmp_strlen13083, sizeof(char));
      strcpy(tmp_str13083, out);
      strcat(tmp_str13083, indent);
      int tmp_strlen13070 = strlen(tmp_str13083) + strlen(lhs_ident) + 1;
      char* tmp_str13070 = calloc(tmp_strlen13070, sizeof(char));
      strcpy(tmp_str13070, tmp_str13083);
      strcat(tmp_str13070, lhs_ident);
      int tmp_strlen13061 = strlen(tmp_str13070) + strlen(" = ") + 1;
      char* tmp_str13061 = calloc(tmp_strlen13061, sizeof(char));
      strcpy(tmp_str13061, tmp_str13070);
      strcat(tmp_str13061, " = ");
      int tmp_strlen13046 = strlen(tmp_str13061) + strlen(tmp_results) + 1;
      char* tmp_str13046 = calloc(tmp_strlen13046, sizeof(char));
      strcpy(tmp_str13046, tmp_str13061);
      strcat(tmp_str13046, tmp_results);
      int tmp_strlen13033 = strlen(tmp_str13046) + strlen(".result") + 1;
      char* tmp_str13033 = calloc(tmp_strlen13033, sizeof(char));
      strcpy(tmp_str13033, tmp_str13046);
      strcat(tmp_str13033, ".result");
      int tmp_strlen13011 = strlen(tmp_str13033) + strlen(itoa(result_count)) + 1;
      char* tmp_str13011 = calloc(tmp_strlen13011, sizeof(char));
      strcpy(tmp_str13011, tmp_str13033);
      strcat(tmp_str13011, itoa(result_count));
      int tmp_strlen13002 = strlen(tmp_str13011) + strlen(";\n") + 1;
      char* tmp_str13002 = calloc(tmp_strlen13002, sizeof(char));
      strcpy(tmp_str13002, tmp_str13011);
      strcat(tmp_str13002, ";\n");
      out = tmp_str13002;
      Peek_results tmp_results12989 = Peek(lhs);
      lhs_tok = tmp_results12989.result1;
      lhs_tok_str = tmp_results12989.result2;
    }
    char* tok_str;
    ConsumeToken_results tmp_results12910 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results12910.result1;
    tok_str = tmp_results12910.result2;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen12785 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str12785 = calloc(tmp_strlen12785, sizeof(char));
  strcpy(tmp_str12785, indent);
  strcat(tmp_str12785, lhs_ident);
  int tmp_strlen12776 = strlen(tmp_str12785) + strlen(" = ") + 1;
  char* tmp_str12776 = calloc(tmp_strlen12776, sizeof(char));
  strcpy(tmp_str12776, tmp_str12785);
  strcat(tmp_str12776, " = ");
  int tmp_strlen12764 = strlen(tmp_str12776) + strlen(rhs_expr) + 1;
  char* tmp_str12764 = calloc(tmp_strlen12764, sizeof(char));
  strcpy(tmp_str12764, tmp_str12776);
  strcat(tmp_str12764, rhs_expr);
  int tmp_strlen12755 = strlen(tmp_str12764) + strlen(";\n") + 1;
  char* tmp_str12755 = calloc(tmp_strlen12755, sizeof(char));
  strcpy(tmp_str12755, tmp_str12764);
  strcat(tmp_str12755, ";\n");
  char* assignments = tmp_str12755;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results12715 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results12715.result1;
    lhs_tok_str = tmp_results12715.result2;
    ConsumeToken_results tmp_results12659 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results12659.result1;
    rhs_tok_str = tmp_results12659.result2;
    ConsumeIdent_results tmp_results12603 = ConsumeIdent(lhs);
    lhs = tmp_results12603.result1;
    lhs_ident = tmp_results12603.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results12525 = TranslateExpr(rhs, indent);
    rhs = tmp_results12525.result1;
    rhs_expr_setup = tmp_results12525.result2;
    rhs_expr = tmp_results12525.result3;
    int tmp_strlen12427 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str12427 = calloc(tmp_strlen12427, sizeof(char));
    strcpy(tmp_str12427, setup);
    strcat(tmp_str12427, rhs_expr_setup);
    setup = tmp_str12427;
    int tmp_strlen12383 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str12383 = calloc(tmp_strlen12383, sizeof(char));
    strcpy(tmp_str12383, assignments);
    strcat(tmp_str12383, indent);
    int tmp_strlen12370 = strlen(tmp_str12383) + strlen(lhs_ident) + 1;
    char* tmp_str12370 = calloc(tmp_strlen12370, sizeof(char));
    strcpy(tmp_str12370, tmp_str12383);
    strcat(tmp_str12370, lhs_ident);
    int tmp_strlen12361 = strlen(tmp_str12370) + strlen(" = ") + 1;
    char* tmp_str12361 = calloc(tmp_strlen12361, sizeof(char));
    strcpy(tmp_str12361, tmp_str12370);
    strcat(tmp_str12361, " = ");
    int tmp_strlen12349 = strlen(tmp_str12361) + strlen(rhs_expr) + 1;
    char* tmp_str12349 = calloc(tmp_strlen12349, sizeof(char));
    strcpy(tmp_str12349, tmp_str12361);
    strcat(tmp_str12349, rhs_expr);
    int tmp_strlen12340 = strlen(tmp_str12349) + strlen(";\n") + 1;
    char* tmp_str12340 = calloc(tmp_strlen12340, sizeof(char));
    strcpy(tmp_str12340, tmp_str12349);
    strcat(tmp_str12340, ";\n");
    assignments = tmp_str12340;
    Peek_results tmp_results12331 = Peek(lhs);
    lhs_tok = tmp_results12331.result1;
    lhs_tok_str = tmp_results12331.result2;
  }
  char* tok_str;
  ConsumeToken_results tmp_results12264 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results12264.result1;
  tok_str = tmp_results12264.result2;
  int tmp_strlen12182 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str12182 = calloc(tmp_strlen12182, sizeof(char));
  strcpy(tmp_str12182, setup);
  strcat(tmp_str12182, assignments);
  return (TranslateAssignStmt_results){src, tmp_str12182};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results12061 = ConsumeToken(src, TOK_IF);
  src = tmp_results12061.result1;
  tok_str = tmp_results12061.result2;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results11968 = TranslateExpr(src, indent);
  src = tmp_results11968.result1;
  cond_setup = tmp_results11968.result2;
  cond = tmp_results11968.result3;
  ConsumeToken_results tmp_results11913 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results11913.result1;
  tok_str = tmp_results11913.result2;
  char* out = cond_setup;
  int tmp_strlen11812 = strlen(out) + strlen(indent) + 1;
  char* tmp_str11812 = calloc(tmp_strlen11812, sizeof(char));
  strcpy(tmp_str11812, out);
  strcat(tmp_str11812, indent);
  int tmp_strlen11802 = strlen(tmp_str11812) + strlen("if (") + 1;
  char* tmp_str11802 = calloc(tmp_strlen11802, sizeof(char));
  strcpy(tmp_str11802, tmp_str11812);
  strcat(tmp_str11802, "if (");
  int tmp_strlen11794 = strlen(tmp_str11802) + strlen(cond) + 1;
  char* tmp_str11794 = calloc(tmp_strlen11794, sizeof(char));
  strcpy(tmp_str11794, tmp_str11802);
  strcat(tmp_str11794, cond);
  int tmp_strlen11783 = strlen(tmp_str11794) + strlen(") {\n") + 1;
  char* tmp_str11783 = calloc(tmp_strlen11783, sizeof(char));
  strcpy(tmp_str11783, tmp_str11794);
  strcat(tmp_str11783, ") {\n");
  out = tmp_str11783;
  char* body;
  int tmp_strlen11702 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str11702 = calloc(tmp_strlen11702, sizeof(char));
  strcpy(tmp_str11702, indent);
  strcat(tmp_str11702, SINGLE_INDENT);
  TranslateStmts_results tmp_results11757 = TranslateStmts(src, tmp_str11702, func_name);
  src = tmp_results11757.result1;
  body = tmp_results11757.result2;
  ConsumeToken_results tmp_results11685 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results11685.result1;
  tok_str = tmp_results11685.result2;
  int tmp_strlen11619 = strlen(out) + strlen(body) + 1;
  char* tmp_str11619 = calloc(tmp_strlen11619, sizeof(char));
  strcpy(tmp_str11619, out);
  strcat(tmp_str11619, body);
  out = tmp_str11619;
  int tmp_strlen11595 = strlen(out) + strlen(indent) + 1;
  char* tmp_str11595 = calloc(tmp_strlen11595, sizeof(char));
  strcpy(tmp_str11595, out);
  strcat(tmp_str11595, indent);
  int tmp_strlen11588 = strlen(tmp_str11595) + strlen("}") + 1;
  char* tmp_str11588 = calloc(tmp_strlen11588, sizeof(char));
  strcpy(tmp_str11588, tmp_str11595);
  strcat(tmp_str11588, "}");
  out = tmp_str11588;
  int tok;
  Peek_results tmp_results11566 = Peek(src);
  tok = tmp_results11566.result1;
  tok_str = tmp_results11566.result2;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen11485 = strlen(out) + strlen("\n") + 1;
    char* tmp_str11485 = calloc(tmp_strlen11485, sizeof(char));
    strcpy(tmp_str11485, out);
    strcat(tmp_str11485, "\n");
    return (TranslateIfStmt_results){src, tmp_str11485};
  }
  ConsumeToken_results tmp_results11474 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results11474.result1;
  tok_str = tmp_results11474.result2;
  Peek_results tmp_results11427 = Peek(src);
  tok = tmp_results11427.result1;
  tok_str = tmp_results11427.result2;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen11286 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str11286 = calloc(tmp_strlen11286, sizeof(char));
    strcpy(tmp_str11286, indent);
    strcat(tmp_str11286, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results11346 = TranslateIfStmt(src, tmp_str11286, func_name);
    src = tmp_results11346.result1;
    else_out = tmp_results11346.result2;
    int tmp_strlen11241 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str11241 = calloc(tmp_strlen11241, sizeof(char));
    strcpy(tmp_str11241, out);
    strcat(tmp_str11241, " else {\n");
    out = tmp_str11241;
    int tmp_strlen11211 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str11211 = calloc(tmp_strlen11211, sizeof(char));
    strcpy(tmp_str11211, out);
    strcat(tmp_str11211, else_out);
    out = tmp_str11211;
    int tmp_strlen11183 = strlen(out) + strlen(indent) + 1;
    char* tmp_str11183 = calloc(tmp_strlen11183, sizeof(char));
    strcpy(tmp_str11183, out);
    strcat(tmp_str11183, indent);
    int tmp_strlen11174 = strlen(tmp_str11183) + strlen("}\n") + 1;
    char* tmp_str11174 = calloc(tmp_strlen11174, sizeof(char));
    strcpy(tmp_str11174, tmp_str11183);
    strcat(tmp_str11174, "}\n");
    out = tmp_str11174;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results11139 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results11139.result1;
  tok_str = tmp_results11139.result2;
  int tmp_strlen11031 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str11031 = calloc(tmp_strlen11031, sizeof(char));
  strcpy(tmp_str11031, indent);
  strcat(tmp_str11031, SINGLE_INDENT);
  TranslateStmts_results tmp_results11090 = TranslateStmts(src, tmp_str11031, func_name);
  src = tmp_results11090.result1;
  else_out = tmp_results11090.result2;
  ConsumeToken_results tmp_results11014 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results11014.result1;
  tok_str = tmp_results11014.result2;
  int tmp_strlen10941 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str10941 = calloc(tmp_strlen10941, sizeof(char));
  strcpy(tmp_str10941, out);
  strcat(tmp_str10941, " else {\n");
  out = tmp_str10941;
  int tmp_strlen10915 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str10915 = calloc(tmp_strlen10915, sizeof(char));
  strcpy(tmp_str10915, out);
  strcat(tmp_str10915, else_out);
  out = tmp_str10915;
  int tmp_strlen10891 = strlen(out) + strlen(indent) + 1;
  char* tmp_str10891 = calloc(tmp_strlen10891, sizeof(char));
  strcpy(tmp_str10891, out);
  strcat(tmp_str10891, indent);
  int tmp_strlen10882 = strlen(tmp_str10891) + strlen("}\n") + 1;
  char* tmp_str10882 = calloc(tmp_strlen10882, sizeof(char));
  strcpy(tmp_str10882, tmp_str10891);
  strcat(tmp_str10882, "}\n");
  out = tmp_str10882;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results10723 = ConsumeToken(src, TOK_FOR);
  src = tmp_results10723.result1;
  tok_str = tmp_results10723.result2;
  Peek_results tmp_results10677 = Peek(src);
  tok = tmp_results10677.result1;
  tok_str = tmp_results10677.result2;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen10489 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str10489 = calloc(tmp_strlen10489, sizeof(char));
    strcpy(tmp_str10489, indent);
    strcat(tmp_str10489, SINGLE_INDENT);
    TranslateExpr_results tmp_results10555 = TranslateExpr(src, tmp_str10489);
    src = tmp_results10555.result1;
    cond_setup = tmp_results10555.result2;
    cond = tmp_results10555.result3;
  }
  ConsumeToken_results tmp_results10477 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results10477.result1;
  tok_str = tmp_results10477.result2;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen10353 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str10353 = calloc(tmp_strlen10353, sizeof(char));
    strcpy(tmp_str10353, indent);
    strcat(tmp_str10353, "while (");
    int tmp_strlen10345 = strlen(tmp_str10353) + strlen(cond) + 1;
    char* tmp_str10345 = calloc(tmp_strlen10345, sizeof(char));
    strcpy(tmp_str10345, tmp_str10353);
    strcat(tmp_str10345, cond);
    int tmp_strlen10334 = strlen(tmp_str10345) + strlen(") {\n") + 1;
    char* tmp_str10334 = calloc(tmp_strlen10334, sizeof(char));
    strcpy(tmp_str10334, tmp_str10345);
    strcat(tmp_str10334, ") {\n");
    out = tmp_str10334;
  } else {
    int tmp_strlen10278 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str10278 = calloc(tmp_strlen10278, sizeof(char));
    strcpy(tmp_str10278, indent);
    strcat(tmp_str10278, "while (true) {\n");
    out = tmp_str10278;
    int tmp_strlen10246 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str10246 = calloc(tmp_strlen10246, sizeof(char));
    strcpy(tmp_str10246, out);
    strcat(tmp_str10246, cond_setup);
    out = tmp_str10246;
    int tmp_strlen10218 = strlen(out) + strlen(indent) + 1;
    char* tmp_str10218 = calloc(tmp_strlen10218, sizeof(char));
    strcpy(tmp_str10218, out);
    strcat(tmp_str10218, indent);
    int tmp_strlen10201 = strlen(tmp_str10218) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str10201 = calloc(tmp_strlen10201, sizeof(char));
    strcpy(tmp_str10201, tmp_str10218);
    strcat(tmp_str10201, SINGLE_INDENT);
    int tmp_strlen10189 = strlen(tmp_str10201) + strlen("if (!(") + 1;
    char* tmp_str10189 = calloc(tmp_strlen10189, sizeof(char));
    strcpy(tmp_str10189, tmp_str10201);
    strcat(tmp_str10189, "if (!(");
    int tmp_strlen10181 = strlen(tmp_str10189) + strlen(cond) + 1;
    char* tmp_str10181 = calloc(tmp_strlen10181, sizeof(char));
    strcpy(tmp_str10181, tmp_str10189);
    strcat(tmp_str10181, cond);
    int tmp_strlen10164 = strlen(tmp_str10181) + strlen(")) break;\n") + 1;
    char* tmp_str10164 = calloc(tmp_strlen10164, sizeof(char));
    strcpy(tmp_str10164, tmp_str10181);
    strcat(tmp_str10164, ")) break;\n");
    out = tmp_str10164;
  }
  char* body;
  int tmp_strlen10077 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str10077 = calloc(tmp_strlen10077, sizeof(char));
  strcpy(tmp_str10077, indent);
  strcat(tmp_str10077, SINGLE_INDENT);
  TranslateStmts_results tmp_results10132 = TranslateStmts(src, tmp_str10077, func_name);
  src = tmp_results10132.result1;
  body = tmp_results10132.result2;
  ConsumeToken_results tmp_results10060 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results10060.result1;
  tok_str = tmp_results10060.result2;
  int tmp_strlen9994 = strlen(out) + strlen(body) + 1;
  char* tmp_str9994 = calloc(tmp_strlen9994, sizeof(char));
  strcpy(tmp_str9994, out);
  strcat(tmp_str9994, body);
  out = tmp_str9994;
  int tmp_strlen9970 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9970 = calloc(tmp_strlen9970, sizeof(char));
  strcpy(tmp_str9970, out);
  strcat(tmp_str9970, indent);
  int tmp_strlen9961 = strlen(tmp_str9970) + strlen("}\n") + 1;
  char* tmp_str9961 = calloc(tmp_strlen9961, sizeof(char));
  strcpy(tmp_str9961, tmp_str9970);
  strcat(tmp_str9961, "}\n");
  out = tmp_str9961;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results9833 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results9833.result1;
  tok_str = tmp_results9833.result2;
  int tmp_strlen9749 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str9749 = calloc(tmp_strlen9749, sizeof(char));
  strcpy(tmp_str9749, indent);
  strcat(tmp_str9749, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str9749};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results9644 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results9644.result1;
  tok_str = tmp_results9644.result2;
  int tmp_strlen9566 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str9566 = calloc(tmp_strlen9566, sizeof(char));
  strcpy(tmp_str9566, indent);
  strcat(tmp_str9566, "break;");
  return (TranslateBreakStmt_results){src, tmp_str9566};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results9441 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results9441.result1;
  tok_str = tmp_results9441.result2;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results9312 = TranslateExprs(src, indent);
  src = tmp_results9312.result1;
  expr_count = tmp_results9312.result2;
  exprs_setup = tmp_results9312.result3;
  exprs_value = tmp_results9312.result4;
  ConsumeToken_results tmp_results9236 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results9236.result1;
  tok_str = tmp_results9236.result2;
  int tmp_strlen9147 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str9147 = calloc(tmp_strlen9147, sizeof(char));
  strcpy(tmp_str9147, exprs_setup);
  strcat(tmp_str9147, indent);
  int tmp_strlen9134 = strlen(tmp_str9147) + strlen("return ") + 1;
  char* tmp_str9134 = calloc(tmp_strlen9134, sizeof(char));
  strcpy(tmp_str9134, tmp_str9147);
  strcat(tmp_str9134, "return ");
  char* out = tmp_str9134;
  if ((expr_count) > (1)) {
    int tmp_strlen9085 = strlen(out) + strlen("(") + 1;
    char* tmp_str9085 = calloc(tmp_strlen9085, sizeof(char));
    strcpy(tmp_str9085, out);
    strcat(tmp_str9085, "(");
    int tmp_strlen9072 = strlen(tmp_str9085) + strlen(func_name) + 1;
    char* tmp_str9072 = calloc(tmp_strlen9072, sizeof(char));
    strcpy(tmp_str9072, tmp_str9085);
    strcat(tmp_str9072, func_name);
    int tmp_strlen9056 = strlen(tmp_str9072) + strlen("_results){") + 1;
    char* tmp_str9056 = calloc(tmp_strlen9056, sizeof(char));
    strcpy(tmp_str9056, tmp_str9072);
    strcat(tmp_str9056, "_results){");
    out = tmp_str9056;
  }
  int tmp_strlen9021 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str9021 = calloc(tmp_strlen9021, sizeof(char));
  strcpy(tmp_str9021, out);
  strcat(tmp_str9021, exprs_value);
  out = tmp_str9021;
  if ((expr_count) > (1)) {
    int tmp_strlen8971 = strlen(out) + strlen("}") + 1;
    char* tmp_str8971 = calloc(tmp_strlen8971, sizeof(char));
    strcpy(tmp_str8971, out);
    strcat(tmp_str8971, "}");
    out = tmp_str8971;
  }
  int tmp_strlen8942 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str8942 = calloc(tmp_strlen8942, sizeof(char));
  strcpy(tmp_str8942, out);
  strcat(tmp_str8942, ";\n");
  out = tmp_str8942;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results8786 = Peek(src);
  tok = tmp_results8786.result1;
  tok_str = tmp_results8786.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results8709 = TranslateConstDeclStmt(src, indent);
    src = tmp_results8709.result1;
    out = tmp_results8709.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results8599 = TranslateVarDeclStmt(src, indent);
      src = tmp_results8599.result1;
      out = tmp_results8599.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results8492 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results8492.result1;
        out = tmp_results8492.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results8378 = TranslateForStmt(src, indent, func_name);
          src = tmp_results8378.result1;
          out = tmp_results8378.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results8258 = TranslateContinueStmt(src, indent);
            src = tmp_results8258.result1;
            out = tmp_results8258.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results8147 = TranslateBreakStmt(src, indent);
              src = tmp_results8147.result1;
              out = tmp_results8147.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results8038 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results8038.result1;
                out = tmp_results8038.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if ((tok) == (TOK_IDENT)) {
                  char* first_ident;
                  ConsumeIdent_results tmp_results7886 = ConsumeIdent(src);
                  src = tmp_results7886.result1;
                  first_ident = tmp_results7886.result2;
                  Peek_results tmp_results7841 = Peek(src);
                  tok = tmp_results7841.result1;
                  tok_str = tmp_results7841.result2;
                  int tmp_strlen7784 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str7784 = calloc(tmp_strlen7784, sizeof(char));
                  strcpy(tmp_str7784, first_ident);
                  strcat(tmp_str7784, src);
                  src = tmp_str7784;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results7720 = TranslateAssignStmt(src, indent);
                    src = tmp_results7720.result1;
                    out = tmp_results7720.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results7561 = TranslateExpr(src, indent);
                    src = tmp_results7561.result1;
                    setup = tmp_results7561.result2;
                    val = tmp_results7561.result3;
                    ConsumeToken_results tmp_results7504 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results7504.result1;
                    tok_str = tmp_results7504.result2;
                    int tmp_strlen7425 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str7425 = calloc(tmp_strlen7425, sizeof(char));
                    strcpy(tmp_str7425, setup);
                    strcat(tmp_str7425, indent);
                    int tmp_strlen7418 = strlen(tmp_str7425) + strlen(val) + 1;
                    char* tmp_str7418 = calloc(tmp_strlen7418, sizeof(char));
                    strcpy(tmp_str7418, tmp_str7425);
                    strcat(tmp_str7418, val);
                    int tmp_strlen7409 = strlen(tmp_str7418) + strlen(";\n") + 1;
                    char* tmp_str7409 = calloc(tmp_strlen7409, sizeof(char));
                    strcpy(tmp_str7409, tmp_str7418);
                    strcat(tmp_str7409, ";\n");
                    out = tmp_str7409;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen7300 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str7300 = calloc(tmp_strlen7300, sizeof(char));
                  strcpy(tmp_str7300, "unexpected stmt token, got: ");
                  strcat(tmp_str7300, itoa(tok));
                  int tmp_strlen7291 = strlen(tmp_str7300) + strlen(" \"") + 1;
                  char* tmp_str7291 = calloc(tmp_strlen7291, sizeof(char));
                  strcpy(tmp_str7291, tmp_str7300);
                  strcat(tmp_str7291, " \"");
                  int tmp_strlen7280 = strlen(tmp_str7291) + strlen(tok_str) + 1;
                  char* tmp_str7280 = calloc(tmp_strlen7280, sizeof(char));
                  strcpy(tmp_str7280, tmp_str7291);
                  strcat(tmp_str7280, tok_str);
                  int tmp_strlen7272 = strlen(tmp_str7280) + strlen("\"") + 1;
                  char* tmp_str7272 = calloc(tmp_strlen7272, sizeof(char));
                  strcpy(tmp_str7272, tmp_str7280);
                  strcat(tmp_str7272, "\"");
                  printf("%s", tmp_str7272);
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
  char* tok_str;
  Peek_results tmp_results7112 = Peek(src);
  tok = tmp_results7112.result1;
  tok_str = tmp_results7112.result2;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results6990 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results6990.result1;
      tok_str = tmp_results6990.result2;
      Peek_results tmp_results6932 = Peek(src);
      tok = tmp_results6932.result1;
      tok_str = tmp_results6932.result2;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results6839 = TranslateStmt(src, indent, func_name);
    src = tmp_results6839.result1;
    stmt_out = tmp_results6839.result2;
    int tmp_strlen6756 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str6756 = calloc(tmp_strlen6756, sizeof(char));
    strcpy(tmp_str6756, out);
    strcat(tmp_str6756, stmt_out);
    out = tmp_str6756;
    Peek_results tmp_results6747 = Peek(src);
    tok = tmp_results6747.result1;
    tok_str = tmp_results6747.result2;
  }
  return (TranslateStmts_results){src, out};
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results6592 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results6592.result1;
  tok_str = tmp_results6592.result2;
  Peek_results tmp_results6543 = Peek(src);
  tok = tmp_results6543.result1;
  tok_str = tmp_results6543.result2;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results6483 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results6483.result1;
    tok_str = tmp_results6483.result2;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results6382 = TranslateConstOrVar(src);
  src = tmp_results6382.result1;
  args = tmp_results6382.result2;
  Peek_results tmp_results6341 = Peek(src);
  tok = tmp_results6341.result1;
  tok_str = tmp_results6341.result2;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results6281 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results6281.result1;
    tok_str = tmp_results6281.result2;
    char* arg;
    TranslateConstOrVar_results tmp_results6205 = TranslateConstOrVar(src);
    src = tmp_results6205.result1;
    arg = tmp_results6205.result2;
    int tmp_strlen6142 = strlen(args) + strlen(", ") + 1;
    char* tmp_str6142 = calloc(tmp_strlen6142, sizeof(char));
    strcpy(tmp_str6142, args);
    strcat(tmp_str6142, ", ");
    int tmp_strlen6135 = strlen(tmp_str6142) + strlen(arg) + 1;
    char* tmp_str6135 = calloc(tmp_strlen6135, sizeof(char));
    strcpy(tmp_str6135, tmp_str6142);
    strcat(tmp_str6135, arg);
    args = tmp_str6135;
    Peek_results tmp_results6126 = Peek(src);
    tok = tmp_results6126.result1;
    tok_str = tmp_results6126.result2;
  }
  ConsumeToken_results tmp_results6091 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results6091.result1;
  tok_str = tmp_results6091.result2;
  int tmp_strlen6019 = strlen("(") + strlen(args) + 1;
  char* tmp_str6019 = calloc(tmp_strlen6019, sizeof(char));
  strcpy(tmp_str6019, "(");
  strcat(tmp_str6019, args);
  int tmp_strlen6012 = strlen(tmp_str6019) + strlen(")") + 1;
  char* tmp_str6012 = calloc(tmp_strlen6012, sizeof(char));
  strcpy(tmp_str6012, tmp_str6019);
  strcat(tmp_str6012, ")");
  return (TranslateFuncArgs_results){src, tmp_str6012};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  char* tok_str;
  Peek_results tmp_results5836 = Peek(src);
  tok = tmp_results5836.result1;
  tok_str = tmp_results5836.result2;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results5776 = TranslateType(src);
    src = tmp_results5776.result1;
    typ = tmp_results5776.result2;
    typ_str = tmp_results5776.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results5695 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results5695.result1;
  tok_str = tmp_results5695.result2;
  TranslateType_results tmp_results5646 = TranslateType(src);
  src = tmp_results5646.result1;
  typ = tmp_results5646.result2;
  typ_str = tmp_results5646.result3;
  Peek_results tmp_results5603 = Peek(src);
  tok = tmp_results5603.result1;
  tok_str = tmp_results5603.result2;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results5544 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results5544.result1;
    tok_str = tmp_results5544.result2;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen5403 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str5403 = calloc(tmp_strlen5403, sizeof(char));
  strcpy(tmp_str5403, "typedef struct {\n");
  strcat(tmp_str5403, SINGLE_INDENT);
  int tmp_strlen5392 = strlen(tmp_str5403) + strlen(typ_str) + 1;
  char* tmp_str5392 = calloc(tmp_strlen5392, sizeof(char));
  strcpy(tmp_str5392, tmp_str5403);
  strcat(tmp_str5392, typ_str);
  int tmp_strlen5375 = strlen(tmp_str5392) + strlen(" result1;\n") + 1;
  char* tmp_str5375 = calloc(tmp_strlen5375, sizeof(char));
  strcpy(tmp_str5375, tmp_str5392);
  strcat(tmp_str5375, " result1;\n");
  char* td = tmp_str5375;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results5312 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results5312.result1;
    tok_str = tmp_results5312.result2;
    TranslateType_results tmp_results5260 = TranslateType(src);
    src = tmp_results5260.result1;
    typ = tmp_results5260.result2;
    typ_str = tmp_results5260.result3;
    res_count = (res_count) + (1);
    int tmp_strlen5155 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str5155 = calloc(tmp_strlen5155, sizeof(char));
    strcpy(tmp_str5155, td);
    strcat(tmp_str5155, SINGLE_INDENT);
    int tmp_strlen5144 = strlen(tmp_str5155) + strlen(typ_str) + 1;
    char* tmp_str5144 = calloc(tmp_strlen5144, sizeof(char));
    strcpy(tmp_str5144, tmp_str5155);
    strcat(tmp_str5144, typ_str);
    int tmp_strlen5131 = strlen(tmp_str5144) + strlen(" result") + 1;
    char* tmp_str5131 = calloc(tmp_strlen5131, sizeof(char));
    strcpy(tmp_str5131, tmp_str5144);
    strcat(tmp_str5131, " result");
    int tmp_strlen5112 = strlen(tmp_str5131) + strlen(itoa(res_count)) + 1;
    char* tmp_str5112 = calloc(tmp_strlen5112, sizeof(char));
    strcpy(tmp_str5112, tmp_str5131);
    strcat(tmp_str5112, itoa(res_count));
    int tmp_strlen5103 = strlen(tmp_str5112) + strlen(";\n") + 1;
    char* tmp_str5103 = calloc(tmp_strlen5103, sizeof(char));
    strcpy(tmp_str5103, tmp_str5112);
    strcat(tmp_str5103, ";\n");
    td = tmp_str5103;
    Peek_results tmp_results5094 = Peek(src);
    tok = tmp_results5094.result1;
    tok_str = tmp_results5094.result2;
  }
  ConsumeToken_results tmp_results5059 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results5059.result1;
  tok_str = tmp_results5059.result2;
  int tmp_strlen4995 = strlen(td) + strlen("} ") + 1;
  char* tmp_str4995 = calloc(tmp_strlen4995, sizeof(char));
  strcpy(tmp_str4995, td);
  strcat(tmp_str4995, "} ");
  int tmp_strlen4982 = strlen(tmp_str4995) + strlen(func_name) + 1;
  char* tmp_str4982 = calloc(tmp_strlen4982, sizeof(char));
  strcpy(tmp_str4982, tmp_str4995);
  strcat(tmp_str4982, func_name);
  int tmp_strlen4965 = strlen(tmp_str4982) + strlen("_results;\n") + 1;
  char* tmp_str4965 = calloc(tmp_strlen4965, sizeof(char));
  strcpy(tmp_str4965, tmp_str4982);
  strcat(tmp_str4965, "_results;\n");
  td = tmp_str4965;
  int tmp_strlen4921 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str4921 = calloc(tmp_strlen4921, sizeof(char));
  strcpy(tmp_str4921, func_name);
  strcat(tmp_str4921, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str4921};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* tok_str;
  char* name;
  ConsumeToken_results tmp_results4791 = ConsumeToken(src, TOK_FN);
  src = tmp_results4791.result1;
  tok_str = tmp_results4791.result2;
  ConsumeIdent_results tmp_results4746 = ConsumeIdent(src);
  src = tmp_results4746.result1;
  name = tmp_results4746.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  }
  Peek_results tmp_results4486 = Peek(src);
  tok = tmp_results4486.result1;
  tok_str = tmp_results4486.result2;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results4426 = TranslateFuncArgs(src);
    src = tmp_results4426.result1;
    args = tmp_results4426.result2;
    Peek_results tmp_results4383 = Peek(src);
    tok = tmp_results4383.result1;
    tok_str = tmp_results4383.result2;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results4315 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results4315.result1;
      tok_str = tmp_results4315.result2;
      TranslateFuncResults_results tmp_results4258 = TranslateFuncResults(src, name);
      src = tmp_results4258.result1;
      results_type_def = tmp_results4258.result2;
      results_type_name = tmp_results4258.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results4137 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results4137.result1;
  tok_str = tmp_results4137.result2;
  int tmp_strlen4032 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str4032 = calloc(tmp_strlen4032, sizeof(char));
  strcpy(tmp_str4032, SINGLE_INDENT);
  strcat(tmp_str4032, "");
  TranslateStmts_results tmp_results4088 = TranslateStmts(src, tmp_str4032, name);
  src = tmp_results4088.result1;
  stmts_out = tmp_results4088.result2;
  ConsumeToken_results tmp_results4020 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results4020.result1;
  tok_str = tmp_results4020.result2;
  int tmp_strlen3930 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str3930 = calloc(tmp_strlen3930, sizeof(char));
  strcpy(tmp_str3930, results_type_name);
  strcat(tmp_str3930, " ");
  int tmp_strlen3922 = strlen(tmp_str3930) + strlen(name) + 1;
  char* tmp_str3922 = calloc(tmp_strlen3922, sizeof(char));
  strcpy(tmp_str3922, tmp_str3930);
  strcat(tmp_str3922, name);
  int tmp_strlen3914 = strlen(tmp_str3922) + strlen(args) + 1;
  char* tmp_str3914 = calloc(tmp_strlen3914, sizeof(char));
  strcpy(tmp_str3914, tmp_str3922);
  strcat(tmp_str3914, args);
  char* df = tmp_str3914;
  int tmp_strlen3868 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str3868 = calloc(tmp_strlen3868, sizeof(char));
  strcpy(tmp_str3868, results_type_def);
  strcat(tmp_str3868, df);
  int tmp_strlen3859 = strlen(tmp_str3868) + strlen(";\n") + 1;
  char* tmp_str3859 = calloc(tmp_strlen3859, sizeof(char));
  strcpy(tmp_str3859, tmp_str3868);
  strcat(tmp_str3859, ";\n");
  char* decl = tmp_str3859;
  int tmp_strlen3837 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str3837 = calloc(tmp_strlen3837, sizeof(char));
  strcpy(tmp_str3837, df);
  strcat(tmp_str3837, " {\n");
  df = tmp_str3837;
  int tmp_strlen3812 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str3812 = calloc(tmp_strlen3812, sizeof(char));
  strcpy(tmp_str3812, df);
  strcat(tmp_str3812, stmts_out);
  df = tmp_str3812;
  if ((strcmp(name, "_main") == 0)) {
    int tmp_strlen3752 = strlen(df) + strlen("  return 0;\n") + 1;
    char* tmp_str3752 = calloc(tmp_strlen3752, sizeof(char));
    strcpy(tmp_str3752, df);
    strcat(tmp_str3752, "  return 0;\n");
    df = tmp_str3752;
  }
  int tmp_strlen3723 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str3723 = calloc(tmp_strlen3723, sizeof(char));
  strcpy(tmp_str3723, df);
  strcat(tmp_str3723, "}\n\n");
  df = tmp_str3723;
  return (TranslateFunc_results){src, decl, df};
}

char* TranslateProgram(char* src) {
  char* out = "";
  int tmp_strlen3583 = strlen(out) + strlen("#include <stdbool.h>\n") + 1;
  char* tmp_str3583 = calloc(tmp_strlen3583, sizeof(char));
  strcpy(tmp_str3583, out);
  strcat(tmp_str3583, "#include <stdbool.h>\n");
  out = tmp_str3583;
  int tmp_strlen3543 = strlen(out) + strlen("#include <stdio.h>\n") + 1;
  char* tmp_str3543 = calloc(tmp_strlen3543, sizeof(char));
  strcpy(tmp_str3543, out);
  strcat(tmp_str3543, "#include <stdio.h>\n");
  out = tmp_str3543;
  int tmp_strlen3502 = strlen(out) + strlen("#include <stdlib.h>\n") + 1;
  char* tmp_str3502 = calloc(tmp_strlen3502, sizeof(char));
  strcpy(tmp_str3502, out);
  strcat(tmp_str3502, "#include <stdlib.h>\n");
  out = tmp_str3502;
  int tmp_strlen3461 = strlen(out) + strlen("#include <string.h>\n") + 1;
  char* tmp_str3461 = calloc(tmp_strlen3461, sizeof(char));
  strcpy(tmp_str3461, out);
  strcat(tmp_str3461, "#include <string.h>\n");
  out = tmp_str3461;
  int tmp_strlen3439 = strlen(out) + strlen("\n") + 1;
  char* tmp_str3439 = calloc(tmp_strlen3439, sizeof(char));
  strcpy(tmp_str3439, out);
  strcat(tmp_str3439, "\n");
  out = tmp_str3439;
  int tmp_strlen3398 = strlen(out) + strlen("char* itoa(int x) {\n") + 1;
  char* tmp_str3398 = calloc(tmp_strlen3398, sizeof(char));
  strcpy(tmp_str3398, out);
  strcat(tmp_str3398, "char* itoa(int x) {\n");
  out = tmp_str3398;
  int tmp_strlen3353 = strlen(out) + strlen("  char* a = malloc(20);\n") + 1;
  char* tmp_str3353 = calloc(tmp_strlen3353, sizeof(char));
  strcpy(tmp_str3353, out);
  strcat(tmp_str3353, "  char* a = malloc(20);\n");
  out = tmp_str3353;
  int tmp_strlen3307 = strlen(out) + strlen("  sprintf(a, \"%i\", x);\n") + 1;
  char* tmp_str3307 = calloc(tmp_strlen3307, sizeof(char));
  strcpy(tmp_str3307, out);
  strcat(tmp_str3307, "  sprintf(a, \"%i\", x);\n");
  out = tmp_str3307;
  int tmp_strlen3274 = strlen(out) + strlen("  return a;\n") + 1;
  char* tmp_str3274 = calloc(tmp_strlen3274, sizeof(char));
  strcpy(tmp_str3274, out);
  strcat(tmp_str3274, "  return a;\n");
  out = tmp_str3274;
  int tmp_strlen3251 = strlen(out) + strlen("}\n") + 1;
  char* tmp_str3251 = calloc(tmp_strlen3251, sizeof(char));
  strcpy(tmp_str3251, out);
  strcat(tmp_str3251, "}\n");
  out = tmp_str3251;
  int tmp_strlen3229 = strlen(out) + strlen("\n") + 1;
  char* tmp_str3229 = calloc(tmp_strlen3229, sizeof(char));
  strcpy(tmp_str3229, out);
  strcat(tmp_str3229, "\n");
  out = tmp_str3229;
  int tmp_strlen3177 = strlen(out) + strlen("char* read(const char* path) {\n") + 1;
  char* tmp_str3177 = calloc(tmp_strlen3177, sizeof(char));
  strcpy(tmp_str3177, out);
  strcat(tmp_str3177, "char* read(const char* path) {\n");
  out = tmp_str3177;
  int tmp_strlen3123 = strlen(out) + strlen("  FILE* f = fopen(path, \"rb\");\n") + 1;
  char* tmp_str3123 = calloc(tmp_strlen3123, sizeof(char));
  strcpy(tmp_str3123, out);
  strcat(tmp_str3123, "  FILE* f = fopen(path, \"rb\");\n");
  out = tmp_str3123;
  int tmp_strlen3083 = strlen(out) + strlen("  if (f == NULL) {\n") + 1;
  char* tmp_str3083 = calloc(tmp_strlen3083, sizeof(char));
  strcpy(tmp_str3083, out);
  strcat(tmp_str3083, "  if (f == NULL) {\n");
  out = tmp_str3083;
  int tmp_strlen3012 = strlen(out) + strlen("    printf(\"could not open file: %s\\n\", path);\n") + 1;
  char* tmp_str3012 = calloc(tmp_strlen3012, sizeof(char));
  strcpy(tmp_str3012, out);
  strcat(tmp_str3012, "    printf(\"could not open file: %s\\n\", path);\n");
  out = tmp_str3012;
  int tmp_strlen2978 = strlen(out) + strlen("    exit(1);\n") + 1;
  char* tmp_str2978 = calloc(tmp_strlen2978, sizeof(char));
  strcpy(tmp_str2978, out);
  strcat(tmp_str2978, "    exit(1);\n");
  out = tmp_str2978;
  int tmp_strlen2953 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str2953 = calloc(tmp_strlen2953, sizeof(char));
  strcpy(tmp_str2953, out);
  strcat(tmp_str2953, "  }\n");
  out = tmp_str2953;
  int tmp_strlen2907 = strlen(out) + strlen("  fseek(f, 0, SEEK_END);\n") + 1;
  char* tmp_str2907 = calloc(tmp_strlen2907, sizeof(char));
  strcpy(tmp_str2907, out);
  strcat(tmp_str2907, "  fseek(f, 0, SEEK_END);\n");
  out = tmp_str2907;
  int tmp_strlen2861 = strlen(out) + strlen("  int length = ftell(f);\n") + 1;
  char* tmp_str2861 = calloc(tmp_strlen2861, sizeof(char));
  strcpy(tmp_str2861, out);
  strcat(tmp_str2861, "  int length = ftell(f);\n");
  out = tmp_str2861;
  int tmp_strlen2809 = strlen(out) + strlen("  char* text = malloc(length);\n") + 1;
  char* tmp_str2809 = calloc(tmp_strlen2809, sizeof(char));
  strcpy(tmp_str2809, out);
  strcat(tmp_str2809, "  char* text = malloc(length);\n");
  out = tmp_str2809;
  int tmp_strlen2763 = strlen(out) + strlen("  fseek(f, 0, SEEK_SET);\n") + 1;
  char* tmp_str2763 = calloc(tmp_strlen2763, sizeof(char));
  strcpy(tmp_str2763, out);
  strcat(tmp_str2763, "  fseek(f, 0, SEEK_SET);\n");
  out = tmp_str2763;
  int tmp_strlen2713 = strlen(out) + strlen("  fread(text, 1, length, f);\n") + 1;
  char* tmp_str2713 = calloc(tmp_strlen2713, sizeof(char));
  strcpy(tmp_str2713, out);
  strcat(tmp_str2713, "  fread(text, 1, length, f);\n");
  out = tmp_str2713;
  int tmp_strlen2679 = strlen(out) + strlen("  fclose(f);\n") + 1;
  char* tmp_str2679 = calloc(tmp_strlen2679, sizeof(char));
  strcpy(tmp_str2679, out);
  strcat(tmp_str2679, "  fclose(f);\n");
  out = tmp_str2679;
  int tmp_strlen2643 = strlen(out) + strlen("  return text;\n") + 1;
  char* tmp_str2643 = calloc(tmp_strlen2643, sizeof(char));
  strcpy(tmp_str2643, out);
  strcat(tmp_str2643, "  return text;\n");
  out = tmp_str2643;
  int tmp_strlen2620 = strlen(out) + strlen("}\n") + 1;
  char* tmp_str2620 = calloc(tmp_strlen2620, sizeof(char));
  strcpy(tmp_str2620, out);
  strcat(tmp_str2620, "}\n");
  out = tmp_str2620;
  int tmp_strlen2598 = strlen(out) + strlen("\n") + 1;
  char* tmp_str2598 = calloc(tmp_strlen2598, sizeof(char));
  strcpy(tmp_str2598, out);
  strcat(tmp_str2598, "\n");
  out = tmp_str2598;
  int tmp_strlen2528 = strlen(out) + strlen("void write(const char* path, const char* text) {\n") + 1;
  char* tmp_str2528 = calloc(tmp_strlen2528, sizeof(char));
  strcpy(tmp_str2528, out);
  strcat(tmp_str2528, "void write(const char* path, const char* text) {\n");
  out = tmp_str2528;
  int tmp_strlen2475 = strlen(out) + strlen("  FILE *f = fopen(path, \"w\");\n") + 1;
  char* tmp_str2475 = calloc(tmp_strlen2475, sizeof(char));
  strcpy(tmp_str2475, out);
  strcat(tmp_str2475, "  FILE *f = fopen(path, \"w\");\n");
  out = tmp_str2475;
  int tmp_strlen2435 = strlen(out) + strlen("  if (f == NULL) {\n") + 1;
  char* tmp_str2435 = calloc(tmp_strlen2435, sizeof(char));
  strcpy(tmp_str2435, out);
  strcat(tmp_str2435, "  if (f == NULL) {\n");
  out = tmp_str2435;
  int tmp_strlen2364 = strlen(out) + strlen("    printf(\"could not open file: %s\\n\", path);\n") + 1;
  char* tmp_str2364 = calloc(tmp_strlen2364, sizeof(char));
  strcpy(tmp_str2364, out);
  strcat(tmp_str2364, "    printf(\"could not open file: %s\\n\", path);\n");
  out = tmp_str2364;
  int tmp_strlen2330 = strlen(out) + strlen("    exit(1);\n") + 1;
  char* tmp_str2330 = calloc(tmp_strlen2330, sizeof(char));
  strcpy(tmp_str2330, out);
  strcat(tmp_str2330, "    exit(1);\n");
  out = tmp_str2330;
  int tmp_strlen2305 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str2305 = calloc(tmp_strlen2305, sizeof(char));
  strcpy(tmp_str2305, out);
  strcat(tmp_str2305, "  }\n");
  out = tmp_str2305;
  int tmp_strlen2256 = strlen(out) + strlen("  fprintf(f, \"%s\", text);\n") + 1;
  char* tmp_str2256 = calloc(tmp_strlen2256, sizeof(char));
  strcpy(tmp_str2256, out);
  strcat(tmp_str2256, "  fprintf(f, \"%s\", text);\n");
  out = tmp_str2256;
  int tmp_strlen2222 = strlen(out) + strlen("  fclose(f);\n") + 1;
  char* tmp_str2222 = calloc(tmp_strlen2222, sizeof(char));
  strcpy(tmp_str2222, out);
  strcat(tmp_str2222, "  fclose(f);\n");
  out = tmp_str2222;
  int tmp_strlen2199 = strlen(out) + strlen("}\n") + 1;
  char* tmp_str2199 = calloc(tmp_strlen2199, sizeof(char));
  strcpy(tmp_str2199, out);
  strcat(tmp_str2199, "}\n");
  out = tmp_str2199;
  int tmp_strlen2177 = strlen(out) + strlen("\n") + 1;
  char* tmp_str2177 = calloc(tmp_strlen2177, sizeof(char));
  strcpy(tmp_str2177, out);
  strcat(tmp_str2177, "\n");
  out = tmp_str2177;
  int tmp_strlen2133 = strlen(out) + strlen("int _main(char* args);\n") + 1;
  char* tmp_str2133 = calloc(tmp_strlen2133, sizeof(char));
  strcpy(tmp_str2133, out);
  strcat(tmp_str2133, "int _main(char* args);\n");
  out = tmp_str2133;
  int tmp_strlen2111 = strlen(out) + strlen("\n") + 1;
  char* tmp_str2111 = calloc(tmp_strlen2111, sizeof(char));
  strcpy(tmp_str2111, out);
  strcat(tmp_str2111, "\n");
  out = tmp_str2111;
  int tmp_strlen2056 = strlen(out) + strlen("int main(int argc, char **argv) {\n") + 1;
  char* tmp_str2056 = calloc(tmp_strlen2056, sizeof(char));
  strcpy(tmp_str2056, out);
  strcat(tmp_str2056, "int main(int argc, char **argv) {\n");
  out = tmp_str2056;
  int tmp_strlen2022 = strlen(out) + strlen("  int l = 0;\n") + 1;
  char* tmp_str2022 = calloc(tmp_strlen2022, sizeof(char));
  strcpy(tmp_str2022, out);
  strcat(tmp_str2022, "  int l = 0;\n");
  out = tmp_str2022;
  int tmp_strlen1966 = strlen(out) + strlen("  for (int i = 1; i < argc; i++) {\n") + 1;
  char* tmp_str1966 = calloc(tmp_strlen1966, sizeof(char));
  strcpy(tmp_str1966, out);
  strcat(tmp_str1966, "  for (int i = 1; i < argc; i++) {\n");
  out = tmp_str1966;
  int tmp_strlen1915 = strlen(out) + strlen("    l += strlen(argv[i]) + 1;\n") + 1;
  char* tmp_str1915 = calloc(tmp_strlen1915, sizeof(char));
  strcpy(tmp_str1915, out);
  strcat(tmp_str1915, "    l += strlen(argv[i]) + 1;\n");
  out = tmp_str1915;
  int tmp_strlen1890 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str1890 = calloc(tmp_strlen1890, sizeof(char));
  strcpy(tmp_str1890, out);
  strcat(tmp_str1890, "  }\n");
  out = tmp_str1890;
  int tmp_strlen1829 = strlen(out) + strlen("  char* args = calloc(l, sizeof(char));\n") + 1;
  char* tmp_str1829 = calloc(tmp_strlen1829, sizeof(char));
  strcpy(tmp_str1829, out);
  strcat(tmp_str1829, "  char* args = calloc(l, sizeof(char));\n");
  out = tmp_str1829;
  int tmp_strlen1790 = strlen(out) + strlen("  char* a = args;\n") + 1;
  char* tmp_str1790 = calloc(tmp_strlen1790, sizeof(char));
  strcpy(tmp_str1790, out);
  strcat(tmp_str1790, "  char* a = args;\n");
  out = tmp_str1790;
  int tmp_strlen1734 = strlen(out) + strlen("  for (int i = 1; i < argc; i++) {\n") + 1;
  char* tmp_str1734 = calloc(tmp_strlen1734, sizeof(char));
  strcpy(tmp_str1734, out);
  strcat(tmp_str1734, "  for (int i = 1; i < argc; i++) {\n");
  out = tmp_str1734;
  int tmp_strlen1684 = strlen(out) + strlen("    int c = strlen(argv[i]);\n") + 1;
  char* tmp_str1684 = calloc(tmp_strlen1684, sizeof(char));
  strcpy(tmp_str1684, out);
  strcat(tmp_str1684, "    int c = strlen(argv[i]);\n");
  out = tmp_str1684;
  int tmp_strlen1635 = strlen(out) + strlen("    strncpy(a, argv[i], c);\n") + 1;
  char* tmp_str1635 = calloc(tmp_strlen1635, sizeof(char));
  strcpy(tmp_str1635, out);
  strcat(tmp_str1635, "    strncpy(a, argv[i], c);\n");
  out = tmp_str1635;
  int tmp_strlen1602 = strlen(out) + strlen("    a += c;\n") + 1;
  char* tmp_str1602 = calloc(tmp_strlen1602, sizeof(char));
  strcpy(tmp_str1602, out);
  strcat(tmp_str1602, "    a += c;\n");
  out = tmp_str1602;
  int tmp_strlen1565 = strlen(out) + strlen("    a[0] = ' ';\n") + 1;
  char* tmp_str1565 = calloc(tmp_strlen1565, sizeof(char));
  strcpy(tmp_str1565, out);
  strcat(tmp_str1565, "    a[0] = ' ';\n");
  out = tmp_str1565;
  int tmp_strlen1532 = strlen(out) + strlen("    a += 1;\n") + 1;
  char* tmp_str1532 = calloc(tmp_strlen1532, sizeof(char));
  strcpy(tmp_str1532, out);
  strcat(tmp_str1532, "    a += 1;\n");
  out = tmp_str1532;
  int tmp_strlen1507 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str1507 = calloc(tmp_strlen1507, sizeof(char));
  strcpy(tmp_str1507, out);
  strcat(tmp_str1507, "  }\n");
  out = tmp_str1507;
  int tmp_strlen1469 = strlen(out) + strlen("  args[l-1] = 0;\n") + 1;
  char* tmp_str1469 = calloc(tmp_strlen1469, sizeof(char));
  strcpy(tmp_str1469, out);
  strcat(tmp_str1469, "  args[l-1] = 0;\n");
  out = tmp_str1469;
  int tmp_strlen1426 = strlen(out) + strlen("  return _main(args);\n") + 1;
  char* tmp_str1426 = calloc(tmp_strlen1426, sizeof(char));
  strcpy(tmp_str1426, out);
  strcat(tmp_str1426, "  return _main(args);\n");
  out = tmp_str1426;
  int tmp_strlen1401 = strlen(out) + strlen("}\n\n") + 1;
  char* tmp_str1401 = calloc(tmp_strlen1401, sizeof(char));
  strcpy(tmp_str1401, out);
  strcat(tmp_str1401, "}\n\n");
  out = tmp_str1401;
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results1271 = Peek(src);
  tok = tmp_results1271.result1;
  tok_str = tmp_results1271.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results1177 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results1177.result1;
      tok_str = tmp_results1177.result2;
      Peek_results tmp_results1119 = Peek(src);
      tok = tmp_results1119.result1;
      tok_str = tmp_results1119.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results991 = TranslateConstDecl(src, "");
        src = tmp_results991.result1;
        const_decl = tmp_results991.result2;
        int tmp_strlen898 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str898 = calloc(tmp_strlen898, sizeof(char));
        strcpy(tmp_str898, constants);
        strcat(tmp_str898, const_decl);
        constants = tmp_str898;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          TranslateFunc_results tmp_results788 = TranslateFunc(src);
          src = tmp_results788.result1;
          fn_decl = tmp_results788.result2;
          fn_def = tmp_results788.result3;
          int tmp_strlen710 = strlen(decls) + strlen(fn_decl) + 1;
          char* tmp_str710 = calloc(tmp_strlen710, sizeof(char));
          strcpy(tmp_str710, decls);
          strcat(tmp_str710, fn_decl);
          decls = tmp_str710;
          int tmp_strlen676 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str676 = calloc(tmp_strlen676, sizeof(char));
          strcpy(tmp_str676, defs);
          strcat(tmp_str676, fn_def);
          defs = tmp_str676;
        } else {
          int tmp_strlen597 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str597 = calloc(tmp_strlen597, sizeof(char));
          strcpy(tmp_str597, "unexpected decl token, got: ");
          strcat(tmp_str597, itoa(tok));
          int tmp_strlen588 = strlen(tmp_str597) + strlen(" \"") + 1;
          char* tmp_str588 = calloc(tmp_strlen588, sizeof(char));
          strcpy(tmp_str588, tmp_str597);
          strcat(tmp_str588, " \"");
          int tmp_strlen577 = strlen(tmp_str588) + strlen(tok_str) + 1;
          char* tmp_str577 = calloc(tmp_strlen577, sizeof(char));
          strcpy(tmp_str577, tmp_str588);
          strcat(tmp_str577, tok_str);
          int tmp_strlen569 = strlen(tmp_str577) + strlen("\"") + 1;
          char* tmp_str569 = calloc(tmp_strlen569, sizeof(char));
          strcpy(tmp_str569, tmp_str577);
          strcat(tmp_str569, "\"");
          printf("%s", tmp_str569);
          exit(1);
        }
      }
    }
    Peek_results tmp_results529 = Peek(src);
    tok = tmp_results529.result1;
    tok_str = tmp_results529.result2;
  }
  ConsumeToken_results tmp_results494 = ConsumeToken(src, TOK_EOF);
  src = tmp_results494.result1;
  tok_str = tmp_results494.result2;
  if ((strcmp(constants, "") != 0)) {
    int tmp_strlen396 = strlen(out) + strlen(constants) + 1;
    char* tmp_str396 = calloc(tmp_strlen396, sizeof(char));
    strcpy(tmp_str396, out);
    strcat(tmp_str396, constants);
    int tmp_strlen388 = strlen(tmp_str396) + strlen("\n") + 1;
    char* tmp_str388 = calloc(tmp_strlen388, sizeof(char));
    strcpy(tmp_str388, tmp_str396);
    strcat(tmp_str388, "\n");
    out = tmp_str388;
  }
  if ((strcmp(decls, "") != 0)) {
    int tmp_strlen333 = strlen(out) + strlen(decls) + 1;
    char* tmp_str333 = calloc(tmp_strlen333, sizeof(char));
    strcpy(tmp_str333, out);
    strcat(tmp_str333, decls);
    int tmp_strlen325 = strlen(tmp_str333) + strlen("\n") + 1;
    char* tmp_str325 = calloc(tmp_strlen325, sizeof(char));
    strcpy(tmp_str325, tmp_str333);
    strcat(tmp_str325, "\n");
    out = tmp_str325;
  }
  if ((strcmp(defs, "") != 0)) {
    int tmp_strlen272 = strlen(out) + strlen(defs) + 1;
    char* tmp_str272 = calloc(tmp_strlen272, sizeof(char));
    strcpy(tmp_str272, out);
    strcat(tmp_str272, defs);
    int tmp_strlen264 = strlen(tmp_str272) + strlen("\n") + 1;
    char* tmp_str264 = calloc(tmp_strlen264, sizeof(char));
    strcpy(tmp_str264, tmp_str272);
    strcat(tmp_str264, "\n");
    out = tmp_str264;
  }
  return out;
}

int _main(char* args) {
  int i = Find(args, " ");
  int tmp_strlen151 = (i) - (0) + 1;
  char* tmp_str151 = calloc(tmp_strlen151, sizeof(char));
  strncpy(tmp_str151, args + 0, tmp_strlen151 - 1);
  tmp_str151[tmp_strlen151 - 1] = 0;
  char* src_file = tmp_str151;
  char* src = read(src_file);
  char* out = TranslateProgram(src);
  int tmp_strlen34 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str34 = calloc(tmp_strlen34, sizeof(char));
  strncpy(tmp_str34, args + (i) + (1), tmp_strlen34 - 1);
  tmp_str34[tmp_strlen34 - 1] = 0;
  char* out_file = tmp_str34;
  write(out_file, out);
  return 0;
}


