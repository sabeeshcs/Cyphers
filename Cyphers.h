#include <string>
#include <map>

using namespace std;
class Cyphers
{
private:
	Cyphers();
	~Cyphers();

public:

	static string MessageToKey(string sMessage, string sKey);
	static string KeyToMessage(string sMessage, string sKey);

	static void CreatePosToCharMap(map<int, char>& pPosToChar);
	static void CreateCharToPosMap(map<char, int>& pCharToPos);
	static bool GetKey(char sKey, int& iVal);
	static bool GetValue(int& iKey, char& sValue);
	static string FillKey(string& sKey, int iLength);

};

