#include <iostream>
#include "spmv_registry.h"
#include "parse_options.h"
#include "mmmatrix.hpp"

std::unique_ptr<MATRIX> loadMatrix(const std::string filename);

int main(int argc, const char *argv[]) {

  auto cliOptions = parseCliOptions(argc, argv);

  auto matrix = loadMatrix(cliOptions->mtxFile);


  SpmvMethodRegistry& registry = SpmvMethodRegistry::instance();
  auto method = registry.getMethod(cliOptions->method);

  method->init(matrix);
  method->compute(nullptr, nullptr,0);

  return 0;
}

std::unique_ptr<MATRIX> loadMatrix(const std::string filename) {

  std::unique_ptr<MATRIX> mmMatrix = MATRIX::fromFile(filename);

  if (!mmMatrix->isSquare()) {
    std::cerr << "Only square matrices are accepted."<< std::endl;
    exit(1);
  }

  if (!mmMatrix->hasFullDiagonal()) {
    std::cerr << "Input matrix has to have a full diagonal.\n" << std::endl;
    exit(1);
  }

  return  mmMatrix;

}