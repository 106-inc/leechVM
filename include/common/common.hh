#ifndef __INCLUDE_COMMON_COMMON_HH__
#define __INCLUDE_COMMON_COMMON_HH__

namespace leech
{

template <Number T> void serializeNum(std::ostream &ost, T val) {
  ost.write(reinterpret_cast<char *>(&val), sizeof(val));
}

class ISerializable {
  virtual std::size_t serialize(std::ostream &ost) const = 0;
  virtual std::size_t serializedSize() const = 0;
  virtual ~ISerializable() = default;
};

} // namespace leech


#endif // __INCLUDE_COMMON_COMMON_HH__
