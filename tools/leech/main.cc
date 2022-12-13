#include <filesystem>
#include <spdlog/spdlog.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

#include "leechVM/leechVM.hh"

namespace fs = std::filesystem;
  
int main(int argc, char **argv) try {
  CLI::App app{"LeechVM"};
  fs::path input{};
  fs::path binaryOutput{};
  bool fromBinary = false;
  app.add_option("input", input, "input file")->required();
  app.add_option("--dump", binaryOutput, "leech -> dinary dump");
  app.add_option("--bin", fromBinary, "execute from binary");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  std::fstream in(input.c_str());
  if (!in.is_open()) {
    throw std::invalid_argument("can't find input file");
  }

  leech::LeechVM vm;
  vm.generateLeechFile(in, fromBinary);
  if (!binaryOutput.empty()) {
    std::ofstream out(binaryOutput.c_str());
    vm.dumpBinary(out);
  } else {
    vm.run();
  }
} catch (const std::exception &e) {
  spdlog::error(e.what());
  return 1;
}
