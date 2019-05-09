#pragma once
/* Vector 3D
 * Header
 */
#include "Vector3D.h"

namespace yuh {

	template<typename T>
	class Vec4
	{
	public:
		Vec4<T>();
		Vec4<T>(T x, T y, T z, T w);
		Vec4<T>(const Vec3<T> &v, T w);

		union {
			struct {
				T x, y, z, w;
			};

			struct {
				T r, g, b, a;
			};

			struct {
				Vec3<T> xyz;
			};
		};

		/* Ep kieu
		*
		*/
		template <typename U> explicit operator Vec4<U>();
		operator T*();

	};


	/* Type Vec3[x]
	*
	*/
	typedef Vec4<float>				Vec4f;
	typedef Vec4<char>				Vec4b;
	typedef Vec4<short>				Vec4s;
	typedef Vec4<int>				Vec4i;
	typedef Vec4<long>				Vec4l;
	typedef Vec4<unsigned char>		Vec4ub;
	typedef Vec4<unsigned short>	Vec4us;
	typedef Vec4<unsigned int>		Vec4ui;
	typedef Vec4<unsigned long>		Vec4ul;

	template<typename T>
	inline Vec4<T>::Vec4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<typename T>
	inline Vec4<T>::Vec4(T x, T y, T z, T w) :
		x(x), y(y), z(z), w(w) {

	}

	template<typename T>
	inline Vec4<T>::Vec4(const Vec3<T>& v, T w)
	{
		xyz = v;
		this->w = w;
	}

	template<typename T>
	template<typename U>
	inline Vec4<T>::operator Vec4<U>(){
		return Vec4<U>(x, y, z, w);
	}

	template<typename T>
	inline Vec4<T>::operator T *() {
		return &x;
	}

	template<typename T>
	std::ostream& operator << (std::ostream& out, Vec4<T> vec) {
		std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")\n";
		return out;
	}
}