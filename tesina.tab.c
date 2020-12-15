/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "tesina.y"

#include <stdio.h>
#include <stdlib.h>
#include "headers/tesina.h"
#define YYERROR_VERBOSE 1
  //per eliminare i warning
    int yylex(void);

#line 80 "tesina.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tesina.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_DATE = 5,                       /* DATE  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_THEN = 7,                       /* THEN  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_PAZIENTE = 10,                  /* PAZIENTE  */
  YYSYMBOL_CF = 11,                        /* CF  */
  YYSYMBOL_ESITOTAMP = 12,                 /* ESITOTAMP  */
  YYSYMBOL_DATATAMP = 13,                  /* DATATAMP  */
  YYSYMBOL_REGIONE = 14,                   /* REGIONE  */
  YYSYMBOL_ISRIC = 15,                     /* ISRIC  */
  YYSYMBOL_REGISTRO = 16,                  /* REGISTRO  */
  YYSYMBOL_ADD = 17,                       /* ADD  */
  YYSYMBOL_GET = 18,                       /* GET  */
  YYSYMBOL_NPAZ = 19,                      /* NPAZ  */
  YYSYMBOL_NPOS = 20,                      /* NPOS  */
  YYSYMBOL_NRIC = 21,                      /* NRIC  */
  YYSYMBOL_POSIN = 22,                     /* POSIN  */
  YYSYMBOL_IMPORT = 23,                    /* IMPORT  */
  YYSYMBOL_EXPORT = 24,                    /* EXPORT  */
  YYSYMBOL_STAMPA = 25,                    /* STAMPA  */
  YYSYMBOL_USRVAR = 26,                    /* USRVAR  */
  YYSYMBOL_NUMVAR = 27,                    /* NUMVAR  */
  YYSYMBOL_STRINGVAR = 28,                 /* STRINGVAR  */
  YYSYMBOL_PAZVAR = 29,                    /* PAZVAR  */
  YYSYMBOL_REGVAR = 30,                    /* REGVAR  */
  YYSYMBOL_EOL = 31,                       /* EOL  */
  YYSYMBOL_32_ = 32,                       /* ':'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_CMP = 34,                       /* CMP  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '|'  */
  YYSYMBOL_UMINUS = 40,                    /* UMINUS  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_45_ = 45,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_prog = 47,                      /* prog  */
  YYSYMBOL_condExp = 48,                   /* condExp  */
  YYSYMBOL_seqOp = 49,                     /* seqOp  */
  YYSYMBOL_stmt = 50,                      /* stmt  */
  YYSYMBOL_paz = 51,                       /* paz  */
  YYSYMBOL_pazvar = 52,                    /* pazvar  */
  YYSYMBOL_reg = 53,                       /* reg  */
  YYSYMBOL_regfun = 54,                    /* regfun  */
  YYSYMBOL_regvar = 55,                    /* regvar  */
  YYSYMBOL_exp = 56                        /* exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,    37,    35,    44,    36,    45,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,    41,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    39,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    34,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    53,    53,    54,    55,    56,    57,    58,    62,    63,
      64,    67,    68,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    84,    85,    86,    90,    91,    92,    93,
      94,    98,    99,   100,   104,   105,   106,   107,   111,   112,
     113,   114,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "STRING",
  "DATE", "IF", "THEN", "ELSE", "WHILE", "PAZIENTE", "CF", "ESITOTAMP",
  "DATATAMP", "REGIONE", "ISRIC", "REGISTRO", "ADD", "GET", "NPAZ", "NPOS",
  "NRIC", "POSIN", "IMPORT", "EXPORT", "STAMPA", "USRVAR", "NUMVAR",
  "STRINGVAR", "PAZVAR", "REGVAR", "EOL", "':'", "'='", "CMP", "'+'",
  "'-'", "'*'", "'/'", "'|'", "UMINUS", "';'", "'('", "')'", "','", "'.'",
  "$accept", "prog", "condExp", "seqOp", "stmt", "paz", "pazvar", "reg",
  "regfun", "regvar", "exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    58,    61,   287,    43,    45,    42,    47,   124,
     288,    59,    40,    41,    44,    46
};
#endif

#define YYPACT_NINF (-54)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -54,    81,   -54,    -2,   -54,   -54,   -54,   111,   111,   -29,
     -12,     3,   -26,     8,    25,   -25,   -24,   -54,    23,    23,
      23,    11,   -19,   -54,   -54,   -54,   -54,   -54,    67,   -54,
      40,    90,    23,    32,   111,   111,   111,   111,    -6,   117,
     -11,   159,   -54,   -54,   -54,    38,    43,   -54,   -54,    58,
     -54,   -54,   111,    68,    23,    23,    23,    23,   111,   111,
      -4,   -54,    55,    55,    55,    55,    80,   -54,   -54,   -54,
     -54,   -54,   -54,    85,   -54,    77,    83,   -54,   -54,   -54,
      84,    91,    92,   152,   -54,   101,   -54,   -13,   -13,   -54,
     -54,   134,   -23,   -54,    23,    -6,    23,    23,    23,   105,
     111,   111,    19,   106,   108,   119,   123,   -54,   -54,   -54,
      23,   -54,   -54,   -54,   -54,    29,    23,    33,    23,   132,
     -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,    44,    52,    53,     0,     0,     0,
       0,     0,    51,    55,    54,    25,    33,     6,     0,     0,
       0,     0,     0,    14,    42,    15,    16,    43,    13,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    55,    54,     0,     0,    50,    49,     0,
       5,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    22,    19,    21,    20,    25,    24,    26,    27,
      28,    29,    30,    33,    32,     0,     0,    38,    39,    40,
       0,     0,     0,     0,    17,    18,     4,    45,    46,    47,
      48,     8,    11,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     9,    12,
       0,    34,    35,    41,    36,     0,     0,     0,     0,     0,
      23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   -53,     9,   -35,   -54,   112,   -54,   -54,
     -18
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    21,    91,    92,    23,    24,    25,    26,    27,
      28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    48,    49,    67,     9,    10,    93,    35,    38,    40,
      22,    52,    51,    32,    60,    52,    30,    31,   101,    73,
      39,    41,    53,    66,    56,    57,     4,     5,     6,    29,
      33,    54,    55,    56,    57,    34,    87,    88,    89,    90,
      94,    36,    50,    62,    63,    64,    65,   108,   109,    42,
      43,    44,    45,    46,    54,    55,    56,    57,    37,    18,
     103,    85,    19,   110,    54,    55,    56,    57,    54,    55,
      56,    57,    58,   116,    52,    61,   102,   118,   104,   105,
     106,     2,     3,    39,     4,     5,     6,     7,    83,    52,
       8,     9,   115,    54,    55,    56,    57,    10,   117,    86,
     119,    84,    54,    55,    56,    57,    11,    12,    13,    14,
      15,    16,    17,    38,     4,     5,     6,    18,    40,    95,
      19,     9,    59,    20,    52,    96,    97,    10,    68,    69,
      70,    71,    72,    98,    99,    -1,    11,    12,    13,    14,
      15,    16,   100,    54,    55,    56,    57,    18,   107,   111,
      19,   112,    74,    20,    54,    55,    56,    57,    54,    55,
      56,    57,   113,     0,     0,     0,   114,    54,    55,    56,
      57,    77,    78,    79,    80,   120,    75,    76,    77,    78,
      79,    80,    81,    82
};

static const yytype_int8 yycheck[] =
{
      18,    19,    20,    38,    10,    16,    59,    33,    33,    33,
       1,    34,    31,    42,    32,    34,     7,     8,    41,    30,
      45,    45,    41,    29,    37,    38,     3,     4,     5,    31,
      42,    35,    36,    37,    38,    32,    54,    55,    56,    57,
      44,    33,    31,    34,    35,    36,    37,   100,   101,    26,
      27,    28,    29,    30,    35,    36,    37,    38,    33,    36,
      95,    52,    39,    44,    35,    36,    37,    38,    35,    36,
      37,    38,    32,    44,    34,    43,    94,    44,    96,    97,
      98,     0,     1,    45,     3,     4,     5,     6,    45,    34,
       9,    10,   110,    35,    36,    37,    38,    16,   116,    31,
     118,    43,    35,    36,    37,    38,    25,    26,    27,    28,
      29,    30,    31,    33,     3,     4,     5,    36,    33,    42,
      39,    10,    32,    42,    34,    42,    42,    16,    11,    12,
      13,    14,    15,    42,    42,    34,    25,    26,    27,    28,
      29,    30,     8,    35,    36,    37,    38,    36,    43,    43,
      39,    43,    40,    42,    35,    36,    37,    38,    35,    36,
      37,    38,    43,    -1,    -1,    -1,    43,    35,    36,    37,
      38,    19,    20,    21,    22,    43,    17,    18,    19,    20,
      21,    22,    23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,     0,     1,     3,     4,     5,     6,     9,    10,
      16,    25,    26,    27,    28,    29,    30,    31,    36,    39,
      42,    48,    50,    51,    52,    53,    54,    55,    56,    31,
      50,    50,    42,    42,    32,    33,    33,    33,    33,    45,
      33,    45,    26,    27,    28,    29,    30,    56,    56,    56,
      31,    31,    34,    41,    35,    36,    37,    38,    32,    32,
      56,    43,    50,    50,    50,    50,    29,    51,    11,    12,
      13,    14,    15,    30,    53,    17,    18,    19,    20,    21,
      22,    23,    24,    45,    43,    50,    31,    56,    56,    56,
      56,    49,    50,    49,    44,    42,    42,    42,    42,    42,
       8,    41,    56,    51,    56,    56,    56,    43,    49,    49,
      44,    43,    43,    43,    43,    56,    44,    56,    44,    56,
      43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    47,    47,    47,    47,    48,    48,
      48,    49,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    52,    52,    52,    52,
      52,    53,    53,    53,    54,    54,    54,    54,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     4,     3,     2,     3,     4,     6,
       4,     1,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,    12,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     6,     6,     6,     5,     3,     3,
       3,     6,     1,     1,     1,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3: /* prog: prog stmt EOL  */
#line 54 "tesina.y"
                             {processTree('P',(yyvsp[-1].a)); treefree((yyvsp[-1].a)); printf(""); }
#line 1206 "tesina.tab.c"
    break;

  case 4: /* prog: prog stmt ';' EOL  */
#line 55 "tesina.y"
                             {processTree('N',(yyvsp[-2].a)); treefree((yyvsp[-2].a)); printf(""); }
#line 1212 "tesina.tab.c"
    break;

  case 5: /* prog: prog condExp EOL  */
#line 56 "tesina.y"
                             {processTree('N',(yyvsp[-1].a)); treefree((yyvsp[-1].a)); printf(""); }
#line 1218 "tesina.tab.c"
    break;

  case 6: /* prog: prog EOL  */
#line 57 "tesina.y"
                             { printf(""); }
#line 1224 "tesina.tab.c"
    break;

  case 7: /* prog: prog error EOL  */
#line 58 "tesina.y"
                             { yyerrok; yyclearin;}
#line 1230 "tesina.tab.c"
    break;

  case 8: /* condExp: IF stmt ':' seqOp  */
#line 62 "tesina.y"
                                       { (yyval.a) = newCond('I',(yyvsp[-2].a),(yyvsp[0].a),NULL); }
#line 1236 "tesina.tab.c"
    break;

  case 9: /* condExp: IF stmt ':' seqOp ELSE seqOp  */
#line 63 "tesina.y"
                                       { (yyval.a) = newCond('I',(yyvsp[-4].a),(yyvsp[-2].a),(yyvsp[0].a)); }
#line 1242 "tesina.tab.c"
    break;

  case 10: /* condExp: WHILE stmt ':' seqOp  */
#line 64 "tesina.y"
                                       { (yyval.a) = newCond('W',(yyvsp[-2].a),(yyvsp[0].a),NULL); }
#line 1248 "tesina.tab.c"
    break;

  case 12: /* seqOp: stmt ';' seqOp  */
#line 68 "tesina.y"
                     { (yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1254 "tesina.tab.c"
    break;

  case 17: /* stmt: '(' exp ')'  */
#line 75 "tesina.y"
                                                                  { (yyval.a) = (yyvsp[-1].a); }
#line 1260 "tesina.tab.c"
    break;

  case 18: /* stmt: stmt CMP stmt  */
#line 76 "tesina.y"
                                                                  { (yyval.a) = newCmp((yyvsp[-1].cmp), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1266 "tesina.tab.c"
    break;

  case 19: /* stmt: USRVAR '=' stmt  */
#line 77 "tesina.y"
                                                                  { (yyval.a) = newasgn((yyvsp[-2].vr), (yyvsp[0].a)); }
#line 1272 "tesina.tab.c"
    break;

  case 20: /* stmt: STRINGVAR '=' stmt  */
#line 78 "tesina.y"
                                                                  { (yyval.a) = newasgn((yyvsp[-2].vr), (yyvsp[0].a)); }
#line 1278 "tesina.tab.c"
    break;

  case 21: /* stmt: NUMVAR '=' stmt  */
#line 79 "tesina.y"
                                                                  { (yyval.a) = newasgn((yyvsp[-2].vr), (yyvsp[0].a)); }
#line 1284 "tesina.tab.c"
    break;

  case 22: /* stmt: STAMPA ':' stmt  */
#line 80 "tesina.y"
                                                                  { (yyval.a) = newPrint((yyvsp[0].a)); }
#line 1290 "tesina.tab.c"
    break;

  case 23: /* paz: PAZIENTE '(' exp ',' exp ',' exp ',' exp ',' exp ')'  */
#line 84 "tesina.y"
                                                                  { (yyval.a) = newPaziente('P',(yyvsp[-9].a),(yyvsp[-7].a),(yyvsp[-5].a),(yyvsp[-3].a),(yyvsp[-1].a)); }
#line 1296 "tesina.tab.c"
    break;

  case 24: /* paz: PAZVAR '=' paz  */
#line 85 "tesina.y"
                                                                  { (yyval.a) = newasgn((yyvsp[-2].vr), (yyvsp[0].a)); }
#line 1302 "tesina.tab.c"
    break;

  case 25: /* paz: PAZVAR  */
#line 86 "tesina.y"
                                                                  { (yyval.a) = newref((yyvsp[0].vr)); }
#line 1308 "tesina.tab.c"
    break;

  case 26: /* pazvar: PAZVAR '.' CF  */
#line 90 "tesina.y"
                                                                { (yyval.a) = newGet((yyvsp[-2].vr),1); }
#line 1314 "tesina.tab.c"
    break;

  case 27: /* pazvar: PAZVAR '.' ESITOTAMP  */
#line 91 "tesina.y"
                                                                  { (yyval.a) = newGet((yyvsp[-2].vr),2); }
#line 1320 "tesina.tab.c"
    break;

  case 28: /* pazvar: PAZVAR '.' DATATAMP  */
#line 92 "tesina.y"
                                                                  { (yyval.a) = newGet((yyvsp[-2].vr),3); }
#line 1326 "tesina.tab.c"
    break;

  case 29: /* pazvar: PAZVAR '.' REGIONE  */
#line 93 "tesina.y"
                                                                  { (yyval.a) = newGet((yyvsp[-2].vr),4); }
#line 1332 "tesina.tab.c"
    break;

  case 30: /* pazvar: PAZVAR '.' ISRIC  */
#line 94 "tesina.y"
                                                                  { (yyval.a) = newGet((yyvsp[-2].vr),5); }
#line 1338 "tesina.tab.c"
    break;

  case 31: /* reg: REGISTRO '(' ')'  */
#line 98 "tesina.y"
                                                                  { (yyval.a) = newRegistro('O'); }
#line 1344 "tesina.tab.c"
    break;

  case 32: /* reg: REGVAR '=' reg  */
#line 99 "tesina.y"
                                                                  { (yyval.a) = newasgn((yyvsp[-2].vr), (yyvsp[0].a)); }
#line 1350 "tesina.tab.c"
    break;

  case 33: /* reg: REGVAR  */
#line 100 "tesina.y"
                                                                  { (yyval.a) = newref((yyvsp[0].vr)); }
#line 1356 "tesina.tab.c"
    break;

  case 34: /* regfun: REGVAR '.' ADD '(' paz ')'  */
#line 104 "tesina.y"
                                                                { (yyval.a) = addPaziente((yyvsp[-5].vr),(yyvsp[-1].a)); }
#line 1362 "tesina.tab.c"
    break;

  case 35: /* regfun: REGVAR '.' GET '(' exp ')'  */
#line 105 "tesina.y"
                                                               { (yyval.a) = getPaziente((yyvsp[-5].vr),(yyvsp[-1].a)); }
#line 1368 "tesina.tab.c"
    break;

  case 36: /* regfun: REGVAR '.' IMPORT '(' exp ')'  */
#line 106 "tesina.y"
                                                               { (yyval.a) = import((yyvsp[-5].vr),(yyvsp[-1].a)); }
#line 1374 "tesina.tab.c"
    break;

  case 37: /* regfun: REGVAR '.' EXPORT '(' ')'  */
#line 107 "tesina.y"
                                                                  { (yyval.a) = export((yyvsp[-4].vr)); }
#line 1380 "tesina.tab.c"
    break;

  case 38: /* regvar: REGVAR '.' NPAZ  */
#line 111 "tesina.y"
                                                                { (yyval.a) = numPazienti((yyvsp[-2].vr)); }
#line 1386 "tesina.tab.c"
    break;

  case 39: /* regvar: REGVAR '.' NPOS  */
#line 112 "tesina.y"
                                                                  { (yyval.a) = numPositivi((yyvsp[-2].vr)); }
#line 1392 "tesina.tab.c"
    break;

  case 40: /* regvar: REGVAR '.' NRIC  */
#line 113 "tesina.y"
                                                                  { (yyval.a) = numRicoverati((yyvsp[-2].vr)); }
#line 1398 "tesina.tab.c"
    break;

  case 41: /* regvar: REGVAR '.' POSIN '(' exp ')'  */
#line 114 "tesina.y"
                                                                  { (yyval.a) = numPositiviByFilter((yyvsp[-5].vr),(yyvsp[-1].a)); }
#line 1404 "tesina.tab.c"
    break;

  case 44: /* exp: NUMBER  */
#line 119 "tesina.y"
                                                                  { (yyval.a) = newnum((yyvsp[0].d)); }
#line 1410 "tesina.tab.c"
    break;

  case 45: /* exp: exp '+' exp  */
#line 120 "tesina.y"
                                                                  { (yyval.a) = newast('+', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1416 "tesina.tab.c"
    break;

  case 46: /* exp: exp '-' exp  */
#line 121 "tesina.y"
                                                                  { (yyval.a) = newast('-', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1422 "tesina.tab.c"
    break;

  case 47: /* exp: exp '*' exp  */
#line 122 "tesina.y"
                                                                  { (yyval.a) = newast('*', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1428 "tesina.tab.c"
    break;

  case 48: /* exp: exp '/' exp  */
#line 123 "tesina.y"
                                                                  { (yyval.a) = newast('/', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1434 "tesina.tab.c"
    break;

  case 49: /* exp: '|' exp  */
#line 124 "tesina.y"
                                                                  { (yyval.a) = newast('|', (yyvsp[0].a), NULL); }
#line 1440 "tesina.tab.c"
    break;

  case 50: /* exp: '-' exp  */
#line 125 "tesina.y"
                                                                  { (yyval.a) = newast('M', (yyvsp[0].a), NULL); }
#line 1446 "tesina.tab.c"
    break;

  case 51: /* exp: USRVAR  */
#line 126 "tesina.y"
                                                                  { (yyval.a) = newref((yyvsp[0].vr)); }
#line 1452 "tesina.tab.c"
    break;

  case 52: /* exp: STRING  */
#line 127 "tesina.y"
                                                                  { (yyval.a) = newString((yyvsp[0].string)); }
#line 1458 "tesina.tab.c"
    break;

  case 53: /* exp: DATE  */
#line 128 "tesina.y"
                                                                  { (yyval.a) = newString((yyvsp[0].string)); }
#line 1464 "tesina.tab.c"
    break;

  case 54: /* exp: STRINGVAR  */
#line 129 "tesina.y"
                                                                  { (yyval.a) = newref((yyvsp[0].vr)); }
#line 1470 "tesina.tab.c"
    break;

  case 55: /* exp: NUMVAR  */
#line 130 "tesina.y"
                                                                  { (yyval.a) = newref((yyvsp[0].vr)); }
#line 1476 "tesina.tab.c"
    break;


#line 1480 "tesina.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 133 "tesina.y"

