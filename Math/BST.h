#pragma once

namespace yuh {
	namespace math {

		///<sumany>Node of BST</sumany>
		template<class T> struct NodeBST {
			T data;
			NodeBST *left	= NULL;
			NodeBST *right	= NULL;
		};

		 
		///<sumany>Class BST</sumany>
		template<class T> class BST
		{
		public:
			~BST();

			///<sumany>Get Root Binary Search Tree</sumany>
			///<returns>NodeBST of Root</returns>
			NodeBST<T> *getRoot();


			///<sumany>Insert data to BSP</sumany>
			///<param name="data">data need insert to BSP</param>
			BST<T>& insert(T data);


			///<sumany>Remove data to BSP</sumany>
			///<param name="data">data need insert to BSP</param>
			bool remove(T data);


			///<sumany>Find Data in BSP</sumany>
			///<param name="data">data need find in BSP</param>
			///<param name="node">result node find if return true</param>
			///<returns>true if has data in BSP</returns>
			bool find(T data, NodeBST<T> *&node);


			///<sumany>Find Data in BSP</sumany>
			///<param name="data">data need find in BSP</param>
			///<param name="node">result node find if return true</param>
			///<param name="nodePrev">node prev result find if return true</param>
			///<returns>true if has data in BSP</returns>
			bool find(T data, NodeBST<T> *&node, NodeBST<T> *&nodePrev);


			///<sumany>LNR</sumany>
			///<param name="callback"> Callback when browser on 1 Node\r\nNode* has node.\r\nptr: is ptr user data.</param>
			///<param name="ptr">User data</param>
			void LNR(void(*callback)(NodeBST<T> *, void *), void *ptr = 0);


		private:
			///<sumany>LNR</sumany>
			///
			void m_LNR(void(*callback)(NodeBST<T> *, void *), NodeBST<T> *node, void *ptr = 0);
			
			//root
			NodeBST<T> *m_root = NULL;
		};
		
#include "BST.inl" 
	}
}
