#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

// Function to compute the height of the function
double height(double x, int n, int* A, int* B) {
    double total_height = 0;
    for (int i = 0; i < n; i++) {
        total_height += sin(A[i] * x + B[i]);
    }
    return total_height;
}

// Function to find local maxima
void findPeaks(int n, double* peaks, double step, int* A, int* B) {
    int peaks_count = 0;
    double prev_height = height(0, n, A, B);

    for (double x = step; x <= 2 * PI; x += step) {
        double current_height = height(x, n, A, B);

        if (prev_height < current_height) {
            // Check if previous height was less and current height is greater
            // Now check if next point is also less to confirm maxima
            double next_height = height(x + step, n, A, B);
            if (next_height < current_height) {
                peaks[peaks_count++] = x; // Store the peak position
            }
        }
        prev_height = current_height;
    }
}

// Main function
int main() {
    int n;
    scanf("%d", &n);

    int A[25], B[25];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    double peaks[25];
    findPeaks(n, peaks, 0.001, A, B); // Find peaks with a resolution of 0.001

    // Count valleys which are found between peaks
    int max_valley_width = 0;
    int valley_index = 0;

    for (int i = 0; i < n - 1; i++) {
        // Calculate width of each valley between peaks
        double width = peaks[i + 1] - peaks[i];

        if (width > max_valley_width) {
            max_valley_width = width; // Update maximum width
            valley_index = i; // Index of leftmost valley
        }
    }

    // Output valley index (1-based)
    printf("%d\n", valley_index + 1);

    return 0;
}
