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
                  int tmp_strlen28108 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str28108 = calloc(tmp_strlen28108, sizeof(char));
                  strcpy(tmp_str28108, "token has no defined precedence: ");
                  strcat(tmp_str28108, itoa(tok));
                  printf("%s", tmp_str28108);
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
      int tmp_strlen27793 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str27793 = calloc(tmp_strlen27793, sizeof(char));
      strncpy(tmp_str27793, haystack + i, tmp_strlen27793 - 1);
      tmp_str27793[tmp_strlen27793 - 1] = 0;
      if ((strcmp(tmp_str27793, needle) != 0)) {
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
      int tmp_strlen27458 = (strlen(prefix)) - (0) + 1;
      char* tmp_str27458 = calloc(tmp_strlen27458, sizeof(char));
      strncpy(tmp_str27458, text + 0, tmp_strlen27458 - 1);
      tmp_str27458[tmp_strlen27458 - 1] = 0;
      return (strcmp(tmp_str27458, prefix) == 0);
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
    int tmp_strlen27064 = (strlen(text)) - (1) + 1;
    char* tmp_str27064 = calloc(tmp_strlen27064, sizeof(char));
    strncpy(tmp_str27064, text + 1, tmp_strlen27064 - 1);
    tmp_str27064[tmp_strlen27064 - 1] = 0;
    text = tmp_str27064;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen26841 = (strlen(src)) - (2) + 1;
      char* tmp_str26841 = calloc(tmp_strlen26841, sizeof(char));
      strncpy(tmp_str26841, src + 2, tmp_strlen26841 - 1);
      tmp_str26841[tmp_strlen26841 - 1] = 0;
      return (Next_results){tmp_str26841, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen26762 = (strlen(src)) - (2) + 1;
        char* tmp_str26762 = calloc(tmp_strlen26762, sizeof(char));
        strncpy(tmp_str26762, src + 2, tmp_strlen26762 - 1);
        tmp_str26762[tmp_strlen26762 - 1] = 0;
        return (Next_results){tmp_str26762, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen26686 = (strlen(src)) - (2) + 1;
          char* tmp_str26686 = calloc(tmp_strlen26686, sizeof(char));
          strncpy(tmp_str26686, src + 2, tmp_strlen26686 - 1);
          tmp_str26686[tmp_strlen26686 - 1] = 0;
          return (Next_results){tmp_str26686, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen26609 = (strlen(src)) - (2) + 1;
            char* tmp_str26609 = calloc(tmp_strlen26609, sizeof(char));
            strncpy(tmp_str26609, src + 2, tmp_strlen26609 - 1);
            tmp_str26609[tmp_strlen26609 - 1] = 0;
            return (Next_results){tmp_str26609, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen26534 = (strlen(src)) - (2) + 1;
              char* tmp_str26534 = calloc(tmp_strlen26534, sizeof(char));
              strncpy(tmp_str26534, src + 2, tmp_strlen26534 - 1);
              tmp_str26534[tmp_strlen26534 - 1] = 0;
              return (Next_results){tmp_str26534, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen26458 = (strlen(src)) - (2) + 1;
                char* tmp_str26458 = calloc(tmp_strlen26458, sizeof(char));
                strncpy(tmp_str26458, src + 2, tmp_strlen26458 - 1);
                tmp_str26458[tmp_strlen26458 - 1] = 0;
                return (Next_results){tmp_str26458, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen26382 = (strlen(src)) - (2) + 1;
                  char* tmp_str26382 = calloc(tmp_strlen26382, sizeof(char));
                  strncpy(tmp_str26382, src + 2, tmp_strlen26382 - 1);
                  tmp_str26382[tmp_strlen26382 - 1] = 0;
                  return (Next_results){tmp_str26382, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen26306 = (strlen(src)) - (2) + 1;
                    char* tmp_str26306 = calloc(tmp_strlen26306, sizeof(char));
                    strncpy(tmp_str26306, src + 2, tmp_strlen26306 - 1);
                    tmp_str26306[tmp_strlen26306 - 1] = 0;
                    return (Next_results){tmp_str26306, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen26227 = (strlen(src)) - (2) + 1;
                      char* tmp_str26227 = calloc(tmp_strlen26227, sizeof(char));
                      strncpy(tmp_str26227, src + 2, tmp_strlen26227 - 1);
                      tmp_str26227[tmp_strlen26227 - 1] = 0;
                      return (Next_results){tmp_str26227, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen26148 = (strlen(src)) - (3) + 1;
                        char* tmp_str26148 = calloc(tmp_strlen26148, sizeof(char));
                        strncpy(tmp_str26148, src + 3, tmp_strlen26148 - 1);
                        tmp_str26148[tmp_strlen26148 - 1] = 0;
                        return (Next_results){tmp_str26148, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen26068 = (strlen(src)) - (1) + 1;
                          char* tmp_str26068 = calloc(tmp_strlen26068, sizeof(char));
                          strncpy(tmp_str26068, src + 1, tmp_strlen26068 - 1);
                          tmp_str26068[tmp_strlen26068 - 1] = 0;
                          return (Next_results){tmp_str26068, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen25989 = (strlen(src)) - (1) + 1;
                            char* tmp_str25989 = calloc(tmp_strlen25989, sizeof(char));
                            strncpy(tmp_str25989, src + 1, tmp_strlen25989 - 1);
                            tmp_str25989[tmp_strlen25989 - 1] = 0;
                            return (Next_results){tmp_str25989, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen25912 = (strlen(src)) - (1) + 1;
                              char* tmp_str25912 = calloc(tmp_strlen25912, sizeof(char));
                              strncpy(tmp_str25912, src + 1, tmp_strlen25912 - 1);
                              tmp_str25912[tmp_strlen25912 - 1] = 0;
                              return (Next_results){tmp_str25912, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen25835 = (strlen(src)) - (1) + 1;
                                char* tmp_str25835 = calloc(tmp_strlen25835, sizeof(char));
                                strncpy(tmp_str25835, src + 1, tmp_strlen25835 - 1);
                                tmp_str25835[tmp_strlen25835 - 1] = 0;
                                return (Next_results){tmp_str25835, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen25756 = (strlen(src)) - (1) + 1;
                                  char* tmp_str25756 = calloc(tmp_strlen25756, sizeof(char));
                                  strncpy(tmp_str25756, src + 1, tmp_strlen25756 - 1);
                                  tmp_str25756[tmp_strlen25756 - 1] = 0;
                                  return (Next_results){tmp_str25756, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen25677 = (strlen(src)) - (1) + 1;
                                    char* tmp_str25677 = calloc(tmp_strlen25677, sizeof(char));
                                    strncpy(tmp_str25677, src + 1, tmp_strlen25677 - 1);
                                    tmp_str25677[tmp_strlen25677 - 1] = 0;
                                    return (Next_results){tmp_str25677, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen25600 = (strlen(src)) - (1) + 1;
                                      char* tmp_str25600 = calloc(tmp_strlen25600, sizeof(char));
                                      strncpy(tmp_str25600, src + 1, tmp_strlen25600 - 1);
                                      tmp_str25600[tmp_strlen25600 - 1] = 0;
                                      return (Next_results){tmp_str25600, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, ":")) {
                                        int tmp_strlen25523 = (strlen(src)) - (1) + 1;
                                        char* tmp_str25523 = calloc(tmp_strlen25523, sizeof(char));
                                        strncpy(tmp_str25523, src + 1, tmp_strlen25523 - 1);
                                        tmp_str25523[tmp_strlen25523 - 1] = 0;
                                        return (Next_results){tmp_str25523, TOK_COLON, ":"};
                                      } else {
                                        if (StartsWith(src, ",")) {
                                          int tmp_strlen25447 = (strlen(src)) - (1) + 1;
                                          char* tmp_str25447 = calloc(tmp_strlen25447, sizeof(char));
                                          strncpy(tmp_str25447, src + 1, tmp_strlen25447 - 1);
                                          tmp_str25447[tmp_strlen25447 - 1] = 0;
                                          return (Next_results){tmp_str25447, TOK_COMMA, ","};
                                        } else {
                                          if (StartsWith(src, "=")) {
                                            int tmp_strlen25371 = (strlen(src)) - (1) + 1;
                                            char* tmp_str25371 = calloc(tmp_strlen25371, sizeof(char));
                                            strncpy(tmp_str25371, src + 1, tmp_strlen25371 - 1);
                                            tmp_str25371[tmp_strlen25371 - 1] = 0;
                                            return (Next_results){tmp_str25371, TOK_ASSIGN, "="};
                                          } else {
                                            if (StartsWith(src, "!")) {
                                              int tmp_strlen25294 = (strlen(src)) - (1) + 1;
                                              char* tmp_str25294 = calloc(tmp_strlen25294, sizeof(char));
                                              strncpy(tmp_str25294, src + 1, tmp_strlen25294 - 1);
                                              tmp_str25294[tmp_strlen25294 - 1] = 0;
                                              return (Next_results){tmp_str25294, TOK_BNOT, "!"};
                                            } else {
                                              if (StartsWith(src, "+")) {
                                                int tmp_strlen25219 = (strlen(src)) - (1) + 1;
                                                char* tmp_str25219 = calloc(tmp_strlen25219, sizeof(char));
                                                strncpy(tmp_str25219, src + 1, tmp_strlen25219 - 1);
                                                tmp_str25219[tmp_strlen25219 - 1] = 0;
                                                return (Next_results){tmp_str25219, TOK_ADD, "+"};
                                              } else {
                                                if (StartsWith(src, "-")) {
                                                  int tmp_strlen25145 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str25145 = calloc(tmp_strlen25145, sizeof(char));
                                                  strncpy(tmp_str25145, src + 1, tmp_strlen25145 - 1);
                                                  tmp_str25145[tmp_strlen25145 - 1] = 0;
                                                  return (Next_results){tmp_str25145, TOK_SUB, "-"};
                                                } else {
                                                  if (StartsWith(src, "*")) {
                                                    int tmp_strlen25071 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str25071 = calloc(tmp_strlen25071, sizeof(char));
                                                    strncpy(tmp_str25071, src + 1, tmp_strlen25071 - 1);
                                                    tmp_str25071[tmp_strlen25071 - 1] = 0;
                                                    return (Next_results){tmp_str25071, TOK_MUL, "*"};
                                                  } else {
                                                    if (StartsWith(src, "/")) {
                                                      int tmp_strlen24997 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str24997 = calloc(tmp_strlen24997, sizeof(char));
                                                      strncpy(tmp_str24997, src + 1, tmp_strlen24997 - 1);
                                                      tmp_str24997[tmp_strlen24997 - 1] = 0;
                                                      return (Next_results){tmp_str24997, TOK_DIV, "/"};
                                                    } else {
                                                      if (StartsWith(src, "%")) {
                                                        int tmp_strlen24923 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str24923 = calloc(tmp_strlen24923, sizeof(char));
                                                        strncpy(tmp_str24923, src + 1, tmp_strlen24923 - 1);
                                                        tmp_str24923[tmp_strlen24923 - 1] = 0;
                                                        return (Next_results){tmp_str24923, TOK_REM, "%"};
                                                      } else {
                                                        if (StartsWith(src, "~")) {
                                                          int tmp_strlen24849 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str24849 = calloc(tmp_strlen24849, sizeof(char));
                                                          strncpy(tmp_str24849, src + 1, tmp_strlen24849 - 1);
                                                          tmp_str24849[tmp_strlen24849 - 1] = 0;
                                                          return (Next_results){tmp_str24849, TOK_INOT, "~"};
                                                        } else {
                                                          if (StartsWith(src, "|")) {
                                                            int tmp_strlen24774 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str24774 = calloc(tmp_strlen24774, sizeof(char));
                                                            strncpy(tmp_str24774, src + 1, tmp_strlen24774 - 1);
                                                            tmp_str24774[tmp_strlen24774 - 1] = 0;
                                                            return (Next_results){tmp_str24774, TOK_IOR, "|"};
                                                          } else {
                                                            if (StartsWith(src, "&")) {
                                                              int tmp_strlen24700 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str24700 = calloc(tmp_strlen24700, sizeof(char));
                                                              strncpy(tmp_str24700, src + 1, tmp_strlen24700 - 1);
                                                              tmp_str24700[tmp_strlen24700 - 1] = 0;
                                                              return (Next_results){tmp_str24700, TOK_IAND, "&"};
                                                            } else {
                                                              if (StartsWith(src, "^")) {
                                                                int tmp_strlen24625 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str24625 = calloc(tmp_strlen24625, sizeof(char));
                                                                strncpy(tmp_str24625, src + 1, tmp_strlen24625 - 1);
                                                                tmp_str24625[tmp_strlen24625 - 1] = 0;
                                                                return (Next_results){tmp_str24625, TOK_IXOR, "^"};
                                                              } else {
                                                                if (StartsWith(src, "<")) {
                                                                  int tmp_strlen24550 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str24550 = calloc(tmp_strlen24550, sizeof(char));
                                                                  strncpy(tmp_str24550, src + 1, tmp_strlen24550 - 1);
                                                                  tmp_str24550[tmp_strlen24550 - 1] = 0;
                                                                  return (Next_results){tmp_str24550, TOK_LESS, "<"};
                                                                } else {
                                                                  if (StartsWith(src, ">")) {
                                                                    int tmp_strlen24475 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str24475 = calloc(tmp_strlen24475, sizeof(char));
                                                                    strncpy(tmp_str24475, src + 1, tmp_strlen24475 - 1);
                                                                    tmp_str24475[tmp_strlen24475 - 1] = 0;
                                                                    return (Next_results){tmp_str24475, TOK_GREATER, ">"};
                                                                  } else {
                                                                    if (IsAlpha(src[0])) {
                                                                      int i = 1;
                                                                      while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                        i = (i) + (1);
                                                                      }
                                                                      i = (i) - (1);
                                                                      int tmp_strlen24244 = (i) - (0) + 1;
                                                                      char* tmp_str24244 = calloc(tmp_strlen24244, sizeof(char));
                                                                      strncpy(tmp_str24244, src + 0, tmp_strlen24244 - 1);
                                                                      tmp_str24244[tmp_strlen24244 - 1] = 0;
                                                                      char* ts = tmp_str24244;
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
                                                                      int tmp_strlen23452 = (strlen(src)) - (i) + 1;
                                                                      char* tmp_str23452 = calloc(tmp_strlen23452, sizeof(char));
                                                                      strncpy(tmp_str23452, src + i, tmp_strlen23452 - 1);
                                                                      tmp_str23452[tmp_strlen23452 - 1] = 0;
                                                                      return (Next_results){tmp_str23452, tt, ts};
                                                                    } else {
                                                                      if (IsNumeric(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        int tmp_strlen23284 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str23284 = calloc(tmp_strlen23284, sizeof(char));
                                                                        strncpy(tmp_str23284, src + i, tmp_strlen23284 - 1);
                                                                        tmp_str23284[tmp_strlen23284 - 1] = 0;
                                                                        int tmp_strlen23263 = (i) - (0) + 1;
                                                                        char* tmp_str23263 = calloc(tmp_strlen23263, sizeof(char));
                                                                        strncpy(tmp_str23263, src + 0, tmp_strlen23263 - 1);
                                                                        tmp_str23263[tmp_strlen23263 - 1] = 0;
                                                                        return (Next_results){tmp_str23284, TOK_INTLIT, tmp_str23263};
                                                                      } else {
                                                                        if (StartsWith(src, "\"")) {
                                                                          int i = 1;
                                                                          while (true) {
                                                                            int tmp_strlen23182 = ((i) + (1)) - (i) + 1;
                                                                            char* tmp_str23182 = calloc(tmp_strlen23182, sizeof(char));
                                                                            strncpy(tmp_str23182, src + i, tmp_strlen23182 - 1);
                                                                            tmp_str23182[tmp_strlen23182 - 1] = 0;
                                                                            if (!((strcmp(tmp_str23182, "\"") != 0))) break;
                                                                            i = (i) + (1);
                                                                            int tmp_strlen23123 = (i) - ((i) - (1)) + 1;
                                                                            char* tmp_str23123 = calloc(tmp_strlen23123, sizeof(char));
                                                                            strncpy(tmp_str23123, src + (i) - (1), tmp_strlen23123 - 1);
                                                                            tmp_str23123[tmp_strlen23123 - 1] = 0;
                                                                            if ((strcmp(tmp_str23123, "\\") == 0)) {
                                                                              i = (i) + (1);
                                                                            }
                                                                          }
                                                                          i = (i) + (1);
                                                                          int tmp_strlen23019 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str23019 = calloc(tmp_strlen23019, sizeof(char));
                                                                          strncpy(tmp_str23019, src + i, tmp_strlen23019 - 1);
                                                                          tmp_str23019[tmp_strlen23019 - 1] = 0;
                                                                          int tmp_strlen22998 = (i) - (0) + 1;
                                                                          char* tmp_str22998 = calloc(tmp_strlen22998, sizeof(char));
                                                                          strncpy(tmp_str22998, src + 0, tmp_strlen22998 - 1);
                                                                          tmp_str22998[tmp_strlen22998 - 1] = 0;
                                                                          return (Next_results){tmp_str23019, TOK_STRLIT, tmp_str22998};
                                                                        } else {
                                                                          int tmp_strlen22933 = (1) - (0) + 1;
                                                                          char* tmp_str22933 = calloc(tmp_strlen22933, sizeof(char));
                                                                          strncpy(tmp_str22933, src + 0, tmp_strlen22933 - 1);
                                                                          tmp_str22933[tmp_strlen22933 - 1] = 0;
                                                                          int tmp_strlen22929 = strlen("unexpected token start: ") + strlen(tmp_str22933) + 1;
                                                                          char* tmp_str22929 = calloc(tmp_strlen22929, sizeof(char));
                                                                          strcpy(tmp_str22929, "unexpected token start: ");
                                                                          strcat(tmp_str22929, tmp_str22933);
                                                                          printf("%s", tmp_str22929);
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
  Next_results tmp_results22817 = Next(src);
  src = tmp_results22817.result1;
  tok = tmp_results22817.result2;
  tok_str = tmp_results22817.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22631 = Next(src);
  src = tmp_results22631.result1;
  actual_tok = tmp_results22631.result2;
  actual_tok_str = tmp_results22631.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen22497 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str22497 = calloc(tmp_strlen22497, sizeof(char));
    strcpy(tmp_str22497, "expected token: ");
    strcat(tmp_str22497, itoa(expected_tok));
    int tmp_strlen22470 = strlen(tmp_str22497) + strlen(" got: ") + 1;
    char* tmp_str22470 = calloc(tmp_strlen22470, sizeof(char));
    strcpy(tmp_str22470, tmp_str22497);
    strcat(tmp_str22470, " got: ");
    int tmp_strlen22450 = strlen(tmp_str22470) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22450 = calloc(tmp_strlen22450, sizeof(char));
    strcpy(tmp_str22450, tmp_str22470);
    strcat(tmp_str22450, itoa(actual_tok));
    int tmp_strlen22441 = strlen(tmp_str22450) + strlen(" \"") + 1;
    char* tmp_str22441 = calloc(tmp_strlen22441, sizeof(char));
    strcpy(tmp_str22441, tmp_str22450);
    strcat(tmp_str22441, " \"");
    int tmp_strlen22423 = strlen(tmp_str22441) + strlen(actual_tok_str) + 1;
    char* tmp_str22423 = calloc(tmp_strlen22423, sizeof(char));
    strcpy(tmp_str22423, tmp_str22441);
    strcat(tmp_str22423, actual_tok_str);
    int tmp_strlen22415 = strlen(tmp_str22423) + strlen("\"") + 1;
    char* tmp_str22415 = calloc(tmp_strlen22415, sizeof(char));
    strcpy(tmp_str22415, tmp_str22423);
    strcat(tmp_str22415, "\"");
    printf("%s", tmp_str22415);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22247 = Next(src);
  src = tmp_results22247.result1;
  actual_tok = tmp_results22247.result2;
  actual_tok_str = tmp_results22247.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen22113 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22113 = calloc(tmp_strlen22113, sizeof(char));
    strcpy(tmp_str22113, "expected ident, got: ");
    strcat(tmp_str22113, itoa(actual_tok));
    int tmp_strlen22104 = strlen(tmp_str22113) + strlen(" \"") + 1;
    char* tmp_str22104 = calloc(tmp_strlen22104, sizeof(char));
    strcpy(tmp_str22104, tmp_str22113);
    strcat(tmp_str22104, " \"");
    int tmp_strlen22086 = strlen(tmp_str22104) + strlen(actual_tok_str) + 1;
    char* tmp_str22086 = calloc(tmp_strlen22086, sizeof(char));
    strcpy(tmp_str22086, tmp_str22104);
    strcat(tmp_str22086, actual_tok_str);
    int tmp_strlen22078 = strlen(tmp_str22086) + strlen("\"") + 1;
    char* tmp_str22078 = calloc(tmp_strlen22078, sizeof(char));
    strcpy(tmp_str22078, tmp_str22086);
    strcat(tmp_str22078, "\"");
    printf("%s", tmp_str22078);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21918 = Next(src);
  src = tmp_results21918.result1;
  tok = tmp_results21918.result2;
  tok_str = tmp_results21918.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen21621 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str21621 = calloc(tmp_strlen21621, sizeof(char));
        strcpy(tmp_str21621, "expected type, got: ");
        strcat(tmp_str21621, itoa(tok));
        int tmp_strlen21612 = strlen(tmp_str21621) + strlen(" \"") + 1;
        char* tmp_str21612 = calloc(tmp_strlen21612, sizeof(char));
        strcpy(tmp_str21612, tmp_str21621);
        strcat(tmp_str21612, " \"");
        int tmp_strlen21601 = strlen(tmp_str21612) + strlen(tok_str) + 1;
        char* tmp_str21601 = calloc(tmp_strlen21601, sizeof(char));
        strcpy(tmp_str21601, tmp_str21612);
        strcat(tmp_str21601, tok_str);
        int tmp_strlen21593 = strlen(tmp_str21601) + strlen("\"") + 1;
        char* tmp_str21593 = calloc(tmp_strlen21593, sizeof(char));
        strcpy(tmp_str21593, tmp_str21601);
        strcat(tmp_str21593, "\"");
        printf("%s", tmp_str21593);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21462 = Next(src);
  src = tmp_results21462.result1;
  tok = tmp_results21462.result2;
  tok_str = tmp_results21462.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen21288 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str21288 = calloc(tmp_strlen21288, sizeof(char));
    strcpy(tmp_str21288, "expected false or true, got: ");
    strcat(tmp_str21288, itoa(tok));
    int tmp_strlen21279 = strlen(tmp_str21288) + strlen(" \"") + 1;
    char* tmp_str21279 = calloc(tmp_strlen21279, sizeof(char));
    strcpy(tmp_str21279, tmp_str21288);
    strcat(tmp_str21279, " \"");
    int tmp_strlen21268 = strlen(tmp_str21279) + strlen(tok_str) + 1;
    char* tmp_str21268 = calloc(tmp_strlen21268, sizeof(char));
    strcpy(tmp_str21268, tmp_str21279);
    strcat(tmp_str21268, tok_str);
    int tmp_strlen21260 = strlen(tmp_str21268) + strlen("\"") + 1;
    char* tmp_str21260 = calloc(tmp_strlen21260, sizeof(char));
    strcpy(tmp_str21260, tmp_str21268);
    strcat(tmp_str21260, "\"");
    printf("%s", tmp_str21260);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results21151 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results21151.result1;
  lit = tmp_results21151.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results21002 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results21002.result1;
  lit = tmp_results21002.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results20801 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results20801.result1;
  tok_str = tmp_results20801.result2;
  Peek_results tmp_results20752 = Peek(src);
  tok = tmp_results20752.result1;
  tok_str = tmp_results20752.result2;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results20600 = TranslateExprs(src, indent);
    src = tmp_results20600.result1;
    expr_count = tmp_results20600.result2;
    args_setup = tmp_results20600.result3;
    arg_values = tmp_results20600.result4;
  }
  ConsumeToken_results tmp_results20520 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results20520.result1;
  tok_str = tmp_results20520.result2;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen20383 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str20383 = calloc(tmp_strlen20383, sizeof(char));
    strcpy(tmp_str20383, "printf(\"%s\", ");
    strcat(tmp_str20383, arg_values);
    int tmp_strlen20376 = strlen(tmp_str20383) + strlen(")") + 1;
    char* tmp_str20376 = calloc(tmp_strlen20376, sizeof(char));
    strcpy(tmp_str20376, tmp_str20383);
    strcat(tmp_str20376, ")");
    val = tmp_str20376;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen20306 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str20306 = calloc(tmp_strlen20306, sizeof(char));
      strcpy(tmp_str20306, "strlen(");
      strcat(tmp_str20306, arg_values);
      int tmp_strlen20299 = strlen(tmp_str20306) + strlen(")") + 1;
      char* tmp_str20299 = calloc(tmp_strlen20299, sizeof(char));
      strcpy(tmp_str20299, tmp_str20306);
      strcat(tmp_str20299, ")");
      val = tmp_str20299;
    } else {
      int tmp_strlen20258 = strlen(callee) + strlen("(") + 1;
      char* tmp_str20258 = calloc(tmp_strlen20258, sizeof(char));
      strcpy(tmp_str20258, callee);
      strcat(tmp_str20258, "(");
      int tmp_strlen20244 = strlen(tmp_str20258) + strlen(arg_values) + 1;
      char* tmp_str20244 = calloc(tmp_strlen20244, sizeof(char));
      strcpy(tmp_str20244, tmp_str20258);
      strcat(tmp_str20244, arg_values);
      int tmp_strlen20237 = strlen(tmp_str20244) + strlen(")") + 1;
      char* tmp_str20237 = calloc(tmp_strlen20237, sizeof(char));
      strcpy(tmp_str20237, tmp_str20244);
      strcat(tmp_str20237, ")");
      val = tmp_str20237;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  char* tok_str;
  int p = strlen(src);
  ConsumeToken_results tmp_results20026 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results20026.result1;
  tok_str = tmp_results20026.result2;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen19838 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str19838 = calloc(tmp_strlen19838, sizeof(char));
  strcpy(tmp_str19838, "strlen(");
  strcat(tmp_str19838, strvar);
  int tmp_strlen19831 = strlen(tmp_str19838) + strlen(")") + 1;
  char* tmp_str19831 = calloc(tmp_strlen19831, sizeof(char));
  strcpy(tmp_str19831, tmp_str19838);
  strcat(tmp_str19831, ")");
  char* high_expr = tmp_str19831;
  Peek_results tmp_results19826 = Peek(src);
  tok = tmp_results19826.result1;
  tok_str = tmp_results19826.result2;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results19767 = ConsumeToken(src, TOK_COLON);
    src = tmp_results19767.result1;
    tok_str = tmp_results19767.result2;
    TranslateExpr_results tmp_results19715 = TranslateExpr(src, indent);
    src = tmp_results19715.result1;
    high_setup = tmp_results19715.result2;
    high_expr = tmp_results19715.result3;
    ConsumeToken_results tmp_results19651 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results19651.result1;
    tok_str = tmp_results19651.result2;
  } else {
    TranslateExpr_results tmp_results19583 = TranslateExpr(src, indent);
    src = tmp_results19583.result1;
    low_setup = tmp_results19583.result2;
    low_expr = tmp_results19583.result3;
    Peek_results tmp_results19521 = Peek(src);
    tok = tmp_results19521.result1;
    tok_str = tmp_results19521.result2;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results19451 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results19451.result1;
      tok_str = tmp_results19451.result2;
      int tmp_strlen19356 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str19356 = calloc(tmp_strlen19356, sizeof(char));
      strcpy(tmp_str19356, strvar);
      strcat(tmp_str19356, "[");
      int tmp_strlen19344 = strlen(tmp_str19356) + strlen(low_expr) + 1;
      char* tmp_str19344 = calloc(tmp_strlen19344, sizeof(char));
      strcpy(tmp_str19344, tmp_str19356);
      strcat(tmp_str19344, low_expr);
      int tmp_strlen19337 = strlen(tmp_str19344) + strlen("]") + 1;
      char* tmp_str19337 = calloc(tmp_strlen19337, sizeof(char));
      strcpy(tmp_str19337, tmp_str19344);
      strcat(tmp_str19337, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str19337};
    }
    ConsumeToken_results tmp_results19318 = ConsumeToken(src, TOK_COLON);
    src = tmp_results19318.result1;
    tok_str = tmp_results19318.result2;
    Peek_results tmp_results19266 = Peek(src);
    tok = tmp_results19266.result1;
    tok_str = tmp_results19266.result2;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results19196 = TranslateExpr(src, indent);
      src = tmp_results19196.result1;
      high_setup = tmp_results19196.result2;
      high_expr = tmp_results19196.result3;
    }
    ConsumeToken_results tmp_results19122 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results19122.result1;
    tok_str = tmp_results19122.result2;
  }
  int tmp_strlen19023 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str19023 = calloc(tmp_strlen19023, sizeof(char));
  strcpy(tmp_str19023, "tmp_str");
  strcat(tmp_str19023, itoa(p));
  char* tmp_str = tmp_str19023;
  int tmp_strlen18970 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str18970 = calloc(tmp_strlen18970, sizeof(char));
  strcpy(tmp_str18970, "tmp_strlen");
  strcat(tmp_str18970, itoa(p));
  char* tmp_strlen = tmp_str18970;
  int tmp_strlen18922 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str18922 = calloc(tmp_strlen18922, sizeof(char));
  strcpy(tmp_str18922, low_setup);
  strcat(tmp_str18922, high_setup);
  char* setup = tmp_str18922;
  int tmp_strlen18894 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18894 = calloc(tmp_strlen18894, sizeof(char));
  strcpy(tmp_str18894, setup);
  strcat(tmp_str18894, indent);
  int tmp_strlen18884 = strlen(tmp_str18894) + strlen("int ") + 1;
  char* tmp_str18884 = calloc(tmp_strlen18884, sizeof(char));
  strcpy(tmp_str18884, tmp_str18894);
  strcat(tmp_str18884, "int ");
  int tmp_strlen18870 = strlen(tmp_str18884) + strlen(tmp_strlen) + 1;
  char* tmp_str18870 = calloc(tmp_strlen18870, sizeof(char));
  strcpy(tmp_str18870, tmp_str18884);
  strcat(tmp_str18870, tmp_strlen);
  int tmp_strlen18860 = strlen(tmp_str18870) + strlen(" = (") + 1;
  char* tmp_str18860 = calloc(tmp_strlen18860, sizeof(char));
  strcpy(tmp_str18860, tmp_str18870);
  strcat(tmp_str18860, " = (");
  int tmp_strlen18847 = strlen(tmp_str18860) + strlen(high_expr) + 1;
  char* tmp_str18847 = calloc(tmp_strlen18847, sizeof(char));
  strcpy(tmp_str18847, tmp_str18860);
  strcat(tmp_str18847, high_expr);
  int tmp_strlen18836 = strlen(tmp_str18847) + strlen(") - (") + 1;
  char* tmp_str18836 = calloc(tmp_strlen18836, sizeof(char));
  strcpy(tmp_str18836, tmp_str18847);
  strcat(tmp_str18836, ") - (");
  int tmp_strlen18824 = strlen(tmp_str18836) + strlen(low_expr) + 1;
  char* tmp_str18824 = calloc(tmp_strlen18824, sizeof(char));
  strcpy(tmp_str18824, tmp_str18836);
  strcat(tmp_str18824, low_expr);
  int tmp_strlen18810 = strlen(tmp_str18824) + strlen(") + 1;\n") + 1;
  char* tmp_str18810 = calloc(tmp_strlen18810, sizeof(char));
  strcpy(tmp_str18810, tmp_str18824);
  strcat(tmp_str18810, ") + 1;\n");
  setup = tmp_str18810;
  int tmp_strlen18782 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18782 = calloc(tmp_strlen18782, sizeof(char));
  strcpy(tmp_str18782, setup);
  strcat(tmp_str18782, indent);
  int tmp_strlen18770 = strlen(tmp_str18782) + strlen("char* ") + 1;
  char* tmp_str18770 = calloc(tmp_strlen18770, sizeof(char));
  strcpy(tmp_str18770, tmp_str18782);
  strcat(tmp_str18770, "char* ");
  int tmp_strlen18759 = strlen(tmp_str18770) + strlen(tmp_str) + 1;
  char* tmp_str18759 = calloc(tmp_strlen18759, sizeof(char));
  strcpy(tmp_str18759, tmp_str18770);
  strcat(tmp_str18759, tmp_str);
  int tmp_strlen18743 = strlen(tmp_str18759) + strlen(" = calloc(") + 1;
  char* tmp_str18743 = calloc(tmp_strlen18743, sizeof(char));
  strcpy(tmp_str18743, tmp_str18759);
  strcat(tmp_str18743, " = calloc(");
  int tmp_strlen18729 = strlen(tmp_str18743) + strlen(tmp_strlen) + 1;
  char* tmp_str18729 = calloc(tmp_strlen18729, sizeof(char));
  strcpy(tmp_str18729, tmp_str18743);
  strcat(tmp_str18729, tmp_strlen);
  int tmp_strlen18705 = strlen(tmp_str18729) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str18705 = calloc(tmp_strlen18705, sizeof(char));
  strcpy(tmp_str18705, tmp_str18729);
  strcat(tmp_str18705, ", sizeof(char));\n");
  setup = tmp_str18705;
  int tmp_strlen18677 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18677 = calloc(tmp_strlen18677, sizeof(char));
  strcpy(tmp_str18677, setup);
  strcat(tmp_str18677, indent);
  int tmp_strlen18663 = strlen(tmp_str18677) + strlen("strncpy(") + 1;
  char* tmp_str18663 = calloc(tmp_strlen18663, sizeof(char));
  strcpy(tmp_str18663, tmp_str18677);
  strcat(tmp_str18663, "strncpy(");
  int tmp_strlen18652 = strlen(tmp_str18663) + strlen(tmp_str) + 1;
  char* tmp_str18652 = calloc(tmp_strlen18652, sizeof(char));
  strcpy(tmp_str18652, tmp_str18663);
  strcat(tmp_str18652, tmp_str);
  int tmp_strlen18644 = strlen(tmp_str18652) + strlen(", ") + 1;
  char* tmp_str18644 = calloc(tmp_strlen18644, sizeof(char));
  strcpy(tmp_str18644, tmp_str18652);
  strcat(tmp_str18644, ", ");
  int tmp_strlen18634 = strlen(tmp_str18644) + strlen(strvar) + 1;
  char* tmp_str18634 = calloc(tmp_strlen18634, sizeof(char));
  strcpy(tmp_str18634, tmp_str18644);
  strcat(tmp_str18634, strvar);
  int tmp_strlen18625 = strlen(tmp_str18634) + strlen(" + ") + 1;
  char* tmp_str18625 = calloc(tmp_strlen18625, sizeof(char));
  strcpy(tmp_str18625, tmp_str18634);
  strcat(tmp_str18625, " + ");
  int tmp_strlen18613 = strlen(tmp_str18625) + strlen(low_expr) + 1;
  char* tmp_str18613 = calloc(tmp_strlen18613, sizeof(char));
  strcpy(tmp_str18613, tmp_str18625);
  strcat(tmp_str18613, low_expr);
  int tmp_strlen18605 = strlen(tmp_str18613) + strlen(", ") + 1;
  char* tmp_str18605 = calloc(tmp_strlen18605, sizeof(char));
  strcpy(tmp_str18605, tmp_str18613);
  strcat(tmp_str18605, ", ");
  int tmp_strlen18591 = strlen(tmp_str18605) + strlen(tmp_strlen) + 1;
  char* tmp_str18591 = calloc(tmp_strlen18591, sizeof(char));
  strcpy(tmp_str18591, tmp_str18605);
  strcat(tmp_str18591, tmp_strlen);
  int tmp_strlen18577 = strlen(tmp_str18591) + strlen(" - 1);\n") + 1;
  char* tmp_str18577 = calloc(tmp_strlen18577, sizeof(char));
  strcpy(tmp_str18577, tmp_str18591);
  strcat(tmp_str18577, " - 1);\n");
  setup = tmp_str18577;
  int tmp_strlen18549 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18549 = calloc(tmp_strlen18549, sizeof(char));
  strcpy(tmp_str18549, setup);
  strcat(tmp_str18549, indent);
  int tmp_strlen18538 = strlen(tmp_str18549) + strlen(tmp_str) + 1;
  char* tmp_str18538 = calloc(tmp_strlen18538, sizeof(char));
  strcpy(tmp_str18538, tmp_str18549);
  strcat(tmp_str18538, tmp_str);
  int tmp_strlen18531 = strlen(tmp_str18538) + strlen("[") + 1;
  char* tmp_str18531 = calloc(tmp_strlen18531, sizeof(char));
  strcpy(tmp_str18531, tmp_str18538);
  strcat(tmp_str18531, "[");
  int tmp_strlen18517 = strlen(tmp_str18531) + strlen(tmp_strlen) + 1;
  char* tmp_str18517 = calloc(tmp_strlen18517, sizeof(char));
  strcpy(tmp_str18517, tmp_str18531);
  strcat(tmp_str18517, tmp_strlen);
  int tmp_strlen18499 = strlen(tmp_str18517) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str18499 = calloc(tmp_strlen18499, sizeof(char));
  strcpy(tmp_str18499, tmp_str18517);
  strcat(tmp_str18499, " - 1] = 0;\n");
  setup = tmp_str18499;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results18340 = Peek(src);
  tok = tmp_results18340.result1;
  tok_str = tmp_results18340.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results18230 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results18230.result1;
    tok_str = tmp_results18230.result2;
    TranslateExpr_results tmp_results18177 = TranslateExpr(src, indent);
    src = tmp_results18177.result1;
    setup = tmp_results18177.result2;
    val = tmp_results18177.result3;
    ConsumeToken_results tmp_results18124 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results18124.result1;
    tok_str = tmp_results18124.result2;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results17964 = TranslateBoolLiteral(src);
      src = tmp_results17964.result1;
      lit = tmp_results17964.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results17833 = TranslateIntLiteral(src);
        src = tmp_results17833.result1;
        lit = tmp_results17833.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results17703 = TranslateStringLiteral(src);
          src = tmp_results17703.result1;
          lit = tmp_results17703.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results17569 = ConsumeIdent(src);
            src = tmp_results17569.result1;
            ident = tmp_results17569.result2;
            Peek_results tmp_results17530 = Peek(src);
            tok = tmp_results17530.result1;
            tok_str = tmp_results17530.result2;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results17403 = TranslateCall(src, indent, ident);
              src = tmp_results17403.result1;
              setup = tmp_results17403.result2;
              expr = tmp_results17403.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results17203 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results17203.result1;
                setup = tmp_results17203.result2;
                expr = tmp_results17203.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen16983 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str16983 = calloc(tmp_strlen16983, sizeof(char));
            strcpy(tmp_str16983, "unexpected expr, got: ");
            strcat(tmp_str16983, itoa(tok));
            int tmp_strlen16974 = strlen(tmp_str16983) + strlen(" \"") + 1;
            char* tmp_str16974 = calloc(tmp_strlen16974, sizeof(char));
            strcpy(tmp_str16974, tmp_str16983);
            strcat(tmp_str16974, " \"");
            int tmp_strlen16963 = strlen(tmp_str16974) + strlen(tok_str) + 1;
            char* tmp_str16963 = calloc(tmp_strlen16963, sizeof(char));
            strcpy(tmp_str16963, tmp_str16974);
            strcat(tmp_str16963, tok_str);
            int tmp_strlen16955 = strlen(tmp_str16963) + strlen("\"") + 1;
            char* tmp_str16955 = calloc(tmp_strlen16955, sizeof(char));
            strcpy(tmp_str16955, tmp_str16963);
            strcat(tmp_str16955, "\"");
            printf("%s", tmp_str16955);
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
  Peek_results tmp_results16802 = Peek(src);
  tok = tmp_results16802.result1;
  tok_str = tmp_results16802.result2;
  if (IsUnaryOp(tok)) {
    ConsumeToken_results tmp_results16745 = ConsumeToken(src, tok);
    src = tmp_results16745.result1;
    tok_str = tmp_results16745.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results16649 = TranslateExpr(src, indent);
    src = tmp_results16649.result1;
    setup = tmp_results16649.result2;
    val = tmp_results16649.result3;
    int tmp_strlen16576 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str16576 = calloc(tmp_strlen16576, sizeof(char));
    strcpy(tmp_str16576, tok_str);
    strcat(tmp_str16576, "(");
    int tmp_strlen16569 = strlen(tmp_str16576) + strlen(val) + 1;
    char* tmp_str16569 = calloc(tmp_strlen16569, sizeof(char));
    strcpy(tmp_str16569, tmp_str16576);
    strcat(tmp_str16569, val);
    int tmp_strlen16562 = strlen(tmp_str16569) + strlen(")") + 1;
    char* tmp_str16562 = calloc(tmp_strlen16562, sizeof(char));
    strcpy(tmp_str16562, tmp_str16569);
    strcat(tmp_str16562, ")");
    val = tmp_str16562;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results16458 = TranslateOperand(src, indent);
    src = tmp_results16458.result1;
    setup = tmp_results16458.result2;
    expr = tmp_results16458.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results16215 = TranslateUnaryExpr(src, indent);
  src = tmp_results16215.result1;
  setup = tmp_results16215.result2;
  val = tmp_results16215.result3;
  int op;
  char* op_str;
  Peek_results tmp_results16122 = Peek(src);
  op = tmp_results16122.result1;
  op_str = tmp_results16122.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results16035 = ConsumeToken(src, op);
    src = tmp_results16035.result1;
    op_str = tmp_results16035.result2;
    int tok;
    char* tok_str;
    Peek_results tmp_results15942 = Peek(src);
    tok = tmp_results15942.result1;
    tok_str = tmp_results15942.result2;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results15872 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results15872.result1;
      tok_str = tmp_results15872.result2;
      Peek_results tmp_results15814 = Peek(src);
      tok = tmp_results15814.result1;
      tok_str = tmp_results15814.result2;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results15717 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results15717.result1;
    setup_b = tmp_results15717.result2;
    val_b = tmp_results15717.result3;
    int tmp_strlen15606 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str15606 = calloc(tmp_strlen15606, sizeof(char));
    strcpy(tmp_str15606, setup);
    strcat(tmp_str15606, setup_b);
    setup = tmp_str15606;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen15514 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15514 = calloc(tmp_strlen15514, sizeof(char));
      strcpy(tmp_str15514, "tmp_str");
      strcat(tmp_str15514, itoa(strlen(src)));
      char* tmp_str = tmp_str15514;
      int tmp_strlen15446 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15446 = calloc(tmp_strlen15446, sizeof(char));
      strcpy(tmp_str15446, "tmp_strlen");
      strcat(tmp_str15446, itoa(strlen(src)));
      char* tmp_strlen = tmp_str15446;
      int tmp_strlen15410 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15410 = calloc(tmp_strlen15410, sizeof(char));
      strcpy(tmp_str15410, setup);
      strcat(tmp_str15410, indent);
      int tmp_strlen15400 = strlen(tmp_str15410) + strlen("int ") + 1;
      char* tmp_str15400 = calloc(tmp_strlen15400, sizeof(char));
      strcpy(tmp_str15400, tmp_str15410);
      strcat(tmp_str15400, "int ");
      int tmp_strlen15386 = strlen(tmp_str15400) + strlen(tmp_strlen) + 1;
      char* tmp_str15386 = calloc(tmp_strlen15386, sizeof(char));
      strcpy(tmp_str15386, tmp_str15400);
      strcat(tmp_str15386, tmp_strlen);
      int tmp_strlen15370 = strlen(tmp_str15386) + strlen(" = strlen(") + 1;
      char* tmp_str15370 = calloc(tmp_strlen15370, sizeof(char));
      strcpy(tmp_str15370, tmp_str15386);
      strcat(tmp_str15370, " = strlen(");
      int tmp_strlen15363 = strlen(tmp_str15370) + strlen(val) + 1;
      char* tmp_str15363 = calloc(tmp_strlen15363, sizeof(char));
      strcpy(tmp_str15363, tmp_str15370);
      strcat(tmp_str15363, val);
      int tmp_strlen15346 = strlen(tmp_str15363) + strlen(") + strlen(") + 1;
      char* tmp_str15346 = calloc(tmp_strlen15346, sizeof(char));
      strcpy(tmp_str15346, tmp_str15363);
      strcat(tmp_str15346, ") + strlen(");
      int tmp_strlen15337 = strlen(tmp_str15346) + strlen(val_b) + 1;
      char* tmp_str15337 = calloc(tmp_strlen15337, sizeof(char));
      strcpy(tmp_str15337, tmp_str15346);
      strcat(tmp_str15337, val_b);
      int tmp_strlen15323 = strlen(tmp_str15337) + strlen(") + 1;\n") + 1;
      char* tmp_str15323 = calloc(tmp_strlen15323, sizeof(char));
      strcpy(tmp_str15323, tmp_str15337);
      strcat(tmp_str15323, ") + 1;\n");
      setup = tmp_str15323;
      int tmp_strlen15287 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15287 = calloc(tmp_strlen15287, sizeof(char));
      strcpy(tmp_str15287, setup);
      strcat(tmp_str15287, indent);
      int tmp_strlen15275 = strlen(tmp_str15287) + strlen("char* ") + 1;
      char* tmp_str15275 = calloc(tmp_strlen15275, sizeof(char));
      strcpy(tmp_str15275, tmp_str15287);
      strcat(tmp_str15275, "char* ");
      int tmp_strlen15264 = strlen(tmp_str15275) + strlen(tmp_str) + 1;
      char* tmp_str15264 = calloc(tmp_strlen15264, sizeof(char));
      strcpy(tmp_str15264, tmp_str15275);
      strcat(tmp_str15264, tmp_str);
      int tmp_strlen15248 = strlen(tmp_str15264) + strlen(" = calloc(") + 1;
      char* tmp_str15248 = calloc(tmp_strlen15248, sizeof(char));
      strcpy(tmp_str15248, tmp_str15264);
      strcat(tmp_str15248, " = calloc(");
      int tmp_strlen15234 = strlen(tmp_str15248) + strlen(tmp_strlen) + 1;
      char* tmp_str15234 = calloc(tmp_strlen15234, sizeof(char));
      strcpy(tmp_str15234, tmp_str15248);
      strcat(tmp_str15234, tmp_strlen);
      int tmp_strlen15210 = strlen(tmp_str15234) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str15210 = calloc(tmp_strlen15210, sizeof(char));
      strcpy(tmp_str15210, tmp_str15234);
      strcat(tmp_str15210, ", sizeof(char));\n");
      setup = tmp_str15210;
      int tmp_strlen15174 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15174 = calloc(tmp_strlen15174, sizeof(char));
      strcpy(tmp_str15174, setup);
      strcat(tmp_str15174, indent);
      int tmp_strlen15161 = strlen(tmp_str15174) + strlen("strcpy(") + 1;
      char* tmp_str15161 = calloc(tmp_strlen15161, sizeof(char));
      strcpy(tmp_str15161, tmp_str15174);
      strcat(tmp_str15161, "strcpy(");
      int tmp_strlen15150 = strlen(tmp_str15161) + strlen(tmp_str) + 1;
      char* tmp_str15150 = calloc(tmp_strlen15150, sizeof(char));
      strcpy(tmp_str15150, tmp_str15161);
      strcat(tmp_str15150, tmp_str);
      int tmp_strlen15142 = strlen(tmp_str15150) + strlen(", ") + 1;
      char* tmp_str15142 = calloc(tmp_strlen15142, sizeof(char));
      strcpy(tmp_str15142, tmp_str15150);
      strcat(tmp_str15142, ", ");
      int tmp_strlen15135 = strlen(tmp_str15142) + strlen(val) + 1;
      char* tmp_str15135 = calloc(tmp_strlen15135, sizeof(char));
      strcpy(tmp_str15135, tmp_str15142);
      strcat(tmp_str15135, val);
      int tmp_strlen15125 = strlen(tmp_str15135) + strlen(");\n") + 1;
      char* tmp_str15125 = calloc(tmp_strlen15125, sizeof(char));
      strcpy(tmp_str15125, tmp_str15135);
      strcat(tmp_str15125, ");\n");
      setup = tmp_str15125;
      int tmp_strlen15089 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15089 = calloc(tmp_strlen15089, sizeof(char));
      strcpy(tmp_str15089, setup);
      strcat(tmp_str15089, indent);
      int tmp_strlen15076 = strlen(tmp_str15089) + strlen("strcat(") + 1;
      char* tmp_str15076 = calloc(tmp_strlen15076, sizeof(char));
      strcpy(tmp_str15076, tmp_str15089);
      strcat(tmp_str15076, "strcat(");
      int tmp_strlen15065 = strlen(tmp_str15076) + strlen(tmp_str) + 1;
      char* tmp_str15065 = calloc(tmp_strlen15065, sizeof(char));
      strcpy(tmp_str15065, tmp_str15076);
      strcat(tmp_str15065, tmp_str);
      int tmp_strlen15057 = strlen(tmp_str15065) + strlen(", ") + 1;
      char* tmp_str15057 = calloc(tmp_strlen15057, sizeof(char));
      strcpy(tmp_str15057, tmp_str15065);
      strcat(tmp_str15057, ", ");
      int tmp_strlen15048 = strlen(tmp_str15057) + strlen(val_b) + 1;
      char* tmp_str15048 = calloc(tmp_strlen15048, sizeof(char));
      strcpy(tmp_str15048, tmp_str15057);
      strcat(tmp_str15048, val_b);
      int tmp_strlen15038 = strlen(tmp_str15048) + strlen(");\n") + 1;
      char* tmp_str15038 = calloc(tmp_strlen15038, sizeof(char));
      strcpy(tmp_str15038, tmp_str15048);
      strcat(tmp_str15038, ");\n");
      setup = tmp_str15038;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen14940 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str14940 = calloc(tmp_strlen14940, sizeof(char));
        strcpy(tmp_str14940, "(strcmp(");
        strcat(tmp_str14940, val);
        int tmp_strlen14932 = strlen(tmp_str14940) + strlen(", ") + 1;
        char* tmp_str14932 = calloc(tmp_strlen14932, sizeof(char));
        strcpy(tmp_str14932, tmp_str14940);
        strcat(tmp_str14932, ", ");
        int tmp_strlen14923 = strlen(tmp_str14932) + strlen(val_b) + 1;
        char* tmp_str14923 = calloc(tmp_strlen14923, sizeof(char));
        strcpy(tmp_str14923, tmp_str14932);
        strcat(tmp_str14923, val_b);
        int tmp_strlen14910 = strlen(tmp_str14923) + strlen(") == 0)") + 1;
        char* tmp_str14910 = calloc(tmp_strlen14910, sizeof(char));
        strcpy(tmp_str14910, tmp_str14923);
        strcat(tmp_str14910, ") == 0)");
        val = tmp_str14910;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen14837 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str14837 = calloc(tmp_strlen14837, sizeof(char));
          strcpy(tmp_str14837, "(strcmp(");
          strcat(tmp_str14837, val);
          int tmp_strlen14829 = strlen(tmp_str14837) + strlen(", ") + 1;
          char* tmp_str14829 = calloc(tmp_strlen14829, sizeof(char));
          strcpy(tmp_str14829, tmp_str14837);
          strcat(tmp_str14829, ", ");
          int tmp_strlen14820 = strlen(tmp_str14829) + strlen(val_b) + 1;
          char* tmp_str14820 = calloc(tmp_strlen14820, sizeof(char));
          strcpy(tmp_str14820, tmp_str14829);
          strcat(tmp_str14820, val_b);
          int tmp_strlen14807 = strlen(tmp_str14820) + strlen(") != 0)") + 1;
          char* tmp_str14807 = calloc(tmp_strlen14807, sizeof(char));
          strcpy(tmp_str14807, tmp_str14820);
          strcat(tmp_str14807, ") != 0)");
          val = tmp_str14807;
        } else {
          int tmp_strlen14761 = strlen("(") + strlen(val) + 1;
          char* tmp_str14761 = calloc(tmp_strlen14761, sizeof(char));
          strcpy(tmp_str14761, "(");
          strcat(tmp_str14761, val);
          int tmp_strlen14753 = strlen(tmp_str14761) + strlen(") ") + 1;
          char* tmp_str14753 = calloc(tmp_strlen14753, sizeof(char));
          strcpy(tmp_str14753, tmp_str14761);
          strcat(tmp_str14753, ") ");
          int tmp_strlen14743 = strlen(tmp_str14753) + strlen(op_str) + 1;
          char* tmp_str14743 = calloc(tmp_strlen14743, sizeof(char));
          strcpy(tmp_str14743, tmp_str14753);
          strcat(tmp_str14743, op_str);
          int tmp_strlen14735 = strlen(tmp_str14743) + strlen(" (") + 1;
          char* tmp_str14735 = calloc(tmp_strlen14735, sizeof(char));
          strcpy(tmp_str14735, tmp_str14743);
          strcat(tmp_str14735, " (");
          int tmp_strlen14726 = strlen(tmp_str14735) + strlen(val_b) + 1;
          char* tmp_str14726 = calloc(tmp_strlen14726, sizeof(char));
          strcpy(tmp_str14726, tmp_str14735);
          strcat(tmp_str14726, val_b);
          int tmp_strlen14719 = strlen(tmp_str14726) + strlen(")") + 1;
          char* tmp_str14719 = calloc(tmp_strlen14719, sizeof(char));
          strcpy(tmp_str14719, tmp_str14726);
          strcat(tmp_str14719, ")");
          val = tmp_str14719;
        }
      }
    }
    Peek_results tmp_results14700 = Peek(src);
    op = tmp_results14700.result1;
    tok_str = tmp_results14700.result2;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results14517 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results14517.result1;
  setup = tmp_results14517.result2;
  expr = tmp_results14517.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results14283 = TranslateExpr(src, indent);
  src = tmp_results14283.result1;
  expr_setup = tmp_results14283.result2;
  expr_value = tmp_results14283.result3;
  int tok;
  char* tok_str;
  Peek_results tmp_results14181 = Peek(src);
  tok = tmp_results14181.result1;
  tok_str = tmp_results14181.result2;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results14010 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results14010.result1;
    tok_str = tmp_results14010.result2;
    TranslateExpr_results tmp_results13958 = TranslateExpr(src, indent);
    src = tmp_results13958.result1;
    expr_setup = tmp_results13958.result2;
    expr_value = tmp_results13958.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen13816 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str13816 = calloc(tmp_strlen13816, sizeof(char));
    strcpy(tmp_str13816, exprs_setup);
    strcat(tmp_str13816, expr_setup);
    exprs_setup = tmp_str13816;
    int tmp_strlen13774 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str13774 = calloc(tmp_strlen13774, sizeof(char));
    strcpy(tmp_str13774, exprs_value);
    strcat(tmp_str13774, ", ");
    int tmp_strlen13760 = strlen(tmp_str13774) + strlen(expr_value) + 1;
    char* tmp_str13760 = calloc(tmp_strlen13760, sizeof(char));
    strcpy(tmp_str13760, tmp_str13774);
    strcat(tmp_str13760, expr_value);
    exprs_value = tmp_str13760;
    Peek_results tmp_results13751 = Peek(src);
    tok = tmp_results13751.result1;
    tok_str = tmp_results13751.result2;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results13580 = ConsumeIdent(src);
  src = tmp_results13580.result1;
  name = tmp_results13580.result2;
  char* tok_str;
  ConsumeToken_results tmp_results13522 = ConsumeToken(src, TOK_COLON);
  src = tmp_results13522.result1;
  tok_str = tmp_results13522.result2;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results13433 = TranslateType(src);
  src = tmp_results13433.result1;
  typ = tmp_results13433.result2;
  typ_str = tmp_results13433.result3;
  int tmp_strlen13358 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str13358 = calloc(tmp_strlen13358, sizeof(char));
  strcpy(tmp_str13358, typ_str);
  strcat(tmp_str13358, " ");
  int tmp_strlen13350 = strlen(tmp_str13358) + strlen(name) + 1;
  char* tmp_str13350 = calloc(tmp_strlen13350, sizeof(char));
  strcpy(tmp_str13350, tmp_str13358);
  strcat(tmp_str13350, name);
  char* out = tmp_str13350;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results13225 = ConsumeToken(src, TOK_LET);
  src = tmp_results13225.result1;
  tok_str = tmp_results13225.result2;
  char* out;
  TranslateConstOrVar_results tmp_results13159 = TranslateConstOrVar(src);
  src = tmp_results13159.result1;
  out = tmp_results13159.result2;
  int tmp_strlen13098 = strlen("const ") + strlen(out) + 1;
  char* tmp_str13098 = calloc(tmp_strlen13098, sizeof(char));
  strcpy(tmp_str13098, "const ");
  strcat(tmp_str13098, out);
  out = tmp_str13098;
  ConsumeToken_results tmp_results13093 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results13093.result1;
  tok_str = tmp_results13093.result2;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results13002 = TranslateExpr(src, indent);
  src = tmp_results13002.result1;
  setup = tmp_results13002.result2;
  val = tmp_results13002.result3;
  ConsumeToken_results tmp_results12953 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results12953.result1;
  tok_str = tmp_results12953.result2;
  int tmp_strlen12885 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str12885 = calloc(tmp_strlen12885, sizeof(char));
  strcpy(tmp_str12885, out);
  strcat(tmp_str12885, " = ");
  int tmp_strlen12878 = strlen(tmp_str12885) + strlen(val) + 1;
  char* tmp_str12878 = calloc(tmp_strlen12878, sizeof(char));
  strcpy(tmp_str12878, tmp_str12885);
  strcat(tmp_str12878, val);
  int tmp_strlen12869 = strlen(tmp_str12878) + strlen(";\n") + 1;
  char* tmp_str12869 = calloc(tmp_strlen12869, sizeof(char));
  strcpy(tmp_str12869, tmp_str12878);
  strcat(tmp_str12869, ";\n");
  out = tmp_str12869;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results12744 = TranslateConstDecl(src, indent);
  src = tmp_results12744.result1;
  out = tmp_results12744.result2;
  int tmp_strlen12672 = strlen(indent) + strlen(out) + 1;
  char* tmp_str12672 = calloc(tmp_strlen12672, sizeof(char));
  strcpy(tmp_str12672, indent);
  strcat(tmp_str12672, out);
  return (TranslateConstDeclStmt_results){src, tmp_str12672};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results12548 = ConsumeToken(src, TOK_VAR);
  src = tmp_results12548.result1;
  tok_str = tmp_results12548.result2;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results12435 = TranslateConstOrVar(src);
  src = tmp_results12435.result1;
  out = tmp_results12435.result2;
  Peek_results tmp_results12395 = Peek(src);
  tok = tmp_results12395.result1;
  tok_str = tmp_results12395.result2;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results12335 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results12335.result1;
    tok_str = tmp_results12335.result2;
    TranslateExpr_results tmp_results12282 = TranslateExpr(src, indent);
    src = tmp_results12282.result1;
    setup = tmp_results12282.result2;
    val = tmp_results12282.result3;
    ConsumeToken_results tmp_results12229 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results12229.result1;
    tok_str = tmp_results12229.result2;
    int tmp_strlen12157 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str12157 = calloc(tmp_strlen12157, sizeof(char));
    strcpy(tmp_str12157, out);
    strcat(tmp_str12157, " = ");
    int tmp_strlen12150 = strlen(tmp_str12157) + strlen(val) + 1;
    char* tmp_str12150 = calloc(tmp_strlen12150, sizeof(char));
    strcpy(tmp_str12150, tmp_str12157);
    strcat(tmp_str12150, val);
    out = tmp_str12150;
  }
  int tmp_strlen12118 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str12118 = calloc(tmp_strlen12118, sizeof(char));
  strcpy(tmp_str12118, setup);
  strcat(tmp_str12118, indent);
  int tmp_strlen12111 = strlen(tmp_str12118) + strlen(out) + 1;
  char* tmp_str12111 = calloc(tmp_strlen12111, sizeof(char));
  strcpy(tmp_str12111, tmp_str12118);
  strcat(tmp_str12111, out);
  int tmp_strlen12102 = strlen(tmp_str12111) + strlen(";\n") + 1;
  char* tmp_str12102 = calloc(tmp_strlen12102, sizeof(char));
  strcpy(tmp_str12102, tmp_str12111);
  strcat(tmp_str12102, ";\n");
  out = tmp_str12102;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen11947 = (x) - (0) + 1;
  char* tmp_str11947 = calloc(tmp_strlen11947, sizeof(char));
  strncpy(tmp_str11947, src + 0, tmp_strlen11947 - 1);
  tmp_str11947[tmp_strlen11947 - 1] = 0;
  char* lhs = tmp_str11947;
  int tmp_strlen11917 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str11917 = calloc(tmp_strlen11917, sizeof(char));
  strncpy(tmp_str11917, src + (x) + (1), tmp_strlen11917 - 1);
  tmp_str11917[tmp_strlen11917 - 1] = 0;
  char* rhs = tmp_str11917;
  char* lhs_ident;
  ConsumeIdent_results tmp_results11880 = ConsumeIdent(lhs);
  lhs = tmp_results11880.result1;
  lhs_ident = tmp_results11880.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results11764 = TranslateExpr(rhs, indent);
  rhs = tmp_results11764.result1;
  setup = tmp_results11764.result2;
  rhs_expr = tmp_results11764.result3;
  int lhs_tok;
  char* lhs_tok_str;
  int rhs_tok;
  char* rhs_tok_str;
  Peek_results tmp_results11612 = Peek(lhs);
  lhs_tok = tmp_results11612.result1;
  lhs_tok_str = tmp_results11612.result2;
  Peek_results tmp_results11575 = Peek(rhs);
  rhs_tok = tmp_results11575.result1;
  rhs_tok_str = tmp_results11575.result2;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results11450 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results11450.result1;
    func_name = tmp_results11450.result2;
    int tmp_strlen11342 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str11342 = calloc(tmp_strlen11342, sizeof(char));
    strcpy(tmp_str11342, "tmp_results");
    strcat(tmp_str11342, itoa(strlen(src)));
    char* tmp_results = tmp_str11342;
    char* out = setup;
    int tmp_strlen11282 = strlen(out) + strlen(indent) + 1;
    char* tmp_str11282 = calloc(tmp_strlen11282, sizeof(char));
    strcpy(tmp_str11282, out);
    strcat(tmp_str11282, indent);
    int tmp_strlen11269 = strlen(tmp_str11282) + strlen(func_name) + 1;
    char* tmp_str11269 = calloc(tmp_strlen11269, sizeof(char));
    strcpy(tmp_str11269, tmp_str11282);
    strcat(tmp_str11269, func_name);
    int tmp_strlen11254 = strlen(tmp_str11269) + strlen("_results ") + 1;
    char* tmp_str11254 = calloc(tmp_strlen11254, sizeof(char));
    strcpy(tmp_str11254, tmp_str11269);
    strcat(tmp_str11254, "_results ");
    int tmp_strlen11239 = strlen(tmp_str11254) + strlen(tmp_results) + 1;
    char* tmp_str11239 = calloc(tmp_strlen11239, sizeof(char));
    strcpy(tmp_str11239, tmp_str11254);
    strcat(tmp_str11239, tmp_results);
    int tmp_strlen11230 = strlen(tmp_str11239) + strlen(" = ") + 1;
    char* tmp_str11230 = calloc(tmp_strlen11230, sizeof(char));
    strcpy(tmp_str11230, tmp_str11239);
    strcat(tmp_str11230, " = ");
    int tmp_strlen11218 = strlen(tmp_str11230) + strlen(rhs_expr) + 1;
    char* tmp_str11218 = calloc(tmp_strlen11218, sizeof(char));
    strcpy(tmp_str11218, tmp_str11230);
    strcat(tmp_str11218, rhs_expr);
    int tmp_strlen11209 = strlen(tmp_str11218) + strlen(";\n") + 1;
    char* tmp_str11209 = calloc(tmp_strlen11209, sizeof(char));
    strcpy(tmp_str11209, tmp_str11218);
    strcat(tmp_str11209, ";\n");
    out = tmp_str11209;
    int tmp_strlen11181 = strlen(out) + strlen(indent) + 1;
    char* tmp_str11181 = calloc(tmp_strlen11181, sizeof(char));
    strcpy(tmp_str11181, out);
    strcat(tmp_str11181, indent);
    int tmp_strlen11168 = strlen(tmp_str11181) + strlen(lhs_ident) + 1;
    char* tmp_str11168 = calloc(tmp_strlen11168, sizeof(char));
    strcpy(tmp_str11168, tmp_str11181);
    strcat(tmp_str11168, lhs_ident);
    int tmp_strlen11159 = strlen(tmp_str11168) + strlen(" = ") + 1;
    char* tmp_str11159 = calloc(tmp_strlen11159, sizeof(char));
    strcpy(tmp_str11159, tmp_str11168);
    strcat(tmp_str11159, " = ");
    int tmp_strlen11144 = strlen(tmp_str11159) + strlen(tmp_results) + 1;
    char* tmp_str11144 = calloc(tmp_strlen11144, sizeof(char));
    strcpy(tmp_str11144, tmp_str11159);
    strcat(tmp_str11144, tmp_results);
    int tmp_strlen11127 = strlen(tmp_str11144) + strlen(".result1;\n") + 1;
    char* tmp_str11127 = calloc(tmp_strlen11127, sizeof(char));
    strcpy(tmp_str11127, tmp_str11144);
    strcat(tmp_str11127, ".result1;\n");
    out = tmp_str11127;
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results11001 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results11001.result1;
      lhs_tok_str = tmp_results11001.result2;
      ConsumeIdent_results tmp_results10941 = ConsumeIdent(lhs);
      lhs = tmp_results10941.result1;
      lhs_ident = tmp_results10941.result2;
      int tmp_strlen10875 = strlen(out) + strlen(indent) + 1;
      char* tmp_str10875 = calloc(tmp_strlen10875, sizeof(char));
      strcpy(tmp_str10875, out);
      strcat(tmp_str10875, indent);
      int tmp_strlen10862 = strlen(tmp_str10875) + strlen(lhs_ident) + 1;
      char* tmp_str10862 = calloc(tmp_strlen10862, sizeof(char));
      strcpy(tmp_str10862, tmp_str10875);
      strcat(tmp_str10862, lhs_ident);
      int tmp_strlen10853 = strlen(tmp_str10862) + strlen(" = ") + 1;
      char* tmp_str10853 = calloc(tmp_strlen10853, sizeof(char));
      strcpy(tmp_str10853, tmp_str10862);
      strcat(tmp_str10853, " = ");
      int tmp_strlen10838 = strlen(tmp_str10853) + strlen(tmp_results) + 1;
      char* tmp_str10838 = calloc(tmp_strlen10838, sizeof(char));
      strcpy(tmp_str10838, tmp_str10853);
      strcat(tmp_str10838, tmp_results);
      int tmp_strlen10825 = strlen(tmp_str10838) + strlen(".result") + 1;
      char* tmp_str10825 = calloc(tmp_strlen10825, sizeof(char));
      strcpy(tmp_str10825, tmp_str10838);
      strcat(tmp_str10825, ".result");
      int tmp_strlen10803 = strlen(tmp_str10825) + strlen(itoa(result_count)) + 1;
      char* tmp_str10803 = calloc(tmp_strlen10803, sizeof(char));
      strcpy(tmp_str10803, tmp_str10825);
      strcat(tmp_str10803, itoa(result_count));
      int tmp_strlen10794 = strlen(tmp_str10803) + strlen(";\n") + 1;
      char* tmp_str10794 = calloc(tmp_strlen10794, sizeof(char));
      strcpy(tmp_str10794, tmp_str10803);
      strcat(tmp_str10794, ";\n");
      out = tmp_str10794;
      Peek_results tmp_results10781 = Peek(lhs);
      lhs_tok = tmp_results10781.result1;
      lhs_tok_str = tmp_results10781.result2;
    }
    char* tok_str;
    ConsumeToken_results tmp_results10702 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results10702.result1;
    tok_str = tmp_results10702.result2;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen10577 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str10577 = calloc(tmp_strlen10577, sizeof(char));
  strcpy(tmp_str10577, indent);
  strcat(tmp_str10577, lhs_ident);
  int tmp_strlen10568 = strlen(tmp_str10577) + strlen(" = ") + 1;
  char* tmp_str10568 = calloc(tmp_strlen10568, sizeof(char));
  strcpy(tmp_str10568, tmp_str10577);
  strcat(tmp_str10568, " = ");
  int tmp_strlen10556 = strlen(tmp_str10568) + strlen(rhs_expr) + 1;
  char* tmp_str10556 = calloc(tmp_strlen10556, sizeof(char));
  strcpy(tmp_str10556, tmp_str10568);
  strcat(tmp_str10556, rhs_expr);
  int tmp_strlen10547 = strlen(tmp_str10556) + strlen(";\n") + 1;
  char* tmp_str10547 = calloc(tmp_strlen10547, sizeof(char));
  strcpy(tmp_str10547, tmp_str10556);
  strcat(tmp_str10547, ";\n");
  char* assignments = tmp_str10547;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results10507 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results10507.result1;
    lhs_tok_str = tmp_results10507.result2;
    ConsumeToken_results tmp_results10451 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results10451.result1;
    rhs_tok_str = tmp_results10451.result2;
    ConsumeIdent_results tmp_results10395 = ConsumeIdent(lhs);
    lhs = tmp_results10395.result1;
    lhs_ident = tmp_results10395.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results10317 = TranslateExpr(rhs, indent);
    rhs = tmp_results10317.result1;
    rhs_expr_setup = tmp_results10317.result2;
    rhs_expr = tmp_results10317.result3;
    int tmp_strlen10219 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str10219 = calloc(tmp_strlen10219, sizeof(char));
    strcpy(tmp_str10219, setup);
    strcat(tmp_str10219, rhs_expr_setup);
    setup = tmp_str10219;
    int tmp_strlen10175 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str10175 = calloc(tmp_strlen10175, sizeof(char));
    strcpy(tmp_str10175, assignments);
    strcat(tmp_str10175, indent);
    int tmp_strlen10162 = strlen(tmp_str10175) + strlen(lhs_ident) + 1;
    char* tmp_str10162 = calloc(tmp_strlen10162, sizeof(char));
    strcpy(tmp_str10162, tmp_str10175);
    strcat(tmp_str10162, lhs_ident);
    int tmp_strlen10153 = strlen(tmp_str10162) + strlen(" = ") + 1;
    char* tmp_str10153 = calloc(tmp_strlen10153, sizeof(char));
    strcpy(tmp_str10153, tmp_str10162);
    strcat(tmp_str10153, " = ");
    int tmp_strlen10141 = strlen(tmp_str10153) + strlen(rhs_expr) + 1;
    char* tmp_str10141 = calloc(tmp_strlen10141, sizeof(char));
    strcpy(tmp_str10141, tmp_str10153);
    strcat(tmp_str10141, rhs_expr);
    int tmp_strlen10132 = strlen(tmp_str10141) + strlen(";\n") + 1;
    char* tmp_str10132 = calloc(tmp_strlen10132, sizeof(char));
    strcpy(tmp_str10132, tmp_str10141);
    strcat(tmp_str10132, ";\n");
    assignments = tmp_str10132;
    Peek_results tmp_results10123 = Peek(lhs);
    lhs_tok = tmp_results10123.result1;
    lhs_tok_str = tmp_results10123.result2;
  }
  char* tok_str;
  ConsumeToken_results tmp_results10056 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results10056.result1;
  tok_str = tmp_results10056.result2;
  int tmp_strlen9974 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str9974 = calloc(tmp_strlen9974, sizeof(char));
  strcpy(tmp_str9974, setup);
  strcat(tmp_str9974, assignments);
  return (TranslateAssignStmt_results){src, tmp_str9974};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results9853 = ConsumeToken(src, TOK_IF);
  src = tmp_results9853.result1;
  tok_str = tmp_results9853.result2;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results9760 = TranslateExpr(src, indent);
  src = tmp_results9760.result1;
  cond_setup = tmp_results9760.result2;
  cond = tmp_results9760.result3;
  ConsumeToken_results tmp_results9705 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results9705.result1;
  tok_str = tmp_results9705.result2;
  char* out = cond_setup;
  int tmp_strlen9604 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9604 = calloc(tmp_strlen9604, sizeof(char));
  strcpy(tmp_str9604, out);
  strcat(tmp_str9604, indent);
  int tmp_strlen9594 = strlen(tmp_str9604) + strlen("if (") + 1;
  char* tmp_str9594 = calloc(tmp_strlen9594, sizeof(char));
  strcpy(tmp_str9594, tmp_str9604);
  strcat(tmp_str9594, "if (");
  int tmp_strlen9586 = strlen(tmp_str9594) + strlen(cond) + 1;
  char* tmp_str9586 = calloc(tmp_strlen9586, sizeof(char));
  strcpy(tmp_str9586, tmp_str9594);
  strcat(tmp_str9586, cond);
  int tmp_strlen9575 = strlen(tmp_str9586) + strlen(") {\n") + 1;
  char* tmp_str9575 = calloc(tmp_strlen9575, sizeof(char));
  strcpy(tmp_str9575, tmp_str9586);
  strcat(tmp_str9575, ") {\n");
  out = tmp_str9575;
  char* body;
  int tmp_strlen9494 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str9494 = calloc(tmp_strlen9494, sizeof(char));
  strcpy(tmp_str9494, indent);
  strcat(tmp_str9494, SINGLE_INDENT);
  TranslateStmts_results tmp_results9549 = TranslateStmts(src, tmp_str9494, func_name);
  src = tmp_results9549.result1;
  body = tmp_results9549.result2;
  ConsumeToken_results tmp_results9477 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results9477.result1;
  tok_str = tmp_results9477.result2;
  int tmp_strlen9411 = strlen(out) + strlen(body) + 1;
  char* tmp_str9411 = calloc(tmp_strlen9411, sizeof(char));
  strcpy(tmp_str9411, out);
  strcat(tmp_str9411, body);
  out = tmp_str9411;
  int tmp_strlen9387 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9387 = calloc(tmp_strlen9387, sizeof(char));
  strcpy(tmp_str9387, out);
  strcat(tmp_str9387, indent);
  int tmp_strlen9380 = strlen(tmp_str9387) + strlen("}") + 1;
  char* tmp_str9380 = calloc(tmp_strlen9380, sizeof(char));
  strcpy(tmp_str9380, tmp_str9387);
  strcat(tmp_str9380, "}");
  out = tmp_str9380;
  int tok;
  Peek_results tmp_results9358 = Peek(src);
  tok = tmp_results9358.result1;
  tok_str = tmp_results9358.result2;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen9277 = strlen(out) + strlen("\n") + 1;
    char* tmp_str9277 = calloc(tmp_strlen9277, sizeof(char));
    strcpy(tmp_str9277, out);
    strcat(tmp_str9277, "\n");
    return (TranslateIfStmt_results){src, tmp_str9277};
  }
  ConsumeToken_results tmp_results9266 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results9266.result1;
  tok_str = tmp_results9266.result2;
  Peek_results tmp_results9219 = Peek(src);
  tok = tmp_results9219.result1;
  tok_str = tmp_results9219.result2;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen9078 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str9078 = calloc(tmp_strlen9078, sizeof(char));
    strcpy(tmp_str9078, indent);
    strcat(tmp_str9078, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results9138 = TranslateIfStmt(src, tmp_str9078, func_name);
    src = tmp_results9138.result1;
    else_out = tmp_results9138.result2;
    int tmp_strlen9033 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str9033 = calloc(tmp_strlen9033, sizeof(char));
    strcpy(tmp_str9033, out);
    strcat(tmp_str9033, " else {\n");
    out = tmp_str9033;
    int tmp_strlen9003 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str9003 = calloc(tmp_strlen9003, sizeof(char));
    strcpy(tmp_str9003, out);
    strcat(tmp_str9003, else_out);
    out = tmp_str9003;
    int tmp_strlen8975 = strlen(out) + strlen(indent) + 1;
    char* tmp_str8975 = calloc(tmp_strlen8975, sizeof(char));
    strcpy(tmp_str8975, out);
    strcat(tmp_str8975, indent);
    int tmp_strlen8966 = strlen(tmp_str8975) + strlen("}\n") + 1;
    char* tmp_str8966 = calloc(tmp_strlen8966, sizeof(char));
    strcpy(tmp_str8966, tmp_str8975);
    strcat(tmp_str8966, "}\n");
    out = tmp_str8966;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results8931 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8931.result1;
  tok_str = tmp_results8931.result2;
  int tmp_strlen8823 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str8823 = calloc(tmp_strlen8823, sizeof(char));
  strcpy(tmp_str8823, indent);
  strcat(tmp_str8823, SINGLE_INDENT);
  TranslateStmts_results tmp_results8882 = TranslateStmts(src, tmp_str8823, func_name);
  src = tmp_results8882.result1;
  else_out = tmp_results8882.result2;
  ConsumeToken_results tmp_results8806 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results8806.result1;
  tok_str = tmp_results8806.result2;
  int tmp_strlen8733 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str8733 = calloc(tmp_strlen8733, sizeof(char));
  strcpy(tmp_str8733, out);
  strcat(tmp_str8733, " else {\n");
  out = tmp_str8733;
  int tmp_strlen8707 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str8707 = calloc(tmp_strlen8707, sizeof(char));
  strcpy(tmp_str8707, out);
  strcat(tmp_str8707, else_out);
  out = tmp_str8707;
  int tmp_strlen8683 = strlen(out) + strlen(indent) + 1;
  char* tmp_str8683 = calloc(tmp_strlen8683, sizeof(char));
  strcpy(tmp_str8683, out);
  strcat(tmp_str8683, indent);
  int tmp_strlen8674 = strlen(tmp_str8683) + strlen("}\n") + 1;
  char* tmp_str8674 = calloc(tmp_strlen8674, sizeof(char));
  strcpy(tmp_str8674, tmp_str8683);
  strcat(tmp_str8674, "}\n");
  out = tmp_str8674;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results8515 = ConsumeToken(src, TOK_FOR);
  src = tmp_results8515.result1;
  tok_str = tmp_results8515.result2;
  Peek_results tmp_results8469 = Peek(src);
  tok = tmp_results8469.result1;
  tok_str = tmp_results8469.result2;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen8281 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8281 = calloc(tmp_strlen8281, sizeof(char));
    strcpy(tmp_str8281, indent);
    strcat(tmp_str8281, SINGLE_INDENT);
    TranslateExpr_results tmp_results8347 = TranslateExpr(src, tmp_str8281);
    src = tmp_results8347.result1;
    cond_setup = tmp_results8347.result2;
    cond = tmp_results8347.result3;
  }
  ConsumeToken_results tmp_results8269 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8269.result1;
  tok_str = tmp_results8269.result2;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen8145 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str8145 = calloc(tmp_strlen8145, sizeof(char));
    strcpy(tmp_str8145, indent);
    strcat(tmp_str8145, "while (");
    int tmp_strlen8137 = strlen(tmp_str8145) + strlen(cond) + 1;
    char* tmp_str8137 = calloc(tmp_strlen8137, sizeof(char));
    strcpy(tmp_str8137, tmp_str8145);
    strcat(tmp_str8137, cond);
    int tmp_strlen8126 = strlen(tmp_str8137) + strlen(") {\n") + 1;
    char* tmp_str8126 = calloc(tmp_strlen8126, sizeof(char));
    strcpy(tmp_str8126, tmp_str8137);
    strcat(tmp_str8126, ") {\n");
    out = tmp_str8126;
  } else {
    int tmp_strlen8070 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str8070 = calloc(tmp_strlen8070, sizeof(char));
    strcpy(tmp_str8070, indent);
    strcat(tmp_str8070, "while (true) {\n");
    out = tmp_str8070;
    int tmp_strlen8038 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str8038 = calloc(tmp_strlen8038, sizeof(char));
    strcpy(tmp_str8038, out);
    strcat(tmp_str8038, cond_setup);
    out = tmp_str8038;
    int tmp_strlen8010 = strlen(out) + strlen(indent) + 1;
    char* tmp_str8010 = calloc(tmp_strlen8010, sizeof(char));
    strcpy(tmp_str8010, out);
    strcat(tmp_str8010, indent);
    int tmp_strlen7993 = strlen(tmp_str8010) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str7993 = calloc(tmp_strlen7993, sizeof(char));
    strcpy(tmp_str7993, tmp_str8010);
    strcat(tmp_str7993, SINGLE_INDENT);
    int tmp_strlen7981 = strlen(tmp_str7993) + strlen("if (!(") + 1;
    char* tmp_str7981 = calloc(tmp_strlen7981, sizeof(char));
    strcpy(tmp_str7981, tmp_str7993);
    strcat(tmp_str7981, "if (!(");
    int tmp_strlen7973 = strlen(tmp_str7981) + strlen(cond) + 1;
    char* tmp_str7973 = calloc(tmp_strlen7973, sizeof(char));
    strcpy(tmp_str7973, tmp_str7981);
    strcat(tmp_str7973, cond);
    int tmp_strlen7956 = strlen(tmp_str7973) + strlen(")) break;\n") + 1;
    char* tmp_str7956 = calloc(tmp_strlen7956, sizeof(char));
    strcpy(tmp_str7956, tmp_str7973);
    strcat(tmp_str7956, ")) break;\n");
    out = tmp_str7956;
  }
  char* body;
  int tmp_strlen7869 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str7869 = calloc(tmp_strlen7869, sizeof(char));
  strcpy(tmp_str7869, indent);
  strcat(tmp_str7869, SINGLE_INDENT);
  TranslateStmts_results tmp_results7924 = TranslateStmts(src, tmp_str7869, func_name);
  src = tmp_results7924.result1;
  body = tmp_results7924.result2;
  ConsumeToken_results tmp_results7852 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results7852.result1;
  tok_str = tmp_results7852.result2;
  int tmp_strlen7786 = strlen(out) + strlen(body) + 1;
  char* tmp_str7786 = calloc(tmp_strlen7786, sizeof(char));
  strcpy(tmp_str7786, out);
  strcat(tmp_str7786, body);
  out = tmp_str7786;
  int tmp_strlen7762 = strlen(out) + strlen(indent) + 1;
  char* tmp_str7762 = calloc(tmp_strlen7762, sizeof(char));
  strcpy(tmp_str7762, out);
  strcat(tmp_str7762, indent);
  int tmp_strlen7753 = strlen(tmp_str7762) + strlen("}\n") + 1;
  char* tmp_str7753 = calloc(tmp_strlen7753, sizeof(char));
  strcpy(tmp_str7753, tmp_str7762);
  strcat(tmp_str7753, "}\n");
  out = tmp_str7753;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results7625 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results7625.result1;
  tok_str = tmp_results7625.result2;
  int tmp_strlen7541 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str7541 = calloc(tmp_strlen7541, sizeof(char));
  strcpy(tmp_str7541, indent);
  strcat(tmp_str7541, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str7541};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results7436 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results7436.result1;
  tok_str = tmp_results7436.result2;
  int tmp_strlen7358 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str7358 = calloc(tmp_strlen7358, sizeof(char));
  strcpy(tmp_str7358, indent);
  strcat(tmp_str7358, "break;");
  return (TranslateBreakStmt_results){src, tmp_str7358};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results7233 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results7233.result1;
  tok_str = tmp_results7233.result2;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results7104 = TranslateExprs(src, indent);
  src = tmp_results7104.result1;
  expr_count = tmp_results7104.result2;
  exprs_setup = tmp_results7104.result3;
  exprs_value = tmp_results7104.result4;
  ConsumeToken_results tmp_results7028 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results7028.result1;
  tok_str = tmp_results7028.result2;
  int tmp_strlen6939 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str6939 = calloc(tmp_strlen6939, sizeof(char));
  strcpy(tmp_str6939, exprs_setup);
  strcat(tmp_str6939, indent);
  int tmp_strlen6926 = strlen(tmp_str6939) + strlen("return ") + 1;
  char* tmp_str6926 = calloc(tmp_strlen6926, sizeof(char));
  strcpy(tmp_str6926, tmp_str6939);
  strcat(tmp_str6926, "return ");
  char* out = tmp_str6926;
  if ((expr_count) > (1)) {
    int tmp_strlen6877 = strlen(out) + strlen("(") + 1;
    char* tmp_str6877 = calloc(tmp_strlen6877, sizeof(char));
    strcpy(tmp_str6877, out);
    strcat(tmp_str6877, "(");
    int tmp_strlen6864 = strlen(tmp_str6877) + strlen(func_name) + 1;
    char* tmp_str6864 = calloc(tmp_strlen6864, sizeof(char));
    strcpy(tmp_str6864, tmp_str6877);
    strcat(tmp_str6864, func_name);
    int tmp_strlen6848 = strlen(tmp_str6864) + strlen("_results){") + 1;
    char* tmp_str6848 = calloc(tmp_strlen6848, sizeof(char));
    strcpy(tmp_str6848, tmp_str6864);
    strcat(tmp_str6848, "_results){");
    out = tmp_str6848;
  }
  int tmp_strlen6813 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str6813 = calloc(tmp_strlen6813, sizeof(char));
  strcpy(tmp_str6813, out);
  strcat(tmp_str6813, exprs_value);
  out = tmp_str6813;
  if ((expr_count) > (1)) {
    int tmp_strlen6763 = strlen(out) + strlen("}") + 1;
    char* tmp_str6763 = calloc(tmp_strlen6763, sizeof(char));
    strcpy(tmp_str6763, out);
    strcat(tmp_str6763, "}");
    out = tmp_str6763;
  }
  int tmp_strlen6734 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str6734 = calloc(tmp_strlen6734, sizeof(char));
  strcpy(tmp_str6734, out);
  strcat(tmp_str6734, ";\n");
  out = tmp_str6734;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6578 = Peek(src);
  tok = tmp_results6578.result1;
  tok_str = tmp_results6578.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results6501 = TranslateConstDeclStmt(src, indent);
    src = tmp_results6501.result1;
    out = tmp_results6501.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results6391 = TranslateVarDeclStmt(src, indent);
      src = tmp_results6391.result1;
      out = tmp_results6391.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results6284 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results6284.result1;
        out = tmp_results6284.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results6170 = TranslateForStmt(src, indent, func_name);
          src = tmp_results6170.result1;
          out = tmp_results6170.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results6050 = TranslateContinueStmt(src, indent);
            src = tmp_results6050.result1;
            out = tmp_results6050.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results5939 = TranslateBreakStmt(src, indent);
              src = tmp_results5939.result1;
              out = tmp_results5939.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results5830 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results5830.result1;
                out = tmp_results5830.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if ((tok) == (TOK_IDENT)) {
                  char* first_ident;
                  ConsumeIdent_results tmp_results5678 = ConsumeIdent(src);
                  src = tmp_results5678.result1;
                  first_ident = tmp_results5678.result2;
                  Peek_results tmp_results5633 = Peek(src);
                  tok = tmp_results5633.result1;
                  tok_str = tmp_results5633.result2;
                  int tmp_strlen5576 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str5576 = calloc(tmp_strlen5576, sizeof(char));
                  strcpy(tmp_str5576, first_ident);
                  strcat(tmp_str5576, src);
                  src = tmp_str5576;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results5512 = TranslateAssignStmt(src, indent);
                    src = tmp_results5512.result1;
                    out = tmp_results5512.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results5353 = TranslateExpr(src, indent);
                    src = tmp_results5353.result1;
                    setup = tmp_results5353.result2;
                    val = tmp_results5353.result3;
                    ConsumeToken_results tmp_results5296 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results5296.result1;
                    tok_str = tmp_results5296.result2;
                    int tmp_strlen5217 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str5217 = calloc(tmp_strlen5217, sizeof(char));
                    strcpy(tmp_str5217, setup);
                    strcat(tmp_str5217, indent);
                    int tmp_strlen5210 = strlen(tmp_str5217) + strlen(val) + 1;
                    char* tmp_str5210 = calloc(tmp_strlen5210, sizeof(char));
                    strcpy(tmp_str5210, tmp_str5217);
                    strcat(tmp_str5210, val);
                    int tmp_strlen5201 = strlen(tmp_str5210) + strlen(";\n") + 1;
                    char* tmp_str5201 = calloc(tmp_strlen5201, sizeof(char));
                    strcpy(tmp_str5201, tmp_str5210);
                    strcat(tmp_str5201, ";\n");
                    out = tmp_str5201;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen5092 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str5092 = calloc(tmp_strlen5092, sizeof(char));
                  strcpy(tmp_str5092, "unexpected stmt token, got: ");
                  strcat(tmp_str5092, itoa(tok));
                  int tmp_strlen5083 = strlen(tmp_str5092) + strlen(" \"") + 1;
                  char* tmp_str5083 = calloc(tmp_strlen5083, sizeof(char));
                  strcpy(tmp_str5083, tmp_str5092);
                  strcat(tmp_str5083, " \"");
                  int tmp_strlen5072 = strlen(tmp_str5083) + strlen(tok_str) + 1;
                  char* tmp_str5072 = calloc(tmp_strlen5072, sizeof(char));
                  strcpy(tmp_str5072, tmp_str5083);
                  strcat(tmp_str5072, tok_str);
                  int tmp_strlen5064 = strlen(tmp_str5072) + strlen("\"") + 1;
                  char* tmp_str5064 = calloc(tmp_strlen5064, sizeof(char));
                  strcpy(tmp_str5064, tmp_str5072);
                  strcat(tmp_str5064, "\"");
                  printf("%s", tmp_str5064);
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
  Peek_results tmp_results4904 = Peek(src);
  tok = tmp_results4904.result1;
  tok_str = tmp_results4904.result2;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results4782 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results4782.result1;
      tok_str = tmp_results4782.result2;
      Peek_results tmp_results4724 = Peek(src);
      tok = tmp_results4724.result1;
      tok_str = tmp_results4724.result2;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results4631 = TranslateStmt(src, indent, func_name);
    src = tmp_results4631.result1;
    stmt_out = tmp_results4631.result2;
    int tmp_strlen4548 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str4548 = calloc(tmp_strlen4548, sizeof(char));
    strcpy(tmp_str4548, out);
    strcat(tmp_str4548, stmt_out);
    out = tmp_str4548;
    Peek_results tmp_results4539 = Peek(src);
    tok = tmp_results4539.result1;
    tok_str = tmp_results4539.result2;
  }
  return (TranslateStmts_results){src, out};
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results4384 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results4384.result1;
  tok_str = tmp_results4384.result2;
  Peek_results tmp_results4335 = Peek(src);
  tok = tmp_results4335.result1;
  tok_str = tmp_results4335.result2;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results4275 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results4275.result1;
    tok_str = tmp_results4275.result2;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results4174 = TranslateConstOrVar(src);
  src = tmp_results4174.result1;
  args = tmp_results4174.result2;
  Peek_results tmp_results4133 = Peek(src);
  tok = tmp_results4133.result1;
  tok_str = tmp_results4133.result2;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results4073 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results4073.result1;
    tok_str = tmp_results4073.result2;
    char* arg;
    TranslateConstOrVar_results tmp_results3997 = TranslateConstOrVar(src);
    src = tmp_results3997.result1;
    arg = tmp_results3997.result2;
    int tmp_strlen3934 = strlen(args) + strlen(", ") + 1;
    char* tmp_str3934 = calloc(tmp_strlen3934, sizeof(char));
    strcpy(tmp_str3934, args);
    strcat(tmp_str3934, ", ");
    int tmp_strlen3927 = strlen(tmp_str3934) + strlen(arg) + 1;
    char* tmp_str3927 = calloc(tmp_strlen3927, sizeof(char));
    strcpy(tmp_str3927, tmp_str3934);
    strcat(tmp_str3927, arg);
    args = tmp_str3927;
    Peek_results tmp_results3918 = Peek(src);
    tok = tmp_results3918.result1;
    tok_str = tmp_results3918.result2;
  }
  ConsumeToken_results tmp_results3883 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results3883.result1;
  tok_str = tmp_results3883.result2;
  int tmp_strlen3811 = strlen("(") + strlen(args) + 1;
  char* tmp_str3811 = calloc(tmp_strlen3811, sizeof(char));
  strcpy(tmp_str3811, "(");
  strcat(tmp_str3811, args);
  int tmp_strlen3804 = strlen(tmp_str3811) + strlen(")") + 1;
  char* tmp_str3804 = calloc(tmp_strlen3804, sizeof(char));
  strcpy(tmp_str3804, tmp_str3811);
  strcat(tmp_str3804, ")");
  return (TranslateFuncArgs_results){src, tmp_str3804};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  char* tok_str;
  Peek_results tmp_results3628 = Peek(src);
  tok = tmp_results3628.result1;
  tok_str = tmp_results3628.result2;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results3568 = TranslateType(src);
    src = tmp_results3568.result1;
    typ = tmp_results3568.result2;
    typ_str = tmp_results3568.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results3487 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results3487.result1;
  tok_str = tmp_results3487.result2;
  TranslateType_results tmp_results3438 = TranslateType(src);
  src = tmp_results3438.result1;
  typ = tmp_results3438.result2;
  typ_str = tmp_results3438.result3;
  Peek_results tmp_results3395 = Peek(src);
  tok = tmp_results3395.result1;
  tok_str = tmp_results3395.result2;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results3336 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results3336.result1;
    tok_str = tmp_results3336.result2;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen3195 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str3195 = calloc(tmp_strlen3195, sizeof(char));
  strcpy(tmp_str3195, "typedef struct {\n");
  strcat(tmp_str3195, SINGLE_INDENT);
  int tmp_strlen3184 = strlen(tmp_str3195) + strlen(typ_str) + 1;
  char* tmp_str3184 = calloc(tmp_strlen3184, sizeof(char));
  strcpy(tmp_str3184, tmp_str3195);
  strcat(tmp_str3184, typ_str);
  int tmp_strlen3167 = strlen(tmp_str3184) + strlen(" result1;\n") + 1;
  char* tmp_str3167 = calloc(tmp_strlen3167, sizeof(char));
  strcpy(tmp_str3167, tmp_str3184);
  strcat(tmp_str3167, " result1;\n");
  char* td = tmp_str3167;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results3104 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results3104.result1;
    tok_str = tmp_results3104.result2;
    TranslateType_results tmp_results3052 = TranslateType(src);
    src = tmp_results3052.result1;
    typ = tmp_results3052.result2;
    typ_str = tmp_results3052.result3;
    res_count = (res_count) + (1);
    int tmp_strlen2947 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str2947 = calloc(tmp_strlen2947, sizeof(char));
    strcpy(tmp_str2947, td);
    strcat(tmp_str2947, SINGLE_INDENT);
    int tmp_strlen2936 = strlen(tmp_str2947) + strlen(typ_str) + 1;
    char* tmp_str2936 = calloc(tmp_strlen2936, sizeof(char));
    strcpy(tmp_str2936, tmp_str2947);
    strcat(tmp_str2936, typ_str);
    int tmp_strlen2923 = strlen(tmp_str2936) + strlen(" result") + 1;
    char* tmp_str2923 = calloc(tmp_strlen2923, sizeof(char));
    strcpy(tmp_str2923, tmp_str2936);
    strcat(tmp_str2923, " result");
    int tmp_strlen2904 = strlen(tmp_str2923) + strlen(itoa(res_count)) + 1;
    char* tmp_str2904 = calloc(tmp_strlen2904, sizeof(char));
    strcpy(tmp_str2904, tmp_str2923);
    strcat(tmp_str2904, itoa(res_count));
    int tmp_strlen2895 = strlen(tmp_str2904) + strlen(";\n") + 1;
    char* tmp_str2895 = calloc(tmp_strlen2895, sizeof(char));
    strcpy(tmp_str2895, tmp_str2904);
    strcat(tmp_str2895, ";\n");
    td = tmp_str2895;
    Peek_results tmp_results2886 = Peek(src);
    tok = tmp_results2886.result1;
    tok_str = tmp_results2886.result2;
  }
  ConsumeToken_results tmp_results2851 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results2851.result1;
  tok_str = tmp_results2851.result2;
  int tmp_strlen2787 = strlen(td) + strlen("} ") + 1;
  char* tmp_str2787 = calloc(tmp_strlen2787, sizeof(char));
  strcpy(tmp_str2787, td);
  strcat(tmp_str2787, "} ");
  int tmp_strlen2774 = strlen(tmp_str2787) + strlen(func_name) + 1;
  char* tmp_str2774 = calloc(tmp_strlen2774, sizeof(char));
  strcpy(tmp_str2774, tmp_str2787);
  strcat(tmp_str2774, func_name);
  int tmp_strlen2757 = strlen(tmp_str2774) + strlen("_results;\n") + 1;
  char* tmp_str2757 = calloc(tmp_strlen2757, sizeof(char));
  strcpy(tmp_str2757, tmp_str2774);
  strcat(tmp_str2757, "_results;\n");
  td = tmp_str2757;
  int tmp_strlen2713 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str2713 = calloc(tmp_strlen2713, sizeof(char));
  strcpy(tmp_str2713, func_name);
  strcat(tmp_str2713, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str2713};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* tok_str;
  char* name;
  ConsumeToken_results tmp_results2583 = ConsumeToken(src, TOK_FN);
  src = tmp_results2583.result1;
  tok_str = tmp_results2583.result2;
  ConsumeIdent_results tmp_results2538 = ConsumeIdent(src);
  src = tmp_results2538.result1;
  name = tmp_results2538.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  }
  Peek_results tmp_results2278 = Peek(src);
  tok = tmp_results2278.result1;
  tok_str = tmp_results2278.result2;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results2218 = TranslateFuncArgs(src);
    src = tmp_results2218.result1;
    args = tmp_results2218.result2;
    Peek_results tmp_results2175 = Peek(src);
    tok = tmp_results2175.result1;
    tok_str = tmp_results2175.result2;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results2107 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results2107.result1;
      tok_str = tmp_results2107.result2;
      TranslateFuncResults_results tmp_results2050 = TranslateFuncResults(src, name);
      src = tmp_results2050.result1;
      results_type_def = tmp_results2050.result2;
      results_type_name = tmp_results2050.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results1929 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results1929.result1;
  tok_str = tmp_results1929.result2;
  int tmp_strlen1824 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str1824 = calloc(tmp_strlen1824, sizeof(char));
  strcpy(tmp_str1824, SINGLE_INDENT);
  strcat(tmp_str1824, "");
  TranslateStmts_results tmp_results1880 = TranslateStmts(src, tmp_str1824, name);
  src = tmp_results1880.result1;
  stmts_out = tmp_results1880.result2;
  ConsumeToken_results tmp_results1812 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results1812.result1;
  tok_str = tmp_results1812.result2;
  int tmp_strlen1722 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str1722 = calloc(tmp_strlen1722, sizeof(char));
  strcpy(tmp_str1722, results_type_name);
  strcat(tmp_str1722, " ");
  int tmp_strlen1714 = strlen(tmp_str1722) + strlen(name) + 1;
  char* tmp_str1714 = calloc(tmp_strlen1714, sizeof(char));
  strcpy(tmp_str1714, tmp_str1722);
  strcat(tmp_str1714, name);
  int tmp_strlen1706 = strlen(tmp_str1714) + strlen(args) + 1;
  char* tmp_str1706 = calloc(tmp_strlen1706, sizeof(char));
  strcpy(tmp_str1706, tmp_str1714);
  strcat(tmp_str1706, args);
  char* df = tmp_str1706;
  int tmp_strlen1660 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str1660 = calloc(tmp_strlen1660, sizeof(char));
  strcpy(tmp_str1660, results_type_def);
  strcat(tmp_str1660, df);
  int tmp_strlen1651 = strlen(tmp_str1660) + strlen(";\n") + 1;
  char* tmp_str1651 = calloc(tmp_strlen1651, sizeof(char));
  strcpy(tmp_str1651, tmp_str1660);
  strcat(tmp_str1651, ";\n");
  char* decl = tmp_str1651;
  int tmp_strlen1629 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str1629 = calloc(tmp_strlen1629, sizeof(char));
  strcpy(tmp_str1629, df);
  strcat(tmp_str1629, " {\n");
  df = tmp_str1629;
  int tmp_strlen1604 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str1604 = calloc(tmp_strlen1604, sizeof(char));
  strcpy(tmp_str1604, df);
  strcat(tmp_str1604, stmts_out);
  df = tmp_str1604;
  if ((strcmp(name, "_main") == 0)) {
    int tmp_strlen1544 = strlen(df) + strlen("  return 0;\n") + 1;
    char* tmp_str1544 = calloc(tmp_strlen1544, sizeof(char));
    strcpy(tmp_str1544, df);
    strcat(tmp_str1544, "  return 0;\n");
    df = tmp_str1544;
  }
  int tmp_strlen1515 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str1515 = calloc(tmp_strlen1515, sizeof(char));
  strcpy(tmp_str1515, df);
  strcat(tmp_str1515, "}\n\n");
  df = tmp_str1515;
  return (TranslateFunc_results){src, decl, df};
}

char* TranslateProgram(char* src) {
  char* out = read("clib/lib.c");
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


