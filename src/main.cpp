# include <iostream> 
# include <chrono>
# include <random>
# include <Accelerate/Accelerate.h>

# include "dot.cpp"


int main() {

    // Generate a random float array.
    int N = 1000000;
    float a[N];
    float b[N];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 0.1);


    for (int i = 0; i < N; ++i) {
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    float norm = l2Norm(a, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << duration.count() << "ms " << norm << std::endl;

    start = std::chrono::high_resolution_clock::now();
    float inner_prod = dot(a, b, N);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << duration.count() << "ms " << inner_prod << std::endl;

    start = std::chrono::high_resolution_clock::now();
    float result = cblas_sdot(N, a, 1, b, 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << duration.count() << "ms " << result << std::endl;

    return 0;
}