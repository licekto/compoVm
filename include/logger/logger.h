#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

#define INFO	"INFO"
#define DEBUG	"DEBUG"
#define	ERROR	"ERROR"

#define SOURCEINFO(what) __FILE__ << "::" << __func__ << "::" << __LINE__ << " -- \"" << what

#ifdef _USER_INFO
#	define USER_INFO(what) cout << what << endl
#else
#	define USER_INFO(what) while(0)
#endif

#ifdef _DEBUG
#	define TRACE(level, what) { \
	stringstream oStr; \
	oStr << SOURCEINFO(what) ; \
	log (level, oStr.str()); }
#else
#	define TRACE(level, what) while (0);
#endif

void log(const string& level, const string& w);