#include <fstream>
#include <iostream>

#include "leechfile/leechfile.hh"

using namespace leech;

int main() {
  FuncMeta fm{};
  fm.addr = 0xACAB;
  fm.names = {"hello", "world"};

  LeechFile cf{};
  cf.meta_.funcs.push_back(std::move(fm));

  std::ofstream f{};
  f.open("out.bin", std::ios::binary | std::ios::out);
  cf.serialize(f);

  return 0;
}
