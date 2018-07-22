#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "eScene.h"
#include "Paramater.h"
#include <array>
#include <vector>
#include <queue>
#include "AsterManager.h"

class Simulation : public SceneManager<eScene, Paramater>::Scene
{
public:
	static const int STATION_SIZE = 10;
	static const int DEFAULT_HOME_TO_EXIT = 5;
	static const int DEFAULT_FLOOR = 5;
	static const int HOME_NUMBER = -1;
	static const int EXIT_NUMBER = -2;
	static const int BOX_SIZE = 8;

	static const int ROOT_BOX_WIDTH = 2;

	Simulation();

	void init() override;
	void update() override;
	void draw() const override;

private:
	GUI _endgui;

	Stopwatch _stopwatch;
	RNG _rng;
	NormalDistribution _dist;

	AsterManager::stationMap _station;
	std::vector<Vec3> _homes;
	std::vector<Vec3> _exits;

	int _makeLoadFlameCount;
	bool _endModeFlag;

	struct Root {
		Root(std::vector<Vec3> poss, int nowtime) : positions(poss), makedRootSize(0), madeTime(nowtime) {};
		std::vector<Vec3> positions;
		size_t makedRootSize;
		int madeTime;
	};
	std::deque<Root> _roots;
	std::deque<AsterManager> _asterManagers;

	Vec3 getRandomPos();

	static bool isInField(int i) {
		return i >= 0 && i < STATION_SIZE;
	}

	static Vec3 makeBoxVec(int i, int j, int k) {
		return Vec3(((i - STATION_SIZE / 2) * BOX_SIZE), ((j - STATION_SIZE / 2) * BOX_SIZE), ((k - STATION_SIZE / 2) * BOX_SIZE));
	}
	static void drawRoot(Vec3 first, Vec3 end) {
		Vec3 firstVec = makeBoxVec(first.x, first.y, first.z);
		Vec3 endVec = makeBoxVec(end.x, end.y, end.z);

		Box((firstVec + endVec) / 2 , absVec3(firstVec - endVec) + Vec3(2, 2, 2)).draw(HSV(70, 1.0, 1.0));
		Box(firstVec, Vec3(2, 2, 2)).draw(HSV(70, 1.0, 1.0));
		Box(endVec, Vec3(2, 2, 2)).draw(HSV(70, 1.0, 1.0));
	}
	static Vec3 absVec3(Vec3 vec){
		return Vec3(abs(vec.x), abs(vec.y), abs(vec.z));
	}
};