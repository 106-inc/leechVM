#ifndef __INCLUDE_LEECHOBJ_LEECHOBJ_HH__
#define __INCLUDE_LEECHOBJ_LEECHOBJ_HH__

#include <algorithm>
#include <concepts>
#include <memory>
#include <string>
#include <vector>

#include "common/common.hh"
#include "common/opcodes.hh"

namespace leech {

class LeechObj : public ISerializable {
  std::size_t sizeInBytes_{};
  ValueType type_{};

public:
  LeechObj(std::size_t size, ValueType type)
      : sizeInBytes_(size), type_(type) {}

  std::size_t serializedSize() const override final { return sizeInBytes_; }
};

template <NumberLeech T> class NumberObj final : public LeechObj {
  T value_{};

public:
  NumberObj(T value)
      : LeechObj(sizeof(T), typeToValueType<T>()), value_(value) {}

  void serialize(std::ostream &ost) const override {
    ost.write(reinterpret_cast<char *>(&value_), sizeof(value_));
  }
};

class StringObj final : public LeechObj {
  std::string string_;

public:
  StringObj(const std::string &string)
      : LeechObj(string.size(), ValueType::String), string_(string) {}

  void serialize(std::ostream &ost) const override {
    for (auto sym : string_)
      serializeNum(ost, sym);
  }
};

using pLeechObj = std::unique_ptr<LeechObj>;

template <typename T>
concept ConvToLeechPtr = std::convertible_to<T, pLeechObj>;

class TupleObj final : public LeechObj {
  std::vector<pLeechObj> tuple_;

public:
  template <std::forward_iterator It>
  TupleObj(It begin, It end) requires
      ConvToLeechPtr<typename std::iterator_traits<It>::value_type>
      : tuple_(std::distance(begin, end)) {
    std::copy(begin, end, tuple_.begin(), tuple_.end());
  }

  template <ConvToLeechPtr T>
  TupleObj(const std::initializer_list<T> &lst)
      : TupleObj(lst.begin(), lst.end()) {}

  void serialize(std::ostream &ost) const override {
    for (auto &&ptr : tuple_)
      ptr->serialize(ost);
  }
};

} // namespace leech

#endif /* __INCLUDE_LEECHOBJ_LEECHOBJ_HH__ */
