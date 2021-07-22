class Joystick
{
	static constexpr double MAX_SIZE = 1;
	static constexpr double MIN_SIZE = -1;
	double _value;
	double _gravity;
	double _dead;

	bool _willSnap;

	double _spaceFromMax() const;
	double _spaceFromMin() const;

	double _clampToMinMaxSize( double number ) const;
protected:
	/// @brief Preferrable to use pushValue(), but if you need to change the value directly, here it is. Still has clamp constraints (if you want to override them, honestly what are you even using this class for at this point?).
	/// @param value The new value to set.
	void setRawValue( double value );
	/// @brief Moves the value by push. Negative push to push the value down, positive up, e.t.c. Effectively is the same as setRawValue(getRawValue() + push).
	/// @param push The amount to push value by.
	void pushValue( double push );
public:

	void updateGravity();

	double getValue() const;
	double getRawValue() const;

	double getDead() const;
	double getGravity() const;
	bool getWillSnap() const;

	void setDead( double value );
	void setGravity( double value );
	void setWillSnap( bool value );
};