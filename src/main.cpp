#include <iostream>
#include "spmv_registry.h"
#include "parse_options.h"
#include "mmmatrix.hpp"


long long int deltaMicroseconds(
    std::chrono::steady_clock::time_point &t2,
    std::chrono::steady_clock::time_point &t1) {
  return std::chrono::duration_cast<std::chrono::microseconds>(t2 -t1).count();
}

int main(int argc, const char *argv[]) {

  auto cliOptions = parseCliOptions(argc, argv);
  
  SpmvMethodRegistry& registry = SpmvMethodRegistry::instance();
  auto method = registry.getMethod(cliOptions->method);

  auto readStart = std::chrono::high_resolution_clock::now();
  auto matrix = MATRIX::fromFile(cliOptions->mtxFile);

  auto initStart = std::chrono::high_resolution_clock::now();
  method->init(matrix, cliOptions->threads);


  //
  double *in = new double[matrix->N+1];
  double *out = new double[matrix->N+1];
  auto computeStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i <cliOptions->iters; ++i) {
    method->compute(in, out,0);
  }
  auto computeEnd = std::chrono::high_resolution_clock::now();


  std::cout << std::endl <<
               "=====================  " << std::endl <<
               "Reading Matrix       : " << deltaMicroseconds(initStart, readStart) << " us" << std::endl <<
               "Initializing Matrix  : " << deltaMicroseconds(computeStart, initStart) << " us" << std::endl <<
               "Computed " << cliOptions->iters << " iterations:" <<std::endl <<
               "    Total            : " << deltaMicroseconds(computeEnd, computeStart) << " us" << std::endl <<
               "    Single Iteration : " << deltaMicroseconds(computeEnd, computeStart)/cliOptions->iters << " us" << std::endl;

  return 0;
}