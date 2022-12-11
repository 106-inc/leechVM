#ifndef __INCLUDE_COMMON_COMMON_HH__
#define __INCLUDE_COMMON_COMMON_HH__

#include <iostream>

namespace leech {

enum class ValueType : std::uint8_t { Integer, Float };

struct ISerializable {
  virtual std::size_t serialize(std::ostream &ost) const = 0;
  virtual std::size_t serializedSize() const = 0;
  virtual ~ISerializable() = default;
};

} // namespace leech

#endif /* __INCLUDE_COMMON_COMMON_HH__ */
