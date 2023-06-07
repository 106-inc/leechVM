#include "gc/gc.hh"
#include "test_header.hh"
#include <stdexcept>
#include <vector>

using namespace leech;

TEST(MemManager, DoubleMMap) {
  gc::MemoryManager mman;

  EXPECT_THROW(gc::MemoryManager(), std::logic_error);
}

TEST(Allocator, Vector) {
  gc::MemoryManager mman;
  std::vector<int,
              decltype(gc::MemoryManager::StackRegion::getAllocator<int>())>
      vec(20);

  
}

#include "test_footer.hh"
