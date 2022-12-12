#include <fstream>
#include <iostream>

#include "class_file/class_file.hh"

using namespace leech;

int main() {
  FuncMeta fm{};
  fm.addr = 0xACAB;
  fm.names = {"hello", "world"};

  ClassFile cf{};
  cf.meta_.funcs.push_back(std::move(fm));

  std::ofstream f{};
  f.open("out.bin", std::ios::binary | std::ios::out);
  cf.serialize(f);

  return 0;
}
