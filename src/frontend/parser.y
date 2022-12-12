%language "c++"
%skeleton "lalr1.cc"

%define parse.trace
%define parse.lac full
%locations
%define api.value.type variant
%define parse.error custom

%param {Driver* driver}

%code requires {
    #include <string>
    #include <memory>
    namespace yy { class Driver; }

    #include "common/common.hh"
    #include "common/opcodes.hh"
}

%code {
    #include "frontend/frontend.hh"

namespace yy
  { parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* yylloc, Driver* driver); }
}

%token <std::string> IDENTIFIER
%token <int> INTEGER
%token FUNC_DECL              ".func"
       CPOLL_DECL             ".cpool"
       NAMES_DECL             ".names"
       CODE_DECL              ".code"
       LABEL                  ".label"
       COLON                  ":"
       LRB                    "("
       RRB                    ")"
       COMMA                  ","

%nterm<leech::Instruction>    instruction;

%%

program:            funcList                                  {};

funcList:           funcList func                             {};
                  | func                                      {};

func:               FUNC_DECL IDENTIFIER
                        cpollBlock namesBlock codeBlock       {};
cpollBlock:         CPOLL_DECL constants                      {};
                  | /* empty */                               {};

constants:          constants leechObjEntry                   {};
                  | leechObjEntry                             {};

leechObjEntry:      INTEGER COLON leechObj                    {};

leechObj:           primitiveTy                               {};
                  | array                                     {};

primitiveTy:        IDENTIFIER                                {};
                  | INTEGER                                   {};

array:              LRB arrayArgs RRB                         {};
arrayArgs:          arrayArgs COMMA primitiveTy               {};
                  | primitiveTy                               {};

namesBlock:         NAMES_DECL names                          {};
                  | /* empty */                               {};

names:              names nameEntry                           {};
                  | nameEntry                                 {};

nameEntry:          INTEGER COLON IDENTIFIER                  {};

codeBlock:          CODE_DECL code                            { driver->instrCount_ = 0; };
                  | /* empty */                               {};

code:               code codeEntry                            {};
                  | codeEntry                                 {};

codeEntry:          LABEL IDENTIFIER                          {
                                                                auto&& it = driver->forwardBranches_.find($2);
                                                                if (it != driver->forwardBranches_.end()) {
                                                                  driver->leechFile_->code[it->second].setArg(driver->instrCount_);
                                                                }
                                                                driver->labels_[$2] = driver->instrCount_;
                                                              };
                  | instruction                               {
                                                                driver->leechFile_->code.push_back($1);
                                                                ++driver->instrCount_;
                                                                ++driver->globalInstrCount_;
                                                              };

instruction:        IDENTIFIER                                {
                                                                // TODO: process invalid opcode
                                                                auto opcode = leech::OpcodeConv::fromName($1).value();
                                                                $$ = leech::Instruction(opcode);
                                                              };
                  | IDENTIFIER INTEGER                        {
                                                                // TODO: process invalid opcode
                                                                auto opcode = leech::OpcodeConv::fromName($1).value();
                                                                $$ = leech::Instruction(opcode, $2);
                                                              };
                  | IDENTIFIER COLON IDENTIFIER               {
                                                                // TODO: process invalid opcode
                                                                auto opcode = leech::OpcodeConv::fromName($1).value();
                                                                auto&& it = driver->labels_.find($3);
                                                                if (it != driver->labels_.end()) {
                                                                  $$ = leech::Instruction(opcode, it->second);
                                                                } else {
                                                                  driver->forwardBranches_[$3] = driver->globalInstrCount_;
                                                                  $$ = leech::Instruction(opcode);
                                                                }
                                                              };
%%

namespace yy {
  void parser::error (const parser::location_type& location, const std::string& string)
  {
    std::cerr << string << " in (line.column): "<< location << std::endl;
  }

  parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* yylloc, Driver* driver)
  {
    return driver->yylex(yylval, yylloc);
  }

  void parser::report_syntax_error(parser::context const& ctx) const
  {
    driver->reportSyntaxError(ctx);
  }
}
