#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace wcvm {

  class dynamic_library {
  public:
    explicit dynamic_library(const std::string &libraryPath) {
  #ifdef _WIN32
      handle = LoadLibraryA(libraryPath.c_str());
      if (!handle) {
        throw std::runtime_error("Failed to load library: " + libraryPath);
      }
  #else
      handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
      if (!handle) {
        throw std::runtime_error("Failed to load library: " +
                                std::string(dlerror()));
      }
  #endif
    }

    ~dynamic_library() {
      if (handle) {
  #ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
  #else
        dlclose(handle);
  #endif
      }
    }

    template <typename T> T get_function(const std::string &functionName) {
  #ifdef _WIN32
      FARPROC func =
          GetProcAddress(static_cast<HMODULE>(handle), functionName.c_str());
      if (!func) {
        throw std::runtime_error("Failed to get function: " + functionName);
      }
  #else
      void *func = dlsym(handle, functionName.c_str());
      char *error;
      if ((error = dlerror()) != nullptr) {
        throw std::runtime_error("Failed to get function: " + functionName + " - " + error);
      }
  #endif
      return reinterpret_cast<T>(func);
    }

  private:
    void *handle = nullptr;
  };

  std::function<void()> load_external_function(const std::string &libraryPath,
                                              const std::string &functionName) {
    dynamic_library lib(libraryPath);
    auto rawFunction = lib.get_function<void (*)()>(functionName);

    // Wrap the raw function pointer into a std::function<void()>
    return [rawFunction]() { rawFunction(); };
  }


  std::string get_lib_name(const std::string &name) {
  #ifdef _WIN32
    return name + ".dll";
  #elif defined(__linux__)
    return name + ".so";
  #else
    return name + ".dylib";
  #endif
  }
} // namespace wcvm