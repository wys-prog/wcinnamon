#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "vm.hpp"

namespace wcvm {
  void vm::init_syscalls() {
    syscalls[0x00] = [this](byte *bytes, word len) {
      
    };

  }

}