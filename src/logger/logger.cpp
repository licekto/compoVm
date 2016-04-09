#include "logger/logger.h"

void log(const string& level, const string& what)
{
	stringstream oss;

	oss << level << "	" << what << "\"" << endl;

#ifdef _LOG
	ofstream log;
	log.open("log.txt", fstream::app);
	log << oss.str();
	log.close();
#endif
#ifdef _CERR
	cerr << oss.str();
#endif
}