
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


int64_t BabyStepGiantStep(int64_t base, int64_t modulus, int64_t result)
{
	int64_t m = static_cast<int64_t>(ceil(sqrt(modulus)));
	std::vector<std::vector<std::pair<int64_t, int64_t>>> hashes(m);

	for (int j = 0; j < m; ++j) {
		int64_t reminder = ModPow(base, j, modulus);
		hashes[reminder % m].push_back({ reminder, j });
	}

	int64_t v = ModPow(InvMod(base, modulus), m, modulus);
	int64_t d = result;
	int64_t hash, index;

	for (int i = 0; i < m; ++i) {
		hash = d % modulus;
		index = hash % m;

		for (auto& pair : hashes[index]) {
			if (pair.first == hash) {
				return i * m + pair.second;
			}
		}

		d = (d % modulus) * v;
	}

	return -1;
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
