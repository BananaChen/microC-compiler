/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAR_SIZE 100
#define SYMBOL_TABLE_SIZE 200
#define ERROR_MESSAGE_SIZE 200
#define ERROR_BUFF_SIZE 100
#define BUF_SIZE 256

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[BUF_SIZE];  // Get current code line from lex

FILE *file; // To generate .j file for Jasmin

extern void printLine(int isError);
extern int isYYError;
int isSyntaxError = 0;

int currScopeLevel = 0;
int currIndex = -1;

char errorBuff[ERROR_BUFF_SIZE][ERROR_MESSAGE_SIZE];
int errorIndex = -1;

typedef struct {
    // int index;
    char name[VAR_SIZE];
    char entryType[VAR_SIZE];
    char dataType[VAR_SIZE];
    int scopeLevel;
    char formalParameters[VAR_SIZE];
    int isPreDeclared;
    int localIndex;
} SymbolEntry;

SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];

/*Code Genetarion variable*/
char typeBuff[10];
char returnTypeBuff[10];
int currLocalIndex = -1;
int cmp_label_index = -1;
int isGlobalDeclare = 0;


/**/
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


/* code generation functions, just an example! */
void genCode(char* str);
int isStatic(int varIndex);
char* getTypeCode(char* type);
void gencode_store();
int gencode_load(char varName[VAR_SIZE]);
int gencode_loadAndFunctCall(char varName[VAR_SIZE]);

void gencode_print(char *type);

char* gencode_postfixExpr(char varName[VAR_SIZE], char* instruction);
char* gencode_arihmeticExpr(char* leftType, char* rightType, char* instruction);
char* gencode_modExpr(char* leftType, char* rightType);

int getVarIndexOfSymbolTable(char varName[VAR_SIZE]);
char* gencode_asgnExpr_typeCast(char* leftType, char* rightType);
char* gencode_asgnExpr(char* leftVarName[VAR_SIZE], char* leftType, char* rightType, char* instruction);

void gencode_functDeclaration(char* returnType, char* nameAndParam);
char* gencode_invokeFunct(char* functName[VAR_SIZE]);
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
%token RET CONT BREAK
%token COMMENT

/* Token with return, which need to sepcify type */
/*%token <i_val> I_CONST
%token <f_val> F_CONST*/
%token <string> STR_CONST I_CONST F_CONST
%token <string> ID TRUE FALSE

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

%type <string> postfix_expression unary_expression unary_expression_for_assignment 
%type <string> multiplicative_expression additive_expression
%type <string> relational_expression equality_expression 
%type <string> logical_and_expression logical_or_expression conditional_expression assignment_expression
%type <string> initializer

%type <string> assignment_operator
/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : external_declaration { /*printSymbolTable(0);*/  }
    | program external_declaration { /*printSymbolTable(0);*/ }
    |
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : type_specifier declarator {
        gencode_functDeclaration($1, $2);
    } compound_statement { insert_funct_declaration($1, $2); genCode(".end method\n"); } //==================================================
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
    : IF LB expression RB statement {
        cmp_label_index++;
        fprintf(file, "\tgoto EXIT%d\n", cmp_label_index);
        fprintf(file, "LABEL_FALSE_%d\:\n", cmp_label_index);
    } ELSE statement {
        fprintf(file, "EXIT%d\:\n", cmp_label_index);
    }
    | IF LB expression RB statement{
        fprintf(file, "LABEL_FALSE_%d\:\n", cmp_label_index);
    }
    ;

iteration_statement
    : WHILE { 
        cmp_label_index++;
        fprintf(file, "LABEL_WHILE_BEGIN_%d\:\n", cmp_label_index); 
    }
    LB expression RB statement { 
        fprintf(file, "\tgoto LABEL_BEGIN_%d\n", cmp_label_index);
        fprintf(file, "LABEL_FALSE_%d\:\n", cmp_label_index);
        fprintf(file, "\tgoto EXIT%d\n", cmp_label_index);
        fprintf(file, "EXIT%d\:\n", cmp_label_index);

     }
    | FOR LB expression_statement expression_statement RB statement
    | FOR LB expression_statement expression_statement expression RB statement
    | FOR LB declaration expression_statement RB statement
    | FOR LB declaration expression_statement expression RB statement
    ;

jump_statement
    : CONT SEMICOLON
    | BREAK SEMICOLON
    | RET SEMICOLON {
        if(strcmp(returnTypeBuff, "void") == 0){
			genCode("\treturn\n");
		}
		else{
			yyerror("Return type should be void");
		}
    }
    | RET assignment_expression SEMICOLON { gencode_returnWithValue(returnTypeBuff, $2); }
    ;

print_func
    : PRINT LB I_CONST RB SEMICOLON {
        gencode_print("int");
    }
    | PRINT LB F_CONST RB SEMICOLON {
        gencode_print("float");
    }
    | PRINT LB STR_CONST RB SEMICOLON {
        gencode_print("string");
    }
    | PRINT LB ID RB SEMICOLON { 
        int isDeclared = lookup_symbol($3);
        if (isDeclared) { 
            int varIndex = gencode_loadAndFunctCall($3);
            char *type = symbolTable[varIndex].dataType;
            gencode_print(type);
        }
    }
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
    : declarator { 
        if (currScopeLevel != 0) {
            currLocalIndex++;
            if ($1[0] != '@' && $1[0] != '#') {
                if (strcmp(typeBuff, "int") == 0) { fprintf(file, "\tldc 0\n"); } 
                else if (strcmp(typeBuff, "float") == 0) { fprintf(file, "\tldc 0.0\n"); } 
                else if (strcmp(typeBuff, "string") == 0) { fprintf(file, "\tldc \"\"\n"); } 
                else if (strcmp(typeBuff, "bool") == 0) { fprintf(file, "\tldc 0\n"); } 
            }
        }
        $$ = $1;
        if ($1[0] != '@' && $1[0] != '#') {
            gencode_declaration($1, typeBuff, 0);
        }
        
    }
    | declarator ASGN {
        if (currScopeLevel == 0) {
            isGlobalDeclare = 1;
        }
    }
    initializer { 
        if (currScopeLevel != 0) {
            currLocalIndex++;
        }
        $$ = $1; 
        if ($1[0] != '@' && $1[0] != '#') {
            gencode_asgnExpr_typeCast(typeBuff, $4);
            gencode_declaration($1, typeBuff, 1);
            isGlobalDeclare = 0;
        }
    }
    ;

declarator //direct_declarator
    : ID { $$ = $1; }
    | LB declarator RB //for what?
    | declarator LB parameter_list RB { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; strcat(tmp, $1);
                                        /*seperate parameter*/ strcat(tmp, "##"); strcat(tmp, $3);  strcpy($$, tmp); }
    | declarator LB RB { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; strcat(tmp, $1); strcpy($$, tmp);}
    | declarator LB identifier_list RB
    ;

parameter_list // parameter_type_list
    : parameter_declaration { $$ = $1; }
    | parameter_list COMMA parameter_declaration { strcat($1, ", "); $$ = strcat($1, $3); }
    ;

parameter_declaration
    : type_specifier declarator { $$ = $1; currLocalIndex++; insert_param_declaration($1, $2); }
    | type_specifier //for what?
    ;

identifier_list
    : ID
    | identifier_list COMMA ID
    ;

initializer
    : assignment_expression { $$ = $1; }
    ;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression_for_assignment assignment_operator assignment_expression {
        if ($1[0] != '@') {
            int varIndex = getVarIndexOfSymbolTable($1);
            $$ = gencode_asgnExpr($1, symbolTable[varIndex].dataType, $3, $2);

        } else {
            yyerror("Assign to const");
        }
    }
	;

conditional_expression
    : logical_or_expression { $$ = $1; }
    ;

logical_or_expression
    : logical_and_expression { $$ = $1; }
    | logical_or_expression OR logical_and_expression { $$ = "bool"; }
    ;

logical_and_expression
    : equality_expression { $$ = $1; }
    | logical_and_expression AND equality_expression { $$ = "bool"; }
    ;

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression EQ relational_expression { gencode_cmpExpr($1, $3, "EQ"); $$ = "bool"; }
    | equality_expression NE relational_expression { gencode_cmpExpr($1, $3, "NE"); $$ = "bool"; }
    ;

relational_expression
    : additive_expression { $$ = $1; }
    | relational_expression MT additive_expression { gencode_cmpExpr($1, $3, "MT"); $$ = "bool"; }
    | relational_expression LT additive_expression { gencode_cmpExpr($1, $3, "LT"); $$ = "bool"; }
    | relational_expression MTE additive_expression { gencode_cmpExpr($1, $3, "MTE"); $$ = "bool"; }
    | relational_expression LTE additive_expression { gencode_cmpExpr($1, $3, "LTE"); $$ = "bool"; }
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
    | additive_expression ADD multiplicative_expression { $$ = gencode_arihmeticExpr($1, $3, "add"); }
    | additive_expression SUB multiplicative_expression { $$ = gencode_arihmeticExpr($1, $3, "sub"); }
    ;

multiplicative_expression
    : unary_expression { $$ = $1; }
    | multiplicative_expression MUL unary_expression { $$ = gencode_arihmeticExpr($1, $3, "mul"); }
    | multiplicative_expression DIV unary_expression { $$ = gencode_arihmeticExpr($1, $3, "div"); }
    | multiplicative_expression MOD unary_expression { $$ = gencode_modExpr($1, $3); }

/*$$ = return data type of unary_expression*/
unary_expression
    : postfix_expression {
        if ($1[0] == '@') {
            $$ = $1 + 1;
        } else if(strcmp($1, "void") == 0 || strcmp($1, "int") == 0 || strcmp($1, "float") == 0 
            || strcmp($1, "bool") == 0 || strcmp($1, "string") == 0) {
                $$ = $1;
        } else {
            int isDeclared = lookup_symbol($1);
            if (isDeclared) {
                int loadedVarIndex = gencode_loadAndFunctCall($1);
                if (loadedVarIndex != -1) {
                    $$ = symbolTable[loadedVarIndex].dataType;
                }
            }
        }

     }
    | INC unary_expression { $$ = $2; }
    | DEC unary_expression { $$ = $2; }
    ;

/* differecne - to not generate code [load] here */
unary_expression_for_assignment
    : postfix_expression { lookup_symbol($1); $$ = $1; }
    | INC unary_expression { $$ = $2; } //================================================ delete '@' in const
    | DEC unary_expression { $$ = $2; }
    ;


postfix_expression
    : primary_expression { $$ = $1; }
    | postfix_expression LB RB { 
        char tmp[VAR_SIZE] = "#"; 
        $$ =strcat(tmp, $1); 
        if ($1[0] != '@') {
            $$ = gencode_invokeFunct($1); 
        }
    }
    | postfix_expression LB argument_expression_list RB { 
        char tmp[VAR_SIZE] = "#"; 
        $$ = strcat(tmp, $1); 
        if ($1[0] != '@') {
            $$ = gencode_invokeFunct($1); 
        }
    }
    | postfix_expression INC { $$ = gencode_postfixExpr($1, "INC"); }
    | postfix_expression DEC { $$ = gencode_postfixExpr($1, "DEC"); }
    ;

primary_expression
    : ID { $$ = $1; }
    | I_CONST {  
        $$ = "@int"; /*if @, means that it is const*/
        if(isGlobalDeclare == 0) { 
            fprintf(file, "\tldc %d\n", yylval.i_val);
        } 
    }
    | F_CONST { 
        $$ = "@float"; 
        if(isGlobalDeclare == 0) { 
        fprintf(file, "\tldc %f\n", yylval.f_val);
        }
    }
    | STR_CONST { 
        $$ = "@string"; 
        if(isGlobalDeclare == 0) { 
            fprintf(file, "\tldc %s\n", $1); 
        }
    }
    | TRUE { 
        $$ = "@bool"; 
        if(isGlobalDeclare == 0) { 
            fprintf(file, "\tldc 1\n"); 
        }
    }
    | FALSE { $$ = "@bool"; 
        if(isGlobalDeclare == 0) { 
            fprintf(file, "\tldc 1\n"); 
        }
    }
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

assignment_operator
    : ASGN { $$ = "ASGN"; }
    | MULASGN { $$ = "MULASGN"; }
    | DIVASGN { $$ = "DIVASGN"; }
    | MODASGN { $$ = "MODASGN"; }
    | ADDASGN { $$ = "ADDASGN"; }
    | SUBASGN { $$ = "SUBASGN"; }

type_specifier // declaration_specifiers
    : INT { $$ = $1; sprintf(typeBuff, "int"); }
    | FLOAT { $$ = $1; sprintf(typeBuff, "float"); }
    | BOOL { $$ = $1; sprintf(typeBuff, "bool"); }
    | STRING { $$ = $1; sprintf(typeBuff, "string"); }
    | VOID { $$ = $1; sprintf(typeBuff, "void"); }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    file = fopen("compiler_hw3.j","w");

    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");


    yyparse();
    if (isSyntaxError == 0) {
        printFinalSymbolTable(0);
    	printf("\n\nTotal lines: %d \n",yylineno);
    }

    fclose(file);

    return 0;
}

void yyerror(char *s)
{
    if (strcmp(s, "syntax error") == 0) {
        isSyntaxError = 1;
        char tmpBuff[BUF_SIZE];
        strcpy(tmpBuff, buf);
        popErrorBuff();
        isYYError = 1;
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno+1, tmpBuff);
        printf("| %s", s);
        printf("\n|-----------------------------------------------|\n\n");
        memset(tmpBuff, 0, 255);
    } else {
        isYYError = 1;
        printLine(1);
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno+1, buf);
        printf("| %s", s);
        printf("\n|-----------------------------------------------|\n\n");
        memset(buf, 0, 255);
    }
}



void printSymbolTable(int startIndex) {

    printf("\n\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    for (int i = startIndex ; i <= currIndex ; ++i) {
        printf("%-10d%-10s%-12s%-10s%-10d%s\n",
           i-startIndex, symbolTable[i].name, symbolTable[i].entryType, 
           symbolTable[i].dataType, symbolTable[i].scopeLevel, symbolTable[i].formalParameters);
    }
}

/*Difference: \n */
void printFinalSymbolTable(int startIndex) {

    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    for (int i = startIndex ; i <= currIndex ; ++i) {
        printf("%-10d%-10s%-12s%-10s%-10d%s\n",
           i-startIndex, symbolTable[i].name, symbolTable[i].entryType, 
           symbolTable[i].dataType, symbolTable[i].scopeLevel, symbolTable[i].formalParameters);
    }
}

void init_symbolEntry(int i) {
    // symbolTable[i].index = 0;
    strcpy(symbolTable[i].name, "NaN");
    strcpy(symbolTable[i].entryType, "NaN");
    strcpy(symbolTable[i].dataType, "NaN");
    symbolTable[i].scopeLevel = -1;
    strcpy(symbolTable[i].formalParameters, "NaN");
    symbolTable[i].isPreDeclared = 0;
    symbolTable[i].localIndex = 0;
}

/*insert*/
void insert_var_declaration(char dataType[VAR_SIZE], char varNames[VAR_SIZE]) {
    char *pch = strtok(varNames, ",");
    char* name;
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
                    symbolTable[i].isPreDeclared = 0;
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

int getCurrLevelIndex() {
    int currLevelIndex = -1;
    for (int i = currIndex ; i >= 0 ; --i) {
        if (symbolTable[i].scopeLevel == currScopeLevel) {
            currLevelIndex++;
        } else {
            break;
        }
    }
    return currLevelIndex;
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
    symbolTable[currIndex].localIndex = currLocalIndex;

    // symbolTable[currIndex].index = getCurrLevelIndex();
}

/*return 1 if no semantic error; return 0 if detected symantic error*/
int lookup_symbol(char varName[VAR_SIZE]) {
    char entryType[VAR_SIZE];
    char errorMessage[ERROR_MESSAGE_SIZE];

    if (varName[0] == '@') { // if it is constant
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
        if (symbolTable[i].scopeLevel == currScopeLevel - 1) {
            if (i != currIndex) {
                printSymbolTable(i+1);
                clearSymbolEntries(i+1, currIndex);
                currIndex = i;
            }
            return;
        } else if (i == 0) {
            printSymbolTable(0);
            clearSymbolEntries(0, currIndex);
            currIndex = -1;
        }
    }
}

/* 
 * =======================================================================================
 * |                                 Code Generate Section                               |
 * =======================================================================================
 */
void genCode(char* str) {
    fprintf(file, str);
}

int isStatic(int varIndex) {
    
    if (symbolTable[varIndex].scopeLevel == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* Translate type to Jasmin representation code*/
char* getTypeCode(char type[10]) {

    if (strcmp(type, "int") == 0) { return "I"; } 
    else if (strcmp(type, "float") == 0) { return "F"; } 
    else if (strcmp(type, "string") == 0) { return "Ljava/lang/String;"; } 
    else if (strcmp(type, "bool") == 0) { return "Z"; } 
    else if (strcmp(type, "void") == 0) { return "V"; }
    else { yyerror("Unsupported type to get type code"); }
}

void gencode_declaration(char* varName, char* type, int isInit) {
    if (currScopeLevel == 0) {
        if (isInit == 1) {
            if (strcmp(type, "int") == 0) {
                fprintf(file, ".field public static %s %s = %d\n", varName, getTypeCode(type), yylval.i_val);
            } else if (strcmp(type, "float") == 0) {
                fprintf(file, ".field public static %s %s = %d\n", varName, getTypeCode(type), yylval.f_val);
            } else if (strcmp(type, "string") == 0) {
                fprintf(file, ".field public static %s %s = %d\n", varName, getTypeCode(type), yylval.string);
            } else if (strcmp(type, "bool") == 0) {
                fprintf(file, ".field public static %s %s = %d\n", varName, getTypeCode(type), yylval.i_val);
            } else {
                yyerror("Invalid type for global declaration");
            }

        } else if (isInit == 0) {
            fprintf(file, ".field public static %s %s\n", varName, getTypeCode(type));
        }
    } else {
        gencode_store(varName, type);
    }
}

void gencode_store(char* varName, char* type) {

    if (currScopeLevel == 0) {
        fprintf(file, "\tputstatic compiler_hw3/%s %s\n", varName, type);
    } else {
        if (strcmp(type, "int") == 0) {
            fprintf(file, "\tistore %d\n", currLocalIndex);
        } else if (strcmp(type, "float") == 0) {
            fprintf(file, "\tfstore %d\n", currLocalIndex);
        } else if (strcmp(type, "string") == 0) {
            fprintf(file, "\tastore %d\n", currLocalIndex);
        } else if (strcmp(type, "bool") == 0) {
            fprintf(file, "\tistore %d\n", currLocalIndex);
        } else {
            yyerror("Invalid type for storage");
        }
    }
}


/* Return index of loaded variable*/
int gencode_load(char varName[VAR_SIZE]) {
    int loadedVarIndex = -1;
    int tmpIndex = currIndex;
    for (int i = currIndex ; symbolTable[i].scopeLevel == currScopeLevel ; --i) {
        tmpIndex = i;
        if (strcmp(symbolTable[i].name, varName) == 0) {
                loadedVarIndex = i;
                break;
        }
    }
    for (int i = tmpIndex ; i >= 0 ; --i) {
        if (symbolTable[i].scopeLevel < currScopeLevel 
            && strcmp(symbolTable[i].name, varName) == 0) {
                loadedVarIndex = i;
                break;
        }
    }

    if (loadedVarIndex == -1) {
        yyerror("ERROR: var not defined");
        return;
    }

    if (isStatic(loadedVarIndex)) {
        if (strcmp(symbolTable[loadedVarIndex].dataType, "int") == 0) {
            fprintf(file, "\tgetstatic compiler_hw3/%s I\n", symbolTable[loadedVarIndex].name);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "float") == 0) {
            fprintf(file, "\tgetstatic compiler_hw3/%s F\n", symbolTable[loadedVarIndex].name);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "string") == 0) {
            fprintf(file, "\tgetstatic compiler_hw3/%s Ljava/lang/String;\n", symbolTable[loadedVarIndex].name);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "bool") == 0) {
            fprintf(file, "\tgetstatic compiler_hw3/%s Z\n", symbolTable[loadedVarIndex].name);
        } else {
            yyerror("Generate Code Load Failed, unsupported type");
        }
    } else {
        if (strcmp(symbolTable[loadedVarIndex].dataType, "int") == 0) {
            fprintf(file, "\tiload %d\n", symbolTable[loadedVarIndex].localIndex);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "float") == 0) {
            fprintf(file, "\tfload %d\n", symbolTable[loadedVarIndex].localIndex);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "string") == 0) {
            fprintf(file, "\taload %d\n", symbolTable[loadedVarIndex].localIndex);
        } else if (strcmp(symbolTable[loadedVarIndex].dataType, "bool") == 0) {
            fprintf(file, "\tiload %d\n", symbolTable[loadedVarIndex].localIndex);
        } else {
            yyerror("Generate Code Load Failed, unsupported type");
        }
    }
    return loadedVarIndex;
}

/* Return index of loaded variable*/
int gencode_loadAndFunctCall(char varName[VAR_SIZE]) {

    if (varName[0] == '@') { // if it is const
        return -1;
    } else if (varName[0] == '#') { // if it is function
        memmove(varName, varName+1, strlen(varName));
        return -1;

    } else { // if it is variable
        int loadedVarIndex = gencode_load(varName);
        return loadedVarIndex;
    }
}

void gencode_print(char *type) {
    fprintf(file, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
    fprintf(file, "\tswap\n");

    if (strcmp(type, "int") == 0) {
        fprintf(file, "\tinvokevirtual java/io/PrintStream/println(I)V\n");
    } else if (strcmp(type, "float") == 0) {
        fprintf(file, "\tinvokevirtual java/io/PrintStream/println(F)V\n");
    } else if (strcmp(type, "string") == 0) {
        fprintf(file, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    } else if (strcmp(type, "bool") == 0) {
        fprintf(file, "\tinvokevirtual java/io/PrintStream/println(I)V\n");
    } else {
        yyerror("Unsupported type to print");
    }
}

char* gencode_postfixExpr(char varName[VAR_SIZE], char* instruction) {
    int varIndex = getVarIndexOfSymbolTable(varName);
    char *varType = symbolTable[varIndex].dataType;

    gencode_load(varName);
    if (strcmp(instruction, "INC") == 0) {
        if (strcmp(varType, "int") == 0) {
            genCode("\tldc 1\n");
			genCode("\tiadd\n");
			gencode_store(varName, varType);
        } else if (strcmp(varType, "float") == 0) {
            genCode("\tldc 1.0\n");
			genCode("\tfadd\n");
			gencode_store(varName, varType);
        } else {
            yyerror("Unsupported type for postfix expr");
        }
    } else if (strcmp(instruction, "DEC") == 0) {
        if (strcmp(varType, "int") == 0) {
            genCode("\tldc 1\n");
			genCode("\tisub\n");
			gencode_store(varName, varType);
        } else if (strcmp(varType, "float") == 0) {
            genCode("\tldc 1.0\n");
			genCode("\tfsub\n");
			gencode_store(varName, varType);
        } else {
            yyerror("Unsupported type for postfix expr");
        }
    }
    return varType;
}

/*for expression*/
char* gencode_arihmeticExpr(char* leftType, char* rightType, char* instruction) {
    if(strcmp(leftType, "int") == 0 && strcmp(rightType, "int") == 0){
        fprintf(file, "\ti%s\n", instruction);
        return "int";
	}
	else if(strcmp(leftType, "int") == 0 && strcmp(rightType, "float") == 0){
        fprintf(file, "\tswap\n");
        fprintf(file, "\ti2f\n");
        fprintf(file, "\tswap\n");
        fprintf(file, "\tf%s\n", instruction);
        return "float";
	}
	else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "int") == 0){
		fprintf(file, "\ti2f\n");
		fprintf(file, "\tf%s\n", instruction);
        return "float";
	}
	else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "float") == 0){
		fprintf(file, "\tf%s\n", instruction);
        return "float";
	}
	else{
		yyerror("Unsupported type for doing instruction in gencode_arihmeticExpr()");
	}
}

char* gencode_modExpr(char* leftType, char* rightType) {
    if(strcmp(leftType, "int") == 0 && strcmp(rightType, "int") == 0){
        fprintf(file, "\tirem\n");
        return "int";
	} else {
        yyerror("Unsupported type for MOD");
    }
}

void gencode_cmpExpr(char* leftType, char* rightType, char* instruction){

    // if(strcmp(leftType, "int") == 0 && strcmp(rightType, "int") == 0){
    //     fprintf(file, "\ti2f\n");
    //     fprintf(file, "\tswap\n");
    //     fprintf(file, "\ti2f\n");
    //     fprintf(file, "\tswap\n");
	// }
	// else if(strcmp(leftType, "int") == 0 && strcmp(rightType, "float") == 0){
    //     fprintf(file, "\tswap\n");
    //     fprintf(file, "\ti2f\n");
    //     fprintf(file, "\tswap\n");
	// }
	// else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "int") == 0){
	// 	fprintf(file, "\ti2f\n");
	// }
	// else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "float") == 0){

	// }
	// else{
	// 	yyerror("Unsupported type for doing instruction in gencode_cmpExpr()");
	// }


	// fprintf(file, "\tfcmpl\n");
    gencode_arihmeticExpr(leftType, rightType, "sub");

	char* jasmin_instruction;

    if (strcmp(instruction, "LT") == 0) {
        jasmin_instruction = "ifge";
    } else if (strcmp(instruction, "MT") == 0) {
        jasmin_instruction = "ifle";
    } else if (strcmp(instruction, "LTE") == 0) {
        jasmin_instruction = "ifgt";
    } else if (strcmp(instruction, "MTE") == 0) {
        jasmin_instruction = "iflt";
    } else if (strcmp(instruction, "EQ") == 0) {
        jasmin_instruction = "ifne";
    } else if (strcmp(instruction, "NE") == 0) {
        jasmin_instruction = "ifeq";
    }
    // cmp_label_index++;

    fprintf(file, "\t%s LABEL_FALSE_%d\n", jasmin_instruction, cmp_label_index);
    // fprintf(file, "\tgoto LABEL_%s_FALSE_%d\n", instruction, cmp_label_index);
    // fprintf(file, "LABEL_%s_FALSE_%d:\n", instruction, cmp_label_index);


    // if (strcmp(instruction, "LT") == 0) {
    //     jasmin_instruction = "iflt";
    // } else if (strcmp(instruction, "MT") == 0) {
    //     jasmin_instruction = "ifgt";
    // } else if (strcmp(instruction, "LTE") == 0) {
    //     jasmin_instruction = "ifle";
    // } else if (strcmp(instruction, "MTE") == 0) {
    //     jasmin_instruction = "ifge";
    // } else if (strcmp(instruction, "EQ") == 0) {
    //     jasmin_instruction = "ifeq";
    // } else if (strcmp(instruction, "NE") == 0) {
    //     jasmin_instruction = "ifne";
    // }

    // fprintf(file, "\t%s LABEL_%s_TRUE_%d\n", jasmin_instruction, instruction, cmp_label_index);
    // fprintf(file, "\tgoto LABEL_%s_FALSE_%d\n", instruction, cmp_label_index);
    // fprintf(file, "LABEL_%s_TRUE_%d:\n", instruction, cmp_label_index);

    // fprintf(file, "LABEL_%s_FALSE_%d:\n", instruction, cmp_label_index);
}

int getVarIndexOfSymbolTable(char varName[VAR_SIZE]) {
    int tmpIndex = currIndex;
    if (lookup_symbol(varName) == 1) {
        for (int i = currIndex ; symbolTable[i].scopeLevel == currScopeLevel ; --i) {
            tmpIndex = i;
            if (strcmp(symbolTable[i].name, varName) == 0) {
                    return i;
            }
        }
        for (int i = tmpIndex ; i >= 0 ; --i) {
            if (symbolTable[i].scopeLevel < currScopeLevel 
                && strcmp(symbolTable[i].name, varName) == 0) {
                    return i;
            }
        }
        yyerror("Var not found in getVarIndexOfSymbolTable)");
    }
}

char* gencode_asgnExpr_typeCast(char* leftType, char* rightType) {
    if(strcmp(leftType, "int") == 0 && strcmp(rightType, "int") == 0){              // int = int
        return "int";
	} else if(strcmp(leftType, "int") == 0 && strcmp(rightType, "float") == 0){     // int = float
        fprintf(file, "\tf2i\n");
        return "int";
	} else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "int") == 0){     // float = int
		fprintf(file, "\ti2f\n");
        return "float";
	} else if(strcmp(leftType, "float") == 0 && strcmp(rightType, "float") == 0){   // float = float
        return "float";
	} else if(strcmp(leftType, "string") == 0 && strcmp(rightType, "string") == 0){ // string = string
        return "string";
	} else if(strcmp(leftType, "bool") == 0 && strcmp(rightType, "bool") == 0){     // bool = bool
        return "bool";
	} else{
		yyerror("Unsupported type assignment");
	}
}

char* gencode_asgnExpr(char* leftVarName[VAR_SIZE], char* leftType, char* rightType, char* instruction) {
    
    if (strcmp(instruction, "ASGN") == 0) {
        gencode_asgnExpr_typeCast(leftType, rightType);
        gencode_store(leftVarName, leftType);

    } else if (strcmp(instruction, "MULASGN") == 0) {
        gencode_load(leftVarName);
        fprintf(file, "\tswap\n");
        gencode_arihmeticExpr(leftType, rightType, "mul");
        gencode_store(leftVarName, leftType);
    } else if (strcmp(instruction, "DIVASGN") == 0) {
        gencode_load(leftVarName);
        fprintf(file, "\tswap\n");
        gencode_arihmeticExpr(leftType, rightType, "div");
        gencode_store(leftVarName, leftType);
    } else if (strcmp(instruction, "MODASMODASGN") == 0) {
        gencode_load(leftVarName);
        fprintf(file, "\tswap\n");
        gencode_modExpr(leftType, rightType);
        gencode_store(leftVarName, leftType);
    } else if (strcmp(instruction, "ADDASGN") == 0) {
        gencode_load(leftVarName);
        fprintf(file, "\tswap\n");
        gencode_arihmeticExpr(leftType, rightType, "add");
        gencode_store(leftVarName, leftType);
    } else if (strcmp(instruction, "SUBASGN") == 0) {
        gencode_load(leftVarName);
        fprintf(file, "\tswap\n");
        gencode_arihmeticExpr(leftType, rightType, "sub");
        gencode_store(leftVarName, leftType);
    }

    return leftType;
}

void gencode_functDeclaration(char* returnType, char* inputNameAndParam) {
    char nameAndParam[VAR_SIZE];
    sprintf(nameAndParam, inputNameAndParam);
    if (nameAndParam[0] == '@' && nameAndParam[1] =='@') {
        memmove(nameAndParam, nameAndParam+2, strlen(nameAndParam));//remove "@@" infront funct declare(in [declarator] grammar)
    } else {
        yyerror("not function when gen code");
        return;
    }

    sprintf(returnTypeBuff, returnType);

    char *pch = strtok(nameAndParam, "##");
    char *params = strtok(NULL, "##");
    char *functName = pch;

    // gen function name code
    genCode(".method public static ");
    genCode(functName);
    genCode("(");

    if (strcmp(functName, "main") == 0) {
        genCode("[Ljava/lang/String;");
    } else {
        // if there is paramater, then cut param
        if (params != NULL) {
            pch = strtok(params, ", ");
            while (pch != NULL) {
                genCode(getTypeCode(pch));
                pch = strtok(NULL, ", ");
            }
        }
    }

    genCode(")");
    genCode(getTypeCode(returnType));
    genCode("\n");
    genCode(".limit stack 50\n");
    genCode(".limit locals 50\n");
    /*check if is predeclared, if predeclared, then dont insert*/
    // for (int i = currIndex ; i >= 0 ; i--) {
    //     if (symbolTable[i].scopeLevel == currScopeLevel) {
    //         if (strcmp(symbolTable[i].name, functName) == 0 && symbolTable[i].isPreDeclared == 1 
    //             && strcmp(symbolTable[i].entryType, "function") == 0) {
    //                 symbolTable[i].isPreDeclared = 0;
    //             return;
    //         }
    //     }
    // }
}

void gencode_returnWithValue(char* returnType, char* rightType) {
    if (strcmp(returnType, "int") == 0 && strcmp(rightType, "int") == 0){              // int = int
        genCode("\tireturn\n");

	} else if (strcmp(returnType, "int") == 0 && strcmp(rightType, "float") == 0){     // int = float
        fprintf(file, "\tf2i\n");
        genCode("\tireturn\n");

	} else if (strcmp(returnType, "float") == 0 && strcmp(rightType, "int") == 0){     // float = int
		fprintf(file, "\ti2f\n");
        genCode("\tfreturn\n");

	} else if (strcmp(returnType, "float") == 0 && strcmp(rightType, "float") == 0){   // float = float
        genCode("\tfreturn\n");

	} else if (strcmp(returnType, "bool") == 0 && strcmp(rightType, "bool") == 0){     // bool = bool
        genCode("\tireturn\n");

	} else {
		yyerror("Return type error");
	}
}

char* gencode_invokeFunct(char* functName[VAR_SIZE]) {
    char tmp[VAR_SIZE] = "#";
    sprintf(tmp, functName);
    // if (lookup_symbol(tmp) == 1) {
        
        int functIndex = getVarIndexOfSymbolTable(functName);

        genCode("\tinvokestatic compiler_hw3/");
        genCode(functName);
        genCode("(");

        char* params = symbolTable[functIndex].formalParameters;
        if (params != NULL) {
            char* pch = strtok(params, ", ");
            while (pch != NULL) {
                if (strcmp(pch, "void") != 0) {
                    genCode(getTypeCode(pch));
                    pch = strtok(NULL, ", ");
                }
            }
        }
        genCode(")");
        genCode(getTypeCode(symbolTable[functIndex].dataType));
        genCode("\n");
        return symbolTable[functIndex].dataType;
    // }
}