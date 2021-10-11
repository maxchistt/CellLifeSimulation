#pragma once
#include <math.h>
#include <utility>
#include <random>

namespace structs {

	template <typename T>
	struct Point2D {
		T x, y;

		Point2D() {
			set(0, 0);
		};

		Point2D(T x, T y) {
			set(x, y);
		};

		void set(T x, T y) {
			this->x = x;
			this->y = y;
		};

		Point2D<T>& operator += (Point2D<T> v)
		{
			this->x += (T)(v.x);
			this->y += (T)(v.y);
			return *this;
		};

		Point2D<T>& operator -= (Point2D<T> v)
		{
			this->x -= v.x;
			this->y -= v.y;
			return *this;
		};

		bool operator==(const Point2D<T>& p2)
		{
			return (this->x == p2.x && this->x == p2.y);
		}
		bool operator!=(const Point2D<T>& p2)
		{
			return !(*this == p2);
		}
	};

	template <typename T>
	struct Vect2D : Point2D<T> {
		Vect2D() :Point2D<T>() {};
		Vect2D(Point2D<T> p) :Point2D<T>(p.x, p.y) {};
		Vect2D(T x, T y) :Point2D<T>(x, y) {};

		Vect2D<T>& operator /= (Point2D<T> v)
		{
			this->x /= v.x;
			this->y /= v.y;
			return *this;
		};

		Vect2D<T>& operator *= (Point2D<T> v)
		{
			this->x *= v.x;
			this->y *= v.y;
			return *this;
		};

		Vect2D<T>& operator /= (T v)
		{
			this->x /= v;
			this->y /= v;
			return *this;
		};

		Vect2D<T>& operator *= (T v)
		{
			this->x *= v;
			this->y *= v;
			return *this;
		};

		double getAbs() {
			return sqrt(pow((double)(this->x), 2) + pow((double)(this->y), 2));
		}

		Vect2D getDistanceVect(Point2D<T> p2) {
			Vect2D<T> dist(p2);
			dist -= *this;
			return dist;
		}
	};
};

