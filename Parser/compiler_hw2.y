/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_SIZE 100
#define SYMBOL_TABLE_SIZE 200

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int currScopeLevel = 0;
int currIndex = 0;

typedef struct {
    int index;
    char name[VAR_SIZE];
    char entryName[VAR_SIZE];
    char dataType[VAR_SIZE];
    int scopeLevel[VAR_SIZE];
    char formalParameters[VAR_SIZE];
} SymbolEntry;

SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char* string;
}

/* Token without return */

%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token AND OR NOT
%token LB RB LCB RCB LSB RSB COMMA SEMICOLON QUOTA
%token PRINT 
%token IF ELSE FOR WHILE
//%token STRING INT FLOAT VOID BOOL
%token TRUE FALSE
%token RET CONT BREAK
%token COMMENT

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
%token <string> ID

%token <string> STRING INT FLOAT VOID BOOL

/* Nonterminal with return, which need to sepcify type */
%type <string> declarator
%type <string> type_specifier

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : external_declaration
    | program external_declaration
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : type_specifier declarator compound_statement  { printf("function [%s]\n", $1); }
    | type_specifier declarator declaration_list compound_statement //for what?
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

compound_statement
    : LCB RCB
    | LCB block_item_list RCB
    ;

block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;

statement
    : compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | print_func
    ;

expression_statement
    : SEMICOLON
    | expression SEMICOLON
    ;

expression
    : assignment_expression
    | expression COMMA assignment_expression
    ;

selection_statement
    : IF LB expression RB statement ELSE statement
    | IF LB expression RB statement
    ;

iteration_statement
    : WHILE LB expression RB statement
    | FOR LB expression_statement expression_statement RB statement
    | FOR LB expression_statement expression_statement expression RB statement
    | FOR LB declaration expression_statement RB statement
    | FOR LB declaration expression_statement expression RB statement
    ;

jump_statement
    : CONT SEMICOLON
    | BREAK SEMICOLON
    | RET SEMICOLON
    | RET expression SEMICOLON
    ;

print_func
    : PRINT LB STR_CONST RB SEMICOLON
    | PRINT LB ID RB SEMICOLON
    ;

//------------------
declaration
    : type_specifier init_declarator_list SEMICOLON
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator
    : declarator
    | declarator ASGN initializer
    ;

declarator //direct_declarator
    : ID
    | LB declarator RB //for what?
    | declarator LB parameter_list RB
    | declarator LB RB 
    | declarator LB identifier_list RB
    ;

parameter_list // parameter_type_list
    : parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;

parameter_declaration
    : type_specifier declarator { printf("parameter [%s] level %d\n", $1, currScopeLevel); }
    | type_specifier //for what?
    ;

identifier_list
    : ID
    | identifier_list COMMA ID
    ;

initializer
    : assignment_expression
    ;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

conditional_expression
    : logical_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR logical_and_expression
    ;

logical_and_expression
    : equality_expression
    | logical_and_expression AND equality_expression
    ;

equality_expression
    : relational_expression
    | equality_expression EQ relational_expression
    | equality_expression NE relational_expression
    ;

relational_expression
    : additive_expression
    | relational_expression MT additive_expression
    | relational_expression LT additive_expression
    | relational_expression MTE additive_expression
    | relational_expression LTE additive_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression ADD multiplicative_expression
    | additive_expression SUB multiplicative_expression
    ;

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression
    | multiplicative_expression DIV unary_expression
    | multiplicative_expression MOD unary_expression

unary_expression
    : postfix_expression
    | INC unary_expression
    | DEC unary_expression
    ;

postfix_expression
    : primary_expression
    | postfix_expression LB RB
    | postfix_expression LB argument_expression_list RB
    | postfix_expression INC
    | postfix_expression DEC
    ;

primary_expression
    : ID
    | I_CONST
    | F_CONST
    | STR_CONST
    | TRUE
    | FALSE
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

assignment_operator
    : ASGN
    | MULASGN
    | DIVASGN
    | MODASGN
    | ADDASGN
    | SUBASGN

/* actions can be taken when meet the token or rule */
type_specifier // declaration_specifiers
    : INT
    | FLOAT
    | BOOL
    | STRING
    | VOID
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    yyparse();
	printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {}
void insert_symbol() {}
int lookup_symbol() {}
void dump_symbol() {
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
}
