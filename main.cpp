#include "Game.h"
#include <iostream>
#include <memory>
#include <array>

int main()
{
	Game myGame;
	while (myGame.isRunning())
	{
		myGame.update();
	}
	return 0;
}/*
#include <iostream>
#include <exception>
using namespace std;

class CBase { virtual void dummy() {} };
class CDerived : public CBase { int a; };

int main() {
	//try {
		CBase* pba = new CDerived;
		CBase* pbb = new CBase;
		CDerived* pd;

		pd = dynamic_cast<CDerived*>(pba);
		if (pd == 0) cout << "Null pointer on first type-cast" << endl;
		try
		{
			auto& pddd = dynamic_cast<CDerived&>(*pbb);
		}
		catch (std::bad_cast exp)
		{
			std::cout << "Caught bad cast\n";
		}

	//}
	//catch (exception& e) { cout << "Exception: " << e.what(); }
	return 0;
}*/