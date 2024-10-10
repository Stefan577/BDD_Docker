// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file src/parser.hpp
 ** Define the kconf::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_SRC_PARSER_HPP_INCLUDED
# define YY_YY_SRC_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 491 "src/parser.ypp"

    #include "varInfo.hpp"
    #include "synExp.hpp"
    
    struct kconf_id;


#line 57 "src/parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 465 "src/parser.ypp"
namespace kconf {
#line 193 "src/parser.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // T_MAINMENU
      // T_MENU
      // T_ENDMENU
      // T_SOURCE
      // T_CHOICE
      // T_ENDCHOICE
      // T_COMMENT
      // T_CONFIG
      // T_MENUCONFIG
      // T_HELP
      // T_IF
      // T_ENDIF
      // T_DEPENDS
      // T_OPTIONAL
      // T_PROMPT
      // T_TYPE
      // T_DEFAULT
      // T_SELECT
      // T_RANGE
      // T_VISIBLE
      // T_OPTION
      // T_ON
      // T_OPT_DEFCONFIG_LIST
      // T_OPT_MODULES
      // T_OPT_ENV
      // T_INSERT
      char dummy1[sizeof (kconf_id*)];

      // T_HELPTEXT
      // T_WORD
      // T_WORD_QUOTE
      // symbol_option_arg
      // prompt
      // word_opt
      char dummy2[sizeof (std::string)];

      // depends_list
      // depends
      // visibility_list
      // visible
      // if_expr
      // expr
      // symbol
      char dummy3[sizeof (synExp*)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    T_EOF = 0,                     // T_EOF
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    T_MAINMENU = 258,              // T_MAINMENU
    T_MENU = 259,                  // T_MENU
    T_ENDMENU = 260,               // T_ENDMENU
    T_SOURCE = 261,                // T_SOURCE
    T_CHOICE = 262,                // T_CHOICE
    T_ENDCHOICE = 263,             // T_ENDCHOICE
    T_COMMENT = 264,               // T_COMMENT
    T_CONFIG = 265,                // T_CONFIG
    T_MENUCONFIG = 266,            // T_MENUCONFIG
    T_HELP = 267,                  // T_HELP
    T_IF = 268,                    // T_IF
    T_ENDIF = 269,                 // T_ENDIF
    T_DEPENDS = 270,               // T_DEPENDS
    T_OPTIONAL = 271,              // T_OPTIONAL
    T_PROMPT = 272,                // T_PROMPT
    T_TYPE = 273,                  // T_TYPE
    T_DEFAULT = 274,               // T_DEFAULT
    T_SELECT = 275,                // T_SELECT
    T_RANGE = 276,                 // T_RANGE
    T_VISIBLE = 277,               // T_VISIBLE
    T_OPTION = 278,                // T_OPTION
    T_ON = 279,                    // T_ON
    T_OPT_DEFCONFIG_LIST = 280,    // T_OPT_DEFCONFIG_LIST
    T_OPT_MODULES = 281,           // T_OPT_MODULES
    T_OPT_ENV = 282,               // T_OPT_ENV
    T_INSERT = 283,                // T_INSERT
    T_HELPTEXT = 284,              // T_HELPTEXT
    T_WORD = 285,                  // T_WORD
    T_WORD_QUOTE = 286,            // T_WORD_QUOTE
    T_UNEQUAL = 287,               // T_UNEQUAL
    T_CLOSE_PAREN = 288,           // T_CLOSE_PAREN
    T_OPEN_PAREN = 289,            // T_OPEN_PAREN
    T_EOL = 290,                   // T_EOL
    T_EOP = 291,                   // T_EOP
    T_OR = 292,                    // T_OR
    T_AND = 293,                   // T_AND
    T_EQUAL = 294,                 // T_EQUAL
    T_NOT = 295                    // T_NOT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 41, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // T_EOF
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_T_MAINMENU = 3,                        // T_MAINMENU
        S_T_MENU = 4,                            // T_MENU
        S_T_ENDMENU = 5,                         // T_ENDMENU
        S_T_SOURCE = 6,                          // T_SOURCE
        S_T_CHOICE = 7,                          // T_CHOICE
        S_T_ENDCHOICE = 8,                       // T_ENDCHOICE
        S_T_COMMENT = 9,                         // T_COMMENT
        S_T_CONFIG = 10,                         // T_CONFIG
        S_T_MENUCONFIG = 11,                     // T_MENUCONFIG
        S_T_HELP = 12,                           // T_HELP
        S_T_IF = 13,                             // T_IF
        S_T_ENDIF = 14,                          // T_ENDIF
        S_T_DEPENDS = 15,                        // T_DEPENDS
        S_T_OPTIONAL = 16,                       // T_OPTIONAL
        S_T_PROMPT = 17,                         // T_PROMPT
        S_T_TYPE = 18,                           // T_TYPE
        S_T_DEFAULT = 19,                        // T_DEFAULT
        S_T_SELECT = 20,                         // T_SELECT
        S_T_RANGE = 21,                          // T_RANGE
        S_T_VISIBLE = 22,                        // T_VISIBLE
        S_T_OPTION = 23,                         // T_OPTION
        S_T_ON = 24,                             // T_ON
        S_T_OPT_DEFCONFIG_LIST = 25,             // T_OPT_DEFCONFIG_LIST
        S_T_OPT_MODULES = 26,                    // T_OPT_MODULES
        S_T_OPT_ENV = 27,                        // T_OPT_ENV
        S_T_INSERT = 28,                         // T_INSERT
        S_T_HELPTEXT = 29,                       // T_HELPTEXT
        S_T_WORD = 30,                           // T_WORD
        S_T_WORD_QUOTE = 31,                     // T_WORD_QUOTE
        S_T_UNEQUAL = 32,                        // T_UNEQUAL
        S_T_CLOSE_PAREN = 33,                    // T_CLOSE_PAREN
        S_T_OPEN_PAREN = 34,                     // T_OPEN_PAREN
        S_T_EOL = 35,                            // T_EOL
        S_T_EOP = 36,                            // T_EOP
        S_T_OR = 37,                             // T_OR
        S_T_AND = 38,                            // T_AND
        S_T_EQUAL = 39,                          // T_EQUAL
        S_T_NOT = 40,                            // T_NOT
        S_YYACCEPT = 41,                         // $accept
        S_input = 42,                            // input
        S_pass = 43,                             // pass
        S_start = 44,                            // start
        S_stmt_list = 45,                        // stmt_list
        S_option_name = 46,                      // option_name
        S_common_stmt = 47,                      // common_stmt
        S_option_error = 48,                     // option_error
        S_config_entry_start = 49,               // config_entry_start
        S_config_stmt = 50,                      // config_stmt
        S_insert_stmt = 51,                      // insert_stmt
        S_menuconfig_entry_start = 52,           // menuconfig_entry_start
        S_menuconfig_stmt = 53,                  // menuconfig_stmt
        S_config_option_list = 54,               // config_option_list
        S_config_option = 55,                    // config_option
        S_symbol_option = 56,                    // symbol_option
        S_symbol_option_list = 57,               // symbol_option_list
        S_symbol_option_arg = 58,                // symbol_option_arg
        S_choice = 59,                           // choice
        S_choice_entry = 60,                     // choice_entry
        S_choice_end = 61,                       // choice_end
        S_choice_stmt = 62,                      // choice_stmt
        S_choice_option_list = 63,               // choice_option_list
        S_choice_option = 64,                    // choice_option
        S_choice_block = 65,                     // choice_block
        S_if_entry = 66,                         // if_entry
        S_if_end = 67,                           // if_end
        S_if_stmt = 68,                          // if_stmt
        S_if_block = 69,                         // if_block
        S_mainmenu_stmt = 70,                    // mainmenu_stmt
        S_menu = 71,                             // menu
        S_menu_entry = 72,                       // menu_entry
        S_menu_end = 73,                         // menu_end
        S_menu_stmt = 74,                        // menu_stmt
        S_menu_block = 75,                       // menu_block
        S_source_stmt = 76,                      // source_stmt
        S_comment = 77,                          // comment
        S_comment_stmt = 78,                     // comment_stmt
        S_help_start = 79,                       // help_start
        S_help = 80,                             // help
        S_depends_list = 81,                     // depends_list
        S_depends = 82,                          // depends
        S_visibility_list = 83,                  // visibility_list
        S_visible = 84,                          // visible
        S_prompt_stmt_opt = 85,                  // prompt_stmt_opt
        S_prompt = 86,                           // prompt
        S_end = 87,                              // end
        S_nl = 88,                               // nl
        S_if_expr = 89,                          // if_expr
        S_expr = 90,                             // expr
        S_symbol = 91,                           // symbol
        S_word_opt = 92                          // word_opt
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_T_MAINMENU: // T_MAINMENU
      case symbol_kind::S_T_MENU: // T_MENU
      case symbol_kind::S_T_ENDMENU: // T_ENDMENU
      case symbol_kind::S_T_SOURCE: // T_SOURCE
      case symbol_kind::S_T_CHOICE: // T_CHOICE
      case symbol_kind::S_T_ENDCHOICE: // T_ENDCHOICE
      case symbol_kind::S_T_COMMENT: // T_COMMENT
      case symbol_kind::S_T_CONFIG: // T_CONFIG
      case symbol_kind::S_T_MENUCONFIG: // T_MENUCONFIG
      case symbol_kind::S_T_HELP: // T_HELP
      case symbol_kind::S_T_IF: // T_IF
      case symbol_kind::S_T_ENDIF: // T_ENDIF
      case symbol_kind::S_T_DEPENDS: // T_DEPENDS
      case symbol_kind::S_T_OPTIONAL: // T_OPTIONAL
      case symbol_kind::S_T_PROMPT: // T_PROMPT
      case symbol_kind::S_T_TYPE: // T_TYPE
      case symbol_kind::S_T_DEFAULT: // T_DEFAULT
      case symbol_kind::S_T_SELECT: // T_SELECT
      case symbol_kind::S_T_RANGE: // T_RANGE
      case symbol_kind::S_T_VISIBLE: // T_VISIBLE
      case symbol_kind::S_T_OPTION: // T_OPTION
      case symbol_kind::S_T_ON: // T_ON
      case symbol_kind::S_T_OPT_DEFCONFIG_LIST: // T_OPT_DEFCONFIG_LIST
      case symbol_kind::S_T_OPT_MODULES: // T_OPT_MODULES
      case symbol_kind::S_T_OPT_ENV: // T_OPT_ENV
      case symbol_kind::S_T_INSERT: // T_INSERT
        value.move< kconf_id* > (std::move (that.value));
        break;

      case symbol_kind::S_T_HELPTEXT: // T_HELPTEXT
      case symbol_kind::S_T_WORD: // T_WORD
      case symbol_kind::S_T_WORD_QUOTE: // T_WORD_QUOTE
      case symbol_kind::S_symbol_option_arg: // symbol_option_arg
      case symbol_kind::S_prompt: // prompt
      case symbol_kind::S_word_opt: // word_opt
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_depends_list: // depends_list
      case symbol_kind::S_depends: // depends
      case symbol_kind::S_visibility_list: // visibility_list
      case symbol_kind::S_visible: // visible
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_symbol: // symbol
        value.move< synExp* > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kconf_id*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kconf_id*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, synExp*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const synExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_T_MAINMENU: // T_MAINMENU
      case symbol_kind::S_T_MENU: // T_MENU
      case symbol_kind::S_T_ENDMENU: // T_ENDMENU
      case symbol_kind::S_T_SOURCE: // T_SOURCE
      case symbol_kind::S_T_CHOICE: // T_CHOICE
      case symbol_kind::S_T_ENDCHOICE: // T_ENDCHOICE
      case symbol_kind::S_T_COMMENT: // T_COMMENT
      case symbol_kind::S_T_CONFIG: // T_CONFIG
      case symbol_kind::S_T_MENUCONFIG: // T_MENUCONFIG
      case symbol_kind::S_T_HELP: // T_HELP
      case symbol_kind::S_T_IF: // T_IF
      case symbol_kind::S_T_ENDIF: // T_ENDIF
      case symbol_kind::S_T_DEPENDS: // T_DEPENDS
      case symbol_kind::S_T_OPTIONAL: // T_OPTIONAL
      case symbol_kind::S_T_PROMPT: // T_PROMPT
      case symbol_kind::S_T_TYPE: // T_TYPE
      case symbol_kind::S_T_DEFAULT: // T_DEFAULT
      case symbol_kind::S_T_SELECT: // T_SELECT
      case symbol_kind::S_T_RANGE: // T_RANGE
      case symbol_kind::S_T_VISIBLE: // T_VISIBLE
      case symbol_kind::S_T_OPTION: // T_OPTION
      case symbol_kind::S_T_ON: // T_ON
      case symbol_kind::S_T_OPT_DEFCONFIG_LIST: // T_OPT_DEFCONFIG_LIST
      case symbol_kind::S_T_OPT_MODULES: // T_OPT_MODULES
      case symbol_kind::S_T_OPT_ENV: // T_OPT_ENV
      case symbol_kind::S_T_INSERT: // T_INSERT
        value.template destroy< kconf_id* > ();
        break;

      case symbol_kind::S_T_HELPTEXT: // T_HELPTEXT
      case symbol_kind::S_T_WORD: // T_WORD
      case symbol_kind::S_T_WORD_QUOTE: // T_WORD_QUOTE
      case symbol_kind::S_symbol_option_arg: // symbol_option_arg
      case symbol_kind::S_prompt: // prompt
      case symbol_kind::S_word_opt: // word_opt
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_depends_list: // depends_list
      case symbol_kind::S_depends: // depends
      case symbol_kind::S_visibility_list: // visibility_list
      case symbol_kind::S_visible: // visible
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_symbol: // symbol
        value.template destroy< synExp* > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kconf_id* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kconf_id*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    Parser (class Driver& driver_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_EOF (location_type l)
      {
        return symbol_type (token::T_EOF, std::move (l));
      }
#else
      static
      symbol_type
      make_T_EOF (const location_type& l)
      {
        return symbol_type (token::T_EOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_MAINMENU (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_MAINMENU, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_MAINMENU (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_MAINMENU, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_MENU (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_MENU, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_MENU (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_MENU, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_ENDMENU (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_ENDMENU, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_ENDMENU (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_ENDMENU, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_SOURCE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_SOURCE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_SOURCE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_SOURCE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_CHOICE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_CHOICE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_CHOICE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_CHOICE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_ENDCHOICE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_ENDCHOICE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_ENDCHOICE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_ENDCHOICE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_COMMENT (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_COMMENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_COMMENT (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_COMMENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_CONFIG (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_CONFIG, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_CONFIG (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_CONFIG, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_MENUCONFIG (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_MENUCONFIG, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_MENUCONFIG (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_MENUCONFIG, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_HELP (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_HELP, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_HELP (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_HELP, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_IF (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_IF (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_ENDIF (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_ENDIF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_ENDIF (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_ENDIF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_DEPENDS (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_DEPENDS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_DEPENDS (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_DEPENDS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPTIONAL (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_OPTIONAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPTIONAL (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_OPTIONAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_PROMPT (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_PROMPT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_PROMPT (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_PROMPT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_TYPE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_TYPE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_TYPE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_TYPE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_DEFAULT (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_DEFAULT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_DEFAULT (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_DEFAULT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_SELECT (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_SELECT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_SELECT (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_SELECT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_RANGE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_RANGE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_RANGE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_RANGE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_VISIBLE (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_VISIBLE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_VISIBLE (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_VISIBLE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPTION (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_OPTION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPTION (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_OPTION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_ON (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_ON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_ON (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_ON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPT_DEFCONFIG_LIST (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_OPT_DEFCONFIG_LIST, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPT_DEFCONFIG_LIST (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_OPT_DEFCONFIG_LIST, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPT_MODULES (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_OPT_MODULES, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPT_MODULES (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_OPT_MODULES, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPT_ENV (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_OPT_ENV, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPT_ENV (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_OPT_ENV, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_INSERT (kconf_id* v, location_type l)
      {
        return symbol_type (token::T_INSERT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_INSERT (const kconf_id*& v, const location_type& l)
      {
        return symbol_type (token::T_INSERT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_HELPTEXT (std::string v, location_type l)
      {
        return symbol_type (token::T_HELPTEXT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_HELPTEXT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::T_HELPTEXT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_WORD (std::string v, location_type l)
      {
        return symbol_type (token::T_WORD, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_WORD (const std::string& v, const location_type& l)
      {
        return symbol_type (token::T_WORD, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_WORD_QUOTE (std::string v, location_type l)
      {
        return symbol_type (token::T_WORD_QUOTE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_T_WORD_QUOTE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::T_WORD_QUOTE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_UNEQUAL (location_type l)
      {
        return symbol_type (token::T_UNEQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_T_UNEQUAL (const location_type& l)
      {
        return symbol_type (token::T_UNEQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_CLOSE_PAREN (location_type l)
      {
        return symbol_type (token::T_CLOSE_PAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_T_CLOSE_PAREN (const location_type& l)
      {
        return symbol_type (token::T_CLOSE_PAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OPEN_PAREN (location_type l)
      {
        return symbol_type (token::T_OPEN_PAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_T_OPEN_PAREN (const location_type& l)
      {
        return symbol_type (token::T_OPEN_PAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_EOL (location_type l)
      {
        return symbol_type (token::T_EOL, std::move (l));
      }
#else
      static
      symbol_type
      make_T_EOL (const location_type& l)
      {
        return symbol_type (token::T_EOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_EOP (location_type l)
      {
        return symbol_type (token::T_EOP, std::move (l));
      }
#else
      static
      symbol_type
      make_T_EOP (const location_type& l)
      {
        return symbol_type (token::T_EOP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_OR (location_type l)
      {
        return symbol_type (token::T_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_T_OR (const location_type& l)
      {
        return symbol_type (token::T_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_AND (location_type l)
      {
        return symbol_type (token::T_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_T_AND (const location_type& l)
      {
        return symbol_type (token::T_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_EQUAL (location_type l)
      {
        return symbol_type (token::T_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_T_EQUAL (const location_type& l)
      {
        return symbol_type (token::T_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_NOT (location_type l)
      {
        return symbol_type (token::T_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_T_NOT (const location_type& l)
      {
        return symbol_type (token::T_NOT, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 325,     ///< Last index in yytable_.
      yynnts_ = 52,  ///< Number of nonterminal symbols.
      yyfinal_ = 11 ///< Termination state number.
    };


    // User arguments.
    class Driver& driver;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
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
      35,    36,    37,    38,    39,    40
    };
    // Last valid token kind.
    const int code_max = 295;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_T_MAINMENU: // T_MAINMENU
      case symbol_kind::S_T_MENU: // T_MENU
      case symbol_kind::S_T_ENDMENU: // T_ENDMENU
      case symbol_kind::S_T_SOURCE: // T_SOURCE
      case symbol_kind::S_T_CHOICE: // T_CHOICE
      case symbol_kind::S_T_ENDCHOICE: // T_ENDCHOICE
      case symbol_kind::S_T_COMMENT: // T_COMMENT
      case symbol_kind::S_T_CONFIG: // T_CONFIG
      case symbol_kind::S_T_MENUCONFIG: // T_MENUCONFIG
      case symbol_kind::S_T_HELP: // T_HELP
      case symbol_kind::S_T_IF: // T_IF
      case symbol_kind::S_T_ENDIF: // T_ENDIF
      case symbol_kind::S_T_DEPENDS: // T_DEPENDS
      case symbol_kind::S_T_OPTIONAL: // T_OPTIONAL
      case symbol_kind::S_T_PROMPT: // T_PROMPT
      case symbol_kind::S_T_TYPE: // T_TYPE
      case symbol_kind::S_T_DEFAULT: // T_DEFAULT
      case symbol_kind::S_T_SELECT: // T_SELECT
      case symbol_kind::S_T_RANGE: // T_RANGE
      case symbol_kind::S_T_VISIBLE: // T_VISIBLE
      case symbol_kind::S_T_OPTION: // T_OPTION
      case symbol_kind::S_T_ON: // T_ON
      case symbol_kind::S_T_OPT_DEFCONFIG_LIST: // T_OPT_DEFCONFIG_LIST
      case symbol_kind::S_T_OPT_MODULES: // T_OPT_MODULES
      case symbol_kind::S_T_OPT_ENV: // T_OPT_ENV
      case symbol_kind::S_T_INSERT: // T_INSERT
        value.copy< kconf_id* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_T_HELPTEXT: // T_HELPTEXT
      case symbol_kind::S_T_WORD: // T_WORD
      case symbol_kind::S_T_WORD_QUOTE: // T_WORD_QUOTE
      case symbol_kind::S_symbol_option_arg: // symbol_option_arg
      case symbol_kind::S_prompt: // prompt
      case symbol_kind::S_word_opt: // word_opt
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_depends_list: // depends_list
      case symbol_kind::S_depends: // depends
      case symbol_kind::S_visibility_list: // visibility_list
      case symbol_kind::S_visible: // visible
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_symbol: // symbol
        value.copy< synExp* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_T_MAINMENU: // T_MAINMENU
      case symbol_kind::S_T_MENU: // T_MENU
      case symbol_kind::S_T_ENDMENU: // T_ENDMENU
      case symbol_kind::S_T_SOURCE: // T_SOURCE
      case symbol_kind::S_T_CHOICE: // T_CHOICE
      case symbol_kind::S_T_ENDCHOICE: // T_ENDCHOICE
      case symbol_kind::S_T_COMMENT: // T_COMMENT
      case symbol_kind::S_T_CONFIG: // T_CONFIG
      case symbol_kind::S_T_MENUCONFIG: // T_MENUCONFIG
      case symbol_kind::S_T_HELP: // T_HELP
      case symbol_kind::S_T_IF: // T_IF
      case symbol_kind::S_T_ENDIF: // T_ENDIF
      case symbol_kind::S_T_DEPENDS: // T_DEPENDS
      case symbol_kind::S_T_OPTIONAL: // T_OPTIONAL
      case symbol_kind::S_T_PROMPT: // T_PROMPT
      case symbol_kind::S_T_TYPE: // T_TYPE
      case symbol_kind::S_T_DEFAULT: // T_DEFAULT
      case symbol_kind::S_T_SELECT: // T_SELECT
      case symbol_kind::S_T_RANGE: // T_RANGE
      case symbol_kind::S_T_VISIBLE: // T_VISIBLE
      case symbol_kind::S_T_OPTION: // T_OPTION
      case symbol_kind::S_T_ON: // T_ON
      case symbol_kind::S_T_OPT_DEFCONFIG_LIST: // T_OPT_DEFCONFIG_LIST
      case symbol_kind::S_T_OPT_MODULES: // T_OPT_MODULES
      case symbol_kind::S_T_OPT_ENV: // T_OPT_ENV
      case symbol_kind::S_T_INSERT: // T_INSERT
        value.move< kconf_id* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_T_HELPTEXT: // T_HELPTEXT
      case symbol_kind::S_T_WORD: // T_WORD
      case symbol_kind::S_T_WORD_QUOTE: // T_WORD_QUOTE
      case symbol_kind::S_symbol_option_arg: // symbol_option_arg
      case symbol_kind::S_prompt: // prompt
      case symbol_kind::S_word_opt: // word_opt
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_depends_list: // depends_list
      case symbol_kind::S_depends: // depends
      case symbol_kind::S_visibility_list: // visibility_list
      case symbol_kind::S_visible: // visible
      case symbol_kind::S_if_expr: // if_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_symbol: // symbol
        value.move< synExp* > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 465 "src/parser.ypp"
} // kconf
#line 2223 "src/parser.hpp"




#endif // !YY_YY_SRC_PARSER_HPP_INCLUDED
