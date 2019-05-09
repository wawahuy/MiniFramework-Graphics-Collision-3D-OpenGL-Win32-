///
///
///<inline>Inline Code </inline>
///
///
template<class T>
inline BST<T>::~BST()
{
}


///<sumany>
///Get Root Binary Search Tree
///</sumany>
///<returns>NodeBST of Root</returns>
template<class T>
inline NodeBST<T>* BST<T>::getRoot()
{
	return m_root;
}


///<sumany>Insert data to BSP</sumany>
///<param name="data">data need insert to BSP</param>
template<class T>
inline BST<T>& BST<T>::insert(T data)
{
	NodeBST<T>** node = &m_root;

	while (*node != NULL) {
		if ((*node)->data > data) {
			node = &(*node)->left;
		}
		else {
			node = &(*node)->right;
		}
	}

	(*node) = new NodeBST<T>;
	(*node)->data = data;

	return *this;
}


///<sumany>Remove data to BSP</sumany>
///<param name="data">data need insert to BSP</param>
template<class T>
inline bool BST<T>::remove(T data)
{
	NodeBST<T> *node;
	NodeBST<T> *nodePrev;

	//Find Node
	if (find(data, node, nodePrev) == false) return false;

	//With 0 Child
	if (node->left == NULL && node->right == NULL) {
		if (nodePrev->left == node)
			nodePrev->left = NULL;
		else
			nodePrev->right = NULL;
	}

	//With 1 Child
	else if (node->left == NULL || node->right == NULL) {
		//---UPDATE---
	}

	//With 2 Child
	else {
		//---UPDATE---
	}

	delete node;

	return false;
}


///<sumany>Find Data in BSP</sumany>
///<param name="data">data need find in BSP</param>
///<param name="node">result node find if return true</param>
///<returns>true if has data in BSP</returns>
template<class T>
inline bool BST<T>::find(T data, NodeBST<T> *&node)
{
	node = m_root;

	while (node != NULL) {

		///Same data
		if (node->data == data) {
			return true;
		}

		///Data only left node
		else if (node->data > data) {
			node = node->left;
		}

		///Data only right node
		else {
			node = node->right;
		}
	}

	return false;
}



///<sumany>Find Data in BSP</sumany>
///<param name="data">data need find in BSP</param>
///<param name="node">result node find if return true</param>
///<param name="nodePrev">node prev result find if return true</param>
///<returns>true if has data in BSP</returns>
template<class T>
inline bool BST<T>::find(T data, NodeBST<T>*& node, NodeBST<T>*& nodePrev)
{
	node = m_root;
	nodePrev = NULL;

	while (node != NULL) {

		///Same data
		if (node->data == data) {
			return true;
		}

		///Node Prev
		nodePrev = node;

		///Data only left node
		if (node->data > data) {
			node = node->left;
		}

		///Data only right node
		else {
			node = node->right;
		}

	}

	return false;
}




///<sumany>LNR</sumany>
///
template<class T>
inline void BST<T>::LNR(void(*callback)(NodeBST<T> *, void *), void *ptr)
{
	m_LNR(callback, getRoot(), ptr);
}


///<sumany>LNR</sumany>
///
template<class T>
inline void BST<T>::m_LNR(void(*callback)(NodeBST<T> *, void *), NodeBST<T> *node, void *ptr)
{
	if (node == NULL) return;
	m_LNR(callback, node->left, ptr);
	callback(node, ptr);
	m_LNR(callback, node->right, ptr);
}
