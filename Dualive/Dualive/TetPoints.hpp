#ifndef TETPOINTS_HPP
#define TETPOINTS_HPP

// http://stackoverflow.com/questions/10411357/reuseing-enum-values-in-separate-enum-types
namespace TetPoints {
	// Used for accessing the points vector in a Tetrahedron
	enum TetPoints {
		// Top
		T = 0,
		// Left
		L,
		// Right
		R,
		// Center
		C,
		// Far
		F,
		Count
	};
}

#endif//TETRAHEDRONPOINTS_HPP