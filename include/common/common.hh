#ifndef __INCLUDE_COMMON_COMMON_HH__
#define __INCLUDE_COMMON_COMMON_HH__

#include <iostream>
#include <type_traits>

namespace leech {

enum class ValueType : std::uint8_t { Unknown, Integer, Float, String, Tuple };

using Integer = std::int64_t;
using Float = double;

template <typename T>
concept NumberLeech = std::is_same_v<T, Integer> || std::is_same_v<T, Float>;

template <typename T>
concept Number = NumberLeech<T> || std::is_integral_v<T>;

template <NumberLeech T> inline consteval ValueType typeToValueType() {
  if constexpr (std::is_same_v<T, Integer>)
    return ValueType::Integer;
  return ValueType::Float;
}

template <Number T> void serializeNum(std::ostream &ost, T val) {
  ost.write(reinterpret_cast<char *>(&val), sizeof(val));
}

struct ISerializable {
  virtual void serialize(std::ostream &ost) const = 0;
  virtual std::size_t serializedSize() const = 0;
  virtual ~ISerializable() = default;
};

} // namespace leech

#endif /* __INCLUDE_COMMON_COMMON_HH__ */
