#include <cmath>
#if defined (__CUDACC__)
    #include <cuda_runtime.h>
    #include <cublas_v2.h>
#elif defined(__APPLE__)
    #include <Accelerate/Accelerate.h>
#endif

using namespace std;

float dot(const std::vector<float>& a, const std::vector<float>& b) {
    int n = a.size();
    float result = 0.0f;

#if defined(__CUDACC__)
    float *d_a, *d_b, *d_result;

    cudaMalloc(&d_a, n * sizeof(float));
    cudaMalloc(&d_b, n * sizeof(float));
    cudaMalloc(&d_result, sizeof(float));
    cudaMemcpy(d_a, a.data(), n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b.data(), n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemset(d_result, 0, sizeof(float));

    int threads = 256;
    int blocks = (n + threads - 1) / threads;
    dot_kernel<<<blocks, threads>>>(d_a, d_b, d_result, n);
    cudaMemcpy(&result, d_result, sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);
#elif defined(__APPLE__)
    result = cblas_sdot(n, a.data(), 1, b.data(), 1);
#else
    float result;
    for (int i = 0; i < n; i++) {
        result += a[i]*b[i];
    }
#endif
    return result;
}