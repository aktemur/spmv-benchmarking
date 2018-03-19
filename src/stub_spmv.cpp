#include <string>
#include <iostream>
#include "spmv.h"
#include "spmv_registry.h"

const std::string StubSpmv::name = "stub";

void StubSpmv::init(std::unique_ptr<MATRIX>& matrix, unsigned int threads) {
  std::cout << "Stub implementation initializing with "<< threads << " threads" << std::endl;
}

void StubSpmv::compute(VECTOR_ELEMENT *input_vector, VECTOR_ELEMENT *output_vector, unsigned int size) {
  std::cout << "Stub implementation computing"<< std::endl;
}

REGISTER_METHOD(StubSpmv)