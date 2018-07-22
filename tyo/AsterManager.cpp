#include "AsterManager.h"
#include <algorithm>
#include <functional>

AsterManager::AsterManager(const Vec3& start, const Vec3& end, const stationMap& station):
	_endPos(end),
	_stationMap(station)
{
	for (auto stationMapPart : _stationMap) {
		for(auto stationMapPartPart : stationMapPart){
			for (auto node : stationMapPartPart) {
				node->status = NodeStatus::none;
			}
		}
	}

	_nowNode = _stationMap[start.x][start.y][start.z];
	_nowNode->status = NodeStatus::open;
	_nowNode->baseNode = nullptr;
	_nowNode->trueCost = 0;
	_nowNode->estimateCost = makeDistance(start, _endPos);
}

std::vector<Vec3> AsterManager::getShortestRoot()
{
	while (true) {
		openNode(_nowNode->position.x + 1, _nowNode->position.y, _nowNode->position.z, 1);
		openNode(_nowNode->position.x - 1, _nowNode->position.y, _nowNode->position.z, 0);
		openNode(_nowNode->position.x, _nowNode->position.y + 1, _nowNode->position.z, 3, 5);
		openNode(_nowNode->position.x, _nowNode->position.y - 1, _nowNode->position.z, 2, 5);
		openNode(_nowNode->position.x, _nowNode->position.y, _nowNode->position.z + 1, 5);
		openNode(_nowNode->position.x, _nowNode->position.y, _nowNode->position.z - 1, 4);

		std::sort(_openNodes.begin(), _openNodes.end());
		_nowNode->status = NodeStatus::closed;
		if (_openNodes.empty()) return std::vector<Vec3>();
		
		_nowNode = _openNodes.back();
		_openNodes.pop_back();
		if (_nowNode->estimateCost == 0) break;
	}

	std::vector<Vec3> ret;
	while (true) {
		ret.emplace_back(_nowNode->position);
		if (_nowNode->position != _endPos) _nowNode->blockType = 1;
		_nowNode = _nowNode->baseNode;
		if (_nowNode == nullptr) break;
	}
	
	//std::reverse(ret.begin(), ret.end());

	return ret;
}

int AsterManager::makeDistance(Vec3 lhs, Vec3 rhs)
{
	int ret = 0;
	ret += abs(lhs.x - rhs.x);
	ret += abs(lhs.y - rhs.y);
	ret += abs(lhs.z - rhs.z);
	return ret;
}

void AsterManager::openNode(int x, int y, int z, int shift, int cost)
{
	if (x < 0 || y < 0 || z < 0) return;
	if (x >= STATION_SIZE || y >= STATION_SIZE || z >= STATION_SIZE) return;

	spAsterNode node = _stationMap[x][y][z];
	if (!node->blockType < 0 ||(node->status != NodeStatus::none && node->position != _endPos)) return;

	node->baseNode = _nowNode;
	if (node->blockType >> shift == 0) node->trueCost = _nowNode->trueCost + cost;
	node->estimateCost = makeDistance(node->position, _endPos);
	node->status = NodeStatus::open;

	_openNodes.push_back(node);
}
