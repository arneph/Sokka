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
                  int tmp_strlen27717 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str27717 = calloc(tmp_strlen27717, sizeof(char));
                  strcpy(tmp_str27717, "token has no defined precedence: ");
                  strcat(tmp_str27717, itoa(tok));
                  printf("%s", tmp_str27717);
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
      int tmp_strlen27402 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str27402 = calloc(tmp_strlen27402, sizeof(char));
      strncpy(tmp_str27402, haystack + i, tmp_strlen27402 - 1);
      tmp_str27402[tmp_strlen27402 - 1] = 0;
      if ((strcmp(tmp_str27402, needle) != 0)) {
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
      int tmp_strlen27067 = (strlen(prefix)) - (0) + 1;
      char* tmp_str27067 = calloc(tmp_strlen27067, sizeof(char));
      strncpy(tmp_str27067, text + 0, tmp_strlen27067 - 1);
      tmp_str27067[tmp_strlen27067 - 1] = 0;
      return (strcmp(tmp_str27067, prefix) == 0);
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
    int tmp_strlen26673 = (strlen(text)) - (1) + 1;
    char* tmp_str26673 = calloc(tmp_strlen26673, sizeof(char));
    strncpy(tmp_str26673, text + 1, tmp_strlen26673 - 1);
    tmp_str26673[tmp_strlen26673 - 1] = 0;
    text = tmp_str26673;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen26450 = (strlen(src)) - (2) + 1;
      char* tmp_str26450 = calloc(tmp_strlen26450, sizeof(char));
      strncpy(tmp_str26450, src + 2, tmp_strlen26450 - 1);
      tmp_str26450[tmp_strlen26450 - 1] = 0;
      return (Next_results){tmp_str26450, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen26371 = (strlen(src)) - (2) + 1;
        char* tmp_str26371 = calloc(tmp_strlen26371, sizeof(char));
        strncpy(tmp_str26371, src + 2, tmp_strlen26371 - 1);
        tmp_str26371[tmp_strlen26371 - 1] = 0;
        return (Next_results){tmp_str26371, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen26295 = (strlen(src)) - (2) + 1;
          char* tmp_str26295 = calloc(tmp_strlen26295, sizeof(char));
          strncpy(tmp_str26295, src + 2, tmp_strlen26295 - 1);
          tmp_str26295[tmp_strlen26295 - 1] = 0;
          return (Next_results){tmp_str26295, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen26218 = (strlen(src)) - (2) + 1;
            char* tmp_str26218 = calloc(tmp_strlen26218, sizeof(char));
            strncpy(tmp_str26218, src + 2, tmp_strlen26218 - 1);
            tmp_str26218[tmp_strlen26218 - 1] = 0;
            return (Next_results){tmp_str26218, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen26143 = (strlen(src)) - (2) + 1;
              char* tmp_str26143 = calloc(tmp_strlen26143, sizeof(char));
              strncpy(tmp_str26143, src + 2, tmp_strlen26143 - 1);
              tmp_str26143[tmp_strlen26143 - 1] = 0;
              return (Next_results){tmp_str26143, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen26067 = (strlen(src)) - (2) + 1;
                char* tmp_str26067 = calloc(tmp_strlen26067, sizeof(char));
                strncpy(tmp_str26067, src + 2, tmp_strlen26067 - 1);
                tmp_str26067[tmp_strlen26067 - 1] = 0;
                return (Next_results){tmp_str26067, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen25991 = (strlen(src)) - (2) + 1;
                  char* tmp_str25991 = calloc(tmp_strlen25991, sizeof(char));
                  strncpy(tmp_str25991, src + 2, tmp_strlen25991 - 1);
                  tmp_str25991[tmp_strlen25991 - 1] = 0;
                  return (Next_results){tmp_str25991, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen25915 = (strlen(src)) - (2) + 1;
                    char* tmp_str25915 = calloc(tmp_strlen25915, sizeof(char));
                    strncpy(tmp_str25915, src + 2, tmp_strlen25915 - 1);
                    tmp_str25915[tmp_strlen25915 - 1] = 0;
                    return (Next_results){tmp_str25915, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen25836 = (strlen(src)) - (2) + 1;
                      char* tmp_str25836 = calloc(tmp_strlen25836, sizeof(char));
                      strncpy(tmp_str25836, src + 2, tmp_strlen25836 - 1);
                      tmp_str25836[tmp_strlen25836 - 1] = 0;
                      return (Next_results){tmp_str25836, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen25757 = (strlen(src)) - (3) + 1;
                        char* tmp_str25757 = calloc(tmp_strlen25757, sizeof(char));
                        strncpy(tmp_str25757, src + 3, tmp_strlen25757 - 1);
                        tmp_str25757[tmp_strlen25757 - 1] = 0;
                        return (Next_results){tmp_str25757, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen25677 = (strlen(src)) - (1) + 1;
                          char* tmp_str25677 = calloc(tmp_strlen25677, sizeof(char));
                          strncpy(tmp_str25677, src + 1, tmp_strlen25677 - 1);
                          tmp_str25677[tmp_strlen25677 - 1] = 0;
                          return (Next_results){tmp_str25677, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen25598 = (strlen(src)) - (1) + 1;
                            char* tmp_str25598 = calloc(tmp_strlen25598, sizeof(char));
                            strncpy(tmp_str25598, src + 1, tmp_strlen25598 - 1);
                            tmp_str25598[tmp_strlen25598 - 1] = 0;
                            return (Next_results){tmp_str25598, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen25521 = (strlen(src)) - (1) + 1;
                              char* tmp_str25521 = calloc(tmp_strlen25521, sizeof(char));
                              strncpy(tmp_str25521, src + 1, tmp_strlen25521 - 1);
                              tmp_str25521[tmp_strlen25521 - 1] = 0;
                              return (Next_results){tmp_str25521, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen25444 = (strlen(src)) - (1) + 1;
                                char* tmp_str25444 = calloc(tmp_strlen25444, sizeof(char));
                                strncpy(tmp_str25444, src + 1, tmp_strlen25444 - 1);
                                tmp_str25444[tmp_strlen25444 - 1] = 0;
                                return (Next_results){tmp_str25444, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen25365 = (strlen(src)) - (1) + 1;
                                  char* tmp_str25365 = calloc(tmp_strlen25365, sizeof(char));
                                  strncpy(tmp_str25365, src + 1, tmp_strlen25365 - 1);
                                  tmp_str25365[tmp_strlen25365 - 1] = 0;
                                  return (Next_results){tmp_str25365, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen25286 = (strlen(src)) - (1) + 1;
                                    char* tmp_str25286 = calloc(tmp_strlen25286, sizeof(char));
                                    strncpy(tmp_str25286, src + 1, tmp_strlen25286 - 1);
                                    tmp_str25286[tmp_strlen25286 - 1] = 0;
                                    return (Next_results){tmp_str25286, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen25209 = (strlen(src)) - (1) + 1;
                                      char* tmp_str25209 = calloc(tmp_strlen25209, sizeof(char));
                                      strncpy(tmp_str25209, src + 1, tmp_strlen25209 - 1);
                                      tmp_str25209[tmp_strlen25209 - 1] = 0;
                                      return (Next_results){tmp_str25209, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, "_")) {
                                        int tmp_strlen25132 = (strlen(src)) - (1) + 1;
                                        char* tmp_str25132 = calloc(tmp_strlen25132, sizeof(char));
                                        strncpy(tmp_str25132, src + 1, tmp_strlen25132 - 1);
                                        tmp_str25132[tmp_strlen25132 - 1] = 0;
                                        return (Next_results){tmp_str25132, TOK_UNDERSCORE, "_"};
                                      } else {
                                        if (StartsWith(src, ":")) {
                                          int tmp_strlen25051 = (strlen(src)) - (1) + 1;
                                          char* tmp_str25051 = calloc(tmp_strlen25051, sizeof(char));
                                          strncpy(tmp_str25051, src + 1, tmp_strlen25051 - 1);
                                          tmp_str25051[tmp_strlen25051 - 1] = 0;
                                          return (Next_results){tmp_str25051, TOK_COLON, ":"};
                                        } else {
                                          if (StartsWith(src, ",")) {
                                            int tmp_strlen24975 = (strlen(src)) - (1) + 1;
                                            char* tmp_str24975 = calloc(tmp_strlen24975, sizeof(char));
                                            strncpy(tmp_str24975, src + 1, tmp_strlen24975 - 1);
                                            tmp_str24975[tmp_strlen24975 - 1] = 0;
                                            return (Next_results){tmp_str24975, TOK_COMMA, ","};
                                          } else {
                                            if (StartsWith(src, "=")) {
                                              int tmp_strlen24899 = (strlen(src)) - (1) + 1;
                                              char* tmp_str24899 = calloc(tmp_strlen24899, sizeof(char));
                                              strncpy(tmp_str24899, src + 1, tmp_strlen24899 - 1);
                                              tmp_str24899[tmp_strlen24899 - 1] = 0;
                                              return (Next_results){tmp_str24899, TOK_ASSIGN, "="};
                                            } else {
                                              if (StartsWith(src, "!")) {
                                                int tmp_strlen24822 = (strlen(src)) - (1) + 1;
                                                char* tmp_str24822 = calloc(tmp_strlen24822, sizeof(char));
                                                strncpy(tmp_str24822, src + 1, tmp_strlen24822 - 1);
                                                tmp_str24822[tmp_strlen24822 - 1] = 0;
                                                return (Next_results){tmp_str24822, TOK_BNOT, "!"};
                                              } else {
                                                if (StartsWith(src, "+")) {
                                                  int tmp_strlen24747 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str24747 = calloc(tmp_strlen24747, sizeof(char));
                                                  strncpy(tmp_str24747, src + 1, tmp_strlen24747 - 1);
                                                  tmp_str24747[tmp_strlen24747 - 1] = 0;
                                                  return (Next_results){tmp_str24747, TOK_ADD, "+"};
                                                } else {
                                                  if (StartsWith(src, "-")) {
                                                    int tmp_strlen24673 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str24673 = calloc(tmp_strlen24673, sizeof(char));
                                                    strncpy(tmp_str24673, src + 1, tmp_strlen24673 - 1);
                                                    tmp_str24673[tmp_strlen24673 - 1] = 0;
                                                    return (Next_results){tmp_str24673, TOK_SUB, "-"};
                                                  } else {
                                                    if (StartsWith(src, "*")) {
                                                      int tmp_strlen24599 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str24599 = calloc(tmp_strlen24599, sizeof(char));
                                                      strncpy(tmp_str24599, src + 1, tmp_strlen24599 - 1);
                                                      tmp_str24599[tmp_strlen24599 - 1] = 0;
                                                      return (Next_results){tmp_str24599, TOK_MUL, "*"};
                                                    } else {
                                                      if (StartsWith(src, "/")) {
                                                        int tmp_strlen24525 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str24525 = calloc(tmp_strlen24525, sizeof(char));
                                                        strncpy(tmp_str24525, src + 1, tmp_strlen24525 - 1);
                                                        tmp_str24525[tmp_strlen24525 - 1] = 0;
                                                        return (Next_results){tmp_str24525, TOK_DIV, "/"};
                                                      } else {
                                                        if (StartsWith(src, "%")) {
                                                          int tmp_strlen24451 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str24451 = calloc(tmp_strlen24451, sizeof(char));
                                                          strncpy(tmp_str24451, src + 1, tmp_strlen24451 - 1);
                                                          tmp_str24451[tmp_strlen24451 - 1] = 0;
                                                          return (Next_results){tmp_str24451, TOK_REM, "%"};
                                                        } else {
                                                          if (StartsWith(src, "~")) {
                                                            int tmp_strlen24377 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str24377 = calloc(tmp_strlen24377, sizeof(char));
                                                            strncpy(tmp_str24377, src + 1, tmp_strlen24377 - 1);
                                                            tmp_str24377[tmp_strlen24377 - 1] = 0;
                                                            return (Next_results){tmp_str24377, TOK_INOT, "~"};
                                                          } else {
                                                            if (StartsWith(src, "|")) {
                                                              int tmp_strlen24302 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str24302 = calloc(tmp_strlen24302, sizeof(char));
                                                              strncpy(tmp_str24302, src + 1, tmp_strlen24302 - 1);
                                                              tmp_str24302[tmp_strlen24302 - 1] = 0;
                                                              return (Next_results){tmp_str24302, TOK_IOR, "|"};
                                                            } else {
                                                              if (StartsWith(src, "&")) {
                                                                int tmp_strlen24228 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str24228 = calloc(tmp_strlen24228, sizeof(char));
                                                                strncpy(tmp_str24228, src + 1, tmp_strlen24228 - 1);
                                                                tmp_str24228[tmp_strlen24228 - 1] = 0;
                                                                return (Next_results){tmp_str24228, TOK_IAND, "&"};
                                                              } else {
                                                                if (StartsWith(src, "^")) {
                                                                  int tmp_strlen24153 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str24153 = calloc(tmp_strlen24153, sizeof(char));
                                                                  strncpy(tmp_str24153, src + 1, tmp_strlen24153 - 1);
                                                                  tmp_str24153[tmp_strlen24153 - 1] = 0;
                                                                  return (Next_results){tmp_str24153, TOK_IXOR, "^"};
                                                                } else {
                                                                  if (StartsWith(src, "<")) {
                                                                    int tmp_strlen24078 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str24078 = calloc(tmp_strlen24078, sizeof(char));
                                                                    strncpy(tmp_str24078, src + 1, tmp_strlen24078 - 1);
                                                                    tmp_str24078[tmp_strlen24078 - 1] = 0;
                                                                    return (Next_results){tmp_str24078, TOK_LESS, "<"};
                                                                  } else {
                                                                    if (StartsWith(src, ">")) {
                                                                      int tmp_strlen24003 = (strlen(src)) - (1) + 1;
                                                                      char* tmp_str24003 = calloc(tmp_strlen24003, sizeof(char));
                                                                      strncpy(tmp_str24003, src + 1, tmp_strlen24003 - 1);
                                                                      tmp_str24003[tmp_strlen24003 - 1] = 0;
                                                                      return (Next_results){tmp_str24003, TOK_GREATER, ">"};
                                                                    } else {
                                                                      if (IsAlpha(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        i = (i) - (1);
                                                                        int tmp_strlen23772 = (i) - (0) + 1;
                                                                        char* tmp_str23772 = calloc(tmp_strlen23772, sizeof(char));
                                                                        strncpy(tmp_str23772, src + 0, tmp_strlen23772 - 1);
                                                                        tmp_str23772[tmp_strlen23772 - 1] = 0;
                                                                        char* ts = tmp_str23772;
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
                                                                        int tmp_strlen22980 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str22980 = calloc(tmp_strlen22980, sizeof(char));
                                                                        strncpy(tmp_str22980, src + i, tmp_strlen22980 - 1);
                                                                        tmp_str22980[tmp_strlen22980 - 1] = 0;
                                                                        return (Next_results){tmp_str22980, tt, ts};
                                                                      } else {
                                                                        if (IsNumeric(src[0])) {
                                                                          int i = 1;
                                                                          while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                            i = (i) + (1);
                                                                          }
                                                                          int tmp_strlen22812 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str22812 = calloc(tmp_strlen22812, sizeof(char));
                                                                          strncpy(tmp_str22812, src + i, tmp_strlen22812 - 1);
                                                                          tmp_str22812[tmp_strlen22812 - 1] = 0;
                                                                          int tmp_strlen22791 = (i) - (0) + 1;
                                                                          char* tmp_str22791 = calloc(tmp_strlen22791, sizeof(char));
                                                                          strncpy(tmp_str22791, src + 0, tmp_strlen22791 - 1);
                                                                          tmp_str22791[tmp_strlen22791 - 1] = 0;
                                                                          return (Next_results){tmp_str22812, TOK_INTLIT, tmp_str22791};
                                                                        } else {
                                                                          if (StartsWith(src, "\"")) {
                                                                            int i = 1;
                                                                            while (true) {
                                                                              int tmp_strlen22710 = ((i) + (1)) - (i) + 1;
                                                                              char* tmp_str22710 = calloc(tmp_strlen22710, sizeof(char));
                                                                              strncpy(tmp_str22710, src + i, tmp_strlen22710 - 1);
                                                                              tmp_str22710[tmp_strlen22710 - 1] = 0;
                                                                              if (!((strcmp(tmp_str22710, "\"") != 0))) break;
                                                                              i = (i) + (1);
                                                                              int tmp_strlen22651 = (i) - ((i) - (1)) + 1;
                                                                              char* tmp_str22651 = calloc(tmp_strlen22651, sizeof(char));
                                                                              strncpy(tmp_str22651, src + (i) - (1), tmp_strlen22651 - 1);
                                                                              tmp_str22651[tmp_strlen22651 - 1] = 0;
                                                                              if ((strcmp(tmp_str22651, "\\") == 0)) {
                                                                                i = (i) + (1);
                                                                              }
                                                                            }
                                                                            i = (i) + (1);
                                                                            int tmp_strlen22547 = (strlen(src)) - (i) + 1;
                                                                            char* tmp_str22547 = calloc(tmp_strlen22547, sizeof(char));
                                                                            strncpy(tmp_str22547, src + i, tmp_strlen22547 - 1);
                                                                            tmp_str22547[tmp_strlen22547 - 1] = 0;
                                                                            int tmp_strlen22526 = (i) - (0) + 1;
                                                                            char* tmp_str22526 = calloc(tmp_strlen22526, sizeof(char));
                                                                            strncpy(tmp_str22526, src + 0, tmp_strlen22526 - 1);
                                                                            tmp_str22526[tmp_strlen22526 - 1] = 0;
                                                                            return (Next_results){tmp_str22547, TOK_STRLIT, tmp_str22526};
                                                                          } else {
                                                                            int tmp_strlen22461 = (1) - (0) + 1;
                                                                            char* tmp_str22461 = calloc(tmp_strlen22461, sizeof(char));
                                                                            strncpy(tmp_str22461, src + 0, tmp_strlen22461 - 1);
                                                                            tmp_str22461[tmp_strlen22461 - 1] = 0;
                                                                            int tmp_strlen22457 = strlen("unexpected token start: ") + strlen(tmp_str22461) + 1;
                                                                            char* tmp_str22457 = calloc(tmp_strlen22457, sizeof(char));
                                                                            strcpy(tmp_str22457, "unexpected token start: ");
                                                                            strcat(tmp_str22457, tmp_str22461);
                                                                            printf("%s", tmp_str22457);
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
  Next_results tmp_results22345 = Next(src);
  tok = tmp_results22345.result2;
  tok_str = tmp_results22345.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22161 = Next(src);
  src = tmp_results22161.result1;
  actual_tok = tmp_results22161.result2;
  actual_tok_str = tmp_results22161.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen22027 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str22027 = calloc(tmp_strlen22027, sizeof(char));
    strcpy(tmp_str22027, "expected token: ");
    strcat(tmp_str22027, itoa(expected_tok));
    int tmp_strlen22000 = strlen(tmp_str22027) + strlen(" got: ") + 1;
    char* tmp_str22000 = calloc(tmp_strlen22000, sizeof(char));
    strcpy(tmp_str22000, tmp_str22027);
    strcat(tmp_str22000, " got: ");
    int tmp_strlen21980 = strlen(tmp_str22000) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str21980 = calloc(tmp_strlen21980, sizeof(char));
    strcpy(tmp_str21980, tmp_str22000);
    strcat(tmp_str21980, itoa(actual_tok));
    int tmp_strlen21971 = strlen(tmp_str21980) + strlen(" \"") + 1;
    char* tmp_str21971 = calloc(tmp_strlen21971, sizeof(char));
    strcpy(tmp_str21971, tmp_str21980);
    strcat(tmp_str21971, " \"");
    int tmp_strlen21953 = strlen(tmp_str21971) + strlen(actual_tok_str) + 1;
    char* tmp_str21953 = calloc(tmp_strlen21953, sizeof(char));
    strcpy(tmp_str21953, tmp_str21971);
    strcat(tmp_str21953, actual_tok_str);
    int tmp_strlen21945 = strlen(tmp_str21953) + strlen("\"") + 1;
    char* tmp_str21945 = calloc(tmp_strlen21945, sizeof(char));
    strcpy(tmp_str21945, tmp_str21953);
    strcat(tmp_str21945, "\"");
    printf("%s", tmp_str21945);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results21777 = Next(src);
  src = tmp_results21777.result1;
  actual_tok = tmp_results21777.result2;
  actual_tok_str = tmp_results21777.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen21643 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str21643 = calloc(tmp_strlen21643, sizeof(char));
    strcpy(tmp_str21643, "expected ident, got: ");
    strcat(tmp_str21643, itoa(actual_tok));
    int tmp_strlen21634 = strlen(tmp_str21643) + strlen(" \"") + 1;
    char* tmp_str21634 = calloc(tmp_strlen21634, sizeof(char));
    strcpy(tmp_str21634, tmp_str21643);
    strcat(tmp_str21634, " \"");
    int tmp_strlen21616 = strlen(tmp_str21634) + strlen(actual_tok_str) + 1;
    char* tmp_str21616 = calloc(tmp_strlen21616, sizeof(char));
    strcpy(tmp_str21616, tmp_str21634);
    strcat(tmp_str21616, actual_tok_str);
    int tmp_strlen21608 = strlen(tmp_str21616) + strlen("\"") + 1;
    char* tmp_str21608 = calloc(tmp_strlen21608, sizeof(char));
    strcpy(tmp_str21608, tmp_str21616);
    strcat(tmp_str21608, "\"");
    printf("%s", tmp_str21608);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results21428 = Next(src);
  src = tmp_results21428.result1;
  actual_tok = tmp_results21428.result2;
  actual_tok_str = tmp_results21428.result3;
  if (((actual_tok) != (TOK_UNDERSCORE)) && ((actual_tok) != (TOK_IDENT))) {
    int tmp_strlen21248 = strlen("expected ident or underscore, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str21248 = calloc(tmp_strlen21248, sizeof(char));
    strcpy(tmp_str21248, "expected ident or underscore, got: ");
    strcat(tmp_str21248, itoa(actual_tok));
    int tmp_strlen21239 = strlen(tmp_str21248) + strlen(" \"") + 1;
    char* tmp_str21239 = calloc(tmp_strlen21239, sizeof(char));
    strcpy(tmp_str21239, tmp_str21248);
    strcat(tmp_str21239, " \"");
    int tmp_strlen21221 = strlen(tmp_str21239) + strlen(actual_tok_str) + 1;
    char* tmp_str21221 = calloc(tmp_strlen21221, sizeof(char));
    strcpy(tmp_str21221, tmp_str21239);
    strcat(tmp_str21221, actual_tok_str);
    int tmp_strlen21213 = strlen(tmp_str21221) + strlen("\"") + 1;
    char* tmp_str21213 = calloc(tmp_strlen21213, sizeof(char));
    strcpy(tmp_str21213, tmp_str21221);
    strcat(tmp_str21213, "\"");
    printf("%s", tmp_str21213);
    exit(1);
  }
  return (ConsumeIdentOrUnderscore_results){src, actual_tok_str};
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21053 = Next(src);
  src = tmp_results21053.result1;
  tok = tmp_results21053.result2;
  tok_str = tmp_results21053.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen20756 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str20756 = calloc(tmp_strlen20756, sizeof(char));
        strcpy(tmp_str20756, "expected type, got: ");
        strcat(tmp_str20756, itoa(tok));
        int tmp_strlen20747 = strlen(tmp_str20756) + strlen(" \"") + 1;
        char* tmp_str20747 = calloc(tmp_strlen20747, sizeof(char));
        strcpy(tmp_str20747, tmp_str20756);
        strcat(tmp_str20747, " \"");
        int tmp_strlen20736 = strlen(tmp_str20747) + strlen(tok_str) + 1;
        char* tmp_str20736 = calloc(tmp_strlen20736, sizeof(char));
        strcpy(tmp_str20736, tmp_str20747);
        strcat(tmp_str20736, tok_str);
        int tmp_strlen20728 = strlen(tmp_str20736) + strlen("\"") + 1;
        char* tmp_str20728 = calloc(tmp_strlen20728, sizeof(char));
        strcpy(tmp_str20728, tmp_str20736);
        strcat(tmp_str20728, "\"");
        printf("%s", tmp_str20728);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results20597 = Next(src);
  src = tmp_results20597.result1;
  tok = tmp_results20597.result2;
  tok_str = tmp_results20597.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen20423 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str20423 = calloc(tmp_strlen20423, sizeof(char));
    strcpy(tmp_str20423, "expected false or true, got: ");
    strcat(tmp_str20423, itoa(tok));
    int tmp_strlen20414 = strlen(tmp_str20423) + strlen(" \"") + 1;
    char* tmp_str20414 = calloc(tmp_strlen20414, sizeof(char));
    strcpy(tmp_str20414, tmp_str20423);
    strcat(tmp_str20414, " \"");
    int tmp_strlen20403 = strlen(tmp_str20414) + strlen(tok_str) + 1;
    char* tmp_str20403 = calloc(tmp_strlen20403, sizeof(char));
    strcpy(tmp_str20403, tmp_str20414);
    strcat(tmp_str20403, tok_str);
    int tmp_strlen20395 = strlen(tmp_str20403) + strlen("\"") + 1;
    char* tmp_str20395 = calloc(tmp_strlen20395, sizeof(char));
    strcpy(tmp_str20395, tmp_str20403);
    strcat(tmp_str20395, "\"");
    printf("%s", tmp_str20395);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results20286 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results20286.result1;
  lit = tmp_results20286.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results20137 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results20137.result1;
  lit = tmp_results20137.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  ConsumeToken_results tmp_results19960 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results19960.result1;
  Peek_results tmp_results19917 = Peek(src);
  tok = tmp_results19917.result1;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results19771 = TranslateExprs(src, indent);
    src = tmp_results19771.result1;
    expr_count = tmp_results19771.result2;
    args_setup = tmp_results19771.result3;
    arg_values = tmp_results19771.result4;
  }
  ConsumeToken_results tmp_results19691 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results19691.result1;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen19560 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str19560 = calloc(tmp_strlen19560, sizeof(char));
    strcpy(tmp_str19560, "printf(\"%s\", ");
    strcat(tmp_str19560, arg_values);
    int tmp_strlen19553 = strlen(tmp_str19560) + strlen(")") + 1;
    char* tmp_str19553 = calloc(tmp_strlen19553, sizeof(char));
    strcpy(tmp_str19553, tmp_str19560);
    strcat(tmp_str19553, ")");
    val = tmp_str19553;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen19483 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str19483 = calloc(tmp_strlen19483, sizeof(char));
      strcpy(tmp_str19483, "strlen(");
      strcat(tmp_str19483, arg_values);
      int tmp_strlen19476 = strlen(tmp_str19483) + strlen(")") + 1;
      char* tmp_str19476 = calloc(tmp_strlen19476, sizeof(char));
      strcpy(tmp_str19476, tmp_str19483);
      strcat(tmp_str19476, ")");
      val = tmp_str19476;
    } else {
      int tmp_strlen19435 = strlen(callee) + strlen("(") + 1;
      char* tmp_str19435 = calloc(tmp_strlen19435, sizeof(char));
      strcpy(tmp_str19435, callee);
      strcat(tmp_str19435, "(");
      int tmp_strlen19421 = strlen(tmp_str19435) + strlen(arg_values) + 1;
      char* tmp_str19421 = calloc(tmp_strlen19421, sizeof(char));
      strcpy(tmp_str19421, tmp_str19435);
      strcat(tmp_str19421, arg_values);
      int tmp_strlen19414 = strlen(tmp_str19421) + strlen(")") + 1;
      char* tmp_str19414 = calloc(tmp_strlen19414, sizeof(char));
      strcpy(tmp_str19414, tmp_str19421);
      strcat(tmp_str19414, ")");
      val = tmp_str19414;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  int p = strlen(src);
  ConsumeToken_results tmp_results19227 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results19227.result1;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen19045 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str19045 = calloc(tmp_strlen19045, sizeof(char));
  strcpy(tmp_str19045, "strlen(");
  strcat(tmp_str19045, strvar);
  int tmp_strlen19038 = strlen(tmp_str19045) + strlen(")") + 1;
  char* tmp_str19038 = calloc(tmp_strlen19038, sizeof(char));
  strcpy(tmp_str19038, tmp_str19045);
  strcat(tmp_str19038, ")");
  char* high_expr = tmp_str19038;
  Peek_results tmp_results19033 = Peek(src);
  tok = tmp_results19033.result1;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results18980 = ConsumeToken(src, TOK_COLON);
    src = tmp_results18980.result1;
    TranslateExpr_results tmp_results18934 = TranslateExpr(src, indent);
    src = tmp_results18934.result1;
    high_setup = tmp_results18934.result2;
    high_expr = tmp_results18934.result3;
    ConsumeToken_results tmp_results18870 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results18870.result1;
  } else {
    TranslateExpr_results tmp_results18808 = TranslateExpr(src, indent);
    src = tmp_results18808.result1;
    low_setup = tmp_results18808.result2;
    low_expr = tmp_results18808.result3;
    Peek_results tmp_results18746 = Peek(src);
    tok = tmp_results18746.result1;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results18682 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results18682.result1;
      int tmp_strlen18593 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str18593 = calloc(tmp_strlen18593, sizeof(char));
      strcpy(tmp_str18593, strvar);
      strcat(tmp_str18593, "[");
      int tmp_strlen18581 = strlen(tmp_str18593) + strlen(low_expr) + 1;
      char* tmp_str18581 = calloc(tmp_strlen18581, sizeof(char));
      strcpy(tmp_str18581, tmp_str18593);
      strcat(tmp_str18581, low_expr);
      int tmp_strlen18574 = strlen(tmp_str18581) + strlen("]") + 1;
      char* tmp_str18574 = calloc(tmp_strlen18574, sizeof(char));
      strcpy(tmp_str18574, tmp_str18581);
      strcat(tmp_str18574, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str18574};
    }
    ConsumeToken_results tmp_results18555 = ConsumeToken(src, TOK_COLON);
    src = tmp_results18555.result1;
    Peek_results tmp_results18509 = Peek(src);
    tok = tmp_results18509.result1;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results18445 = TranslateExpr(src, indent);
      src = tmp_results18445.result1;
      high_setup = tmp_results18445.result2;
      high_expr = tmp_results18445.result3;
    }
    ConsumeToken_results tmp_results18371 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results18371.result1;
  }
  int tmp_strlen18278 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str18278 = calloc(tmp_strlen18278, sizeof(char));
  strcpy(tmp_str18278, "tmp_str");
  strcat(tmp_str18278, itoa(p));
  char* tmp_str = tmp_str18278;
  int tmp_strlen18225 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str18225 = calloc(tmp_strlen18225, sizeof(char));
  strcpy(tmp_str18225, "tmp_strlen");
  strcat(tmp_str18225, itoa(p));
  char* tmp_strlen = tmp_str18225;
  int tmp_strlen18177 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str18177 = calloc(tmp_strlen18177, sizeof(char));
  strcpy(tmp_str18177, low_setup);
  strcat(tmp_str18177, high_setup);
  char* setup = tmp_str18177;
  int tmp_strlen18149 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18149 = calloc(tmp_strlen18149, sizeof(char));
  strcpy(tmp_str18149, setup);
  strcat(tmp_str18149, indent);
  int tmp_strlen18139 = strlen(tmp_str18149) + strlen("int ") + 1;
  char* tmp_str18139 = calloc(tmp_strlen18139, sizeof(char));
  strcpy(tmp_str18139, tmp_str18149);
  strcat(tmp_str18139, "int ");
  int tmp_strlen18125 = strlen(tmp_str18139) + strlen(tmp_strlen) + 1;
  char* tmp_str18125 = calloc(tmp_strlen18125, sizeof(char));
  strcpy(tmp_str18125, tmp_str18139);
  strcat(tmp_str18125, tmp_strlen);
  int tmp_strlen18115 = strlen(tmp_str18125) + strlen(" = (") + 1;
  char* tmp_str18115 = calloc(tmp_strlen18115, sizeof(char));
  strcpy(tmp_str18115, tmp_str18125);
  strcat(tmp_str18115, " = (");
  int tmp_strlen18102 = strlen(tmp_str18115) + strlen(high_expr) + 1;
  char* tmp_str18102 = calloc(tmp_strlen18102, sizeof(char));
  strcpy(tmp_str18102, tmp_str18115);
  strcat(tmp_str18102, high_expr);
  int tmp_strlen18091 = strlen(tmp_str18102) + strlen(") - (") + 1;
  char* tmp_str18091 = calloc(tmp_strlen18091, sizeof(char));
  strcpy(tmp_str18091, tmp_str18102);
  strcat(tmp_str18091, ") - (");
  int tmp_strlen18079 = strlen(tmp_str18091) + strlen(low_expr) + 1;
  char* tmp_str18079 = calloc(tmp_strlen18079, sizeof(char));
  strcpy(tmp_str18079, tmp_str18091);
  strcat(tmp_str18079, low_expr);
  int tmp_strlen18065 = strlen(tmp_str18079) + strlen(") + 1;\n") + 1;
  char* tmp_str18065 = calloc(tmp_strlen18065, sizeof(char));
  strcpy(tmp_str18065, tmp_str18079);
  strcat(tmp_str18065, ") + 1;\n");
  setup = tmp_str18065;
  int tmp_strlen18037 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18037 = calloc(tmp_strlen18037, sizeof(char));
  strcpy(tmp_str18037, setup);
  strcat(tmp_str18037, indent);
  int tmp_strlen18025 = strlen(tmp_str18037) + strlen("char* ") + 1;
  char* tmp_str18025 = calloc(tmp_strlen18025, sizeof(char));
  strcpy(tmp_str18025, tmp_str18037);
  strcat(tmp_str18025, "char* ");
  int tmp_strlen18014 = strlen(tmp_str18025) + strlen(tmp_str) + 1;
  char* tmp_str18014 = calloc(tmp_strlen18014, sizeof(char));
  strcpy(tmp_str18014, tmp_str18025);
  strcat(tmp_str18014, tmp_str);
  int tmp_strlen17998 = strlen(tmp_str18014) + strlen(" = calloc(") + 1;
  char* tmp_str17998 = calloc(tmp_strlen17998, sizeof(char));
  strcpy(tmp_str17998, tmp_str18014);
  strcat(tmp_str17998, " = calloc(");
  int tmp_strlen17984 = strlen(tmp_str17998) + strlen(tmp_strlen) + 1;
  char* tmp_str17984 = calloc(tmp_strlen17984, sizeof(char));
  strcpy(tmp_str17984, tmp_str17998);
  strcat(tmp_str17984, tmp_strlen);
  int tmp_strlen17960 = strlen(tmp_str17984) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str17960 = calloc(tmp_strlen17960, sizeof(char));
  strcpy(tmp_str17960, tmp_str17984);
  strcat(tmp_str17960, ", sizeof(char));\n");
  setup = tmp_str17960;
  int tmp_strlen17932 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str17932 = calloc(tmp_strlen17932, sizeof(char));
  strcpy(tmp_str17932, setup);
  strcat(tmp_str17932, indent);
  int tmp_strlen17918 = strlen(tmp_str17932) + strlen("strncpy(") + 1;
  char* tmp_str17918 = calloc(tmp_strlen17918, sizeof(char));
  strcpy(tmp_str17918, tmp_str17932);
  strcat(tmp_str17918, "strncpy(");
  int tmp_strlen17907 = strlen(tmp_str17918) + strlen(tmp_str) + 1;
  char* tmp_str17907 = calloc(tmp_strlen17907, sizeof(char));
  strcpy(tmp_str17907, tmp_str17918);
  strcat(tmp_str17907, tmp_str);
  int tmp_strlen17899 = strlen(tmp_str17907) + strlen(", ") + 1;
  char* tmp_str17899 = calloc(tmp_strlen17899, sizeof(char));
  strcpy(tmp_str17899, tmp_str17907);
  strcat(tmp_str17899, ", ");
  int tmp_strlen17889 = strlen(tmp_str17899) + strlen(strvar) + 1;
  char* tmp_str17889 = calloc(tmp_strlen17889, sizeof(char));
  strcpy(tmp_str17889, tmp_str17899);
  strcat(tmp_str17889, strvar);
  int tmp_strlen17880 = strlen(tmp_str17889) + strlen(" + ") + 1;
  char* tmp_str17880 = calloc(tmp_strlen17880, sizeof(char));
  strcpy(tmp_str17880, tmp_str17889);
  strcat(tmp_str17880, " + ");
  int tmp_strlen17868 = strlen(tmp_str17880) + strlen(low_expr) + 1;
  char* tmp_str17868 = calloc(tmp_strlen17868, sizeof(char));
  strcpy(tmp_str17868, tmp_str17880);
  strcat(tmp_str17868, low_expr);
  int tmp_strlen17860 = strlen(tmp_str17868) + strlen(", ") + 1;
  char* tmp_str17860 = calloc(tmp_strlen17860, sizeof(char));
  strcpy(tmp_str17860, tmp_str17868);
  strcat(tmp_str17860, ", ");
  int tmp_strlen17846 = strlen(tmp_str17860) + strlen(tmp_strlen) + 1;
  char* tmp_str17846 = calloc(tmp_strlen17846, sizeof(char));
  strcpy(tmp_str17846, tmp_str17860);
  strcat(tmp_str17846, tmp_strlen);
  int tmp_strlen17832 = strlen(tmp_str17846) + strlen(" - 1);\n") + 1;
  char* tmp_str17832 = calloc(tmp_strlen17832, sizeof(char));
  strcpy(tmp_str17832, tmp_str17846);
  strcat(tmp_str17832, " - 1);\n");
  setup = tmp_str17832;
  int tmp_strlen17804 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str17804 = calloc(tmp_strlen17804, sizeof(char));
  strcpy(tmp_str17804, setup);
  strcat(tmp_str17804, indent);
  int tmp_strlen17793 = strlen(tmp_str17804) + strlen(tmp_str) + 1;
  char* tmp_str17793 = calloc(tmp_strlen17793, sizeof(char));
  strcpy(tmp_str17793, tmp_str17804);
  strcat(tmp_str17793, tmp_str);
  int tmp_strlen17786 = strlen(tmp_str17793) + strlen("[") + 1;
  char* tmp_str17786 = calloc(tmp_strlen17786, sizeof(char));
  strcpy(tmp_str17786, tmp_str17793);
  strcat(tmp_str17786, "[");
  int tmp_strlen17772 = strlen(tmp_str17786) + strlen(tmp_strlen) + 1;
  char* tmp_str17772 = calloc(tmp_strlen17772, sizeof(char));
  strcpy(tmp_str17772, tmp_str17786);
  strcat(tmp_str17772, tmp_strlen);
  int tmp_strlen17754 = strlen(tmp_str17772) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str17754 = calloc(tmp_strlen17754, sizeof(char));
  strcpy(tmp_str17754, tmp_str17772);
  strcat(tmp_str17754, " - 1] = 0;\n");
  setup = tmp_str17754;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results17595 = Peek(src);
  tok = tmp_results17595.result1;
  tok_str = tmp_results17595.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results17485 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results17485.result1;
    TranslateExpr_results tmp_results17438 = TranslateExpr(src, indent);
    src = tmp_results17438.result1;
    setup = tmp_results17438.result2;
    val = tmp_results17438.result3;
    ConsumeToken_results tmp_results17385 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results17385.result1;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results17231 = TranslateBoolLiteral(src);
      src = tmp_results17231.result1;
      lit = tmp_results17231.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results17100 = TranslateIntLiteral(src);
        src = tmp_results17100.result1;
        lit = tmp_results17100.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results16970 = TranslateStringLiteral(src);
          src = tmp_results16970.result1;
          lit = tmp_results16970.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results16836 = ConsumeIdent(src);
            src = tmp_results16836.result1;
            ident = tmp_results16836.result2;
            Peek_results tmp_results16797 = Peek(src);
            tok = tmp_results16797.result1;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results16676 = TranslateCall(src, indent, ident);
              src = tmp_results16676.result1;
              setup = tmp_results16676.result2;
              expr = tmp_results16676.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results16476 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results16476.result1;
                setup = tmp_results16476.result2;
                expr = tmp_results16476.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen16256 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str16256 = calloc(tmp_strlen16256, sizeof(char));
            strcpy(tmp_str16256, "unexpected expr, got: ");
            strcat(tmp_str16256, itoa(tok));
            int tmp_strlen16247 = strlen(tmp_str16256) + strlen(" \"") + 1;
            char* tmp_str16247 = calloc(tmp_strlen16247, sizeof(char));
            strcpy(tmp_str16247, tmp_str16256);
            strcat(tmp_str16247, " \"");
            int tmp_strlen16236 = strlen(tmp_str16247) + strlen(tok_str) + 1;
            char* tmp_str16236 = calloc(tmp_strlen16236, sizeof(char));
            strcpy(tmp_str16236, tmp_str16247);
            strcat(tmp_str16236, tok_str);
            int tmp_strlen16228 = strlen(tmp_str16236) + strlen("\"") + 1;
            char* tmp_str16228 = calloc(tmp_strlen16228, sizeof(char));
            strcpy(tmp_str16228, tmp_str16236);
            strcat(tmp_str16228, "\"");
            printf("%s", tmp_str16228);
            exit(1);
          }
        }
      }
    }
  }
}

TranslateUnaryExpr_results TranslateUnaryExpr(char* src, char* indent) {
  int tok;
  Peek_results tmp_results16099 = Peek(src);
  tok = tmp_results16099.result1;
  if (IsUnaryOp(tok)) {
    char* tok_str;
    ConsumeToken_results tmp_results16020 = ConsumeToken(src, tok);
    src = tmp_results16020.result1;
    tok_str = tmp_results16020.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results15924 = TranslateExpr(src, indent);
    src = tmp_results15924.result1;
    setup = tmp_results15924.result2;
    val = tmp_results15924.result3;
    int tmp_strlen15851 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str15851 = calloc(tmp_strlen15851, sizeof(char));
    strcpy(tmp_str15851, tok_str);
    strcat(tmp_str15851, "(");
    int tmp_strlen15844 = strlen(tmp_str15851) + strlen(val) + 1;
    char* tmp_str15844 = calloc(tmp_strlen15844, sizeof(char));
    strcpy(tmp_str15844, tmp_str15851);
    strcat(tmp_str15844, val);
    int tmp_strlen15837 = strlen(tmp_str15844) + strlen(")") + 1;
    char* tmp_str15837 = calloc(tmp_strlen15837, sizeof(char));
    strcpy(tmp_str15837, tmp_str15844);
    strcat(tmp_str15837, ")");
    val = tmp_str15837;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results15733 = TranslateOperand(src, indent);
    src = tmp_results15733.result1;
    setup = tmp_results15733.result2;
    expr = tmp_results15733.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results15490 = TranslateUnaryExpr(src, indent);
  src = tmp_results15490.result1;
  setup = tmp_results15490.result2;
  val = tmp_results15490.result3;
  int op;
  char* op_str;
  Peek_results tmp_results15397 = Peek(src);
  op = tmp_results15397.result1;
  op_str = tmp_results15397.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results15310 = ConsumeToken(src, op);
    src = tmp_results15310.result1;
    op_str = tmp_results15310.result2;
    int tok;
    Peek_results tmp_results15245 = Peek(src);
    tok = tmp_results15245.result1;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results15181 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results15181.result1;
      Peek_results tmp_results15129 = Peek(src);
      tok = tmp_results15129.result1;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results15038 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results15038.result1;
    setup_b = tmp_results15038.result2;
    val_b = tmp_results15038.result3;
    int tmp_strlen14927 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str14927 = calloc(tmp_strlen14927, sizeof(char));
    strcpy(tmp_str14927, setup);
    strcat(tmp_str14927, setup_b);
    setup = tmp_str14927;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen14835 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str14835 = calloc(tmp_strlen14835, sizeof(char));
      strcpy(tmp_str14835, "tmp_str");
      strcat(tmp_str14835, itoa(strlen(src)));
      char* tmp_str = tmp_str14835;
      int tmp_strlen14767 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str14767 = calloc(tmp_strlen14767, sizeof(char));
      strcpy(tmp_str14767, "tmp_strlen");
      strcat(tmp_str14767, itoa(strlen(src)));
      char* tmp_strlen = tmp_str14767;
      int tmp_strlen14731 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14731 = calloc(tmp_strlen14731, sizeof(char));
      strcpy(tmp_str14731, setup);
      strcat(tmp_str14731, indent);
      int tmp_strlen14721 = strlen(tmp_str14731) + strlen("int ") + 1;
      char* tmp_str14721 = calloc(tmp_strlen14721, sizeof(char));
      strcpy(tmp_str14721, tmp_str14731);
      strcat(tmp_str14721, "int ");
      int tmp_strlen14707 = strlen(tmp_str14721) + strlen(tmp_strlen) + 1;
      char* tmp_str14707 = calloc(tmp_strlen14707, sizeof(char));
      strcpy(tmp_str14707, tmp_str14721);
      strcat(tmp_str14707, tmp_strlen);
      int tmp_strlen14691 = strlen(tmp_str14707) + strlen(" = strlen(") + 1;
      char* tmp_str14691 = calloc(tmp_strlen14691, sizeof(char));
      strcpy(tmp_str14691, tmp_str14707);
      strcat(tmp_str14691, " = strlen(");
      int tmp_strlen14684 = strlen(tmp_str14691) + strlen(val) + 1;
      char* tmp_str14684 = calloc(tmp_strlen14684, sizeof(char));
      strcpy(tmp_str14684, tmp_str14691);
      strcat(tmp_str14684, val);
      int tmp_strlen14667 = strlen(tmp_str14684) + strlen(") + strlen(") + 1;
      char* tmp_str14667 = calloc(tmp_strlen14667, sizeof(char));
      strcpy(tmp_str14667, tmp_str14684);
      strcat(tmp_str14667, ") + strlen(");
      int tmp_strlen14658 = strlen(tmp_str14667) + strlen(val_b) + 1;
      char* tmp_str14658 = calloc(tmp_strlen14658, sizeof(char));
      strcpy(tmp_str14658, tmp_str14667);
      strcat(tmp_str14658, val_b);
      int tmp_strlen14644 = strlen(tmp_str14658) + strlen(") + 1;\n") + 1;
      char* tmp_str14644 = calloc(tmp_strlen14644, sizeof(char));
      strcpy(tmp_str14644, tmp_str14658);
      strcat(tmp_str14644, ") + 1;\n");
      setup = tmp_str14644;
      int tmp_strlen14608 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14608 = calloc(tmp_strlen14608, sizeof(char));
      strcpy(tmp_str14608, setup);
      strcat(tmp_str14608, indent);
      int tmp_strlen14596 = strlen(tmp_str14608) + strlen("char* ") + 1;
      char* tmp_str14596 = calloc(tmp_strlen14596, sizeof(char));
      strcpy(tmp_str14596, tmp_str14608);
      strcat(tmp_str14596, "char* ");
      int tmp_strlen14585 = strlen(tmp_str14596) + strlen(tmp_str) + 1;
      char* tmp_str14585 = calloc(tmp_strlen14585, sizeof(char));
      strcpy(tmp_str14585, tmp_str14596);
      strcat(tmp_str14585, tmp_str);
      int tmp_strlen14569 = strlen(tmp_str14585) + strlen(" = calloc(") + 1;
      char* tmp_str14569 = calloc(tmp_strlen14569, sizeof(char));
      strcpy(tmp_str14569, tmp_str14585);
      strcat(tmp_str14569, " = calloc(");
      int tmp_strlen14555 = strlen(tmp_str14569) + strlen(tmp_strlen) + 1;
      char* tmp_str14555 = calloc(tmp_strlen14555, sizeof(char));
      strcpy(tmp_str14555, tmp_str14569);
      strcat(tmp_str14555, tmp_strlen);
      int tmp_strlen14531 = strlen(tmp_str14555) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str14531 = calloc(tmp_strlen14531, sizeof(char));
      strcpy(tmp_str14531, tmp_str14555);
      strcat(tmp_str14531, ", sizeof(char));\n");
      setup = tmp_str14531;
      int tmp_strlen14495 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14495 = calloc(tmp_strlen14495, sizeof(char));
      strcpy(tmp_str14495, setup);
      strcat(tmp_str14495, indent);
      int tmp_strlen14482 = strlen(tmp_str14495) + strlen("strcpy(") + 1;
      char* tmp_str14482 = calloc(tmp_strlen14482, sizeof(char));
      strcpy(tmp_str14482, tmp_str14495);
      strcat(tmp_str14482, "strcpy(");
      int tmp_strlen14471 = strlen(tmp_str14482) + strlen(tmp_str) + 1;
      char* tmp_str14471 = calloc(tmp_strlen14471, sizeof(char));
      strcpy(tmp_str14471, tmp_str14482);
      strcat(tmp_str14471, tmp_str);
      int tmp_strlen14463 = strlen(tmp_str14471) + strlen(", ") + 1;
      char* tmp_str14463 = calloc(tmp_strlen14463, sizeof(char));
      strcpy(tmp_str14463, tmp_str14471);
      strcat(tmp_str14463, ", ");
      int tmp_strlen14456 = strlen(tmp_str14463) + strlen(val) + 1;
      char* tmp_str14456 = calloc(tmp_strlen14456, sizeof(char));
      strcpy(tmp_str14456, tmp_str14463);
      strcat(tmp_str14456, val);
      int tmp_strlen14446 = strlen(tmp_str14456) + strlen(");\n") + 1;
      char* tmp_str14446 = calloc(tmp_strlen14446, sizeof(char));
      strcpy(tmp_str14446, tmp_str14456);
      strcat(tmp_str14446, ");\n");
      setup = tmp_str14446;
      int tmp_strlen14410 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str14410 = calloc(tmp_strlen14410, sizeof(char));
      strcpy(tmp_str14410, setup);
      strcat(tmp_str14410, indent);
      int tmp_strlen14397 = strlen(tmp_str14410) + strlen("strcat(") + 1;
      char* tmp_str14397 = calloc(tmp_strlen14397, sizeof(char));
      strcpy(tmp_str14397, tmp_str14410);
      strcat(tmp_str14397, "strcat(");
      int tmp_strlen14386 = strlen(tmp_str14397) + strlen(tmp_str) + 1;
      char* tmp_str14386 = calloc(tmp_strlen14386, sizeof(char));
      strcpy(tmp_str14386, tmp_str14397);
      strcat(tmp_str14386, tmp_str);
      int tmp_strlen14378 = strlen(tmp_str14386) + strlen(", ") + 1;
      char* tmp_str14378 = calloc(tmp_strlen14378, sizeof(char));
      strcpy(tmp_str14378, tmp_str14386);
      strcat(tmp_str14378, ", ");
      int tmp_strlen14369 = strlen(tmp_str14378) + strlen(val_b) + 1;
      char* tmp_str14369 = calloc(tmp_strlen14369, sizeof(char));
      strcpy(tmp_str14369, tmp_str14378);
      strcat(tmp_str14369, val_b);
      int tmp_strlen14359 = strlen(tmp_str14369) + strlen(");\n") + 1;
      char* tmp_str14359 = calloc(tmp_strlen14359, sizeof(char));
      strcpy(tmp_str14359, tmp_str14369);
      strcat(tmp_str14359, ");\n");
      setup = tmp_str14359;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen14261 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str14261 = calloc(tmp_strlen14261, sizeof(char));
        strcpy(tmp_str14261, "(strcmp(");
        strcat(tmp_str14261, val);
        int tmp_strlen14253 = strlen(tmp_str14261) + strlen(", ") + 1;
        char* tmp_str14253 = calloc(tmp_strlen14253, sizeof(char));
        strcpy(tmp_str14253, tmp_str14261);
        strcat(tmp_str14253, ", ");
        int tmp_strlen14244 = strlen(tmp_str14253) + strlen(val_b) + 1;
        char* tmp_str14244 = calloc(tmp_strlen14244, sizeof(char));
        strcpy(tmp_str14244, tmp_str14253);
        strcat(tmp_str14244, val_b);
        int tmp_strlen14231 = strlen(tmp_str14244) + strlen(") == 0)") + 1;
        char* tmp_str14231 = calloc(tmp_strlen14231, sizeof(char));
        strcpy(tmp_str14231, tmp_str14244);
        strcat(tmp_str14231, ") == 0)");
        val = tmp_str14231;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen14158 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str14158 = calloc(tmp_strlen14158, sizeof(char));
          strcpy(tmp_str14158, "(strcmp(");
          strcat(tmp_str14158, val);
          int tmp_strlen14150 = strlen(tmp_str14158) + strlen(", ") + 1;
          char* tmp_str14150 = calloc(tmp_strlen14150, sizeof(char));
          strcpy(tmp_str14150, tmp_str14158);
          strcat(tmp_str14150, ", ");
          int tmp_strlen14141 = strlen(tmp_str14150) + strlen(val_b) + 1;
          char* tmp_str14141 = calloc(tmp_strlen14141, sizeof(char));
          strcpy(tmp_str14141, tmp_str14150);
          strcat(tmp_str14141, val_b);
          int tmp_strlen14128 = strlen(tmp_str14141) + strlen(") != 0)") + 1;
          char* tmp_str14128 = calloc(tmp_strlen14128, sizeof(char));
          strcpy(tmp_str14128, tmp_str14141);
          strcat(tmp_str14128, ") != 0)");
          val = tmp_str14128;
        } else {
          int tmp_strlen14082 = strlen("(") + strlen(val) + 1;
          char* tmp_str14082 = calloc(tmp_strlen14082, sizeof(char));
          strcpy(tmp_str14082, "(");
          strcat(tmp_str14082, val);
          int tmp_strlen14074 = strlen(tmp_str14082) + strlen(") ") + 1;
          char* tmp_str14074 = calloc(tmp_strlen14074, sizeof(char));
          strcpy(tmp_str14074, tmp_str14082);
          strcat(tmp_str14074, ") ");
          int tmp_strlen14064 = strlen(tmp_str14074) + strlen(op_str) + 1;
          char* tmp_str14064 = calloc(tmp_strlen14064, sizeof(char));
          strcpy(tmp_str14064, tmp_str14074);
          strcat(tmp_str14064, op_str);
          int tmp_strlen14056 = strlen(tmp_str14064) + strlen(" (") + 1;
          char* tmp_str14056 = calloc(tmp_strlen14056, sizeof(char));
          strcpy(tmp_str14056, tmp_str14064);
          strcat(tmp_str14056, " (");
          int tmp_strlen14047 = strlen(tmp_str14056) + strlen(val_b) + 1;
          char* tmp_str14047 = calloc(tmp_strlen14047, sizeof(char));
          strcpy(tmp_str14047, tmp_str14056);
          strcat(tmp_str14047, val_b);
          int tmp_strlen14040 = strlen(tmp_str14047) + strlen(")") + 1;
          char* tmp_str14040 = calloc(tmp_strlen14040, sizeof(char));
          strcpy(tmp_str14040, tmp_str14047);
          strcat(tmp_str14040, ")");
          val = tmp_str14040;
        }
      }
    }
    Peek_results tmp_results14021 = Peek(src);
    op = tmp_results14021.result1;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results13844 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results13844.result1;
  setup = tmp_results13844.result2;
  expr = tmp_results13844.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results13610 = TranslateExpr(src, indent);
  src = tmp_results13610.result1;
  expr_setup = tmp_results13610.result2;
  expr_value = tmp_results13610.result3;
  int tok;
  Peek_results tmp_results13532 = Peek(src);
  tok = tmp_results13532.result1;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results13367 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results13367.result1;
    TranslateExpr_results tmp_results13321 = TranslateExpr(src, indent);
    src = tmp_results13321.result1;
    expr_setup = tmp_results13321.result2;
    expr_value = tmp_results13321.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen13179 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str13179 = calloc(tmp_strlen13179, sizeof(char));
    strcpy(tmp_str13179, exprs_setup);
    strcat(tmp_str13179, expr_setup);
    exprs_setup = tmp_str13179;
    int tmp_strlen13137 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str13137 = calloc(tmp_strlen13137, sizeof(char));
    strcpy(tmp_str13137, exprs_value);
    strcat(tmp_str13137, ", ");
    int tmp_strlen13123 = strlen(tmp_str13137) + strlen(expr_value) + 1;
    char* tmp_str13123 = calloc(tmp_strlen13123, sizeof(char));
    strcpy(tmp_str13123, tmp_str13137);
    strcat(tmp_str13123, expr_value);
    exprs_value = tmp_str13123;
    Peek_results tmp_results13114 = Peek(src);
    tok = tmp_results13114.result1;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results12949 = ConsumeIdent(src);
  src = tmp_results12949.result1;
  name = tmp_results12949.result2;
  ConsumeToken_results tmp_results12915 = ConsumeToken(src, TOK_COLON);
  src = tmp_results12915.result1;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results12832 = TranslateType(src);
  src = tmp_results12832.result1;
  typ = tmp_results12832.result2;
  typ_str = tmp_results12832.result3;
  int tmp_strlen12757 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str12757 = calloc(tmp_strlen12757, sizeof(char));
  strcpy(tmp_str12757, typ_str);
  strcat(tmp_str12757, " ");
  int tmp_strlen12749 = strlen(tmp_str12757) + strlen(name) + 1;
  char* tmp_str12749 = calloc(tmp_strlen12749, sizeof(char));
  strcpy(tmp_str12749, tmp_str12757);
  strcat(tmp_str12749, name);
  char* out = tmp_str12749;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  ConsumeToken_results tmp_results12648 = ConsumeToken(src, TOK_LET);
  src = tmp_results12648.result1;
  char* out;
  TranslateConstOrVar_results tmp_results12588 = TranslateConstOrVar(src);
  src = tmp_results12588.result1;
  out = tmp_results12588.result2;
  int tmp_strlen12527 = strlen("const ") + strlen(out) + 1;
  char* tmp_str12527 = calloc(tmp_strlen12527, sizeof(char));
  strcpy(tmp_str12527, "const ");
  strcat(tmp_str12527, out);
  out = tmp_str12527;
  ConsumeToken_results tmp_results12522 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results12522.result1;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results12437 = TranslateExpr(src, indent);
  src = tmp_results12437.result1;
  setup = tmp_results12437.result2;
  val = tmp_results12437.result3;
  ConsumeToken_results tmp_results12388 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results12388.result1;
  int tmp_strlen12326 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str12326 = calloc(tmp_strlen12326, sizeof(char));
  strcpy(tmp_str12326, out);
  strcat(tmp_str12326, " = ");
  int tmp_strlen12319 = strlen(tmp_str12326) + strlen(val) + 1;
  char* tmp_str12319 = calloc(tmp_strlen12319, sizeof(char));
  strcpy(tmp_str12319, tmp_str12326);
  strcat(tmp_str12319, val);
  int tmp_strlen12310 = strlen(tmp_str12319) + strlen(";\n") + 1;
  char* tmp_str12310 = calloc(tmp_strlen12310, sizeof(char));
  strcpy(tmp_str12310, tmp_str12319);
  strcat(tmp_str12310, ";\n");
  out = tmp_str12310;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results12185 = TranslateConstDecl(src, indent);
  src = tmp_results12185.result1;
  out = tmp_results12185.result2;
  int tmp_strlen12113 = strlen(indent) + strlen(out) + 1;
  char* tmp_str12113 = calloc(tmp_strlen12113, sizeof(char));
  strcpy(tmp_str12113, indent);
  strcat(tmp_str12113, out);
  return (TranslateConstDeclStmt_results){src, tmp_str12113};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  ConsumeToken_results tmp_results12013 = ConsumeToken(src, TOK_VAR);
  src = tmp_results12013.result1;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results11906 = TranslateConstOrVar(src);
  src = tmp_results11906.result1;
  out = tmp_results11906.result2;
  Peek_results tmp_results11866 = Peek(src);
  tok = tmp_results11866.result1;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results11812 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results11812.result1;
    TranslateExpr_results tmp_results11765 = TranslateExpr(src, indent);
    src = tmp_results11765.result1;
    setup = tmp_results11765.result2;
    val = tmp_results11765.result3;
    ConsumeToken_results tmp_results11712 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results11712.result1;
    int tmp_strlen11646 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str11646 = calloc(tmp_strlen11646, sizeof(char));
    strcpy(tmp_str11646, out);
    strcat(tmp_str11646, " = ");
    int tmp_strlen11639 = strlen(tmp_str11646) + strlen(val) + 1;
    char* tmp_str11639 = calloc(tmp_strlen11639, sizeof(char));
    strcpy(tmp_str11639, tmp_str11646);
    strcat(tmp_str11639, val);
    out = tmp_str11639;
  }
  int tmp_strlen11607 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str11607 = calloc(tmp_strlen11607, sizeof(char));
  strcpy(tmp_str11607, setup);
  strcat(tmp_str11607, indent);
  int tmp_strlen11600 = strlen(tmp_str11607) + strlen(out) + 1;
  char* tmp_str11600 = calloc(tmp_strlen11600, sizeof(char));
  strcpy(tmp_str11600, tmp_str11607);
  strcat(tmp_str11600, out);
  int tmp_strlen11591 = strlen(tmp_str11600) + strlen(";\n") + 1;
  char* tmp_str11591 = calloc(tmp_strlen11591, sizeof(char));
  strcpy(tmp_str11591, tmp_str11600);
  strcat(tmp_str11591, ";\n");
  out = tmp_str11591;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen11436 = (x) - (0) + 1;
  char* tmp_str11436 = calloc(tmp_strlen11436, sizeof(char));
  strncpy(tmp_str11436, src + 0, tmp_strlen11436 - 1);
  tmp_str11436[tmp_strlen11436 - 1] = 0;
  char* lhs = tmp_str11436;
  int tmp_strlen11406 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str11406 = calloc(tmp_strlen11406, sizeof(char));
  strncpy(tmp_str11406, src + (x) + (1), tmp_strlen11406 - 1);
  tmp_str11406[tmp_strlen11406 - 1] = 0;
  char* rhs = tmp_str11406;
  char* lhs_ident;
  ConsumeIdentOrUnderscore_results tmp_results11369 = ConsumeIdentOrUnderscore(lhs);
  lhs = tmp_results11369.result1;
  lhs_ident = tmp_results11369.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results11241 = TranslateExpr(rhs, indent);
  rhs = tmp_results11241.result1;
  setup = tmp_results11241.result2;
  rhs_expr = tmp_results11241.result3;
  int lhs_tok;
  int rhs_tok;
  Peek_results tmp_results11145 = Peek(lhs);
  lhs_tok = tmp_results11145.result1;
  Peek_results tmp_results11118 = Peek(rhs);
  rhs_tok = tmp_results11118.result1;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results11003 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results11003.result1;
    func_name = tmp_results11003.result2;
    int tmp_strlen10895 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str10895 = calloc(tmp_strlen10895, sizeof(char));
    strcpy(tmp_str10895, "tmp_results");
    strcat(tmp_str10895, itoa(strlen(src)));
    char* tmp_results = tmp_str10895;
    char* out = setup;
    int tmp_strlen10835 = strlen(out) + strlen(indent) + 1;
    char* tmp_str10835 = calloc(tmp_strlen10835, sizeof(char));
    strcpy(tmp_str10835, out);
    strcat(tmp_str10835, indent);
    int tmp_strlen10822 = strlen(tmp_str10835) + strlen(func_name) + 1;
    char* tmp_str10822 = calloc(tmp_strlen10822, sizeof(char));
    strcpy(tmp_str10822, tmp_str10835);
    strcat(tmp_str10822, func_name);
    int tmp_strlen10807 = strlen(tmp_str10822) + strlen("_results ") + 1;
    char* tmp_str10807 = calloc(tmp_strlen10807, sizeof(char));
    strcpy(tmp_str10807, tmp_str10822);
    strcat(tmp_str10807, "_results ");
    int tmp_strlen10792 = strlen(tmp_str10807) + strlen(tmp_results) + 1;
    char* tmp_str10792 = calloc(tmp_strlen10792, sizeof(char));
    strcpy(tmp_str10792, tmp_str10807);
    strcat(tmp_str10792, tmp_results);
    int tmp_strlen10783 = strlen(tmp_str10792) + strlen(" = ") + 1;
    char* tmp_str10783 = calloc(tmp_strlen10783, sizeof(char));
    strcpy(tmp_str10783, tmp_str10792);
    strcat(tmp_str10783, " = ");
    int tmp_strlen10771 = strlen(tmp_str10783) + strlen(rhs_expr) + 1;
    char* tmp_str10771 = calloc(tmp_strlen10771, sizeof(char));
    strcpy(tmp_str10771, tmp_str10783);
    strcat(tmp_str10771, rhs_expr);
    int tmp_strlen10762 = strlen(tmp_str10771) + strlen(";\n") + 1;
    char* tmp_str10762 = calloc(tmp_strlen10762, sizeof(char));
    strcpy(tmp_str10762, tmp_str10771);
    strcat(tmp_str10762, ";\n");
    out = tmp_str10762;
    if ((strcmp(lhs_ident, "_") != 0)) {
      int tmp_strlen10699 = strlen(out) + strlen(indent) + 1;
      char* tmp_str10699 = calloc(tmp_strlen10699, sizeof(char));
      strcpy(tmp_str10699, out);
      strcat(tmp_str10699, indent);
      int tmp_strlen10686 = strlen(tmp_str10699) + strlen(lhs_ident) + 1;
      char* tmp_str10686 = calloc(tmp_strlen10686, sizeof(char));
      strcpy(tmp_str10686, tmp_str10699);
      strcat(tmp_str10686, lhs_ident);
      int tmp_strlen10677 = strlen(tmp_str10686) + strlen(" = ") + 1;
      char* tmp_str10677 = calloc(tmp_strlen10677, sizeof(char));
      strcpy(tmp_str10677, tmp_str10686);
      strcat(tmp_str10677, " = ");
      int tmp_strlen10662 = strlen(tmp_str10677) + strlen(tmp_results) + 1;
      char* tmp_str10662 = calloc(tmp_strlen10662, sizeof(char));
      strcpy(tmp_str10662, tmp_str10677);
      strcat(tmp_str10662, tmp_results);
      int tmp_strlen10645 = strlen(tmp_str10662) + strlen(".result1;\n") + 1;
      char* tmp_str10645 = calloc(tmp_strlen10645, sizeof(char));
      strcpy(tmp_str10645, tmp_str10662);
      strcat(tmp_str10645, ".result1;\n");
      out = tmp_str10645;
    }
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results10509 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results10509.result1;
      ConsumeIdentOrUnderscore_results tmp_results10459 = ConsumeIdentOrUnderscore(lhs);
      lhs = tmp_results10459.result1;
      lhs_ident = tmp_results10459.result2;
      if ((strcmp(lhs_ident, "_") != 0)) {
        int tmp_strlen10342 = strlen(out) + strlen(indent) + 1;
        char* tmp_str10342 = calloc(tmp_strlen10342, sizeof(char));
        strcpy(tmp_str10342, out);
        strcat(tmp_str10342, indent);
        int tmp_strlen10329 = strlen(tmp_str10342) + strlen(lhs_ident) + 1;
        char* tmp_str10329 = calloc(tmp_strlen10329, sizeof(char));
        strcpy(tmp_str10329, tmp_str10342);
        strcat(tmp_str10329, lhs_ident);
        int tmp_strlen10320 = strlen(tmp_str10329) + strlen(" = ") + 1;
        char* tmp_str10320 = calloc(tmp_strlen10320, sizeof(char));
        strcpy(tmp_str10320, tmp_str10329);
        strcat(tmp_str10320, " = ");
        int tmp_strlen10305 = strlen(tmp_str10320) + strlen(tmp_results) + 1;
        char* tmp_str10305 = calloc(tmp_strlen10305, sizeof(char));
        strcpy(tmp_str10305, tmp_str10320);
        strcat(tmp_str10305, tmp_results);
        int tmp_strlen10292 = strlen(tmp_str10305) + strlen(".result") + 1;
        char* tmp_str10292 = calloc(tmp_strlen10292, sizeof(char));
        strcpy(tmp_str10292, tmp_str10305);
        strcat(tmp_str10292, ".result");
        int tmp_strlen10270 = strlen(tmp_str10292) + strlen(itoa(result_count)) + 1;
        char* tmp_str10270 = calloc(tmp_strlen10270, sizeof(char));
        strcpy(tmp_str10270, tmp_str10292);
        strcat(tmp_str10270, itoa(result_count));
        int tmp_strlen10261 = strlen(tmp_str10270) + strlen(";\n") + 1;
        char* tmp_str10261 = calloc(tmp_strlen10261, sizeof(char));
        strcpy(tmp_str10261, tmp_str10270);
        strcat(tmp_str10261, ";\n");
        out = tmp_str10261;
      }
      Peek_results tmp_results10234 = Peek(lhs);
      lhs_tok = tmp_results10234.result1;
    }
    ConsumeToken_results tmp_results10193 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results10193.result1;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen10074 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str10074 = calloc(tmp_strlen10074, sizeof(char));
  strcpy(tmp_str10074, indent);
  strcat(tmp_str10074, lhs_ident);
  int tmp_strlen10065 = strlen(tmp_str10074) + strlen(" = ") + 1;
  char* tmp_str10065 = calloc(tmp_strlen10065, sizeof(char));
  strcpy(tmp_str10065, tmp_str10074);
  strcat(tmp_str10065, " = ");
  int tmp_strlen10053 = strlen(tmp_str10065) + strlen(rhs_expr) + 1;
  char* tmp_str10053 = calloc(tmp_strlen10053, sizeof(char));
  strcpy(tmp_str10053, tmp_str10065);
  strcat(tmp_str10053, rhs_expr);
  int tmp_strlen10044 = strlen(tmp_str10053) + strlen(";\n") + 1;
  char* tmp_str10044 = calloc(tmp_strlen10044, sizeof(char));
  strcpy(tmp_str10044, tmp_str10053);
  strcat(tmp_str10044, ";\n");
  char* assignments = tmp_str10044;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results10004 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results10004.result1;
    ConsumeToken_results tmp_results9958 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results9958.result1;
    ConsumeIdent_results tmp_results9912 = ConsumeIdent(lhs);
    lhs = tmp_results9912.result1;
    lhs_ident = tmp_results9912.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results9834 = TranslateExpr(rhs, indent);
    rhs = tmp_results9834.result1;
    rhs_expr_setup = tmp_results9834.result2;
    rhs_expr = tmp_results9834.result3;
    int tmp_strlen9736 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str9736 = calloc(tmp_strlen9736, sizeof(char));
    strcpy(tmp_str9736, setup);
    strcat(tmp_str9736, rhs_expr_setup);
    setup = tmp_str9736;
    int tmp_strlen9692 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str9692 = calloc(tmp_strlen9692, sizeof(char));
    strcpy(tmp_str9692, assignments);
    strcat(tmp_str9692, indent);
    int tmp_strlen9679 = strlen(tmp_str9692) + strlen(lhs_ident) + 1;
    char* tmp_str9679 = calloc(tmp_strlen9679, sizeof(char));
    strcpy(tmp_str9679, tmp_str9692);
    strcat(tmp_str9679, lhs_ident);
    int tmp_strlen9670 = strlen(tmp_str9679) + strlen(" = ") + 1;
    char* tmp_str9670 = calloc(tmp_strlen9670, sizeof(char));
    strcpy(tmp_str9670, tmp_str9679);
    strcat(tmp_str9670, " = ");
    int tmp_strlen9658 = strlen(tmp_str9670) + strlen(rhs_expr) + 1;
    char* tmp_str9658 = calloc(tmp_strlen9658, sizeof(char));
    strcpy(tmp_str9658, tmp_str9670);
    strcat(tmp_str9658, rhs_expr);
    int tmp_strlen9649 = strlen(tmp_str9658) + strlen(";\n") + 1;
    char* tmp_str9649 = calloc(tmp_strlen9649, sizeof(char));
    strcpy(tmp_str9649, tmp_str9658);
    strcat(tmp_str9649, ";\n");
    assignments = tmp_str9649;
    Peek_results tmp_results9640 = Peek(lhs);
    lhs_tok = tmp_results9640.result1;
  }
  ConsumeToken_results tmp_results9607 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results9607.result1;
  int tmp_strlen9531 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str9531 = calloc(tmp_strlen9531, sizeof(char));
  strcpy(tmp_str9531, setup);
  strcat(tmp_str9531, assignments);
  return (TranslateAssignStmt_results){src, tmp_str9531};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results9434 = ConsumeToken(src, TOK_IF);
  src = tmp_results9434.result1;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results9347 = TranslateExpr(src, indent);
  src = tmp_results9347.result1;
  cond_setup = tmp_results9347.result2;
  cond = tmp_results9347.result3;
  ConsumeToken_results tmp_results9292 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results9292.result1;
  char* out = cond_setup;
  int tmp_strlen9197 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9197 = calloc(tmp_strlen9197, sizeof(char));
  strcpy(tmp_str9197, out);
  strcat(tmp_str9197, indent);
  int tmp_strlen9187 = strlen(tmp_str9197) + strlen("if (") + 1;
  char* tmp_str9187 = calloc(tmp_strlen9187, sizeof(char));
  strcpy(tmp_str9187, tmp_str9197);
  strcat(tmp_str9187, "if (");
  int tmp_strlen9179 = strlen(tmp_str9187) + strlen(cond) + 1;
  char* tmp_str9179 = calloc(tmp_strlen9179, sizeof(char));
  strcpy(tmp_str9179, tmp_str9187);
  strcat(tmp_str9179, cond);
  int tmp_strlen9168 = strlen(tmp_str9179) + strlen(") {\n") + 1;
  char* tmp_str9168 = calloc(tmp_strlen9168, sizeof(char));
  strcpy(tmp_str9168, tmp_str9179);
  strcat(tmp_str9168, ") {\n");
  out = tmp_str9168;
  char* body;
  int tmp_strlen9087 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str9087 = calloc(tmp_strlen9087, sizeof(char));
  strcpy(tmp_str9087, indent);
  strcat(tmp_str9087, SINGLE_INDENT);
  TranslateStmts_results tmp_results9142 = TranslateStmts(src, tmp_str9087, func_name);
  src = tmp_results9142.result1;
  body = tmp_results9142.result2;
  ConsumeToken_results tmp_results9070 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results9070.result1;
  int tmp_strlen9010 = strlen(out) + strlen(body) + 1;
  char* tmp_str9010 = calloc(tmp_strlen9010, sizeof(char));
  strcpy(tmp_str9010, out);
  strcat(tmp_str9010, body);
  out = tmp_str9010;
  int tmp_strlen8986 = strlen(out) + strlen(indent) + 1;
  char* tmp_str8986 = calloc(tmp_strlen8986, sizeof(char));
  strcpy(tmp_str8986, out);
  strcat(tmp_str8986, indent);
  int tmp_strlen8979 = strlen(tmp_str8986) + strlen("}") + 1;
  char* tmp_str8979 = calloc(tmp_strlen8979, sizeof(char));
  strcpy(tmp_str8979, tmp_str8986);
  strcat(tmp_str8979, "}");
  out = tmp_str8979;
  int tok;
  Peek_results tmp_results8957 = Peek(src);
  tok = tmp_results8957.result1;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen8882 = strlen(out) + strlen("\n") + 1;
    char* tmp_str8882 = calloc(tmp_strlen8882, sizeof(char));
    strcpy(tmp_str8882, out);
    strcat(tmp_str8882, "\n");
    return (TranslateIfStmt_results){src, tmp_str8882};
  }
  ConsumeToken_results tmp_results8871 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results8871.result1;
  Peek_results tmp_results8830 = Peek(src);
  tok = tmp_results8830.result1;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen8695 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8695 = calloc(tmp_strlen8695, sizeof(char));
    strcpy(tmp_str8695, indent);
    strcat(tmp_str8695, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results8755 = TranslateIfStmt(src, tmp_str8695, func_name);
    src = tmp_results8755.result1;
    else_out = tmp_results8755.result2;
    int tmp_strlen8650 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str8650 = calloc(tmp_strlen8650, sizeof(char));
    strcpy(tmp_str8650, out);
    strcat(tmp_str8650, " else {\n");
    out = tmp_str8650;
    int tmp_strlen8620 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str8620 = calloc(tmp_strlen8620, sizeof(char));
    strcpy(tmp_str8620, out);
    strcat(tmp_str8620, else_out);
    out = tmp_str8620;
    int tmp_strlen8592 = strlen(out) + strlen(indent) + 1;
    char* tmp_str8592 = calloc(tmp_strlen8592, sizeof(char));
    strcpy(tmp_str8592, out);
    strcat(tmp_str8592, indent);
    int tmp_strlen8583 = strlen(tmp_str8592) + strlen("}\n") + 1;
    char* tmp_str8583 = calloc(tmp_strlen8583, sizeof(char));
    strcpy(tmp_str8583, tmp_str8592);
    strcat(tmp_str8583, "}\n");
    out = tmp_str8583;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results8548 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8548.result1;
  int tmp_strlen8446 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str8446 = calloc(tmp_strlen8446, sizeof(char));
  strcpy(tmp_str8446, indent);
  strcat(tmp_str8446, SINGLE_INDENT);
  TranslateStmts_results tmp_results8505 = TranslateStmts(src, tmp_str8446, func_name);
  src = tmp_results8505.result1;
  else_out = tmp_results8505.result2;
  ConsumeToken_results tmp_results8429 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results8429.result1;
  int tmp_strlen8362 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str8362 = calloc(tmp_strlen8362, sizeof(char));
  strcpy(tmp_str8362, out);
  strcat(tmp_str8362, " else {\n");
  out = tmp_str8362;
  int tmp_strlen8336 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str8336 = calloc(tmp_strlen8336, sizeof(char));
  strcpy(tmp_str8336, out);
  strcat(tmp_str8336, else_out);
  out = tmp_str8336;
  int tmp_strlen8312 = strlen(out) + strlen(indent) + 1;
  char* tmp_str8312 = calloc(tmp_strlen8312, sizeof(char));
  strcpy(tmp_str8312, out);
  strcat(tmp_str8312, indent);
  int tmp_strlen8303 = strlen(tmp_str8312) + strlen("}\n") + 1;
  char* tmp_str8303 = calloc(tmp_strlen8303, sizeof(char));
  strcpy(tmp_str8303, tmp_str8312);
  strcat(tmp_str8303, "}\n");
  out = tmp_str8303;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  ConsumeToken_results tmp_results8168 = ConsumeToken(src, TOK_FOR);
  src = tmp_results8168.result1;
  Peek_results tmp_results8128 = Peek(src);
  tok = tmp_results8128.result1;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen7946 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str7946 = calloc(tmp_strlen7946, sizeof(char));
    strcpy(tmp_str7946, indent);
    strcat(tmp_str7946, SINGLE_INDENT);
    TranslateExpr_results tmp_results8012 = TranslateExpr(src, tmp_str7946);
    src = tmp_results8012.result1;
    cond_setup = tmp_results8012.result2;
    cond = tmp_results8012.result3;
  }
  ConsumeToken_results tmp_results7934 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results7934.result1;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen7816 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str7816 = calloc(tmp_strlen7816, sizeof(char));
    strcpy(tmp_str7816, indent);
    strcat(tmp_str7816, "while (");
    int tmp_strlen7808 = strlen(tmp_str7816) + strlen(cond) + 1;
    char* tmp_str7808 = calloc(tmp_strlen7808, sizeof(char));
    strcpy(tmp_str7808, tmp_str7816);
    strcat(tmp_str7808, cond);
    int tmp_strlen7797 = strlen(tmp_str7808) + strlen(") {\n") + 1;
    char* tmp_str7797 = calloc(tmp_strlen7797, sizeof(char));
    strcpy(tmp_str7797, tmp_str7808);
    strcat(tmp_str7797, ") {\n");
    out = tmp_str7797;
  } else {
    int tmp_strlen7741 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str7741 = calloc(tmp_strlen7741, sizeof(char));
    strcpy(tmp_str7741, indent);
    strcat(tmp_str7741, "while (true) {\n");
    out = tmp_str7741;
    int tmp_strlen7709 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str7709 = calloc(tmp_strlen7709, sizeof(char));
    strcpy(tmp_str7709, out);
    strcat(tmp_str7709, cond_setup);
    out = tmp_str7709;
    int tmp_strlen7681 = strlen(out) + strlen(indent) + 1;
    char* tmp_str7681 = calloc(tmp_strlen7681, sizeof(char));
    strcpy(tmp_str7681, out);
    strcat(tmp_str7681, indent);
    int tmp_strlen7664 = strlen(tmp_str7681) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str7664 = calloc(tmp_strlen7664, sizeof(char));
    strcpy(tmp_str7664, tmp_str7681);
    strcat(tmp_str7664, SINGLE_INDENT);
    int tmp_strlen7652 = strlen(tmp_str7664) + strlen("if (!(") + 1;
    char* tmp_str7652 = calloc(tmp_strlen7652, sizeof(char));
    strcpy(tmp_str7652, tmp_str7664);
    strcat(tmp_str7652, "if (!(");
    int tmp_strlen7644 = strlen(tmp_str7652) + strlen(cond) + 1;
    char* tmp_str7644 = calloc(tmp_strlen7644, sizeof(char));
    strcpy(tmp_str7644, tmp_str7652);
    strcat(tmp_str7644, cond);
    int tmp_strlen7627 = strlen(tmp_str7644) + strlen(")) break;\n") + 1;
    char* tmp_str7627 = calloc(tmp_strlen7627, sizeof(char));
    strcpy(tmp_str7627, tmp_str7644);
    strcat(tmp_str7627, ")) break;\n");
    out = tmp_str7627;
  }
  char* body;
  int tmp_strlen7540 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str7540 = calloc(tmp_strlen7540, sizeof(char));
  strcpy(tmp_str7540, indent);
  strcat(tmp_str7540, SINGLE_INDENT);
  TranslateStmts_results tmp_results7595 = TranslateStmts(src, tmp_str7540, func_name);
  src = tmp_results7595.result1;
  body = tmp_results7595.result2;
  ConsumeToken_results tmp_results7523 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results7523.result1;
  int tmp_strlen7463 = strlen(out) + strlen(body) + 1;
  char* tmp_str7463 = calloc(tmp_strlen7463, sizeof(char));
  strcpy(tmp_str7463, out);
  strcat(tmp_str7463, body);
  out = tmp_str7463;
  int tmp_strlen7439 = strlen(out) + strlen(indent) + 1;
  char* tmp_str7439 = calloc(tmp_strlen7439, sizeof(char));
  strcpy(tmp_str7439, out);
  strcat(tmp_str7439, indent);
  int tmp_strlen7430 = strlen(tmp_str7439) + strlen("}\n") + 1;
  char* tmp_str7430 = calloc(tmp_strlen7430, sizeof(char));
  strcpy(tmp_str7430, tmp_str7439);
  strcat(tmp_str7430, "}\n");
  out = tmp_str7430;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results7326 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results7326.result1;
  int tmp_strlen7248 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str7248 = calloc(tmp_strlen7248, sizeof(char));
  strcpy(tmp_str7248, indent);
  strcat(tmp_str7248, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str7248};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  ConsumeToken_results tmp_results7167 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results7167.result1;
  int tmp_strlen7095 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str7095 = calloc(tmp_strlen7095, sizeof(char));
  strcpy(tmp_str7095, indent);
  strcat(tmp_str7095, "break;");
  return (TranslateBreakStmt_results){src, tmp_str7095};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  ConsumeToken_results tmp_results6994 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results6994.result1;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results6871 = TranslateExprs(src, indent);
  src = tmp_results6871.result1;
  expr_count = tmp_results6871.result2;
  exprs_setup = tmp_results6871.result3;
  exprs_value = tmp_results6871.result4;
  ConsumeToken_results tmp_results6795 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results6795.result1;
  int tmp_strlen6712 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str6712 = calloc(tmp_strlen6712, sizeof(char));
  strcpy(tmp_str6712, exprs_setup);
  strcat(tmp_str6712, indent);
  int tmp_strlen6699 = strlen(tmp_str6712) + strlen("return ") + 1;
  char* tmp_str6699 = calloc(tmp_strlen6699, sizeof(char));
  strcpy(tmp_str6699, tmp_str6712);
  strcat(tmp_str6699, "return ");
  char* out = tmp_str6699;
  if ((expr_count) > (1)) {
    int tmp_strlen6650 = strlen(out) + strlen("(") + 1;
    char* tmp_str6650 = calloc(tmp_strlen6650, sizeof(char));
    strcpy(tmp_str6650, out);
    strcat(tmp_str6650, "(");
    int tmp_strlen6637 = strlen(tmp_str6650) + strlen(func_name) + 1;
    char* tmp_str6637 = calloc(tmp_strlen6637, sizeof(char));
    strcpy(tmp_str6637, tmp_str6650);
    strcat(tmp_str6637, func_name);
    int tmp_strlen6621 = strlen(tmp_str6637) + strlen("_results){") + 1;
    char* tmp_str6621 = calloc(tmp_strlen6621, sizeof(char));
    strcpy(tmp_str6621, tmp_str6637);
    strcat(tmp_str6621, "_results){");
    out = tmp_str6621;
  }
  int tmp_strlen6586 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str6586 = calloc(tmp_strlen6586, sizeof(char));
  strcpy(tmp_str6586, out);
  strcat(tmp_str6586, exprs_value);
  out = tmp_str6586;
  if ((expr_count) > (1)) {
    int tmp_strlen6536 = strlen(out) + strlen("}") + 1;
    char* tmp_str6536 = calloc(tmp_strlen6536, sizeof(char));
    strcpy(tmp_str6536, out);
    strcat(tmp_str6536, "}");
    out = tmp_str6536;
  }
  int tmp_strlen6507 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str6507 = calloc(tmp_strlen6507, sizeof(char));
  strcpy(tmp_str6507, out);
  strcat(tmp_str6507, ";\n");
  out = tmp_str6507;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6351 = Peek(src);
  tok = tmp_results6351.result1;
  tok_str = tmp_results6351.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results6274 = TranslateConstDeclStmt(src, indent);
    src = tmp_results6274.result1;
    out = tmp_results6274.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results6164 = TranslateVarDeclStmt(src, indent);
      src = tmp_results6164.result1;
      out = tmp_results6164.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results6057 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results6057.result1;
        out = tmp_results6057.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results5943 = TranslateForStmt(src, indent, func_name);
          src = tmp_results5943.result1;
          out = tmp_results5943.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results5823 = TranslateContinueStmt(src, indent);
            src = tmp_results5823.result1;
            out = tmp_results5823.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results5712 = TranslateBreakStmt(src, indent);
              src = tmp_results5712.result1;
              out = tmp_results5712.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results5603 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results5603.result1;
                out = tmp_results5603.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if (((tok) == (TOK_IDENT)) || ((tok) == (TOK_UNDERSCORE))) {
                  char* first_ident;
                  ConsumeIdentOrUnderscore_results tmp_results5426 = ConsumeIdentOrUnderscore(src);
                  src = tmp_results5426.result1;
                  first_ident = tmp_results5426.result2;
                  Peek_results tmp_results5369 = Peek(src);
                  tok = tmp_results5369.result1;
                  int tmp_strlen5318 = strlen(first_ident) + strlen(src) + 1;
                  char* tmp_str5318 = calloc(tmp_strlen5318, sizeof(char));
                  strcpy(tmp_str5318, first_ident);
                  strcat(tmp_str5318, src);
                  src = tmp_str5318;
                  if (((tok) == (TOK_COMMA)) || ((tok) == (TOK_ASSIGN))) {
                    TranslateAssignStmt_results tmp_results5254 = TranslateAssignStmt(src, indent);
                    src = tmp_results5254.result1;
                    out = tmp_results5254.result2;
                    return (TranslateStmt_results){src, out};
                  } else {
                    char* setup;
                    char* val;
                    TranslateExpr_results tmp_results5095 = TranslateExpr(src, indent);
                    src = tmp_results5095.result1;
                    setup = tmp_results5095.result2;
                    val = tmp_results5095.result3;
                    ConsumeToken_results tmp_results5038 = ConsumeToken(src, TOK_NEWLINE);
                    src = tmp_results5038.result1;
                    int tmp_strlen4965 = strlen(setup) + strlen(indent) + 1;
                    char* tmp_str4965 = calloc(tmp_strlen4965, sizeof(char));
                    strcpy(tmp_str4965, setup);
                    strcat(tmp_str4965, indent);
                    int tmp_strlen4958 = strlen(tmp_str4965) + strlen(val) + 1;
                    char* tmp_str4958 = calloc(tmp_strlen4958, sizeof(char));
                    strcpy(tmp_str4958, tmp_str4965);
                    strcat(tmp_str4958, val);
                    int tmp_strlen4949 = strlen(tmp_str4958) + strlen(";\n") + 1;
                    char* tmp_str4949 = calloc(tmp_strlen4949, sizeof(char));
                    strcpy(tmp_str4949, tmp_str4958);
                    strcat(tmp_str4949, ";\n");
                    out = tmp_str4949;
                    return (TranslateStmt_results){src, out};
                  }
                } else {
                  int tmp_strlen4840 = strlen("unexpected stmt token, got: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str4840 = calloc(tmp_strlen4840, sizeof(char));
                  strcpy(tmp_str4840, "unexpected stmt token, got: ");
                  strcat(tmp_str4840, itoa(tok));
                  int tmp_strlen4831 = strlen(tmp_str4840) + strlen(" \"") + 1;
                  char* tmp_str4831 = calloc(tmp_strlen4831, sizeof(char));
                  strcpy(tmp_str4831, tmp_str4840);
                  strcat(tmp_str4831, " \"");
                  int tmp_strlen4820 = strlen(tmp_str4831) + strlen(tok_str) + 1;
                  char* tmp_str4820 = calloc(tmp_strlen4820, sizeof(char));
                  strcpy(tmp_str4820, tmp_str4831);
                  strcat(tmp_str4820, tok_str);
                  int tmp_strlen4812 = strlen(tmp_str4820) + strlen("\"") + 1;
                  char* tmp_str4812 = calloc(tmp_strlen4812, sizeof(char));
                  strcpy(tmp_str4812, tmp_str4820);
                  strcat(tmp_str4812, "\"");
                  printf("%s", tmp_str4812);
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
  Peek_results tmp_results4676 = Peek(src);
  tok = tmp_results4676.result1;
  char* out = "";
  while ((tok) != (TOK_RCURLY)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results4560 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results4560.result1;
      Peek_results tmp_results4508 = Peek(src);
      tok = tmp_results4508.result1;
      continue;
    }
    char* stmt_out;
    TranslateStmt_results tmp_results4421 = TranslateStmt(src, indent, func_name);
    src = tmp_results4421.result1;
    stmt_out = tmp_results4421.result2;
    int tmp_strlen4338 = strlen(out) + strlen(stmt_out) + 1;
    char* tmp_str4338 = calloc(tmp_strlen4338, sizeof(char));
    strcpy(tmp_str4338, out);
    strcat(tmp_str4338, stmt_out);
    out = tmp_str4338;
    Peek_results tmp_results4329 = Peek(src);
    tok = tmp_results4329.result1;
  }
  return (TranslateStmts_results){src, out};
}

TranslateFuncArgs_results TranslateFuncArgs(char* src) {
  int tok;
  ConsumeToken_results tmp_results4204 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results4204.result1;
  Peek_results tmp_results4161 = Peek(src);
  tok = tmp_results4161.result1;
  if ((tok) == (TOK_RPAREN)) {
    ConsumeToken_results tmp_results4107 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results4107.result1;
    return (TranslateFuncArgs_results){src, "()"};
  }
  char* args;
  TranslateConstOrVar_results tmp_results4012 = TranslateConstOrVar(src);
  src = tmp_results4012.result1;
  args = tmp_results4012.result2;
  Peek_results tmp_results3971 = Peek(src);
  tok = tmp_results3971.result1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results3917 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results3917.result1;
    char* arg;
    TranslateConstOrVar_results tmp_results3847 = TranslateConstOrVar(src);
    src = tmp_results3847.result1;
    arg = tmp_results3847.result2;
    int tmp_strlen3784 = strlen(args) + strlen(", ") + 1;
    char* tmp_str3784 = calloc(tmp_strlen3784, sizeof(char));
    strcpy(tmp_str3784, args);
    strcat(tmp_str3784, ", ");
    int tmp_strlen3777 = strlen(tmp_str3784) + strlen(arg) + 1;
    char* tmp_str3777 = calloc(tmp_strlen3777, sizeof(char));
    strcpy(tmp_str3777, tmp_str3784);
    strcat(tmp_str3777, arg);
    args = tmp_str3777;
    Peek_results tmp_results3768 = Peek(src);
    tok = tmp_results3768.result1;
  }
  ConsumeToken_results tmp_results3739 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results3739.result1;
  int tmp_strlen3673 = strlen("(") + strlen(args) + 1;
  char* tmp_str3673 = calloc(tmp_strlen3673, sizeof(char));
  strcpy(tmp_str3673, "(");
  strcat(tmp_str3673, args);
  int tmp_strlen3666 = strlen(tmp_str3673) + strlen(")") + 1;
  char* tmp_str3666 = calloc(tmp_strlen3666, sizeof(char));
  strcpy(tmp_str3666, tmp_str3673);
  strcat(tmp_str3666, ")");
  return (TranslateFuncArgs_results){src, tmp_str3666};
}

TranslateFuncResults_results TranslateFuncResults(char* src, char* func_name) {
  int typ;
  char* typ_str;
  int tok;
  Peek_results tmp_results3514 = Peek(src);
  tok = tmp_results3514.result1;
  if ((tok) != (TOK_LPAREN)) {
    TranslateType_results tmp_results3460 = TranslateType(src);
    src = tmp_results3460.result1;
    typ = tmp_results3460.result2;
    typ_str = tmp_results3460.result3;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  ConsumeToken_results tmp_results3379 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results3379.result1;
  TranslateType_results tmp_results3336 = TranslateType(src);
  src = tmp_results3336.result1;
  typ = tmp_results3336.result2;
  typ_str = tmp_results3336.result3;
  Peek_results tmp_results3293 = Peek(src);
  tok = tmp_results3293.result1;
  if ((tok) != (TOK_COMMA)) {
    ConsumeToken_results tmp_results3240 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results3240.result1;
    return (TranslateFuncResults_results){src, "", typ_str};
  }
  int tmp_strlen3105 = strlen("typedef struct {\n") + strlen(SINGLE_INDENT) + 1;
  char* tmp_str3105 = calloc(tmp_strlen3105, sizeof(char));
  strcpy(tmp_str3105, "typedef struct {\n");
  strcat(tmp_str3105, SINGLE_INDENT);
  int tmp_strlen3094 = strlen(tmp_str3105) + strlen(typ_str) + 1;
  char* tmp_str3094 = calloc(tmp_strlen3094, sizeof(char));
  strcpy(tmp_str3094, tmp_str3105);
  strcat(tmp_str3094, typ_str);
  int tmp_strlen3077 = strlen(tmp_str3094) + strlen(" result1;\n") + 1;
  char* tmp_str3077 = calloc(tmp_strlen3077, sizeof(char));
  strcpy(tmp_str3077, tmp_str3094);
  strcat(tmp_str3077, " result1;\n");
  char* td = tmp_str3077;
  int res_count = 1;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results3014 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results3014.result1;
    TranslateType_results tmp_results2968 = TranslateType(src);
    src = tmp_results2968.result1;
    typ = tmp_results2968.result2;
    typ_str = tmp_results2968.result3;
    res_count = (res_count) + (1);
    int tmp_strlen2863 = strlen(td) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str2863 = calloc(tmp_strlen2863, sizeof(char));
    strcpy(tmp_str2863, td);
    strcat(tmp_str2863, SINGLE_INDENT);
    int tmp_strlen2852 = strlen(tmp_str2863) + strlen(typ_str) + 1;
    char* tmp_str2852 = calloc(tmp_strlen2852, sizeof(char));
    strcpy(tmp_str2852, tmp_str2863);
    strcat(tmp_str2852, typ_str);
    int tmp_strlen2839 = strlen(tmp_str2852) + strlen(" result") + 1;
    char* tmp_str2839 = calloc(tmp_strlen2839, sizeof(char));
    strcpy(tmp_str2839, tmp_str2852);
    strcat(tmp_str2839, " result");
    int tmp_strlen2820 = strlen(tmp_str2839) + strlen(itoa(res_count)) + 1;
    char* tmp_str2820 = calloc(tmp_strlen2820, sizeof(char));
    strcpy(tmp_str2820, tmp_str2839);
    strcat(tmp_str2820, itoa(res_count));
    int tmp_strlen2811 = strlen(tmp_str2820) + strlen(";\n") + 1;
    char* tmp_str2811 = calloc(tmp_strlen2811, sizeof(char));
    strcpy(tmp_str2811, tmp_str2820);
    strcat(tmp_str2811, ";\n");
    td = tmp_str2811;
    Peek_results tmp_results2802 = Peek(src);
    tok = tmp_results2802.result1;
  }
  ConsumeToken_results tmp_results2773 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results2773.result1;
  int tmp_strlen2715 = strlen(td) + strlen("} ") + 1;
  char* tmp_str2715 = calloc(tmp_strlen2715, sizeof(char));
  strcpy(tmp_str2715, td);
  strcat(tmp_str2715, "} ");
  int tmp_strlen2702 = strlen(tmp_str2715) + strlen(func_name) + 1;
  char* tmp_str2702 = calloc(tmp_strlen2702, sizeof(char));
  strcpy(tmp_str2702, tmp_str2715);
  strcat(tmp_str2702, func_name);
  int tmp_strlen2685 = strlen(tmp_str2702) + strlen("_results;\n") + 1;
  char* tmp_str2685 = calloc(tmp_strlen2685, sizeof(char));
  strcpy(tmp_str2685, tmp_str2702);
  strcat(tmp_str2685, "_results;\n");
  td = tmp_str2685;
  int tmp_strlen2641 = strlen(func_name) + strlen("_results") + 1;
  char* tmp_str2641 = calloc(tmp_strlen2641, sizeof(char));
  strcpy(tmp_str2641, func_name);
  strcat(tmp_str2641, "_results");
  return (TranslateFuncResults_results){src, td, tmp_str2641};
}

TranslateFunc_results TranslateFunc(char* src) {
  int tok;
  char* name;
  ConsumeToken_results tmp_results2535 = ConsumeToken(src, TOK_FN);
  src = tmp_results2535.result1;
  ConsumeIdent_results tmp_results2496 = ConsumeIdent(src);
  src = tmp_results2496.result1;
  name = tmp_results2496.result2;
  char* args = "()";
  char* results_type_def = "";
  char* results_type_name = "void";
  if ((strcmp(name, "main") == 0)) {
    name = "_main";
    args = "(char* args)";
    results_type_name = "int";
  }
  Peek_results tmp_results2236 = Peek(src);
  tok = tmp_results2236.result1;
  if ((tok) == (TOK_LPAREN)) {
    TranslateFuncArgs_results tmp_results2182 = TranslateFuncArgs(src);
    src = tmp_results2182.result1;
    args = tmp_results2182.result2;
    Peek_results tmp_results2139 = Peek(src);
    tok = tmp_results2139.result1;
    if ((tok) == (TOK_RARROW)) {
      ConsumeToken_results tmp_results2077 = ConsumeToken(src, TOK_RARROW);
      src = tmp_results2077.result1;
      TranslateFuncResults_results tmp_results2026 = TranslateFuncResults(src, name);
      src = tmp_results2026.result1;
      results_type_def = tmp_results2026.result2;
      results_type_name = tmp_results2026.result3;
    }
  }
  char* stmts_out;
  ConsumeToken_results tmp_results1905 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results1905.result1;
  int tmp_strlen1806 = strlen(SINGLE_INDENT) + strlen("") + 1;
  char* tmp_str1806 = calloc(tmp_strlen1806, sizeof(char));
  strcpy(tmp_str1806, SINGLE_INDENT);
  strcat(tmp_str1806, "");
  TranslateStmts_results tmp_results1862 = TranslateStmts(src, tmp_str1806, name);
  src = tmp_results1862.result1;
  stmts_out = tmp_results1862.result2;
  ConsumeToken_results tmp_results1794 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results1794.result1;
  int tmp_strlen1710 = strlen(results_type_name) + strlen(" ") + 1;
  char* tmp_str1710 = calloc(tmp_strlen1710, sizeof(char));
  strcpy(tmp_str1710, results_type_name);
  strcat(tmp_str1710, " ");
  int tmp_strlen1702 = strlen(tmp_str1710) + strlen(name) + 1;
  char* tmp_str1702 = calloc(tmp_strlen1702, sizeof(char));
  strcpy(tmp_str1702, tmp_str1710);
  strcat(tmp_str1702, name);
  int tmp_strlen1694 = strlen(tmp_str1702) + strlen(args) + 1;
  char* tmp_str1694 = calloc(tmp_strlen1694, sizeof(char));
  strcpy(tmp_str1694, tmp_str1702);
  strcat(tmp_str1694, args);
  char* df = tmp_str1694;
  int tmp_strlen1648 = strlen(results_type_def) + strlen(df) + 1;
  char* tmp_str1648 = calloc(tmp_strlen1648, sizeof(char));
  strcpy(tmp_str1648, results_type_def);
  strcat(tmp_str1648, df);
  int tmp_strlen1639 = strlen(tmp_str1648) + strlen(";\n") + 1;
  char* tmp_str1639 = calloc(tmp_strlen1639, sizeof(char));
  strcpy(tmp_str1639, tmp_str1648);
  strcat(tmp_str1639, ";\n");
  char* decl = tmp_str1639;
  int tmp_strlen1617 = strlen(df) + strlen(" {\n") + 1;
  char* tmp_str1617 = calloc(tmp_strlen1617, sizeof(char));
  strcpy(tmp_str1617, df);
  strcat(tmp_str1617, " {\n");
  df = tmp_str1617;
  int tmp_strlen1592 = strlen(df) + strlen(stmts_out) + 1;
  char* tmp_str1592 = calloc(tmp_strlen1592, sizeof(char));
  strcpy(tmp_str1592, df);
  strcat(tmp_str1592, stmts_out);
  df = tmp_str1592;
  if ((strcmp(name, "_main") == 0)) {
    int tmp_strlen1532 = strlen(df) + strlen("  return 0;\n") + 1;
    char* tmp_str1532 = calloc(tmp_strlen1532, sizeof(char));
    strcpy(tmp_str1532, df);
    strcat(tmp_str1532, "  return 0;\n");
    df = tmp_str1532;
  }
  int tmp_strlen1503 = strlen(df) + strlen("}\n\n") + 1;
  char* tmp_str1503 = calloc(tmp_strlen1503, sizeof(char));
  strcpy(tmp_str1503, df);
  strcat(tmp_str1503, "}\n\n");
  df = tmp_str1503;
  return (TranslateFunc_results){src, decl, df};
}

char* TranslateProgram(char* src) {
  char* out = read("clib/lib.c");
  char* constants = "";
  char* decls = "";
  char* defs = "";
  int tok;
  char* tok_str;
  Peek_results tmp_results1259 = Peek(src);
  tok = tmp_results1259.result1;
  tok_str = tmp_results1259.result2;
  while ((tok) != (TOK_EOF)) {
    if ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results1165 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results1165.result1;
      Peek_results tmp_results1113 = Peek(src);
      tok = tmp_results1113.result1;
      tok_str = tmp_results1113.result2;
      continue;
    } else {
      if ((tok) == (TOK_LET)) {
        char* const_decl;
        TranslateConstDecl_results tmp_results985 = TranslateConstDecl(src, "");
        src = tmp_results985.result1;
        const_decl = tmp_results985.result2;
        int tmp_strlen892 = strlen(constants) + strlen(const_decl) + 1;
        char* tmp_str892 = calloc(tmp_strlen892, sizeof(char));
        strcpy(tmp_str892, constants);
        strcat(tmp_str892, const_decl);
        constants = tmp_str892;
      } else {
        if ((tok) == (TOK_FN)) {
          char* fn_decl;
          char* fn_def;
          TranslateFunc_results tmp_results782 = TranslateFunc(src);
          src = tmp_results782.result1;
          fn_decl = tmp_results782.result2;
          fn_def = tmp_results782.result3;
          int tmp_strlen704 = strlen(decls) + strlen(fn_decl) + 1;
          char* tmp_str704 = calloc(tmp_strlen704, sizeof(char));
          strcpy(tmp_str704, decls);
          strcat(tmp_str704, fn_decl);
          decls = tmp_str704;
          int tmp_strlen670 = strlen(defs) + strlen(fn_def) + 1;
          char* tmp_str670 = calloc(tmp_strlen670, sizeof(char));
          strcpy(tmp_str670, defs);
          strcat(tmp_str670, fn_def);
          defs = tmp_str670;
        } else {
          int tmp_strlen591 = strlen("unexpected decl token, got: ") + strlen(itoa(tok)) + 1;
          char* tmp_str591 = calloc(tmp_strlen591, sizeof(char));
          strcpy(tmp_str591, "unexpected decl token, got: ");
          strcat(tmp_str591, itoa(tok));
          int tmp_strlen582 = strlen(tmp_str591) + strlen(" \"") + 1;
          char* tmp_str582 = calloc(tmp_strlen582, sizeof(char));
          strcpy(tmp_str582, tmp_str591);
          strcat(tmp_str582, " \"");
          int tmp_strlen571 = strlen(tmp_str582) + strlen(tok_str) + 1;
          char* tmp_str571 = calloc(tmp_strlen571, sizeof(char));
          strcpy(tmp_str571, tmp_str582);
          strcat(tmp_str571, tok_str);
          int tmp_strlen563 = strlen(tmp_str571) + strlen("\"") + 1;
          char* tmp_str563 = calloc(tmp_strlen563, sizeof(char));
          strcpy(tmp_str563, tmp_str571);
          strcat(tmp_str563, "\"");
          printf("%s", tmp_str563);
          exit(1);
        }
      }
    }
    Peek_results tmp_results523 = Peek(src);
    tok = tmp_results523.result1;
    tok_str = tmp_results523.result2;
  }
  ConsumeToken_results tmp_results488 = ConsumeToken(src, TOK_EOF);
  src = tmp_results488.result1;
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


