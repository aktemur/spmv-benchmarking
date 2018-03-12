#include <iostream>
#include "spmv_registry.h"


int main(int argc, const char *argv[]) {

  SpmvMethodRegistry& registry = SpmvMethodRegistry::instance();

  SpmvMethod* method = registry.getMethod(argv[1]);

  std::cout << "Selected method:" << method->name << std::endl;
  method->init(nullptr);
  method->compute(nullptr, nullptr,0);
  return 0;
}
