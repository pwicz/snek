#pragma once

class Location
{
public:
	bool operator==(const Location& rhs) const {
		if (x == rhs.x && y == rhs.y)
			return true;
		else
			return false;
	}
	void Add(const Location& val) {
		x += val.x;
		y += val.y;
	}
	int x;
	int y;
};