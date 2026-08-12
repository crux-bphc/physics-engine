#include <iostream>
#include <string>
#include <cuda_runtime.h>
#include <solvers/rk_solver.hpp>
#include "raylib.h"
#include <cmath>
#include <cstdlib>
__device__ float func(float t, float x){
    return  10 * std::cos(5 * t);
}

__device__ float rk4solve(float xn, float yn, float x, float h){ //separate cuda implementation should be written for this
    while(xn < x){
	float k1 = func(xn, yn);
	float k2 = func(xn + (h/2), (yn + ((h/2) * k1)));
	float k3 = func(xn + (h/2), (yn + ((h/2) * k2)));
	float k4 = func(xn + h, yn + (h * k3));
	yn += ((h/6)*(k1 + (2*k2) + (2*k3) + k4));
	xn += h;
    }

   return yn;
}

__global__
void rkSolveKernel(float* Pos, float* PosNew, int n, double t){
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i < n) {
	PosNew[i] =  rk4solve(0, Pos[i], t, 0.01);
    }
}

void rkSolve(float* ballPos, float* ballPosNext, int n){
    float *d_ballPos, *d_ballPosNext;
    int size = n * sizeof(float);

    cudaMalloc((void**)&d_ballPos, size); 
    cudaMemcpy(d_ballPos, ballPos, n * sizeof(float), cudaMemcpyHostToDevice);

    cudaMalloc((void**)&d_ballPosNext, size);
    rkSolveKernel<<<ceil(n/256.0),256>>>(d_ballPos, d_ballPosNext, n, GetTime());
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
    float* ballPos = new float[n];
    float* ballPosNew = new float[n];
    float* ballPosY = new float[n];
    for(int i = 0; i < n; i++){
	ballPos[i] = (float)(screenWidth/2) + rand()%200;
	ballPosY[i] = (float)(screenHeight/2) + rand()%200;
	ballPosNew[i] = 0;
    }
    while(!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(YELLOW);
	rkSolve(ballPos, ballPosNew,  n);
	for(int i = 0; i < n; i++){
	    DrawCircleV({ballPosNew[i], ballPosY[i]}, 10, BLACK); 
	}
	std::swap(ballPos, ballPosNew);
	EndDrawing();

    }
    CloseWindow();

    return 0;
}
