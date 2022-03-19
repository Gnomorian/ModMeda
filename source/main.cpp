#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "Commandline.h"
#include "Command.h"

using namespace winrt;
using namespace Windows::Foundation;

int wmain(int argc, wchar_t* args[])
{
	init_apartment();
	Uri uri(L"http://aka.ms/cppwinrt");
	printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());
	Commandline cmd{ argc, args };
	makeCommandFromArgs(cmd)->execute();
}