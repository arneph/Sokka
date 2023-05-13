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
int main();

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
                  int tmp_strlen29348 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str29348 = calloc(tmp_strlen29348, sizeof(char));
                  strcpy(tmp_str29348, "token has no defined precedence: ");
                  strcat(tmp_str29348, itoa(tok));
                  printf("%s", tmp_str29348);
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
      int tmp_strlen29033 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str29033 = calloc(tmp_strlen29033, sizeof(char));
      strncpy(tmp_str29033, haystack + i, tmp_strlen29033 - 1);
      tmp_str29033[tmp_strlen29033 - 1] = 0;
      if ((strcmp(tmp_str29033, needle) != 0)) {
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
      int tmp_strlen28698 = (strlen(prefix)) - (0) + 1;
      char* tmp_str28698 = calloc(tmp_strlen28698, sizeof(char));
      strncpy(tmp_str28698, text + 0, tmp_strlen28698 - 1);
      tmp_str28698[tmp_strlen28698 - 1] = 0;
      return (strcmp(tmp_str28698, prefix) == 0);
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
    int tmp_strlen28304 = (strlen(text)) - (1) + 1;
    char* tmp_str28304 = calloc(tmp_strlen28304, sizeof(char));
    strncpy(tmp_str28304, text + 1, tmp_strlen28304 - 1);
    tmp_str28304[tmp_strlen28304 - 1] = 0;
    text = tmp_str28304;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen28081 = (strlen(src)) - (2) + 1;
      char* tmp_str28081 = calloc(tmp_strlen28081, sizeof(char));
      strncpy(tmp_str28081, src + 2, tmp_strlen28081 - 1);
      tmp_str28081[tmp_strlen28081 - 1] = 0;
      return (Next_results){tmp_str28081, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen28002 = (strlen(src)) - (2) + 1;
        char* tmp_str28002 = calloc(tmp_strlen28002, sizeof(char));
        strncpy(tmp_str28002, src + 2, tmp_strlen28002 - 1);
        tmp_str28002[tmp_strlen28002 - 1] = 0;
        return (Next_results){tmp_str28002, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen27926 = (strlen(src)) - (2) + 1;
          char* tmp_str27926 = calloc(tmp_strlen27926, sizeof(char));
          strncpy(tmp_str27926, src + 2, tmp_strlen27926 - 1);
          tmp_str27926[tmp_strlen27926 - 1] = 0;
          return (Next_results){tmp_str27926, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen27849 = (strlen(src)) - (2) + 1;
            char* tmp_str27849 = calloc(tmp_strlen27849, sizeof(char));
            strncpy(tmp_str27849, src + 2, tmp_strlen27849 - 1);
            tmp_str27849[tmp_strlen27849 - 1] = 0;
            return (Next_results){tmp_str27849, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen27774 = (strlen(src)) - (2) + 1;
              char* tmp_str27774 = calloc(tmp_strlen27774, sizeof(char));
              strncpy(tmp_str27774, src + 2, tmp_strlen27774 - 1);
              tmp_str27774[tmp_strlen27774 - 1] = 0;
              return (Next_results){tmp_str27774, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen27698 = (strlen(src)) - (2) + 1;
                char* tmp_str27698 = calloc(tmp_strlen27698, sizeof(char));
                strncpy(tmp_str27698, src + 2, tmp_strlen27698 - 1);
                tmp_str27698[tmp_strlen27698 - 1] = 0;
                return (Next_results){tmp_str27698, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen27622 = (strlen(src)) - (2) + 1;
                  char* tmp_str27622 = calloc(tmp_strlen27622, sizeof(char));
                  strncpy(tmp_str27622, src + 2, tmp_strlen27622 - 1);
                  tmp_str27622[tmp_strlen27622 - 1] = 0;
                  return (Next_results){tmp_str27622, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen27546 = (strlen(src)) - (2) + 1;
                    char* tmp_str27546 = calloc(tmp_strlen27546, sizeof(char));
                    strncpy(tmp_str27546, src + 2, tmp_strlen27546 - 1);
                    tmp_str27546[tmp_strlen27546 - 1] = 0;
                    return (Next_results){tmp_str27546, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen27467 = (strlen(src)) - (2) + 1;
                      char* tmp_str27467 = calloc(tmp_strlen27467, sizeof(char));
                      strncpy(tmp_str27467, src + 2, tmp_strlen27467 - 1);
                      tmp_str27467[tmp_strlen27467 - 1] = 0;
                      return (Next_results){tmp_str27467, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen27388 = (strlen(src)) - (3) + 1;
                        char* tmp_str27388 = calloc(tmp_strlen27388, sizeof(char));
                        strncpy(tmp_str27388, src + 3, tmp_strlen27388 - 1);
                        tmp_str27388[tmp_strlen27388 - 1] = 0;
                        return (Next_results){tmp_str27388, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen27308 = (strlen(src)) - (1) + 1;
                          char* tmp_str27308 = calloc(tmp_strlen27308, sizeof(char));
                          strncpy(tmp_str27308, src + 1, tmp_strlen27308 - 1);
                          tmp_str27308[tmp_strlen27308 - 1] = 0;
                          return (Next_results){tmp_str27308, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen27229 = (strlen(src)) - (1) + 1;
                            char* tmp_str27229 = calloc(tmp_strlen27229, sizeof(char));
                            strncpy(tmp_str27229, src + 1, tmp_strlen27229 - 1);
                            tmp_str27229[tmp_strlen27229 - 1] = 0;
                            return (Next_results){tmp_str27229, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen27152 = (strlen(src)) - (1) + 1;
                              char* tmp_str27152 = calloc(tmp_strlen27152, sizeof(char));
                              strncpy(tmp_str27152, src + 1, tmp_strlen27152 - 1);
                              tmp_str27152[tmp_strlen27152 - 1] = 0;
                              return (Next_results){tmp_str27152, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen27075 = (strlen(src)) - (1) + 1;
                                char* tmp_str27075 = calloc(tmp_strlen27075, sizeof(char));
                                strncpy(tmp_str27075, src + 1, tmp_strlen27075 - 1);
                                tmp_str27075[tmp_strlen27075 - 1] = 0;
                                return (Next_results){tmp_str27075, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen26996 = (strlen(src)) - (1) + 1;
                                  char* tmp_str26996 = calloc(tmp_strlen26996, sizeof(char));
                                  strncpy(tmp_str26996, src + 1, tmp_strlen26996 - 1);
                                  tmp_str26996[tmp_strlen26996 - 1] = 0;
                                  return (Next_results){tmp_str26996, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen26917 = (strlen(src)) - (1) + 1;
                                    char* tmp_str26917 = calloc(tmp_strlen26917, sizeof(char));
                                    strncpy(tmp_str26917, src + 1, tmp_strlen26917 - 1);
                                    tmp_str26917[tmp_strlen26917 - 1] = 0;
                                    return (Next_results){tmp_str26917, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen26840 = (strlen(src)) - (1) + 1;
                                      char* tmp_str26840 = calloc(tmp_strlen26840, sizeof(char));
                                      strncpy(tmp_str26840, src + 1, tmp_strlen26840 - 1);
                                      tmp_str26840[tmp_strlen26840 - 1] = 0;
                                      return (Next_results){tmp_str26840, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, ":")) {
                                        int tmp_strlen26763 = (strlen(src)) - (1) + 1;
                                        char* tmp_str26763 = calloc(tmp_strlen26763, sizeof(char));
                                        strncpy(tmp_str26763, src + 1, tmp_strlen26763 - 1);
                                        tmp_str26763[tmp_strlen26763 - 1] = 0;
                                        return (Next_results){tmp_str26763, TOK_COLON, ":"};
                                      } else {
                                        if (StartsWith(src, ",")) {
                                          int tmp_strlen26687 = (strlen(src)) - (1) + 1;
                                          char* tmp_str26687 = calloc(tmp_strlen26687, sizeof(char));
                                          strncpy(tmp_str26687, src + 1, tmp_strlen26687 - 1);
                                          tmp_str26687[tmp_strlen26687 - 1] = 0;
                                          return (Next_results){tmp_str26687, TOK_COMMA, ","};
                                        } else {
                                          if (StartsWith(src, "=")) {
                                            int tmp_strlen26611 = (strlen(src)) - (1) + 1;
                                            char* tmp_str26611 = calloc(tmp_strlen26611, sizeof(char));
                                            strncpy(tmp_str26611, src + 1, tmp_strlen26611 - 1);
                                            tmp_str26611[tmp_strlen26611 - 1] = 0;
                                            return (Next_results){tmp_str26611, TOK_ASSIGN, "="};
                                          } else {
                                            if (StartsWith(src, "!")) {
                                              int tmp_strlen26534 = (strlen(src)) - (1) + 1;
                                              char* tmp_str26534 = calloc(tmp_strlen26534, sizeof(char));
                                              strncpy(tmp_str26534, src + 1, tmp_strlen26534 - 1);
                                              tmp_str26534[tmp_strlen26534 - 1] = 0;
                                              return (Next_results){tmp_str26534, TOK_BNOT, "!"};
                                            } else {
                                              if (StartsWith(src, "+")) {
                                                int tmp_strlen26459 = (strlen(src)) - (1) + 1;
                                                char* tmp_str26459 = calloc(tmp_strlen26459, sizeof(char));
                                                strncpy(tmp_str26459, src + 1, tmp_strlen26459 - 1);
                                                tmp_str26459[tmp_strlen26459 - 1] = 0;
                                                return (Next_results){tmp_str26459, TOK_ADD, "+"};
                                              } else {
                                                if (StartsWith(src, "-")) {
                                                  int tmp_strlen26385 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str26385 = calloc(tmp_strlen26385, sizeof(char));
                                                  strncpy(tmp_str26385, src + 1, tmp_strlen26385 - 1);
                                                  tmp_str26385[tmp_strlen26385 - 1] = 0;
                                                  return (Next_results){tmp_str26385, TOK_SUB, "-"};
                                                } else {
                                                  if (StartsWith(src, "*")) {
                                                    int tmp_strlen26311 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str26311 = calloc(tmp_strlen26311, sizeof(char));
                                                    strncpy(tmp_str26311, src + 1, tmp_strlen26311 - 1);
                                                    tmp_str26311[tmp_strlen26311 - 1] = 0;
                                                    return (Next_results){tmp_str26311, TOK_MUL, "*"};
                                                  } else {
                                                    if (StartsWith(src, "/")) {
                                                      int tmp_strlen26237 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str26237 = calloc(tmp_strlen26237, sizeof(char));
                                                      strncpy(tmp_str26237, src + 1, tmp_strlen26237 - 1);
                                                      tmp_str26237[tmp_strlen26237 - 1] = 0;
                                                      return (Next_results){tmp_str26237, TOK_DIV, "/"};
                                                    } else {
                                                      if (StartsWith(src, "%")) {
                                                        int tmp_strlen26163 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str26163 = calloc(tmp_strlen26163, sizeof(char));
                                                        strncpy(tmp_str26163, src + 1, tmp_strlen26163 - 1);
                                                        tmp_str26163[tmp_strlen26163 - 1] = 0;
                                                        return (Next_results){tmp_str26163, TOK_REM, "%"};
                                                      } else {
                                                        if (StartsWith(src, "~")) {
                                                          int tmp_strlen26089 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str26089 = calloc(tmp_strlen26089, sizeof(char));
                                                          strncpy(tmp_str26089, src + 1, tmp_strlen26089 - 1);
                                                          tmp_str26089[tmp_strlen26089 - 1] = 0;
                                                          return (Next_results){tmp_str26089, TOK_INOT, "~"};
                                                        } else {
                                                          if (StartsWith(src, "|")) {
                                                            int tmp_strlen26014 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str26014 = calloc(tmp_strlen26014, sizeof(char));
                                                            strncpy(tmp_str26014, src + 1, tmp_strlen26014 - 1);
                                                            tmp_str26014[tmp_strlen26014 - 1] = 0;
                                                            return (Next_results){tmp_str26014, TOK_IOR, "|"};
                                                          } else {
                                                            if (StartsWith(src, "&")) {
                                                              int tmp_strlen25940 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str25940 = calloc(tmp_strlen25940, sizeof(char));
                                                              strncpy(tmp_str25940, src + 1, tmp_strlen25940 - 1);
                                                              tmp_str25940[tmp_strlen25940 - 1] = 0;
                                                              return (Next_results){tmp_str25940, TOK_IAND, "&"};
                                                            } else {
                                                              if (StartsWith(src, "^")) {
                                                                int tmp_strlen25865 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str25865 = calloc(tmp_strlen25865, sizeof(char));
                                                                strncpy(tmp_str25865, src + 1, tmp_strlen25865 - 1);
                                                                tmp_str25865[tmp_strlen25865 - 1] = 0;
                                                                return (Next_results){tmp_str25865, TOK_IXOR, "^"};
                                                              } else {
                                                                if (StartsWith(src, "<")) {
                                                                  int tmp_strlen25790 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str25790 = calloc(tmp_strlen25790, sizeof(char));
                                                                  strncpy(tmp_str25790, src + 1, tmp_strlen25790 - 1);
                                                                  tmp_str25790[tmp_strlen25790 - 1] = 0;
                                                                  return (Next_results){tmp_str25790, TOK_LESS, "<"};
                                                                } else {
                                                                  if (StartsWith(src, ">")) {
                                                                    int tmp_strlen25715 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str25715 = calloc(tmp_strlen25715, sizeof(char));
                                                                    strncpy(tmp_str25715, src + 1, tmp_strlen25715 - 1);
                                                                    tmp_str25715[tmp_strlen25715 - 1] = 0;
                                                                    return (Next_results){tmp_str25715, TOK_GREATER, ">"};
                                                                  } else {
                                                                    if (IsAlpha(src[0])) {
                                                                      int i = 1;
                                                                      while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                        i = (i) + (1);
                                                                      }
                                                                      i = (i) - (1);
                                                                      int tmp_strlen25484 = (i) - (0) + 1;
                                                                      char* tmp_str25484 = calloc(tmp_strlen25484, sizeof(char));
                                                                      strncpy(tmp_str25484, src + 0, tmp_strlen25484 - 1);
                                                                      tmp_str25484[tmp_strlen25484 - 1] = 0;
                                                                      char* ts = tmp_str25484;
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
                                                                      int tmp_strlen24692 = (strlen(src)) - (i) + 1;
                                                                      char* tmp_str24692 = calloc(tmp_strlen24692, sizeof(char));
                                                                      strncpy(tmp_str24692, src + i, tmp_strlen24692 - 1);
                                                                      tmp_str24692[tmp_strlen24692 - 1] = 0;
                                                                      return (Next_results){tmp_str24692, tt, ts};
                                                                    } else {
                                                                      if (IsNumeric(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        int tmp_strlen24524 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str24524 = calloc(tmp_strlen24524, sizeof(char));
                                                                        strncpy(tmp_str24524, src + i, tmp_strlen24524 - 1);
                                                                        tmp_str24524[tmp_strlen24524 - 1] = 0;
                                                                        int tmp_strlen24503 = (i) - (0) + 1;
                                                                        char* tmp_str24503 = calloc(tmp_strlen24503, sizeof(char));
                                                                        strncpy(tmp_str24503, src + 0, tmp_strlen24503 - 1);
                                                                        tmp_str24503[tmp_strlen24503 - 1] = 0;
                                                                        return (Next_results){tmp_str24524, TOK_INTLIT, tmp_str24503};
                                                                      } else {
                                                                        if (StartsWith(src, "\"")) {
                                                                          int i = 1;
                                                                          while (true) {
                                                                            int tmp_strlen24422 = ((i) + (1)) - (i) + 1;
                                                                            char* tmp_str24422 = calloc(tmp_strlen24422, sizeof(char));
                                                                            strncpy(tmp_str24422, src + i, tmp_strlen24422 - 1);
                                                                            tmp_str24422[tmp_strlen24422 - 1] = 0;
                                                                            if (!((strcmp(tmp_str24422, "\"") != 0))) break;
                                                                            i = (i) + (1);
                                                                            int tmp_strlen24363 = (i) - ((i) - (1)) + 1;
                                                                            char* tmp_str24363 = calloc(tmp_strlen24363, sizeof(char));
                                                                            strncpy(tmp_str24363, src + (i) - (1), tmp_strlen24363 - 1);
                                                                            tmp_str24363[tmp_strlen24363 - 1] = 0;
                                                                            if ((strcmp(tmp_str24363, "\\") == 0)) {
                                                                              i = (i) + (1);
                                                                            }
                                                                          }
                                                                          i = (i) + (1);
                                                                          int tmp_strlen24259 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str24259 = calloc(tmp_strlen24259, sizeof(char));
                                                                          strncpy(tmp_str24259, src + i, tmp_strlen24259 - 1);
                                                                          tmp_str24259[tmp_strlen24259 - 1] = 0;
                                                                          int tmp_strlen24238 = (i) - (0) + 1;
                                                                          char* tmp_str24238 = calloc(tmp_strlen24238, sizeof(char));
                                                                          strncpy(tmp_str24238, src + 0, tmp_strlen24238 - 1);
                                                                          tmp_str24238[tmp_strlen24238 - 1] = 0;
                                                                          return (Next_results){tmp_str24259, TOK_STRLIT, tmp_str24238};
                                                                        } else {
                                                                          int tmp_strlen24173 = (1) - (0) + 1;
                                                                          char* tmp_str24173 = calloc(tmp_strlen24173, sizeof(char));
                                                                          strncpy(tmp_str24173, src + 0, tmp_strlen24173 - 1);
                                                                          tmp_str24173[tmp_strlen24173 - 1] = 0;
                                                                          int tmp_strlen24169 = strlen("unexpected token start: ") + strlen(tmp_str24173) + 1;
                                                                          char* tmp_str24169 = calloc(tmp_strlen24169, sizeof(char));
                                                                          strcpy(tmp_str24169, "unexpected token start: ");
                                                                          strcat(tmp_str24169, tmp_str24173);
                                                                          printf("%s", tmp_str24169);
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
  Next_results tmp_results24057 = Next(src);
  src = tmp_results24057.result1;
  tok = tmp_results24057.result2;
  tok_str = tmp_results24057.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results23871 = Next(src);
  src = tmp_results23871.result1;
  actual_tok = tmp_results23871.result2;
  actual_tok_str = tmp_results23871.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen23737 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str23737 = calloc(tmp_strlen23737, sizeof(char));
    strcpy(tmp_str23737, "expected token: ");
    strcat(tmp_str23737, itoa(expected_tok));
    int tmp_strlen23710 = strlen(tmp_str23737) + strlen(" got: ") + 1;
    char* tmp_str23710 = calloc(tmp_strlen23710, sizeof(char));
    strcpy(tmp_str23710, tmp_str23737);
    strcat(tmp_str23710, " got: ");
    int tmp_strlen23690 = strlen(tmp_str23710) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str23690 = calloc(tmp_strlen23690, sizeof(char));
    strcpy(tmp_str23690, tmp_str23710);
    strcat(tmp_str23690, itoa(actual_tok));
    int tmp_strlen23681 = strlen(tmp_str23690) + strlen(" \"") + 1;
    char* tmp_str23681 = calloc(tmp_strlen23681, sizeof(char));
    strcpy(tmp_str23681, tmp_str23690);
    strcat(tmp_str23681, " \"");
    int tmp_strlen23663 = strlen(tmp_str23681) + strlen(actual_tok_str) + 1;
    char* tmp_str23663 = calloc(tmp_strlen23663, sizeof(char));
    strcpy(tmp_str23663, tmp_str23681);
    strcat(tmp_str23663, actual_tok_str);
    int tmp_strlen23655 = strlen(tmp_str23663) + strlen("\"") + 1;
    char* tmp_str23655 = calloc(tmp_strlen23655, sizeof(char));
    strcpy(tmp_str23655, tmp_str23663);
    strcat(tmp_str23655, "\"");
    printf("%s", tmp_str23655);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results23487 = Next(src);
  src = tmp_results23487.result1;
  actual_tok = tmp_results23487.result2;
  actual_tok_str = tmp_results23487.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen23353 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str23353 = calloc(tmp_strlen23353, sizeof(char));
    strcpy(tmp_str23353, "expected ident, got: ");
    strcat(tmp_str23353, itoa(actual_tok));
    int tmp_strlen23344 = strlen(tmp_str23353) + strlen(" \"") + 1;
    char* tmp_str23344 = calloc(tmp_strlen23344, sizeof(char));
    strcpy(tmp_str23344, tmp_str23353);
    strcat(tmp_str23344, " \"");
    int tmp_strlen23326 = strlen(tmp_str23344) + strlen(actual_tok_str) + 1;
    char* tmp_str23326 = calloc(tmp_strlen23326, sizeof(char));
    strcpy(tmp_str23326, tmp_str23344);
    strcat(tmp_str23326, actual_tok_str);
    int tmp_strlen23318 = strlen(tmp_str23326) + strlen("\"") + 1;
    char* tmp_str23318 = calloc(tmp_strlen23318, sizeof(char));
    strcpy(tmp_str23318, tmp_str23326);
    strcat(tmp_str23318, "\"");
    printf("%s", tmp_str23318);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results23158 = Next(src);
  src = tmp_results23158.result1;
  tok = tmp_results23158.result2;
  tok_str = tmp_results23158.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen22861 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str22861 = calloc(tmp_strlen22861, sizeof(char));
        strcpy(tmp_str22861, "expected type, got: ");
        strcat(tmp_str22861, itoa(tok));
        int tmp_strlen22852 = strlen(tmp_str22861) + strlen(" \"") + 1;
        char* tmp_str22852 = calloc(tmp_strlen22852, sizeof(char));
        strcpy(tmp_str22852, tmp_str22861);
        strcat(tmp_str22852, " \"");
        int tmp_strlen22841 = strlen(tmp_str22852) + strlen(tok_str) + 1;
        char* tmp_str22841 = calloc(tmp_strlen22841, sizeof(char));
        strcpy(tmp_str22841, tmp_str22852);
        strcat(tmp_str22841, tok_str);
        int tmp_strlen22833 = strlen(tmp_str22841) + strlen("\"") + 1;
        char* tmp_str22833 = calloc(tmp_strlen22833, sizeof(char));
        strcpy(tmp_str22833, tmp_str22841);
        strcat(tmp_str22833, "\"");
        printf("%s", tmp_str22833);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results22702 = Next(src);
  src = tmp_results22702.result1;
  tok = tmp_results22702.result2;
  tok_str = tmp_results22702.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen22528 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str22528 = calloc(tmp_strlen22528, sizeof(char));
    strcpy(tmp_str22528, "expected false or true, got: ");
    strcat(tmp_str22528, itoa(tok));
    int tmp_strlen22519 = strlen(tmp_str22528) + strlen(" \"") + 1;
    char* tmp_str22519 = calloc(tmp_strlen22519, sizeof(char));
    strcpy(tmp_str22519, tmp_str22528);
    strcat(tmp_str22519, " \"");
    int tmp_strlen22508 = strlen(tmp_str22519) + strlen(tok_str) + 1;
    char* tmp_str22508 = calloc(tmp_strlen22508, sizeof(char));
    strcpy(tmp_str22508, tmp_str22519);
    strcat(tmp_str22508, tok_str);
    int tmp_strlen22500 = strlen(tmp_str22508) + strlen("\"") + 1;
    char* tmp_str22500 = calloc(tmp_strlen22500, sizeof(char));
    strcpy(tmp_str22500, tmp_str22508);
    strcat(tmp_str22500, "\"");
    printf("%s", tmp_str22500);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results22391 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results22391.result1;
  lit = tmp_results22391.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results22242 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results22242.result1;
  lit = tmp_results22242.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results22041 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results22041.result1;
  tok_str = tmp_results22041.result2;
  Peek_results tmp_results21992 = Peek(src);
  tok = tmp_results21992.result1;
  tok_str = tmp_results21992.result2;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results21840 = TranslateExprs(src, indent);
    src = tmp_results21840.result1;
    expr_count = tmp_results21840.result2;
    args_setup = tmp_results21840.result3;
    arg_values = tmp_results21840.result4;
  }
  ConsumeToken_results tmp_results21760 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results21760.result1;
  tok_str = tmp_results21760.result2;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen21623 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str21623 = calloc(tmp_strlen21623, sizeof(char));
    strcpy(tmp_str21623, "printf(\"%s\", ");
    strcat(tmp_str21623, arg_values);
    int tmp_strlen21616 = strlen(tmp_str21623) + strlen(")") + 1;
    char* tmp_str21616 = calloc(tmp_strlen21616, sizeof(char));
    strcpy(tmp_str21616, tmp_str21623);
    strcat(tmp_str21616, ")");
    val = tmp_str21616;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen21546 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str21546 = calloc(tmp_strlen21546, sizeof(char));
      strcpy(tmp_str21546, "strlen(");
      strcat(tmp_str21546, arg_values);
      int tmp_strlen21539 = strlen(tmp_str21546) + strlen(")") + 1;
      char* tmp_str21539 = calloc(tmp_strlen21539, sizeof(char));
      strcpy(tmp_str21539, tmp_str21546);
      strcat(tmp_str21539, ")");
      val = tmp_str21539;
    } else {
      int tmp_strlen21498 = strlen(callee) + strlen("(") + 1;
      char* tmp_str21498 = calloc(tmp_strlen21498, sizeof(char));
      strcpy(tmp_str21498, callee);
      strcat(tmp_str21498, "(");
      int tmp_strlen21484 = strlen(tmp_str21498) + strlen(arg_values) + 1;
      char* tmp_str21484 = calloc(tmp_strlen21484, sizeof(char));
      strcpy(tmp_str21484, tmp_str21498);
      strcat(tmp_str21484, arg_values);
      int tmp_strlen21477 = strlen(tmp_str21484) + strlen(")") + 1;
      char* tmp_str21477 = calloc(tmp_strlen21477, sizeof(char));
      strcpy(tmp_str21477, tmp_str21484);
      strcat(tmp_str21477, ")");
      val = tmp_str21477;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  char* tok_str;
  int p = strlen(src);
  ConsumeToken_results tmp_results21266 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results21266.result1;
  tok_str = tmp_results21266.result2;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen21078 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str21078 = calloc(tmp_strlen21078, sizeof(char));
  strcpy(tmp_str21078, "strlen(");
  strcat(tmp_str21078, strvar);
  int tmp_strlen21071 = strlen(tmp_str21078) + strlen(")") + 1;
  char* tmp_str21071 = calloc(tmp_strlen21071, sizeof(char));
  strcpy(tmp_str21071, tmp_str21078);
  strcat(tmp_str21071, ")");
  char* high_expr = tmp_str21071;
  Peek_results tmp_results21066 = Peek(src);
  tok = tmp_results21066.result1;
  tok_str = tmp_results21066.result2;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results21007 = ConsumeToken(src, TOK_COLON);
    src = tmp_results21007.result1;
    tok_str = tmp_results21007.result2;
    TranslateExpr_results tmp_results20955 = TranslateExpr(src, indent);
    src = tmp_results20955.result1;
    high_setup = tmp_results20955.result2;
    high_expr = tmp_results20955.result3;
    ConsumeToken_results tmp_results20891 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results20891.result1;
    tok_str = tmp_results20891.result2;
  } else {
    TranslateExpr_results tmp_results20823 = TranslateExpr(src, indent);
    src = tmp_results20823.result1;
    low_setup = tmp_results20823.result2;
    low_expr = tmp_results20823.result3;
    Peek_results tmp_results20761 = Peek(src);
    tok = tmp_results20761.result1;
    tok_str = tmp_results20761.result2;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results20691 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results20691.result1;
      tok_str = tmp_results20691.result2;
      int tmp_strlen20596 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str20596 = calloc(tmp_strlen20596, sizeof(char));
      strcpy(tmp_str20596, strvar);
      strcat(tmp_str20596, "[");
      int tmp_strlen20584 = strlen(tmp_str20596) + strlen(low_expr) + 1;
      char* tmp_str20584 = calloc(tmp_strlen20584, sizeof(char));
      strcpy(tmp_str20584, tmp_str20596);
      strcat(tmp_str20584, low_expr);
      int tmp_strlen20577 = strlen(tmp_str20584) + strlen("]") + 1;
      char* tmp_str20577 = calloc(tmp_strlen20577, sizeof(char));
      strcpy(tmp_str20577, tmp_str20584);
      strcat(tmp_str20577, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str20577};
    }
    ConsumeToken_results tmp_results20558 = ConsumeToken(src, TOK_COLON);
    src = tmp_results20558.result1;
    tok_str = tmp_results20558.result2;
    Peek_results tmp_results20506 = Peek(src);
    tok = tmp_results20506.result1;
    tok_str = tmp_results20506.result2;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results20436 = TranslateExpr(src, indent);
      src = tmp_results20436.result1;
      high_setup = tmp_results20436.result2;
      high_expr = tmp_results20436.result3;
    }
    ConsumeToken_results tmp_results20362 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results20362.result1;
    tok_str = tmp_results20362.result2;
  }
  int tmp_strlen20263 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str20263 = calloc(tmp_strlen20263, sizeof(char));
  strcpy(tmp_str20263, "tmp_str");
  strcat(tmp_str20263, itoa(p));
  char* tmp_str = tmp_str20263;
  int tmp_strlen20210 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str20210 = calloc(tmp_strlen20210, sizeof(char));
  strcpy(tmp_str20210, "tmp_strlen");
  strcat(tmp_str20210, itoa(p));
  char* tmp_strlen = tmp_str20210;
  int tmp_strlen20162 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str20162 = calloc(tmp_strlen20162, sizeof(char));
  strcpy(tmp_str20162, low_setup);
  strcat(tmp_str20162, high_setup);
  char* setup = tmp_str20162;
  int tmp_strlen20134 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str20134 = calloc(tmp_strlen20134, sizeof(char));
  strcpy(tmp_str20134, setup);
  strcat(tmp_str20134, indent);
  int tmp_strlen20124 = strlen(tmp_str20134) + strlen("int ") + 1;
  char* tmp_str20124 = calloc(tmp_strlen20124, sizeof(char));
  strcpy(tmp_str20124, tmp_str20134);
  strcat(tmp_str20124, "int ");
  int tmp_strlen20110 = strlen(tmp_str20124) + strlen(tmp_strlen) + 1;
  char* tmp_str20110 = calloc(tmp_strlen20110, sizeof(char));
  strcpy(tmp_str20110, tmp_str20124);
  strcat(tmp_str20110, tmp_strlen);
  int tmp_strlen20100 = strlen(tmp_str20110) + strlen(" = (") + 1;
  char* tmp_str20100 = calloc(tmp_strlen20100, sizeof(char));
  strcpy(tmp_str20100, tmp_str20110);
  strcat(tmp_str20100, " = (");
  int tmp_strlen20087 = strlen(tmp_str20100) + strlen(high_expr) + 1;
  char* tmp_str20087 = calloc(tmp_strlen20087, sizeof(char));
  strcpy(tmp_str20087, tmp_str20100);
  strcat(tmp_str20087, high_expr);
  int tmp_strlen20076 = strlen(tmp_str20087) + strlen(") - (") + 1;
  char* tmp_str20076 = calloc(tmp_strlen20076, sizeof(char));
  strcpy(tmp_str20076, tmp_str20087);
  strcat(tmp_str20076, ") - (");
  int tmp_strlen20064 = strlen(tmp_str20076) + strlen(low_expr) + 1;
  char* tmp_str20064 = calloc(tmp_strlen20064, sizeof(char));
  strcpy(tmp_str20064, tmp_str20076);
  strcat(tmp_str20064, low_expr);
  int tmp_strlen20050 = strlen(tmp_str20064) + strlen(") + 1;\n") + 1;
  char* tmp_str20050 = calloc(tmp_strlen20050, sizeof(char));
  strcpy(tmp_str20050, tmp_str20064);
  strcat(tmp_str20050, ") + 1;\n");
  setup = tmp_str20050;
  int tmp_strlen20022 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str20022 = calloc(tmp_strlen20022, sizeof(char));
  strcpy(tmp_str20022, setup);
  strcat(tmp_str20022, indent);
  int tmp_strlen20010 = strlen(tmp_str20022) + strlen("char* ") + 1;
  char* tmp_str20010 = calloc(tmp_strlen20010, sizeof(char));
  strcpy(tmp_str20010, tmp_str20022);
  strcat(tmp_str20010, "char* ");
  int tmp_strlen19999 = strlen(tmp_str20010) + strlen(tmp_str) + 1;
  char* tmp_str19999 = calloc(tmp_strlen19999, sizeof(char));
  strcpy(tmp_str19999, tmp_str20010);
  strcat(tmp_str19999, tmp_str);
  int tmp_strlen19983 = strlen(tmp_str19999) + strlen(" = calloc(") + 1;
  char* tmp_str19983 = calloc(tmp_strlen19983, sizeof(char));
  strcpy(tmp_str19983, tmp_str19999);
  strcat(tmp_str19983, " = calloc(");
  int tmp_strlen19969 = strlen(tmp_str19983) + strlen(tmp_strlen) + 1;
  char* tmp_str19969 = calloc(tmp_strlen19969, sizeof(char));
  strcpy(tmp_str19969, tmp_str19983);
  strcat(tmp_str19969, tmp_strlen);
  int tmp_strlen19945 = strlen(tmp_str19969) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str19945 = calloc(tmp_strlen19945, sizeof(char));
  strcpy(tmp_str19945, tmp_str19969);
  strcat(tmp_str19945, ", sizeof(char));\n");
  setup = tmp_str19945;
  int tmp_strlen19917 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str19917 = calloc(tmp_strlen19917, sizeof(char));
  strcpy(tmp_str19917, setup);
  strcat(tmp_str19917, indent);
  int tmp_strlen19903 = strlen(tmp_str19917) + strlen("strncpy(") + 1;
  char* tmp_str19903 = calloc(tmp_strlen19903, sizeof(char));
  strcpy(tmp_str19903, tmp_str19917);
  strcat(tmp_str19903, "strncpy(");
  int tmp_strlen19892 = strlen(tmp_str19903) + strlen(tmp_str) + 1;
  char* tmp_str19892 = calloc(tmp_strlen19892, sizeof(char));
  strcpy(tmp_str19892, tmp_str19903);
  strcat(tmp_str19892, tmp_str);
  int tmp_strlen19884 = strlen(tmp_str19892) + strlen(", ") + 1;
  char* tmp_str19884 = calloc(tmp_strlen19884, sizeof(char));
  strcpy(tmp_str19884, tmp_str19892);
  strcat(tmp_str19884, ", ");
  int tmp_strlen19874 = strlen(tmp_str19884) + strlen(strvar) + 1;
  char* tmp_str19874 = calloc(tmp_strlen19874, sizeof(char));
  strcpy(tmp_str19874, tmp_str19884);
  strcat(tmp_str19874, strvar);
  int tmp_strlen19865 = strlen(tmp_str19874) + strlen(" + ") + 1;
  char* tmp_str19865 = calloc(tmp_strlen19865, sizeof(char));
  strcpy(tmp_str19865, tmp_str19874);
  strcat(tmp_str19865, " + ");
  int tmp_strlen19853 = strlen(tmp_str19865) + strlen(low_expr) + 1;
  char* tmp_str19853 = calloc(tmp_strlen19853, sizeof(char));
  strcpy(tmp_str19853, tmp_str19865);
  strcat(tmp_str19853, low_expr);
  int tmp_strlen19845 = strlen(tmp_str19853) + strlen(", ") + 1;
  char* tmp_str19845 = calloc(tmp_strlen19845, sizeof(char));
  strcpy(tmp_str19845, tmp_str19853);
  strcat(tmp_str19845, ", ");
  int tmp_strlen19831 = strlen(tmp_str19845) + strlen(tmp_strlen) + 1;
  char* tmp_str19831 = calloc(tmp_strlen19831, sizeof(char));
  strcpy(tmp_str19831, tmp_str19845);
  strcat(tmp_str19831, tmp_strlen);
  int tmp_strlen19817 = strlen(tmp_str19831) + strlen(" - 1);\n") + 1;
  char* tmp_str19817 = calloc(tmp_strlen19817, sizeof(char));
  strcpy(tmp_str19817, tmp_str19831);
  strcat(tmp_str19817, " - 1);\n");
  setup = tmp_str19817;
  int tmp_strlen19789 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str19789 = calloc(tmp_strlen19789, sizeof(char));
  strcpy(tmp_str19789, setup);
  strcat(tmp_str19789, indent);
  int tmp_strlen19778 = strlen(tmp_str19789) + strlen(tmp_str) + 1;
  char* tmp_str19778 = calloc(tmp_strlen19778, sizeof(char));
  strcpy(tmp_str19778, tmp_str19789);
  strcat(tmp_str19778, tmp_str);
  int tmp_strlen19771 = strlen(tmp_str19778) + strlen("[") + 1;
  char* tmp_str19771 = calloc(tmp_strlen19771, sizeof(char));
  strcpy(tmp_str19771, tmp_str19778);
  strcat(tmp_str19771, "[");
  int tmp_strlen19757 = strlen(tmp_str19771) + strlen(tmp_strlen) + 1;
  char* tmp_str19757 = calloc(tmp_strlen19757, sizeof(char));
  strcpy(tmp_str19757, tmp_str19771);
  strcat(tmp_str19757, tmp_strlen);
  int tmp_strlen19739 = strlen(tmp_str19757) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str19739 = calloc(tmp_strlen19739, sizeof(char));
  strcpy(tmp_str19739, tmp_str19757);
  strcat(tmp_str19739, " - 1] = 0;\n");
  setup = tmp_str19739;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results19580 = Peek(src);
  tok = tmp_results19580.result1;
  tok_str = tmp_results19580.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results19470 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results19470.result1;
    tok_str = tmp_results19470.result2;
    TranslateExpr_results tmp_results19417 = TranslateExpr(src, indent);
    src = tmp_results19417.result1;
    setup = tmp_results19417.result2;
    val = tmp_results19417.result3;
    ConsumeToken_results tmp_results19364 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results19364.result1;
    tok_str = tmp_results19364.result2;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results19204 = TranslateBoolLiteral(src);
      src = tmp_results19204.result1;
      lit = tmp_results19204.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results19073 = TranslateIntLiteral(src);
        src = tmp_results19073.result1;
        lit = tmp_results19073.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results18943 = TranslateStringLiteral(src);
          src = tmp_results18943.result1;
          lit = tmp_results18943.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results18809 = ConsumeIdent(src);
            src = tmp_results18809.result1;
            ident = tmp_results18809.result2;
            Peek_results tmp_results18770 = Peek(src);
            tok = tmp_results18770.result1;
            tok_str = tmp_results18770.result2;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results18643 = TranslateCall(src, indent, ident);
              src = tmp_results18643.result1;
              setup = tmp_results18643.result2;
              expr = tmp_results18643.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results18443 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results18443.result1;
                setup = tmp_results18443.result2;
                expr = tmp_results18443.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen18223 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str18223 = calloc(tmp_strlen18223, sizeof(char));
            strcpy(tmp_str18223, "unexpected expr, got: ");
            strcat(tmp_str18223, itoa(tok));
            int tmp_strlen18214 = strlen(tmp_str18223) + strlen(" \"") + 1;
            char* tmp_str18214 = calloc(tmp_strlen18214, sizeof(char));
            strcpy(tmp_str18214, tmp_str18223);
            strcat(tmp_str18214, " \"");
            int tmp_strlen18203 = strlen(tmp_str18214) + strlen(tok_str) + 1;
            char* tmp_str18203 = calloc(tmp_strlen18203, sizeof(char));
            strcpy(tmp_str18203, tmp_str18214);
            strcat(tmp_str18203, tok_str);
            int tmp_strlen18195 = strlen(tmp_str18203) + strlen("\"") + 1;
            char* tmp_str18195 = calloc(tmp_strlen18195, sizeof(char));
            strcpy(tmp_str18195, tmp_str18203);
            strcat(tmp_str18195, "\"");
            printf("%s", tmp_str18195);
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
  Peek_results tmp_results18042 = Peek(src);
  tok = tmp_results18042.result1;
  tok_str = tmp_results18042.result2;
  if (IsUnaryOp(tok)) {
    ConsumeToken_results tmp_results17985 = ConsumeToken(src, tok);
    src = tmp_results17985.result1;
    tok_str = tmp_results17985.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results17889 = TranslateExpr(src, indent);
    src = tmp_results17889.result1;
    setup = tmp_results17889.result2;
    val = tmp_results17889.result3;
    int tmp_strlen17816 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str17816 = calloc(tmp_strlen17816, sizeof(char));
    strcpy(tmp_str17816, tok_str);
    strcat(tmp_str17816, "(");
    int tmp_strlen17809 = strlen(tmp_str17816) + strlen(val) + 1;
    char* tmp_str17809 = calloc(tmp_strlen17809, sizeof(char));
    strcpy(tmp_str17809, tmp_str17816);
    strcat(tmp_str17809, val);
    int tmp_strlen17802 = strlen(tmp_str17809) + strlen(")") + 1;
    char* tmp_str17802 = calloc(tmp_strlen17802, sizeof(char));
    strcpy(tmp_str17802, tmp_str17809);
    strcat(tmp_str17802, ")");
    val = tmp_str17802;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results17698 = TranslateOperand(src, indent);
    src = tmp_results17698.result1;
    setup = tmp_results17698.result2;
    expr = tmp_results17698.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results17455 = TranslateUnaryExpr(src, indent);
  src = tmp_results17455.result1;
  setup = tmp_results17455.result2;
  val = tmp_results17455.result3;
  int op;
  char* op_str;
  Peek_results tmp_results17362 = Peek(src);
  op = tmp_results17362.result1;
  op_str = tmp_results17362.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results17275 = ConsumeToken(src, op);
    src = tmp_results17275.result1;
    op_str = tmp_results17275.result2;
    int tok;
    char* tok_str;
    Peek_results tmp_results17182 = Peek(src);
    tok = tmp_results17182.result1;
    tok_str = tmp_results17182.result2;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results17112 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results17112.result1;
      tok_str = tmp_results17112.result2;
      Peek_results tmp_results17054 = Peek(src);
      tok = tmp_results17054.result1;
      tok_str = tmp_results17054.result2;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results16957 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results16957.result1;
    setup_b = tmp_results16957.result2;
    val_b = tmp_results16957.result3;
    int tmp_strlen16846 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str16846 = calloc(tmp_strlen16846, sizeof(char));
    strcpy(tmp_str16846, setup);
    strcat(tmp_str16846, setup_b);
    setup = tmp_str16846;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen16754 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str16754 = calloc(tmp_strlen16754, sizeof(char));
      strcpy(tmp_str16754, "tmp_str");
      strcat(tmp_str16754, itoa(strlen(src)));
      char* tmp_str = tmp_str16754;
      int tmp_strlen16686 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str16686 = calloc(tmp_strlen16686, sizeof(char));
      strcpy(tmp_str16686, "tmp_strlen");
      strcat(tmp_str16686, itoa(strlen(src)));
      char* tmp_strlen = tmp_str16686;
      int tmp_strlen16650 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str16650 = calloc(tmp_strlen16650, sizeof(char));
      strcpy(tmp_str16650, setup);
      strcat(tmp_str16650, indent);
      int tmp_strlen16640 = strlen(tmp_str16650) + strlen("int ") + 1;
      char* tmp_str16640 = calloc(tmp_strlen16640, sizeof(char));
      strcpy(tmp_str16640, tmp_str16650);
      strcat(tmp_str16640, "int ");
      int tmp_strlen16626 = strlen(tmp_str16640) + strlen(tmp_strlen) + 1;
      char* tmp_str16626 = calloc(tmp_strlen16626, sizeof(char));
      strcpy(tmp_str16626, tmp_str16640);
      strcat(tmp_str16626, tmp_strlen);
      int tmp_strlen16610 = strlen(tmp_str16626) + strlen(" = strlen(") + 1;
      char* tmp_str16610 = calloc(tmp_strlen16610, sizeof(char));
      strcpy(tmp_str16610, tmp_str16626);
      strcat(tmp_str16610, " = strlen(");
      int tmp_strlen16603 = strlen(tmp_str16610) + strlen(val) + 1;
      char* tmp_str16603 = calloc(tmp_strlen16603, sizeof(char));
      strcpy(tmp_str16603, tmp_str16610);
      strcat(tmp_str16603, val);
      int tmp_strlen16586 = strlen(tmp_str16603) + strlen(") + strlen(") + 1;
      char* tmp_str16586 = calloc(tmp_strlen16586, sizeof(char));
      strcpy(tmp_str16586, tmp_str16603);
      strcat(tmp_str16586, ") + strlen(");
      int tmp_strlen16577 = strlen(tmp_str16586) + strlen(val_b) + 1;
      char* tmp_str16577 = calloc(tmp_strlen16577, sizeof(char));
      strcpy(tmp_str16577, tmp_str16586);
      strcat(tmp_str16577, val_b);
      int tmp_strlen16563 = strlen(tmp_str16577) + strlen(") + 1;\n") + 1;
      char* tmp_str16563 = calloc(tmp_strlen16563, sizeof(char));
      strcpy(tmp_str16563, tmp_str16577);
      strcat(tmp_str16563, ") + 1;\n");
      setup = tmp_str16563;
      int tmp_strlen16527 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str16527 = calloc(tmp_strlen16527, sizeof(char));
      strcpy(tmp_str16527, setup);
      strcat(tmp_str16527, indent);
      int tmp_strlen16515 = strlen(tmp_str16527) + strlen("char* ") + 1;
      char* tmp_str16515 = calloc(tmp_strlen16515, sizeof(char));
      strcpy(tmp_str16515, tmp_str16527);
      strcat(tmp_str16515, "char* ");
      int tmp_strlen16504 = strlen(tmp_str16515) + strlen(tmp_str) + 1;
      char* tmp_str16504 = calloc(tmp_strlen16504, sizeof(char));
      strcpy(tmp_str16504, tmp_str16515);
      strcat(tmp_str16504, tmp_str);
      int tmp_strlen16488 = strlen(tmp_str16504) + strlen(" = calloc(") + 1;
      char* tmp_str16488 = calloc(tmp_strlen16488, sizeof(char));
      strcpy(tmp_str16488, tmp_str16504);
      strcat(tmp_str16488, " = calloc(");
      int tmp_strlen16474 = strlen(tmp_str16488) + strlen(tmp_strlen) + 1;
      char* tmp_str16474 = calloc(tmp_strlen16474, sizeof(char));
      strcpy(tmp_str16474, tmp_str16488);
      strcat(tmp_str16474, tmp_strlen);
      int tmp_strlen16450 = strlen(tmp_str16474) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str16450 = calloc(tmp_strlen16450, sizeof(char));
      strcpy(tmp_str16450, tmp_str16474);
      strcat(tmp_str16450, ", sizeof(char));\n");
      setup = tmp_str16450;
      int tmp_strlen16414 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str16414 = calloc(tmp_strlen16414, sizeof(char));
      strcpy(tmp_str16414, setup);
      strcat(tmp_str16414, indent);
      int tmp_strlen16401 = strlen(tmp_str16414) + strlen("strcpy(") + 1;
      char* tmp_str16401 = calloc(tmp_strlen16401, sizeof(char));
      strcpy(tmp_str16401, tmp_str16414);
      strcat(tmp_str16401, "strcpy(");
      int tmp_strlen16390 = strlen(tmp_str16401) + strlen(tmp_str) + 1;
      char* tmp_str16390 = calloc(tmp_strlen16390, sizeof(char));
      strcpy(tmp_str16390, tmp_str16401);
      strcat(tmp_str16390, tmp_str);
      int tmp_strlen16382 = strlen(tmp_str16390) + strlen(", ") + 1;
      char* tmp_str16382 = calloc(tmp_strlen16382, sizeof(char));
      strcpy(tmp_str16382, tmp_str16390);
      strcat(tmp_str16382, ", ");
      int tmp_strlen16375 = strlen(tmp_str16382) + strlen(val) + 1;
      char* tmp_str16375 = calloc(tmp_strlen16375, sizeof(char));
      strcpy(tmp_str16375, tmp_str16382);
      strcat(tmp_str16375, val);
      int tmp_strlen16365 = strlen(tmp_str16375) + strlen(");\n") + 1;
      char* tmp_str16365 = calloc(tmp_strlen16365, sizeof(char));
      strcpy(tmp_str16365, tmp_str16375);
      strcat(tmp_str16365, ");\n");
      setup = tmp_str16365;
      int tmp_strlen16329 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str16329 = calloc(tmp_strlen16329, sizeof(char));
      strcpy(tmp_str16329, setup);
      strcat(tmp_str16329, indent);
      int tmp_strlen16316 = strlen(tmp_str16329) + strlen("strcat(") + 1;
      char* tmp_str16316 = calloc(tmp_strlen16316, sizeof(char));
      strcpy(tmp_str16316, tmp_str16329);
      strcat(tmp_str16316, "strcat(");
      int tmp_strlen16305 = strlen(tmp_str16316) + strlen(tmp_str) + 1;
      char* tmp_str16305 = calloc(tmp_strlen16305, sizeof(char));
      strcpy(tmp_str16305, tmp_str16316);
      strcat(tmp_str16305, tmp_str);
      int tmp_strlen16297 = strlen(tmp_str16305) + strlen(", ") + 1;
      char* tmp_str16297 = calloc(tmp_strlen16297, sizeof(char));
      strcpy(tmp_str16297, tmp_str16305);
      strcat(tmp_str16297, ", ");
      int tmp_strlen16288 = strlen(tmp_str16297) + strlen(val_b) + 1;
      char* tmp_str16288 = calloc(tmp_strlen16288, sizeof(char));
      strcpy(tmp_str16288, tmp_str16297);
      strcat(tmp_str16288, val_b);
      int tmp_strlen16278 = strlen(tmp_str16288) + strlen(");\n") + 1;
      char* tmp_str16278 = calloc(tmp_strlen16278, sizeof(char));
      strcpy(tmp_str16278, tmp_str16288);
      strcat(tmp_str16278, ");\n");
      setup = tmp_str16278;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen16180 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str16180 = calloc(tmp_strlen16180, sizeof(char));
        strcpy(tmp_str16180, "(strcmp(");
        strcat(tmp_str16180, val);
        int tmp_strlen16172 = strlen(tmp_str16180) + strlen(", ") + 1;
        char* tmp_str16172 = calloc(tmp_strlen16172, sizeof(char));
        strcpy(tmp_str16172, tmp_str16180);
        strcat(tmp_str16172, ", ");
        int tmp_strlen16163 = strlen(tmp_str16172) + strlen(val_b) + 1;
        char* tmp_str16163 = calloc(tmp_strlen16163, sizeof(char));
        strcpy(tmp_str16163, tmp_str16172);
        strcat(tmp_str16163, val_b);
        int tmp_strlen16150 = strlen(tmp_str16163) + strlen(") == 0)") + 1;
        char* tmp_str16150 = calloc(tmp_strlen16150, sizeof(char));
        strcpy(tmp_str16150, tmp_str16163);
        strcat(tmp_str16150, ") == 0)");
        val = tmp_str16150;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen16077 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str16077 = calloc(tmp_strlen16077, sizeof(char));
          strcpy(tmp_str16077, "(strcmp(");
          strcat(tmp_str16077, val);
          int tmp_strlen16069 = strlen(tmp_str16077) + strlen(", ") + 1;
          char* tmp_str16069 = calloc(tmp_strlen16069, sizeof(char));
          strcpy(tmp_str16069, tmp_str16077);
          strcat(tmp_str16069, ", ");
          int tmp_strlen16060 = strlen(tmp_str16069) + strlen(val_b) + 1;
          char* tmp_str16060 = calloc(tmp_strlen16060, sizeof(char));
          strcpy(tmp_str16060, tmp_str16069);
          strcat(tmp_str16060, val_b);
          int tmp_strlen16047 = strlen(tmp_str16060) + strlen(") != 0)") + 1;
          char* tmp_str16047 = calloc(tmp_strlen16047, sizeof(char));
          strcpy(tmp_str16047, tmp_str16060);
          strcat(tmp_str16047, ") != 0)");
          val = tmp_str16047;
        } else {
          int tmp_strlen16001 = strlen("(") + strlen(val) + 1;
          char* tmp_str16001 = calloc(tmp_strlen16001, sizeof(char));
          strcpy(tmp_str16001, "(");
          strcat(tmp_str16001, val);
          int tmp_strlen15993 = strlen(tmp_str16001) + strlen(") ") + 1;
          char* tmp_str15993 = calloc(tmp_strlen15993, sizeof(char));
          strcpy(tmp_str15993, tmp_str16001);
          strcat(tmp_str15993, ") ");
          int tmp_strlen15983 = strlen(tmp_str15993) + strlen(op_str) + 1;
          char* tmp_str15983 = calloc(tmp_strlen15983, sizeof(char));
          strcpy(tmp_str15983, tmp_str15993);
          strcat(tmp_str15983, op_str);
          int tmp_strlen15975 = strlen(tmp_str15983) + strlen(" (") + 1;
          char* tmp_str15975 = calloc(tmp_strlen15975, sizeof(char));
          strcpy(tmp_str15975, tmp_str15983);
          strcat(tmp_str15975, " (");
          int tmp_strlen15966 = strlen(tmp_str15975) + strlen(val_b) + 1;
          char* tmp_str15966 = calloc(tmp_strlen15966, sizeof(char));
          strcpy(tmp_str15966, tmp_str15975);
          strcat(tmp_str15966, val_b);
          int tmp_strlen15959 = strlen(tmp_str15966) + strlen(")") + 1;
          char* tmp_str15959 = calloc(tmp_strlen15959, sizeof(char));
          strcpy(tmp_str15959, tmp_str15966);
          strcat(tmp_str15959, ")");
          val = tmp_str15959;
        }
      }
    }
    Peek_results tmp_results15940 = Peek(src);
    op = tmp_results15940.result1;
    tok_str = tmp_results15940.result2;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results15757 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results15757.result1;
  setup = tmp_results15757.result2;
  expr = tmp_results15757.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results15523 = TranslateExpr(src, indent);
  src = tmp_results15523.result1;
  expr_setup = tmp_results15523.result2;
  expr_value = tmp_results15523.result3;
  int tok;
  char* tok_str;
  Peek_results tmp_results15421 = Peek(src);
  tok = tmp_results15421.result1;
  tok_str = tmp_results15421.result2;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results15250 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results15250.result1;
    tok_str = tmp_results15250.result2;
    TranslateExpr_results tmp_results15198 = TranslateExpr(src, indent);
    src = tmp_results15198.result1;
    expr_setup = tmp_results15198.result2;
    expr_value = tmp_results15198.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen15056 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str15056 = calloc(tmp_strlen15056, sizeof(char));
    strcpy(tmp_str15056, exprs_setup);
    strcat(tmp_str15056, expr_setup);
    exprs_setup = tmp_str15056;
    int tmp_strlen15014 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str15014 = calloc(tmp_strlen15014, sizeof(char));
    strcpy(tmp_str15014, exprs_value);
    strcat(tmp_str15014, ", ");
    int tmp_strlen15000 = strlen(tmp_str15014) + strlen(expr_value) + 1;
    char* tmp_str15000 = calloc(tmp_strlen15000, sizeof(char));
    strcpy(tmp_str15000, tmp_str15014);
    strcat(tmp_str15000, expr_value);
    exprs_value = tmp_str15000;
    Peek_results tmp_results14991 = Peek(src);
    tok = tmp_results14991.result1;
    tok_str = tmp_results14991.result2;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results14820 = ConsumeIdent(src);
  src = tmp_results14820.result1;
  name = tmp_results14820.result2;
  char* tok_str;
  ConsumeToken_results tmp_results14762 = ConsumeToken(src, TOK_COLON);
  src = tmp_results14762.result1;
  tok_str = tmp_results14762.result2;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results14673 = TranslateType(src);
  src = tmp_results14673.result1;
  typ = tmp_results14673.result2;
  typ_str = tmp_results14673.result3;
  int tmp_strlen14598 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str14598 = calloc(tmp_strlen14598, sizeof(char));
  strcpy(tmp_str14598, typ_str);
  strcat(tmp_str14598, " ");
  int tmp_strlen14590 = strlen(tmp_str14598) + strlen(name) + 1;
  char* tmp_str14590 = calloc(tmp_strlen14590, sizeof(char));
  strcpy(tmp_str14590, tmp_str14598);
  strcat(tmp_str14590, name);
  char* out = tmp_str14590;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results14465 = ConsumeToken(src, TOK_LET);
  src = tmp_results14465.result1;
  tok_str = tmp_results14465.result2;
  char* out;
  TranslateConstOrVar_results tmp_results14399 = TranslateConstOrVar(src);
  src = tmp_results14399.result1;
  out = tmp_results14399.result2;
  int tmp_strlen14338 = strlen("const ") + strlen(out) + 1;
  char* tmp_str14338 = calloc(tmp_strlen14338, sizeof(char));
  strcpy(tmp_str14338, "const ");
  strcat(tmp_str14338, out);
  out = tmp_str14338;
  ConsumeToken_results tmp_results14333 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results14333.result1;
  tok_str = tmp_results14333.result2;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results14242 = TranslateExpr(src, indent);
  src = tmp_results14242.result1;
  setup = tmp_results14242.result2;
  val = tmp_results14242.result3;
  ConsumeToken_results tmp_results14193 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results14193.result1;
  tok_str = tmp_results14193.result2;
  int tmp_strlen14125 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str14125 = calloc(tmp_strlen14125, sizeof(char));
  strcpy(tmp_str14125, out);
  strcat(tmp_str14125, " = ");
  int tmp_strlen14118 = strlen(tmp_str14125) + strlen(val) + 1;
  char* tmp_str14118 = calloc(tmp_strlen14118, sizeof(char));
  strcpy(tmp_str14118, tmp_str14125);
  strcat(tmp_str14118, val);
  int tmp_strlen14109 = strlen(tmp_str14118) + strlen(";\n") + 1;
  char* tmp_str14109 = calloc(tmp_strlen14109, sizeof(char));
  strcpy(tmp_str14109, tmp_str14118);
  strcat(tmp_str14109, ";\n");
  out = tmp_str14109;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results13984 = TranslateConstDecl(src, indent);
  src = tmp_results13984.result1;
  out = tmp_results13984.result2;
  int tmp_strlen13912 = strlen(indent) + strlen(out) + 1;
  char* tmp_str13912 = calloc(tmp_strlen13912, sizeof(char));
  strcpy(tmp_str13912, indent);
  strcat(tmp_str13912, out);
  return (TranslateConstDeclStmt_results){src, tmp_str13912};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results13788 = ConsumeToken(src, TOK_VAR);
  src = tmp_results13788.result1;
  tok_str = tmp_results13788.result2;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results13675 = TranslateConstOrVar(src);
  src = tmp_results13675.result1;
  out = tmp_results13675.result2;
  Peek_results tmp_results13635 = Peek(src);
  tok = tmp_results13635.result1;
  tok_str = tmp_results13635.result2;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results13575 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results13575.result1;
    tok_str = tmp_results13575.result2;
    TranslateExpr_results tmp_results13522 = TranslateExpr(src, indent);
    src = tmp_results13522.result1;
    setup = tmp_results13522.result2;
    val = tmp_results13522.result3;
    ConsumeToken_results tmp_results13469 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results13469.result1;
    tok_str = tmp_results13469.result2;
    int tmp_strlen13397 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str13397 = calloc(tmp_strlen13397, sizeof(char));
    strcpy(tmp_str13397, out);
    strcat(tmp_str13397, " = ");
    int tmp_strlen13390 = strlen(tmp_str13397) + strlen(val) + 1;
    char* tmp_str13390 = calloc(tmp_strlen13390, sizeof(char));
    strcpy(tmp_str13390, tmp_str13397);
    strcat(tmp_str13390, val);
    out = tmp_str13390;
  }
  int tmp_strlen13358 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str13358 = calloc(tmp_strlen13358, sizeof(char));
  strcpy(tmp_str13358, setup);
  strcat(tmp_str13358, indent);
  int tmp_strlen13351 = strlen(tmp_str13358) + strlen(out) + 1;
  char* tmp_str13351 = calloc(tmp_strlen13351, sizeof(char));
  strcpy(tmp_str13351, tmp_str13358);
  strcat(tmp_str13351, out);
  int tmp_strlen13342 = strlen(tmp_str13351) + strlen(";\n") + 1;
  char* tmp_str13342 = calloc(tmp_strlen13342, sizeof(char));
  strcpy(tmp_str13342, tmp_str13351);
  strcat(tmp_str13342, ";\n");
  out = tmp_str13342;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen13187 = (x) - (0) + 1;
  char* tmp_str13187 = calloc(tmp_strlen13187, sizeof(char));
  strncpy(tmp_str13187, src + 0, tmp_strlen13187 - 1);
  tmp_str13187[tmp_strlen13187 - 1] = 0;
  char* lhs = tmp_str13187;
  int tmp_strlen13157 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str13157 = calloc(tmp_strlen13157, sizeof(char));
  strncpy(tmp_str13157, src + (x) + (1), tmp_strlen13157 - 1);
  tmp_str13157[tmp_strlen13157 - 1] = 0;
  char* rhs = tmp_str13157;
  char* lhs_ident;
  ConsumeIdent_results tmp_results13120 = ConsumeIdent(lhs);
  lhs = tmp_results13120.result1;
  lhs_ident = tmp_results13120.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results13004 = TranslateExpr(rhs, indent);
  rhs = tmp_results13004.result1;
  setup = tmp_results13004.result2;
  rhs_expr = tmp_results13004.result3;
  int lhs_tok;
  char* lhs_tok_str;
  int rhs_tok;
  char* rhs_tok_str;
  Peek_results tmp_results12852 = Peek(lhs);
  lhs_tok = tmp_results12852.result1;
  lhs_tok_str = tmp_results12852.result2;
  Peek_results tmp_results12815 = Peek(rhs);
  rhs_tok = tmp_results12815.result1;
  rhs_tok_str = tmp_results12815.result2;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results12690 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results12690.result1;
    func_name = tmp_results12690.result2;
    int tmp_strlen12582 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str12582 = calloc(tmp_strlen12582, sizeof(char));
    strcpy(tmp_str12582, "tmp_results");
    strcat(tmp_str12582, itoa(strlen(src)));
    char* tmp_results = tmp_str12582;
    char* out = setup;
    int tmp_strlen12522 = strlen(out) + strlen(indent) + 1;
    char* tmp_str12522 = calloc(tmp_strlen12522, sizeof(char));
    strcpy(tmp_str12522, out);
    strcat(tmp_str12522, indent);
    int tmp_strlen12509 = strlen(tmp_str12522) + strlen(func_name) + 1;
    char* tmp_str12509 = calloc(tmp_strlen12509, sizeof(char));
    strcpy(tmp_str12509, tmp_str12522);
    strcat(tmp_str12509, func_name);
    int tmp_strlen12494 = strlen(tmp_str12509) + strlen("_results ") + 1;
    char* tmp_str12494 = calloc(tmp_strlen12494, sizeof(char));
    strcpy(tmp_str12494, tmp_str12509);
    strcat(tmp_str12494, "_results ");
    int tmp_strlen12479 = strlen(tmp_str12494) + strlen(tmp_results) + 1;
    char* tmp_str12479 = calloc(tmp_strlen12479, sizeof(char));
    strcpy(tmp_str12479, tmp_str12494);
    strcat(tmp_str12479, tmp_results);
    int tmp_strlen12470 = strlen(tmp_str12479) + strlen(" = ") + 1;
    char* tmp_str12470 = calloc(tmp_strlen12470, sizeof(char));
    strcpy(tmp_str12470, tmp_str12479);
    strcat(tmp_str12470, " = ");
    int tmp_strlen12458 = strlen(tmp_str12470) + strlen(rhs_expr) + 1;
    char* tmp_str12458 = calloc(tmp_strlen12458, sizeof(char));
    strcpy(tmp_str12458, tmp_str12470);
    strcat(tmp_str12458, rhs_expr);
    int tmp_strlen12449 = strlen(tmp_str12458) + strlen(";\n") + 1;
    char* tmp_str12449 = calloc(tmp_strlen12449, sizeof(char));
    strcpy(tmp_str12449, tmp_str12458);
    strcat(tmp_str12449, ";\n");
    out = tmp_str12449;
    int tmp_strlen12421 = strlen(out) + strlen(indent) + 1;
    char* tmp_str12421 = calloc(tmp_strlen12421, sizeof(char));
    strcpy(tmp_str12421, out);
    strcat(tmp_str12421, indent);
    int tmp_strlen12408 = strlen(tmp_str12421) + strlen(lhs_ident) + 1;
    char* tmp_str12408 = calloc(tmp_strlen12408, sizeof(char));
    strcpy(tmp_str12408, tmp_str12421);
    strcat(tmp_str12408, lhs_ident);
    int tmp_strlen12399 = strlen(tmp_str12408) + strlen(" = ") + 1;
    char* tmp_str12399 = calloc(tmp_strlen12399, sizeof(char));
    strcpy(tmp_str12399, tmp_str12408);
    strcat(tmp_str12399, " = ");
    int tmp_strlen12384 = strlen(tmp_str12399) + strlen(tmp_results) + 1;
    char* tmp_str12384 = calloc(tmp_strlen12384, sizeof(char));
    strcpy(tmp_str12384, tmp_str12399);
    strcat(tmp_str12384, tmp_results);
    int tmp_strlen12367 = strlen(tmp_str12384) + strlen(".result1;\n") + 1;
    char* tmp_str12367 = calloc(tmp_strlen12367, sizeof(char));
    strcpy(tmp_str12367, tmp_str12384);
    strcat(tmp_str12367, ".result1;\n");
    out = tmp_str12367;
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results12241 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results12241.result1;
      lhs_tok_str = tmp_results12241.result2;
      ConsumeIdent_results tmp_results12181 = ConsumeIdent(lhs);
      lhs = tmp_results12181.result1;
      lhs_ident = tmp_results12181.result2;
      int tmp_strlen12115 = strlen(out) + strlen(indent) + 1;
      char* tmp_str12115 = calloc(tmp_strlen12115, sizeof(char));
      strcpy(tmp_str12115, out);
      strcat(tmp_str12115, indent);
      int tmp_strlen12102 = strlen(tmp_str12115) + strlen(lhs_ident) + 1;
      char* tmp_str12102 = calloc(tmp_strlen12102, sizeof(char));
      strcpy(tmp_str12102, tmp_str12115);
      strcat(tmp_str12102, lhs_ident);
      int tmp_strlen12093 = strlen(tmp_str12102) + strlen(" = ") + 1;
      char* tmp_str12093 = calloc(tmp_strlen12093, sizeof(char));
      strcpy(tmp_str12093, tmp_str12102);
      strcat(tmp_str12093, " = ");
      int tmp_strlen12078 = strlen(tmp_str12093) + strlen(tmp_results) + 1;
      char* tmp_str12078 = calloc(tmp_strlen12078, sizeof(char));
      strcpy(tmp_str12078, tmp_str12093);
      strcat(tmp_str12078, tmp_results);
      int tmp_strlen12065 = strlen(tmp_str12078) + strlen(".result") + 1;
      char* tmp_str12065 = calloc(tmp_strlen12065, sizeof(char));
      strcpy(tmp_str12065, tmp_str12078);
      strcat(tmp_str12065, ".result");
      int tmp_strlen12043 = strlen(tmp_str12065) + strlen(itoa(result_count)) + 1;
      char* tmp_str12043 = calloc(tmp_strlen12043, sizeof(char));
      strcpy(tmp_str12043, tmp_str12065);
      strcat(tmp_str12043, itoa(result_count));
      int tmp_strlen12034 = strlen(tmp_str12043) + strlen(";\n") + 1;
      char* tmp_str12034 = calloc(tmp_strlen12034, sizeof(char));
      strcpy(tmp_str12034, tmp_str12043);
      strcat(tmp_str12034, ";\n");
      out = tmp_str12034;
      Peek_results tmp_results12021 = Peek(lhs);
      lhs_tok = tmp_results12021.result1;
      lhs_tok_str = tmp_results12021.result2;
    }
    char* tok_str;
    ConsumeToken_results tmp_results11942 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results11942.result1;
    tok_str = tmp_results11942.result2;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen11817 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str11817 = calloc(tmp_strlen11817, sizeof(char));
  strcpy(tmp_str11817, indent);
  strcat(tmp_str11817, lhs_ident);
  int tmp_strlen11808 = strlen(tmp_str11817) + strlen(" = ") + 1;
  char* tmp_str11808 = calloc(tmp_strlen11808, sizeof(char));
  strcpy(tmp_str11808, tmp_str11817);
  strcat(tmp_str11808, " = ");
  int tmp_strlen11796 = strlen(tmp_str11808) + strlen(rhs_expr) + 1;
  char* tmp_str11796 = calloc(tmp_strlen11796, sizeof(char));
  strcpy(tmp_str11796, tmp_str11808);
  strcat(tmp_str11796, rhs_expr);
  int tmp_strlen11787 = strlen(tmp_str11796) + strlen(";\n") + 1;
  char* tmp_str11787 = calloc(tmp_strlen11787, sizeof(char));
  strcpy(tmp_str11787, tmp_str11796);
  strcat(tmp_str11787, ";\n");
  char* assignments = tmp_str11787;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results11747 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results11747.result1;
    lhs_tok_str = tmp_results11747.result2;
    ConsumeToken_results tmp_results11691 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results11691.result1;
    rhs_tok_str = tmp_results11691.result2;
    ConsumeIdent_results tmp_results11635 = ConsumeIdent(lhs);
    lhs = tmp_results11635.result1;
    lhs_ident = tmp_results11635.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results11557 = TranslateExpr(rhs, indent);
    rhs = tmp_results11557.result1;
    rhs_expr_setup = tmp_results11557.result2;
    rhs_expr = tmp_results11557.result3;
    int tmp_strlen11459 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str11459 = calloc(tmp_strlen11459, sizeof(char));
    strcpy(tmp_str11459, setup);
    strcat(tmp_str11459, rhs_expr_setup);
    setup = tmp_str11459;
    int tmp_strlen11415 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str11415 = calloc(tmp_strlen11415, sizeof(char));
    strcpy(tmp_str11415, assignments);
    strcat(tmp_str11415, indent);
    int tmp_strlen11402 = strlen(tmp_str11415) + strlen(lhs_ident) + 1;
    char* tmp_str11402 = calloc(tmp_strlen11402, sizeof(char));
    strcpy(tmp_str11402, tmp_str11415);
    strcat(tmp_str11402, lhs_ident);
    int tmp_strlen11393 = strlen(tmp_str11402) + strlen(" = ") + 1;
    char* tmp_str11393 = calloc(tmp_strlen11393, sizeof(char));
    strcpy(tmp_str11393, tmp_str11402);
    strcat(tmp_str11393, " = ");
    int tmp_strlen11381 = strlen(tmp_str11393) + strlen(rhs_expr) + 1;
    char* tmp_str11381 = calloc(tmp_strlen11381, sizeof(char));
    strcpy(tmp_str11381, tmp_str11393);
    strcat(tmp_str11381, rhs_expr);
    int tmp_strlen11372 = strlen(tmp_str11381) + strlen(";\n") + 1;
    char* tmp_str11372 = calloc(tmp_strlen11372, sizeof(char));
    strcpy(tmp_str11372, tmp_str11381);
    strcat(tmp_str11372, ";\n");
    assignments = tmp_str11372;
    Peek_results tmp_results11363 = Peek(lhs);
    lhs_tok = tmp_results11363.result1;
    lhs_tok_str = tmp_results11363.result2;
  }
  char* tok_str;
  ConsumeToken_results tmp_results11296 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results11296.result1;
  tok_str = tmp_results11296.result2;
  int tmp_strlen11214 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str11214 = calloc(tmp_strlen11214, sizeof(char));
  strcpy(tmp_str11214, setup);
  strcat(tmp_str11214, assignments);
  return (TranslateAssignStmt_results){src, tmp_str11214};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results11093 = ConsumeToken(src, TOK_IF);
  src = tmp_results11093.result1;
  tok_str = tmp_results11093.result2;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results11000 = TranslateExpr(src, indent);
  src = tmp_results11000.result1;
  cond_setup = tmp_results11000.result2;
  cond = tmp_results11000.result3;
  ConsumeToken_results tmp_results10945 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results10945.result1;
  tok_str = tmp_results10945.result2;
  char* out = cond_setup;
  int tmp_strlen10844 = strlen(out) + strlen(indent) + 1;
  char* tmp_str10844 = calloc(tmp_strlen10844, sizeof(char));
  strcpy(tmp_str10844, out);
  strcat(tmp_str10844, indent);
  int tmp_strlen10834 = strlen(tmp_str10844) + strlen("if (") + 1;
  char* tmp_str10834 = calloc(tmp_strlen10834, sizeof(char));
  strcpy(tmp_str10834, tmp_str10844);
  strcat(tmp_str10834, "if (");
  int tmp_strlen10826 = strlen(tmp_str10834) + strlen(cond) + 1;
  char* tmp_str10826 = calloc(tmp_strlen10826, sizeof(char));
  strcpy(tmp_str10826, tmp_str10834);
  strcat(tmp_str10826, cond);
  int tmp_strlen10815 = strlen(tmp_str10826) + strlen(") {\n") + 1;
  char* tmp_str10815 = calloc(tmp_strlen10815, sizeof(char));
  strcpy(tmp_str10815, tmp_str10826);
  strcat(tmp_str10815, ") {\n");
  out = tmp_str10815;
  char* body;
  int tmp_strlen10734 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str10734 = calloc(tmp_strlen10734, sizeof(char));
  strcpy(tmp_str10734, indent);
  strcat(tmp_str10734, SINGLE_INDENT);
  TranslateStmts_results tmp_results10789 = TranslateStmts(src, tmp_str10734, func_name);
  src = tmp_results10789.result1;
  body = tmp_results10789.result2;
  ConsumeToken_results tmp_results10717 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results10717.result1;
  tok_str = tmp_results10717.result2;
  int tmp_strlen10651 = strlen(out) + strlen(body) + 1;
  char* tmp_str10651 = calloc(tmp_strlen10651, sizeof(char));
  strcpy(tmp_str10651, out);
  strcat(tmp_str10651, body);
  out = tmp_str10651;
  int tmp_strlen10627 = strlen(out) + strlen(indent) + 1;
  char* tmp_str10627 = calloc(tmp_strlen10627, sizeof(char));
  strcpy(tmp_str10627, out);
  strcat(tmp_str10627, indent);
  int tmp_strlen10620 = strlen(tmp_str10627) + strlen("}") + 1;
  char* tmp_str10620 = calloc(tmp_strlen10620, sizeof(char));
  strcpy(tmp_str10620, tmp_str10627);
  strcat(tmp_str10620, "}");
  out = tmp_str10620;
  int tok;
  Peek_results tmp_results10598 = Peek(src);
  tok = tmp_results10598.result1;
  tok_str = tmp_results10598.result2;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen10517 = strlen(out) + strlen("\n") + 1;
    char* tmp_str10517 = calloc(tmp_strlen10517, sizeof(char));
    strcpy(tmp_str10517, out);
    strcat(tmp_str10517, "\n");
    return (TranslateIfStmt_results){src, tmp_str10517};
  }
  ConsumeToken_results tmp_results10506 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results10506.result1;
  tok_str = tmp_results10506.result2;
  Peek_results tmp_results10459 = Peek(src);
  tok = tmp_results10459.result1;
  tok_str = tmp_results10459.result2;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen10318 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str10318 = calloc(tmp_strlen10318, sizeof(char));
    strcpy(tmp_str10318, indent);
    strcat(tmp_str10318, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results10378 = TranslateIfStmt(src, tmp_str10318, func_name);
    src = tmp_results10378.result1;
    else_out = tmp_results10378.result2;
    int tmp_strlen10273 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str10273 = calloc(tmp_strlen10273, sizeof(char));
    strcpy(tmp_str10273, out);
    strcat(tmp_str10273, " else {\n");
    out = tmp_str10273;
    int tmp_strlen10243 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str10243 = calloc(tmp_strlen10243, sizeof(char));
    strcpy(tmp_str10243, out);
    strcat(tmp_str10243, else_out);
    out = tmp_str10243;
    int tmp_strlen10215 = strlen(out) + strlen(indent) + 1;
    char* tmp_str10215 = calloc(tmp_strlen10215, sizeof(char));
    strcpy(tmp_str10215, out);
    strcat(tmp_str10215, indent);
    int tmp_strlen10206 = strlen(tmp_str10215) + strlen("}\n") + 1;
    char* tmp_str10206 = calloc(tmp_strlen10206, sizeof(char));
    strcpy(tmp_str10206, tmp_str10215);
    strcat(tmp_str10206, "}\n");
    out = tmp_str10206;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results10171 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results10171.result1;
  tok_str = tmp_results10171.result2;
  int tmp_strlen10063 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str10063 = calloc(tmp_strlen10063, sizeof(char));
  strcpy(tmp_str10063, indent);
  strcat(tmp_str10063, SINGLE_INDENT);
  TranslateStmts_results tmp_results10122 = TranslateStmts(src, tmp_str10063, func_name);
  src = tmp_results10122.result1;
  else_out = tmp_results10122.result2;
  ConsumeToken_results tmp_results10046 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results10046.result1;
  tok_str = tmp_results10046.result2;
  int tmp_strlen9973 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str9973 = calloc(tmp_strlen9973, sizeof(char));
  strcpy(tmp_str9973, out);
  strcat(tmp_str9973, " else {\n");
  out = tmp_str9973;
  int tmp_strlen9947 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str9947 = calloc(tmp_strlen9947, sizeof(char));
  strcpy(tmp_str9947, out);
  strcat(tmp_str9947, else_out);
  out = tmp_str9947;
  int tmp_strlen9923 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9923 = calloc(tmp_strlen9923, sizeof(char));
  strcpy(tmp_str9923, out);
  strcat(tmp_str9923, indent);
  int tmp_strlen9914 = strlen(tmp_str9923) + strlen("}\n") + 1;
  char* tmp_str9914 = calloc(tmp_strlen9914, sizeof(char));
  strcpy(tmp_str9914, tmp_str9923);
  strcat(tmp_str9914, "}\n");
  out = tmp_str9914;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results9755 = ConsumeToken(src, TOK_FOR);
  src = tmp_results9755.result1;
  tok_str = tmp_results9755.result2;
  Peek_results tmp_results9709 = Peek(src);
  tok = tmp_results9709.result1;
  tok_str = tmp_results9709.result2;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen9521 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str9521 = calloc(tmp_strlen9521, sizeof(char));
    strcpy(tmp_str9521, indent);
    strcat(tmp_str9521, SINGLE_INDENT);
    TranslateExpr_results tmp_results9587 = TranslateExpr(src, tmp_str9521);
    src = tmp_results9587.result1;
    cond_setup = tmp_results9587.result2;
    cond = tmp_results9587.result3;
  }
  ConsumeToken_results tmp_results9509 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results9509.result1;
  tok_str = tmp_results9509.result2;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen9385 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str9385 = calloc(tmp_strlen9385, sizeof(char));
    strcpy(tmp_str9385, indent);
    strcat(tmp_str9385, "while (");
    int tmp_strlen9377 = strlen(tmp_str9385) + strlen(cond) + 1;
    char* tmp_str9377 = calloc(tmp_strlen9377, sizeof(char));
    strcpy(tmp_str9377, tmp_str9385);
    strcat(tmp_str9377, cond);
    int tmp_strlen9366 = strlen(tmp_str9377) + strlen(") {\n") + 1;
    char* tmp_str9366 = calloc(tmp_strlen9366, sizeof(char));
    strcpy(tmp_str9366, tmp_str9377);
    strcat(tmp_str9366, ") {\n");
    out = tmp_str9366;
  } else {
    int tmp_strlen9310 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str9310 = calloc(tmp_strlen9310, sizeof(char));
    strcpy(tmp_str9310, indent);
    strcat(tmp_str9310, "while (true) {\n");
    out = tmp_str9310;
    int tmp_strlen9278 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str9278 = calloc(tmp_strlen9278, sizeof(char));
    strcpy(tmp_str9278, out);
    strcat(tmp_str9278, cond_setup);
    out = tmp_str9278;
    int tmp_strlen9250 = strlen(out) + strlen(indent) + 1;
    char* tmp_str9250 = calloc(tmp_strlen9250, sizeof(char));
    strcpy(tmp_str9250, out);
    strcat(tmp_str9250, indent);
    int tmp_strlen9233 = strlen(tmp_str9250) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str9233 = calloc(tmp_strlen9233, sizeof(char));
    strcpy(tmp_str9233, tmp_str9250);
    strcat(tmp_str9233, SINGLE_INDENT);
    int tmp_strlen9221 = strlen(tmp_str9233) + strlen("if (!(") + 1;
    char* tmp_str9221 = calloc(tmp_strlen9221, sizeof(char));
    strcpy(tmp_str9221, tmp_str9233);
    strcat(tmp_str9221, "if (!(");
    int tmp_strlen9213 = strlen(tmp_str9221) + strlen(cond) + 1;
    char* tmp_str9213 = calloc(tmp_strlen9213, sizeof(char));
    strcpy(tmp_str9213, tmp_str9221);
    strcat(tmp_str9213, cond);
    int tmp_strlen9196 = strlen(tmp_str9213) + strlen(")) break;\n") + 1;
    char* tmp_str9196 = calloc(tmp_strlen9196, sizeof(char));
    strcpy(tmp_str9196, tmp_str9213);
    strcat(tmp_str9196, ")) break;\n");
    out = tmp_str9196;
  }
  char* body;
  int tmp_strlen9109 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str9109 = calloc(tmp_strlen9109, sizeof(char));
  strcpy(tmp_str9109, indent);
  strcat(tmp_str9109, SINGLE_INDENT);
  TranslateStmts_results tmp_results9164 = TranslateStmts(src, tmp_str9109, func_name);
  src = tmp_results9164.result1;
  body = tmp_results9164.result2;
  ConsumeToken_results tmp_results9092 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results9092.result1;
  tok_str = tmp_results9092.result2;
  int tmp_strlen9026 = strlen(out) + strlen(body) + 1;
  char* tmp_str9026 = calloc(tmp_strlen9026, sizeof(char));
  strcpy(tmp_str9026, out);
  strcat(tmp_str9026, body);
  out = tmp_str9026;
  int tmp_strlen9002 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9002 = calloc(tmp_strlen9002, sizeof(char));
  strcpy(tmp_str9002, out);
  strcat(tmp_str9002, indent);
  int tmp_strlen8993 = strlen(tmp_str9002) + strlen("}\n") + 1;
  char* tmp_str8993 = calloc(tmp_strlen8993, sizeof(char));
  strcpy(tmp_str8993, tmp_str9002);
  strcat(tmp_str8993, "}\n");
  out = tmp_str8993;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results8865 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results8865.result1;
  tok_str = tmp_results8865.result2;
  int tmp_strlen8781 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str8781 = calloc(tmp_strlen8781, sizeof(char));
  strcpy(tmp_str8781, indent);
  strcat(tmp_str8781, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str8781};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results8676 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results8676.result1;
  tok_str = tmp_results8676.result2;
  int tmp_strlen8598 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str8598 = calloc(tmp_strlen8598, sizeof(char));
  strcpy(tmp_str8598, indent);
  strcat(tmp_str8598, "break;");
  return (TranslateBreakStmt_results){src, tmp_str8598};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results8473 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results8473.result1;
  tok_str = tmp_results8473.result2;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results8344 = TranslateExprs(src, indent);
  src = tmp_results8344.result1;
  expr_count = tmp_results8344.result2;
  exprs_setup = tmp_results8344.result3;
  exprs_value = tmp_results8344.result4;
  ConsumeToken_results tmp_results8268 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results8268.result1;
  tok_str = tmp_results8268.result2;
  int tmp_strlen8179 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str8179 = calloc(tmp_strlen8179, sizeof(char));
  strcpy(tmp_str8179, exprs_setup);
  strcat(tmp_str8179, indent);
  int tmp_strlen8166 = strlen(tmp_str8179) + strlen("return ") + 1;
  char* tmp_str8166 = calloc(tmp_strlen8166, sizeof(char));
  strcpy(tmp_str8166, tmp_str8179);
  strcat(tmp_str8166, "return ");
  char* out = tmp_str8166;
  if ((expr_count) > (1)) {
    int tmp_strlen8117 = strlen(out) + strlen("(") + 1;
    char* tmp_str8117 = calloc(tmp_strlen8117, sizeof(char));
    strcpy(tmp_str8117, out);
    strcat(tmp_str8117, "(");
    int tmp_strlen8104 = strlen(tmp_str8117) + strlen(func_name) + 1;
    char* tmp_str8104 = calloc(tmp_strlen8104, sizeof(char));
    strcpy(tmp_str8104, tmp_str8117);
    strcat(tmp_str8104, func_name);
    int tmp_strlen8088 = strlen(tmp_str8104) + strlen("_results){") + 1;
    char* tmp_str8088 = calloc(tmp_strlen8088, sizeof(char));
    strcpy(tmp_str8088, tmp_str8104);
    strcat(tmp_str8088, "_results){");
    out = tmp_str8088;
  }
  int tmp_strlen8053 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str8053 = calloc(tmp_strlen8053, sizeof(char));
  strcpy(tmp_str8053, out);
  strcat(tmp_str8053, exprs_value);
  out = tmp_str8053;
  if ((expr_count) > (1)) {
    int tmp_strlen8003 = strlen(out) + strlen("}") + 1;
    char* tmp_str8003 = calloc(tmp_strlen8003, sizeof(char));
    strcpy(tmp_str8003, out);
    strcat(tmp_str8003, "}");
    out = tmp_str8003;
  }
  int tmp_strlen7974 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str7974 = calloc(tmp_strlen7974, sizeof(char));
  strcpy(tmp_str7974, out);
  strcat(tmp_str7974, ";\n");
  out = tmp_str7974;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results7818 = Peek(src);
  tok = tmp_results7818.result1;
  tok_str = tmp_results7818.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results7741 = TranslateConstDeclStmt(src, indent);
    src = tmp_results7741.result1;
    out = tmp_results7741.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results7631 = TranslateVarDeclStmt(src, indent);
      src = tmp_results7631.result1;
      out = tmp_results7631.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results7524 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results7524.result1;
        out = tmp_results7524.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results7410 = TranslateForStmt(src, indent, func_name);
          src = tmp_results7410.result1;
          out = tmp_results7410.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results7290 = TranslateContinueStmt(src, indent);
            src = tmp_results7290.result1;
            out = tmp_results7290.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results7179 = TranslateBreakStmt(src, indent);
              src = tmp_results7179.result1;
              out = tmp_results7179.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results7070 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results7070.result1;
                out = tmp_results7070.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if ((tok) == (TOK_IDENT)) {
                  char* first_ident;
                  ConsumeIdent_results tmp_results6918 = ConsumeIdent(src);
                  src = tmp_results6918.result1;
                  first_ident = tmp_results6918.result2;
                  Peek_results tmp_results6873 = Peek(src);
                  tok = tmp_results6873.result1;
                  tok_str = tmp_results6873.result2;
                  int tmp_strlen6816 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str6816 = calloc(tmp_strlen6816, sizeof(char));
                  strcpy(tmp_str6816, first_ident);
                  strcat(tmp_str6816, src);
                  src = tmp_str6816;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results6752 = TranslateAssignStmt(src, indent);
                    src = tmp_results6752.result1;
                    out = tmp_results6752.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results6593 = TranslateExpr(src, indent);
                    src = tmp_results6593.result1;
                    setup = tmp_results6593.result2;
                    val = tmp_results6593.result3;
                    ConsumeToken_results tmp_results6536 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results6536.result1;
                    tok_str = tmp_results6536.result2;
                    int tmp_strlen6457 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str6457 = calloc(tmp_strlen6457, sizeof(char));
                    strcpy(tmp_str6457, setup);
                    strcat(tmp_str6457, indent);
                    int tmp_strlen6450 = strlen(tmp_str6457) + strlen(val) + 1;
                    char* tmp_str6450 = calloc(tmp_strlen6450, sizeof(char));
                    strcpy(tmp_str6450, tmp_str6457);
                    strcat(tmp_str6450, val);
                    int tmp_strlen6441 = strlen(tmp_str6450) + strlen(";\n") + 1;
                    char* tmp_str6441 = calloc(tmp_strlen6441, sizeof(char));
                    strcpy(tmp_str6441, tmp_str6450);
                    strcat(tmp_str6441, ";\n");
                    out = tmp_str6441;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen6332 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str6332 = calloc(tmp_strlen6332, sizeof(char));
                  strcpy(tmp_str6332, "unexpected stmt token, got: ");
                  strcat(tmp_str6332, itoa(tok));
                  int tmp_strlen6323 = strlen(tmp_str6332) + strlen(" \"") + 1;
                  char* tmp_str6323 = calloc(tmp_strlen6323, sizeof(char));
                  strcpy(tmp_str6323, tmp_str6332);
                  strcat(tmp_str6323, " \"");
                  int tmp_strlen6312 = strlen(tmp_str6323) + strlen(tok_str) + 1;
                  char* tmp_str6312 = calloc(tmp_strlen6312, sizeof(char));
                  strcpy(tmp_str6312, tmp_str6323);
                  strcat(tmp_str6312, tok_str);
                  int tmp_strlen6304 = strlen(tmp_str6312) + strlen("\"") + 1;
                  char* tmp_str6304 = calloc(tmp_strlen6304, sizeof(char));
                  strcpy(tmp_str6304, tmp_str6312);
                  strcat(tmp_str6304, "\"");
                  printf("%s", tmp_str6304);
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
  Peek_results tmp_results6144 = Peek(src);
  tok = tmp_results6144.result1;
  tok_str = tmp_results6144.result2;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results6022 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results6022.result1;
      tok_str = tmp_results6022.result2;
      Peek_results tmp_results5964 = Peek(src);
      tok = tmp_results5964.result1;
      tok_str = tmp_results5964.result2;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results5871 = TranslateStmt(src, indent, func_name);
    src = tmp_results5871.result1;
    stmt_out = tmp_results5871.result2;
    int tmp_strlen5788 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str5788 = calloc(tmp_strlen5788, sizeof(char));
    strcpy(tmp_str5788, out);
    strcat(tmp_str5788, stmt_out);
    out = tmp_str5788;
    Peek_results tmp_results5779 = Peek(src);
    tok = tmp_results5779.result1;
    tok_str = tmp_results5779.result2;
  }
  return (TranslateStmts_results){src, out};
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results5624 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results5624.result1;
  tok_str = tmp_results5624.result2;
  Peek_results tmp_results5575 = Peek(src);
  tok = tmp_results5575.result1;
  tok_str = tmp_results5575.result2;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results5515 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results5515.result1;
    tok_str = tmp_results5515.result2;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results5414 = TranslateConstOrVar(src);
  src = tmp_results5414.result1;
  args = tmp_results5414.result2;
  Peek_results tmp_results5373 = Peek(src);
  tok = tmp_results5373.result1;
  tok_str = tmp_results5373.result2;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results5313 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results5313.result1;
    tok_str = tmp_results5313.result2;
    char* arg;
    TranslateConstOrVar_results tmp_results5237 = TranslateConstOrVar(src);
    src = tmp_results5237.result1;
    arg = tmp_results5237.result2;
    int tmp_strlen5174 = strlen(args) + strlen(", ") + 1;
    char* tmp_str5174 = calloc(tmp_strlen5174, sizeof(char));
    strcpy(tmp_str5174, args);
    strcat(tmp_str5174, ", ");
    int tmp_strlen5167 = strlen(tmp_str5174) + strlen(arg) + 1;
    char* tmp_str5167 = calloc(tmp_strlen5167, sizeof(char));
    strcpy(tmp_str5167, tmp_str5174);
    strcat(tmp_str5167, arg);
    args = tmp_str5167;
    Peek_results tmp_results5158 = Peek(src);
    tok = tmp_results5158.result1;
    tok_str = tmp_results5158.result2;
  }
  ConsumeToken_results tmp_results5123 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results5123.result1;
  tok_str = tmp_results5123.result2;
  int tmp_strlen5051 = strlen("(") + strlen(args) + 1;
  char* tmp_str5051 = calloc(tmp_strlen5051, sizeof(char));
  strcpy(tmp_str5051, "(");
  strcat(tmp_str5051, args);
  int tmp_strlen5044 = strlen(tmp_str5051) + strlen(")") + 1;
  char* tmp_str5044 = calloc(tmp_strlen5044, sizeof(char));
  strcpy(tmp_str5044, tmp_str5051);
  strcat(tmp_str5044, ")");
  return (TranslateFuncArgs_results){src, tmp_str5044};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  char* tok_str;
  Peek_results tmp_results4868 = Peek(src);
  tok = tmp_results4868.result1;
  tok_str = tmp_results4868.result2;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results4808 = TranslateType(src);
    src = tmp_results4808.result1;
    typ = tmp_results4808.result2;
    typ_str = tmp_results4808.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results4727 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results4727.result1;
  tok_str = tmp_results4727.result2;
  TranslateType_results tmp_results4678 = TranslateType(src);
  src = tmp_results4678.result1;
  typ = tmp_results4678.result2;
  typ_str = tmp_results4678.result3;
  Peek_results tmp_results4635 = Peek(src);
  tok = tmp_results4635.result1;
  tok_str = tmp_results4635.result2;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results4576 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results4576.result1;
    tok_str = tmp_results4576.result2;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen4435 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str4435 = calloc(tmp_strlen4435, sizeof(char));
  strcpy(tmp_str4435, "typedef struct {\n");
  strcat(tmp_str4435, SINGLE_INDENT);
  int tmp_strlen4424 = strlen(tmp_str4435) + strlen(typ_str) + 1;
  char* tmp_str4424 = calloc(tmp_strlen4424, sizeof(char));
  strcpy(tmp_str4424, tmp_str4435);
  strcat(tmp_str4424, typ_str);
  int tmp_strlen4407 = strlen(tmp_str4424) + strlen(" result1;\n") + 1;
  char* tmp_str4407 = calloc(tmp_strlen4407, sizeof(char));
  strcpy(tmp_str4407, tmp_str4424);
  strcat(tmp_str4407, " result1;\n");
  char* td = tmp_str4407;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results4344 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results4344.result1;
    tok_str = tmp_results4344.result2;
    TranslateType_results tmp_results4292 = TranslateType(src);
    src = tmp_results4292.result1;
    typ = tmp_results4292.result2;
    typ_str = tmp_results4292.result3;
    res_count = (res_count) + (1);
    int tmp_strlen4187 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str4187 = calloc(tmp_strlen4187, sizeof(char));
    strcpy(tmp_str4187, td);
    strcat(tmp_str4187, SINGLE_INDENT);
    int tmp_strlen4176 = strlen(tmp_str4187) + strlen(typ_str) + 1;
    char* tmp_str4176 = calloc(tmp_strlen4176, sizeof(char));
    strcpy(tmp_str4176, tmp_str4187);
    strcat(tmp_str4176, typ_str);
    int tmp_strlen4163 = strlen(tmp_str4176) + strlen(" result") + 1;
    char* tmp_str4163 = calloc(tmp_strlen4163, sizeof(char));
    strcpy(tmp_str4163, tmp_str4176);
    strcat(tmp_str4163, " result");
    int tmp_strlen4144 = strlen(tmp_str4163) + strlen(itoa(res_count)) + 1;
    char* tmp_str4144 = calloc(tmp_strlen4144, sizeof(char));
    strcpy(tmp_str4144, tmp_str4163);
    strcat(tmp_str4144, itoa(res_count));
    int tmp_strlen4135 = strlen(tmp_str4144) + strlen(";\n") + 1;
    char* tmp_str4135 = calloc(tmp_strlen4135, sizeof(char));
    strcpy(tmp_str4135, tmp_str4144);
    strcat(tmp_str4135, ";\n");
    td = tmp_str4135;
    Peek_results tmp_results4126 = Peek(src);
    tok = tmp_results4126.result1;
    tok_str = tmp_results4126.result2;
  }
  ConsumeToken_results tmp_results4091 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results4091.result1;
  tok_str = tmp_results4091.result2;
  int tmp_strlen4027 = strlen(td) + strlen("} ") + 1;
  char* tmp_str4027 = calloc(tmp_strlen4027, sizeof(char));
  strcpy(tmp_str4027, td);
  strcat(tmp_str4027, "} ");
  int tmp_strlen4014 = strlen(tmp_str4027) + strlen(func_name) + 1;
  char* tmp_str4014 = calloc(tmp_strlen4014, sizeof(char));
  strcpy(tmp_str4014, tmp_str4027);
  strcat(tmp_str4014, func_name);
  int tmp_strlen3997 = strlen(tmp_str4014) + strlen("_results;\n") + 1;
  char* tmp_str3997 = calloc(tmp_strlen3997, sizeof(char));
  strcpy(tmp_str3997, tmp_str4014);
  strcat(tmp_str3997, "_results;\n");
  td = tmp_str3997;
  int tmp_strlen3953 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str3953 = calloc(tmp_strlen3953, sizeof(char));
  strcpy(tmp_str3953, func_name);
  strcat(tmp_str3953, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str3953};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* tok_str;
  char* name;
  ConsumeToken_results tmp_results3823 = ConsumeToken(src, TOK_FN);
  src = tmp_results3823.result1;
  tok_str = tmp_results3823.result2;
  ConsumeIdent_results tmp_results3778 = ConsumeIdent(src);
  src = tmp_results3778.result1;
  name = tmp_results3778.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    results_type_name = "int";
  }
  Peek_results tmp_results3571 = Peek(src);
  tok = tmp_results3571.result1;
  tok_str = tmp_results3571.result2;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results3511 = TranslateFuncArgs(src);
    src = tmp_results3511.result1;
    args = tmp_results3511.result2;
    Peek_results tmp_results3468 = Peek(src);
    tok = tmp_results3468.result1;
    tok_str = tmp_results3468.result2;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results3400 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results3400.result1;
      tok_str = tmp_results3400.result2;
      TranslateFuncResults_results tmp_results3343 = TranslateFuncResults(src, name);
      src = tmp_results3343.result1;
      results_type_def = tmp_results3343.result2;
      results_type_name = tmp_results3343.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results3222 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results3222.result1;
  tok_str = tmp_results3222.result2;
  int tmp_strlen3117 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str3117 = calloc(tmp_strlen3117, sizeof(char));
  strcpy(tmp_str3117, SINGLE_INDENT);
  strcat(tmp_str3117, "");
  TranslateStmts_results tmp_results3173 = TranslateStmts(src, tmp_str3117, name);
  src = tmp_results3173.result1;
  stmts_out = tmp_results3173.result2;
  ConsumeToken_results tmp_results3105 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results3105.result1;
  tok_str = tmp_results3105.result2;
  int tmp_strlen3015 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str3015 = calloc(tmp_strlen3015, sizeof(char));
  strcpy(tmp_str3015, results_type_name);
  strcat(tmp_str3015, " ");
  int tmp_strlen3007 = strlen(tmp_str3015) + strlen(name) + 1;
  char* tmp_str3007 = calloc(tmp_strlen3007, sizeof(char));
  strcpy(tmp_str3007, tmp_str3015);
  strcat(tmp_str3007, name);
  int tmp_strlen2999 = strlen(tmp_str3007) + strlen(args) + 1;
  char* tmp_str2999 = calloc(tmp_strlen2999, sizeof(char));
  strcpy(tmp_str2999, tmp_str3007);
  strcat(tmp_str2999, args);
  char* df = tmp_str2999;
  int tmp_strlen2953 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str2953 = calloc(tmp_strlen2953, sizeof(char));
  strcpy(tmp_str2953, results_type_def);
  strcat(tmp_str2953, df);
  int tmp_strlen2944 = strlen(tmp_str2953) + strlen(";\n") + 1;
  char* tmp_str2944 = calloc(tmp_strlen2944, sizeof(char));
  strcpy(tmp_str2944, tmp_str2953);
  strcat(tmp_str2944, ";\n");
  char* decl = tmp_str2944;
  int tmp_strlen2922 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str2922 = calloc(tmp_strlen2922, sizeof(char));
  strcpy(tmp_str2922, df);
  strcat(tmp_str2922, " {\n");
  df = tmp_str2922;
  int tmp_strlen2897 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str2897 = calloc(tmp_strlen2897, sizeof(char));
  strcpy(tmp_str2897, df);
  strcat(tmp_str2897, stmts_out);
  df = tmp_str2897;
  int tmp_strlen2874 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str2874 = calloc(tmp_strlen2874, sizeof(char));
  strcpy(tmp_str2874, df);
  strcat(tmp_str2874, "}\n\n");
  df = tmp_str2874;
  return (TranslateFunc_results){src, decl, df};
}

char* TranslateProgram(char* src) {
  char* out = "";
  int tmp_strlen2734 = strlen(out) + strlen("#include <stdbool.h>\n") + 1;
  char* tmp_str2734 = calloc(tmp_strlen2734, sizeof(char));
  strcpy(tmp_str2734, out);
  strcat(tmp_str2734, "#include <stdbool.h>\n");
  out = tmp_str2734;
  int tmp_strlen2694 = strlen(out) + strlen("#include <stdio.h>\n") + 1;
  char* tmp_str2694 = calloc(tmp_strlen2694, sizeof(char));
  strcpy(tmp_str2694, out);
  strcat(tmp_str2694, "#include <stdio.h>\n");
  out = tmp_str2694;
  int tmp_strlen2653 = strlen(out) + strlen("#include <stdlib.h>\n") + 1;
  char* tmp_str2653 = calloc(tmp_strlen2653, sizeof(char));
  strcpy(tmp_str2653, out);
  strcat(tmp_str2653, "#include <stdlib.h>\n");
  out = tmp_str2653;
  int tmp_strlen2612 = strlen(out) + strlen("#include <string.h>\n") + 1;
  char* tmp_str2612 = calloc(tmp_strlen2612, sizeof(char));
  strcpy(tmp_str2612, out);
  strcat(tmp_str2612, "#include <string.h>\n");
  out = tmp_str2612;
  int tmp_strlen2590 = strlen(out) + strlen("\n") + 1;
  char* tmp_str2590 = calloc(tmp_strlen2590, sizeof(char));
  strcpy(tmp_str2590, out);
  strcat(tmp_str2590, "\n");
  out = tmp_str2590;
  int tmp_strlen2549 = strlen(out) + strlen("char* itoa(int x) {\n") + 1;
  char* tmp_str2549 = calloc(tmp_strlen2549, sizeof(char));
  strcpy(tmp_str2549, out);
  strcat(tmp_str2549, "char* itoa(int x) {\n");
  out = tmp_str2549;
  int tmp_strlen2504 = strlen(out) + strlen("  char* a = malloc(20);\n") + 1;
  char* tmp_str2504 = calloc(tmp_strlen2504, sizeof(char));
  strcpy(tmp_str2504, out);
  strcat(tmp_str2504, "  char* a = malloc(20);\n");
  out = tmp_str2504;
  int tmp_strlen2458 = strlen(out) + strlen("  sprintf(a, \"%i\", x);\n") + 1;
  char* tmp_str2458 = calloc(tmp_strlen2458, sizeof(char));
  strcpy(tmp_str2458, out);
  strcat(tmp_str2458, "  sprintf(a, \"%i\", x);\n");
  out = tmp_str2458;
  int tmp_strlen2425 = strlen(out) + strlen("  return a;\n") + 1;
  char* tmp_str2425 = calloc(tmp_strlen2425, sizeof(char));
  strcpy(tmp_str2425, out);
  strcat(tmp_str2425, "  return a;\n");
  out = tmp_str2425;
  int tmp_strlen2402 = strlen(out) + strlen("}\n") + 1;
  char* tmp_str2402 = calloc(tmp_strlen2402, sizeof(char));
  strcpy(tmp_str2402, out);
  strcat(tmp_str2402, "}\n");
  out = tmp_str2402;
  int tmp_strlen2380 = strlen(out) + strlen("\n") + 1;
  char* tmp_str2380 = calloc(tmp_strlen2380, sizeof(char));
  strcpy(tmp_str2380, out);
  strcat(tmp_str2380, "\n");
  out = tmp_str2380;
  int tmp_strlen2328 = strlen(out) + strlen("char* read(const char* path) {\n") + 1;
  char* tmp_str2328 = calloc(tmp_strlen2328, sizeof(char));
  strcpy(tmp_str2328, out);
  strcat(tmp_str2328, "char* read(const char* path) {\n");
  out = tmp_str2328;
  int tmp_strlen2274 = strlen(out) + strlen("  FILE* f = fopen(path, \"rb\");\n") + 1;
  char* tmp_str2274 = calloc(tmp_strlen2274, sizeof(char));
  strcpy(tmp_str2274, out);
  strcat(tmp_str2274, "  FILE* f = fopen(path, \"rb\");\n");
  out = tmp_str2274;
  int tmp_strlen2234 = strlen(out) + strlen("  if (f == NULL) {\n") + 1;
  char* tmp_str2234 = calloc(tmp_strlen2234, sizeof(char));
  strcpy(tmp_str2234, out);
  strcat(tmp_str2234, "  if (f == NULL) {\n");
  out = tmp_str2234;
  int tmp_strlen2163 = strlen(out) + strlen("    printf(\"could not open file: %s\\n\", path);\n") + 1;
  char* tmp_str2163 = calloc(tmp_strlen2163, sizeof(char));
  strcpy(tmp_str2163, out);
  strcat(tmp_str2163, "    printf(\"could not open file: %s\\n\", path);\n");
  out = tmp_str2163;
  int tmp_strlen2129 = strlen(out) + strlen("    exit(1);\n") + 1;
  char* tmp_str2129 = calloc(tmp_strlen2129, sizeof(char));
  strcpy(tmp_str2129, out);
  strcat(tmp_str2129, "    exit(1);\n");
  out = tmp_str2129;
  int tmp_strlen2104 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str2104 = calloc(tmp_strlen2104, sizeof(char));
  strcpy(tmp_str2104, out);
  strcat(tmp_str2104, "  }\n");
  out = tmp_str2104;
  int tmp_strlen2058 = strlen(out) + strlen("  fseek(f, 0, SEEK_END);\n") + 1;
  char* tmp_str2058 = calloc(tmp_strlen2058, sizeof(char));
  strcpy(tmp_str2058, out);
  strcat(tmp_str2058, "  fseek(f, 0, SEEK_END);\n");
  out = tmp_str2058;
  int tmp_strlen2012 = strlen(out) + strlen("  int length = ftell(f);\n") + 1;
  char* tmp_str2012 = calloc(tmp_strlen2012, sizeof(char));
  strcpy(tmp_str2012, out);
  strcat(tmp_str2012, "  int length = ftell(f);\n");
  out = tmp_str2012;
  int tmp_strlen1960 = strlen(out) + strlen("  char* text = malloc(length);\n") + 1;
  char* tmp_str1960 = calloc(tmp_strlen1960, sizeof(char));
  strcpy(tmp_str1960, out);
  strcat(tmp_str1960, "  char* text = malloc(length);\n");
  out = tmp_str1960;
  int tmp_strlen1914 = strlen(out) + strlen("  fseek(f, 0, SEEK_SET);\n") + 1;
  char* tmp_str1914 = calloc(tmp_strlen1914, sizeof(char));
  strcpy(tmp_str1914, out);
  strcat(tmp_str1914, "  fseek(f, 0, SEEK_SET);\n");
  out = tmp_str1914;
  int tmp_strlen1864 = strlen(out) + strlen("  fread(text, 1, length, f);\n") + 1;
  char* tmp_str1864 = calloc(tmp_strlen1864, sizeof(char));
  strcpy(tmp_str1864, out);
  strcat(tmp_str1864, "  fread(text, 1, length, f);\n");
  out = tmp_str1864;
  int tmp_strlen1830 = strlen(out) + strlen("  fclose(f);\n") + 1;
  char* tmp_str1830 = calloc(tmp_strlen1830, sizeof(char));
  strcpy(tmp_str1830, out);
  strcat(tmp_str1830, "  fclose(f);\n");
  out = tmp_str1830;
  int tmp_strlen1794 = strlen(out) + strlen("  return text;\n") + 1;
  char* tmp_str1794 = calloc(tmp_strlen1794, sizeof(char));
  strcpy(tmp_str1794, out);
  strcat(tmp_str1794, "  return text;\n");
  out = tmp_str1794;
  int tmp_strlen1771 = strlen(out) + strlen("}\n") + 1;
  char* tmp_str1771 = calloc(tmp_strlen1771, sizeof(char));
  strcpy(tmp_str1771, out);
  strcat(tmp_str1771, "}\n");
  out = tmp_str1771;
  int tmp_strlen1749 = strlen(out) + strlen("\n") + 1;
  char* tmp_str1749 = calloc(tmp_strlen1749, sizeof(char));
  strcpy(tmp_str1749, out);
  strcat(tmp_str1749, "\n");
  out = tmp_str1749;
  int tmp_strlen1679 = strlen(out) + strlen("void write(const char* path, const char* text) {\n") + 1;
  char* tmp_str1679 = calloc(tmp_strlen1679, sizeof(char));
  strcpy(tmp_str1679, out);
  strcat(tmp_str1679, "void write(const char* path, const char* text) {\n");
  out = tmp_str1679;
  int tmp_strlen1626 = strlen(out) + strlen("  FILE *f = fopen(path, \"w\");\n") + 1;
  char* tmp_str1626 = calloc(tmp_strlen1626, sizeof(char));
  strcpy(tmp_str1626, out);
  strcat(tmp_str1626, "  FILE *f = fopen(path, \"w\");\n");
  out = tmp_str1626;
  int tmp_strlen1586 = strlen(out) + strlen("  if (f == NULL) {\n") + 1;
  char* tmp_str1586 = calloc(tmp_strlen1586, sizeof(char));
  strcpy(tmp_str1586, out);
  strcat(tmp_str1586, "  if (f == NULL) {\n");
  out = tmp_str1586;
  int tmp_strlen1515 = strlen(out) + strlen("    printf(\"could not open file: %s\\n\", path);\n") + 1;
  char* tmp_str1515 = calloc(tmp_strlen1515, sizeof(char));
  strcpy(tmp_str1515, out);
  strcat(tmp_str1515, "    printf(\"could not open file: %s\\n\", path);\n");
  out = tmp_str1515;
  int tmp_strlen1481 = strlen(out) + strlen("    exit(1);\n") + 1;
  char* tmp_str1481 = calloc(tmp_strlen1481, sizeof(char));
  strcpy(tmp_str1481, out);
  strcat(tmp_str1481, "    exit(1);\n");
  out = tmp_str1481;
  int tmp_strlen1456 = strlen(out) + strlen("  }\n") + 1;
  char* tmp_str1456 = calloc(tmp_strlen1456, sizeof(char));
  strcpy(tmp_str1456, out);
  strcat(tmp_str1456, "  }\n");
  out = tmp_str1456;
  int tmp_strlen1407 = strlen(out) + strlen("  fprintf(f, \"%s\", text);\n") + 1;
  char* tmp_str1407 = calloc(tmp_strlen1407, sizeof(char));
  strcpy(tmp_str1407, out);
  strcat(tmp_str1407, "  fprintf(f, \"%s\", text);\n");
  out = tmp_str1407;
  int tmp_strlen1373 = strlen(out) + strlen("  fclose(f);\n") + 1;
  char* tmp_str1373 = calloc(tmp_strlen1373, sizeof(char));
  strcpy(tmp_str1373, out);
  strcat(tmp_str1373, "  fclose(f);\n");
  out = tmp_str1373;
  int tmp_strlen1348 = strlen(out) + strlen("}\n\n") + 1;
  char* tmp_str1348 = calloc(tmp_strlen1348, sizeof(char));
  strcpy(tmp_str1348, out);
  strcat(tmp_str1348, "}\n\n");
  out = tmp_str1348;
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results1218 = Peek(src);
  tok = tmp_results1218.result1;
  tok_str = tmp_results1218.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results1124 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results1124.result1;
      tok_str = tmp_results1124.result2;
      Peek_results tmp_results1066 = Peek(src);
      tok = tmp_results1066.result1;
      tok_str = tmp_results1066.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results938 = TranslateConstDecl(src, "");
        src = tmp_results938.result1;
        const_decl = tmp_results938.result2;
        int tmp_strlen845 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str845 = calloc(tmp_strlen845, sizeof(char));
        strcpy(tmp_str845, constants);
        strcat(tmp_str845, const_decl);
        constants = tmp_str845;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          TranslateFunc_results tmp_results735 = TranslateFunc(src);
          src = tmp_results735.result1;
          fn_decl = tmp_results735.result2;
          fn_def = tmp_results735.result3;
          int tmp_strlen657 = strlen(decls) + strlen(fn_decl) + 1;
          char* tmp_str657 = calloc(tmp_strlen657, sizeof(char));
          strcpy(tmp_str657, decls);
          strcat(tmp_str657, fn_decl);
          decls = tmp_str657;
          int tmp_strlen623 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str623 = calloc(tmp_strlen623, sizeof(char));
          strcpy(tmp_str623, defs);
          strcat(tmp_str623, fn_def);
          defs = tmp_str623;
        } else {
          int tmp_strlen544 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str544 = calloc(tmp_strlen544, sizeof(char));
          strcpy(tmp_str544, "unexpected decl token, got: ");
          strcat(tmp_str544, itoa(tok));
          int tmp_strlen535 = strlen(tmp_str544) + strlen(" \"") + 1;
          char* tmp_str535 = calloc(tmp_strlen535, sizeof(char));
          strcpy(tmp_str535, tmp_str544);
          strcat(tmp_str535, " \"");
          int tmp_strlen524 = strlen(tmp_str535) + strlen(tok_str) + 1;
          char* tmp_str524 = calloc(tmp_strlen524, sizeof(char));
          strcpy(tmp_str524, tmp_str535);
          strcat(tmp_str524, tok_str);
          int tmp_strlen516 = strlen(tmp_str524) + strlen("\"") + 1;
          char* tmp_str516 = calloc(tmp_strlen516, sizeof(char));
          strcpy(tmp_str516, tmp_str524);
          strcat(tmp_str516, "\"");
          printf("%s", tmp_str516);
          exit(1);
        }
      }
    }
    Peek_results tmp_results476 = Peek(src);
    tok = tmp_results476.result1;
    tok_str = tmp_results476.result2;
  }
  ConsumeToken_results tmp_results441 = ConsumeToken(src, TOK_EOF);
  src = tmp_results441.result1;
  tok_str = tmp_results441.result2;
  if ((strcmp(constants, "") != 0)) {
    int tmp_strlen343 = strlen(out) + strlen(constants) + 1;
    char* tmp_str343 = calloc(tmp_strlen343, sizeof(char));
    strcpy(tmp_str343, out);
    strcat(tmp_str343, constants);
    int tmp_strlen335 = strlen(tmp_str343) + strlen("\n") + 1;
    char* tmp_str335 = calloc(tmp_strlen335, sizeof(char));
    strcpy(tmp_str335, tmp_str343);
    strcat(tmp_str335, "\n");
    out = tmp_str335;
  }
  if ((strcmp(decls, "") != 0)) {
    int tmp_strlen280 = strlen(out) + strlen(decls) + 1;
    char* tmp_str280 = calloc(tmp_strlen280, sizeof(char));
    strcpy(tmp_str280, out);
    strcat(tmp_str280, decls);
    int tmp_strlen272 = strlen(tmp_str280) + strlen("\n") + 1;
    char* tmp_str272 = calloc(tmp_strlen272, sizeof(char));
    strcpy(tmp_str272, tmp_str280);
    strcat(tmp_str272, "\n");
    out = tmp_str272;
  }
  if ((strcmp(defs, "") != 0)) {
    int tmp_strlen219 = strlen(out) + strlen(defs) + 1;
    char* tmp_str219 = calloc(tmp_strlen219, sizeof(char));
    strcpy(tmp_str219, out);
    strcat(tmp_str219, defs);
    int tmp_strlen211 = strlen(tmp_str219) + strlen("\n") + 1;
    char* tmp_str211 = calloc(tmp_strlen211, sizeof(char));
    strcpy(tmp_str211, tmp_str219);
    strcat(tmp_str211, "\n");
    out = tmp_str211;
  }
  return out;
}

int main() {
  char* src_file = "sokka.sk";
  char* src = read(src_file);
  char* out = TranslateProgram(src);
  int tmp_strlen39 = ((strlen(src_file)) - (3)) - (0) + 1;
  char* tmp_str39 = calloc(tmp_strlen39, sizeof(char));
  strncpy(tmp_str39, src_file + 0, tmp_strlen39 - 1);
  tmp_str39[tmp_strlen39 - 1] = 0;
  int tmp_strlen9 = strlen(tmp_str39) + strlen(".B.c") + 1;
  char* tmp_str9 = calloc(tmp_strlen9, sizeof(char));
  strcpy(tmp_str9, tmp_str39);
  strcat(tmp_str9, ".B.c");
  write(tmp_str9, out);
}


