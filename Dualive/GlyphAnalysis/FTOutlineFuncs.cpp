#include "DecomposedValue.hpp"
#include "FTOutlineFuncs.hpp"

int moveTo(const FT_Vector* to, void* contoursPointer) {
	DecomposedOutline* contours = (DecomposedOutline*)contoursPointer;
	contours->push_back({ DecomposedValue(DecomposedValueType::Move, *to) });
	return 0;
}

int lineTo(const FT_Vector* to, void* contoursPointer) {
	DecomposedOutline* contours = (DecomposedOutline*)contoursPointer;
	contours->back().push_back(DecomposedValue(DecomposedValueType::Line, *to));
	return 0;
}

int conicTo(const FT_Vector* control, const FT_Vector* to, void* contoursPointer) {
	DecomposedOutline* contours = (DecomposedOutline*)contoursPointer;
	contours->back().push_back(DecomposedValue(DecomposedValueType::Conic, *control));
	contours->back().push_back(DecomposedValue(DecomposedValueType::Conic, *to));
	return 0;
}

int cubicTo(const FT_Vector* control1, const FT_Vector* control2, const FT_Vector* to, void* contourManagementPointer) {
	return 0;
}