#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

// Function to represent the signal: f(t) = t^2 (for 0 <= t <= T)
double signal_function(double t) {
    return t * t; // Example signal f(t) = t^2
}

// Function to compute the a_0 term
double compute_a0(double T) {
    double sum = 0.0, dt = 0.01;
    for (double t = 0.0; t < T; t += dt) {
        sum += signal_function(t) * dt;
    }
    return (1.0 / T) * sum;
}

// Function to compute the a_n terms
double compute_an(int n, double T) {
    double sum = 0.0, dt = 0.01;
    for (double t = 0.0; t < T; t += dt) {
        sum += signal_function(t) * cos(2 * n * PI * t / T) * dt;
    }
    return (2.0 / T) * sum;
}

// Function to compute the b_n terms
double compute_bn(int n, double T) {
    double sum = 0.0, dt = 0.01;
    for (double t = 0.0; t < T; t += dt) {
        sum += signal_function(t) * sin(2 * n * PI * t / T) * dt;
    }
    return (2.0 / T) * sum;
}

int main() {
    int N_TERMS;
    double T;

    // Get user input for the number of Fourier terms and period
    printf("Enter the number of Fourier terms (e.g., 10): ");
    scanf("%d", &N_TERMS);

    printf("Enter the period of the signal (e.g., 2.0): ");
    scanf("%lf", &T);

    // Compute and print Fourier coefficients
    double a0 = compute_a0(T);
    printf("a0: %lf\n", a0);

    for (int n = 1; n <= N_TERMS; n++) {
        double an = compute_an(n, T);
        double bn = compute_bn(n, T);
        printf("a%d: %lf, b%d: %lf\n", n, an, n, bn);
    }

    return 0;
}
