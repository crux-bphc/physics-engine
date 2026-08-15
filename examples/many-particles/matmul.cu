#include <iostream>
#include <string>
#include <cuda_runtime.h>
#include "raylib.h"
#include <cmath>
#include <cstdlib>

__device__ float func(float t, float x){
    return  x * 2 * std::cos(5 * x * t);
}

__global__
void matMulKernel(float* M, float* N, int Width, float* P){ 
    const int TileWidth = 2;
    int row = blockIdx.y * TileWidth + threadIdx.y;
    int column = blockIdx.x * TileWidth + threadIdx.x;
    __shared__ float Mds[TileWidth][TileWidth];
    __shared__ float Nds[TileWidth][TileWidth];
    float Pvalue = 0;
    for (int p = 0; p < Width/TileWidth; p++){
	Mds[threadIdx.y][threadIdx.x] = M[row * Width + p * TileWidth + threadIdx.x];
	Nds[threadIdx.y][threadIdx.x] = N[((p * TileWidth) + threadIdx.y)*Width + column];
	__syncthreads();
	for (int k = 0; k < TileWidth; k++){
	    Pvalue += Mds[threadIdx.y][k] * Nds[k][threadIdx.x];
	}
	__syncthreads();
    }
    P[row * Width + column] = Pvalue;
    

}

void matMul(float* M, float* N, int W, float* P){
    float *d_M, *d_N, *d_P;
    int Width = W;
    
    int size = sizeof(float) * Width * Width;

    cudaMalloc((void**)&d_M, size); 
    cudaMemcpy(d_M, M, size, cudaMemcpyHostToDevice);

    cudaMalloc((void**)&d_N, size); 
    cudaMemcpy(d_N, N, size, cudaMemcpyHostToDevice);

    cudaMalloc((void**)&d_P, size); 
    matMulKernel<<<ceil(Width * Width/256.0),256>>>(d_M, d_N, Width, d_P); //calling the kernel
    cudaMemcpy(P, d_P, Width * Width, cudaMemcpyDeviceToHost);
    
    cudaFree(d_M);
    cudaFree(d_N);
    cudaFree(d_P);
}

int main(){
    float *arrM = new float[16];
    float *arrN = new float[16];
    for (int i = 0; i < 16; i++){ //linearized array bro
	arrM[i] = 2;
	arrN[i] = 2;
    }
    float *arrP = new float[4];
    matMul(arrM, arrN, 4, arrP);
    std::cout << arrP[0];
    return 0;
}
