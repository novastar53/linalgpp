# include <cmath>

using namespace std;

float l2Norm(const float* a, int size_a) {
    float total;
    for (int i = 0; i < size_a; i++){
        total += a[i]*a[i];
    }
    float norm = sqrt(total);
    return norm;
}

float dot(const float* a, const float* b, int size) {
    float result;
    for (int i = 0; i < size; i++) {
        result += a[i]*b[i];
    }
    return result;
}