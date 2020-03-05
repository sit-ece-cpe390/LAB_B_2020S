#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

void f();

uint64_t b1(uint32_t n) {
	for (int i = 0; i < n; i++)
		f();
	return 0;
}

uint64_t b2(uint32_t n) {
	for (; n > 0; n--) {
		f();
	}
	return 0;
}

uint64_t b3(uint32_t n) {
	uint64_t sum = 0;
	for (int i = 0; i < n; i++)
		sum += i;
	return sum;
}

uint64_t b4(uint32_t n) {
	uint64_t sum = 0;
	for (; n > 0; n--)
		sum += n;
	return sum;
}

uint64_t b5(uint32_t x[], uint32_t n) {
	uint64_t sum = 0;
	for (int i = 0; i < n; i++)
		sum += x[i];
	return sum;
}

uint64_t b6(uint32_t x[], uint32_t n) {
	uint64_t sum = x[0];
	for (; n > 0; n--)
		sum += x[n];
	return sum;
}

uint64_t b7(uint32_t x[], uint32_t n) {
	for (int i = 0; i < n; i++)
		x[i] = 0;
	return 0;
}

uint64_t b8(uint32_t x[], uint32_t n) {
	for ( ; n > 0; n--)
		x[n] = 0;
	x[0] = 0;
	return 0;
}

/*
	write a function that sets elements x[0], x[2], x[4] ... = 0
	then goes back and sets the odd elements x[1], x[3], x[5] .. = 0
	compare the speed of sequential access to the speed of writing out of order
 */
uint64_t b9(uint32_t x[], uint32_t n) {

	return 0;
}

/*
	write a function that sets elements mod 4 = 0: x[0], x[4], x[8] ... = 0
	then the elements mod 4 = 1: x[1], x[5], x[9] ... = 0
	then the elements mod 4 = 2: x[2], x[6], x[10] ... = 0
	last x[3], x[7], x[11] ... = 0
	compare the speed of sequential access to the speed of writing out of order
 */
uint64_t b10(uint32_t x[], uint32_t n) {

	return 0;
}

uint64_t b11(uint32_t x[], uint32_t n) {
	const uint32_t chunk = 32;
	for (uint32_t i = 0; i < chunk; i++) {
		for (uint32_t j = i; j < n; j += chunk)
			x[j] = 0;
	}
	return 0;
}

uint64_t b12(uint32_t x[], uint32_t n) {
	const uint32_t chunk = 1024;
	for (uint32_t i = 0; i < chunk; i++) {
		for (uint32_t j = i; j < n; j += chunk)
			x[j] = 0;
	}
	return 0;
}

uint32_t countPrimes1(uint32_t n) {
	uint32_t count = 0;
	for (uint32_t i = 2; i <= n; i++) {
		for (uint32_t j = 2; j < i; j++)
			if (i % j == 0)
				goto notPrime;
		count++;
	notPrime: ; // do nothing if not prime
	}
	return count;
}

int32_t countPrimes2(uint32_t n) {
	uint32_t count = 1; // special case for 2, the only even prime
	for (uint32_t i = 3; i <= n; i+= 2) {
		for (uint32_t j = 3; j <= sqrt(i); j++)
			if (i % j == 0)
				goto notPrime;
		count++;
	notPrime: ; // do nothing if not prime
	}
	return count;
}

// benchmark adding an array of single precision floating point
uint64_t b13(float x[], uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += x[i];
	return sum;
}

// benchmark writing zeros to an array of single precision floating point
uint64_t b14(float x[], uint32_t n) {
	for (int i = 0; i < n; i++)
		x[i] = 0;
	return 0;
}

// benchmark multiplying an array of single precision floating point
uint64_t b15(float x[], uint32_t n) {
	float prod = 1;
	for (int i = 0; i < n; i++)
		prod *= x[i];
	return prod;
}

#if 0
// benchmark sum of floating point reciprocals
// 1/1 + 1/2 + 1/3 + ... + 1/n
float b16(uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += ???
	return sum;
}


// benchmark sum of floating point square roots
// sqrt(1) + sqrt(2) + ... + sqrt(n)
float b17(uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += ???
	return sum;
}

// benchmark sum of floating point square roots
// sqrt(1) + sqrt(2) + ... + sqrt(n)
float b15(uint32_t n) {
	float sum = 0;
	for (int i = 0; i < n; i++)
		sum += ???
	return sum;
}

#endif




/*
	This is matrix multiplication for a matrix of size 10x10
 */
void matmult(float ans[10][10], float a[10][10], float b[10][10]) {
	const int n = 10;
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			ans[i][j] = 0;
			for (uint32_t k = 0; k < n; k++)
				ans[i][j] += a[i][k] * b[k][j];
		}
}

#if 0
/*
	the following code is not legal because 2-D matrices must be fixed in size.
	Instead, write the code to index using the rule: a[i][k] = a[i*n+k]
	This is what the compiler actually does for 2d matrices when it knows the size
	of n in advance
 */
void matmult2(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			ans[i][j] = 0;
			for (uint32_t k = 0; k < n; k++)
				ans[i][j] += a[i][k] * b[k][j];
		}
}

/*
	matmult2 above is inefficient because you are repeatedly writing ans[i][j],
	then reading it in again, adding a new multiplication and writing again.
	Avoid this by using a scalar variable which can be in a register.
 */
void matmult3(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0; i < n; i++) 
		for (uint32_t j = 0; j < n; j++) {
			double dot = 0;
			for (uint32_t k = 0; k < n; k++)
				dot += a[i][k] * b[k][j];
			ans[i][j] = ???
		}
}

/*
	matmult3 above is inefficient because every time you look up a location:

	a[i][k] you are computing a[i*n+k] which uses a multiplication which takes a few extra clocks

	rewrite the function to take advantage of the fact that we just need to add
	not multiply.
 */
void matmult4(float ans[], float a[], float b[], uint32_t n) {
	for (uint32_t i = 0, c = 0; i < n; i++, c++) 
		for (uint32_t j = 0, e = ???; j < n; j++) {
			double dot = 0;
			for (uint32_t k = 0, d = ???; k < n; k++)
				dot += a[d] * b[e];
			ans[c] = ???
		}
}
#endif


template<typename Func>
void benchmark1(const char msg[], Func f, uint32_t n) {
	for (uint32_t trials = 0; trials < 10; trials++) {
		clock_t t0 = clock();
		uint64_t res = f(n);
		clock_t t1 = clock();
		cout << setw(12) << msg << setw(20) << res << '\t' << (t1-t0) << '\n';
	}
}

template<typename Func>
void benchmark2(const char msg[], Func f, uint32_t n) {
	uint32_t* p = new uint32_t[n]; // allocate a big chunk of memory
	for (uint32_t trials = 0; trials < 10; trials++) {
		clock_t t0 = clock();
		uint64_t res = f(p, n); // give it to the function to play with
		clock_t t1 = clock();
		cout << setw(12) << msg << '\t' << setw(20) << res << '\t' << (t1-t0) << '\n';
	}
	delete [] p;
}

template<typename Func>
void benchmark3(const char msg[], Func f, uint32_t n) {
	uint32_t* p = new float[n]; // allocate a big chunk of memory
	clock_t t0 = clock();
	uint64_t res = f(p, n); // give it to the function to play with
	clock_t t1 = clock();
	delete [] p;
	cout << msg << '\t' << res << '\t' << (t1-t0) << '\n';
}

int main() {
	const uint32_t n = 100000000; // 100 million
	benchmark1("b1", b1, n);
	benchmark1("b2", b2, n); // compare b1 and b2. What can you conclude?
	benchmark1("b3", b3, n);
	benchmark1("b4", b4, n); // compare b3 and b4. What can you conclude?
	// what can you conclude from the difference between b1,b3 and b2,b4?

	constexpr uint32_t numPrimes = 100000;
	benchmark1("countPrimes1", countPrimes1, numPrimes);
	benchmark1("countPrimes2", countPrimes2, numPrimes);
	benchmark1("countPrimes2", countPrimes2, numPrimes*10);

	const uint32_t n2 = 40000000; // 40 million
	benchmark2("b5", b5, n2);
	benchmark2("b6", b6, n2); // compare b5 and b6, what can you conclude?

	benchmark2("b7", b7, n2);
	benchmark2("b8", b8, n2); // compare b7 and b8, what can you conclude?
	// what can you conclude from the difference between b5,b7 and b6,b8?

	// compare the times for going increasingly non-sequential. What happens?
	benchmark2("b9", b9, n2);
	benchmark2("b10", b10, n2);
	benchmark2("b11", b11, n2);
	benchmark2("b12", b12, n2);	
}
