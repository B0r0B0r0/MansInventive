#pragma once
#include <string>
using namespace std;

class Loger
{
private:
	static Loger* instance;
	Loger() {}
	~Loger() {}

public:
	static Loger& getInstance();
	static void deleteInstance();
	void log(string str);
	void showLog();
};

