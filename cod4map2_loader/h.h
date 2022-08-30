#pragma once

#ifndef hh_h
#define hh_h


#pragma warning(disable: 26495)

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <TlHelp32.h>

namespace fs = std::filesystem;

#include "filesystem.h"
#include "utils.h"

#include "cod4map2_loader.h"
#endif