#include "leechfile/leechfile.hh"

namespace leech {

/**
 * FuncMeta definitions
 */

void FuncMeta::serialize(std::ostream &ost) const {
  /* Write function address */
  serializeNum<std::uint64_t>(ost, addr);

  /* Write constant pool */
  auto cstNum = cstPool.size();
  serializeNum<std::uint64_t>(ost, cstNum);
  for (const auto &cst : cstPool)
    cst->serialize(ost);

  /* Write names */
  auto nameNum = names.size();
  serializeNum<std::uint64_t>(ost, nameNum);
  for (const auto &name : names) {
    auto strlen = name.size();
    serializeNum(ost, strlen);
    if (strlen > 0)
      ost.write(name.data(), strlen * sizeof(char));
  }
}

/**
 * Meta definitions
 */

void Meta::serialize(std::ostream &ost) const {
  /* Write function number */
  auto funcNum = funcs.size();
  serializeNum<std::uint64_t>(ost, funcNum);

  /* Write functions meta */
  for (const auto &func : funcs)
    func.serialize(ost);
}

/**
 * LeechFile definitions
 */

void LeechFile::serialize(std::ostream &ost) const {
  /* Write magic */
  auto magic = reinterpret_cast<const std::uint64_t *>("theLEECH");
  serializeNum<uint64_t>(ost, *magic);

  /* Write meta */
  meta_.serialize(ost);

  /* Write code */
  serializeNum<uint64_t>(ost, code_.size());
  for (const auto &inst : code_)
    inst.serialize(ost);
}

} // namespace leech
