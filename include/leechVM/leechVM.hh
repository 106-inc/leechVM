#ifndef __INCLUDE_LEECHVM_LEECHVM_HH__
#define __INCLUDE_LEECHVM_LEECHVM_HH__

#include "executor/executor.hh"
#include "frontend/frontend.hh"

namespace leech {

class LeechVM final {
public:
  LeechVM() = default;
  LeechVM(const LeechVM &) = delete;
  LeechVM(LeechVM &&) = delete;
  LeechVM &operator=(const LeechVM &) = delete;
  LeechVM &operator=(LeechVM &&) = delete;

  void generateLeechFile(std::istream &in, bool isFromBinary);
  void dumpBinary(std::ostream &out);
  void run();

private:
  LeechFile leechFile_;
};

} // namespace leech

#endif // __INCLUDE_LEECHVM_LEECHVM_HH__
