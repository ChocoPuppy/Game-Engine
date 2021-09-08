#pragma once
#include <utility>
struct Vector2D : std::pair<double, double>
{
	constexpr Vector2D( double x = 0, double y = 0 ) : std::pair<double, double>{ x,y } {}

	double const & x() const;
	double & x();
	double const & y() const;
	double & y();

	float magnitude() const;
	Vector2D normalize() const;

	Vector2D & operator+=( Vector2D const & rhs );
	Vector2D & operator-=( Vector2D const & rhs );
	Vector2D & operator*=( float rhs );
	Vector2D & operator/=( float rhs );

	/// @brief This non-assign operator isn't a friend like the others because it's sided (If you swap the two inputs to the opposite sides of the operator the output will change)
	/// @param rhs The reason why this function only has one paramter is due to the linker only checking the left hand side (or, if that fails, global namespace overrides, which is what those friend functions are) for relavent overrides, thus meaning you can't do float / Vector2D (since that results in a different output than Vector2D / float).
	/// @return A copy of this with all values divided by rhs.
	Vector2D operator/( float rhs );

	friend Vector2D operator+( Vector2D lhs, Vector2D const & rhs );
	friend Vector2D operator-( Vector2D lhs, Vector2D const & rhs );
	friend Vector2D operator-( Vector2D lhs );

	/// @brief An unsided non-assigning multiplier.
	/// @detail The compiler, when reading operators, doesn't consider arguments in any specific order (so writing float * Vector2D is exactly the same as writing Vector2D * float to the compiler). When interpreting operators, it considered operator overrides of the lhs first if the lhs has a valid override, it'll call lhs.operator*(rhs), if the lhs has no valid operator overrides, then it considers global operator overrides, however it never tries to find any overrides in the rhs, so even if the right hand symbol has a perfectly valid operator override, it will never call rhs.operator*(lhs). As of such, by writing this as a friend function (friend functions are actually global unless specified otherwise and only connects to the class it's in in that it can access private members, so this function can't actually be called via Vector2D.operator*())
	/// @param lhs
	/// @param rhs
	/// @return a Vector2D with all values multiplied by rhs.
	friend Vector2D operator*( Vector2D lhs, float rhs );
	//	friend Vector2D operator/( Vector2D lhs, float rhs );
};