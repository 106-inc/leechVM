set(GRAMMAR_GEN ${CMAKE_CURRENT_BINARY_DIR})

BISON_TARGET(parser parser.y ${GRAMMAR_GEN}/parser.cc
             DEFINES_FILE ${GRAMMAR_GEN}/parser.hh)

message(STATUS "bison files generated in: ${BISON_parser_OUTPUTS}")

FLEX_TARGET(lexer lexer.l  ${GRAMMAR_GEN}/lexer.cc)
message(STATUS "flex files generated in: ${FLEX_lexer_OUTPUTS}")

add_flex_bison_dependency(lexer parser)

add_library(frontend frontend.cc ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})
target_include_directories(
    frontend
    SYSTEM
    PUBLIC
    ${GRAMMAR_GEN}
)
