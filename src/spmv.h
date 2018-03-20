#ifndef SPMV_BENCHMARKING_SPMV_H
#define SPMV_BENCHMARKING_SPMV_H

#include <string>
#include "mmmatrix.hpp"

#define MATRIX_ELEMENT double
#define VECTOR_ELEMENT double
#define MATRIX thundercat::MMMatrix <MATRIX_ELEMENT>

class SpmvMethod {
public:

    const std::string name;

    virtual void init(std::unique_ptr<MATRIX > &matrix, unsigned int threads) = 0;

    virtual void compute(VECTOR_ELEMENT *input_vector, VECTOR_ELEMENT *output_vector) = 0;

};

class StubSpmv : public SpmvMethod {
public:

    static const std::string name;

    virtual void init(std::unique_ptr<MATRIX > &matrix, unsigned int threads);

    virtual void compute(VECTOR_ELEMENT *input_vector, VECTOR_ELEMENT *output_vector);

};


#endif //SPMV_BENCHMARKING_SPMV_H
