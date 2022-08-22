struct symbol
{
    char *name;
    double value;
    struct ast *func;
    struct symlist *syms;
};

#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);

struct symlist
{
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

// built-in function type
enum bifs
{
    B_sqrt = 1,
    B_exp,
    B_log,
    B_print
};

struct ast
{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

/*  node type
    + - * / |
    0-7 比较操作符，位编码：04 等于， 02 小于， 01 大于
    M 单目负号
    L 表达式或者语句列表
    I IF 语句
    W WHILE 语句
    N 符号引用
    = 赋值
    S 符号列表
    F 内置函数调用
    C 用户函数调用
*/

// built-in function struct
struct fncall
{
    int nodetype;
    struct ast *l;
    enum bifs functype;
};

// user define function struct
struct ufncall
{
    int nodetype;
    struct ast *l;
    struct symbol *s;
};

struct flow
{
    int nodetype; // type: I or W
    struct ast *cond;
    struct ast *tl; // then or do branch
    struct ast *el; // optional else branch
};

struct numval
{
    int nodetype; // type: K
    double number;
};

struct symref
{
    int nodetype; // type: N
    struct symbol *s;
};

struct symasgn
{
    int nodetype; // type: =
    struct symbol *s;
    struct ast *v;
};

// construct abstract tree
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newflow(int flowtype, struct ast *cond, struct ast *tl, struct ast *tr);

// define function
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

// calculate abstract tree
double eval(struct ast *);

// delete and free abstract tree
void treefree(struct ast *);

extern int yylineno;
void yyerror(char *s, ...);