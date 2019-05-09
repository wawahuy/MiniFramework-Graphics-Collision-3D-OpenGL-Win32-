#include "FunctionSystem.h"


namespace yuh {


	bool SYSTEM_API CheckASCIIAZaz_(const char & c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c=='_';
	}

	std::string SYSTEM_API GlslCodeReplaceVarName(const std::string & code, std::map<std::string, std::string>& replaceVar)
	{
		std::string newCode = code;

		for (auto key = replaceVar.begin(); key != replaceVar.end(); key++) {
			std::string	 value   = key->first;
			std::string	 change	 = key->second;
			unsigned int lenKey  = value.length();
			unsigned int pos;

			std::string currentCode = "";
			std::string cutCode = newCode;

			while ((pos = cutCode.find(value)) != std::string::npos) {


				if ( (pos != 0 && CheckASCIIAZaz_(cutCode[pos-1])) ||
					 (pos + lenKey < cutCode.length() && CheckASCIIAZaz_(cutCode[pos+lenKey]))) {
					currentCode += cutCode.substr(0, pos + lenKey);
				}
				else {
					currentCode += cutCode.substr(0, pos) + change;
				}
				
				cutCode.erase(cutCode.begin(), cutCode.begin() + pos + lenKey);
			}

			newCode = currentCode + cutCode;
		}

		return newCode;
	}

}
