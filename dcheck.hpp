#pragma once


#include <string>
#include <sstream>
#include <stdexcept>

#ifndef DCHECK
#ifdef NDEBUG
#define DCHECK_(x,y,z)
#define DCHECK(x) 
#define DCHECK_EQ(x, y) 
#define DCHECK_NE(x, y) 
#define DCHECK_LE(x, y) 
#define DCHECK_LT(x, y) 
#define DCHECK_GE(x, y) 
#define DCHECK_GT(x, y) 
#else//NDEBUG
#define DCHECK_(x,y,z) \
  if (!(x)) throw std::runtime_error(std::string(" in file ") + __FILE__ + ':' + std::to_string(__LINE__) + (" the check failed: " #x) + ", we got " + std::to_string(y) + " vs " + std::to_string(z))
#define DCHECK(x) \
  if (!(x)) throw std::runtime_error(std::string(" in file ") + __FILE__ + ':' + std::to_string(__LINE__) + (" the check failed: " #x))
#define DCHECK_EQ(x, y) DCHECK_((x) == (y), x,y)
#define DCHECK_NE(x, y) DCHECK_((x) != (y), x,y)
#define DCHECK_LE(x, y) DCHECK_((x) <= (y), x,y)
#define DCHECK_LT(x, y) DCHECK_((x) < (y) ,x,y)
#define DCHECK_GE(x, y) DCHECK_((x) >= (y),x,y )
#define DCHECK_GT(x, y) DCHECK_((x) > (y) ,x,y)
#endif //NDEBUG
#endif //DCHECK
