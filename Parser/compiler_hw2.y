/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_SIZE 100
#define SYMBOL_TABLE_SIZE 200
#define ERROR_MESSAGE_SIZE 200
#define ERROR_BUFF_SIZE 100

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int currScopeLevel = 0;
int currIndex = -1;

char errorBuff[ERROR_BUFF_SIZE][ERROR_MESSAGE_SIZE];
int errorIndex = -1;

typedef struct {
    //int index;
    char name[VAR_SIZE];
    char entryType[VAR_SIZE];
    char dataType[VAR_SIZE];
    int scopeLevel;
    char formalParameters[VAR_SIZE];
    int isPreDeclared;
} SymbolEntry;

SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];


void printSymbolTable(int startIndex);
void init_symbolEntry();

void clearSymbolEntries(int headIndex, int tailIndex);

void insert_var_declaration(char* dataType, char* varNames);
void insert_param_declaration(char* dataType, char* varNames);
void insert_funct_declaration(char* dataType, char* nameAndParam);

void popErrorBuff();
void pushErrorBuff(char errorMessage[ERROR_MESSAGE_SIZE]);

int checkRedeclare(char entryType[VAR_SIZE], char name[VAR_SIZE]);
/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol(char name[VAR_SIZE], char entryType[VAR_SIZE], 
                    char dataType[VAR_SIZE], int scopeLevel, char formalParam[VAR_SIZE], int isPreDeclared);
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
%token RET CONT BREAK
%token COMMENT

/* Token with return, which need to sepcify type */
/*%token <i_val> I_CONST
%token <f_val> F_CONST*/
%token <string> STR_CONST I_CONST F_CONST
%token <string> ID 
%token <string> TRUE
%token <string> FALSE

%token <string> STRING INT FLOAT VOID BOOL

/* Nonterminal with return, which need to sepcify type */
%type <string> type_specifier

%type <string> declarator
%type <string> identifier_list
%type <string> primary_expression

%type <string> parameter_declaration 
%type <string> parameter_list

%type <string> init_declarator
%type <string> init_declarator_list

%type <string> postfix_expression
/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : external_declaration { /*printSymbolTable(0);*/  }
    | program external_declaration { printSymbolTable(0); }
    | 
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : type_specifier declarator compound_statement { insert_funct_declaration($1, $2); } //==================================================
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
    | expression SEMICOLON { popErrorBuff(); }
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
    | PRINT LB ID RB SEMICOLON { lookup_symbol($3); popErrorBuff(); }
    ;

//------------------
declaration
    : type_specifier init_declarator_list SEMICOLON { insert_var_declaration($1, $2); }//==============================================================
    ;

init_declarator_list
    : init_declarator { $$ = $1; }
    | init_declarator_list COMMA init_declarator { strcat($1, ", "); $$ = strcat($1, $3); }
    ;

init_declarator
    : declarator { $$ = $1; }
    | declarator ASGN initializer { $$ = $1; }
    ;

declarator //direct_declarator
    : ID { $$ = $1; }
    | LB declarator RB //for what?
    | declarator LB parameter_list RB { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; strcat(tmp, $1);
                                        /*seperate parameter*/ strcat(tmp, "##"); $$ = strcat(tmp, $3); }
    | declarator LB RB { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; $$ = strcat(tmp, $1); }
    | declarator LB identifier_list RB
    ;

parameter_list // parameter_type_list
    : parameter_declaration { $$ = $1; }
    | parameter_list COMMA parameter_declaration { strcat($1, ", "); $$ = strcat($1, $3); }
    ;

parameter_declaration
    : type_specifier declarator { $$ = $1; insert_param_declaration($1, $2); }
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
    : postfix_expression { lookup_symbol($1); }
    | INC unary_expression
    | DEC unary_expression
    ;

postfix_expression
    : primary_expression { $$ = $1; }
    | postfix_expression LB RB { char tmp[VAR_SIZE] = "#"; $$ =strcat(tmp, $1); }
    | postfix_expression LB argument_expression_list RB { char tmp[VAR_SIZE] = "#"; $$ =strcat(tmp, $1); }
    | postfix_expression INC { $$ = $1; }
    | postfix_expression DEC { $$ = $1; }
    ;

primary_expression
    : ID { $$ = $1; }
    | I_CONST { $$ = "@"; }
    | F_CONST { $$ = "@"; }
    | STR_CONST { $$ = "@"; }
    | TRUE { $$ = "@"; }
    | FALSE { $$ = "@"; }
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
    yylineno = 1;
    printf("fuck u");
    printf("%d: ", yylineno);

    yyparse();
	printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    printf("\n\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n");
}



void printSymbolTable(int startIndex) {

    printf("\n\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    for (int i = startIndex ; i <= currIndex ; ++i) {
        printf("%-10d%-10s%-12s%-10s%-10d%-10s\n",
           i-startIndex, symbolTable[i].name, symbolTable[i].entryType, 
           symbolTable[i].dataType, symbolTable[i].scopeLevel, symbolTable[i].formalParameters);
    } 
}


void init_symbolEntry(int i) {
    strcpy(symbolTable[i].name, "NaN");
    strcpy(symbolTable[i].entryType, "NaN");
    strcpy(symbolTable[i].dataType, "NaN");
    symbolTable[i].scopeLevel = -1;
    strcpy(symbolTable[i].formalParameters, "NaN");
    symbolTable[i].isPreDeclared = 0;
}

/*insert*/
void insert_var_declaration(char dataType[VAR_SIZE], char varNames[VAR_SIZE]) {
    char *pch = strtok(varNames, ",");
    char *name;
    char entryType[VAR_SIZE];
    int isPreDeclared = 0;

    if (varNames[0] == '@' && varNames[1] =='@') {//if is function declare
        memmove(varNames, varNames+2, strlen(varNames));//remove "@@" infront funct declare(in [declarator] grammar)
        strcpy(entryType, "function");
        isPreDeclared = 1;
    } else {
        strcpy(entryType, "variable");
    }

    while (pch != NULL) {
        name = pch;
        if (checkRedeclare(entryType, name) == 0) {
            insert_symbol(name, entryType, dataType, currScopeLevel, "", isPreDeclared);
            pch = strtok(NULL, ",");
        }
        else {
            return;
        }
    }
}

void insert_param_declaration(char dataType[VAR_SIZE], char paramName[VAR_SIZE]) {
    insert_symbol(paramName, "parameter", dataType, currScopeLevel+1, "", 0);
}

void insert_funct_declaration(char* dataType, char* nameAndParam) {
    // printf("[   ]%s\n", nameAndParam);
    if (nameAndParam[0] == '@' && nameAndParam[1] =='@') {
        memmove(nameAndParam, nameAndParam+2, strlen(nameAndParam));//remove "@@" infront funct declare(in [declarator] grammar)
    } else {
        yyerror("not function");
        return;
    }

    char *pch = strtok(nameAndParam, "##");
    char *functName = pch;

    pch = strtok(NULL, "##");
    if (pch == NULL) {
        pch = "";
    }

    /*check if is predeclared, if predeclared, then dont insert*/
    for (int i = currIndex ; i >= 0 ; i--) {
        if (symbolTable[i].scopeLevel == currScopeLevel) {
            if (strcmp(symbolTable[i].name, functName) == 0 && symbolTable[i].isPreDeclared == 1 
                && strcmp(symbolTable[i].entryType, "function") == 0) {
                return;
            }
        }
    }

    if (checkRedeclare("function", functName) == 0) {
        insert_symbol(functName, "function", dataType, currScopeLevel, pch, 0);
    }
    else {
        return;
    }
}

void clearSymbolEntries(int headIndex, int tailIndex) {
    for (int i = headIndex ; i <= tailIndex ; ++i) {
        init_symbolEntry(i);
    }
}

/*return 0 if no semantic error; return 1 if detected symantic error*/
int checkRedeclare(char entryType[VAR_SIZE], char name[VAR_SIZE]) {
    char errorMessage[ERROR_MESSAGE_SIZE];
    for (int i = currIndex ; i >= 0 ; i--) {
        if (symbolTable[i].scopeLevel == currScopeLevel) {
            /*Semantic Error: Redeclare*/
            if (strcmp(symbolTable[i].name, name) == 0) {
                    strcpy(errorMessage, "Redeclared ");
                    strcat(errorMessage, entryType);
                    strcat(errorMessage, " ");
                    strcat(errorMessage, name);
                    yyerror(errorMessage);
                return 1;
            }
        }
    }
    return 0;
}

void popErrorBuff() {
    for (int i = 0 ; i <= errorIndex ; ++i) {
        yyerror(errorBuff[i]);
        strcpy(errorBuff[i], "");
    }
    errorIndex = -1;
}

void pushErrorBuff(char errorMessage[ERROR_MESSAGE_SIZE]) {
    errorIndex++;
    strcpy(errorBuff[errorIndex], errorMessage);
}

void create_symbol() {}
void insert_symbol(char name[VAR_SIZE], char entryType[VAR_SIZE], 
                    char dataType[VAR_SIZE], int scopeLevel, char formalParam[VAR_SIZE], int isPreDeclared) {

    
    currIndex++;
    init_symbolEntry(currIndex);

    strcpy(symbolTable[currIndex].name, name);
    strcpy(symbolTable[currIndex].entryType, entryType);
    strcpy(symbolTable[currIndex].dataType, dataType);
    symbolTable[currIndex].scopeLevel = scopeLevel;
    strcpy(symbolTable[currIndex].formalParameters, formalParam);
    symbolTable[currIndex].isPreDeclared = isPreDeclared;


    // printf("[funct insert]current index: %d, %s\n", currIndex, symbolTable[currIndex].name);
    //  printSymbolTable(0);
}

/*return 1 if no semantic error; return 0 if detected symantic error*/
int lookup_symbol(char varName[VAR_SIZE]) {
    char entryType[VAR_SIZE];
    char errorMessage[ERROR_MESSAGE_SIZE];

    if (varName[0] == '@') {
        return 1;
    } else if (varName[0] == '#') {
        strcpy(entryType, "function");
        memmove(varName, varName+1, strlen(varName));
    } else {
        strcpy(entryType, "variable");
    }

    // printf("[lookUp] %s %s\n", entryType, varName);

    int isDeclared = 0;
    int tmpIndex = currIndex;
    for (int i = currIndex ; symbolTable[i].scopeLevel == currScopeLevel ; --i) {
        tmpIndex = i;
        if (strcmp(symbolTable[i].name, varName) == 0) {
                isDeclared = 1;
                break;
        }
    }
    for (int i = tmpIndex ; i >= 0 ; --i) {
        if (symbolTable[i].scopeLevel < currScopeLevel 
            && strcmp(symbolTable[i].name, varName) == 0) {
                isDeclared = 1;
                break;
        }
    }

    if (isDeclared == 0) {
        strcpy(errorMessage, "Undeclared ");
        strcat(errorMessage, entryType);
        strcat(errorMessage, " ");
        strcat(errorMessage, varName);
        pushErrorBuff(errorMessage);
        return 0;
    } else if (isDeclared == 1){
        return 1;
    }
}

void dump_symbol() {
    for (int i = currIndex ; i >= 0 ; --i) {
        // if (currScopeLevel <= 0) {
        //     return;
        // }
        
        //printf("\n### i: %d, currIndex: %d, outerScopeLevel: %d, currScopeLevel: %d", i, currIndex, symbolTable[i].scopeLevel, currScopeLevel);
        if (symbolTable[i].scopeLevel == currScopeLevel - 1) {
            if (i != currIndex) {
                printSymbolTable(i+1);
                clearSymbolEntries(i+1, currIndex);
                currIndex = i;
            }
            return;
        }
        // printSymbolTable(0);
    }
}
