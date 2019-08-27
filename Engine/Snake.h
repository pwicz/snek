#pragma once

#include "Board.h"
#include "Location.h"
#include <assert.h>
#include <random>

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(const Location& in_loc, Color& in_c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		bool DoesColide(Location& in_loc) const;
		Location getLocation() const;
	private:
		Location loc;
		Color c;
	};
	
public:
	Snake(const Location& loc);
	void MoveBy();
	void Grow();
	void Draw(Board& brd) const;
	void ChangeNextMove(Location newNextMove);
	void ChangeBodyColor(std::mt19937& rng);
	bool CheckIfOnBorder(Board& brd) const;
	bool DoesColide(Location& loc) const;
	bool DoesColideWithHead(Location& loc) const;
	bool DoesHeadColideWithBody();
	Location GetNextHeadLocation();
	int GetEatenPoints() const;

private:
	static constexpr Color headColor = Colors::Yellow;
	Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 500;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	Location nextMove = {1, 0};
	Location lastMove = { 1, 0 };
	int eatenPoints = 0;
};