#include <spdlog/spdlog.h>

#include "frontend/frontend.hh"

int main(int argc, char **argv) try {
  yy::Driver driver(std::cin, std::cout);
} catch (const std::exception &e) {
  spdlog::error(e.what());
  return 1;
}
