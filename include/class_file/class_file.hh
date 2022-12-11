#ifndef __INCLUDE_CLASS_FILE_CLASS_FILE_HH__
#define __INCLUDE_CLASS_FILE_CLASS_FILE_HH__

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include "../common/common.hh"

namespace leech {

using Byte = std::uint8_t;

class Value final : public ISerializable {
  ValueType type;
  std::size_t size;
  void *data;

  void serialize(std::ostream &ost) const override{

  };
};

class FuncMeta final : public ISerializable {
  std::vector<Value> cstPool;
  std::vector<std::string> names;
  std::uint32_t addr;

  void serialize(std::ostream &ost) const override {
    /* Write FuncMeta size */
    auto metaSize = serializedSize();
    ost.write(reinterpret_cast<const char *>(metaSize), sizeof(metaSize));

    /* Write function address */
    ost.write(reinterpret_cast<const char *>(addr), sizeof(addr));

    /* Write constant pool */
    auto cstNum = cstPool.size();
    ost.write(reinterpret_cast<const char *>(cstNum), sizeof(cstNum));
    for (const auto &cst : cstPool)
      cst.serialize(ost);

    /* Write names */
    auto nameNum = names.size();
    ost.write(reinterpret_cast<const char *>(nameNum), sizeof(nameNum));
    for (const auto &name : names) {
      auto strlen = name.size();
      ost.write(reinterpret_cast<const char *>(strlen), sizeof(strlen));
      if (len > 0)
        ost.write(name.data(), strlen * sizeof(char));
    }
  }
};

class Meta final : public ISerializable {
private:
  std::vector<FuncMeta> funcs;

public:
  void serialize(std::ostream &ost) const override {
    /* Write function number */
    auto funcNum = funcs.size();
    ost.write(reinterpret_cast<const char *>(funcNum), sizeof(funcNum));

    /* Write functions meta */
    for (const auto &func : funcs)
      func.serialize(ost);
  }
};

class ClassFile final : public ISerializable {
private:
  Meta meta_;
  std::vector<Byte> code_;

public:
  void serialize(std::ostream &ost) const override {
    /* Write magic */

    /* Write meta */
    meta_.serialize(ost);

    /* Write code */
    ost.write(reinterpret_cast<const char *>(code_.data()),
              code_.size() * sizeof(Byte));
  }

  static ClassFile deserialize(Byte *data);
};

} // namespace leech

#endif // __INCLUDE_CLASS_FILE_CLASS_FILE_HH__
