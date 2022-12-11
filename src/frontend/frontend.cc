#include "frontend/frontend.hh"

namespace yy {

Driver::Driver(std::istream &in, std::ostream &out) {
  m_lexer = std::make_unique<Lexer>(in, out);
}

bool Driver::parse() {
  parser parser(this);
  bool res = parser.parse();
  return !res;
}

parser::token_type Driver::yylex(parser::semantic_type *yylval,
                                 parser::location_type *yylloc) {
  parser::token_type token = static_cast<parser::token_type>(m_lexer->yylex());
  if (token == yy::parser::token_type::IDENTIFIER) {
    std::string name(m_lexer->YYText());
    parser::semantic_type tmp;
    tmp.as<std::string>() = name;
    yylval->swap<std::string>(tmp);
  } else if (token == yy::parser::token_type::INTEGER) {
    yylval->as<int>() = std::atoi(m_lexer->YYText());
  }

  *yylloc = m_lexer->getCurLocation();
  return token;
}

void Driver::reportSyntaxError(const parser::context &ctx) {
  auto loc = ctx.location();

  std::cerr << "syntax error in ";
  std::cerr << "line: " << loc.begin.line;
  std::cerr << ", column: " << loc.begin.column << std::endl;

  reportExpctdTok(ctx);
  reportUnexpctdTok(ctx);
}

void Driver::reportExpctdTok(const yy::parser::context &ctx) {
  // Report the tokens expected at this point.
  parser::symbol_kind_type expectd_tokns[Meta::numTokens];
  size_t num_of_expectd_tokns =
      ctx.expected_tokens(expectd_tokns, Meta::numTokens);

  std::cerr << "expected:";

  for (size_t i = 0; i < num_of_expectd_tokns; ++i) {
    if (i != 0)
      std::cerr << " or ";

    std::cerr << " <" << parser::symbol_name(expectd_tokns[i]) << "> ";
  }

  std::cerr << std::endl;
}

void Driver::reportUnexpctdTok(const yy::parser::context &ctx) {
  // Report the unexpected token.
  auto lookahead = ctx.token();

  std::cerr << "before: "
            << "<" << parser::symbol_name(lookahead) << ">" << std::endl;
}

} // namespace yy
