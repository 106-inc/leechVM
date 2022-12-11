#ifndef __INCLUDE_CLASS_FILE_CLASS_FILE_HH__
#define __INCLUDE_CLASS_FILE_CLASS_FILE_HH__

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace leech {

using Byte = std::uint8_t;

enum class ValueType : std::uint8_t { Integer, Float };

class ISerializable {
  virtual std::size_t serialize(std::ostream &ost) const = 0;
  virtual std::size_t serializedSize() const = 0;
};

class Value : ISerializable final {
  ValueType type;
  std::size_t size;
  void *data;

  std::size_t serialize(std::ostream &ost) const override{

  };
};

class FuncMeta : ISerializable final {
  std::vector<Value> constantPool;
  std::vector<std::string> names;
};

class Meta : ISerializable final {
  std::vector<FuncMeta> funcs;

  std::size_t serialize(std::ostream &ost) const override {
    const auto pos = ost.tellp();

    for (const auto &func : funcs) {

      func.serialize(ost);
    }

    return static_cast<std::size_t>(ost.tellp() - pos);
  }
};

class ClassFile : ISerializable final {
private:
  Meta meta_;
  std::vector<Byte> code_;

public:
  std::size_t serialize(std::ostream &ost) const override {
    const auto pos = ost.tellp();

    /* auto metaSize = */ meta_.serialize(ost);

    ost.write(reinterpret_cast<const char *>(code_.data()),
              code_.size() * sizeof(Byte));

    return static_cast<std::size_t>(ost.tellp() - pos);
  }

  static ClassFile deserialize(Byte *data);
};

} // namespace leech

#endif // __INCLUDE_CLASS_FILE_CLASS_FILE_HH__
