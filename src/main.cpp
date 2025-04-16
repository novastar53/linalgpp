# include <iostream> 
# include <chrono>
# include <random>

# include "dot.cpp"


int main() {

    // Generate a random float array.
    int N = 100000;
    std::vector<float> a(N);
    std::vector<float> b(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 0.1);


    for (int i = 0; i < N; ++i) {
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    float inner_prod = dot(a, b);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    std::cout << duration.count() << "ms " << inner_prod << std::endl;

    return 0;
}