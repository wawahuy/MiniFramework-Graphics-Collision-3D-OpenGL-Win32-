/////////////////////////////////////////////////////////////////////////////////
// Matrix.h
//
// Project: Engine YUH
// AUTHOR: Nguyen Gia Huy
// CREATED: 02-08-2018
// UPDATED: 29-08-2018
//
// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
// 
// Copyright (C) Nguyen Gia Huy 2018
/////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Mat3.h"
#include <iomanip>

namespace yuh {
	namespace math {

		/* Matrix 4x4
		 * Major - row , support OpenGL
		 *
		 */
		template<typename T>
		class Mat4 {

		public:
			/* Create matrix with identity
			 *
			 */
			Mat4();

			/* Create matrix with values
			 *
			 */
			Mat4( T a00, T a01, T a02, T a03,
				  T a10, T a11, T a12, T a13,
				  T a20, T a21, T a22, T a23,
				  T a30, T a31, T a32, T a33);

			~Mat4();


			/* Set value of element [row][col]
			 *
			 */
			void set(int row, int col, T value);


			void setRow(int row, int c0, int c1, int c2, int c3);

			void setCol(int col, int r0, int r1, int r2, int r3);


			/* Get pointer of matrix
			 * Note pointer is major - row
			 *
			 */
			const T *getPtr();


			/* Matrix to pointer value matrix
			 *
			 */
			operator const T*();


			/* Indentity matrix
			 *
			 */
			void release();


			/* Transponse matrix
			 *
			 */
			Mat4<T>& transpose();


			/* Inverse matric
			 */
			Mat4<T>& inverse();


			/* Mat4 (4x4) * Mat4 (4x1)
			 *
			 */
			Mat4 operator * (const Mat4 &mR);

			/* Mat4 * Vec4
			 */
			Vec4<T> operator * (const Vec4<T> &vec);


			union {
				T m_mtrix[4][4];
				
				struct {
					T _11, _12, _13, _14;
					T _21, _22, _23, _24;
					T _31, _32, _33, _34;
					T _41, _42, _43, _44;
				};
			};
		};


		typedef Mat4<char>		Mat4c;
		typedef Mat4<short>		Mat4s;
		typedef Mat4<int>		Mat4i;
		typedef Mat4<long>		Mat4l;
		typedef Mat4<float>		Mat4f;
		typedef Mat4<double>	Mat4d;

		typedef Mat4<unsigned char>		Mat4uc;
		typedef Mat4<unsigned short>	Mat4us;
		typedef Mat4<unsigned int>		Mat4ui;
		typedef Mat4<unsigned long>		Mat4ul;

#include "Mat4.inl"
	}
}