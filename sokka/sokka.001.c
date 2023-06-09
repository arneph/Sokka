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
                  int tmp_strlen28760 = strlen("token has no defined precedence: ") + strlen(itoa(tok)) + 1;
                  char* tmp_str28760 = calloc(tmp_strlen28760, sizeof(char));
                  strcpy(tmp_str28760, "token has no defined precedence: ");
                  strcat(tmp_str28760, itoa(tok));
                  printf("%s", tmp_str28760);
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
      int tmp_strlen28443 = ((i) + (strlen(needle))) - (i) + 1;
      char* tmp_str28443 = calloc(tmp_strlen28443, sizeof(char));
      strncpy(tmp_str28443, haystack + i, tmp_strlen28443 - 1);
      tmp_str28443[tmp_strlen28443 - 1] = 0;
      if ((strcmp(tmp_str28443, needle) != 0)) {
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
      int tmp_strlen28109 = (strlen(prefix)) - (0) + 1;
      char* tmp_str28109 = calloc(tmp_strlen28109, sizeof(char));
      strncpy(tmp_str28109, text + 0, tmp_strlen28109 - 1);
      tmp_str28109[tmp_strlen28109 - 1] = 0;
      return (strcmp(tmp_str28109, prefix) == 0);
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
    int tmp_strlen27714 = (strlen(text)) - (1) + 1;
    char* tmp_str27714 = calloc(tmp_strlen27714, sizeof(char));
    strncpy(tmp_str27714, text + 1, tmp_strlen27714 - 1);
    tmp_str27714[tmp_strlen27714 - 1] = 0;
    text = tmp_str27714;
  }
  return text;
}

Next_results Next(char* src) {
  src = RemoveLeadingWhitespace(src);
  if ((strcmp(src, "") == 0)) {
    return (Next_results){"", TOK_EOF, ""};
  } else {
    if (StartsWith(src, "->")) {
      int tmp_strlen27491 = (strlen(src)) - (2) + 1;
      char* tmp_str27491 = calloc(tmp_strlen27491, sizeof(char));
      strncpy(tmp_str27491, src + 2, tmp_strlen27491 - 1);
      tmp_str27491[tmp_strlen27491 - 1] = 0;
      return (Next_results){tmp_str27491, TOK_RARROW, "->"};
    } else {
      if (StartsWith(src, "||")) {
        int tmp_strlen27412 = (strlen(src)) - (2) + 1;
        char* tmp_str27412 = calloc(tmp_strlen27412, sizeof(char));
        strncpy(tmp_str27412, src + 2, tmp_strlen27412 - 1);
        tmp_str27412[tmp_strlen27412 - 1] = 0;
        return (Next_results){tmp_str27412, TOK_BOR, "||"};
      } else {
        if (StartsWith(src, "&&")) {
          int tmp_strlen27336 = (strlen(src)) - (2) + 1;
          char* tmp_str27336 = calloc(tmp_strlen27336, sizeof(char));
          strncpy(tmp_str27336, src + 2, tmp_strlen27336 - 1);
          tmp_str27336[tmp_strlen27336 - 1] = 0;
          return (Next_results){tmp_str27336, TOK_BAND, "&&"};
        } else {
          if (StartsWith(src, "==")) {
            int tmp_strlen27259 = (strlen(src)) - (2) + 1;
            char* tmp_str27259 = calloc(tmp_strlen27259, sizeof(char));
            strncpy(tmp_str27259, src + 2, tmp_strlen27259 - 1);
            tmp_str27259[tmp_strlen27259 - 1] = 0;
            return (Next_results){tmp_str27259, TOK_EQ, "=="};
          } else {
            if (StartsWith(src, "!=")) {
              int tmp_strlen27184 = (strlen(src)) - (2) + 1;
              char* tmp_str27184 = calloc(tmp_strlen27184, sizeof(char));
              strncpy(tmp_str27184, src + 2, tmp_strlen27184 - 1);
              tmp_str27184[tmp_strlen27184 - 1] = 0;
              return (Next_results){tmp_str27184, TOK_NEQ, "!="};
            } else {
              if (StartsWith(src, "<=")) {
                int tmp_strlen27108 = (strlen(src)) - (2) + 1;
                char* tmp_str27108 = calloc(tmp_strlen27108, sizeof(char));
                strncpy(tmp_str27108, src + 2, tmp_strlen27108 - 1);
                tmp_str27108[tmp_strlen27108 - 1] = 0;
                return (Next_results){tmp_str27108, TOK_LEQ, "<="};
              } else {
                if (StartsWith(src, ">=")) {
                  int tmp_strlen27032 = (strlen(src)) - (2) + 1;
                  char* tmp_str27032 = calloc(tmp_strlen27032, sizeof(char));
                  strncpy(tmp_str27032, src + 2, tmp_strlen27032 - 1);
                  tmp_str27032[tmp_strlen27032 - 1] = 0;
                  return (Next_results){tmp_str27032, TOK_GEQ, ">="};
                } else {
                  if (StartsWith(src, "++")) {
                    int tmp_strlen26956 = (strlen(src)) - (2) + 1;
                    char* tmp_str26956 = calloc(tmp_strlen26956, sizeof(char));
                    strncpy(tmp_str26956, src + 2, tmp_strlen26956 - 1);
                    tmp_str26956[tmp_strlen26956 - 1] = 0;
                    return (Next_results){tmp_str26956, TOK_STRCAT, "++"};
                  } else {
                    if (StartsWith(src, "<>")) {
                      int tmp_strlen26877 = (strlen(src)) - (2) + 1;
                      char* tmp_str26877 = calloc(tmp_strlen26877, sizeof(char));
                      strncpy(tmp_str26877, src + 2, tmp_strlen26877 - 1);
                      tmp_str26877[tmp_strlen26877 - 1] = 0;
                      return (Next_results){tmp_str26877, TOK_STREQ, "<>"};
                    } else {
                      if (StartsWith(src, "<!>")) {
                        int tmp_strlen26798 = (strlen(src)) - (3) + 1;
                        char* tmp_str26798 = calloc(tmp_strlen26798, sizeof(char));
                        strncpy(tmp_str26798, src + 3, tmp_strlen26798 - 1);
                        tmp_str26798[tmp_strlen26798 - 1] = 0;
                        return (Next_results){tmp_str26798, TOK_STRNEQ, "<!>"};
                      } else {
                        if (StartsWith(src, "\n")) {
                          int tmp_strlen26718 = (strlen(src)) - (1) + 1;
                          char* tmp_str26718 = calloc(tmp_strlen26718, sizeof(char));
                          strncpy(tmp_str26718, src + 1, tmp_strlen26718 - 1);
                          tmp_str26718[tmp_strlen26718 - 1] = 0;
                          return (Next_results){tmp_str26718, TOK_NEWLINE, "\n"};
                        } else {
                          if (StartsWith(src, "(")) {
                            int tmp_strlen26639 = (strlen(src)) - (1) + 1;
                            char* tmp_str26639 = calloc(tmp_strlen26639, sizeof(char));
                            strncpy(tmp_str26639, src + 1, tmp_strlen26639 - 1);
                            tmp_str26639[tmp_strlen26639 - 1] = 0;
                            return (Next_results){tmp_str26639, TOK_LPAREN, "("};
                          } else {
                            if (StartsWith(src, ")")) {
                              int tmp_strlen26562 = (strlen(src)) - (1) + 1;
                              char* tmp_str26562 = calloc(tmp_strlen26562, sizeof(char));
                              strncpy(tmp_str26562, src + 1, tmp_strlen26562 - 1);
                              tmp_str26562[tmp_strlen26562 - 1] = 0;
                              return (Next_results){tmp_str26562, TOK_RPAREN, ")"};
                            } else {
                              if (StartsWith(src, "[")) {
                                int tmp_strlen26485 = (strlen(src)) - (1) + 1;
                                char* tmp_str26485 = calloc(tmp_strlen26485, sizeof(char));
                                strncpy(tmp_str26485, src + 1, tmp_strlen26485 - 1);
                                tmp_str26485[tmp_strlen26485 - 1] = 0;
                                return (Next_results){tmp_str26485, TOK_LBRACKET, "["};
                              } else {
                                if (StartsWith(src, "]")) {
                                  int tmp_strlen26406 = (strlen(src)) - (1) + 1;
                                  char* tmp_str26406 = calloc(tmp_strlen26406, sizeof(char));
                                  strncpy(tmp_str26406, src + 1, tmp_strlen26406 - 1);
                                  tmp_str26406[tmp_strlen26406 - 1] = 0;
                                  return (Next_results){tmp_str26406, TOK_RBRACKET, "]"};
                                } else {
                                  if (StartsWith(src, "{")) {
                                    int tmp_strlen26327 = (strlen(src)) - (1) + 1;
                                    char* tmp_str26327 = calloc(tmp_strlen26327, sizeof(char));
                                    strncpy(tmp_str26327, src + 1, tmp_strlen26327 - 1);
                                    tmp_str26327[tmp_strlen26327 - 1] = 0;
                                    return (Next_results){tmp_str26327, TOK_LCURLY, "{"};
                                  } else {
                                    if (StartsWith(src, "}")) {
                                      int tmp_strlen26250 = (strlen(src)) - (1) + 1;
                                      char* tmp_str26250 = calloc(tmp_strlen26250, sizeof(char));
                                      strncpy(tmp_str26250, src + 1, tmp_strlen26250 - 1);
                                      tmp_str26250[tmp_strlen26250 - 1] = 0;
                                      return (Next_results){tmp_str26250, TOK_RCURLY, "}"};
                                    } else {
                                      if (StartsWith(src, "_")) {
                                        int tmp_strlen26173 = (strlen(src)) - (1) + 1;
                                        char* tmp_str26173 = calloc(tmp_strlen26173, sizeof(char));
                                        strncpy(tmp_str26173, src + 1, tmp_strlen26173 - 1);
                                        tmp_str26173[tmp_strlen26173 - 1] = 0;
                                        return (Next_results){tmp_str26173, TOK_UNDERSCORE, "_"};
                                      } else {
                                        if (StartsWith(src, ":")) {
                                          int tmp_strlen26092 = (strlen(src)) - (1) + 1;
                                          char* tmp_str26092 = calloc(tmp_strlen26092, sizeof(char));
                                          strncpy(tmp_str26092, src + 1, tmp_strlen26092 - 1);
                                          tmp_str26092[tmp_strlen26092 - 1] = 0;
                                          return (Next_results){tmp_str26092, TOK_COLON, ":"};
                                        } else {
                                          if (StartsWith(src, ",")) {
                                            int tmp_strlen26016 = (strlen(src)) - (1) + 1;
                                            char* tmp_str26016 = calloc(tmp_strlen26016, sizeof(char));
                                            strncpy(tmp_str26016, src + 1, tmp_strlen26016 - 1);
                                            tmp_str26016[tmp_strlen26016 - 1] = 0;
                                            return (Next_results){tmp_str26016, TOK_COMMA, ","};
                                          } else {
                                            if (StartsWith(src, "=")) {
                                              int tmp_strlen25940 = (strlen(src)) - (1) + 1;
                                              char* tmp_str25940 = calloc(tmp_strlen25940, sizeof(char));
                                              strncpy(tmp_str25940, src + 1, tmp_strlen25940 - 1);
                                              tmp_str25940[tmp_strlen25940 - 1] = 0;
                                              return (Next_results){tmp_str25940, TOK_ASSIGN, "="};
                                            } else {
                                              if (StartsWith(src, "!")) {
                                                int tmp_strlen25863 = (strlen(src)) - (1) + 1;
                                                char* tmp_str25863 = calloc(tmp_strlen25863, sizeof(char));
                                                strncpy(tmp_str25863, src + 1, tmp_strlen25863 - 1);
                                                tmp_str25863[tmp_strlen25863 - 1] = 0;
                                                return (Next_results){tmp_str25863, TOK_BNOT, "!"};
                                              } else {
                                                if (StartsWith(src, "+")) {
                                                  int tmp_strlen25788 = (strlen(src)) - (1) + 1;
                                                  char* tmp_str25788 = calloc(tmp_strlen25788, sizeof(char));
                                                  strncpy(tmp_str25788, src + 1, tmp_strlen25788 - 1);
                                                  tmp_str25788[tmp_strlen25788 - 1] = 0;
                                                  return (Next_results){tmp_str25788, TOK_ADD, "+"};
                                                } else {
                                                  if (StartsWith(src, "-")) {
                                                    int tmp_strlen25714 = (strlen(src)) - (1) + 1;
                                                    char* tmp_str25714 = calloc(tmp_strlen25714, sizeof(char));
                                                    strncpy(tmp_str25714, src + 1, tmp_strlen25714 - 1);
                                                    tmp_str25714[tmp_strlen25714 - 1] = 0;
                                                    return (Next_results){tmp_str25714, TOK_SUB, "-"};
                                                  } else {
                                                    if (StartsWith(src, "*")) {
                                                      int tmp_strlen25640 = (strlen(src)) - (1) + 1;
                                                      char* tmp_str25640 = calloc(tmp_strlen25640, sizeof(char));
                                                      strncpy(tmp_str25640, src + 1, tmp_strlen25640 - 1);
                                                      tmp_str25640[tmp_strlen25640 - 1] = 0;
                                                      return (Next_results){tmp_str25640, TOK_MUL, "*"};
                                                    } else {
                                                      if (StartsWith(src, "/")) {
                                                        int tmp_strlen25566 = (strlen(src)) - (1) + 1;
                                                        char* tmp_str25566 = calloc(tmp_strlen25566, sizeof(char));
                                                        strncpy(tmp_str25566, src + 1, tmp_strlen25566 - 1);
                                                        tmp_str25566[tmp_strlen25566 - 1] = 0;
                                                        return (Next_results){tmp_str25566, TOK_DIV, "/"};
                                                      } else {
                                                        if (StartsWith(src, "%")) {
                                                          int tmp_strlen25492 = (strlen(src)) - (1) + 1;
                                                          char* tmp_str25492 = calloc(tmp_strlen25492, sizeof(char));
                                                          strncpy(tmp_str25492, src + 1, tmp_strlen25492 - 1);
                                                          tmp_str25492[tmp_strlen25492 - 1] = 0;
                                                          return (Next_results){tmp_str25492, TOK_REM, "%"};
                                                        } else {
                                                          if (StartsWith(src, "~")) {
                                                            int tmp_strlen25418 = (strlen(src)) - (1) + 1;
                                                            char* tmp_str25418 = calloc(tmp_strlen25418, sizeof(char));
                                                            strncpy(tmp_str25418, src + 1, tmp_strlen25418 - 1);
                                                            tmp_str25418[tmp_strlen25418 - 1] = 0;
                                                            return (Next_results){tmp_str25418, TOK_INOT, "~"};
                                                          } else {
                                                            if (StartsWith(src, "|")) {
                                                              int tmp_strlen25343 = (strlen(src)) - (1) + 1;
                                                              char* tmp_str25343 = calloc(tmp_strlen25343, sizeof(char));
                                                              strncpy(tmp_str25343, src + 1, tmp_strlen25343 - 1);
                                                              tmp_str25343[tmp_strlen25343 - 1] = 0;
                                                              return (Next_results){tmp_str25343, TOK_IOR, "|"};
                                                            } else {
                                                              if (StartsWith(src, "&")) {
                                                                int tmp_strlen25269 = (strlen(src)) - (1) + 1;
                                                                char* tmp_str25269 = calloc(tmp_strlen25269, sizeof(char));
                                                                strncpy(tmp_str25269, src + 1, tmp_strlen25269 - 1);
                                                                tmp_str25269[tmp_strlen25269 - 1] = 0;
                                                                return (Next_results){tmp_str25269, TOK_IAND, "&"};
                                                              } else {
                                                                if (StartsWith(src, "^")) {
                                                                  int tmp_strlen25194 = (strlen(src)) - (1) + 1;
                                                                  char* tmp_str25194 = calloc(tmp_strlen25194, sizeof(char));
                                                                  strncpy(tmp_str25194, src + 1, tmp_strlen25194 - 1);
                                                                  tmp_str25194[tmp_strlen25194 - 1] = 0;
                                                                  return (Next_results){tmp_str25194, TOK_IXOR, "^"};
                                                                } else {
                                                                  if (StartsWith(src, "<")) {
                                                                    int tmp_strlen25119 = (strlen(src)) - (1) + 1;
                                                                    char* tmp_str25119 = calloc(tmp_strlen25119, sizeof(char));
                                                                    strncpy(tmp_str25119, src + 1, tmp_strlen25119 - 1);
                                                                    tmp_str25119[tmp_strlen25119 - 1] = 0;
                                                                    return (Next_results){tmp_str25119, TOK_LESS, "<"};
                                                                  } else {
                                                                    if (StartsWith(src, ">")) {
                                                                      int tmp_strlen25044 = (strlen(src)) - (1) + 1;
                                                                      char* tmp_str25044 = calloc(tmp_strlen25044, sizeof(char));
                                                                      strncpy(tmp_str25044, src + 1, tmp_strlen25044 - 1);
                                                                      tmp_str25044[tmp_strlen25044 - 1] = 0;
                                                                      return (Next_results){tmp_str25044, TOK_GREATER, ">"};
                                                                    } else {
                                                                      if (IsAlpha(src[0])) {
                                                                        int i = 1;
                                                                        while (((i) < (strlen(src))) && ((IsAlphaNumeric(src[(i) - (1)])) || ((src[(i) - (1)]) == (95)))) {
                                                                          i = (i) + (1);
                                                                        }
                                                                        i = (i) - (1);
                                                                        int tmp_strlen24814 = (i) - (0) + 1;
                                                                        char* tmp_str24814 = calloc(tmp_strlen24814, sizeof(char));
                                                                        strncpy(tmp_str24814, src + 0, tmp_strlen24814 - 1);
                                                                        tmp_str24814[tmp_strlen24814 - 1] = 0;
                                                                        char* ts = tmp_str24814;
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
                                                                        int tmp_strlen24021 = (strlen(src)) - (i) + 1;
                                                                        char* tmp_str24021 = calloc(tmp_strlen24021, sizeof(char));
                                                                        strncpy(tmp_str24021, src + i, tmp_strlen24021 - 1);
                                                                        tmp_str24021[tmp_strlen24021 - 1] = 0;
                                                                        return (Next_results){tmp_str24021, tt, ts};
                                                                      } else {
                                                                        if (IsNumeric(src[0])) {
                                                                          int i = 1;
                                                                          while (((i) < (strlen(src))) && (IsNumeric(src[i]))) {
                                                                            i = (i) + (1);
                                                                          }
                                                                          int tmp_strlen23853 = (strlen(src)) - (i) + 1;
                                                                          char* tmp_str23853 = calloc(tmp_strlen23853, sizeof(char));
                                                                          strncpy(tmp_str23853, src + i, tmp_strlen23853 - 1);
                                                                          tmp_str23853[tmp_strlen23853 - 1] = 0;
                                                                          int tmp_strlen23833 = (i) - (0) + 1;
                                                                          char* tmp_str23833 = calloc(tmp_strlen23833, sizeof(char));
                                                                          strncpy(tmp_str23833, src + 0, tmp_strlen23833 - 1);
                                                                          tmp_str23833[tmp_strlen23833 - 1] = 0;
                                                                          return (Next_results){tmp_str23853, TOK_INTLIT, tmp_str23833};
                                                                        } else {
                                                                          if (StartsWith(src, "\"")) {
                                                                            int i = 1;
                                                                            while (true) {
                                                                              int tmp_strlen23751 = ((i) + (1)) - (i) + 1;
                                                                              char* tmp_str23751 = calloc(tmp_strlen23751, sizeof(char));
                                                                              strncpy(tmp_str23751, src + i, tmp_strlen23751 - 1);
                                                                              tmp_str23751[tmp_strlen23751 - 1] = 0;
                                                                              if (!((strcmp(tmp_str23751, "\"") != 0))) break;
                                                                              i = (i) + (1);
                                                                              int tmp_strlen23690 = (i) - ((i) - (1)) + 1;
                                                                              char* tmp_str23690 = calloc(tmp_strlen23690, sizeof(char));
                                                                              strncpy(tmp_str23690, src + (i) - (1), tmp_strlen23690 - 1);
                                                                              tmp_str23690[tmp_strlen23690 - 1] = 0;
                                                                              if ((strcmp(tmp_str23690, "\\") == 0)) {
                                                                                i = (i) + (1);
                                                                              }
                                                                            }
                                                                            i = (i) + (1);
                                                                            int tmp_strlen23588 = (strlen(src)) - (i) + 1;
                                                                            char* tmp_str23588 = calloc(tmp_strlen23588, sizeof(char));
                                                                            strncpy(tmp_str23588, src + i, tmp_strlen23588 - 1);
                                                                            tmp_str23588[tmp_strlen23588 - 1] = 0;
                                                                            int tmp_strlen23568 = (i) - (0) + 1;
                                                                            char* tmp_str23568 = calloc(tmp_strlen23568, sizeof(char));
                                                                            strncpy(tmp_str23568, src + 0, tmp_strlen23568 - 1);
                                                                            tmp_str23568[tmp_strlen23568 - 1] = 0;
                                                                            return (Next_results){tmp_str23588, TOK_STRLIT, tmp_str23568};
                                                                          } else {
                                                                            int tmp_strlen23503 = (1) - (0) + 1;
                                                                            char* tmp_str23503 = calloc(tmp_strlen23503, sizeof(char));
                                                                            strncpy(tmp_str23503, src + 0, tmp_strlen23503 - 1);
                                                                            tmp_str23503[tmp_strlen23503 - 1] = 0;
                                                                            int tmp_strlen23500 = strlen("unexpected token start: ") + strlen(tmp_str23503) + 1;
                                                                            char* tmp_str23500 = calloc(tmp_strlen23500, sizeof(char));
                                                                            strcpy(tmp_str23500, "unexpected token start: ");
                                                                            strcat(tmp_str23500, tmp_str23503);
                                                                            printf("%s", tmp_str23500);
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
  Next_results tmp_results23388 = Next(src);
  src = tmp_results23388.result1;
  tok = tmp_results23388.result2;
  tok_str = tmp_results23388.result3;
  return (Peek_results){tok, tok_str};
}

ConsumeToken_results ConsumeToken(char* src, int expected_tok) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results23202 = Next(src);
  src = tmp_results23202.result1;
  actual_tok = tmp_results23202.result2;
  actual_tok_str = tmp_results23202.result3;
  if ((actual_tok) != (expected_tok)) {
    int tmp_strlen23068 = strlen("expected token: ") + strlen(itoa(expected_tok)) + 1;
    char* tmp_str23068 = calloc(tmp_strlen23068, sizeof(char));
    strcpy(tmp_str23068, "expected token: ");
    strcat(tmp_str23068, itoa(expected_tok));
    int tmp_strlen23041 = strlen(tmp_str23068) + strlen(" got: ") + 1;
    char* tmp_str23041 = calloc(tmp_strlen23041, sizeof(char));
    strcpy(tmp_str23041, tmp_str23068);
    strcat(tmp_str23041, " got: ");
    int tmp_strlen23021 = strlen(tmp_str23041) + strlen(itoa(actual_tok)) + 1;
    char* tmp_str23021 = calloc(tmp_strlen23021, sizeof(char));
    strcpy(tmp_str23021, tmp_str23041);
    strcat(tmp_str23021, itoa(actual_tok));
    int tmp_strlen23012 = strlen(tmp_str23021) + strlen(" \"") + 1;
    char* tmp_str23012 = calloc(tmp_strlen23012, sizeof(char));
    strcpy(tmp_str23012, tmp_str23021);
    strcat(tmp_str23012, " \"");
    int tmp_strlen22994 = strlen(tmp_str23012) + strlen(actual_tok_str) + 1;
    char* tmp_str22994 = calloc(tmp_strlen22994, sizeof(char));
    strcpy(tmp_str22994, tmp_str23012);
    strcat(tmp_str22994, actual_tok_str);
    int tmp_strlen22986 = strlen(tmp_str22994) + strlen("\"") + 1;
    char* tmp_str22986 = calloc(tmp_strlen22986, sizeof(char));
    strcpy(tmp_str22986, tmp_str22994);
    strcat(tmp_str22986, "\"");
    printf("%s", tmp_str22986);
    exit(1);
  }
  return (ConsumeToken_results){src, actual_tok_str};
}

ConsumeIdent_results ConsumeIdent(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22818 = Next(src);
  src = tmp_results22818.result1;
  actual_tok = tmp_results22818.result2;
  actual_tok_str = tmp_results22818.result3;
  if ((actual_tok) != (TOK_IDENT)) {
    int tmp_strlen22684 = strlen("expected ident, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22684 = calloc(tmp_strlen22684, sizeof(char));
    strcpy(tmp_str22684, "expected ident, got: ");
    strcat(tmp_str22684, itoa(actual_tok));
    int tmp_strlen22675 = strlen(tmp_str22684) + strlen(" \"") + 1;
    char* tmp_str22675 = calloc(tmp_strlen22675, sizeof(char));
    strcpy(tmp_str22675, tmp_str22684);
    strcat(tmp_str22675, " \"");
    int tmp_strlen22657 = strlen(tmp_str22675) + strlen(actual_tok_str) + 1;
    char* tmp_str22657 = calloc(tmp_strlen22657, sizeof(char));
    strcpy(tmp_str22657, tmp_str22675);
    strcat(tmp_str22657, actual_tok_str);
    int tmp_strlen22649 = strlen(tmp_str22657) + strlen("\"") + 1;
    char* tmp_str22649 = calloc(tmp_strlen22649, sizeof(char));
    strcpy(tmp_str22649, tmp_str22657);
    strcat(tmp_str22649, "\"");
    printf("%s", tmp_str22649);
    exit(1);
  }
  return (ConsumeIdent_results){src, actual_tok_str};
}

ConsumeIdentOrUnderscore_results ConsumeIdentOrUnderscore(char* src) {
  int actual_tok;
  char* actual_tok_str;
  Next_results tmp_results22469 = Next(src);
  src = tmp_results22469.result1;
  actual_tok = tmp_results22469.result2;
  actual_tok_str = tmp_results22469.result3;
  if (((actual_tok) == (TOK_UNDERSCORE)) || ((actual_tok) == (TOK_IDENT))) {
    return (ConsumeIdentOrUnderscore_results){src, actual_tok_str};
  } else {
    int tmp_strlen22241 = strlen("expected ident or underscore, got: ") + strlen(itoa(actual_tok)) + 1;
    char* tmp_str22241 = calloc(tmp_strlen22241, sizeof(char));
    strcpy(tmp_str22241, "expected ident or underscore, got: ");
    strcat(tmp_str22241, itoa(actual_tok));
    int tmp_strlen22232 = strlen(tmp_str22241) + strlen(" \"") + 1;
    char* tmp_str22232 = calloc(tmp_strlen22232, sizeof(char));
    strcpy(tmp_str22232, tmp_str22241);
    strcat(tmp_str22232, " \"");
    int tmp_strlen22214 = strlen(tmp_str22232) + strlen(actual_tok_str) + 1;
    char* tmp_str22214 = calloc(tmp_strlen22214, sizeof(char));
    strcpy(tmp_str22214, tmp_str22232);
    strcat(tmp_str22214, actual_tok_str);
    int tmp_strlen22206 = strlen(tmp_str22214) + strlen("\"") + 1;
    char* tmp_str22206 = calloc(tmp_strlen22206, sizeof(char));
    strcpy(tmp_str22206, tmp_str22214);
    strcat(tmp_str22206, "\"");
    printf("%s", tmp_str22206);
    exit(1);
  }
}

TranslateType_results TranslateType(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results22077 = Next(src);
  src = tmp_results22077.result1;
  tok = tmp_results22077.result2;
  tok_str = tmp_results22077.result3;
  if ((tok) == (TOK_BOOL)) {
    return (TranslateType_results){src, TYPE_BOOL, "bool"};
  } else {
    if ((tok) == (TOK_INT)) {
      return (TranslateType_results){src, TYPE_INT, "int"};
    } else {
      if ((tok) == (TOK_STRING)) {
        return (TranslateType_results){src, TYPE_STRING, "char*"};
      } else {
        int tmp_strlen21780 = strlen("expected type, got: ") + strlen(itoa(tok)) + 1;
        char* tmp_str21780 = calloc(tmp_strlen21780, sizeof(char));
        strcpy(tmp_str21780, "expected type, got: ");
        strcat(tmp_str21780, itoa(tok));
        int tmp_strlen21771 = strlen(tmp_str21780) + strlen(" \"") + 1;
        char* tmp_str21771 = calloc(tmp_strlen21771, sizeof(char));
        strcpy(tmp_str21771, tmp_str21780);
        strcat(tmp_str21771, " \"");
        int tmp_strlen21760 = strlen(tmp_str21771) + strlen(tok_str) + 1;
        char* tmp_str21760 = calloc(tmp_strlen21760, sizeof(char));
        strcpy(tmp_str21760, tmp_str21771);
        strcat(tmp_str21760, tok_str);
        int tmp_strlen21752 = strlen(tmp_str21760) + strlen("\"") + 1;
        char* tmp_str21752 = calloc(tmp_strlen21752, sizeof(char));
        strcpy(tmp_str21752, tmp_str21760);
        strcat(tmp_str21752, "\"");
        printf("%s", tmp_str21752);
        exit(1);
      }
    }
  }
}

TranslateBoolLiteral_results TranslateBoolLiteral(char* src) {
  int tok;
  char* tok_str;
  Next_results tmp_results21621 = Next(src);
  src = tmp_results21621.result1;
  tok = tmp_results21621.result2;
  tok_str = tmp_results21621.result3;
  if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
    return (TranslateBoolLiteral_results){src, tok_str};
  } else {
    int tmp_strlen21447 = strlen("expected false or true, got: ") + strlen(itoa(tok)) + 1;
    char* tmp_str21447 = calloc(tmp_strlen21447, sizeof(char));
    strcpy(tmp_str21447, "expected false or true, got: ");
    strcat(tmp_str21447, itoa(tok));
    int tmp_strlen21438 = strlen(tmp_str21447) + strlen(" \"") + 1;
    char* tmp_str21438 = calloc(tmp_strlen21438, sizeof(char));
    strcpy(tmp_str21438, tmp_str21447);
    strcat(tmp_str21438, " \"");
    int tmp_strlen21427 = strlen(tmp_str21438) + strlen(tok_str) + 1;
    char* tmp_str21427 = calloc(tmp_strlen21427, sizeof(char));
    strcpy(tmp_str21427, tmp_str21438);
    strcat(tmp_str21427, tok_str);
    int tmp_strlen21419 = strlen(tmp_str21427) + strlen("\"") + 1;
    char* tmp_str21419 = calloc(tmp_strlen21419, sizeof(char));
    strcpy(tmp_str21419, tmp_str21427);
    strcat(tmp_str21419, "\"");
    printf("%s", tmp_str21419);
    exit(1);
  }
}

TranslateIntLiteral_results TranslateIntLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results21310 = ConsumeToken(src, TOK_INTLIT);
  src = tmp_results21310.result1;
  lit = tmp_results21310.result2;
  return (TranslateIntLiteral_results){src, lit};
}

TranslateStringLiteral_results TranslateStringLiteral(char* src) {
  char* lit;
  ConsumeToken_results tmp_results21161 = ConsumeToken(src, TOK_STRLIT);
  src = tmp_results21161.result1;
  lit = tmp_results21161.result2;
  return (TranslateStringLiteral_results){src, lit};
}

TranslateCall_results TranslateCall(char* src, char* indent, char* callee) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results20960 = ConsumeToken(src, TOK_LPAREN);
  src = tmp_results20960.result1;
  tok_str = tmp_results20960.result2;
  Peek_results tmp_results20911 = Peek(src);
  tok = tmp_results20911.result1;
  tok_str = tmp_results20911.result2;
  char* args_setup = "";
  char* arg_values = "";
  if ((tok) != (TOK_RPAREN)) {
    int expr_count;
    TranslateExprs_results tmp_results20759 = TranslateExprs(src, indent);
    src = tmp_results20759.result1;
    expr_count = tmp_results20759.result2;
    args_setup = tmp_results20759.result3;
    arg_values = tmp_results20759.result4;
  }
  ConsumeToken_results tmp_results20679 = ConsumeToken(src, TOK_RPAREN);
  src = tmp_results20679.result1;
  tok_str = tmp_results20679.result2;
  char* val;
  if ((strcmp(callee, "print") == 0)) {
    int tmp_strlen20542 = strlen("printf(\"%s\", ") + strlen(arg_values) + 1;
    char* tmp_str20542 = calloc(tmp_strlen20542, sizeof(char));
    strcpy(tmp_str20542, "printf(\"%s\", ");
    strcat(tmp_str20542, arg_values);
    int tmp_strlen20535 = strlen(tmp_str20542) + strlen(")") + 1;
    char* tmp_str20535 = calloc(tmp_strlen20535, sizeof(char));
    strcpy(tmp_str20535, tmp_str20542);
    strcat(tmp_str20535, ")");
    val = tmp_str20535;
  } else {
    if ((strcmp(callee, "len") == 0)) {
      int tmp_strlen20465 = strlen("strlen(") + strlen(arg_values) + 1;
      char* tmp_str20465 = calloc(tmp_strlen20465, sizeof(char));
      strcpy(tmp_str20465, "strlen(");
      strcat(tmp_str20465, arg_values);
      int tmp_strlen20458 = strlen(tmp_str20465) + strlen(")") + 1;
      char* tmp_str20458 = calloc(tmp_strlen20458, sizeof(char));
      strcpy(tmp_str20458, tmp_str20465);
      strcat(tmp_str20458, ")");
      val = tmp_str20458;
    } else {
      int tmp_strlen20417 = strlen(callee) + strlen("(") + 1;
      char* tmp_str20417 = calloc(tmp_strlen20417, sizeof(char));
      strcpy(tmp_str20417, callee);
      strcat(tmp_str20417, "(");
      int tmp_strlen20403 = strlen(tmp_str20417) + strlen(arg_values) + 1;
      char* tmp_str20403 = calloc(tmp_strlen20403, sizeof(char));
      strcpy(tmp_str20403, tmp_str20417);
      strcat(tmp_str20403, arg_values);
      int tmp_strlen20396 = strlen(tmp_str20403) + strlen(")") + 1;
      char* tmp_str20396 = calloc(tmp_strlen20396, sizeof(char));
      strcpy(tmp_str20396, tmp_str20403);
      strcat(tmp_str20396, ")");
      val = tmp_str20396;
    }
  }
  return (TranslateCall_results){src, args_setup, val};
}

TranslateSubstrExpr_results TranslateSubstrExpr(char* src, char* indent, char* strvar) {
  int tok;
  char* tok_str;
  int p = strlen(src);
  ConsumeToken_results tmp_results20185 = ConsumeToken(src, TOK_LBRACKET);
  src = tmp_results20185.result1;
  tok_str = tmp_results20185.result2;
  char* low_setup = "";
  char* low_expr = "0";
  char* high_setup = "";
  int tmp_strlen19997 = strlen("strlen(") + strlen(strvar) + 1;
  char* tmp_str19997 = calloc(tmp_strlen19997, sizeof(char));
  strcpy(tmp_str19997, "strlen(");
  strcat(tmp_str19997, strvar);
  int tmp_strlen19990 = strlen(tmp_str19997) + strlen(")") + 1;
  char* tmp_str19990 = calloc(tmp_strlen19990, sizeof(char));
  strcpy(tmp_str19990, tmp_str19997);
  strcat(tmp_str19990, ")");
  char* high_expr = tmp_str19990;
  Peek_results tmp_results19985 = Peek(src);
  tok = tmp_results19985.result1;
  tok_str = tmp_results19985.result2;
  if ((tok) == (TOK_COLON)) {
    ConsumeToken_results tmp_results19926 = ConsumeToken(src, TOK_COLON);
    src = tmp_results19926.result1;
    tok_str = tmp_results19926.result2;
    TranslateExpr_results tmp_results19874 = TranslateExpr(src, indent);
    src = tmp_results19874.result1;
    high_setup = tmp_results19874.result2;
    high_expr = tmp_results19874.result3;
    ConsumeToken_results tmp_results19810 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results19810.result1;
    tok_str = tmp_results19810.result2;
  } else {
    TranslateExpr_results tmp_results19742 = TranslateExpr(src, indent);
    src = tmp_results19742.result1;
    low_setup = tmp_results19742.result2;
    low_expr = tmp_results19742.result3;
    Peek_results tmp_results19680 = Peek(src);
    tok = tmp_results19680.result1;
    tok_str = tmp_results19680.result2;
    if ((tok) == (TOK_RBRACKET)) {
      ConsumeToken_results tmp_results19610 = ConsumeToken(src, TOK_RBRACKET);
      src = tmp_results19610.result1;
      tok_str = tmp_results19610.result2;
      int tmp_strlen19515 = strlen(strvar) + strlen("[") + 1;
      char* tmp_str19515 = calloc(tmp_strlen19515, sizeof(char));
      strcpy(tmp_str19515, strvar);
      strcat(tmp_str19515, "[");
      int tmp_strlen19503 = strlen(tmp_str19515) + strlen(low_expr) + 1;
      char* tmp_str19503 = calloc(tmp_strlen19503, sizeof(char));
      strcpy(tmp_str19503, tmp_str19515);
      strcat(tmp_str19503, low_expr);
      int tmp_strlen19496 = strlen(tmp_str19503) + strlen("]") + 1;
      char* tmp_str19496 = calloc(tmp_strlen19496, sizeof(char));
      strcpy(tmp_str19496, tmp_str19503);
      strcat(tmp_str19496, "]");
      return (TranslateSubstrExpr_results){src, low_setup, tmp_str19496};
    }
    ConsumeToken_results tmp_results19477 = ConsumeToken(src, TOK_COLON);
    src = tmp_results19477.result1;
    tok_str = tmp_results19477.result2;
    Peek_results tmp_results19425 = Peek(src);
    tok = tmp_results19425.result1;
    tok_str = tmp_results19425.result2;
    if ((tok) != (TOK_RBRACKET)) {
      TranslateExpr_results tmp_results19355 = TranslateExpr(src, indent);
      src = tmp_results19355.result1;
      high_setup = tmp_results19355.result2;
      high_expr = tmp_results19355.result3;
    }
    ConsumeToken_results tmp_results19281 = ConsumeToken(src, TOK_RBRACKET);
    src = tmp_results19281.result1;
    tok_str = tmp_results19281.result2;
  }
  int tmp_strlen19182 = strlen("tmp_str") + strlen(itoa(p)) + 1;
  char* tmp_str19182 = calloc(tmp_strlen19182, sizeof(char));
  strcpy(tmp_str19182, "tmp_str");
  strcat(tmp_str19182, itoa(p));
  char* tmp_str = tmp_str19182;
  int tmp_strlen19129 = strlen("tmp_strlen") + strlen(itoa(p)) + 1;
  char* tmp_str19129 = calloc(tmp_strlen19129, sizeof(char));
  strcpy(tmp_str19129, "tmp_strlen");
  strcat(tmp_str19129, itoa(p));
  char* tmp_strlen = tmp_str19129;
  int tmp_strlen19081 = strlen(low_setup) + strlen(high_setup) + 1;
  char* tmp_str19081 = calloc(tmp_strlen19081, sizeof(char));
  strcpy(tmp_str19081, low_setup);
  strcat(tmp_str19081, high_setup);
  char* setup = tmp_str19081;
  int tmp_strlen19053 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str19053 = calloc(tmp_strlen19053, sizeof(char));
  strcpy(tmp_str19053, setup);
  strcat(tmp_str19053, indent);
  int tmp_strlen19043 = strlen(tmp_str19053) + strlen("int ") + 1;
  char* tmp_str19043 = calloc(tmp_strlen19043, sizeof(char));
  strcpy(tmp_str19043, tmp_str19053);
  strcat(tmp_str19043, "int ");
  int tmp_strlen19029 = strlen(tmp_str19043) + strlen(tmp_strlen) + 1;
  char* tmp_str19029 = calloc(tmp_strlen19029, sizeof(char));
  strcpy(tmp_str19029, tmp_str19043);
  strcat(tmp_str19029, tmp_strlen);
  int tmp_strlen19019 = strlen(tmp_str19029) + strlen(" = (") + 1;
  char* tmp_str19019 = calloc(tmp_strlen19019, sizeof(char));
  strcpy(tmp_str19019, tmp_str19029);
  strcat(tmp_str19019, " = (");
  int tmp_strlen19006 = strlen(tmp_str19019) + strlen(high_expr) + 1;
  char* tmp_str19006 = calloc(tmp_strlen19006, sizeof(char));
  strcpy(tmp_str19006, tmp_str19019);
  strcat(tmp_str19006, high_expr);
  int tmp_strlen18995 = strlen(tmp_str19006) + strlen(") - (") + 1;
  char* tmp_str18995 = calloc(tmp_strlen18995, sizeof(char));
  strcpy(tmp_str18995, tmp_str19006);
  strcat(tmp_str18995, ") - (");
  int tmp_strlen18983 = strlen(tmp_str18995) + strlen(low_expr) + 1;
  char* tmp_str18983 = calloc(tmp_strlen18983, sizeof(char));
  strcpy(tmp_str18983, tmp_str18995);
  strcat(tmp_str18983, low_expr);
  int tmp_strlen18969 = strlen(tmp_str18983) + strlen(") + 1;\n") + 1;
  char* tmp_str18969 = calloc(tmp_strlen18969, sizeof(char));
  strcpy(tmp_str18969, tmp_str18983);
  strcat(tmp_str18969, ") + 1;\n");
  setup = tmp_str18969;
  int tmp_strlen18941 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18941 = calloc(tmp_strlen18941, sizeof(char));
  strcpy(tmp_str18941, setup);
  strcat(tmp_str18941, indent);
  int tmp_strlen18929 = strlen(tmp_str18941) + strlen("char* ") + 1;
  char* tmp_str18929 = calloc(tmp_strlen18929, sizeof(char));
  strcpy(tmp_str18929, tmp_str18941);
  strcat(tmp_str18929, "char* ");
  int tmp_strlen18918 = strlen(tmp_str18929) + strlen(tmp_str) + 1;
  char* tmp_str18918 = calloc(tmp_strlen18918, sizeof(char));
  strcpy(tmp_str18918, tmp_str18929);
  strcat(tmp_str18918, tmp_str);
  int tmp_strlen18902 = strlen(tmp_str18918) + strlen(" = calloc(") + 1;
  char* tmp_str18902 = calloc(tmp_strlen18902, sizeof(char));
  strcpy(tmp_str18902, tmp_str18918);
  strcat(tmp_str18902, " = calloc(");
  int tmp_strlen18888 = strlen(tmp_str18902) + strlen(tmp_strlen) + 1;
  char* tmp_str18888 = calloc(tmp_strlen18888, sizeof(char));
  strcpy(tmp_str18888, tmp_str18902);
  strcat(tmp_str18888, tmp_strlen);
  int tmp_strlen18864 = strlen(tmp_str18888) + strlen(", sizeof(char));\n") + 1;
  char* tmp_str18864 = calloc(tmp_strlen18864, sizeof(char));
  strcpy(tmp_str18864, tmp_str18888);
  strcat(tmp_str18864, ", sizeof(char));\n");
  setup = tmp_str18864;
  int tmp_strlen18836 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18836 = calloc(tmp_strlen18836, sizeof(char));
  strcpy(tmp_str18836, setup);
  strcat(tmp_str18836, indent);
  int tmp_strlen18822 = strlen(tmp_str18836) + strlen("strncpy(") + 1;
  char* tmp_str18822 = calloc(tmp_strlen18822, sizeof(char));
  strcpy(tmp_str18822, tmp_str18836);
  strcat(tmp_str18822, "strncpy(");
  int tmp_strlen18811 = strlen(tmp_str18822) + strlen(tmp_str) + 1;
  char* tmp_str18811 = calloc(tmp_strlen18811, sizeof(char));
  strcpy(tmp_str18811, tmp_str18822);
  strcat(tmp_str18811, tmp_str);
  int tmp_strlen18803 = strlen(tmp_str18811) + strlen(", ") + 1;
  char* tmp_str18803 = calloc(tmp_strlen18803, sizeof(char));
  strcpy(tmp_str18803, tmp_str18811);
  strcat(tmp_str18803, ", ");
  int tmp_strlen18793 = strlen(tmp_str18803) + strlen(strvar) + 1;
  char* tmp_str18793 = calloc(tmp_strlen18793, sizeof(char));
  strcpy(tmp_str18793, tmp_str18803);
  strcat(tmp_str18793, strvar);
  int tmp_strlen18784 = strlen(tmp_str18793) + strlen(" + ") + 1;
  char* tmp_str18784 = calloc(tmp_strlen18784, sizeof(char));
  strcpy(tmp_str18784, tmp_str18793);
  strcat(tmp_str18784, " + ");
  int tmp_strlen18772 = strlen(tmp_str18784) + strlen(low_expr) + 1;
  char* tmp_str18772 = calloc(tmp_strlen18772, sizeof(char));
  strcpy(tmp_str18772, tmp_str18784);
  strcat(tmp_str18772, low_expr);
  int tmp_strlen18764 = strlen(tmp_str18772) + strlen(", ") + 1;
  char* tmp_str18764 = calloc(tmp_strlen18764, sizeof(char));
  strcpy(tmp_str18764, tmp_str18772);
  strcat(tmp_str18764, ", ");
  int tmp_strlen18750 = strlen(tmp_str18764) + strlen(tmp_strlen) + 1;
  char* tmp_str18750 = calloc(tmp_strlen18750, sizeof(char));
  strcpy(tmp_str18750, tmp_str18764);
  strcat(tmp_str18750, tmp_strlen);
  int tmp_strlen18736 = strlen(tmp_str18750) + strlen(" - 1);\n") + 1;
  char* tmp_str18736 = calloc(tmp_strlen18736, sizeof(char));
  strcpy(tmp_str18736, tmp_str18750);
  strcat(tmp_str18736, " - 1);\n");
  setup = tmp_str18736;
  int tmp_strlen18708 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str18708 = calloc(tmp_strlen18708, sizeof(char));
  strcpy(tmp_str18708, setup);
  strcat(tmp_str18708, indent);
  int tmp_strlen18697 = strlen(tmp_str18708) + strlen(tmp_str) + 1;
  char* tmp_str18697 = calloc(tmp_strlen18697, sizeof(char));
  strcpy(tmp_str18697, tmp_str18708);
  strcat(tmp_str18697, tmp_str);
  int tmp_strlen18690 = strlen(tmp_str18697) + strlen("[") + 1;
  char* tmp_str18690 = calloc(tmp_strlen18690, sizeof(char));
  strcpy(tmp_str18690, tmp_str18697);
  strcat(tmp_str18690, "[");
  int tmp_strlen18676 = strlen(tmp_str18690) + strlen(tmp_strlen) + 1;
  char* tmp_str18676 = calloc(tmp_strlen18676, sizeof(char));
  strcpy(tmp_str18676, tmp_str18690);
  strcat(tmp_str18676, tmp_strlen);
  int tmp_strlen18658 = strlen(tmp_str18676) + strlen(" - 1] = 0;\n") + 1;
  char* tmp_str18658 = calloc(tmp_strlen18658, sizeof(char));
  strcpy(tmp_str18658, tmp_str18676);
  strcat(tmp_str18658, " - 1] = 0;\n");
  setup = tmp_str18658;
  return (TranslateSubstrExpr_results){src, setup, tmp_str};
}

TranslateOperand_results TranslateOperand(char* src, char* indent) {
  int tok;
  char* tok_str;
  Peek_results tmp_results18499 = Peek(src);
  tok = tmp_results18499.result1;
  tok_str = tmp_results18499.result2;
  if ((tok) == (TOK_LPAREN)) {
    char* setup;
    char* val;
    ConsumeToken_results tmp_results18389 = ConsumeToken(src, TOK_LPAREN);
    src = tmp_results18389.result1;
    tok_str = tmp_results18389.result2;
    TranslateExpr_results tmp_results18336 = TranslateExpr(src, indent);
    src = tmp_results18336.result1;
    setup = tmp_results18336.result2;
    val = tmp_results18336.result3;
    ConsumeToken_results tmp_results18283 = ConsumeToken(src, TOK_RPAREN);
    src = tmp_results18283.result1;
    tok_str = tmp_results18283.result2;
    return (TranslateOperand_results){src, setup, val};
  } else {
    if (((tok) == (TOK_FALSE)) || ((tok) == (TOK_TRUE))) {
      char* lit;
      TranslateBoolLiteral_results tmp_results18123 = TranslateBoolLiteral(src);
      src = tmp_results18123.result1;
      lit = tmp_results18123.result2;
      return (TranslateOperand_results){src, "", lit};
    } else {
      if ((tok) == (TOK_INTLIT)) {
        char* lit;
        TranslateIntLiteral_results tmp_results17992 = TranslateIntLiteral(src);
        src = tmp_results17992.result1;
        lit = tmp_results17992.result2;
        return (TranslateOperand_results){src, "", lit};
      } else {
        if ((tok) == (TOK_STRLIT)) {
          char* lit;
          TranslateStringLiteral_results tmp_results17862 = TranslateStringLiteral(src);
          src = tmp_results17862.result1;
          lit = tmp_results17862.result2;
          return (TranslateOperand_results){src, "", lit};
        } else {
          if ((tok) == (TOK_IDENT)) {
            char* ident;
            ConsumeIdent_results tmp_results17728 = ConsumeIdent(src);
            src = tmp_results17728.result1;
            ident = tmp_results17728.result2;
            Peek_results tmp_results17689 = Peek(src);
            tok = tmp_results17689.result1;
            tok_str = tmp_results17689.result2;
            if ((tok) == (TOK_LPAREN)) {
              char* setup;
              char* expr;
              TranslateCall_results tmp_results17562 = TranslateCall(src, indent, ident);
              src = tmp_results17562.result1;
              setup = tmp_results17562.result2;
              expr = tmp_results17562.result3;
              return (TranslateOperand_results){src, setup, expr};
            } else {
              if ((tok) == (TOK_LBRACKET)) {
                char* setup;
                char* expr;
                TranslateSubstrExpr_results tmp_results17362 = TranslateSubstrExpr(src, indent, ident);
                src = tmp_results17362.result1;
                setup = tmp_results17362.result2;
                expr = tmp_results17362.result3;
                return (TranslateOperand_results){src, setup, expr};
              } else {
                return (TranslateOperand_results){src, "", ident};
              }
            }
          } else {
            int tmp_strlen17142 = strlen("unexpected expr, got: ") + strlen(itoa(tok)) + 1;
            char* tmp_str17142 = calloc(tmp_strlen17142, sizeof(char));
            strcpy(tmp_str17142, "unexpected expr, got: ");
            strcat(tmp_str17142, itoa(tok));
            int tmp_strlen17133 = strlen(tmp_str17142) + strlen(" \"") + 1;
            char* tmp_str17133 = calloc(tmp_strlen17133, sizeof(char));
            strcpy(tmp_str17133, tmp_str17142);
            strcat(tmp_str17133, " \"");
            int tmp_strlen17122 = strlen(tmp_str17133) + strlen(tok_str) + 1;
            char* tmp_str17122 = calloc(tmp_strlen17122, sizeof(char));
            strcpy(tmp_str17122, tmp_str17133);
            strcat(tmp_str17122, tok_str);
            int tmp_strlen17114 = strlen(tmp_str17122) + strlen("\"") + 1;
            char* tmp_str17114 = calloc(tmp_strlen17114, sizeof(char));
            strcpy(tmp_str17114, tmp_str17122);
            strcat(tmp_str17114, "\"");
            printf("%s", tmp_str17114);
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
  Peek_results tmp_results16961 = Peek(src);
  tok = tmp_results16961.result1;
  tok_str = tmp_results16961.result2;
  if (IsUnaryOp(tok)) {
    ConsumeToken_results tmp_results16904 = ConsumeToken(src, tok);
    src = tmp_results16904.result1;
    tok_str = tmp_results16904.result2;
    char* setup;
    char* val;
    TranslateExpr_results tmp_results16808 = TranslateExpr(src, indent);
    src = tmp_results16808.result1;
    setup = tmp_results16808.result2;
    val = tmp_results16808.result3;
    int tmp_strlen16735 = strlen(tok_str) + strlen("(") + 1;
    char* tmp_str16735 = calloc(tmp_strlen16735, sizeof(char));
    strcpy(tmp_str16735, tok_str);
    strcat(tmp_str16735, "(");
    int tmp_strlen16728 = strlen(tmp_str16735) + strlen(val) + 1;
    char* tmp_str16728 = calloc(tmp_strlen16728, sizeof(char));
    strcpy(tmp_str16728, tmp_str16735);
    strcat(tmp_str16728, val);
    int tmp_strlen16721 = strlen(tmp_str16728) + strlen(")") + 1;
    char* tmp_str16721 = calloc(tmp_strlen16721, sizeof(char));
    strcpy(tmp_str16721, tmp_str16728);
    strcat(tmp_str16721, ")");
    val = tmp_str16721;
    return (TranslateUnaryExpr_results){src, setup, val};
  } else {
    char* setup;
    char* expr;
    TranslateOperand_results tmp_results16617 = TranslateOperand(src, indent);
    src = tmp_results16617.result1;
    setup = tmp_results16617.result2;
    expr = tmp_results16617.result3;
    return (TranslateUnaryExpr_results){src, setup, expr};
  }
}

TranslateExprWithPrecedence_results TranslateExprWithPrecedence(char* src, char* indent, int precedence) {
  char* setup;
  char* val;
  TranslateUnaryExpr_results tmp_results16374 = TranslateUnaryExpr(src, indent);
  src = tmp_results16374.result1;
  setup = tmp_results16374.result2;
  val = tmp_results16374.result3;
  int op;
  char* op_str;
  Peek_results tmp_results16281 = Peek(src);
  op = tmp_results16281.result1;
  op_str = tmp_results16281.result2;
  while ((IsBinaryOp(op)) && ((Precedence(op)) > (precedence))) {
    ConsumeToken_results tmp_results16194 = ConsumeToken(src, op);
    src = tmp_results16194.result1;
    op_str = tmp_results16194.result2;
    int tok;
    char* tok_str;
    Peek_results tmp_results16101 = Peek(src);
    tok = tmp_results16101.result1;
    tok_str = tmp_results16101.result2;
    while ((tok) == (TOK_NEWLINE)) {
      ConsumeToken_results tmp_results16031 = ConsumeToken(src, TOK_NEWLINE);
      src = tmp_results16031.result1;
      tok_str = tmp_results16031.result2;
      Peek_results tmp_results15973 = Peek(src);
      tok = tmp_results15973.result1;
      tok_str = tmp_results15973.result2;
    }
    char* setup_b;
    char* val_b;
    TranslateExprWithPrecedence_results tmp_results15876 = TranslateExprWithPrecedence(src, indent, Precedence(op));
    src = tmp_results15876.result1;
    setup_b = tmp_results15876.result2;
    val_b = tmp_results15876.result3;
    int tmp_strlen15765 = strlen(setup) + strlen(setup_b) + 1;
    char* tmp_str15765 = calloc(tmp_strlen15765, sizeof(char));
    strcpy(tmp_str15765, setup);
    strcat(tmp_str15765, setup_b);
    setup = tmp_str15765;
    if ((op) == (TOK_STRCAT)) {
      int tmp_strlen15673 = strlen("tmp_str") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15673 = calloc(tmp_strlen15673, sizeof(char));
      strcpy(tmp_str15673, "tmp_str");
      strcat(tmp_str15673, itoa(strlen(src)));
      char* tmp_str = tmp_str15673;
      int tmp_strlen15605 = strlen("tmp_strlen") + strlen(itoa(strlen(src))) + 1;
      char* tmp_str15605 = calloc(tmp_strlen15605, sizeof(char));
      strcpy(tmp_str15605, "tmp_strlen");
      strcat(tmp_str15605, itoa(strlen(src)));
      char* tmp_strlen = tmp_str15605;
      int tmp_strlen15569 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15569 = calloc(tmp_strlen15569, sizeof(char));
      strcpy(tmp_str15569, setup);
      strcat(tmp_str15569, indent);
      int tmp_strlen15559 = strlen(tmp_str15569) + strlen("int ") + 1;
      char* tmp_str15559 = calloc(tmp_strlen15559, sizeof(char));
      strcpy(tmp_str15559, tmp_str15569);
      strcat(tmp_str15559, "int ");
      int tmp_strlen15545 = strlen(tmp_str15559) + strlen(tmp_strlen) + 1;
      char* tmp_str15545 = calloc(tmp_strlen15545, sizeof(char));
      strcpy(tmp_str15545, tmp_str15559);
      strcat(tmp_str15545, tmp_strlen);
      int tmp_strlen15529 = strlen(tmp_str15545) + strlen(" = strlen(") + 1;
      char* tmp_str15529 = calloc(tmp_strlen15529, sizeof(char));
      strcpy(tmp_str15529, tmp_str15545);
      strcat(tmp_str15529, " = strlen(");
      int tmp_strlen15522 = strlen(tmp_str15529) + strlen(val) + 1;
      char* tmp_str15522 = calloc(tmp_strlen15522, sizeof(char));
      strcpy(tmp_str15522, tmp_str15529);
      strcat(tmp_str15522, val);
      int tmp_strlen15505 = strlen(tmp_str15522) + strlen(") + strlen(") + 1;
      char* tmp_str15505 = calloc(tmp_strlen15505, sizeof(char));
      strcpy(tmp_str15505, tmp_str15522);
      strcat(tmp_str15505, ") + strlen(");
      int tmp_strlen15496 = strlen(tmp_str15505) + strlen(val_b) + 1;
      char* tmp_str15496 = calloc(tmp_strlen15496, sizeof(char));
      strcpy(tmp_str15496, tmp_str15505);
      strcat(tmp_str15496, val_b);
      int tmp_strlen15482 = strlen(tmp_str15496) + strlen(") + 1;\n") + 1;
      char* tmp_str15482 = calloc(tmp_strlen15482, sizeof(char));
      strcpy(tmp_str15482, tmp_str15496);
      strcat(tmp_str15482, ") + 1;\n");
      setup = tmp_str15482;
      int tmp_strlen15446 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15446 = calloc(tmp_strlen15446, sizeof(char));
      strcpy(tmp_str15446, setup);
      strcat(tmp_str15446, indent);
      int tmp_strlen15434 = strlen(tmp_str15446) + strlen("char* ") + 1;
      char* tmp_str15434 = calloc(tmp_strlen15434, sizeof(char));
      strcpy(tmp_str15434, tmp_str15446);
      strcat(tmp_str15434, "char* ");
      int tmp_strlen15423 = strlen(tmp_str15434) + strlen(tmp_str) + 1;
      char* tmp_str15423 = calloc(tmp_strlen15423, sizeof(char));
      strcpy(tmp_str15423, tmp_str15434);
      strcat(tmp_str15423, tmp_str);
      int tmp_strlen15407 = strlen(tmp_str15423) + strlen(" = calloc(") + 1;
      char* tmp_str15407 = calloc(tmp_strlen15407, sizeof(char));
      strcpy(tmp_str15407, tmp_str15423);
      strcat(tmp_str15407, " = calloc(");
      int tmp_strlen15393 = strlen(tmp_str15407) + strlen(tmp_strlen) + 1;
      char* tmp_str15393 = calloc(tmp_strlen15393, sizeof(char));
      strcpy(tmp_str15393, tmp_str15407);
      strcat(tmp_str15393, tmp_strlen);
      int tmp_strlen15369 = strlen(tmp_str15393) + strlen(", sizeof(char));\n") + 1;
      char* tmp_str15369 = calloc(tmp_strlen15369, sizeof(char));
      strcpy(tmp_str15369, tmp_str15393);
      strcat(tmp_str15369, ", sizeof(char));\n");
      setup = tmp_str15369;
      int tmp_strlen15333 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15333 = calloc(tmp_strlen15333, sizeof(char));
      strcpy(tmp_str15333, setup);
      strcat(tmp_str15333, indent);
      int tmp_strlen15320 = strlen(tmp_str15333) + strlen("strcpy(") + 1;
      char* tmp_str15320 = calloc(tmp_strlen15320, sizeof(char));
      strcpy(tmp_str15320, tmp_str15333);
      strcat(tmp_str15320, "strcpy(");
      int tmp_strlen15309 = strlen(tmp_str15320) + strlen(tmp_str) + 1;
      char* tmp_str15309 = calloc(tmp_strlen15309, sizeof(char));
      strcpy(tmp_str15309, tmp_str15320);
      strcat(tmp_str15309, tmp_str);
      int tmp_strlen15301 = strlen(tmp_str15309) + strlen(", ") + 1;
      char* tmp_str15301 = calloc(tmp_strlen15301, sizeof(char));
      strcpy(tmp_str15301, tmp_str15309);
      strcat(tmp_str15301, ", ");
      int tmp_strlen15294 = strlen(tmp_str15301) + strlen(val) + 1;
      char* tmp_str15294 = calloc(tmp_strlen15294, sizeof(char));
      strcpy(tmp_str15294, tmp_str15301);
      strcat(tmp_str15294, val);
      int tmp_strlen15284 = strlen(tmp_str15294) + strlen(");\n") + 1;
      char* tmp_str15284 = calloc(tmp_strlen15284, sizeof(char));
      strcpy(tmp_str15284, tmp_str15294);
      strcat(tmp_str15284, ");\n");
      setup = tmp_str15284;
      int tmp_strlen15248 = strlen(setup) + strlen(indent) + 1;
      char* tmp_str15248 = calloc(tmp_strlen15248, sizeof(char));
      strcpy(tmp_str15248, setup);
      strcat(tmp_str15248, indent);
      int tmp_strlen15235 = strlen(tmp_str15248) + strlen("strcat(") + 1;
      char* tmp_str15235 = calloc(tmp_strlen15235, sizeof(char));
      strcpy(tmp_str15235, tmp_str15248);
      strcat(tmp_str15235, "strcat(");
      int tmp_strlen15224 = strlen(tmp_str15235) + strlen(tmp_str) + 1;
      char* tmp_str15224 = calloc(tmp_strlen15224, sizeof(char));
      strcpy(tmp_str15224, tmp_str15235);
      strcat(tmp_str15224, tmp_str);
      int tmp_strlen15216 = strlen(tmp_str15224) + strlen(", ") + 1;
      char* tmp_str15216 = calloc(tmp_strlen15216, sizeof(char));
      strcpy(tmp_str15216, tmp_str15224);
      strcat(tmp_str15216, ", ");
      int tmp_strlen15207 = strlen(tmp_str15216) + strlen(val_b) + 1;
      char* tmp_str15207 = calloc(tmp_strlen15207, sizeof(char));
      strcpy(tmp_str15207, tmp_str15216);
      strcat(tmp_str15207, val_b);
      int tmp_strlen15197 = strlen(tmp_str15207) + strlen(");\n") + 1;
      char* tmp_str15197 = calloc(tmp_strlen15197, sizeof(char));
      strcpy(tmp_str15197, tmp_str15207);
      strcat(tmp_str15197, ");\n");
      setup = tmp_str15197;
      val = tmp_str;
    } else {
      if ((op) == (TOK_STREQ)) {
        int tmp_strlen15099 = strlen("(strcmp(") + strlen(val) + 1;
        char* tmp_str15099 = calloc(tmp_strlen15099, sizeof(char));
        strcpy(tmp_str15099, "(strcmp(");
        strcat(tmp_str15099, val);
        int tmp_strlen15091 = strlen(tmp_str15099) + strlen(", ") + 1;
        char* tmp_str15091 = calloc(tmp_strlen15091, sizeof(char));
        strcpy(tmp_str15091, tmp_str15099);
        strcat(tmp_str15091, ", ");
        int tmp_strlen15082 = strlen(tmp_str15091) + strlen(val_b) + 1;
        char* tmp_str15082 = calloc(tmp_strlen15082, sizeof(char));
        strcpy(tmp_str15082, tmp_str15091);
        strcat(tmp_str15082, val_b);
        int tmp_strlen15069 = strlen(tmp_str15082) + strlen(") == 0)") + 1;
        char* tmp_str15069 = calloc(tmp_strlen15069, sizeof(char));
        strcpy(tmp_str15069, tmp_str15082);
        strcat(tmp_str15069, ") == 0)");
        val = tmp_str15069;
      } else {
        if ((op) == (TOK_STRNEQ)) {
          int tmp_strlen14996 = strlen("(strcmp(") + strlen(val) + 1;
          char* tmp_str14996 = calloc(tmp_strlen14996, sizeof(char));
          strcpy(tmp_str14996, "(strcmp(");
          strcat(tmp_str14996, val);
          int tmp_strlen14988 = strlen(tmp_str14996) + strlen(", ") + 1;
          char* tmp_str14988 = calloc(tmp_strlen14988, sizeof(char));
          strcpy(tmp_str14988, tmp_str14996);
          strcat(tmp_str14988, ", ");
          int tmp_strlen14979 = strlen(tmp_str14988) + strlen(val_b) + 1;
          char* tmp_str14979 = calloc(tmp_strlen14979, sizeof(char));
          strcpy(tmp_str14979, tmp_str14988);
          strcat(tmp_str14979, val_b);
          int tmp_strlen14966 = strlen(tmp_str14979) + strlen(") != 0)") + 1;
          char* tmp_str14966 = calloc(tmp_strlen14966, sizeof(char));
          strcpy(tmp_str14966, tmp_str14979);
          strcat(tmp_str14966, ") != 0)");
          val = tmp_str14966;
        } else {
          int tmp_strlen14920 = strlen("(") + strlen(val) + 1;
          char* tmp_str14920 = calloc(tmp_strlen14920, sizeof(char));
          strcpy(tmp_str14920, "(");
          strcat(tmp_str14920, val);
          int tmp_strlen14912 = strlen(tmp_str14920) + strlen(") ") + 1;
          char* tmp_str14912 = calloc(tmp_strlen14912, sizeof(char));
          strcpy(tmp_str14912, tmp_str14920);
          strcat(tmp_str14912, ") ");
          int tmp_strlen14902 = strlen(tmp_str14912) + strlen(op_str) + 1;
          char* tmp_str14902 = calloc(tmp_strlen14902, sizeof(char));
          strcpy(tmp_str14902, tmp_str14912);
          strcat(tmp_str14902, op_str);
          int tmp_strlen14894 = strlen(tmp_str14902) + strlen(" (") + 1;
          char* tmp_str14894 = calloc(tmp_strlen14894, sizeof(char));
          strcpy(tmp_str14894, tmp_str14902);
          strcat(tmp_str14894, " (");
          int tmp_strlen14885 = strlen(tmp_str14894) + strlen(val_b) + 1;
          char* tmp_str14885 = calloc(tmp_strlen14885, sizeof(char));
          strcpy(tmp_str14885, tmp_str14894);
          strcat(tmp_str14885, val_b);
          int tmp_strlen14878 = strlen(tmp_str14885) + strlen(")") + 1;
          char* tmp_str14878 = calloc(tmp_strlen14878, sizeof(char));
          strcpy(tmp_str14878, tmp_str14885);
          strcat(tmp_str14878, ")");
          val = tmp_str14878;
        }
      }
    }
    Peek_results tmp_results14859 = Peek(src);
    op = tmp_results14859.result1;
    tok_str = tmp_results14859.result2;
  }
  return (TranslateExprWithPrecedence_results){src, setup, val};
}

TranslateExpr_results TranslateExpr(char* src, char* indent) {
  char* setup;
  char* expr;
  TranslateExprWithPrecedence_results tmp_results14676 = TranslateExprWithPrecedence(src, indent, 0);
  src = tmp_results14676.result1;
  setup = tmp_results14676.result2;
  expr = tmp_results14676.result3;
  return (TranslateExpr_results){src, setup, expr};
}

TranslateExprs_results TranslateExprs(char* src, char* indent) {
  char* expr_setup;
  char* expr_value;
  TranslateExpr_results tmp_results14442 = TranslateExpr(src, indent);
  src = tmp_results14442.result1;
  expr_setup = tmp_results14442.result2;
  expr_value = tmp_results14442.result3;
  int tok;
  char* tok_str;
  Peek_results tmp_results14340 = Peek(src);
  tok = tmp_results14340.result1;
  tok_str = tmp_results14340.result2;
  int exprs_count = 1;
  char* exprs_setup = expr_setup;
  char* exprs_value = expr_value;
  while ((tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results14169 = ConsumeToken(src, TOK_COMMA);
    src = tmp_results14169.result1;
    tok_str = tmp_results14169.result2;
    TranslateExpr_results tmp_results14117 = TranslateExpr(src, indent);
    src = tmp_results14117.result1;
    expr_setup = tmp_results14117.result2;
    expr_value = tmp_results14117.result3;
    exprs_count = (exprs_count) + (1);
    int tmp_strlen13975 = strlen(exprs_setup) + strlen(expr_setup) + 1;
    char* tmp_str13975 = calloc(tmp_strlen13975, sizeof(char));
    strcpy(tmp_str13975, exprs_setup);
    strcat(tmp_str13975, expr_setup);
    exprs_setup = tmp_str13975;
    int tmp_strlen13933 = strlen(exprs_value) + strlen(", ") + 1;
    char* tmp_str13933 = calloc(tmp_strlen13933, sizeof(char));
    strcpy(tmp_str13933, exprs_value);
    strcat(tmp_str13933, ", ");
    int tmp_strlen13919 = strlen(tmp_str13933) + strlen(expr_value) + 1;
    char* tmp_str13919 = calloc(tmp_strlen13919, sizeof(char));
    strcpy(tmp_str13919, tmp_str13933);
    strcat(tmp_str13919, expr_value);
    exprs_value = tmp_str13919;
    Peek_results tmp_results13910 = Peek(src);
    tok = tmp_results13910.result1;
    tok_str = tmp_results13910.result2;
  }
  return (TranslateExprs_results){src, exprs_count, exprs_setup, exprs_value};
}

TranslateConstOrVar_results TranslateConstOrVar(char* src) {
  char* name;
  ConsumeIdent_results tmp_results13739 = ConsumeIdent(src);
  src = tmp_results13739.result1;
  name = tmp_results13739.result2;
  char* tok_str;
  ConsumeToken_results tmp_results13681 = ConsumeToken(src, TOK_COLON);
  src = tmp_results13681.result1;
  tok_str = tmp_results13681.result2;
  int typ;
  char* typ_str;
  TranslateType_results tmp_results13592 = TranslateType(src);
  src = tmp_results13592.result1;
  typ = tmp_results13592.result2;
  typ_str = tmp_results13592.result3;
  int tmp_strlen13517 = strlen(typ_str) + strlen(" ") + 1;
  char* tmp_str13517 = calloc(tmp_strlen13517, sizeof(char));
  strcpy(tmp_str13517, typ_str);
  strcat(tmp_str13517, " ");
  int tmp_strlen13509 = strlen(tmp_str13517) + strlen(name) + 1;
  char* tmp_str13509 = calloc(tmp_strlen13509, sizeof(char));
  strcpy(tmp_str13509, tmp_str13517);
  strcat(tmp_str13509, name);
  char* out = tmp_str13509;
  return (TranslateConstOrVar_results){src, out};
}

TranslateConstDecl_results TranslateConstDecl(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results13384 = ConsumeToken(src, TOK_LET);
  src = tmp_results13384.result1;
  tok_str = tmp_results13384.result2;
  char* out;
  TranslateConstOrVar_results tmp_results13318 = TranslateConstOrVar(src);
  src = tmp_results13318.result1;
  out = tmp_results13318.result2;
  int tmp_strlen13257 = strlen("const ") + strlen(out) + 1;
  char* tmp_str13257 = calloc(tmp_strlen13257, sizeof(char));
  strcpy(tmp_str13257, "const ");
  strcat(tmp_str13257, out);
  out = tmp_str13257;
  ConsumeToken_results tmp_results13252 = ConsumeToken(src, TOK_ASSIGN);
  src = tmp_results13252.result1;
  tok_str = tmp_results13252.result2;
  char* setup;
  char* val;
  TranslateExpr_results tmp_results13161 = TranslateExpr(src, indent);
  src = tmp_results13161.result1;
  setup = tmp_results13161.result2;
  val = tmp_results13161.result3;
  ConsumeToken_results tmp_results13112 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results13112.result1;
  tok_str = tmp_results13112.result2;
  int tmp_strlen13044 = strlen(out) + strlen(" = ") + 1;
  char* tmp_str13044 = calloc(tmp_strlen13044, sizeof(char));
  strcpy(tmp_str13044, out);
  strcat(tmp_str13044, " = ");
  int tmp_strlen13037 = strlen(tmp_str13044) + strlen(val) + 1;
  char* tmp_str13037 = calloc(tmp_strlen13037, sizeof(char));
  strcpy(tmp_str13037, tmp_str13044);
  strcat(tmp_str13037, val);
  int tmp_strlen13028 = strlen(tmp_str13037) + strlen(";\n") + 1;
  char* tmp_str13028 = calloc(tmp_strlen13028, sizeof(char));
  strcpy(tmp_str13028, tmp_str13037);
  strcat(tmp_str13028, ";\n");
  out = tmp_str13028;
  return (TranslateConstDecl_results){src, out};
}

TranslateConstDeclStmt_results TranslateConstDeclStmt(char* src, char* indent) {
  char* out;
  TranslateConstDecl_results tmp_results12903 = TranslateConstDecl(src, indent);
  src = tmp_results12903.result1;
  out = tmp_results12903.result2;
  int tmp_strlen12831 = strlen(indent) + strlen(out) + 1;
  char* tmp_str12831 = calloc(tmp_strlen12831, sizeof(char));
  strcpy(tmp_str12831, indent);
  strcat(tmp_str12831, out);
  return (TranslateConstDeclStmt_results){src, tmp_str12831};
}

TranslateVarDeclStmt_results TranslateVarDeclStmt(char* src, char* indent) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results12707 = ConsumeToken(src, TOK_VAR);
  src = tmp_results12707.result1;
  tok_str = tmp_results12707.result2;
  char* setup = "";
  char* val;
  char* out;
  TranslateConstOrVar_results tmp_results12594 = TranslateConstOrVar(src);
  src = tmp_results12594.result1;
  out = tmp_results12594.result2;
  Peek_results tmp_results12554 = Peek(src);
  tok = tmp_results12554.result1;
  tok_str = tmp_results12554.result2;
  if ((tok) == (TOK_ASSIGN)) {
    ConsumeToken_results tmp_results12494 = ConsumeToken(src, TOK_ASSIGN);
    src = tmp_results12494.result1;
    tok_str = tmp_results12494.result2;
    TranslateExpr_results tmp_results12441 = TranslateExpr(src, indent);
    src = tmp_results12441.result1;
    setup = tmp_results12441.result2;
    val = tmp_results12441.result3;
    ConsumeToken_results tmp_results12388 = ConsumeToken(src, TOK_NEWLINE);
    src = tmp_results12388.result1;
    tok_str = tmp_results12388.result2;
    int tmp_strlen12316 = strlen(out) + strlen(" = ") + 1;
    char* tmp_str12316 = calloc(tmp_strlen12316, sizeof(char));
    strcpy(tmp_str12316, out);
    strcat(tmp_str12316, " = ");
    int tmp_strlen12309 = strlen(tmp_str12316) + strlen(val) + 1;
    char* tmp_str12309 = calloc(tmp_strlen12309, sizeof(char));
    strcpy(tmp_str12309, tmp_str12316);
    strcat(tmp_str12309, val);
    out = tmp_str12309;
  }
  int tmp_strlen12277 = strlen(setup) + strlen(indent) + 1;
  char* tmp_str12277 = calloc(tmp_strlen12277, sizeof(char));
  strcpy(tmp_str12277, setup);
  strcat(tmp_str12277, indent);
  int tmp_strlen12270 = strlen(tmp_str12277) + strlen(out) + 1;
  char* tmp_str12270 = calloc(tmp_strlen12270, sizeof(char));
  strcpy(tmp_str12270, tmp_str12277);
  strcat(tmp_str12270, out);
  int tmp_strlen12261 = strlen(tmp_str12270) + strlen(";\n") + 1;
  char* tmp_str12261 = calloc(tmp_strlen12261, sizeof(char));
  strcpy(tmp_str12261, tmp_str12270);
  strcat(tmp_str12261, ";\n");
  out = tmp_str12261;
  return (TranslateVarDeclStmt_results){src, out};
}

TranslateAssignStmt_results TranslateAssignStmt(char* src, char* indent) {
  int x = Find(src, "=");
  int tmp_strlen12105 = (x) - (0) + 1;
  char* tmp_str12105 = calloc(tmp_strlen12105, sizeof(char));
  strncpy(tmp_str12105, src + 0, tmp_strlen12105 - 1);
  tmp_str12105[tmp_strlen12105 - 1] = 0;
  char* lhs = tmp_str12105;
  int tmp_strlen12072 = (strlen(src)) - ((x) + (1)) + 1;
  char* tmp_str12072 = calloc(tmp_strlen12072, sizeof(char));
  strncpy(tmp_str12072, src + (x) + (1), tmp_strlen12072 - 1);
  tmp_str12072[tmp_strlen12072 - 1] = 0;
  char* rhs = tmp_str12072;
  char* lhs_ident;
  ConsumeIdentOrUnderscore_results tmp_results12039 = ConsumeIdentOrUnderscore(lhs);
  lhs = tmp_results12039.result1;
  lhs_ident = tmp_results12039.result2;
  char* old_rhs = rhs;
  char* setup;
  char* rhs_expr;
  TranslateExpr_results tmp_results11911 = TranslateExpr(rhs, indent);
  rhs = tmp_results11911.result1;
  setup = tmp_results11911.result2;
  rhs_expr = tmp_results11911.result3;
  int lhs_tok;
  char* lhs_tok_str;
  int rhs_tok;
  char* rhs_tok_str;
  Peek_results tmp_results11759 = Peek(lhs);
  lhs_tok = tmp_results11759.result1;
  lhs_tok_str = tmp_results11759.result2;
  Peek_results tmp_results11722 = Peek(rhs);
  rhs_tok = tmp_results11722.result1;
  rhs_tok_str = tmp_results11722.result2;
  if (((lhs_tok) == (TOK_COMMA)) && ((rhs_tok) != (TOK_COMMA))) {
    char* func_name;
    ConsumeIdent_results tmp_results11597 = ConsumeIdent(old_rhs);
    old_rhs = tmp_results11597.result1;
    func_name = tmp_results11597.result2;
    int tmp_strlen11489 = strlen("tmp_results") + strlen(itoa(strlen(src))) + 1;
    char* tmp_str11489 = calloc(tmp_strlen11489, sizeof(char));
    strcpy(tmp_str11489, "tmp_results");
    strcat(tmp_str11489, itoa(strlen(src)));
    char* tmp_results = tmp_str11489;
    char* out = setup;
    int tmp_strlen11429 = strlen(out) + strlen(indent) + 1;
    char* tmp_str11429 = calloc(tmp_strlen11429, sizeof(char));
    strcpy(tmp_str11429, out);
    strcat(tmp_str11429, indent);
    int tmp_strlen11416 = strlen(tmp_str11429) + strlen(func_name) + 1;
    char* tmp_str11416 = calloc(tmp_strlen11416, sizeof(char));
    strcpy(tmp_str11416, tmp_str11429);
    strcat(tmp_str11416, func_name);
    int tmp_strlen11401 = strlen(tmp_str11416) + strlen("_results ") + 1;
    char* tmp_str11401 = calloc(tmp_strlen11401, sizeof(char));
    strcpy(tmp_str11401, tmp_str11416);
    strcat(tmp_str11401, "_results ");
    int tmp_strlen11386 = strlen(tmp_str11401) + strlen(tmp_results) + 1;
    char* tmp_str11386 = calloc(tmp_strlen11386, sizeof(char));
    strcpy(tmp_str11386, tmp_str11401);
    strcat(tmp_str11386, tmp_results);
    int tmp_strlen11377 = strlen(tmp_str11386) + strlen(" = ") + 1;
    char* tmp_str11377 = calloc(tmp_strlen11377, sizeof(char));
    strcpy(tmp_str11377, tmp_str11386);
    strcat(tmp_str11377, " = ");
    int tmp_strlen11365 = strlen(tmp_str11377) + strlen(rhs_expr) + 1;
    char* tmp_str11365 = calloc(tmp_strlen11365, sizeof(char));
    strcpy(tmp_str11365, tmp_str11377);
    strcat(tmp_str11365, rhs_expr);
    int tmp_strlen11356 = strlen(tmp_str11365) + strlen(";\n") + 1;
    char* tmp_str11356 = calloc(tmp_strlen11356, sizeof(char));
    strcpy(tmp_str11356, tmp_str11365);
    strcat(tmp_str11356, ";\n");
    out = tmp_str11356;
    if ((strcmp(lhs_ident, "_") != 0)) {
      int tmp_strlen11293 = strlen(out) + strlen(indent) + 1;
      char* tmp_str11293 = calloc(tmp_strlen11293, sizeof(char));
      strcpy(tmp_str11293, out);
      strcat(tmp_str11293, indent);
      int tmp_strlen11280 = strlen(tmp_str11293) + strlen(lhs_ident) + 1;
      char* tmp_str11280 = calloc(tmp_strlen11280, sizeof(char));
      strcpy(tmp_str11280, tmp_str11293);
      strcat(tmp_str11280, lhs_ident);
      int tmp_strlen11271 = strlen(tmp_str11280) + strlen(" = ") + 1;
      char* tmp_str11271 = calloc(tmp_strlen11271, sizeof(char));
      strcpy(tmp_str11271, tmp_str11280);
      strcat(tmp_str11271, " = ");
      int tmp_strlen11256 = strlen(tmp_str11271) + strlen(tmp_results) + 1;
      char* tmp_str11256 = calloc(tmp_strlen11256, sizeof(char));
      strcpy(tmp_str11256, tmp_str11271);
      strcat(tmp_str11256, tmp_results);
      int tmp_strlen11239 = strlen(tmp_str11256) + strlen(".result1;\n") + 1;
      char* tmp_str11239 = calloc(tmp_strlen11239, sizeof(char));
      strcpy(tmp_str11239, tmp_str11256);
      strcat(tmp_str11239, ".result1;\n");
      out = tmp_str11239;
    }
    int result_count = 1;
    while ((lhs_tok) == (TOK_COMMA)) {
      result_count = (result_count) + (1);
      ConsumeToken_results tmp_results11103 = ConsumeToken(lhs, TOK_COMMA);
      lhs = tmp_results11103.result1;
      lhs_tok_str = tmp_results11103.result2;
      ConsumeIdentOrUnderscore_results tmp_results11043 = ConsumeIdentOrUnderscore(lhs);
      lhs = tmp_results11043.result1;
      lhs_ident = tmp_results11043.result2;
      if ((strcmp(lhs_ident, "_") != 0)) {
        int tmp_strlen10926 = strlen(out) + strlen(indent) + 1;
        char* tmp_str10926 = calloc(tmp_strlen10926, sizeof(char));
        strcpy(tmp_str10926, out);
        strcat(tmp_str10926, indent);
        int tmp_strlen10913 = strlen(tmp_str10926) + strlen(lhs_ident) + 1;
        char* tmp_str10913 = calloc(tmp_strlen10913, sizeof(char));
        strcpy(tmp_str10913, tmp_str10926);
        strcat(tmp_str10913, lhs_ident);
        int tmp_strlen10904 = strlen(tmp_str10913) + strlen(" = ") + 1;
        char* tmp_str10904 = calloc(tmp_strlen10904, sizeof(char));
        strcpy(tmp_str10904, tmp_str10913);
        strcat(tmp_str10904, " = ");
        int tmp_strlen10889 = strlen(tmp_str10904) + strlen(tmp_results) + 1;
        char* tmp_str10889 = calloc(tmp_strlen10889, sizeof(char));
        strcpy(tmp_str10889, tmp_str10904);
        strcat(tmp_str10889, tmp_results);
        int tmp_strlen10876 = strlen(tmp_str10889) + strlen(".result") + 1;
        char* tmp_str10876 = calloc(tmp_strlen10876, sizeof(char));
        strcpy(tmp_str10876, tmp_str10889);
        strcat(tmp_str10876, ".result");
        int tmp_strlen10854 = strlen(tmp_str10876) + strlen(itoa(result_count)) + 1;
        char* tmp_str10854 = calloc(tmp_strlen10854, sizeof(char));
        strcpy(tmp_str10854, tmp_str10876);
        strcat(tmp_str10854, itoa(result_count));
        int tmp_strlen10845 = strlen(tmp_str10854) + strlen(";\n") + 1;
        char* tmp_str10845 = calloc(tmp_strlen10845, sizeof(char));
        strcpy(tmp_str10845, tmp_str10854);
        strcat(tmp_str10845, ";\n");
        out = tmp_str10845;
      }
      Peek_results tmp_results10818 = Peek(lhs);
      lhs_tok = tmp_results10818.result1;
      lhs_tok_str = tmp_results10818.result2;
    }
    char* tok_str;
    ConsumeToken_results tmp_results10739 = ConsumeToken(rhs, TOK_NEWLINE);
    src = tmp_results10739.result1;
    tok_str = tmp_results10739.result2;
    return (TranslateAssignStmt_results){src, out};
  }
  int tmp_strlen10614 = strlen(indent) + strlen(lhs_ident) + 1;
  char* tmp_str10614 = calloc(tmp_strlen10614, sizeof(char));
  strcpy(tmp_str10614, indent);
  strcat(tmp_str10614, lhs_ident);
  int tmp_strlen10605 = strlen(tmp_str10614) + strlen(" = ") + 1;
  char* tmp_str10605 = calloc(tmp_strlen10605, sizeof(char));
  strcpy(tmp_str10605, tmp_str10614);
  strcat(tmp_str10605, " = ");
  int tmp_strlen10593 = strlen(tmp_str10605) + strlen(rhs_expr) + 1;
  char* tmp_str10593 = calloc(tmp_strlen10593, sizeof(char));
  strcpy(tmp_str10593, tmp_str10605);
  strcat(tmp_str10593, rhs_expr);
  int tmp_strlen10584 = strlen(tmp_str10593) + strlen(";\n") + 1;
  char* tmp_str10584 = calloc(tmp_strlen10584, sizeof(char));
  strcpy(tmp_str10584, tmp_str10593);
  strcat(tmp_str10584, ";\n");
  char* assignments = tmp_str10584;
  while ((lhs_tok) == (TOK_COMMA)) {
    ConsumeToken_results tmp_results10544 = ConsumeToken(lhs, TOK_COMMA);
    lhs = tmp_results10544.result1;
    lhs_tok_str = tmp_results10544.result2;
    ConsumeToken_results tmp_results10488 = ConsumeToken(rhs, TOK_COMMA);
    rhs = tmp_results10488.result1;
    rhs_tok_str = tmp_results10488.result2;
    ConsumeIdent_results tmp_results10432 = ConsumeIdent(lhs);
    lhs = tmp_results10432.result1;
    lhs_ident = tmp_results10432.result2;
    char* rhs_expr_setup;
    TranslateExpr_results tmp_results10354 = TranslateExpr(rhs, indent);
    rhs = tmp_results10354.result1;
    rhs_expr_setup = tmp_results10354.result2;
    rhs_expr = tmp_results10354.result3;
    int tmp_strlen10256 = strlen(setup) + strlen(rhs_expr_setup) + 1;
    char* tmp_str10256 = calloc(tmp_strlen10256, sizeof(char));
    strcpy(tmp_str10256, setup);
    strcat(tmp_str10256, rhs_expr_setup);
    setup = tmp_str10256;
    int tmp_strlen10212 = strlen(assignments) + strlen(indent) + 1;
    char* tmp_str10212 = calloc(tmp_strlen10212, sizeof(char));
    strcpy(tmp_str10212, assignments);
    strcat(tmp_str10212, indent);
    int tmp_strlen10199 = strlen(tmp_str10212) + strlen(lhs_ident) + 1;
    char* tmp_str10199 = calloc(tmp_strlen10199, sizeof(char));
    strcpy(tmp_str10199, tmp_str10212);
    strcat(tmp_str10199, lhs_ident);
    int tmp_strlen10190 = strlen(tmp_str10199) + strlen(" = ") + 1;
    char* tmp_str10190 = calloc(tmp_strlen10190, sizeof(char));
    strcpy(tmp_str10190, tmp_str10199);
    strcat(tmp_str10190, " = ");
    int tmp_strlen10178 = strlen(tmp_str10190) + strlen(rhs_expr) + 1;
    char* tmp_str10178 = calloc(tmp_strlen10178, sizeof(char));
    strcpy(tmp_str10178, tmp_str10190);
    strcat(tmp_str10178, rhs_expr);
    int tmp_strlen10169 = strlen(tmp_str10178) + strlen(";\n") + 1;
    char* tmp_str10169 = calloc(tmp_strlen10169, sizeof(char));
    strcpy(tmp_str10169, tmp_str10178);
    strcat(tmp_str10169, ";\n");
    assignments = tmp_str10169;
    Peek_results tmp_results10160 = Peek(lhs);
    lhs_tok = tmp_results10160.result1;
    lhs_tok_str = tmp_results10160.result2;
  }
  char* tok_str;
  ConsumeToken_results tmp_results10093 = ConsumeToken(rhs, TOK_NEWLINE);
  src = tmp_results10093.result1;
  tok_str = tmp_results10093.result2;
  int tmp_strlen10011 = strlen(setup) + strlen(assignments) + 1;
  char* tmp_str10011 = calloc(tmp_strlen10011, sizeof(char));
  strcpy(tmp_str10011, setup);
  strcat(tmp_str10011, assignments);
  return (TranslateAssignStmt_results){src, tmp_str10011};
}

TranslateIfStmt_results TranslateIfStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results9890 = ConsumeToken(src, TOK_IF);
  src = tmp_results9890.result1;
  tok_str = tmp_results9890.result2;
  char* cond_setup;
  char* cond;
  TranslateExpr_results tmp_results9797 = TranslateExpr(src, indent);
  src = tmp_results9797.result1;
  cond_setup = tmp_results9797.result2;
  cond = tmp_results9797.result3;
  ConsumeToken_results tmp_results9742 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results9742.result1;
  tok_str = tmp_results9742.result2;
  char* out = cond_setup;
  int tmp_strlen9641 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9641 = calloc(tmp_strlen9641, sizeof(char));
  strcpy(tmp_str9641, out);
  strcat(tmp_str9641, indent);
  int tmp_strlen9631 = strlen(tmp_str9641) + strlen("if (") + 1;
  char* tmp_str9631 = calloc(tmp_strlen9631, sizeof(char));
  strcpy(tmp_str9631, tmp_str9641);
  strcat(tmp_str9631, "if (");
  int tmp_strlen9623 = strlen(tmp_str9631) + strlen(cond) + 1;
  char* tmp_str9623 = calloc(tmp_strlen9623, sizeof(char));
  strcpy(tmp_str9623, tmp_str9631);
  strcat(tmp_str9623, cond);
  int tmp_strlen9612 = strlen(tmp_str9623) + strlen(") {\n") + 1;
  char* tmp_str9612 = calloc(tmp_strlen9612, sizeof(char));
  strcpy(tmp_str9612, tmp_str9623);
  strcat(tmp_str9612, ") {\n");
  out = tmp_str9612;
  char* body;
  int tmp_strlen9531 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str9531 = calloc(tmp_strlen9531, sizeof(char));
  strcpy(tmp_str9531, indent);
  strcat(tmp_str9531, SINGLE_INDENT);
  TranslateStmts_results tmp_results9586 = TranslateStmts(src, tmp_str9531, func_name);
  src = tmp_results9586.result1;
  body = tmp_results9586.result2;
  ConsumeToken_results tmp_results9514 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results9514.result1;
  tok_str = tmp_results9514.result2;
  int tmp_strlen9448 = strlen(out) + strlen(body) + 1;
  char* tmp_str9448 = calloc(tmp_strlen9448, sizeof(char));
  strcpy(tmp_str9448, out);
  strcat(tmp_str9448, body);
  out = tmp_str9448;
  int tmp_strlen9424 = strlen(out) + strlen(indent) + 1;
  char* tmp_str9424 = calloc(tmp_strlen9424, sizeof(char));
  strcpy(tmp_str9424, out);
  strcat(tmp_str9424, indent);
  int tmp_strlen9417 = strlen(tmp_str9424) + strlen("}") + 1;
  char* tmp_str9417 = calloc(tmp_strlen9417, sizeof(char));
  strcpy(tmp_str9417, tmp_str9424);
  strcat(tmp_str9417, "}");
  out = tmp_str9417;
  int tok;
  Peek_results tmp_results9395 = Peek(src);
  tok = tmp_results9395.result1;
  tok_str = tmp_results9395.result2;
  if ((tok) != (TOK_ELSE)) {
    int tmp_strlen9314 = strlen(out) + strlen("\n") + 1;
    char* tmp_str9314 = calloc(tmp_strlen9314, sizeof(char));
    strcpy(tmp_str9314, out);
    strcat(tmp_str9314, "\n");
    return (TranslateIfStmt_results){src, tmp_str9314};
  }
  ConsumeToken_results tmp_results9303 = ConsumeToken(src, TOK_ELSE);
  src = tmp_results9303.result1;
  tok_str = tmp_results9303.result2;
  Peek_results tmp_results9256 = Peek(src);
  tok = tmp_results9256.result1;
  tok_str = tmp_results9256.result2;
  char* else_out;
  if ((tok) == (TOK_IF)) {
    int tmp_strlen9115 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str9115 = calloc(tmp_strlen9115, sizeof(char));
    strcpy(tmp_str9115, indent);
    strcat(tmp_str9115, SINGLE_INDENT);
    TranslateIfStmt_results tmp_results9175 = TranslateIfStmt(src, tmp_str9115, func_name);
    src = tmp_results9175.result1;
    else_out = tmp_results9175.result2;
    int tmp_strlen9070 = strlen(out) + strlen(" else {\n") + 1;
    char* tmp_str9070 = calloc(tmp_strlen9070, sizeof(char));
    strcpy(tmp_str9070, out);
    strcat(tmp_str9070, " else {\n");
    out = tmp_str9070;
    int tmp_strlen9040 = strlen(out) + strlen(else_out) + 1;
    char* tmp_str9040 = calloc(tmp_strlen9040, sizeof(char));
    strcpy(tmp_str9040, out);
    strcat(tmp_str9040, else_out);
    out = tmp_str9040;
    int tmp_strlen9012 = strlen(out) + strlen(indent) + 1;
    char* tmp_str9012 = calloc(tmp_strlen9012, sizeof(char));
    strcpy(tmp_str9012, out);
    strcat(tmp_str9012, indent);
    int tmp_strlen9003 = strlen(tmp_str9012) + strlen("}\n") + 1;
    char* tmp_str9003 = calloc(tmp_strlen9003, sizeof(char));
    strcpy(tmp_str9003, tmp_str9012);
    strcat(tmp_str9003, "}\n");
    out = tmp_str9003;
    return (TranslateIfStmt_results){src, out};
  }
  ConsumeToken_results tmp_results8968 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8968.result1;
  tok_str = tmp_results8968.result2;
  int tmp_strlen8860 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str8860 = calloc(tmp_strlen8860, sizeof(char));
  strcpy(tmp_str8860, indent);
  strcat(tmp_str8860, SINGLE_INDENT);
  TranslateStmts_results tmp_results8919 = TranslateStmts(src, tmp_str8860, func_name);
  src = tmp_results8919.result1;
  else_out = tmp_results8919.result2;
  ConsumeToken_results tmp_results8843 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results8843.result1;
  tok_str = tmp_results8843.result2;
  int tmp_strlen8770 = strlen(out) + strlen(" else {\n") + 1;
  char* tmp_str8770 = calloc(tmp_strlen8770, sizeof(char));
  strcpy(tmp_str8770, out);
  strcat(tmp_str8770, " else {\n");
  out = tmp_str8770;
  int tmp_strlen8744 = strlen(out) + strlen(else_out) + 1;
  char* tmp_str8744 = calloc(tmp_strlen8744, sizeof(char));
  strcpy(tmp_str8744, out);
  strcat(tmp_str8744, else_out);
  out = tmp_str8744;
  int tmp_strlen8720 = strlen(out) + strlen(indent) + 1;
  char* tmp_str8720 = calloc(tmp_strlen8720, sizeof(char));
  strcpy(tmp_str8720, out);
  strcat(tmp_str8720, indent);
  int tmp_strlen8711 = strlen(tmp_str8720) + strlen("}\n") + 1;
  char* tmp_str8711 = calloc(tmp_strlen8711, sizeof(char));
  strcpy(tmp_str8711, tmp_str8720);
  strcat(tmp_str8711, "}\n");
  out = tmp_str8711;
  return (TranslateIfStmt_results){src, out};
}

TranslateForStmt_results TranslateForStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  ConsumeToken_results tmp_results8552 = ConsumeToken(src, TOK_FOR);
  src = tmp_results8552.result1;
  tok_str = tmp_results8552.result2;
  Peek_results tmp_results8506 = Peek(src);
  tok = tmp_results8506.result1;
  tok_str = tmp_results8506.result2;
  char* cond_setup = "";
  char* cond = "true";
  if ((tok) != (TOK_LCURLY)) {
    int tmp_strlen8318 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8318 = calloc(tmp_strlen8318, sizeof(char));
    strcpy(tmp_str8318, indent);
    strcat(tmp_str8318, SINGLE_INDENT);
    TranslateExpr_results tmp_results8384 = TranslateExpr(src, tmp_str8318);
    src = tmp_results8384.result1;
    cond_setup = tmp_results8384.result2;
    cond = tmp_results8384.result3;
  }
  ConsumeToken_results tmp_results8306 = ConsumeToken(src, TOK_LCURLY);
  src = tmp_results8306.result1;
  tok_str = tmp_results8306.result2;
  char* out;
  if ((strcmp(cond_setup, "") == 0)) {
    int tmp_strlen8182 = strlen(indent) + strlen("while (") + 1;
    char* tmp_str8182 = calloc(tmp_strlen8182, sizeof(char));
    strcpy(tmp_str8182, indent);
    strcat(tmp_str8182, "while (");
    int tmp_strlen8174 = strlen(tmp_str8182) + strlen(cond) + 1;
    char* tmp_str8174 = calloc(tmp_strlen8174, sizeof(char));
    strcpy(tmp_str8174, tmp_str8182);
    strcat(tmp_str8174, cond);
    int tmp_strlen8163 = strlen(tmp_str8174) + strlen(") {\n") + 1;
    char* tmp_str8163 = calloc(tmp_strlen8163, sizeof(char));
    strcpy(tmp_str8163, tmp_str8174);
    strcat(tmp_str8163, ") {\n");
    out = tmp_str8163;
  } else {
    int tmp_strlen8107 = strlen(indent) + strlen("while (true) {\n") + 1;
    char* tmp_str8107 = calloc(tmp_strlen8107, sizeof(char));
    strcpy(tmp_str8107, indent);
    strcat(tmp_str8107, "while (true) {\n");
    out = tmp_str8107;
    int tmp_strlen8075 = strlen(out) + strlen(cond_setup) + 1;
    char* tmp_str8075 = calloc(tmp_strlen8075, sizeof(char));
    strcpy(tmp_str8075, out);
    strcat(tmp_str8075, cond_setup);
    out = tmp_str8075;
    int tmp_strlen8047 = strlen(out) + strlen(indent) + 1;
    char* tmp_str8047 = calloc(tmp_strlen8047, sizeof(char));
    strcpy(tmp_str8047, out);
    strcat(tmp_str8047, indent);
    int tmp_strlen8030 = strlen(tmp_str8047) + strlen(SINGLE_INDENT) + 1;
    char* tmp_str8030 = calloc(tmp_strlen8030, sizeof(char));
    strcpy(tmp_str8030, tmp_str8047);
    strcat(tmp_str8030, SINGLE_INDENT);
    int tmp_strlen8018 = strlen(tmp_str8030) + strlen("if (!(") + 1;
    char* tmp_str8018 = calloc(tmp_strlen8018, sizeof(char));
    strcpy(tmp_str8018, tmp_str8030);
    strcat(tmp_str8018, "if (!(");
    int tmp_strlen8010 = strlen(tmp_str8018) + strlen(cond) + 1;
    char* tmp_str8010 = calloc(tmp_strlen8010, sizeof(char));
    strcpy(tmp_str8010, tmp_str8018);
    strcat(tmp_str8010, cond);
    int tmp_strlen7993 = strlen(tmp_str8010) + strlen(")) break;\n") + 1;
    char* tmp_str7993 = calloc(tmp_strlen7993, sizeof(char));
    strcpy(tmp_str7993, tmp_str8010);
    strcat(tmp_str7993, ")) break;\n");
    out = tmp_str7993;
  }
  char* body;
  int tmp_strlen7906 = strlen(indent) + strlen(SINGLE_INDENT) + 1;
  char* tmp_str7906 = calloc(tmp_strlen7906, sizeof(char));
  strcpy(tmp_str7906, indent);
  strcat(tmp_str7906, SINGLE_INDENT);
  TranslateStmts_results tmp_results7961 = TranslateStmts(src, tmp_str7906, func_name);
  src = tmp_results7961.result1;
  body = tmp_results7961.result2;
  ConsumeToken_results tmp_results7889 = ConsumeToken(src, TOK_RCURLY);
  src = tmp_results7889.result1;
  tok_str = tmp_results7889.result2;
  int tmp_strlen7823 = strlen(out) + strlen(body) + 1;
  char* tmp_str7823 = calloc(tmp_strlen7823, sizeof(char));
  strcpy(tmp_str7823, out);
  strcat(tmp_str7823, body);
  out = tmp_str7823;
  int tmp_strlen7799 = strlen(out) + strlen(indent) + 1;
  char* tmp_str7799 = calloc(tmp_strlen7799, sizeof(char));
  strcpy(tmp_str7799, out);
  strcat(tmp_str7799, indent);
  int tmp_strlen7790 = strlen(tmp_str7799) + strlen("}\n") + 1;
  char* tmp_str7790 = calloc(tmp_strlen7790, sizeof(char));
  strcpy(tmp_str7790, tmp_str7799);
  strcat(tmp_str7790, "}\n");
  out = tmp_str7790;
  return (TranslateForStmt_results){src, out};
}

TranslateContinueStmt_results TranslateContinueStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results7662 = ConsumeToken(src, TOK_CONTINUE);
  src = tmp_results7662.result1;
  tok_str = tmp_results7662.result2;
  int tmp_strlen7578 = strlen(indent) + strlen("continue;") + 1;
  char* tmp_str7578 = calloc(tmp_strlen7578, sizeof(char));
  strcpy(tmp_str7578, indent);
  strcat(tmp_str7578, "continue;");
  return (TranslateContinueStmt_results){src, tmp_str7578};
}

TranslateBreakStmt_results TranslateBreakStmt(char* src, char* indent) {
  char* tok_str;
  ConsumeToken_results tmp_results7473 = ConsumeToken(src, TOK_BREAK);
  src = tmp_results7473.result1;
  tok_str = tmp_results7473.result2;
  int tmp_strlen7395 = strlen(indent) + strlen("break;") + 1;
  char* tmp_str7395 = calloc(tmp_strlen7395, sizeof(char));
  strcpy(tmp_str7395, indent);
  strcat(tmp_str7395, "break;");
  return (TranslateBreakStmt_results){src, tmp_str7395};
}

TranslateReturnStmt_results TranslateReturnStmt(char* src, char* indent, char* func_name) {
  char* tok_str;
  ConsumeToken_results tmp_results7270 = ConsumeToken(src, TOK_RETURN);
  src = tmp_results7270.result1;
  tok_str = tmp_results7270.result2;
  int expr_count;
  char* exprs_setup;
  char* exprs_value;
  TranslateExprs_results tmp_results7141 = TranslateExprs(src, indent);
  src = tmp_results7141.result1;
  expr_count = tmp_results7141.result2;
  exprs_setup = tmp_results7141.result3;
  exprs_value = tmp_results7141.result4;
  ConsumeToken_results tmp_results7065 = ConsumeToken(src, TOK_NEWLINE);
  src = tmp_results7065.result1;
  tok_str = tmp_results7065.result2;
  int tmp_strlen6976 = strlen(exprs_setup) + strlen(indent) + 1;
  char* tmp_str6976 = calloc(tmp_strlen6976, sizeof(char));
  strcpy(tmp_str6976, exprs_setup);
  strcat(tmp_str6976, indent);
  int tmp_strlen6963 = strlen(tmp_str6976) + strlen("return ") + 1;
  char* tmp_str6963 = calloc(tmp_strlen6963, sizeof(char));
  strcpy(tmp_str6963, tmp_str6976);
  strcat(tmp_str6963, "return ");
  char* out = tmp_str6963;
  if ((expr_count) > (1)) {
    int tmp_strlen6914 = strlen(out) + strlen("(") + 1;
    char* tmp_str6914 = calloc(tmp_strlen6914, sizeof(char));
    strcpy(tmp_str6914, out);
    strcat(tmp_str6914, "(");
    int tmp_strlen6901 = strlen(tmp_str6914) + strlen(func_name) + 1;
    char* tmp_str6901 = calloc(tmp_strlen6901, sizeof(char));
    strcpy(tmp_str6901, tmp_str6914);
    strcat(tmp_str6901, func_name);
    int tmp_strlen6885 = strlen(tmp_str6901) + strlen("_results){") + 1;
    char* tmp_str6885 = calloc(tmp_strlen6885, sizeof(char));
    strcpy(tmp_str6885, tmp_str6901);
    strcat(tmp_str6885, "_results){");
    out = tmp_str6885;
  }
  int tmp_strlen6850 = strlen(out) + strlen(exprs_value) + 1;
  char* tmp_str6850 = calloc(tmp_strlen6850, sizeof(char));
  strcpy(tmp_str6850, out);
  strcat(tmp_str6850, exprs_value);
  out = tmp_str6850;
  if ((expr_count) > (1)) {
    int tmp_strlen6800 = strlen(out) + strlen("}") + 1;
    char* tmp_str6800 = calloc(tmp_strlen6800, sizeof(char));
    strcpy(tmp_str6800, out);
    strcat(tmp_str6800, "}");
    out = tmp_str6800;
  }
  int tmp_strlen6771 = strlen(out) + strlen(";\n") + 1;
  char* tmp_str6771 = calloc(tmp_strlen6771, sizeof(char));
  strcpy(tmp_str6771, out);
  strcat(tmp_str6771, ";\n");
  out = tmp_str6771;
  return (TranslateReturnStmt_results){src, out};
}

TranslateStmt_results TranslateStmt(char* src, char* indent, char* func_name) {
  int tok;
  char* tok_str;
  Peek_results tmp_results6615 = Peek(src);
  tok = tmp_results6615.result1;
  tok_str = tmp_results6615.result2;
  char* out;
  if ((tok) == (TOK_LET)) {
    TranslateConstDeclStmt_results tmp_results6538 = TranslateConstDeclStmt(src, indent);
    src = tmp_results6538.result1;
    out = tmp_results6538.result2;
    return (TranslateStmt_results){src, out};
  } else {
    if ((tok) == (TOK_VAR)) {
      TranslateVarDeclStmt_results tmp_results6428 = TranslateVarDeclStmt(src, indent);
      src = tmp_results6428.result1;
      out = tmp_results6428.result2;
      return (TranslateStmt_results){src, out};
    } else {
      if ((tok) == (TOK_IF)) {
        TranslateIfStmt_results tmp_results6321 = TranslateIfStmt(src, indent, func_name);
        src = tmp_results6321.result1;
        out = tmp_results6321.result2;
        return (TranslateStmt_results){src, out};
      } else {
        if ((tok) == (TOK_FOR)) {
          TranslateForStmt_results tmp_results6207 = TranslateForStmt(src, indent, func_name);
          src = tmp_results6207.result1;
          out = tmp_results6207.result2;
          return (TranslateStmt_results){src, out};
        } else {
          if ((tok) == (TOK_CONTINUE)) {
            TranslateContinueStmt_results tmp_results6087 = TranslateContinueStmt(src, indent);
            src = tmp_results6087.result1;
            out = tmp_results6087.result2;
            return (TranslateStmt_results){src, out};
          } else {
            if ((tok) == (TOK_BREAK)) {
              TranslateBreakStmt_results tmp_results5976 = TranslateBreakStmt(src, indent);
              src = tmp_results5976.result1;
              out = tmp_results5976.result2;
              return (TranslateStmt_results){src, out};
            } else {
              if ((tok) == (TOK_RETURN)) {
                TranslateReturnStmt_results tmp_results5867 = TranslateReturnStmt(src, indent, func_name);
                src = tmp_results5867.result1;
                out = tmp_results5867.result2;
                return (TranslateStmt_results){src, out};
              } else {
                if (((tok) == (TOK_IDENT)) || ((tok) == (TOK_UNDERSCORE))) {
                  char* first_ident;
                  ConsumeIdentOrUnderscore_results tmp_results5690 = ConsumeIdentOrUnderscore(src);
                  src = tmp_results5690.result1;
                  first_ident = tmp_results5690.result2;
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
  int tmp_strlen150 = (i) - (0) + 1;
  char* tmp_str150 = calloc(tmp_strlen150, sizeof(char));
  strncpy(tmp_str150, args + 0, tmp_strlen150 - 1);
  tmp_str150[tmp_strlen150 - 1] = 0;
  char* src_file = tmp_str150;
  char* src = read(src_file);
  char* out = TranslateProgram(src);
  int tmp_strlen30 = (strlen(args)) - ((i) + (1)) + 1;
  char* tmp_str30 = calloc(tmp_strlen30, sizeof(char));
  strncpy(tmp_str30, args + (i) + (1), tmp_strlen30 - 1);
  tmp_str30[tmp_strlen30 - 1] = 0;
  char* out_file = tmp_str30;
  write(out_file, out);
  return 0;
}

