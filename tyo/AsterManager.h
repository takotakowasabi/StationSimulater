#pragma once
#include <Siv3D.hpp>
#include "AsterNode.h"
#include <vector>
#include <queue>

/*
static bool AsterCompare(spAsterNode lhs, spAsterNode rhs) {
	if (lhs->estimateCost + lhs->trueCost == rhs->estimateCost + rhs->trueCost) return lhs->trueCost > rhs->trueCost;
	return lhs->estimateCost + lhs->trueCost > rhs->estimateCost + rhs->trueCost;
};
*/

class AsterManager {
public:
	static const int STATION_SIZE = 10;
	using stationMap = std::array < std::array<std::array<spAsterNode, STATION_SIZE>, STATION_SIZE>, STATION_SIZE>;

	explicit AsterManager(const Vec3& start, const Vec3& end, const stationMap& atation);
	std::vector<Vec3> getShortestRoot();

private:
	static int makeDistance(Vec3 lhs, Vec3 rhs);

	void openNode(int x, int y, int z, int shift, int cost = 1);

	//std::priority_queue<spAsterNode/*, std::vector<spAsterNode>, decltype(AsterCompare)*/> _openNodes;
	std::vector<spAsterNode> _openNodes;
	
	spAsterNode _nowNode;
	Vec3 _endPos;

	const stationMap& _stationMap;
};