// ProcessReader.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
using std::string;
#include "..\SharedMemory.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SharedMemory& sm = SharedMemory::Instance();
	string szValue;
	bool bRet = sm.ReadSharedMemory("1",szValue);
	if(bRet)
	{
		printf("read value is %s",szValue.c_str());
	}
	sm.DeleteSharedMemory("1");
	getchar();
	return 0;
}
