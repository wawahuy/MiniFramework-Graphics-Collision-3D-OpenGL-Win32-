#pragma once
#include "Export.h"
#include <vector>
#include <string>
#include <map>

namespace yuh {

	typedef std::pair<std::string, std::string> GLSLCodeListName;

	template<class T, size_t num>
	void CopyArrayToVector(std::vector<T> &out, const T (&cp)[num]) {
		out.resize(num);
		memcpy(&out[0], cp, sizeof(cp));
	}


	/* Char in A->Z a->z and _
	 *
	 */
	bool SYSTEM_API CheckASCIIAZaz_(const char &c);

	/* Change code update name var  in glsl code
	 *
	 */
	std::string SYSTEM_API GlslCodeReplaceVarName(const std::string &code, std::map<std::string, std::string>& replaceVar);

	template<size_t num>
	std::string GlslCodeReplaceVarName(const std::string &code, const GLSLCodeListName (&replaceVar)[num]) {
		std::map<std::string, std::string> m;
		for (int i = 0; i < num; i++) m.insert(replaceVar[i]);
		return GlslCodeReplaceVarName(code, m);
	}

}