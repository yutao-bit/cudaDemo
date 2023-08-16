#include <iostream>
#include <cuda_runtime.h>
#include "cuda.h"

#define CHECK(res) { if(res != cudaSuccess){printf("Error ：%s:%d , ", __FILE__,__LINE__);   \
printf("code : %d , reason : %s \n", res,cudaGetErrorString(res));exit(-1);}}

#define WIDTH  1000
#define HEIGHT 2000

//实现矩阵乘法
int main(){
    // int dev = 0;
    // cudaDeviceProp devProp;
    // cudaGetDeviceProperties(&devProp, dev);
    // std::cout << "使用GPU device " << dev << ": " << devProp.name << std::endl;
    // std::cout << "SM的数量：" << devProp.multiProcessorCount << std::endl;
    // std::cout << "每个线程块的共享内存大小 KB：" << devProp.sharedMemPerBlock / 1024.0f << std::endl;
    // std::cout <<"每个线程块的最大线程数：" << devProp.maxThreadsPerBlock << std::endl;
    // std::cout << "每个EM的最大线程数：" << devProp.maxThreadsPerMultiProcessor << std::endl;
    // std::cout << "每个SM的最大线程束数：" << devProp.maxThreadsPerMultiProcessor / 32 << std::endl;
    
    Matrix *A; //2000*1000
    Matrix *B; //1000*2000
    Matrix *C; //2000*2000

    // Allocate memory
    cudaMallocManaged((void**)&A, sizeof(Matrix));
    cudaMallocManaged((void**)&B, sizeof(Matrix));
    cudaMallocManaged((void**)&C, sizeof(Matrix));
    A->width = WIDTH;
    A->height = HEIGHT;
    B->width = HEIGHT;
    B->height = WIDTH;
    C->width = HEIGHT;
    C->height = HEIGHT;
    cudaMallocManaged((void**)&A->elements, A->height * A->width * sizeof(float));
    cudaMallocManaged((void**)&B->elements, B->height * B->width * sizeof(float));
    cudaMallocManaged((void**)&C->elements, C->height * C->width * sizeof(float));

    // Initialize matrix
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        A->elements[i] = 2.0;
        B->elements[i] = 2.0;
    }
    for (int i = 0; i < C->width * C->height; ++i)
    {
        C->elements[i] = 0.0;
    }

    // Main function
    vector_add_wrapper(C, A, B);

    CHECK(cudaDeviceSynchronize());

    printf("%f ", C->elements[0]);
    printf("%f \n", C->elements[C->width + 1]);

    CHECK(cudaGetLastError());

    // Cleanup after kernel execution
    cudaFree(A->elements);
    cudaFree(B->elements);
    cudaFree(C->elements);
    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    return 0;
}