#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>

static void input_vector(const char* file_name, int dimension, double* vector) {
	FILE* file_stream = fopen(file_name, "r");
	for (int i = 0; i < dimension; i++) {
		fscanf_s(file_stream, "%lf ", vector + i);
	}
	fclose(file_stream);
}

int main()
{
	int k = 9;
	int n = 0;
	int K = 0;
	double lam = 0.3;
	double* xi = new double[k];
	double* ni = new double[k];
	double mean = 0;
	double disp = 0;
	double std_dev = 0;

	input_vector("xi.txt", k, xi);
	input_vector("ni.txt", k, ni);
	
	for (int i = 0; i < k; i++) {
		mean = mean + xi[i] * ni[i];
		n += ni[i];
	}
	mean /= n;
	printf_s("n = %d \nmean = %lf, ", n, mean);

	for (int i = 0; i < k; i++) {
		disp += (mean - xi[i]) * (mean - xi[i]) * ni[i];
	}
	disp /= n;
	std_dev = sqrt(disp);

	printf_s("variance = %lf, standart deviation = %lf \n", disp, std_dev);
	printf_s("two sigma method : % lf - % lf \n", mean - 2 * std_dev, mean + 2 * std_dev);

	int i = 0, j = 1;
	for (; i < k; j = j + ni[i], i++) {
		if (K < j + ni[i] && K >= j) break;
	}
	j = j + ni[i];

	printf_s("quantile for k = %d: %lf", K, (double)(j - 1) / n);
}
