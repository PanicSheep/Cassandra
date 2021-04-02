#pragma once
#include <cassert>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <limits>
#include <vector>
#include <omp.h>

class Vector
{
public:
	using value_type = float;
private:
	std::vector<value_type> data;
public:
	Vector(std::vector<value_type> data) noexcept : data(std::move(data)) {}
	Vector(std::size_t size = 0, value_type value = 0) : data(size, value) {}

	[[nodiscard]] auto operator==(const Vector& o) const noexcept { return data == o.data; }
	[[nodiscard]] auto operator!=(const Vector& o) const noexcept { return data != o.data; }

	std::size_t size() const noexcept { return data.size(); }
	void push_back(value_type x) noexcept { data.push_back(x); }
	void clear() noexcept { data.clear(); }
	void reserve(std::size_t new_capacity) noexcept { data.reserve(new_capacity); }

	template <typename Iterator>
	void insert(std::vector<value_type>::const_iterator where, Iterator first, Iterator last) { data.insert(where, first, last); }

	auto begin() noexcept { return data.begin(); }
	auto begin() const noexcept { return data.begin(); }
	auto cbegin() const noexcept { return data.cbegin(); }
	auto end() noexcept { return data.end(); }
	auto end() const noexcept { return data.end(); }
	auto cend() const noexcept { return data.cend(); }

	value_type& operator[](std::size_t i) noexcept { return data[i]; }
	value_type& operator()(std::size_t i) noexcept { return data[i]; }
	const value_type& operator[](std::size_t i) const noexcept { return data[i]; }
	const value_type& operator()(std::size_t i) const noexcept { return data[i]; }

	Vector& operator+=(const Vector& x) 
	{
		assert(data.size() == x.size());
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			data[i] += x[i];
		return *this;
	}

	Vector& operator-=(const Vector& x)
	{
		assert(data.size() == x.size());
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			data[i] -= x[i];
		return *this;
	}

	Vector& operator*=(value_type m)
	{
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			data[i] *= m;
		return *this;
	}

	Vector& operator/=(value_type m) 
	{
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			data[i] /= m;
		return *this;
	}

	Vector elementwise_multiplication(Vector x) const
	{
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			x[i] *= data[i];
		return x;
	}

	Vector elementwise_division(Vector x) const
	{
		const int64_t size = data.size();
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
			x[i] /= data[i];
		return x;
	}
};

inline Vector operator+(      Vector  l, const Vector&  r) { return l += r; }
inline Vector operator+(const Vector& l,       Vector&& r) { return r += l; }

inline Vector operator-(      Vector  l, const Vector&  r) { return l -= r; }
inline Vector operator-(const Vector& l,       Vector&& r)
{
	assert(l.size() == r.size());
	const int64_t size = r.size();
	#pragma omp parallel for
	for (int64_t i = 0; i < size; i++)
		r[i] = l[i] - r[i];
	return r;
}

inline Vector operator*(Vector vec, Vector::value_type mul) { return vec *= mul; }
inline Vector operator*(Vector::value_type mul, Vector vec) { return vec *= mul; }

inline Vector operator/(Vector vec, Vector::value_type mul) { return vec /= mul; }

inline Vector inv(Vector x, Vector::value_type infinity = std::numeric_limits<Vector::value_type>::infinity())
{
	const int64_t size = x.size();
	#pragma omp parallel for
	for(int64_t i = 0; i < size; i++)
		if (x[i] == 0)
			x[i] = infinity;
		else
			x[i] = Vector::value_type(1) / x[i];
	return x;
}
