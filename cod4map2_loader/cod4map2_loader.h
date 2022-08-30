#pragma once

#ifndef maploader
#define maploader

namespace cod4map
{
	bool OpenCoD4Map(int argc, char* argv[]);
	void FixArgumentPaths(int argc, char* argv[], std::string& out);

}

#endif