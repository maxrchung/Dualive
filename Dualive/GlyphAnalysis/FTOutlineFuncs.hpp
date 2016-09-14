#ifndef FTOUTLINEFUNCS_HPP
#define FTOUTLINEFUNCS_HPP

#include <freetype/ftoutln.h>

int moveTo(const FT_Vector* to, void* user);
int lineTo(const FT_Vector* to, void* user);
int conicTo(const FT_Vector* control, const FT_Vector* to, void* user);
int cubicTo(const FT_Vector* control1, const FT_Vector* control2, const FT_Vector* to, void* user);

#endif//FTOUTLINEFUNCS_HPP