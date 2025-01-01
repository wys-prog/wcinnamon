#pragma once

#include <string>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <filesystem>

#include "vm.hpp"

namespace wcvm {

  void vm::init_disk() {
    if (!std::filesystem::exists(config.env)) throw std::runtime_error("No such path: " + config.env);
    if (!std::filesystem::exists(config.env + "boot")) throw std::runtime_error("No such file: " + config.env + "boot");

    std::ifstream file(config.env + "boot");
    std::cout << "Reading " << config.env << "boot..." << std::endl;

    for (int i = 0; i < 512; ++i) {
      char buff[1] = {0};
      file.read(buff, 1);
      memory[i] = buff[0];
      std::cout << std::hex << std::uppercase << (int)memory[i] << ' ';
    }

    std::cout << std::endl;

    file.close();
  }

}