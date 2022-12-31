#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
For the language grammar, please refer to Grammar section on the github page:
  https://github.com/lightbulb12294/CSI2P-II-Mini1#grammar
*/

#define MAX_LENGTH 200
typedef enum
{
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    REM,
    PREINC,
    PREDEC,
    POSTINC,
    POSTDEC,
    IDENTIFIER,
    CONSTANT,
    LPAR,
    RPAR,
    PLUS,
    MINUS,
    END
} Kind;
typedef enum
{
    STMT,
    EXPR,
    ASSIGN_EXPR,
    ADD_EXPR,
    MUL_EXPR,
    UNARY_EXPR,
    POSTFIX_EXPR,
    PRI_EXPR
} GrammarState;
typedef struct TokenUnit
{
    Kind kind;
    int val; // record the integer value or variable name
    struct TokenUnit *next;
} Token;
typedef struct ASTUnit
{
    Kind kind;
    int val; // record the integer value or variable name
    struct ASTUnit *lhs, *mid, *rhs;
} AST;

/// utility interfaces

// err marco should be used when a expression error occurs.
#define err(x)                                                \
    {                                                         \
        puts("Compile Error!");                               \
        if (DEBUG)                                            \
        {                                                     \
            fprintf(stderr, "Error at line: %d\n", __LINE__); \
            fprintf(stderr, "Error message: %s\n", x);        \
        }                                                     \
        exit(0);                                              \
    }
// You may set DEBUG=1 to debug. Remember setting back to 0 before submit.
#define DEBUG 0
// Split the input char array into token linked list.
Token *lexer(const char *in);
// Create a new token.
Token *new_token(Kind kind, int val);
// Translate a token linked list into array, return its length.
size_t token_list_to_arr(Token **head);
// Parse the token array. Return the constructed AST.
AST *parser(Token *arr, size_t len);
// Parse the token array. Return the constructed AST.
AST *parse(Token *arr, int l, int r, GrammarState S);
// Create a new AST node.
AST *new_AST(Kind kind, int val);
// Find the location of next token that fits the condition(cond). Return -1 if not found. Search direction from start to end.
int findNextSection(Token *arr, int start, int end, int (*cond)(Kind));
// Return 1 if kind is ASSIGN.
int condASSIGN(Kind kind);
// Return 1 if kind is ADD or SUB.
int condADD(Kind kind);
// Return 1 if kind is MUL, DIV, or REM.
int condMUL(Kind kind);
// Return 1 if kind is RPAR.
int condRPAR(Kind kind);
// Check if the AST is semantically right. This function will call err() automatically if check failed.
void semantic_check(AST *now);
// Generate ASM code. Return a string
char *codegen(AST *now);
// Optimize the final_ans and print;
void optimize();
// Free the whole AST.
void freeAST(AST *now);

/// debug interfaces

// Print token array.
void token_print(Token *in, size_t len);
// Print AST tree.
void AST_print(AST *head);

char input[MAX_LENGTH];

int main()
{
    while (fgets(input, MAX_LENGTH, stdin) != NULL)
    {
        Token *content = lexer(input);
        size_t len = token_list_to_arr(&content);
        if (len == 0)
            continue;
        // token_print(content, len);
        AST *ast_root = parser(content, len);
        // AST_print(ast_root);
        semantic_check(ast_root);
        codegen(ast_root);
        free(content);
        freeAST(ast_root);
    }
    optimize();
    return 0;
}

Token *lexer(const char *in)
{
    Token *head = NULL;
    Token **now = &head;
    for (int i = 0; in[i]; i++)
    {
        if (isspace(in[i])) // ignore space characters
            continue;
        else if (isdigit(in[i]))
        {
            (*now) = new_token(CONSTANT, atoi(in + i)); // atoi ignores the characters after those that form the integral number
            while (in[i + 1] && isdigit(in[i + 1]))
                i++;
        }
        else if ('x' <= in[i] && in[i] <= 'z') // variable
            (*now) = new_token(IDENTIFIER, in[i]);
        else
            switch (in[i])
            {
            case '=':
                (*now) = new_token(ASSIGN, 0);
                break;
            case '+':
                if (in[i + 1] && in[i + 1] == '+')
                {
                    i++;
                    // In lexer scope, all "++" will be labeled as PREINC.
                    (*now) = new_token(PREINC, 0);
                }
                // In lexer scope, all single "+" will be labeled as PLUS.
                else
                    (*now) = new_token(PLUS, 0);
                break;
            case '-':
                if (in[i + 1] && in[i + 1] == '-')
                {
                    i++;
                    // In lexer scope, all "--" will be labeled as PREDEC.
                    (*now) = new_token(PREDEC, 0);
                }
                // In lexer scope, all single "-" will be labeled as MINUS.
                else
                    (*now) = new_token(MINUS, 0);
                break;
            case '*':
                (*now) = new_token(MUL, 0);
                break;
            case '/':
                (*now) = new_token(DIV, 0);
                break;
            case '%':
                (*now) = new_token(REM, 0);
                break;
            case '(':
                (*now) = new_token(LPAR, 0);
                break;
            case ')':
                (*now) = new_token(RPAR, 0);
                break;
            case ';':
                (*now) = new_token(END, 0);
                break;
            default:
                err("Unexpected character.");
            }
        now = &((*now)->next);
    }
    return head;
}

Token *new_token(Kind kind, int val)
{
    Token *res = (Token *)malloc(sizeof(Token));
    res->kind = kind;
    res->val = val;
    res->next = NULL;
    return res;
}

size_t token_list_to_arr(Token **head)
{
    size_t res;
    Token *now = (*head), *del;
    for (res = 0; now != NULL; res++)
        now = now->next;
    now = (*head);
    if (res != 0)
        (*head) = (Token *)malloc(sizeof(Token) * res);
    for (int i = 0; i < res; i++)
    {
        (*head)[i] = (*now);
        del = now;
        now = now->next;
        free(del);
    }
    return res;
}

AST *parser(Token *arr, size_t len)
{
    for (int i = 1; i < len; i++)
    {
        // correctly identify "ADD" and "SUB"
        if (arr[i].kind == PLUS || arr[i].kind == MINUS)
        {
            switch (arr[i - 1].kind)
            {
            case PREINC:     // ++
            case PREDEC:     // --
            case IDENTIFIER: // x+
            case CONSTANT:   // 5+
            case RPAR:       // )+
                // if it is PREINC/PREDEC/IDENTIFIER/CONSTANT/RPAR
                arr[i].kind = arr[i].kind - PLUS + ADD; // plus->add  minus->sub
            default:
                break;
            }
        }
    }
    return parse(arr, 0, len - 1, STMT);
}

AST *parse(Token *arr, int l, int r, GrammarState S)
{
    AST *now = NULL;
    if (l > r)
        err("Unexpected parsing range.");
    int nxt;
    switch (S)
    {
    case STMT: // (1) x = y +++ 5;
        if (l == r && arr[l].kind == END)
            return NULL;
        else if (arr[r].kind == END)
            return parse(arr, l, r - 1, EXPR);
        else
            err("Expected \';\' at the end of line.");
    case EXPR: // (2) x = y +++ 5
        return parse(arr, l, r, ASSIGN_EXPR);
    case ASSIGN_EXPR: // (3) x = y +++ 5   (7) y +++ 5
        if ((nxt = findNextSection(arr, l, r, condASSIGN)) != -1)
        {
            now = new_AST(arr[nxt].kind, 0);                // (4) =
            now->lhs = parse(arr, l, nxt - 1, UNARY_EXPR);  // (5) x
            now->rhs = parse(arr, nxt + 1, r, ASSIGN_EXPR); // (6) y +++ 5
            return now;
        }
        return parse(arr, l, r, ADD_EXPR);
    case ADD_EXPR: // (8) y +++ 5  (12) y++
        if ((nxt = findNextSection(arr, r, l, condADD)) != -1)
        {
            now = new_AST(arr[nxt].kind, 0);             // (9) +
            now->lhs = parse(arr, l, nxt - 1, ADD_EXPR); // (10) y++
            now->rhs = parse(arr, nxt + 1, r, MUL_EXPR); // (11) 5
            return now;
        }
        return parse(arr, l, r, MUL_EXPR);
    case MUL_EXPR: // (13) y++ (18) 5
        // TODO: Implement MUL_EXPR.
        // hint: Take ADD_EXPR as reference.
        if ((nxt = findNextSection(arr, r, l, condMUL)) != -1)
        {
            now = new_AST(arr[nxt].kind, 0);
            now->lhs = parse(arr, l, nxt - 1, MUL_EXPR);
            now->rhs = parse(arr, nxt + 1, r, UNARY_EXPR);
            return now;
        }
        return parse(arr, l, r, UNARY_EXPR);
    case UNARY_EXPR: // (14) y++ (19) 5
        // TODO: Implement UNARY_EXPR.
        // hint: Take POSTFIX_EXPR as reference.
        if (arr[l].kind == PREINC || arr[l].kind == PREDEC || arr[l].kind == PLUS || arr[l].kind == MINUS)
        {
            now = new_AST(arr[l].kind, 0);
            now->mid = parse(arr, l + 1, r, UNARY_EXPR);
            return now;
        }
        return parse(arr, l, r, POSTFIX_EXPR);
    case POSTFIX_EXPR: // (15) y++ (20) 5
        if (arr[r].kind == PREINC || arr[r].kind == PREDEC)
        {
            // translate "PREINC", "PREDEC" into "POSTINC", "POSTDEC"
            now = new_AST(arr[r].kind - PREINC + POSTINC, 0); // (16) ++
            now->mid = parse(arr, l, r - 1, POSTFIX_EXPR);    // (17) y
            return now;
        }
        return parse(arr, l, r, PRI_EXPR);
    case PRI_EXPR: // (21) 5
        if (findNextSection(arr, l, r, condRPAR) == r)
        {
            now = new_AST(LPAR, 0);
            now->mid = parse(arr, l + 1, r - 1, EXPR);
            return now;
        }
        if (l == r)
        {
            if (arr[l].kind == IDENTIFIER || arr[l].kind == CONSTANT)
                return new_AST(arr[l].kind, arr[l].val); // (22) 5
            err("Unexpected token during parsing.");
        }
        err("No token left for parsing.");
    default:
        err("Unexpected grammar state.");
    }
}

AST *new_AST(Kind kind, int val)
{
    AST *res = (AST *)malloc(sizeof(AST));
    res->kind = kind;
    res->val = val;
    res->lhs = res->mid = res->rhs = NULL;
    return res;
}

int findNextSection(Token *arr, int start, int end, int (*cond)(Kind))
{
    int par = 0;
    int d = (start < end) ? 1 : -1;
    for (int i = start; (start < end) ? (i <= end) : (i >= end); i += d)
    {
        if (arr[i].kind == LPAR)
            par++;
        if (arr[i].kind == RPAR)
            par--;
        if (par == 0 && cond(arr[i].kind) == 1)
            return i;
    }
    return -1;
}

int condASSIGN(Kind kind)
{
    return kind == ASSIGN;
}

int condADD(Kind kind)
{
    return kind == ADD || kind == SUB;
}

int condMUL(Kind kind)
{
    return kind == MUL || kind == DIV || kind == REM;
}

int condRPAR(Kind kind)
{
    return kind == RPAR;
}

void semantic_check(AST *now)
{
    if (now == NULL)
        return;
    // Left operand of '=' must be an identifier or identifier with one or more parentheses.
    if (now->kind == ASSIGN)
    {
        AST *tmp = now->lhs;
        while (tmp->kind == LPAR)
            tmp = tmp->mid; // while assign's lhs is () or (((()))) search for mid which should end up with x, y, z
        if (tmp->kind != IDENTIFIER)
            err("Lvalue is required as left operand of assignment.");
        semantic_check(now->rhs);
    }
    // Operand of INC/DEC must be an identifier or identifier with one or more parentheses.
    else if (now->kind == PREINC || now->kind == PREDEC || now->kind == POSTINC || now->kind == POSTDEC)
    {
        AST *tmp = now->mid;
        while (tmp->kind == LPAR)
            tmp = tmp->mid;
        if (tmp->kind != IDENTIFIER)
            err("Value is require as operand of INC/DEC.");
    }
    else
    {
        semantic_check(now->lhs);
        semantic_check(now->mid);
        semantic_check(now->rhs);
    }
    // TODO: Implement the remaining semantic_check code.
    // hint: Follow the instruction above and ASSIGN-part code to implement.
    // hint: Semantic of each node needs to be checked recursively (from the current node to lhs/mid/rhs node).
}

#define MAXL 30
typedef struct _ASM
{
    int type; // {add 0, sub 1, mul 2, div 3, rem 4, load 5, store 6}
    char prm1[MAXL], prm2[MAXL], prm3[MAXL];
    int mem;
} ASM;
ASM final_ans[3000];
int ans_count;
char tmp[MAXL], _tmp[MAXL];
char OPS[5][4] = {"add", "sub", "mul", "div", "rem"};
int negative = 1, xyz[3], post[3]; // post_x, post_y, post_z
int r_exist[256], r_temp;
int find_r()
{ // find the current available r (r0 = x, r1 = y, r2 = z)
    for (int i = 3; i < 256; i++)
    {
        if (r_exist[i] == 0)
        {
            r_exist[i] = 1;
            return i;
        }
    }
}
int free_r(int i)
{
    if (i > 2)
        r_exist[i] = 0;
}
void setASM(int type, char prm1[12], char prm2[12], char prm3[12], int mem)
{
    final_ans[ans_count].type = type;
    final_ans[ans_count].mem = mem;
    strcpy(final_ans[ans_count].prm1, prm1);
    strcpy(final_ans[ans_count].prm2, prm2);
    strcpy(final_ans[ans_count].prm3, prm3);
    ans_count++;
}

char *codegen(AST *now)
{
    AST *tmp_ast;
    if (now == NULL)
        return "\0";
    char tmp1[MAXL], tmp2[MAXL], tmp3[MAXL], tmp4[MAXL], tmp5[MAXL];
    int _tmp1, _tmp2, t1 = 1, t2 = 1;
    switch (now->kind)
    {
    case ASSIGN:
        tmp_ast = now->lhs;
        while (tmp_ast->kind != IDENTIFIER)
            tmp_ast = tmp_ast->mid;
        _tmp1 = (tmp_ast->val - 'x') * 4;
        strcpy(tmp1, codegen(now->rhs));
        _tmp2 = atoi(tmp1 + 1);
        free_r(_tmp2);
        strcpy(tmp2, "r");
        sprintf(_tmp, "%d", tmp_ast->val - 'x');
        strcat(tmp2, _tmp);
        if (tmp1[0] != 'r' && atoi(tmp1) < 0)
        {
            sprintf(tmp1, "%d", (-atoi(tmp1)));
            setASM(1, tmp2, "0", tmp1, -1); // update r0
        }
        else
        {
            setASM(0, tmp2, "0", tmp1, -1); // update r0
        }
        setASM(6, tmp2, "\0", "\0", _tmp1); // store r0 x
        xyz[tmp_ast->val - 'x'] = 1;
        for (int i = 0; i < 3; i++)
        {
            if (post[i])
            {
                strcpy(tmp1, "r");
                sprintf(_tmp, "%d", i);
                strcat(tmp1, _tmp);
                setASM(0, tmp1, tmp1, "1", -1);
                setASM(6, tmp1, "\0", "\0", i * 4);
                post[i] = 0;
            }
            else if (post[i])
            {
                strcpy(tmp1, "r");
                sprintf(_tmp, "%d", i);
                strcat(tmp1, _tmp);
                setASM(1, tmp1, tmp1, "1", -1);
                setASM(6, tmp1, "\0", "\0", i * 4);
                post[i] = 0;
            }
        }
        strcpy(tmp, tmp2);
        return tmp;
    case IDENTIFIER:
        // printf("IDTF %c\n", (char)now->val);
        if (!xyz[now->val - 'x'])
        {
            strcpy(tmp1, "r");
            sprintf(_tmp, "%d", now->val - 'x');
            strcat(tmp1, _tmp);
            setASM(5, tmp1, "\0", "\0", (now->val - 'x') * 4);
            xyz[now->val - 'x'] = 1;
        }
        if (negative == -1)
        {
            strcpy(tmp1, "r");
            sprintf(_tmp, "%d", find_r());
            strcat(tmp1, _tmp);
            strcpy(tmp2, "r");
            sprintf(_tmp, "%d", now->val - 'x');
            strcat(tmp2, _tmp);
            setASM(1, tmp1, "0", tmp2, -1);
            negative = 1;
            strcpy(tmp, tmp1);
            return tmp;
        }
        strcpy(tmp, "r");
        sprintf(_tmp, "%d", now->val - 'x');
        strcat(tmp, _tmp);
        return tmp;
    case CONSTANT:
        // printf("returning %d\n", now->val);
        if (negative == 1)
        {
            strcpy(tmp1, "r");
            sprintf(_tmp, "%d", find_r());
            strcat(tmp1, _tmp);
            sprintf(_tmp, "%d", now->val);
            strcpy(tmp2, _tmp);
            setASM(0, tmp1, "0", tmp2, -1);
        }
        else
        {
            strcpy(tmp1, "r");
            sprintf(_tmp, "%d", find_r());
            strcat(tmp1, _tmp);
            sprintf(_tmp, "%d", now->val);
            strcpy(tmp2, _tmp);
            setASM(1, tmp1, "0", tmp2, -1);
            negative = 1;
        }
        strcpy(tmp, tmp1);
        return tmp;
    case PREINC:
        tmp_ast = now->mid;
        while (tmp_ast->kind != IDENTIFIER)
            tmp_ast = tmp_ast->mid;
        strcpy(tmp1, codegen(tmp_ast));
        setASM(0, tmp1, tmp1, "1", -1);
        setASM(6, tmp1, "\0", "\0", (tmp_ast->val - 'x') * 4);
        strcpy(tmp, tmp1);
        return tmp;
    case PREDEC:
        tmp_ast = now->mid;
        while (tmp_ast->kind != IDENTIFIER)
            tmp_ast = tmp_ast->mid;
        strcpy(tmp1, codegen(tmp_ast));
        setASM(1, tmp1, tmp1, "1", -1);
        setASM(6, tmp1, "\0", "\0", (tmp_ast->val - 'x') * 4);
        strcpy(tmp, tmp1);
        return tmp;
    case POSTINC:
        tmp_ast = now->mid;
        while (tmp_ast->kind != IDENTIFIER)
            tmp_ast = tmp_ast->mid;
        switch (tmp_ast->val)
        {
        case 'x':
            post[0] = 1;
            break;
        case 'y':
            post[1] = 1;
            break;
        case 'z':
            post[2] = 1;
            break;
        default:
            err("Unexpected value during POSTINC");
            break;
        }
        return codegen(tmp_ast);
    case POSTDEC:
        tmp_ast = now->mid;
        while (tmp_ast->kind != IDENTIFIER)
            tmp_ast = tmp_ast->mid;
        switch (tmp_ast->val)
        {
        case 'x':
            post[0] = -1;
            break;
        case 'y':
            post[1] = -1;
            break;
        case 'z':
            post[2] = -1;
            break;
        default:
            err("Unexpected value during POSTDEC");
            break;
        }
        return codegen(tmp_ast);
    case LPAR:
    case RPAR:
        return codegen(now->mid);
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case REM:
        tmp_ast = now->lhs;
        if (tmp_ast->kind == LPAR || tmp_ast->kind == CONSTANT)
        {
            while (tmp_ast->kind == LPAR)
                tmp_ast = tmp_ast->mid;
            if (tmp_ast->kind == CONSTANT)
            {
                sprintf(tmp1, "%d", tmp_ast->val);
                t1 = 0;
            }
            else
            {
                strcpy(tmp1, codegen(tmp_ast));
            }
        }
        else
        {
            strcpy(tmp1, codegen(now->lhs));
        }
        tmp_ast = now->rhs;
        if (tmp_ast->kind == LPAR || tmp_ast->kind == CONSTANT)
        {
            while (tmp_ast->kind == LPAR)
                tmp_ast = tmp_ast->mid;
            if (tmp_ast->kind == CONSTANT)
            {
                sprintf(tmp2, "%d", tmp_ast->val);
                t2 = 0;
            }
            else
            {
                strcpy(tmp2, codegen(tmp_ast));
            }
        }
        else
        {
            strcpy(tmp2, codegen(now->rhs));
        }
        if ((!t1 && !t2) || (!t1 && tmp2[0] != 'r') || (tmp1[0] != 'r' && !t2))
        {
            switch (now->kind)
            {
            case ADD:
                sprintf(_tmp, "%d", (atoi(tmp1) + atoi(tmp2)));
                break;
            case SUB:
                sprintf(_tmp, "%d", (atoi(tmp1) - atoi(tmp2)));
                break;
            case MUL:
                sprintf(_tmp, "%d", (atoi(tmp1) * atoi(tmp2)));
                break;
            case DIV:
                sprintf(_tmp, "%d", (atoi(tmp1) / atoi(tmp2)));
                break;
            case REM:
                sprintf(_tmp, "%d", (atoi(tmp1) % atoi(tmp2)));
                break;
            default:
                err("");
            }
            return _tmp;
        }
        if (t1 && tmp1[0] == 'r')
        {
            free_r(atoi(tmp1 + 1));
        }
        else
            t1 = 1;
        if (t2 && tmp2[0] == 'r')
        {
            free_r(atoi(tmp2 + 1));
        }
        else
            t2 = 1;
        strcpy(tmp3, "r");
        sprintf(_tmp, "%d", find_r());
        strcat(tmp3, _tmp);
        int change_1 = 0, change_2 = 0;
        if (tmp1[0] != 'r' && atoi(tmp1) < 0)
        { // deal with negative
            sprintf(tmp1, "%d", (-atoi(tmp1)));
            strcpy(tmp4, "r");
            sprintf(_tmp, "%d", find_r());
            strcat(tmp4, _tmp);
            setASM(1, tmp4, "0", tmp1, -1);
            change_1 = 1;
        }
        if (tmp2[0] != 'r' && atoi(tmp2) < 0)
        { // deal with negative
            sprintf(tmp2, "%d", (-atoi(tmp2)));
            strcpy(tmp5, "r");
            sprintf(_tmp, "%d", find_r());
            strcat(tmp5, _tmp);
            setASM(1, tmp5, "0", tmp2, -1);
            change_2 = 1;
        }
        if (!change_1 && !change_2)
            setASM(now->kind - ADD, tmp3, tmp1, tmp2, -1);
        else if (change_1 && change_2)
            setASM(now->kind - ADD, tmp3, tmp4, tmp5, -1);
        else if (change_1)
            setASM(now->kind - ADD, tmp3, tmp4, tmp2, -1);
        else if (change_2)
            setASM(now->kind - ADD, tmp3, tmp1, tmp5, -1);
        strcpy(tmp, tmp3);
        return tmp;
    case PLUS:
        return codegen(now->mid);
    case MINUS:
        negative *= -1;
        return codegen(now->mid);
    default:
        err("Unexpected token during codegen");
    }
}
// ADD, SUB, MUL, DIV, REM, PREINC, PREDEC, POSTINC, POSTDEC, IDENTIFIER, CONSTANT, LPAR, RPAR, PLUS, MINUS, END

int r_store[256], r_use[256];
void optimize()
{

    for (int i = ans_count - 1; i >= 0; i--)
    {
        // store and change
        int prm1 = atoi(final_ans[i].prm1 + 1);
        if (final_ans[i].type == 6)
        {
            if (!r_store[prm1])
            {
                r_store[prm1] = 1; // found a store
            }
            else
            {
                final_ans[i].type = -1; // if already stored i don't need another one
            }
        }
        else
        { // change r0 r1 r2
            if (!r_use[prm1])
            {
                final_ans[i].type = -1; // if I don't use r0 between these two store, I don't need the previous one
            }
            else
            {
                r_use[prm1] = 0;
            }
        }
        // use
        // prm2, prm3, prm1 for store
        if (final_ans[i].type == 6)
        {
            r_use[atoi(final_ans[i].prm1 + 1)] = 1;
        }
        else if (final_ans[i].type != -1)
        {
            if (final_ans[i].prm2[0] == 'r')
                r_use[atoi(final_ans[i].prm2 + 1)] = 1;
            if (final_ans[i].prm3[0] == 'r')
                r_use[atoi(final_ans[i].prm3 + 1)] = 1;
        }
    }
    for (int i = 0; i < ans_count; i++)
    {
        if (final_ans[i].type == 5)
        {
            printf("load %s [%d]\n", final_ans[i].prm1, final_ans[i].mem);
        }
        else if (final_ans[i].type == 6)
        {
            printf("store [%d] %s\n", final_ans[i].mem, final_ans[i].prm1);
        }
        else if (final_ans[i].type != -1)
        {
            printf("%s %s %s %s\n", OPS[final_ans[i].type], final_ans[i].prm1, final_ans[i].prm2, final_ans[i].prm3);
        }
    }
}

void freeAST(AST *now)
{
    if (now == NULL)
        return;
    freeAST(now->lhs);
    freeAST(now->mid);
    freeAST(now->rhs);
    free(now);
}

void token_print(Token *in, size_t len)
{
    const static char KindName[][20] = {
        "Assign", "Add", "Sub", "Mul", "Div", "Rem", "Inc", "Dec", "Inc", "Dec", "Identifier", "Constant", "LPar", "RPar", "Plus", "Minus", "End"};
    const static char KindSymbol[][20] = {
        "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "\"++\"", "\"--\"", "\"++\"", "\"--\"", "", "", "'('", "')'", "'+'", "'-'"};
    const static char format_str[] = "<Index = %3d>: %-10s, %-6s = %s\n";
    const static char format_int[] = "<Index = %3d>: %-10s, %-6s = %d\n";
    for (int i = 0; i < len; i++)
    {
        switch (in[i].kind)
        {
        case LPAR:
        case RPAR:
        case PREINC:
        case PREDEC:
        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case REM:
        case ASSIGN:
        case PLUS:
        case MINUS:
            printf(format_str, i, KindName[in[i].kind], "symbol", KindSymbol[in[i].kind]);
            break;
        case CONSTANT:
            printf(format_int, i, KindName[in[i].kind], "value", in[i].val);
            break;
        case IDENTIFIER:
            printf(format_str, i, KindName[in[i].kind], "name", (char *)(&(in[i].val)));
            break;
        case END:
            printf("<Index = %3d>: %-10s\n", i, KindName[in[i].kind]);
            break;
        default:
            puts("=== unknown token ===");
        }
    }
}

void AST_print(AST *head)
{
    static char indent_str[MAX_LENGTH] = "";
    static int indent = 0;
    char *indent_now = indent_str + indent;
    const static char KindName[][20] = {
        "Assign", "Add", "Sub", "Mul", "Div", "Rem", "PreInc", "PreDec", "PostInc", "PostDec", "Identifier", "Constant", "Parentheses", "Parentheses", "Plus", "Minus"};
    const static char format[] = "%s\n";
    const static char format_str[] = "%s, <%s = %s>\n";
    const static char format_val[] = "%s, <%s = %d>\n";
    if (head == NULL)
        return;
    indent_str[indent - 1] = '-';
    printf("%s", indent_str);
    indent_str[indent - 1] = ' ';
    if (indent_str[indent - 2] == '`')
        indent_str[indent - 2] = ' ';
    switch (head->kind)
    {
    case ASSIGN:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case REM:
    case PREINC:
    case PREDEC:
    case POSTINC:
    case POSTDEC:
    case LPAR:
    case RPAR:
    case PLUS:
    case MINUS:
        printf(format, KindName[head->kind]);
        break;
    case IDENTIFIER:
        printf(format_str, KindName[head->kind], "name", (char *)&(head->val));
        break;
    case CONSTANT:
        printf(format_val, KindName[head->kind], "value", head->val);
        break;
    default:
        puts("=== unknown AST type ===");
    }
    indent += 2;
    strcpy(indent_now, "| ");
    AST_print(head->lhs);
    strcpy(indent_now, "` ");
    AST_print(head->mid);
    AST_print(head->rhs);
    indent -= 2;
    (*indent_now) = '\0';
}

// todo1: 7+8+6+9; (statement without assign)
// todo2: x = 1+5+689+48978/5494; (previous statement is useless)
//        x = 5;
