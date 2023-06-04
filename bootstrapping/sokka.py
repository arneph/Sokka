import sys

TOK_NEWLINE = 0
TOK_EOF = 1

TOK_FN = 100
TOK_LET = 101
TOK_VAR = 102
TOK_IF = 103
TOK_ELSE = 104
TOK_FOR = 105
TOK_CONTINUE = 106
TOK_BREAK = 107
TOK_RETURN = 108
TOK_BOOL = 110
TOK_INT = 111
TOK_STRING = 112
TOK_FALSE = 120
TOK_TRUE = 121

TOK_LPAREN = 200
TOK_RPAREN = 201
TOK_LBRACKET = 202
TOK_RBRACKET = 203
TOK_LCURLY = 204
TOK_RCURLY = 205
TOK_COLON = 210
TOK_COMMA = 211
TOK_ASSIGN = 212
TOK_RARROW = 213
# Bool operators
TOK_BNOT = 220
TOK_BOR = 221
TOK_BAND = 222
# Int operators
TOK_ADD = 230
TOK_SUB = 231
TOK_MUL = 232
TOK_DIV = 233
TOK_REM = 234
TOK_INOT = 235
TOK_IOR = 236
TOK_IAND = 237
TOK_IXOR = 238
# Comparison operators
TOK_EQ = 240
TOK_NEQ = 241
TOK_LESS = 242
TOK_LEQ = 243
TOK_GEQ = 244
TOK_GREATER = 245
# Str operators
TOK_STRCAT = 250
TOK_STREQ = 251
TOK_STRNEQ = 252

TOK_IDENT = 300
TOK_INTLIT = 301
TOK_STRLIT = 302

TYPE_BOOL = 1000
TYPE_INT = 1001
TYPE_STRING = 1002

SINGLE_INDENT = '  '

def IsUnaryOp(tok: int) -> bool:
    return tok == TOK_BNOT or tok == TOK_ADD or tok == TOK_SUB or tok == TOK_INOT

def IsBinaryOp(tok: int) -> bool:
    return (tok == TOK_BOR or tok == TOK_BAND or tok == TOK_ADD or tok == TOK_SUB 
        or tok == TOK_MUL or tok == TOK_DIV or tok == TOK_REM or tok == TOK_IOR 
        or tok == TOK_IAND or tok == TOK_IXOR or tok == TOK_EQ or tok == TOK_NEQ
        or tok == TOK_LESS or tok == TOK_LEQ or tok == TOK_GEQ or tok == TOK_GREATER
        or tok == TOK_STRCAT or tok == TOK_STREQ or tok == TOK_STRNEQ)

def Precedence(tok: int) -> int:
    if tok == TOK_BOR:
        return 1
    elif tok == TOK_BAND:
        return 2
    elif (tok == TOK_EQ or tok == TOK_NEQ 
        or tok == TOK_LESS or tok == TOK_LEQ or tok == TOK_GEQ or tok == TOK_GREATER
        or tok == TOK_STREQ or tok == TOK_STRNEQ):
        return 3
    elif tok == TOK_IOR:
        return 4
    elif tok == TOK_IXOR:
        return 5
    elif tok == TOK_IAND:
        return 6
    elif tok == TOK_ADD or tok == TOK_SUB or tok == TOK_STRCAT:
        return 7
    elif tok == TOK_MUL or tok == TOK_DIV or tok == TOK_REM:
        return 8
    else:
        raise Exception('token has no defined precedence: ' + str(tok))

def Next(src: str) -> tuple[str, int, str]:
    src = src.lstrip(' \t')
    if src == '':
        return '', TOK_EOF, ''
    elif src.startswith('->'):
        return src[2:], TOK_RARROW, '->'
    elif src.startswith('||'):
        return src[2:], TOK_BOR, '||'
    elif src.startswith('&&'):
        return src[2:], TOK_BAND, '&&'
    elif src.startswith('=='):
        return src[2:], TOK_EQ, '=='
    elif src.startswith('!='):
        return src[2:], TOK_NEQ, '!='
    elif src.startswith('<='):
        return src[2:], TOK_LEQ, '<='
    elif src.startswith('>='):
        return src[2:], TOK_GEQ, '>='
    elif src.startswith('++'):
        return src[2:], TOK_STRCAT, '++'
    elif src.startswith('<>'):
        return src[2:], TOK_STREQ, '<>'
    elif src.startswith('<!>'):
        return src[3:], TOK_STRNEQ, '<!>'
    elif src.startswith('\n'):
        return src[1:], TOK_NEWLINE, '\n'
    elif src.startswith('('):
        return src[1:], TOK_LPAREN, '('
    elif src.startswith(')'):
        return src[1:], TOK_RPAREN, ')'
    elif src.startswith('['):
        return src[1:], TOK_LBRACKET, '['
    elif src.startswith(']'):
        return src[1:], TOK_RBRACKET, ']'
    elif src.startswith('{'):
        return src[1:], TOK_LCURLY, '{'
    elif src.startswith('}'):
        return src[1:], TOK_RCURLY, '}'
    elif src.startswith(':'):
        return src[1:], TOK_COLON, ':'
    elif src.startswith(','):
        return src[1:], TOK_COMMA, ','
    elif src.startswith('='):
        return src[1:], TOK_ASSIGN, '='
    elif src.startswith('!'):
        return src[1:], TOK_BNOT, '!'
    elif src.startswith('+'):
        return src[1:], TOK_ADD, '+'
    elif src.startswith('-'):
        return src[1:], TOK_SUB, '-'
    elif src.startswith('*'):
        return src[1:], TOK_MUL, '*'
    elif src.startswith('/'):
        return src[1:], TOK_DIV, '/'
    elif src.startswith('%'):
        return src[1:], TOK_REM, '%'
    elif src.startswith('~'):
        return src[1:], TOK_INOT, '~'
    elif src.startswith('|'):
        return src[1:], TOK_IOR, '|'
    elif src.startswith('&'):
        return src[1:], TOK_IAND, '&'
    elif src.startswith('^'):
        return src[1:], TOK_IXOR, '^'
    elif src.startswith('<'):
        return src[1:], TOK_LESS, '<'
    elif src.startswith('>'):
        return src[1:], TOK_GREATER, '>'
    elif src[:1].isalpha():
        i = 1
        while src[i-1:i].isalnum() or src[i-1:i] == '_':
            i += 1
        i -= 1
        ts = src[:i]
        if ts == 'fn':
            tt = TOK_FN
        elif ts == 'let':
            tt = TOK_LET
        elif ts == 'var':
            tt = TOK_VAR
        elif ts == 'if':
            tt = TOK_IF
        elif ts == 'else':
            tt = TOK_ELSE
        elif ts == 'for':
            tt = TOK_FOR
        elif ts == 'return':
            tt = TOK_RETURN
        elif ts == 'bool':
            tt = TOK_BOOL
        elif ts == 'int':
            tt = TOK_INT
        elif ts == 'string':
            tt = TOK_STRING
        elif ts == 'false':
            tt = TOK_FALSE
        elif ts == 'true':
            tt = TOK_TRUE
        else:
            tt = TOK_IDENT
        return src[i:], tt, ts
    elif src[:1].isdecimal():
        i = 1
        while src[:i].isdecimal():
            i += 1
        i -= 1
        return src[i:], TOK_INTLIT, src[:i]
    elif src.startswith('"'):
        i = 1
        while src[i:i+1] != '"':
            i += 1
            if src[i-1:i] == '\\':
                i += 1
        i += 1
        return src[i:], TOK_STRLIT, src[:i]
    else:
        raise Exception('unexpected token start: ' + src[:1])

def Peek(src: str) -> tuple[int, str]:
    src, tok, tok_str = Next(src)
    return tok, tok_str

def ConsumeToken(src: str, expected_tok: int) -> tuple[str, str]:
    src, actual_tok, actual_tok_str = Next(src)
    if actual_tok != expected_tok:
        raise Exception('expected token: ' + str(expected_tok)
            + ' got: ' + str(actual_tok) + ' "' + actual_tok_str + '"')
    return src, actual_tok_str

def ConsumeIdent(src: str) -> tuple[str, str]:
    src, actual_tok, actual_tok_str = Next(src)
    if actual_tok != TOK_IDENT:
        raise Exception('expected ident, got: ' + str(actual_tok) + ' "' + actual_tok_str + '"')
    return src, actual_tok_str

def TranslateType(src: str) -> tuple[str, int, str]:
    src, tok, tok_str = Next(src)
    if tok == TOK_BOOL:
        return src, TYPE_BOOL, 'bool'
    elif tok == TOK_INT:
        return src, TYPE_INT, 'int'
    elif tok == TOK_STRING:
        return src, TYPE_STRING, 'char*'
    else:
        raise Exception('expected type, got: ' + str(tok) + ' "' + tok_str + '"')

def TranslateBoolLiteral(src: str) -> tuple[str, str]:
    src, tok, tok_str = Next(src)
    if tok == TOK_FALSE or tok == TOK_TRUE:
        return src, tok_str
    else:
        raise Exception('expected false or true, got: ' + str(tok) + ' "' + tok_str + '"')

def TranslateIntLiteral(src: str) -> tuple[str, str]:
    src, lit = ConsumeToken(src, TOK_INTLIT)
    return src, lit

def TranslateStringLiteral(src: str) -> tuple[str, str]:
    src, lit = ConsumeToken(src, TOK_STRLIT)
    return src, lit

def TranslateCall(src: str, indent: str, callee: str) -> tuple[str, str, str]:
    src, tok_str = ConsumeToken(src, TOK_LPAREN)
    tok, tok_str = Peek(src)
    if tok != TOK_RPAREN:
        src, expr_count, args_setup, arg_values = TranslateExprs(src, indent)
    else:
        args_setup = ''
        arg_values = ''
    src, tok_str = ConsumeToken(src, TOK_RPAREN)
    if callee == 'print':
        val = 'printf("%s", ' + arg_values + ')'
    elif callee == 'len':
        val = 'strlen(' + arg_values + ')'
    else:
        val = callee + '(' + arg_values + ')'
    return src, args_setup, val

def TranslateSubstrExpr(src: str, indent: str, var: str) -> tuple[str, str, str]:
    src, tok_str = ConsumeToken(src, TOK_LBRACKET)
    tok, tok_str = Peek(src)
    if tok == TOK_COLON:
        p = len(src)
        src, tok_str = ConsumeToken(src, TOK_COLON)
        low_setup = ''
        low_expr = '0'
        src, high_setup, high_expr = TranslateExpr(src, indent)
        src, tok_str = ConsumeToken(src, TOK_RBRACKET)
    else:
        src, low_setup, low_expr = TranslateExpr(src, indent)
        tok, tok_str = Peek(src)
        if tok == TOK_RBRACKET:
            src, tok_str = ConsumeToken(src, TOK_RBRACKET)
            return src, low_setup, var + '[' + low_expr + ']'
        p = len(src)
        src, tok_str = ConsumeToken(src, TOK_COLON)
        tok, tok_str = Peek(src)
        if tok == TOK_RBRACKET:
            high_setup = ''
            high_expr = 'strlen(' + var + ')'
        else:
            src, high_setup, high_expr = TranslateExpr(src, indent)
        src, tok_str = ConsumeToken(src, TOK_RBRACKET)
    tmp_str = 'tmp_str' + str(p)
    tmp_strlen = 'tmp_strlen' + str(p)
    setup = low_setup + high_setup
    setup += indent + 'int ' + tmp_strlen + ' = (' + high_expr + ') - (' + low_expr + ') + 1;\n'
    setup += indent + 'char* ' + tmp_str + ' = calloc(' + tmp_strlen + ', sizeof(char));\n'
    setup += indent + 'strncpy(' + tmp_str + ', ' + var + ' + ' + low_expr + ', ' + tmp_strlen + ' - 1);\n'
    setup += indent + tmp_str + '[' + tmp_strlen + ' - 1] = 0;\n'
    return src, setup, tmp_str

def TranslateOperand(src: str, indent: str) -> tuple[str, str, str]:
    tok, tok_str = Peek(src)
    if tok == TOK_LPAREN:
        src, tok_str = ConsumeToken(src, TOK_LPAREN)
        src, setup, val = TranslateExpr(src, indent)
        src, tok_str = ConsumeToken(src, TOK_RPAREN)
        return src, setup, val
    elif tok == TOK_FALSE or tok == TOK_TRUE:
        src, lit = TranslateBoolLiteral(src)
        return src, '', lit
    elif tok == TOK_INTLIT:
        src, lit = TranslateIntLiteral(src)
        return src, '', lit
    elif tok == TOK_STRLIT:
        src, lit = TranslateStringLiteral(src)
        return src, '', lit
    elif tok == TOK_IDENT:
        src, ident = ConsumeIdent(src)
        tok, tok_str = Peek(src)
        if tok == TOK_LPAREN:
            return TranslateCall(src, indent, ident)
        elif tok == TOK_LBRACKET:
            return TranslateSubstrExpr(src, indent, ident)
        return src, '', ident
    else:
        raise Exception('unexpected expr, got: ' + str(tok) + ' "' + tok_str + '"')

def TranslateUnaryExpr(src: str, indent: str) -> tuple[str, str, str]:
    tok, tok_str = Peek(src)
    if IsUnaryOp(tok):
        src, tok_str = ConsumeToken(src, tok)
        src, setup, val = TranslateExpr(src, indent)
        val = tok_str + '(' + val + ')'
        return src, setup, val
    else:
        return TranslateOperand(src, indent)

def TranslateExprWithPrecedence(src: str, indent: str, precedence: int) -> tuple[str, str, str]:
    src, setup, val = TranslateUnaryExpr(src, indent)
    op, op_str = Peek(src)
    while IsBinaryOp(op) and Precedence(op) > precedence:
        src, op_str = ConsumeToken(src, op)
        tok, tok_str = Peek(src)
        while tok == TOK_NEWLINE:
            src, tok_str = ConsumeToken(src, TOK_NEWLINE)
            tok, tok_str = Peek(src)
        src, setup_b, val_b = TranslateExprWithPrecedence(src, indent, Precedence(op))
        setup += setup_b
        if op == TOK_STRCAT:
            tmp_str = 'tmp_str' + str(len(src))
            tmp_strlen = 'tmp_strlen' + str(len(src))
            setup += indent + 'int ' + tmp_strlen + ' = strlen(' + val + ') + strlen(' + val_b + ') + 1;\n'
            setup += indent + 'char* ' + tmp_str + ' = calloc(' + tmp_strlen + ', sizeof(char));\n'
            setup += indent + 'strcpy(' + tmp_str + ', ' + val + ');\n'
            setup += indent + 'strcat(' + tmp_str + ', ' + val_b + ');\n'
            val = tmp_str
        elif op == TOK_STREQ:
            val = '(strcmp(' + val + ', ' + val_b + ') == 0)'
        elif op == TOK_STRNEQ:
            val = '(strcmp(' + val + ', ' + val_b + ') != 0)'
        else:
            val = '(' + val + ') ' + op_str + ' (' + val_b + ')'
        op, tok_str = Peek(src)
    return src, setup, val

def TranslateExpr(src: str, indent: str) -> tuple[str, str, str]:
    return TranslateExprWithPrecedence(src, indent, 0)

def TranslateExprs(src: str, indent: str) -> tuple[str, int, str, str]:
    src, expr_setup, expr_value = TranslateExpr(src, indent)
    tok, tok_str = Peek(src)
    exprs_count = 1
    exprs_setup = expr_setup
    exprs_value = expr_value
    while tok == TOK_COMMA:
        src, tok_str = ConsumeToken(src, TOK_COMMA)
        src, expr_setup, expr_value = TranslateExpr(src, indent)
        exprs_count += 1
        exprs_setup += expr_setup
        exprs_value += ', ' + expr_value
        tok, tok_str = Peek(src)
    return src, exprs_count, exprs_setup, exprs_value

def TranslateConstOrVar(src: str) -> tuple[str, str]:
    src, name = ConsumeIdent(src)
    src, tok_str = ConsumeToken(src, TOK_COLON)
    src, typ, typ_str = TranslateType(src)
    out = typ_str + ' ' + name
    return src, out

def TranslateConstDecl(src: str, indent: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_LET)
    src, out = TranslateConstOrVar(src)
    out = 'const ' + out
    src, tok_str = ConsumeToken(src, TOK_ASSIGN)
    src, setup, val = TranslateExpr(src, indent)
    assert setup == ''
    src, tok_str = ConsumeToken(src, TOK_NEWLINE)
    out += ' = ' + val + ';\n'
    return src, out

def TranslateConstDeclStmt(src: str, indent: str) -> tuple[str, str]:
    src, out = TranslateConstDecl(src, indent)
    return src, indent + out

def TranslateVarDeclStmt(src: str, indent: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_VAR)
    setup = ''
    src, out = TranslateConstOrVar(src)
    tok, tok_str = Peek(src)
    if tok == TOK_ASSIGN:
        src, tok_str = ConsumeToken(src, TOK_ASSIGN)
        src, setup, val = TranslateExpr(src, indent)
        src, tok_str = ConsumeToken(src, TOK_NEWLINE)
        out += ' = ' + val
    out = setup + indent + out + ';\n'
    return src, out

def TranslateAssignStmt(src: str, indent: str) -> tuple[str, str]:
    x = src.find('=')
    lhs = src[:x]
    rhs = src[x+1:]
    lhs, lhs_ident = ConsumeIdent(lhs)
    old_rhs = rhs
    rhs, setup, rhs_expr = TranslateExpr(rhs, indent)
    lhs_tok, lhs_tok_str = Peek(lhs)
    rhs_tok, rhs_tok_str = Peek(rhs)
    if lhs_tok == TOK_COMMA and rhs_tok != TOK_COMMA:
        old_rhs, func_name = ConsumeIdent(old_rhs)
        tmp_results = 'tmp_results' + str(len(src))
        out = setup
        out += indent + func_name + '_results ' + tmp_results + ' = ' + rhs_expr + ';\n'
        out += indent + lhs_ident + ' = ' + tmp_results + '.result1;\n'
        result_count = 1
        while lhs_tok == TOK_COMMA:
            result_count += 1
            lhs, lhs_tok_str = ConsumeToken(lhs, TOK_COMMA)
            lhs, lhs_ident = ConsumeIdent(lhs)
            out += indent + lhs_ident + ' = ' + tmp_results + '.result' + str(result_count) + ';\n'
            lhs_tok, lhs_tok_str = Peek(lhs)
        src, tok_str = ConsumeToken(rhs, TOK_NEWLINE)
        return src, out
    assignments = indent + lhs_ident + ' = ' + rhs_expr + ';\n'
    while lhs_tok == TOK_COMMA:
        lhs, lhs_tok_str = ConsumeToken(lhs, TOK_COMMA)
        rhs, rhs_tok_str = ConsumeToken(rhs, TOK_COMMA)
        lhs, lhs_ident = ConsumeIdent(lhs)
        rhs, rhs_expr_setup, rhs_expr = TranslateExpr(rhs, indent)
        setup += rhs_expr_setup
        assignments += indent + lhs_ident + ' = ' + rhs_expr + ';\n'
        lhs_tok, lhs_tok_str = Peek(lhs)
    src, tok_str = ConsumeToken(rhs, TOK_NEWLINE)
    return src, setup + assignments

def TranslateIfStmt(src: str, indent: str, func_name: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_IF)
    src, cond_setup, cond = TranslateExpr(src, indent)
    src, tok_str = ConsumeToken(src, TOK_LCURLY)
    out = cond_setup
    out += indent + 'if (' + cond + ') {\n'
    src, body = TranslateStmts(src, indent + SINGLE_INDENT, func_name)
    src, tok_str = ConsumeToken(src, TOK_RCURLY)
    out += body
    out += indent + '}'
    tok, tok_str = Peek(src)
    if tok != TOK_ELSE:
        return src, out + '\n'
    src, tok_str = ConsumeToken(src, TOK_ELSE)
    tok, tok_str = Peek(src)
    if tok == TOK_IF:
        src, else_out = TranslateIfStmt(src, indent + SINGLE_INDENT, func_name)
        out += ' else {\n'
        out += else_out
        out += indent + '}\n'
        return src, out
    src, tok_str = ConsumeToken(src, TOK_LCURLY)
    src, else_out = TranslateStmts(src, indent + SINGLE_INDENT, func_name)
    src, tok_str = ConsumeToken(src, TOK_RCURLY)
    out += ' else {\n'
    out += else_out
    out += indent + '}\n'
    return src, out

def TranslateForStmt(src: str, indent: str, func_name: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_FOR)
    tok, tok_str = Peek(src)
    if tok != TOK_LCURLY:
        src, cond_setup, cond = TranslateExpr(src, indent + SINGLE_INDENT)
    else:
        cond_setup = ''
        cond = 'true'
    src, tok_str = ConsumeToken(src, TOK_LCURLY)
    if cond_setup == '':
        out = indent + 'while (' + cond + ') {\n'
    else:
        out = indent + 'while (true) {\n'
        out += cond_setup
        out += indent + SINGLE_INDENT + 'if (!(' + cond + ')) break;\n'
    src, body = TranslateStmts(src, indent + SINGLE_INDENT, func_name)
    src, tok_str = ConsumeToken(src, TOK_RCURLY)
    out += body
    out += indent + '}\n'
    return src, out

def TranslateContinueStmt(src: str, indent: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_CONTINUE)
    out = indent + 'continue;'
    return src, out

def TranslateBreakStmt(src: str, indent: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_BREAK)
    out = indent + 'break;'
    return src, out

def TranslateReturnStmt(src: str, indent: str, func_name: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_RETURN)
    src, expr_count, exprs_setup, exprs_value = TranslateExprs(src, indent)
    src, tok_str = ConsumeToken(src, TOK_NEWLINE)
    out = exprs_setup + indent + 'return '
    if expr_count > 1:
        out += '(' + func_name + '_results){'
    out += exprs_value
    if expr_count > 1:
        out += '}'
    out += ';\n'
    return src, out

def TranslateStmt(src: str, indent: str, func_name: str) -> tuple[str, str]:
    tok, tok_str = Peek(src)
    if tok == TOK_LET:
        return TranslateConstDeclStmt(src, indent)
    elif tok == TOK_VAR:
        return TranslateVarDeclStmt(src, indent)
    elif tok == TOK_IF:
        return TranslateIfStmt(src, indent, func_name)
    elif tok == TOK_FOR:
        return TranslateForStmt(src, indent, func_name)
    elif tok == TOK_CONTINUE:
        return TranslateContinueStmt(src)
    elif tok == TOK_BREAK:
        return TranslateBreakStmt(src)
    elif tok == TOK_RETURN:
        return TranslateReturnStmt(src, indent, func_name)
    elif tok == TOK_IDENT:
        src, first_ident = ConsumeIdent(src)
        tok, tok_str = Peek(src)
        src = first_ident + src
        if tok == TOK_COMMA or tok == TOK_ASSIGN:
            return TranslateAssignStmt(src, indent)
        else:
            src, setup, val = TranslateExpr(src, indent)
            src, tok_str = ConsumeToken(src, TOK_NEWLINE)
            out = setup + indent + val + ';\n'
            return src, out
    else:
        raise Exception('unexpected stmt token: ' + str(tok) + ' "' + tok_str + '"')

def TranslateStmts(src: str, indent: str, func_name: str) -> tuple[str, str]:
    tok, tok_str = Peek(src)
    out = ''
    while tok != TOK_RCURLY:
        if tok == TOK_NEWLINE:
            src, tok_str = ConsumeToken(src, TOK_NEWLINE)
            tok, tok_str = Peek(src)
            continue
        src, stmt_out = TranslateStmt(src, indent, func_name)
        out += stmt_out
        tok, tok_str = Peek(src)
    return src, out

def TranslateFuncArgs(src: str) -> tuple[str, str]:
    src, tok_str = ConsumeToken(src, TOK_LPAREN)
    tok, tok_str = Peek(src)
    if tok == TOK_RPAREN:
        src, tok_str = ConsumeToken(src, TOK_RPAREN)
        return src, '()'
    src, args = TranslateConstOrVar(src)
    tok, tok_str = Peek(src)
    while tok == TOK_COMMA:
        src, tok_str = ConsumeToken(src, TOK_COMMA)
        src, arg = TranslateConstOrVar(src)
        args += ', ' + arg
        tok, tok_str = Peek(src)
    src, tok_str = ConsumeToken(src, TOK_RPAREN)
    return src, '(' + args  + ')'

def TranslateFuncResults(src: str, func_name: str) -> tuple[str, str, str]:
    tok, tok_str = Peek(src)
    if tok != TOK_LPAREN:
        src, typ, typ_str = TranslateType(src)
        return src, '', typ_str
    src, tok_str = ConsumeToken(src, TOK_LPAREN)
    src, typ, typ_str = TranslateType(src)
    tok, tok_str = Peek(src)
    if tok != TOK_COMMA:
        src, tok_str = ConsumeToken(src, TOK_RPAREN)
        return src, '', typ_str
    td = 'typedef struct {\n' + SINGLE_INDENT + typ_str + ' result1;\n'
    res_count = 1
    while tok == TOK_COMMA:
        src, tok_str = ConsumeToken(src, TOK_COMMA)
        src, typ, typ_str = TranslateType(src)
        res_count += 1
        td += SINGLE_INDENT + typ_str + ' result' + str(res_count) + ';\n'
        tok, tok_str = Peek(src)
    src, tok_str = ConsumeToken(src, TOK_RPAREN)
    td += '} ' + func_name + '_results;\n'
    return src, td, func_name + '_results'

def TranslateFunc(src: str) -> tuple[str, str, str]:
    src, tok_str = ConsumeToken(src, TOK_FN)
    src, name = ConsumeIdent(src)
    args = '()'
    results_type_def = ''
    results_type_name = 'void' if name != 'main' else 'int'
    tok, tok_str = Peek(src)
    if tok == TOK_LPAREN:
        src, args = TranslateFuncArgs(src)
        tok, tok_str = Peek(src)
        if tok == TOK_RARROW:
            src, tok_str = ConsumeToken(src, TOK_RARROW)
            src, results_type_def, results_type_name = TranslateFuncResults(src, name)
    src, tok_str = ConsumeToken(src, TOK_LCURLY)
    src, stmts_out = TranslateStmts(src, SINGLE_INDENT, name)
    src, tok_str = ConsumeToken(src, TOK_RCURLY)
    if name == 'main':
        name = '_main'
        df = 'int '
        args = '(char* args)'
    else:
        df = 'void '
    df = results_type_name + ' ' + name + args
    decl = results_type_def + df + ';\n'
    df += ' {\n'
    df += stmts_out
    if name == '_main':
        df += '  return 0;\n'
    df += '}\n\n'
    return src, decl, df

def TranslateProgram(src: str) -> str:
    clib_file = open('clib/lib.c', "r")
    out = clib_file.read()
    constants = ''
    decls = ''
    defs = ''
    tok, tok_str = Peek(src)
    while tok != TOK_EOF:
        if tok == TOK_NEWLINE:
            src, tok_str = ConsumeToken(src, TOK_NEWLINE)
            tok, tok_str = Peek(src)
            continue
        elif tok == TOK_LET:
            src, const_decl = TranslateConstDecl(src, '')
            constants += const_decl
        elif tok == TOK_FN:
            src, fn_decl, fn_def = TranslateFunc(src)
            decls += fn_decl
            defs += fn_def
        else:
            raise Exception('expected "let" or "fn" token, got: ' + str(tok) + ' "' + tok_str + '"')
        tok, tok_str = Peek(src)
    src, tok_str = ConsumeToken(src, TOK_EOF)
    if constants != '':
        out += constants + '\n'
    if decls != '':
        out += decls + '\n'
    if defs != '':
        out += defs
    return out

src_file = open(sys.argv[1], "r")
src = src_file.read()
out = TranslateProgram(src)
out_file = open(sys.argv[2], "w")
out_file.write(out)
