#ifndef __INCLUDE_LEECHFILE_LEECHFILE_HH__
#define __INCLUDE_LEECHFILE_LEECHFILE_HH__

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "common/common.hh"
#include "leechobj/leechobj.hh"

namespace leech {

using Byte = std::uint8_t;

struct FuncMeta final : public ISerializable {
  std::vector<std::unique_ptr<LeechObj>> cstPool;
  std::vector<std::string> names;
  std::uint64_t addr;

  void serialize(std::ostream &ost) const override;
  std::size_t serializedSize() const override;
};

struct Meta final : public ISerializable {
  std::vector<FuncMeta> funcs;

  void serialize(std::ostream &ost) const override;
  std::size_t serializedSize() const override;
};

struct LeechFile final : public ISerializable {
  Meta meta_;
  std::vector<Byte> code_;

  void serialize(std::ostream &ost) const override;
  std::size_t serializedSize() const override;
};

} // namespace leech

#endif // __INCLUDE_LEECHFILE_LEECHFILE_HH__
