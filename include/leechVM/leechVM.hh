#ifndef __INCLUDE_LEECHVM_LEECHVM_HH__
#define __INCLUDE_LEECHVM_LEECHVM_HH__

#include "frontend/frontend.hh"

namespace leech {

class LeechVM final {
public:
  LeechVM(const LeechVM &) = delete;
  LeechVM(LeechVM &&) = delete;
  LeechVM &operator=(const LeechVM &) = delete;
  LeechVM &operator=(LeechVM &&) = delete;

  LeechVM(std::istream &in) : driver_{in, std::cout} {}
  void run();

private:
  yy::Driver driver_;
};

} // namespace leech

#endif // __INCLUDE_LEECHVM_LEECHVM_HH__
