#ifndef _CUDA_H_
#define _CUDA_H_

struct Matrix{
    int width;
    int height;
    float* elements;
};

extern "C" void vector_add_wrapper(Matrix* C, Matrix* A, Matrix* B);

#endif//_CUDA_H_