%language "c++"
%skeleton "lalr1.cc"

%define api.value.type variant
%param {Driver* driver}

%code requires {
    #include <string>
    #include <memory>
    namespace yy { class Driver; }
}

%code {
    #include "frontend/frontend.hh"
    namespace yy {parser::token_type yylex(parser::semantic_type* yylval, Driver* driver);}
}

%token <std::string> IDENTIFIER
%token <int> INTEGER
%token FUNC_DECL              ".func"
       CPOLL_DECL             ".cpool"
       NAMES_DECL             ".names"
       CODE_DECL              ".code"
       COLON                  ":"
%%

program:            funcList                                  {};

funcList:           funcList func                             {};
                  | func                                      {};

func:               FUNC_DECL cpollBlock namesBlock codeBlock {};
cpollBlock:         CPOLL_DECL constants                      {};
                  | /* empty */                               {};

constants:          constants leechObjEntry                   {};
                  | leechObjEntry                             {};

leechObjEntry:      IDENTIFIER COLON leechObj                 {};

leechObj:           IDENTIFIER                                {};

namesBlock:         NAMES_DECL names                          {};
                  | /* empty */                               {};

names:              names nameEntry                           {};
                  | nameEntry                                 {};

nameEntry:          IDENTIFIER COLON IDENTIFIER               {};

codeBlock:          CODE_DECL instructions                    {};
                  | /* empty */                               {};

instructions:       instructions instruction                  {};
                  | instruction                               {};

instruction:        IDENTIFIER                                {};
                  | IDENTIFIER INTEGER                        {};
%%

namespace yy {
    parser::token_type yylex (parser::semantic_type* yylval, Driver* driver) {
        return driver->yylex(yylval);
    }

    void parser::error (const std::string& msg) {
        std::cout << msg << " in line: " << std::endl;
    }
}
