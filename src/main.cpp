#include <iostream>
#include "spmv_registry.h"
#include "parse_options.h"
#include "mmmatrix.hpp"


long long int deltaMicroseconds(
    std::chrono::steady_clock::time_point &t2,
    std::chrono::steady_clock::time_point &t1) {
  return std::chrono::duration_cast<std::chrono::microseconds>(t2 -t1).count();
}

std::unique_ptr<MATRIX> loadMatrix(const std::string filename);

int main(int argc, const char *argv[]) {

  auto cliOptions = parseCliOptions(argc, argv);
  
  SpmvMethodRegistry& registry = SpmvMethodRegistry::instance();
  auto method = registry.getMethod(cliOptions->method);

  auto readStart = std::chrono::high_resolution_clock::now();
  auto matrix = loadMatrix(cliOptions->mtxFile);

  auto initStart = std::chrono::high_resolution_clock::now();
  method->init(matrix);

  auto computeStart = std::chrono::high_resolution_clock::now();
  method->compute(nullptr, nullptr,0);
  auto computeEnd = std::chrono::high_resolution_clock::now();


  std::cout << "Reading Matrix       : " << deltaMicroseconds(initStart, readStart) << "us" << std::endl <<
               "Initializing Matrix  : " << deltaMicroseconds(computeStart, initStart) << "us" << std::endl <<
               "Computing            : " << deltaMicroseconds(computeEnd, computeStart) << "us" << std::endl ;


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