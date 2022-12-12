#ifndef __INCLUDE_EXECUTOR_EXECUTOR_HH__
#define __INCLUDE_EXECUTOR_EXECUTOR_HH__

#include <functional>
#include <optional>
#include <stack>
#include <string_view>

#include "leechfile/leechfile.hh"

namespace leech {

constexpr std::string_view kMainFuncName = "main";

class StackFrame final {
  const FuncMeta *pmeta_ = nullptr;
  std::stack<pLeechObj> dataStack_{};

public:
  StackFrame(const FuncMeta *pmeta);

  StackFrame(const StackFrame &) = delete;
  StackFrame &operator=(const StackFrame &) = delete;
  StackFrame(StackFrame &&) = default;
  StackFrame &operator=(StackFrame &&) = default;

  template <class T, typename... Args>
  void emplace(Args &&...args) requires std::derived_from<T, LeechObj> {
    dataStack_.emplace(new T(std::forward<Args>(args)...));
  }

  const auto getConst(ArgType idx) const {
    return pmeta_->cstPool.at(idx).get();
  }

  std::string_view getName(ArgType idx) const { return pmeta_->names.at(idx); }

  const auto top() const { return dataStack_.top().get(); }

  void pop() { dataStack_.pop(); }
};

using FuncStack = std::stack<StackFrame>;

struct State final {
  FuncStack funcStack{};
  LeechFile *pFile{};
  std::uint64_t pc{};
  std::optional<std::uint64_t> nextPC{};

  State() = default;
  State(LeechFile *pfile);

  State(const State &) = default;
  State &operator=(const State &) = default;

  const auto &getInst(std::uint64_t idx) const { return pFile->code.at(idx); }
};

using ExecFunc = std::function<void(const Instruction &, State &)>;

class Executor final {
  State state_{};
  static inline std::unordered_map<Opcodes, ExecFunc> execMap_{};

public:
  Executor(LeechFile *leechFile) : state_(leechFile) {}

  void execute();
};

} // namespace leech

#endif // __INCLUDE_EXECUTOR_EXECUTOR_HH__
