#ifndef PARSEOBJ_HPP
#define PARSEOBJ_HPP

#include "geometry.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>

Mesh getMeshFromObj(const std::string& filename);

#endif