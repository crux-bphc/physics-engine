#include <iostream>
#include <string>
#include <cuda_runtime.h>
#include <solvers/rk_solver_cuda.cuh>
#include "raylib.h"
#include <cmath>
#include <cstdlib>

__device__ float func(float t, float x){
    return  100 * std::cos(5 * t);
}


__global__
void rkSolveKernel(float* Pos, float* PosNew, int n, double t){ //creates a separate thread for solving the position of every particle
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i < n) {
	cuda_solvers::rk4::RK4Solver oiler(t, Pos[i], t+0.001, 0.01, func);//0.001 added to time is arbitrary, it should be the delta t instead 
	PosNew[i] =  oiler.solve();
    }
}

void rkSolve(float* ballPos, float* ballPosNext, int n){
    float *d_ballPos, *d_ballPosNext;
    int size = n * sizeof(float);

    cudaMalloc((void**)&d_ballPos, size); 
    cudaMemcpy(d_ballPos, ballPos, n * sizeof(float), cudaMemcpyHostToDevice);

    cudaMalloc((void**)&d_ballPosNext, size);
    rkSolveKernel<<<ceil(n/256.0),256>>>(d_ballPos, d_ballPosNext, n, GetTime()); //calling the kernel
    cudaMemcpy(ballPosNext, d_ballPosNext, n * sizeof(float), cudaMemcpyDeviceToHost);
    
    cudaFree(d_ballPos);
    cudaFree(d_ballPosNext);
}

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);
    int n = 100; //num of particles
    float t = GetTime();
    float* ballPosX = new float[n];
    float* ballPosXNew = new float[n];
    float* ballPosY = new float[n];
    for(int i = 0; i < n; i++){
	ballPosX[i] = (float)(screenWidth/2) + rand()%200; 
	ballPosY[i] = (float)(screenHeight/2) + rand()%200;
	ballPosXNew[i] = 0;
    }
    while(!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(YELLOW);
	rkSolve(ballPosX, ballPosXNew,  n);
	for(int i = 0; i < n; i++){
	    DrawCircleV({ballPosXNew[i], ballPosY[i]}, 10, BLACK); 
	}
	std::swap(ballPosX, ballPosXNew); 
	EndDrawing();

    }
    CloseWindow();

    return 0;
}
