/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "compiler_hw2.y" /* yacc.c:339  */

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


#line 122 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    INC = 263,
    DEC = 264,
    MT = 265,
    LT = 266,
    MTE = 267,
    LTE = 268,
    EQ = 269,
    NE = 270,
    ASGN = 271,
    ADDASGN = 272,
    SUBASGN = 273,
    MULASGN = 274,
    DIVASGN = 275,
    MODASGN = 276,
    AND = 277,
    OR = 278,
    NOT = 279,
    LB = 280,
    RB = 281,
    LCB = 282,
    RCB = 283,
    LSB = 284,
    RSB = 285,
    COMMA = 286,
    SEMICOLON = 287,
    QUOTA = 288,
    PRINT = 289,
    IF = 290,
    ELSE = 291,
    FOR = 292,
    WHILE = 293,
    RET = 294,
    CONT = 295,
    BREAK = 296,
    COMMENT = 297,
    STR_CONST = 298,
    I_CONST = 299,
    F_CONST = 300,
    ID = 301,
    TRUE = 302,
    FALSE = 303,
    STRING = 304,
    INT = 305,
    FLOAT = 306,
    VOID = 307,
    BOOL = 308
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define INC 263
#define DEC 264
#define MT 265
#define LT 266
#define MTE 267
#define LTE 268
#define EQ 269
#define NE 270
#define ASGN 271
#define ADDASGN 272
#define SUBASGN 273
#define MULASGN 274
#define DIVASGN 275
#define MODASGN 276
#define AND 277
#define OR 278
#define NOT 279
#define LB 280
#define RB 281
#define LCB 282
#define RCB 283
#define LSB 284
#define RSB 285
#define COMMA 286
#define SEMICOLON 287
#define QUOTA 288
#define PRINT 289
#define IF 290
#define ELSE 291
#define FOR 292
#define WHILE 293
#define RET 294
#define CONT 295
#define BREAK 296
#define COMMENT 297
#define STR_CONST 298
#define I_CONST 299
#define F_CONST 300
#define ID 301
#define TRUE 302
#define FALSE 303
#define STRING 304
#define INT 305
#define FLOAT 306
#define VOID 307
#define BOOL 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 61 "compiler_hw2.y" /* yacc.c:355  */

    int i_val;
    double f_val;
    char* string;

#line 274 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 291 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   112,   113,   117,   118,   122,   123,   127,
     128,   132,   133,   137,   138,   142,   143,   147,   148,   149,
     150,   151,   152,   156,   157,   161,   162,   166,   167,   171,
     172,   173,   174,   175,   179,   180,   181,   182,   186,   187,
     192,   196,   197,   201,   202,   206,   207,   208,   210,   211,
     215,   216,   220,   221,   225,   226,   230,   234,   235,   239,
     243,   244,   248,   249,   253,   254,   255,   259,   260,   261,
     262,   263,   267,   268,   269,   273,   274,   275,   276,   279,
     280,   281,   285,   286,   287,   288,   289,   293,   294,   295,
     296,   297,   298,   302,   303,   307,   308,   309,   310,   311,
     312,   315,   316,   317,   318,   319
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "MOD", "INC",
  "DEC", "MT", "LT", "MTE", "LTE", "EQ", "NE", "ASGN", "ADDASGN",
  "SUBASGN", "MULASGN", "DIVASGN", "MODASGN", "AND", "OR", "NOT", "LB",
  "RB", "LCB", "RCB", "LSB", "RSB", "COMMA", "SEMICOLON", "QUOTA", "PRINT",
  "IF", "ELSE", "FOR", "WHILE", "RET", "CONT", "BREAK", "COMMENT",
  "STR_CONST", "I_CONST", "F_CONST", "ID", "TRUE", "FALSE", "STRING",
  "INT", "FLOAT", "VOID", "BOOL", "$accept", "program",
  "external_declaration", "function_definition", "declaration_list",
  "compound_statement", "block_item_list", "block_item", "statement",
  "expression_statement", "expression", "selection_statement",
  "iteration_statement", "jump_statement", "print_func", "declaration",
  "init_declarator_list", "init_declarator", "declarator",
  "parameter_list", "parameter_declaration", "identifier_list",
  "initializer", "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "argument_expression_list", "assignment_operator",
  "type_specifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     218,   -69,   -69,   -69,   -69,   -69,    19,   -69,   -69,   -69,
     -13,   -69,   -69,   -13,   -69,    74,   -69,   225,   108,   -13,
     -69,   191,   205,    76,   154,   -69,   -69,   -13,   -69,   -69,
      -3,   191,   191,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -17,    -4,   134,   273,   179,   138,    70,     6,
     -69,   -69,   -69,   -10,   -69,    -6,   -13,   -69,   -69,     3,
      13,    29,    57,   170,    43,    60,   -69,   123,   -69,   -69,
     -69,   155,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   -69,   -69,   -69,   -69,   -69,
     -69,   191,   -69,   -69,    92,   -69,   218,   -69,   -20,    69,
     -11,   191,   145,   191,   -69,   180,   -69,   -69,   -69,   -69,
     191,   -69,    -4,   -69,   134,   273,   273,   179,   179,   179,
     179,   138,   138,   -69,   -69,   -69,   -69,   -69,   -69,    48,
     -69,   -69,    83,    86,    50,   176,   176,    67,   -69,   -69,
     -69,   191,   120,   124,     2,   201,   217,     2,   -69,   -69,
     -69,    66,     2,   115,     2,   116,   -69,     2,   -69,     2,
     -69,     2,   -69,   -69,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,   104,   101,   102,   105,   103,     0,     2,     5,     6,
       0,     1,     3,     0,    45,     0,    41,    43,     0,     0,
      40,     0,     0,     0,     0,     7,     9,     0,    46,    42,
      43,     0,     0,    90,    88,    89,    87,    91,    92,    44,
      56,    57,    59,    60,    62,    64,    67,    72,    75,    79,
      82,    48,    54,     0,    50,     0,    53,    11,    23,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    13,    16,
      18,     0,    19,    20,    21,    22,    15,    25,     8,    10,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    99,   100,    96,    97,
      98,     0,    85,    86,     0,    47,     0,    49,     0,    52,
       0,     0,     0,     0,    36,     0,    34,    35,    12,    14,
       0,    24,    61,    75,    63,    65,    66,    68,    69,    70,
      71,    73,    74,    76,    77,    78,    58,    83,    93,     0,
      51,    55,     0,     0,     0,     0,     0,     0,    37,    26,
      84,     0,     0,     0,     0,     0,     0,     0,    94,    38,
      39,    28,     0,     0,     0,     0,    29,     0,    30,     0,
      32,     0,    27,    31,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   153,   -69,   -69,     0,   -69,    98,   125,   -68,
     -60,   -69,   -69,   -69,   -69,   -15,   -69,   161,    17,   -69,
      95,   -69,   -69,   -21,   -69,   -69,   148,   157,   144,   211,
     142,   -27,   -69,   -69,   -69,   -69,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,    24,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     9,    15,    16,    30,    53,
      54,    55,    39,    77,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,   139,   101,    27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    10,    26,   115,    80,    81,    82,    10,    76,    79,
      31,    32,    13,    21,   102,   103,   105,    25,    83,    11,
     107,   106,    22,    56,    78,   108,   141,    17,   110,    23,
      18,   104,   142,    14,    58,   143,    59,    60,   111,    61,
      62,    63,    64,    65,   145,    33,    34,    35,    36,    37,
      38,   144,    76,   147,   112,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   133,   134,   135,     1,     2,
       3,     4,     5,   109,   150,   116,   154,   155,   156,   151,
     136,   120,   113,   138,    31,    32,    95,    96,    97,    98,
      99,   100,   117,   157,    22,   163,   165,   146,   120,   149,
      31,    32,   167,    23,    57,    19,    20,    56,    58,   152,
      59,    60,   153,    61,    62,    63,    64,    65,   137,    33,
      34,    35,    36,    37,    38,     1,     2,     3,     4,     5,
     158,    31,    32,    22,    28,    33,    34,    35,    36,    37,
      38,   169,   171,    92,    93,    94,   120,   120,    84,    85,
      23,   118,   159,    31,    32,    58,   160,    59,    60,    12,
      61,    62,    63,    64,    65,   119,    33,    34,    35,    36,
      37,    38,     1,     2,     3,     4,     5,    58,    31,    32,
      29,    23,    90,    91,    31,    32,   120,   121,    33,    34,
      35,    36,    37,    38,     1,     2,     3,     4,     5,    31,
      32,   140,   114,     1,     2,     3,     4,     5,    58,    31,
      32,   120,   148,    33,    34,    35,    36,    37,    38,    33,
      34,    35,    36,    37,    38,    31,    32,   162,   125,   126,
     122,    51,   131,   132,    33,    34,    35,    36,    37,    38,
     124,    21,     0,   164,    33,    34,    35,    36,    37,    38,
      22,    52,    23,     0,     1,     2,     3,     4,     5,     0,
      33,    34,    35,    36,    37,    38,     0,     1,     2,     3,
       4,     5,     0,     0,     1,     2,     3,     4,     5,   161,
       0,     0,   166,    86,    87,    88,    89,   168,     0,   170,
       0,     0,   172,     0,   173,     0,   174,   127,   128,   129,
     130
};

static const yytype_int16 yycheck[] =
{
      21,     0,    17,    63,    31,    32,    23,     6,    23,    24,
       8,     9,    25,    16,     8,     9,    26,    17,    22,     0,
      26,    31,    25,    22,    24,    31,    46,    10,    25,    27,
      13,    25,    43,    46,    32,    46,    34,    35,    25,    37,
      38,    39,    40,    41,   112,    43,    44,    45,    46,    47,
      48,   111,    67,   113,    25,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    49,    50,
      51,    52,    53,    56,    26,    32,    26,   145,   146,    31,
     101,    31,    25,   104,     8,     9,    16,    17,    18,    19,
      20,    21,    32,    26,    25,   155,   156,   112,    31,   120,
       8,     9,    36,    27,    28,    31,    32,   106,    32,    26,
      34,    35,    26,    37,    38,    39,    40,    41,    26,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
     151,     8,     9,    25,    26,    43,    44,    45,    46,    47,
      48,    26,    26,     5,     6,     7,    31,    31,    14,    15,
      27,    28,    32,     8,     9,    32,    32,    34,    35,     6,
      37,    38,    39,    40,    41,    67,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    32,     8,     9,
      19,    27,     3,     4,     8,     9,    31,    32,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,     8,
       9,   106,    32,    49,    50,    51,    52,    53,    32,     8,
       9,    31,    32,    43,    44,    45,    46,    47,    48,    43,
      44,    45,    46,    47,    48,     8,     9,    26,    84,    85,
      82,    26,    90,    91,    43,    44,    45,    46,    47,    48,
      83,    16,    -1,    26,    43,    44,    45,    46,    47,    48,
      25,    46,    27,    -1,    49,    50,    51,    52,    53,    -1,
      43,    44,    45,    46,    47,    48,    -1,    49,    50,    51,
      52,    53,    -1,    -1,    49,    50,    51,    52,    53,   154,
      -1,    -1,   157,    10,    11,    12,    13,   162,    -1,   164,
      -1,    -1,   167,    -1,   169,    -1,   171,    86,    87,    88,
      89
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    50,    51,    52,    53,    55,    56,    57,    69,
      90,     0,    56,    25,    46,    70,    71,    72,    72,    31,
      32,    16,    25,    27,    58,    59,    69,    90,    26,    71,
      72,     8,     9,    43,    44,    45,    46,    47,    48,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    26,    46,    73,    74,    75,    90,    28,    32,    34,
      35,    37,    38,    39,    40,    41,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    77,    59,    69,
      85,    85,    23,    22,    14,    15,    10,    11,    12,    13,
       3,     4,     5,     6,     7,    16,    17,    18,    19,    20,
      21,    89,     8,     9,    25,    26,    31,    26,    31,    72,
      25,    25,    25,    25,    32,    64,    32,    32,    28,    61,
      31,    32,    80,    85,    81,    82,    82,    83,    83,    83,
      83,    84,    84,    85,    85,    85,    77,    26,    77,    88,
      74,    46,    43,    46,    64,    63,    69,    64,    32,    77,
      26,    31,    26,    26,    26,    63,    63,    26,    77,    32,
      32,    62,    26,    64,    26,    64,    62,    36,    62,    26,
      62,    26,    62,    62,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      66,    66,    66,    66,    67,    67,    67,    67,    68,    68,
      69,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    80,    81,    81,    81,    82,    82,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    85,
      85,    85,    86,    86,    86,    86,    86,    87,    87,    87,
      87,    87,    87,    88,    88,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     3,     4,     1,
       2,     2,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     7,     5,     5,
       6,     7,     6,     7,     2,     2,     2,     3,     5,     5,
       3,     1,     3,     1,     3,     1,     3,     4,     3,     4,
       1,     3,     2,     1,     1,     3,     1,     1,     3,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     3,     4,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 111 "compiler_hw2.y" /* yacc.c:1646  */
    { /*printSymbolTable(0);*/  }
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 112 "compiler_hw2.y" /* yacc.c:1646  */
    { printSymbolTable(0); }
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "compiler_hw2.y" /* yacc.c:1646  */
    { insert_funct_declaration((yyvsp[-2].string), (yyvsp[-1].string)); }
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 157 "compiler_hw2.y" /* yacc.c:1646  */
    { popErrorBuff(); }
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 187 "compiler_hw2.y" /* yacc.c:1646  */
    { lookup_symbol((yyvsp[-2].string)); popErrorBuff(); }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 192 "compiler_hw2.y" /* yacc.c:1646  */
    { insert_var_declaration((yyvsp[-2].string), (yyvsp[-1].string)); }
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 196 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 197 "compiler_hw2.y" /* yacc.c:1646  */
    { strcat((yyvsp[-2].string), ", "); (yyval.string) = strcat((yyvsp[-2].string), (yyvsp[0].string)); }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 201 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 202 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-2].string); }
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 208 "compiler_hw2.y" /* yacc.c:1646  */
    { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; strcat(tmp, (yyvsp[-3].string));
                                        /*seperate parameter*/ strcat(tmp, "##"); (yyval.string) = strcat(tmp, (yyvsp[-1].string)); }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 210 "compiler_hw2.y" /* yacc.c:1646  */
    { /*differ funct declare from var declare*/ char tmp[VAR_SIZE] = "@@"; (yyval.string) = strcat(tmp, (yyvsp[-2].string)); }
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 215 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 216 "compiler_hw2.y" /* yacc.c:1646  */
    { strcat((yyvsp[-2].string), ", "); (yyval.string) = strcat((yyvsp[-2].string), (yyvsp[0].string)); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 220 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); insert_param_declaration((yyvsp[-1].string), (yyvsp[0].string)); }
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 279 "compiler_hw2.y" /* yacc.c:1646  */
    { lookup_symbol((yyvsp[0].string)); }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 285 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 286 "compiler_hw2.y" /* yacc.c:1646  */
    { char tmp[VAR_SIZE] = "#"; (yyval.string) =strcat(tmp, (yyvsp[-2].string)); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 287 "compiler_hw2.y" /* yacc.c:1646  */
    { char tmp[VAR_SIZE] = "#"; (yyval.string) =strcat(tmp, (yyvsp[-3].string)); }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 288 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 289 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 293 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 294 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = "@"; }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 295 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = "@"; }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 296 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = "@"; }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 297 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = "@"; }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 298 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = "@"; }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1697 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 322 "compiler_hw2.y" /* yacc.c:1906  */


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
