#include <string>
#include "spmv.h"
#include "spmv_registry.h"

SpmvMethodRegistry& SpmvMethodRegistry::instance() {
  static SpmvMethodRegistry instance;
  return instance;
}

void SpmvMethodRegistry::add(SpmvMethodCreator * creator, std::string name) {
  registry[name] = creator;
}

SpmvMethod* SpmvMethodRegistry::getMethod(std::string name) {
  SpmvMethodCreator* creator;
  try {
    creator = registry.at(name); /* throws out_of_range if plugin unknown */
  } catch (...) {
    std::cerr << "Method \"" << name << "\" is not registered. All available methods are:" << std::endl;
    for (auto it = registry.begin(); it != registry.end(); ++it ){
      std::cerr << it->first << "  ";
    }
    exit(1);
  }

  return creator->getMethod();
}