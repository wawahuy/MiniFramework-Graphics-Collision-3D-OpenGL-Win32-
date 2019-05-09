///////////////////////////////////////////////////////////////////////////////////
//// Matrix.h
////
//// Project: Engine YUH
//// AUTHOR: Nguyen Gia Huy
//// CREATED: 02-08-2018
//// UPDATED: 29-08-2018
////
//// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
//// 
//// Copyright (C) Nguyen Gia Huy 2018
///////////////////////////////////////////////////////////////////////////////////
//
//#pragma once
//#include "Vector3D.h"
//
//namespace yuh {
//	namespace math {
//		
//
//		/* Matrix 4x4
//		 * Major - row , support OpenGL
//		 *
//		 */
//		template<typename T>
//		class Mat3 {
//
//		public:
//			/* Create matrix with identity
//			 *
//			 */
//			Mat3();
//
//			/* Create matrix with values
//			 *
//			 */
//			Mat3( T a00, T a01, T a02, T a03,
//				  T a10, T a11, T a12, T a13,
//				  T a20, T a21, T a22, T a23,
//				  T a30, T a31, T a32, T a33);
//
//			~Mat3();
//
//
//			/* Set value of element [row][col]
//			 *
//			 */
//			void set(int row, int col, T value);
//
//
//			void setRow(int row, int c0, int c1, int c2, int c3);
//
//			void setCol(int col, int r0, int r1, int r2, int r3);
//
//
//			/* Get pointer of matrix
//			 * Note pointer is major - row
//			 *
//			 */
//			const T *getPtr();
//
//
//			/* Matrix to pointer value matrix
//			 *
//			 */
//			operator const T*();
//
//
//			/* Indentity matrix
//			 *
//			 */
//			void release();
//
//
//			/* Transponse matrix
//			 *
//			 */
//			Mat3<T>& transpose();
//
//
//			/* Inverse matric
//			 */
//			Mat3<T>& inverse();
//
//
//			/* Mat3 (3x3) * Mat3 (3x1)
//			 *
//			 */
//			Mat3 operator * (const Mat4 &mR);
//
//			/* Mat3 * Vec3
//			 */
//			Vec3<T> operator * (const Vec4<T> &vec);
//
//
//			T m_mtrix[3][3];
//
//		};
//
//
//		typedef Mat3<char>		Mat3c;
//		typedef Mat3<short>		Mat3s;
//		typedef Mat3<int>		Mat3i;
//		typedef Mat3<long>		Mat3l;
//		typedef Mat3<float>		Mat3f;
//		typedef Mat3<double>	Mat3d;
//
//		typedef Mat3<unsigned char>		Mat3uc;
//		typedef Mat3<unsigned short>	Mat3us;
//		typedef Mat3<unsigned int>		Mat3ui;
//		typedef Mat3<unsigned long>		Mat3ul;
//
//#include "Mat3.inl"
//	}
//}