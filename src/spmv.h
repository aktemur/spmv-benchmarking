#ifndef SPMV_BENCHMARKING_SPMV_H
#define SPMV_BENCHMARKING_SPMV_H

#include <string>

#include "mmmatrix.hpp"


#define ELEMENT_TYPE double
#define MATRIX thundercat::MMMatrix <ELEMENT_TYPE>

class SpmvMethod {
public:

    const std::string name ;

    virtual void init(MATRIX *matrix) = 0;

    virtual void compute(double *input_vector, double *output_vector, unsigned int size) = 0;


};

#endif //SPMV_BENCHMARKING_SPMV_H
