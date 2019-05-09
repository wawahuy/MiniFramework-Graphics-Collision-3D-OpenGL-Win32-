template<typename T>
inline Mat4<T>::Mat4()
{
	release();
}

template<typename T>
inline yuh::math::Mat4<T>::Mat4(T a00, T a01, T a02, T a03, T a10, T a11, T a12, T a13, T a20, T a21, T a22, T a23, T a30, T a31, T a32, T a33)
{
	m_mtrix[0][0] = a00; m_mtrix[0][1] = a01; m_mtrix[0][2] = a02; m_mtrix[0][3] = a03;
	m_mtrix[1][0] = a10; m_mtrix[1][1] = a11; m_mtrix[1][2] = a12; m_mtrix[1][3] = a13;
	m_mtrix[2][0] = a20; m_mtrix[2][1] = a21; m_mtrix[2][2] = a22; m_mtrix[2][3] = a23;
	m_mtrix[3][0] = a30; m_mtrix[3][1] = a31; m_mtrix[3][2] = a32; m_mtrix[3][3] = a33;
}

template<typename T>
inline yuh::math::Mat4<T>::~Mat4()
{
}

template<typename T>
inline void yuh::math::Mat4<T>::set(int row, int col, T value)
{
	m_mtrix[row][col] = value;
}

template<typename T>
inline void yuh::math::Mat4<T>::setRow(int row, int c1, int c2, int c3, int c4)
{
	m_mtrix[row][0] = c1;
	m_mtrix[row][1] = c2;
	m_mtrix[row][2] = c3;
	m_mtrix[row][3] = c4;
}

template<typename T>
inline void yuh::math::Mat4<T>::setCol(int col, int r1, int r2, int r3, int r4)
{
	m_mtrix[0][col] = r1;
	m_mtrix[1][col] = r2;
	m_mtrix[2][col] = r3;
	m_mtrix[3][col] = r4;
}

template<typename T>
inline const T * yuh::math::Mat4<T>::getPtr()
{
	return &m_mtrix[0][0];
}

template<typename T>
inline yuh::math::Mat4<T>::operator const T*()
{
	return &m_mtrix[0][0];
}

template<typename T>
inline void yuh::math::Mat4<T>::release()
{
	m_mtrix[0][0] = 1.0; m_mtrix[0][1] = 0.0; m_mtrix[0][2] = 0.0; m_mtrix[0][3] = 0.0;
	m_mtrix[1][0] = 0.0; m_mtrix[1][1] = 1.0; m_mtrix[1][2] = 0.0; m_mtrix[1][3] = 0.0;
	m_mtrix[2][0] = 0.0; m_mtrix[2][1] = 0.0; m_mtrix[2][2] = 1.0; m_mtrix[2][3] = 0.0;
	m_mtrix[3][0] = 0.0; m_mtrix[3][1] = 0.0; m_mtrix[3][2] = 0.0; m_mtrix[3][3] = 1.0;
}

template<typename T>
inline Mat4<T>& yuh::math::Mat4<T>::transpose()
{
	std::swap(m_mtrix[1][0], m_mtrix[0][1]);
	std::swap(m_mtrix[2][0], m_mtrix[0][2]);
	std::swap(m_mtrix[3][0], m_mtrix[0][3]);
	std::swap(m_mtrix[1][2], m_mtrix[2][1]);
	std::swap(m_mtrix[1][3], m_mtrix[3][1]);
	std::swap(m_mtrix[2][3], m_mtrix[3][2]);

	return *this;
}

template<typename T>
inline Mat4<T> & yuh::math::Mat4<T>::inverse()
{
	//
	// <-----------UPDATE ------------------->
	//
	return *this;
}

template<typename T>
inline Mat4<T> yuh::math::Mat4<T>::operator*(const Mat4<T> &mR)
{
	return Mat4<T>(
		m_mtrix[0][0] * mR.m_mtrix[0][0] + m_mtrix[0][1] * mR.m_mtrix[1][0] + m_mtrix[0][2] * mR.m_mtrix[2][0] + m_mtrix[0][3] * mR.m_mtrix[3][0],
		m_mtrix[0][0] * mR.m_mtrix[0][1] + m_mtrix[0][1] * mR.m_mtrix[1][1] + m_mtrix[0][2] * mR.m_mtrix[2][1] + m_mtrix[0][3] * mR.m_mtrix[3][1],
		m_mtrix[0][0] * mR.m_mtrix[0][2] + m_mtrix[0][1] * mR.m_mtrix[1][2] + m_mtrix[0][2] * mR.m_mtrix[2][2] + m_mtrix[0][3] * mR.m_mtrix[3][2],
		m_mtrix[0][0] * mR.m_mtrix[0][3] + m_mtrix[0][1] * mR.m_mtrix[1][3] + m_mtrix[0][2] * mR.m_mtrix[2][3] + m_mtrix[0][3] * mR.m_mtrix[3][3],

		m_mtrix[1][0] * mR.m_mtrix[0][0] + m_mtrix[1][1] * mR.m_mtrix[1][0] + m_mtrix[1][2] * mR.m_mtrix[2][0] + m_mtrix[1][3] * mR.m_mtrix[3][0],
		m_mtrix[1][0] * mR.m_mtrix[0][1] + m_mtrix[1][1] * mR.m_mtrix[1][1] + m_mtrix[1][2] * mR.m_mtrix[2][1] + m_mtrix[1][3] * mR.m_mtrix[3][1],
		m_mtrix[1][0] * mR.m_mtrix[0][2] + m_mtrix[1][1] * mR.m_mtrix[1][2] + m_mtrix[1][2] * mR.m_mtrix[2][2] + m_mtrix[1][3] * mR.m_mtrix[3][2],
		m_mtrix[1][0] * mR.m_mtrix[0][3] + m_mtrix[1][1] * mR.m_mtrix[1][3] + m_mtrix[1][2] * mR.m_mtrix[2][3] + m_mtrix[1][3] * mR.m_mtrix[3][3],

		m_mtrix[2][0] * mR.m_mtrix[0][0] + m_mtrix[2][1] * mR.m_mtrix[1][0] + m_mtrix[2][2] * mR.m_mtrix[2][0] + m_mtrix[2][3] * mR.m_mtrix[3][0],
		m_mtrix[2][0] * mR.m_mtrix[0][1] + m_mtrix[2][1] * mR.m_mtrix[1][1] + m_mtrix[2][2] * mR.m_mtrix[2][1] + m_mtrix[2][3] * mR.m_mtrix[3][1],
		m_mtrix[2][0] * mR.m_mtrix[0][2] + m_mtrix[2][1] * mR.m_mtrix[1][2] + m_mtrix[2][2] * mR.m_mtrix[2][2] + m_mtrix[2][3] * mR.m_mtrix[3][2],
		m_mtrix[2][0] * mR.m_mtrix[0][3] + m_mtrix[2][1] * mR.m_mtrix[1][3] + m_mtrix[2][2] * mR.m_mtrix[2][3] + m_mtrix[2][3] * mR.m_mtrix[3][3],

		m_mtrix[3][0] * mR.m_mtrix[0][0] + m_mtrix[3][1] * mR.m_mtrix[1][0] + m_mtrix[3][2] * mR.m_mtrix[2][0] + m_mtrix[3][3] * mR.m_mtrix[3][0],
		m_mtrix[3][0] * mR.m_mtrix[0][1] + m_mtrix[3][1] * mR.m_mtrix[1][1] + m_mtrix[3][2] * mR.m_mtrix[2][1] + m_mtrix[3][3] * mR.m_mtrix[3][1],
		m_mtrix[3][0] * mR.m_mtrix[0][2] + m_mtrix[3][1] * mR.m_mtrix[1][2] + m_mtrix[3][2] * mR.m_mtrix[2][2] + m_mtrix[3][3] * mR.m_mtrix[3][2],
		m_mtrix[3][0] * mR.m_mtrix[0][3] + m_mtrix[3][1] * mR.m_mtrix[1][3] + m_mtrix[3][2] * mR.m_mtrix[2][3] + m_mtrix[3][3] * mR.m_mtrix[3][3]
	);
}


template<typename T>
inline Vec4<T> yuh::math::Mat4<T>::operator*(const Vec4<T> &vec)
{
	
	return Vec4<T>(
		m_mtrix[0][0] * vec.x + m_mtrix[0][1] * vec.y + m_mtrix[0][2] * vec.z + m_mtrix[0][3] * vec.w,
		m_mtrix[1][0] * vec.x + m_mtrix[1][1] * vec.y + m_mtrix[1][2] * vec.z + m_mtrix[1][3] * vec.w,
		m_mtrix[2][0] * vec.x + m_mtrix[2][1] * vec.y + m_mtrix[2][2] * vec.z + m_mtrix[2][3] * vec.w,
		m_mtrix[3][0] * vec.x + m_mtrix[3][1] * vec.y + m_mtrix[3][2] * vec.z + m_mtrix[3][3] * vec.w
		);
	
}

template<typename T> std::ostream& yuh::math::operator<< (std::ostream& out, Mat4<T> &m) {
	const T *pointer = m.getPtr();

	std::cout << std::endl << "=================================Matrix=============================" << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << std::setw(16) << pointer[i*4+j];
		}
		std::cout << std::endl;
	}
	std::cout << "====================================================================" << std::endl << std::endl;
	return out;
}



