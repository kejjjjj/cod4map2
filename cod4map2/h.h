#pragma once

#ifndef hh_h
#define hh_h

#define CreateThreadArg(func, arg) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func, (LPVOID)arg, NULL, NULL);
#define CreateThreadMin(func) CreateThreadArg(func, NULL);

#pragma warning(disable: 26495)

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <psapi.h>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

//detours
#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

#include "koukut.h"

#endif