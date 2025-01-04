#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "syscalls.hpp"
#include "disk.hpp"
#include "core.hpp"
#include "cfg.hpp"
#include "vm.hpp"

size_t parse_memory(const std::string &value, size_t multiplier = 1) {
    size_t m = std::stoull(value) * multiplier;
    if (m >= MEMORY_MAX) {
      std::cout << "Max memory: " << MEMORY_MAX << std::endl;
      return MEMORY_MAX;
    }
    return m;
  }

wcvm::cfg get_config(const std::vector<std::string> &args) {
  wcvm::cfg cfg = {std::filesystem::absolute("./"), MEMORY_STD, THREAD_STD};

  for (size_t i = 0; i < args.size(); ++i) {
    try {
      if (args[i] == "-e" && i + 1 < args.size()) {
        cfg.env = std::filesystem::absolute(args[++i]);

      } else if (args[i] == "-m" && i + 1 < args.size()) {
        cfg.size_memory = parse_memory(args[++i]);

      } else if (args[i] == "-mG" && i + 1 < args.size()) {
        cfg.size_memory = parse_memory(args[++i], 1024 * 1024 * 1024);

      } else if (args[i] == "-mK" && i + 1 < args.size()) {
        cfg.size_memory = parse_memory(args[++i], 1024);

      } else if (args[i] == "-mM" && i + 1 < args.size()) {
        cfg.size_memory = parse_memory(args[++i], 1024 * 1024);

      } else if (args[i] == "-t" && i + 1 < args.size()) {
        size_t t = std::stoull(args[++i]);
        if (t >= THREAD_MAX) {
          std::cout << "Max threads: " << THREAD_MAX << std::endl;
          cfg.thread_count = THREAD_MAX;
        } else {
          cfg.thread_count = t;
        }

      } else {
        std::cerr << "Unknown command-line argument: " << args[i] << std::endl;
      }
    } catch (const std::exception &e) {
      std::cerr << "Error parsing argument '" << args[i] << "': " << e.what() << std::endl;
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