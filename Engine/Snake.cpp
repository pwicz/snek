#include "Snake.h"
#include "Location.h"

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy()
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(nextMove);
	lastMove = nextMove;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		segments[nSegments].InitBody(segments[nSegments-1].getLocation(), bodyColor);
		nSegments++;
	}

	eatenPoints++;
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
}

bool Snake::CheckIfOnBorder(Board& brd) const
{
	return brd.DoesColideWithBorder(segments[0].getLocation());
}

void Snake::ChangeNextMove(Location newNextMove)
{
	assert(abs(newNextMove.x) + abs(newNextMove.y) == 1);

	if (!((lastMove.x == newNextMove.x * -1) || (lastMove.y == newNextMove.y * -1)))
	{
		nextMove = newNextMove;
	}
	
}

void Snake::ChangeBodyColor(std::mt19937& rng)
{
	std::uniform_int_distribution<int> colorDist(150, 255);
	Color c = { 0, 0, 0 };
	c.SetG(colorDist(rng));
	bodyColor = c;
}

bool Snake::DoesColide(Location& loc) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].DoesColide(loc)) {
			return true;
		}
	}
	return false;
}

bool Snake::DoesColideWithHead(Location& loc) const
{
	return segments[0].DoesColide(loc);
}

bool Snake::DoesHeadColideWithBody()
{
	if (nSegments < 3)
		return false;

	bool colide = false;
	for (int i = 1; i < nSegments-1; i++) {
		if (segments[i].DoesColide(GetNextHeadLocation())) {
			colide = true;
			break;
		}
	}
	return colide;
}

Location Snake::GetNextHeadLocation()
{
	Location loc = segments[0].getLocation();
	loc.Add(nextMove);
	return loc;
}

int Snake::GetEatenPoints() const
{
	return eatenPoints;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Location& in_loc, Color& in_c)
{
	c = in_c;
	loc = in_loc;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

bool Snake::Segment::DoesColide(Location& in_loc) const
{
	return loc == in_loc;
}

Location Snake::Segment::getLocation() const
{
	return loc;
}
