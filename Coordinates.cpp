#include "Coordinates.h"
#include "Vector2D.h"
#include <cmath>

Coordinates::Coordinates( Vector2D const & vector2D ) : Coordinates( (int)std::round( vector2D.x ), (int)std::round( vector2D.y ) ) {}