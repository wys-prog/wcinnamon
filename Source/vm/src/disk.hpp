#pragma once

#include <string>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <filesystem>

#include "vm.hpp"

namespace wcvm {

  void vm::init_disk() {
    if (!std::filesystem::exists(env)) throw std::runtime_error("No such path: " + env);
    if (!std::filesystem::exists(env + "/boot")) throw std::runtime_error("No such file: " + env + "/boot");

    std::ifstream file(env + "/boot");

    for (int i = 0; i < 512; ++i) {
      file.read((char*)memory[i], sizeof(byte));
    }
  }

}