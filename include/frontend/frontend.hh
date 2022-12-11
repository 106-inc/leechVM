#ifndef __INCLUDE_DRIVER_HH__
#define __INCLUDE_DRIVER_HH__

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "lLexer.hh"
#include "parser.hh"

namespace yy {

class Driver final {
public:
  ~Driver() = default;
  Driver(std::istream &in, std::ostream &out);

  parser::token_type yylex(parser::semantic_type *yylval,
                           parser::location_type *yylloc);
  bool parse();

  friend parser;

private:
  void reportSyntaxError(const parser::context &ctx);
  void reportExpctdTok(const yy::parser::context &ctx);

  enum Meta { numTokens = 10 };

private:
  std::unique_ptr<Lexer> m_lexer = nullptr;
};

} // namespace yy

#endif /* __INCLUDE_DRIVER_HH__ */
