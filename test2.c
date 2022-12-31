int postIncDec[3]; // [0]='x' , [1] ='y', [2] = 'y';
int sign;          // negative = 0 , positive == 1;
int Rarray[256];
int LoadCheck[3] = {0, 0, 0}; // check whether X Y Z is loaded;

int findR() // find the empty R number
{
    for (int i = 3; i < 256; i++)
    {
        if (!Rarray[i])
        {
            Rarray[i] = 1;
            return i;
        }
    }
}

void check(int num)
{
    if (num > 2)
        Rarray[num] = 0;
}

void LoadXYZ(int num) // print Load of X, Y, Z;
{
    printf("load r%d [%d]\n", num, num * 4);
    LoadCheck[num] = 1;
}

AST *temp;
int num, left, right;
if (root == NULL)
    return "\0";
switch (root->kind)
{
case END:    //";"
case ASSIGN: //"="
    temp = root->lhs;
    while (temp->kind != IDENTIFIER)
        temp = temp->mid;
    // printf("NO");
    num = codegen(root->rhs);
    // check(num + 1);
    if (num < 0)
        printf("sub r%d 0 r%d\n", temp->val - 'x', num);
    else
        printf("add r%d 0 r%d\n", temp->val - 'x', num);
    printf("store [%d] r%d\n", (temp->val - 'x') * 4, temp->val - 'x');
case ADD: //"+"
    // return codegen(root->mid);
    left = codegen(root->lhs);
    right = codegen(root->rhs);
    printf("add r%d r%d r%d\n", left, left, right);
    return left;
case SUB: //"-"
    left = codegen(root->lhs);
    right = codegen(root->rhs);
    printf("sub r%d r%d r%d\n", left, left, right);
    return left;
case MUL: //"*"
    left = codegen(root->lhs);
    right = codegen(root->rhs);
    printf("mul r%d r%d r%d\n", left, left, right);
    return left;
case DIV: //"/"
    left = codegen(root->lhs);
    right = codegen(root->rhs);
    printf("div r%d r%d r%d\n", left, left, right);
    return left;
case REM: //"%"
    left = codegen(root->lhs);
    right = codegen(root->rhs);
    printf("rem r%d r%d r%d\n", left, left, right);
    return left;
case PREINC: //"++"
    temp = root->mid;
    while (temp->kind != IDENTIFIER)
        temp = temp->mid;
    num = codegen(temp);
    printf("add r%d r%d 1\n", num, num);
    printf("store [%d] r%d\n", (temp->val - 'x') * 4, num);
    return num;
case PREDEC: //"--"
    temp = root->mid;
    while (temp->kind != IDENTIFIER)
        temp = temp->mid;
    num = codegen(temp);
    printf("sub r%d r%d 1\n", num, num);
    printf("store [%d] r%d\n", (temp->val - 'x') * 4, num);
    return num;
case POSTINC: //"++"
    temp = root->mid;
    while (temp->kind != IDENTIFIER)
        temp = temp->mid;
    if (temp->val == 'x')
        printf("add r%d 1 r%d\n", temp->val - 'x', temp->val - 'x');
    else if (temp->val == 'y')
        printf("add r%d 1 r%d\n", temp->val - 'x', temp->val - 'x');
    else if (temp->val == 'z')
        printf("add r%d 1 r%d\n", temp->val - 'x', temp->val - 'x');
    else
        err("Unexpected value during POSTINC");
    printf("store [%d] r%d\n", (temp->val - 'x') * 4, temp->val - 'x');
    return codegen(temp);
case POSTDEC: //"--"
    temp = root->mid;
    while (temp->kind != IDENTIFIER)
        temp = temp->mid;
    if (temp->val == 'x')
        printf("sub r%d r%d 1\n", temp->val - 'x', temp->val - 'x');
    else if (temp->val == 'y')
        printf("sub r%d r%d 1\n", temp->val - 'x', temp->val - 'x');
    else if (temp->val == 'z')
        printf("add r%d 1 r%d\n", temp->val - 'x', temp->val - 'x');
    else
        err("Unexpected value during POSTINC");
    printf("store [%d] r%d\n", (temp->val - 'x') * 4, temp->val - 'x');
    return codegen(temp);
case PLUS: //"+"
    return codegen(root->mid);
case MINUS: //"-"
    if (sign)
        sign = 0;
    else
        sign = 1;
    return codegen(root->mid);
case IDENTIFIER: // xyz
    // printf("yes");
    if (LoadCheck[root->val - 'x'] != 1)
    {
        LoadXYZ(root->val - 'x');
    }
    temp = root->rhs;
    if (temp->kind == END)
    {
        return root->val - 'x';
    }
    else
    {
        return codegen(temp);
    }
case CONSTANT: // 123
    num = findR();
    printf("add r%d 0 %d\n", num, root->val);
    return num;
case LPAR: //"("
    return codegen(root->mid);
case RPAR: //")"
    return codegen(root->mid);
default:
    err("Unexpected token during codegen");
}