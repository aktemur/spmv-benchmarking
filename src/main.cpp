#include <iostream>
#include "spmv_registry.h"
#include "parse_options.h"


int main(int argc, const char *argv[]) {

  auto cliOptions = parseCliOptions(argc, argv);

  SpmvMethodRegistry& registry = SpmvMethodRegistry::instance();


  auto method = registry.getMethod(cliOptions->method);

  method->init(nullptr);
  method->compute(nullptr, nullptr,0);

  return 0;
}


