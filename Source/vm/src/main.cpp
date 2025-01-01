#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "syscalls.hpp"
#include "disk.hpp"
#include "core.hpp"
#include "cfg.hpp"
#include "io.hpp"
#include "vm.hpp"

wcvm::cfg get_config(const std::vector<std::string> &args) {
  wcvm::cfg cfg = {std::filesystem::absolute("./"), MEMORY_STD, THREAD_STD};

  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i] == "-e") {
      cfg.env = std::filesystem::absolute(args[++i]);

    } else if (args[i] == "-m") {

      size_t m = std::stoull(args[++i]);
      if (m >= MEMORY_MAX) {
        std::cout << "Max memory: " << MEMORY_MAX << std::endl;
        cfg.size_memory = MEMORY_MAX;
      } else cfg.size_memory = m;

    } else if (args[i] == "-t") {

      size_t m = std::stoull(args[++i]);
      if (m >= THREAD_MAX) {
        std::cout << "Max threads: " << THREAD_MAX << std::endl;
        cfg.thread_count = THREAD_MAX;
      } else cfg.thread_count = m;

    } else {
      std::cerr << "Unknown command-line: " << args[i] << std::endl;
    }
  }

  return cfg;
}

int main(int argc, const char** argv) {
  std::vector<std::string> args;

  for (int i = 1; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  wcvm::cfg cfg = get_config(args);

  wcvm::vm vm(cfg);
  vm.init();

  return 0;
}