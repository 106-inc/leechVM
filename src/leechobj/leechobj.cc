#include "leechobj/leechobj.hh"

namespace leech {
bool LeechObj::compare(LeechObj *obj, CmpOp) const {
  std::ostringstream ss;
  ss << "Comparing of " << toUnderlying(type_) << " and "
     << toUnderlying(obj->type_) << " is not supported yet.";
  throw std::invalid_argument(ss.str());
}

} // namespace leech
