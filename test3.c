#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TBLSIZE 65535
#define MAXLEN 256

typedef enum
{
    UNKNOWN,
    END,
    INT,
    ID,
    ADDSUB,
    MULDIV,
    ASSIGN,
    LPAREN,
    RPAREN,
    ENDFILE
} TokenSet;
typedef enum
{
    MISPAREN,
    NOTNUMID,
    NOTFOUND,
    RUNOUT
} ErrorType;

/*to remember ID's value*/
/*ex x=5;
name[0]='x';
name[0]'s value is 5*/
typedef struct
{
    /*the name of the ID*/
    char name[MAXLEN];
    /*the value of the ID*/
    int val;
} Symbol;
Symbol table[TBLSIZE];

typedef struct _Node
{
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode;

char *getLexeme(void);

static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

int getval(void);
int setval(char *str, int val);
int match(TokenSet token);
int evaluateTree(BTNode *root);

BTNode *makeNode(TokenSet tok, const char *lexe);
BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);

void advance(void);
void statement(void);
void error(ErrorType errorNum);
void freeTree(BTNode *root);

int sbcount = 0;
int pos = 0;
/*err=0 no error err=1 there are some errors*/
int err;

int main()
{
    // printf(">> ");
    while (1)
    {
        statement();
    }
    return 0;
}
/*statement   := END | expr END*/
void statement(void)
{
    BTNode *retp;
    pos = 0;
    int ans;
    if (match(ENDFILE))
    {
        if (err == 0)
            printf("EXIT 0\n");
        exit(0);
    }
    else if (match(END))
    {
        advance();
    }
    else
    {
        retp = expr();
        if (match(END))
        {
            if (retp->data == ASSIGN)
            {
                evaluateTree(retp);
                printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\n");
                // printf("ans: %d\n", evaluateTree(retp));
            }
            else if (retp->data != ASSIGN)
            {
                error(NOTNUMID);
            }
            printf("retp->lexeme: %s\n", retp->lexeme);
            printPrefix(retp);
            printf("\n");
            freeTree(retp);
            advance();
        }
    }
}
int evaluateTree(BTNode *root)
{
    int retval = 0, lv, rv;
    int r0, r4, r8;
    if (root != NULL)
    {
        switch (root->data)
        {
        case INT:
            retval = root->val;
            printf("MOV r%d %d\n", pos, root->val);
            pos++;
            break;
        case ID:
            //!!!!!!!!!!!
            retval = root->val;
            if (strcmp(root->lexeme, "x") == 0)
            {
                printf("MOV r%d [0]\n", pos);
                pos++;
            }
            else if (strcmp(root->lexeme, "y") == 0)
            {
                printf("MOV r%d [4]\n", pos);
                pos++;
            }
            else if (strcmp(root->lexeme, "z") == 0)
            {
                printf("MOV r%d [8]\n", pos);
                pos++;
            }
            break;
        /*to compute the value*/
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0)
            {
                printf("ADD r%d r%d\n", pos - 2, pos - 1);
                retval = lv + rv;
                pos--;
            }
            else if (strcmp(root->lexeme, "-") == 0)
            {
                printf("SUB r%d r%d\n", pos - 2, pos - 1);
                retval = lv - rv;
                pos--;
            }
            else if (strcmp(root->lexeme, "*") == 0)
            {
                printf("MUL r%d r%d\n", pos - 2, pos - 1);
                retval = lv * rv;
                pos--;
            }
            else if (strcmp(root->lexeme, "/") == 0)
            {
                printf("DIV r%d r%d\n", pos - 2, pos - 1);
                retval = lv / rv;
                pos--;
            }
            else if (strcmp(root->lexeme, "=") == 0)
            {
                if (strcmp(root->left->lexeme, "x") == 0)
                {
                    printf("MOV [0] r%d\n", pos - 1);
                    r0 = retval;
                }
                else if (strcmp(root->left->lexeme, "y") == 0)
                {
                    printf("MOV [4] r%d\n", pos - 1);
                    r4 = retval;
                }
                else if (strcmp(root->left->lexeme, "z") == 0)
                {
                    printf("MOV [8] r%d\n", pos - 1);
                    r8 = retval;
                }
                retval = setval(root->left->lexeme, rv);
            }
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}
void error(ErrorType errorNum)
{
    err = 1;
    switch (errorNum)
    {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        printf("EXIT 1\n");
        break;
    case NOTNUMID:
        /*3++ should be here*/
        fprintf(stderr, "Number or identifier expected\n");
        printf("EXIT 1\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", getLexeme());
        printf("EXIT 1\n");
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
        printf("EXIT 1\n");
        break;
    }
    exit(0);
}
TokenSet getToken(void)
{
    int i;
    int sum_ID = 0;
    char c;

    while ((c = fgetc(stdin)) == ' ' || c == '\t')
        ; // 忽略空白字元

    if (isdigit(c))
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN)
        {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    }
    else if (c == '+' || c == '-')
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    }
    else if (c == '*' || c == '/')
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n')
    {
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=')
    {
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(')
    {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')')
    {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (isalpha(c) || c == '_')
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        /*int flag=0;
        if(isalpha(c)) flag=1;
        c = fgetc(stdin);
        if(isalpha(c) && flag==1) error(NOTNUMID);*/
        int flag = 0;
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_')
        {
            flag = 1;
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        if (flag == 1)
            error(NOTFOUND);
        lexeme[i] = '\0';
        return ID;
    }
    else if (c == EOF)
    {
        return ENDFILE;
    }
    else
    {
        return UNKNOWN;
    }
}
void advance(void)
{
    lookahead = getToken();
}
int match(TokenSet token)
{
    if (lookahead == UNKNOWN)
        advance();
    return token == lookahead;
}
char *getLexeme(void)
{
    return lexeme;
}
int getval(void)
{ /*看看這個token對應的整數值是多少*/
    int i, retval, found;

    if (match(INT))
    {
        /*string==>123=atoi("123")*/
        retval = atoi(getLexeme());
    }
    else if (match(ID))
    {
        i = 0;
        found = 0;
        retval = 0;
        while (i < sbcount && !found)
        {
            /*ex. "x" 看有沒有再table裡面*/
            if (strcmp(getLexeme(), table[i].name) == 0)
            {
                /*to get the value*/
                retval = table[i].val;
                found = 1;
                break;
            }
            else
            {
                i++;
            }
        }
        /*cannot find the ID in the table*/
        if (!found)
        {
            if (sbcount < TBLSIZE)
            {
                /*to create one in the table*/
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            }
            else
            {
                error(RUNOUT);
            }
        }
    }
    return retval;
}
/* "x" to set  */
int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    /*to search , sbcount目前有多少個變數*/
    while (i < sbcount)
    {
        /*to find the ID in the table*/
        if (strcmp(str, table[i].name) == 0)
        {
            /*if 有  "x" to set val*/
            table[i].val = val;
            /*to cover the val*/
            retval = val;
            break;
        }
        else
        {
            i++;
        }
    }
    /*return the new value*/
    return retval;
}
/* create a node without any child.*/
BTNode *makeNode(TokenSet tok, const char *lexe)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree(BTNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode *factor(void)
{
    BTNode *retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT))
    {
        retp = makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    }
    else if (match(ID))
    {
        BTNode *left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();

        if (match(ASSIGN))
        {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        }
        else
        {
            retp = left;
        }
    }
    else if (match(ADDSUB))
    {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT))
        {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            /*應該可以改成負號*/
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        }
        else
        {
            error(NOTNUMID);
        }
    }
    else if (match(LPAREN))
    {
        advance();
        retp = expr();
        if (match(RPAREN))
        {
            advance();
        }
        else
        {
            error(MISPAREN);
        }
    }
    else
    {
        error(NOTNUMID);
    }
    return retp;
}
/*  term        := factor term_tail*/
BTNode *term(void)
{
    BTNode *node;

    node = factor();

    return term_tail(node);
}
/*term_tail := MULDIV factor term_tail | NIL*/
BTNode *term_tail(BTNode *left)
{
    BTNode *node;

    if (match(MULDIV))
    {
        node = makeNode(MULDIV, getLexeme());
        advance();

        node->left = left;
        node->right = factor();

        return term_tail(node);
    }
    else
        return left;
}
/*  expr        := term expr_tail*/
BTNode *expr(void)
{
    BTNode *node;

    node = term();
    /*+3 or 3+ should be illegal*/
    return expr_tail(node);
}
/*  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode *expr_tail(BTNode *left)
{
    BTNode *node;
    /*match這個token*/
    if (match(ADDSUB))
    {
        /*吃掉這個token*/
        node = makeNode(ADDSUB, getLexeme());
        /*再Advance*/
        advance();

        node->left = left;
        node->right = term();

        return expr_tail(node);
    }
    else
        return left;
}

void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}