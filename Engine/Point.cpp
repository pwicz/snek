#include "Point.h"

void Point::Respawn(Location in_loc)
{
	loc = in_loc;
}

void Point::Draw(Board& brd, Color c)
{
	brd.DrawCell(loc, c);
	// yesss
}

Location Point::GetLocation() const
{
	return loc;
}
