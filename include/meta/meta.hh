#ifndef __INCLUDE_META_META_HH__
#define __INCLUDE_META_META_HH__

#include <string>
#include <vector>

namespace leech {

struct Value;

struct FuncMeta final {
  std::vector<Value> constantPool;
  std::vector<std::string> names;
};

struct Meta final {
  std::vector<FuncMeta> funcs;
};

} // namespace leech

#endif // __INCLUDE_META_META_HH__
