#ifndef SPMV_BENCHMARKING_PLAIN_CSR_H
#define SPMV_BENCHMARKING_PLAIN_CSR_H

#include <vector>
#include "spmv.h"

class PlainCsr : public SpmvMethod {
public:

    static const std::string name;

    virtual void init(std::unique_ptr<MATRIX > &matrix, unsigned int threads);

    virtual void compute(VECTOR_ELEMENT *input_vector, VECTOR_ELEMENT *output_vector, unsigned int size);

private:
    std::unique_ptr<thundercat::CSRMatrix<MATRIX_ELEMENT>> matrix;
};

#endif //SPMV_BENCHMARKING_PLAIN_CSR_H
