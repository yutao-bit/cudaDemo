#include "cuda.h"
#include "stdio.h"

__device__ float get_element(Matrix* A, int row, int col){
    return A->elements[row * A->width + col];
}
__device__ void set_element(Matrix* C, int row, int col, float value){
    C->elements[row * C->width + col] = value;
}

__global__ void vector_add(Matrix* C, Matrix* A, Matrix* B){
    int indexCol = threadIdx.x + blockIdx.x * blockDim.x;
    int indexRow = threadIdx.y + blockIdx.y * blockDim.y;
    if(indexCol >= C->width || indexRow >= C->height) {
        //printf("%d %d \n", indexCol, indexRow);
        return;
    }

	float cValue = 0.0;
    for(int i = 0; i < A->width; i++){
        cValue += get_element(A, indexRow, i) * get_element(B, i, indexCol);
    }
    set_element(C, indexRow, indexCol, cValue);
}

void vector_add_wrapper(Matrix* C, Matrix* A, Matrix* B){
    if(A->width != B->height || A->height != C->height || B->width != C->width) return ;
    //以输出的矩阵C的宽高元素数量创建线程
    dim3 blockSize(32, 32);
    dim3 girdSize((C->width + blockSize.x - 1) / 32, (C->height + blockSize.y - 1) / 32);
    vector_add<<<girdSize,blockSize>>>(C, A, B);
}