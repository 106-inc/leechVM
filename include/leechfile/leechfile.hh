#ifndef __INCLUDE_LEECHFILE_LEECHFILE_HH__
#define __INCLUDE_LEECHFILE_LEECHFILE_HH__

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../common/common.hh"
#include "../leechobj/leechobj.hh"

namespace leech {

using Byte = std::uint8_t;

struct FuncMeta final : public ISerializable {
  std::vector<std::unique_ptr<LeechObj>> cstPool;
  std::vector<std::string> names;
  std::uint64_t addr;

  void serialize(std::ostream &ost) const override {
    /* Write FuncMeta size */
    auto metaSize = serializedSize();
    serializeNum(ost, metaSize);

    /* Write function address */
    serializeNum(ost, addr);

    /* Write constant pool */
    auto cstNum = cstPool.size();
    serializeNum<uint64_t>(ost, cstNum);
    for (const auto &cst : cstPool)
      cst->serialize(ost);

    /* Write names */
    auto nameNum = names.size();
    serializeNum<uint64_t>(ost, nameNum);
    for (const auto &name : names) {
      auto strlen = name.size();
      serializeNum(ost, strlen);
      if (strlen > 0)
        ost.write(name.data(), strlen * sizeof(char));
    }
  }

  std::size_t serializedSize() const override { return 0; }
};

struct Meta final : public ISerializable {
  std::vector<FuncMeta> funcs;

  void serialize(std::ostream &ost) const override {
    /* Write function number */
    auto funcNum = funcs.size();
    serializeNum<uint64_t>(ost, funcNum);

    /* Write functions meta */
    for (const auto &func : funcs)
      func.serialize(ost);
  }

  std::size_t serializedSize() const override { return 0; }
};

struct LeechFile final : public ISerializable {
  // private:
  Meta meta_;
  std::vector<Byte> code_;

public:
  void serialize(std::ostream &ost) const override {
    /* Write magic */
    auto magic = reinterpret_cast<const uint64_t *>("theLEECH");
    serializeNum(ost, *magic);

    /* Write meta */
    meta_.serialize(ost);

    /* Write code */
    if (code_.size() > 0)
      ost.write(reinterpret_cast<const char *>(code_.data()),
                code_.size() * sizeof(Byte));
  }

  std::size_t serializedSize() const override { return 0; }
};

} // namespace leech

#endif // __INCLUDE_LEECHFILE_LEECHFILE_HH__
