#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>

#include <glad/glad.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// For printing out the current file and line number                         //
///////////////////////////////////////////////////////////////////////////////
#include <sstream>

template <typename T>
std::string NumberToString(T x)
{
	std::ostringstream ss;
	ss << x;
	return ss.str();
}

#define GET_FILE_LINE (std::string(__FILE__) + ":" + NumberToString(__LINE__)).c_str()
///////////////////////////////////////////////////////////////////////////////

class Statics {
public:
	static Statics& Instance()
	{
		static Statics m_instance; //properly instantiated on first use, destroyed on 2nd and after.
		return m_instance;
	}

private:
	Statics() {}

public:
	//ensure that no copies ever get made.
	Statics(Statics const&) = delete;
	void operator=(Statics const&) = delete;

	///////////////////////////////////////////////////////////////////////////////
	//functions

	const char* errorString(GLenum err);

	char* textFileRead(const char* fn);

	void checkError(const char* str);
};



