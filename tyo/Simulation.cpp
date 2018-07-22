#include "Simulation.h"

Simulation::Simulation() :
	SceneManager<eScene, Paramater>::Scene(),
	_rng(Random(1, 99999)),
	_dist((STATION_SIZE - 1) / 2.0, STATION_SIZE / 4.0)
{
}

void Simulation::init()
{
	for (int i = 0; i < STATION_SIZE; i++) {
		for (int j = 0; j < STATION_SIZE; j++) {
			for (int k = 0; k < STATION_SIZE; k++) {
				_station[i][j][k] = std::make_shared<AsterNode>(Vec3(i, j, k));
			}
		}
	}

	_makeLoadFlameCount = 0;
	_endModeFlag = false;

	_homes.emplace_back(Random(0, STATION_SIZE - DEFAULT_HOME_TO_EXIT - 1),
		DEFAULT_FLOOR,
		Random(0, STATION_SIZE - DEFAULT_HOME_TO_EXIT - 1));

	_exits.emplace_back(_homes.front().x + DEFAULT_HOME_TO_EXIT,
		DEFAULT_FLOOR,
		_homes.front().z + DEFAULT_HOME_TO_EXIT
	);

	_station[_homes.front().x][DEFAULT_FLOOR][_homes.front().z]->blockType = HOME_NUMBER;
	_station[_exits.front().x][DEFAULT_FLOOR][_exits.front().y]->blockType = EXIT_NUMBER;

	_asterManagers.push_back(AsterManager(_homes.back(), _exits.back(), _station));

	Graphics3D::SetAmbientLight(ColorF(0.4, 0.2, 0.1));
	Graphics3D::SetAmbientLightForward(ColorF(0.4, 0.4, 0.4));

	_stopwatch.start();
}

void Simulation::update()
{
	//ClearPrint();
	//Println(_stopwatch.s());
	int nowTime = _stopwatch.ms();

	if (_stopwatch.s() < m_data->simulationTime) {
		++_makeLoadFlameCount;

		if (!_asterManagers.empty() && _makeLoadFlameCount >= 5) {
			_stopwatch.pause();
			_roots.emplace_back(_asterManagers.front().getShortestRoot(), nowTime);
			if (!_roots.back().positions.size()) _roots.pop_back();
			_stopwatch.start();
			_asterManagers.pop_front();
			_makeLoadFlameCount = 0;
		}

		for (int i = 0; i < int(nowTime / m_data->homeDevelopmentSpeed) - int(_homes.size()); i++) {
			_homes.emplace_back(getRandomPos());
			_station[_homes.back().x][_homes.back().y][_homes.back().z]->blockType = HOME_NUMBER;
			_asterManagers.push_back(AsterManager(_homes.back(), _exits.back(), _station));
		}

		for (int i = 0; i < int(nowTime / m_data->exitDevelopmentSpeed) - int(_exits.size()); i++) {
			_exits.emplace_back(getRandomPos());
			_station[_exits.back().x][_exits.back().y][_exits.back().z]->blockType = EXIT_NUMBER;
			_asterManagers.push_back(AsterManager(_homes.back(), _exits.back(), _station));
		}
	}
	else if (!_endModeFlag) {
		_endgui = GUI(GUIStyle::Default);
		_endgui.setTitle(L"シミュレーション終了");

		_endgui.add(L"record", GUIButton::Create(L"記録"));
		_endgui.addln(L"title", GUIButton::Create(L"設定に戻る"));

		_endModeFlag = true;
	}
	else {
		if (_endgui.button(L"title").pressed) {
			changeScene(eScene::title);
		}
		else if (_endgui.button(L"record").pressed) {
			int rootSize = 0;
			for (auto& root : _roots) {
				rootSize += root.positions.size();
			}

			CSVReader reader(L"records.csv");
			std::vector<std::vector<int>> reads(reader.rows);
			if (reader)
			{
				for (int i = 0; i < reads.size(); i++) {
					reads[i].resize(reader.columns(i));
					for (int j = 0; j < reads[i].size(); j++) {
						reads[i][j] = reader.get<int>(i, j);
					}
				}
				reader.close();
			}

			CSVWriter writer(L"records.csv");

			for (int i = 0; i < reads.size(); i++) {
				for (int j = 0; j < reads[i].size(); j++) {
					writer.write(reads[i][j]);
				}
				writer.nextLine();
			}

			writer.writeRow(
				m_data->homeDevelopmentSpeed,
				m_data->exitDevelopmentSpeed,
				m_data->makeLoadSpeed,
				m_data->simulationTime,
				_homes.size(),
				_exits.size(),
				rootSize
			);
			writer.close();

			_endgui.button(L"record").enabled = false;
		}
	}
	if (!_roots.empty()) {
		for (auto& root : _roots) {
			if (root.makedRootSize < root.positions.size() - 1) {
				root.makedRootSize = (nowTime - root.madeTime) / m_data->makeLoadSpeed;
				if (root.makedRootSize > root.positions.size() - 1) root.makedRootSize = root.positions.size() - 1;
			}
		}
	}
}

void Simulation::draw() const
{
	Graphics3D::FreeCamera();

	Plane(Vec3(- BOX_SIZE / 2, 0, - BOX_SIZE / 2), STATION_SIZE * BOX_SIZE).drawForward(HSV(0, 0.5, 0.5).toColorF(0.5));
	
	for (auto home : _homes) {
		Box(makeBoxVec(int(home.x), int(home.y), int(home.z)), BOX_SIZE).draw(HSV(210, 1.0, 1.0));
	}
	for (auto exit : _exits) {
		Box(makeBoxVec(int(exit.x), int(exit.y), int(exit.z)), BOX_SIZE).draw(HSV(140, 1.0, 1.0));
	}

	if (!_roots.empty()) {
		for (auto root : _roots) {
			for (int i = 0; i < int(root.makedRootSize); i++) {
				drawRoot(root.positions[i], root.positions[i + 1]);
			}
		}
	}
}

Vec3 Simulation::getRandomPos()
{
	int x = 0, y = 0, z = 0;
	while (true) {
		x = _dist(_rng);
		y = _dist(_rng);
		z = _dist(_rng);
		if (!isInField(x) || !isInField(y) || !isInField(z)) continue;
		if (_station[x][y][z]->blockType) continue;
		break;
	}
	return Vec3(x, y, z);
}
