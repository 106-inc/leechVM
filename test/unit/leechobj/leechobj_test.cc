#include <sstream>
#include <string_view>

#include "leechobj/leechobj.hh"
#include "test_header.hh"

using namespace leech;

TEST(Serialize, Int) {
  // Assign
  Integer val = 0xE4;
  NumberObj<Integer> integer(val);
  std::ostringstream ss;
  std::string_view answ("\x1\x8\x0\x0\x0\x0\x0\x0\x0\xE4\x0\x0\x0\x0\x0\x0\x0",
                        1 + sizeof(std::size_t) + sizeof(Integer));
  // Act
  integer.serialize(ss);
  auto str = ss.view();

  // Assert
  EXPECT_EQ(str, answ);
}

#include "test_footer.hh"
