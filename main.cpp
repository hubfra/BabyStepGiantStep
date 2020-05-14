
#include <iostream>
#include <chrono>
#include <vector>


int64_t BabyStepGiantStep(int64_t base, int64_t modulus, int64_t result);
int64_t ModPow(int64_t base, int64_t exponent, int64_t modulus);
int64_t InvMod(int64_t a, int64_t n);


int main()
{
	int64_t g = 1336465782;
	int64_t p = 1628175011;
	int64_t A = 439311755;

	auto start = std::chrono::steady_clock::now();
	std::cout << BabyStepGiantStep(g, p, A) << '\n';
	auto end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << '\n';
	return 0;
}


struct HashSet
{
	int64_t index = -1;
	std::vector<int64_t> hashes;
};

int64_t BabyStepGiantStep(int64_t base, int64_t modulus, int64_t result)
{
	int64_t m = static_cast<int64_t>(ceil(sqrt(modulus)));
	std::vector<HashSet> hash_sets(m);

	for (int j = 0; j < m; ++j) {
		int64_t mod = ModPow(base, j, modulus);
		hash_sets[mod % m].hashes.push_back(mod);
	}

	int64_t v = ModPow(InvMod(base, modulus), m, modulus);
	int64_t d = result;

	for (int i = 0; i < m; ++i) {
		int64_t hash = d % modulus;
		int64_t index = hash % m;

		for (int64_t p : hash_sets[index].hashes) {
			if (p == hash) {
				return i * m + hash_sets[index].index;
			}
		}

		d = (d % modulus) * v;
	}

	return 0;
}

int64_t ModPow(int64_t base, int64_t exponent, int64_t modulus)
{
	int64_t result = 1;
	int64_t pow = base % modulus;

	for (int64_t a = 1; a <= exponent; a <<= 1) {
		if (a & exponent) result = (result * pow) % modulus;
		pow = (pow * pow) % modulus;
	}

	return result;
}

int64_t InvMod(int64_t a, int64_t n)
{
	int64_t q, r, s;
	int64_t q1, r1, s1;
	int64_t q2, r2, s2;

	if (a > n) {
		q1 = 0, r1 = a, s1 = 1;
		q2 = 0, r2 = n, s2 = 0;
	}
	else {
		q1 = 0, r1 = n, s1 = 0;
		q2 = 0, r2 = a, s2 = 1;
	}

	while (r2 != 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		s = s1 - q * s2;

		q1 = q2, r1 = r2, s1 = s2;
		q2 = q, r2 = r, s2 = s;
	}

	if (r1 != 1) return -1;
	else if (s1 >= 0) return s1;
	else return s1 + n;
}