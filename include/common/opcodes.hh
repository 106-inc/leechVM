#ifndef __INCLUDE_COMMON_OPCODES_HH__
#define __INCLUDE_COMMON_OPCODES_HH__

#include <concepts>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace leech {
enum class Opcodes {
  UNKNOWN,
  POP_TOP,
  ROT_TWO,
  ROT_THREE,
  DUP_TOP,
  DUP_TOP_TWO,
  ROT_FOUR,
  NOP,
  UNARY_POSITIVE,
  UNARY_NEGATIVE,
  UNARY_NOT,
  UNARY_INVERT,
  BINARY_MATRIX_MULTIPLY,
  INPLACE_MATRIX_MULTIPLY,
  BINARY_POWER,
  BINARY_MULTIPLY,
  BINARY_MODULO,
  BINARY_ADD,
  BINARY_SUBTRACT,
  BINARY_SUBSCR,
  BINARY_FLOOR_DIVIDE,
  BINARY_TRUE_DIVIDE,
  INPLACE_FLOOR_DIVIDE,
  INPLACE_TRUE_DIVIDE,
  GET_LEN,
  MATCH_MAPPING,
  MATCH_SEQUENCE,
  MATCH_KEYS,
  COPY_DICT_WITHOUT_KEYS,
  WITH_EXCEPT_START,
  GET_AITER,
  GET_ANEXT,
  BEFORE_ASYNC_WITH,
  END_ASYNC_FOR,
  INPLACE_ADD,
  INPLACE_SUBTRACT,
  INPLACE_MULTIPLY,
  INPLACE_MODULO,
  STORE_SUBSCR,
  DELETE_SUBSCR,
  BINARY_LSHIFT,
  BINARY_RSHIFT,
  BINARY_AND,
  BINARY_XOR,
  BINARY_OR,
  INPLACE_POWER,
  GET_ITER,
  GET_YIELD_FROM_ITER,
  PRINT_EXPR,
  LOAD_BUILD_CLASS,
  YIELD_FROM,
  GET_AWAITABLE,
  LOAD_ASSERTION_ERROR,
  INPLACE_LSHIFT,
  INPLACE_RSHIFT,
  INPLACE_AND,
  INPLACE_XOR,
  INPLACE_OR,
  LIST_TO_TUPLE,
  RETURN_VALUE,
  IMPORT_STAR,
  SETUP_ANNOTATIONS,
  YIELD_VALUE,
  POP_BLOCK,
  POP_EXCEPT,
  HAVE_ARGUMENT,
  STORE_NAME,
  DELETE_NAME,
  UNPACK_SEQUENCE,
  FOR_ITER,
  UNPACK_EX,
  STORE_ATTR,
  DELETE_ATTR,
  STORE_GLOBAL,
  DELETE_GLOBAL,
  ROT_N,
  LOAD_CONST,
  LOAD_NAME,
  BUILD_TUPLE,
  BUILD_LIST,
  BUILD_SET,
  BUILD_MAP,
  LOAD_ATTR,
  COMPARE_OP,
  IMPORT_NAME,
  IMPORT_FROM,
  JUMP_FORWARD,
  JUMP_IF_FALSE_OR_POP,
  JUMP_IF_TRUE_OR_POP,
  JUMP_ABSOLUTE,
  POP_JUMP_IF_FALSE,
  POP_JUMP_IF_TRUE,
  LOAD_GLOBAL,
  IS_OP,
  CONTAINS_OP,
  RERAISE,
  JUMP_IF_NOT_EXC_MATCH,
  SETUP_FINALLY,
  LOAD_FAST,
  STORE_FAST,
  DELETE_FAST,
  GEN_START,
  RAISE_VARARGS,
  CALL_FUNCTION,
  MAKE_FUNCTION,
  BUILD_SLICE,
  LOAD_CLOSURE,
  LOAD_DEREF,
  STORE_DEREF,
  DELETE_DEREF,
  CALL_FUNCTION_KW,
  CALL_FUNCTION_EX,
  SETUP_WITH,
  EXTENDED_ARG,
  LIST_APPEND,
  SET_ADD,
  MAP_ADD,
  LOAD_CLASSDEREF,
  MATCH_CLASS,
  SETUP_ASYNC_WITH,
  FORMAT_VALUE,
  BUILD_CONST_KEY_MAP,
  BUILD_STRING,
  LOAD_METHOD,
  CALL_METHOD,
  LIST_EXTEND,
  SET_UPDATE,
  DICT_MERGE,
  DICT_UPDATE
};

template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

class OpcodeConv final {
private:
  static const auto &getStrToOpcodeMap() {
    static std::unordered_map<std::string_view, Opcodes> toOpcodeMap{
        {"POP_TOP", Opcodes::POP_TOP},
        {"ROT_TWO", Opcodes::ROT_TWO},
        {"ROT_THREE", Opcodes::ROT_THREE},
        {"DUP_TOP", Opcodes::DUP_TOP},
        {"DUP_TOP_TWO", Opcodes::DUP_TOP_TWO},
        {"ROT_FOUR", Opcodes::ROT_FOUR},
        {"NOP", Opcodes::NOP},
        {"UNARY_POSITIVE", Opcodes::UNARY_POSITIVE},
        {"UNARY_NEGATIVE", Opcodes::UNARY_NEGATIVE},
        {"UNARY_NOT", Opcodes::UNARY_NOT},
        {"UNARY_INVERT", Opcodes::UNARY_INVERT},
        {"BINARY_MATRIX_MULTIPLY", Opcodes::BINARY_MATRIX_MULTIPLY},
        {"INPLACE_MATRIX_MULTIPLY", Opcodes::INPLACE_MATRIX_MULTIPLY},
        {"BINARY_POWER", Opcodes::BINARY_POWER},
        {"BINARY_MULTIPLY", Opcodes::BINARY_MULTIPLY},
        {"BINARY_MODULO", Opcodes::BINARY_MODULO},
        {"BINARY_ADD", Opcodes::BINARY_ADD},
        {"BINARY_SUBTRACT", Opcodes::BINARY_SUBTRACT},
        {"BINARY_SUBSCR", Opcodes::BINARY_SUBSCR},
        {"BINARY_FLOOR_DIVIDE", Opcodes::BINARY_FLOOR_DIVIDE},
        {"BINARY_TRUE_DIVIDE", Opcodes::BINARY_TRUE_DIVIDE},
        {"INPLACE_FLOOR_DIVIDE", Opcodes::INPLACE_FLOOR_DIVIDE},
        {"INPLACE_TRUE_DIVIDE", Opcodes::INPLACE_TRUE_DIVIDE},
        {"GET_LEN", Opcodes::GET_LEN},
        {"MATCH_MAPPING", Opcodes::MATCH_MAPPING},
        {"MATCH_SEQUENCE", Opcodes::MATCH_SEQUENCE},
        {"MATCH_KEYS", Opcodes::MATCH_KEYS},
        {"COPY_DICT_WITHOUT_KEYS", Opcodes::COPY_DICT_WITHOUT_KEYS},
        {"WITH_EXCEPT_START", Opcodes::WITH_EXCEPT_START},
        {"GET_AITER", Opcodes::GET_AITER},
        {"GET_ANEXT", Opcodes::GET_ANEXT},
        {"BEFORE_ASYNC_WITH", Opcodes::BEFORE_ASYNC_WITH},
        {"END_ASYNC_FOR", Opcodes::END_ASYNC_FOR},
        {"INPLACE_ADD", Opcodes::INPLACE_ADD},
        {"INPLACE_SUBTRACT", Opcodes::INPLACE_SUBTRACT},
        {"INPLACE_MULTIPLY", Opcodes::INPLACE_MULTIPLY},
        {"INPLACE_MODULO", Opcodes::INPLACE_MODULO},
        {"STORE_SUBSCR", Opcodes::STORE_SUBSCR},
        {"DELETE_SUBSCR", Opcodes::DELETE_SUBSCR},
        {"BINARY_LSHIFT", Opcodes::BINARY_LSHIFT},
        {"BINARY_RSHIFT", Opcodes::BINARY_RSHIFT},
        {"BINARY_AND", Opcodes::BINARY_AND},
        {"BINARY_XOR", Opcodes::BINARY_XOR},
        {"BINARY_OR", Opcodes::BINARY_OR},
        {"INPLACE_POWER", Opcodes::INPLACE_POWER},
        {"GET_ITER", Opcodes::GET_ITER},
        {"GET_YIELD_FROM_ITER", Opcodes::GET_YIELD_FROM_ITER},
        {"PRINT_EXPR", Opcodes::PRINT_EXPR},
        {"LOAD_BUILD_CLASS", Opcodes::LOAD_BUILD_CLASS},
        {"YIELD_FROM", Opcodes::YIELD_FROM},
        {"GET_AWAITABLE", Opcodes::GET_AWAITABLE},
        {"LOAD_ASSERTION_ERROR", Opcodes::LOAD_ASSERTION_ERROR},
        {"INPLACE_LSHIFT", Opcodes::INPLACE_LSHIFT},
        {"INPLACE_RSHIFT", Opcodes::INPLACE_RSHIFT},
        {"INPLACE_AND", Opcodes::INPLACE_AND},
        {"INPLACE_XOR", Opcodes::INPLACE_XOR},
        {"INPLACE_OR", Opcodes::INPLACE_OR},
        {"LIST_TO_TUPLE", Opcodes::LIST_TO_TUPLE},
        {"RETURN_VALUE", Opcodes::RETURN_VALUE},
        {"IMPORT_STAR", Opcodes::IMPORT_STAR},
        {"SETUP_ANNOTATIONS", Opcodes::SETUP_ANNOTATIONS},
        {"YIELD_VALUE", Opcodes::YIELD_VALUE},
        {"POP_BLOCK", Opcodes::POP_BLOCK},
        {"POP_EXCEPT", Opcodes::POP_EXCEPT},
        {"HAVE_ARGUMENT", Opcodes::HAVE_ARGUMENT},
        {"STORE_NAME", Opcodes::STORE_NAME},
        {"DELETE_NAME", Opcodes::DELETE_NAME},
        {"UNPACK_SEQUENCE", Opcodes::UNPACK_SEQUENCE},
        {"FOR_ITER", Opcodes::FOR_ITER},
        {"UNPACK_EX", Opcodes::UNPACK_EX},
        {"STORE_ATTR", Opcodes::STORE_ATTR},
        {"DELETE_ATTR", Opcodes::DELETE_ATTR},
        {"STORE_GLOBAL", Opcodes::STORE_GLOBAL},
        {"DELETE_GLOBAL", Opcodes::DELETE_GLOBAL},
        {"ROT_N", Opcodes::ROT_N},
        {"LOAD_CONST", Opcodes::LOAD_CONST},
        {"LOAD_NAME", Opcodes::LOAD_NAME},
        {"BUILD_TUPLE", Opcodes::BUILD_TUPLE},
        {"BUILD_LIST", Opcodes::BUILD_LIST},
        {"BUILD_SET", Opcodes::BUILD_SET},
        {"BUILD_MAP", Opcodes::BUILD_MAP},
        {"LOAD_ATTR", Opcodes::LOAD_ATTR},
        {"COMPARE_OP", Opcodes::COMPARE_OP},
        {"IMPORT_NAME", Opcodes::IMPORT_NAME},
        {"IMPORT_FROM", Opcodes::IMPORT_FROM},
        {"JUMP_FORWARD", Opcodes::JUMP_FORWARD},
        {"JUMP_IF_FALSE_OR_POP", Opcodes::JUMP_IF_FALSE_OR_POP},
        {"JUMP_IF_TRUE_OR_POP", Opcodes::JUMP_IF_TRUE_OR_POP},
        {"JUMP_ABSOLUTE", Opcodes::JUMP_ABSOLUTE},
        {"POP_JUMP_IF_FALSE", Opcodes::POP_JUMP_IF_FALSE},
        {"POP_JUMP_IF_TRUE", Opcodes::POP_JUMP_IF_TRUE},
        {"LOAD_GLOBAL", Opcodes::LOAD_GLOBAL},
        {"IS_OP", Opcodes::IS_OP},
        {"CONTAINS_OP", Opcodes::CONTAINS_OP},
        {"RERAISE", Opcodes::RERAISE},
        {"JUMP_IF_NOT_EXC_MATCH", Opcodes::JUMP_IF_NOT_EXC_MATCH},
        {"SETUP_FINALLY", Opcodes::SETUP_FINALLY},
        {"LOAD_FAST", Opcodes::LOAD_FAST},
        {"STORE_FAST", Opcodes::STORE_FAST},
        {"DELETE_FAST", Opcodes::DELETE_FAST},
        {"GEN_START", Opcodes::GEN_START},
        {"RAISE_VARARGS", Opcodes::RAISE_VARARGS},
        {"CALL_FUNCTION", Opcodes::CALL_FUNCTION},
        {"MAKE_FUNCTION", Opcodes::MAKE_FUNCTION},
        {"BUILD_SLICE", Opcodes::BUILD_SLICE},
        {"LOAD_CLOSURE", Opcodes::LOAD_CLOSURE},
        {"LOAD_DEREF", Opcodes::LOAD_DEREF},
        {"STORE_DEREF", Opcodes::STORE_DEREF},
        {"DELETE_DEREF", Opcodes::DELETE_DEREF},
        {"CALL_FUNCTION_KW", Opcodes::CALL_FUNCTION_KW},
        {"CALL_FUNCTION_EX", Opcodes::CALL_FUNCTION_EX},
        {"SETUP_WITH", Opcodes::SETUP_WITH},
        {"EXTENDED_ARG", Opcodes::EXTENDED_ARG},
        {"LIST_APPEND", Opcodes::LIST_APPEND},
        {"SET_ADD", Opcodes::SET_ADD},
        {"MAP_ADD", Opcodes::MAP_ADD},
        {"LOAD_CLASSDEREF", Opcodes::LOAD_CLASSDEREF},
        {"MATCH_CLASS", Opcodes::MATCH_CLASS},
        {"SETUP_ASYNC_WITH", Opcodes::SETUP_ASYNC_WITH},
        {"FORMAT_VALUE", Opcodes::FORMAT_VALUE},
        {"BUILD_CONST_KEY_MAP", Opcodes::BUILD_CONST_KEY_MAP},
        {"BUILD_STRING", Opcodes::BUILD_STRING},
        {"LOAD_METHOD", Opcodes::LOAD_METHOD},
        {"CALL_METHOD", Opcodes::CALL_METHOD},
        {"LIST_EXTEND", Opcodes::LIST_EXTEND},
        {"SET_UPDATE", Opcodes::SET_UPDATE},
        {"DICT_MERGE", Opcodes::DICT_MERGE},
        {"DICT_UPDATE", Opcodes::DICT_UPDATE}};

    return toOpcodeMap;
  }

  static const auto &getOpcodeToStrMap() {
    static std::unordered_map<Opcodes, std::string_view> toStrMap{
        {Opcodes::POP_TOP, "POP_TOP"},
        {Opcodes::ROT_TWO, "ROT_TWO"},
        {Opcodes::ROT_THREE, "ROT_THREE"},
        {Opcodes::DUP_TOP, "DUP_TOP"},
        {Opcodes::DUP_TOP_TWO, "DUP_TOP_TWO"},
        {Opcodes::ROT_FOUR, "ROT_FOUR"},
        {Opcodes::NOP, "NOP"},
        {Opcodes::UNARY_POSITIVE, "UNARY_POSITIVE"},
        {Opcodes::UNARY_NEGATIVE, "UNARY_NEGATIVE"},
        {Opcodes::UNARY_NOT, "UNARY_NOT"},
        {Opcodes::UNARY_INVERT, "UNARY_INVERT"},
        {Opcodes::BINARY_MATRIX_MULTIPLY, "BINARY_MATRIX_MULTIPLY"},
        {Opcodes::INPLACE_MATRIX_MULTIPLY, "INPLACE_MATRIX_MULTIPLY"},
        {Opcodes::BINARY_POWER, "BINARY_POWER"},
        {Opcodes::BINARY_MULTIPLY, "BINARY_MULTIPLY"},
        {Opcodes::BINARY_MODULO, "BINARY_MODULO"},
        {Opcodes::BINARY_ADD, "BINARY_ADD"},
        {Opcodes::BINARY_SUBTRACT, "BINARY_SUBTRACT"},
        {Opcodes::BINARY_SUBSCR, "BINARY_SUBSCR"},
        {Opcodes::BINARY_FLOOR_DIVIDE, "BINARY_FLOOR_DIVIDE"},
        {Opcodes::BINARY_TRUE_DIVIDE, "BINARY_TRUE_DIVIDE"},
        {Opcodes::INPLACE_FLOOR_DIVIDE, "INPLACE_FLOOR_DIVIDE"},
        {Opcodes::INPLACE_TRUE_DIVIDE, "INPLACE_TRUE_DIVIDE"},
        {Opcodes::GET_LEN, "GET_LEN"},
        {Opcodes::MATCH_MAPPING, "MATCH_MAPPING"},
        {Opcodes::MATCH_SEQUENCE, "MATCH_SEQUENCE"},
        {Opcodes::MATCH_KEYS, "MATCH_KEYS"},
        {Opcodes::COPY_DICT_WITHOUT_KEYS, "COPY_DICT_WITHOUT_KEYS"},
        {Opcodes::WITH_EXCEPT_START, "WITH_EXCEPT_START"},
        {Opcodes::GET_AITER, "GET_AITER"},
        {Opcodes::GET_ANEXT, "GET_ANEXT"},
        {Opcodes::BEFORE_ASYNC_WITH, "BEFORE_ASYNC_WITH"},
        {Opcodes::END_ASYNC_FOR, "END_ASYNC_FOR"},
        {Opcodes::INPLACE_ADD, "INPLACE_ADD"},
        {Opcodes::INPLACE_SUBTRACT, "INPLACE_SUBTRACT"},
        {Opcodes::INPLACE_MULTIPLY, "INPLACE_MULTIPLY"},
        {Opcodes::INPLACE_MODULO, "INPLACE_MODULO"},
        {Opcodes::STORE_SUBSCR, "STORE_SUBSCR"},
        {Opcodes::DELETE_SUBSCR, "DELETE_SUBSCR"},
        {Opcodes::BINARY_LSHIFT, "BINARY_LSHIFT"},
        {Opcodes::BINARY_RSHIFT, "BINARY_RSHIFT"},
        {Opcodes::BINARY_AND, "BINARY_AND"},
        {Opcodes::BINARY_XOR, "BINARY_XOR"},
        {Opcodes::BINARY_OR, "BINARY_OR"},
        {Opcodes::INPLACE_POWER, "INPLACE_POWER"},
        {Opcodes::GET_ITER, "GET_ITER"},
        {Opcodes::GET_YIELD_FROM_ITER, "GET_YIELD_FROM_ITER"},
        {Opcodes::PRINT_EXPR, "PRINT_EXPR"},
        {Opcodes::LOAD_BUILD_CLASS, "LOAD_BUILD_CLASS"},
        {Opcodes::YIELD_FROM, "YIELD_FROM"},
        {Opcodes::GET_AWAITABLE, "GET_AWAITABLE"},
        {Opcodes::LOAD_ASSERTION_ERROR, "LOAD_ASSERTION_ERROR"},
        {Opcodes::INPLACE_LSHIFT, "INPLACE_LSHIFT"},
        {Opcodes::INPLACE_RSHIFT, "INPLACE_RSHIFT"},
        {Opcodes::INPLACE_AND, "INPLACE_AND"},
        {Opcodes::INPLACE_XOR, "INPLACE_XOR"},
        {Opcodes::INPLACE_OR, "INPLACE_OR"},
        {Opcodes::LIST_TO_TUPLE, "LIST_TO_TUPLE"},
        {Opcodes::RETURN_VALUE, "RETURN_VALUE"},
        {Opcodes::IMPORT_STAR, "IMPORT_STAR"},
        {Opcodes::SETUP_ANNOTATIONS, "SETUP_ANNOTATIONS"},
        {Opcodes::YIELD_VALUE, "YIELD_VALUE"},
        {Opcodes::POP_BLOCK, "POP_BLOCK"},
        {Opcodes::POP_EXCEPT, "POP_EXCEPT"},
        {Opcodes::HAVE_ARGUMENT, "HAVE_ARGUMENT"},
        {Opcodes::STORE_NAME, "STORE_NAME"},
        {Opcodes::DELETE_NAME, "DELETE_NAME"},
        {Opcodes::UNPACK_SEQUENCE, "UNPACK_SEQUENCE"},
        {Opcodes::FOR_ITER, "FOR_ITER"},
        {Opcodes::UNPACK_EX, "UNPACK_EX"},
        {Opcodes::STORE_ATTR, "STORE_ATTR"},
        {Opcodes::DELETE_ATTR, "DELETE_ATTR"},
        {Opcodes::STORE_GLOBAL, "STORE_GLOBAL"},
        {Opcodes::DELETE_GLOBAL, "DELETE_GLOBAL"},
        {Opcodes::ROT_N, "ROT_N"},
        {Opcodes::LOAD_CONST, "LOAD_CONST"},
        {Opcodes::LOAD_NAME, "LOAD_NAME"},
        {Opcodes::BUILD_TUPLE, "BUILD_TUPLE"},
        {Opcodes::BUILD_LIST, "BUILD_LIST"},
        {Opcodes::BUILD_SET, "BUILD_SET"},
        {Opcodes::BUILD_MAP, "BUILD_MAP"},
        {Opcodes::LOAD_ATTR, "LOAD_ATTR"},
        {Opcodes::COMPARE_OP, "COMPARE_OP"},
        {Opcodes::IMPORT_NAME, "IMPORT_NAME"},
        {Opcodes::IMPORT_FROM, "IMPORT_FROM"},
        {Opcodes::JUMP_FORWARD, "JUMP_FORWARD"},
        {Opcodes::JUMP_IF_FALSE_OR_POP, "JUMP_IF_FALSE_OR_POP"},
        {Opcodes::JUMP_IF_TRUE_OR_POP, "JUMP_IF_TRUE_OR_POP"},
        {Opcodes::JUMP_ABSOLUTE, "JUMP_ABSOLUTE"},
        {Opcodes::POP_JUMP_IF_FALSE, "POP_JUMP_IF_FALSE"},
        {Opcodes::POP_JUMP_IF_TRUE, "POP_JUMP_IF_TRUE"},
        {Opcodes::LOAD_GLOBAL, "LOAD_GLOBAL"},
        {Opcodes::IS_OP, "IS_OP"},
        {Opcodes::CONTAINS_OP, "CONTAINS_OP"},
        {Opcodes::RERAISE, "RERAISE"},
        {Opcodes::JUMP_IF_NOT_EXC_MATCH, "JUMP_IF_NOT_EXC_MATCH"},
        {Opcodes::SETUP_FINALLY, "SETUP_FINALLY"},
        {Opcodes::LOAD_FAST, "LOAD_FAST"},
        {Opcodes::STORE_FAST, "STORE_FAST"},
        {Opcodes::DELETE_FAST, "DELETE_FAST"},
        {Opcodes::GEN_START, "GEN_START"},
        {Opcodes::RAISE_VARARGS, "RAISE_VARARGS"},
        {Opcodes::CALL_FUNCTION, "CALL_FUNCTION"},
        {Opcodes::MAKE_FUNCTION, "MAKE_FUNCTION"},
        {Opcodes::BUILD_SLICE, "BUILD_SLICE"},
        {Opcodes::LOAD_CLOSURE, "LOAD_CLOSURE"},
        {Opcodes::LOAD_DEREF, "LOAD_DEREF"},
        {Opcodes::STORE_DEREF, "STORE_DEREF"},
        {Opcodes::DELETE_DEREF, "DELETE_DEREF"},
        {Opcodes::CALL_FUNCTION_KW, "CALL_FUNCTION_KW"},
        {Opcodes::CALL_FUNCTION_EX, "CALL_FUNCTION_EX"},
        {Opcodes::SETUP_WITH, "SETUP_WITH"},
        {Opcodes::EXTENDED_ARG, "EXTENDED_ARG"},
        {Opcodes::LIST_APPEND, "LIST_APPEND"},
        {Opcodes::SET_ADD, "SET_ADD"},
        {Opcodes::MAP_ADD, "MAP_ADD"},
        {Opcodes::LOAD_CLASSDEREF, "LOAD_CLASSDEREF"},
        {Opcodes::MATCH_CLASS, "MATCH_CLASS"},
        {Opcodes::SETUP_ASYNC_WITH, "SETUP_ASYNC_WITH"},
        {Opcodes::FORMAT_VALUE, "FORMAT_VALUE"},
        {Opcodes::BUILD_CONST_KEY_MAP, "BUILD_CONST_KEY_MAP"},
        {Opcodes::BUILD_STRING, "BUILD_STRING"},
        {Opcodes::LOAD_METHOD, "LOAD_METHOD"},
        {Opcodes::CALL_METHOD, "CALL_METHOD"},
        {Opcodes::LIST_EXTEND, "LIST_EXTEND"},
        {Opcodes::SET_UPDATE, "SET_UPDATE"},
        {Opcodes::DICT_MERGE, "DICT_MERGE"},
        {Opcodes::DICT_UPDATE, "DICT_UPDATE"}};
    return toStrMap;
  }

  template <typename Map, typename Key>
  static auto getOptFromMap(const Map &map, const Key &key)
      -> std::optional<typename Map::mapped_type> {
    if (auto found = map.find(key); found != map.end())
      return found->second;
    return std::nullopt;
  }

public:
  OpcodeConv() = delete;

  template <StringLike T>
  static std::optional<Opcodes> fromName(const T &name) {
    auto toOpcodeMap = getStrToOpcodeMap();
    return getOptFromMap(toOpcodeMap, name);
  }

  static std::optional<std::string_view> toName(Opcodes opcode) {
    auto toStrMap = getOpcodeToStrMap();
    return getOptFromMap(toStrMap, opcode);
  }
};

} // namespace leech

#endif /* __INCLUDE_COMMON_OPCODES_HH__ */
