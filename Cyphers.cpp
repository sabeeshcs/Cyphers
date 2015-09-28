#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <locale>    
#include "Cyphers.h"


Cyphers::Cyphers()
{

}


Cyphers::~Cyphers()
{
}

void Cyphers::CreateCharToPosMap(map<char, int>& pCharToPos)
{
	pCharToPos['A'] = 1;
	pCharToPos['B'] = 2;
	pCharToPos['C'] = 3;
	pCharToPos['D'] = 4;
	pCharToPos['E'] = 5;
	pCharToPos['F'] = 6;
	pCharToPos['G'] = 7;
	pCharToPos['H'] = 8;
	pCharToPos['I'] = 9;
	pCharToPos['J'] = 10;
	pCharToPos['K'] = 11;
	pCharToPos['L'] = 12;
	pCharToPos['M'] = 13;
	pCharToPos['N'] = 14;
	pCharToPos['O'] = 15;
	pCharToPos['P'] = 16;
	pCharToPos['Q'] = 17;
	pCharToPos['R'] = 18;
	pCharToPos['S'] = 19;
	pCharToPos['T'] = 20;
	pCharToPos['U'] = 21;
	pCharToPos['V'] = 22;
	pCharToPos['W'] = 23;
	pCharToPos['X'] = 24;
	pCharToPos['Y'] = 25;
	pCharToPos['Z'] = 26;
}

void Cyphers::CreatePosToCharMap(map<int, char>& pPosToChar)
{
	
		pPosToChar[1] = 'A';
		pPosToChar[2] = 'B';
		pPosToChar[3] = 'C';
		pPosToChar[4] = 'D';
		pPosToChar[5] = 'E';
		pPosToChar[6] = 'F';
		pPosToChar[7] = 'G';
		pPosToChar[8] = 'H';
		pPosToChar[9] = 'I';
		pPosToChar[10] = 'J';
		pPosToChar[11] = 'K';
		pPosToChar[12] = 'L';
		pPosToChar[13] = 'M';
		pPosToChar[14] = 'N';
		pPosToChar[15] = 'O';
		pPosToChar[16] = 'P';
		pPosToChar[17] = 'Q';
		pPosToChar[18] = 'R';
		pPosToChar[19] = 'S';
		pPosToChar[20] = 'T';
		pPosToChar[21] = 'U';
		pPosToChar[22] = 'V';
		pPosToChar[23] = 'W';
		pPosToChar[24] = 'X';
		pPosToChar[25] = 'Y';
		pPosToChar[26] = 'Z';
}

bool Cyphers::GetKey(char sKey, int& iVal)
{
	bool bRet = false;
	std::locale loc;
	static map<char, int> pCharToPos;

	CreateCharToPosMap( pCharToPos);

	sKey = std::toupper(sKey, loc);

	if (pCharToPos.find(sKey) == pCharToPos.end())
	{
		iVal = 0;
	}
	else
	{
		iVal = pCharToPos[sKey];
		bRet = true;
	}

	return bRet;

}

bool Cyphers::GetValue(int& iKey, char& sValue )
{
	bool bRet = false;
	static map<int, char> pPosToChar;

	CreatePosToCharMap(pPosToChar);

	if ( pPosToChar.find(iKey) == pPosToChar.end())
	{
		sValue = ' ';
	}
	else
	{
		sValue = pPosToChar[iKey];
		bRet = true;
	}

	return bRet;

}

string Cyphers::MessageToKey(string sMessage, string sKey)
{
	string sRet = "";
	vector<int> pMessage;
	vector<int> pKey;
	vector<int> pRes;
	std::locale loc;

	int iVal = 0;
	int iLength = 0;
	
	//remove all space form a string
	sMessage.erase(std::remove(sMessage.begin(), sMessage.end(), ' '), sMessage.end());


	iLength = sMessage.length();
	//message to integer
	for (std::string::iterator it = sMessage.begin(); it != sMessage.end(); ++it) {
		if (GetKey((*it), iVal) == true)
		{
			pMessage.push_back(iVal);
		}
	}

	//Fill the key
	std::string sNewKey;
	sNewKey = FillKey(sKey, iLength);

	iVal = 0;
	//key to integer
	for (std::string::iterator it = sNewKey.begin(); it != sNewKey.end(); ++it) {
		if (GetKey( (*it), iVal) == true)
			pKey.push_back(iVal);
	}


	iVal = 0;

	for (int iCount = 0; iCount < iLength; iCount++)
	{
		iVal = ((pMessage[iCount] + pKey[iCount]) % 26) + 1;
		pRes.push_back(iVal);
	}

	char sVal;
	for ( vector<int>::iterator it = pRes.begin(); it != pRes.end(); it++ )
	{
		if (GetValue(*it, sVal) == true)
		{
			sRet += (sRet.length() == 0  ? sVal : std::tolower(sVal, loc));
		}
	}

	
	return sRet;
}

string Cyphers::FillKey(string& sKey, int iLength)
{
	string sRet = "";
	int iPos = 0;
	while (true)
	{
		if (sRet.length() >= iLength)
			break;
		else
		{
			if (iPos > sKey.length())
				iPos = 0;
			sRet += sKey.substr(iPos++, 1);

		}
	}

	return sRet;
}


string Cyphers::KeyToMessage(string sMessage, string sKey)
{
	string sRet = "";
	vector<int> pMessage;
	vector<int> pKey;
	vector<int> pRes;
	std::locale loc;

	int iVal = 0;
	int iLength = 0;

	//remove all space form a string
	sMessage.erase(std::remove(sMessage.begin(), sMessage.end(), ' '), sMessage.end());

	iLength = sMessage.length();
	//message to integer
	for (std::string::iterator it = sMessage.begin(); it != sMessage.end(); ++it) {
		if (GetKey((*it), iVal) == true)
		{
			cout << *it << iVal<<endl;

			pMessage.push_back(iVal);
		}
	}

	//Fill the key
	std::string sNewKey;
	sNewKey = FillKey(sKey, iLength);

	iVal = 0;
	//key to integer
	for (std::string::iterator it = sNewKey.begin(); it != sNewKey.end(); ++it) {
		if (GetKey((*it), iVal) == true)
			pKey.push_back(iVal);
	}


	iVal = 0;
	for (int iCount = 0; iCount < iLength; iCount++)
	{
		iVal = (pMessage[iCount] - pKey[iCount]);
		if (iVal <= 0)
			iVal = (26 + iVal) - 1;
		else
			iVal = (iVal % 26) - 1;

		pRes.push_back(iVal);
	}

	char sVal;
	for (vector<int>::iterator it = pRes.begin(); it != pRes.end(); it++)
	{
		if (GetValue(*it, sVal) == true)
		{
			sRet += (sRet.length() == 0 ? sVal : std::tolower(sVal, loc));
		}
	}


	return sRet;
}
