#include <string>
#include <iostream>
#include "plain_csr.h"
#include "spmv_registry.h"
#ifdef OPENMP_EXISTS
#include "omp.h"
#endif

const std::string PlainCsr::name = "pcsr";

void PlainCsr::init(std::unique_ptr<MATRIX>& matrix, unsigned int threads) {
  PlainCsr::matrix = matrix->toCSR();
#ifdef OPENMP_EXISTS
  omp_set_num_threads(threads);
#endif
}

void PlainCsr::compute(VECTOR_ELEMENT *input_vector, VECTOR_ELEMENT *output_vector, unsigned int size) {
#ifdef OPENMP_EXISTS
#pragma omp parallel for
#endif
  for (int i = 0; i < matrix->N; i++) {
    double ww = 0.0;
    for (int k = matrix->rowPtr[i]; k < matrix->rowPtr[i + 1]; k++) {
      ww += matrix->values[k] * input_vector[matrix->colIndices[k]];
    }
    output_vector[i] += ww;
  }
}

REGISTER_METHOD(PlainCsr)