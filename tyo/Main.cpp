#include "Define.h"
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "eScene.h"
#include "Paramater.h"
#include "Title.h"
#include "Simulation.h"

void Main()
{
	Window::SetTitle(L"Station SImulater");
	Window::Resize(Define::WIN_W, Define::WIN_H);

	SceneManager<eScene, Paramater> manager;

	manager.add<Title>(eScene::title);
	manager.add<Simulation>(eScene::simulation);

	manager.init(eScene::title);

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
