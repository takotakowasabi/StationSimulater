#include "Title.h"

void Title::init()
{
	gui = GUI(GUIStyle::Default);
	gui.setTitle(L"設定パラメータ");

	gui.addln(GUIText::Create(L"駅の発展シミュレーションを行います、"));
	gui.addln(GUIText::Create(L"パラメーターを入力してください。"));

	gui.add(GUIText::Create(L"ホームの発展速度(ms)："));
	gui.addln(L"homeDevelopmentSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"出口の発展速度(ms)："));
	gui.addln(L"exitDevelopmentSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"道路の生成時間(ms)："));
	gui.addln(L"makeLoadSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"シミュレーション時間(s)："));
	gui.addln(L"simulationTime", GUITextField::Create(8));

	gui.add(L"exit", GUIButton::Create(L"終了"));
	gui.addln(L"ok", GUIButton::Create(L"OK", false));

	gui.setCenter(Window::Center());
}

void Title::update()
{	
	int homeDevelopmentSpeed = Parse<int>(gui.textField(L"homeDevelopmentSpeed").text);
	int exitDevelopmentSpeed = Parse<int>(gui.textField(L"exitDevelopmentSpeed").text);
	int makeLoadSpeed = Parse<int>(gui.textField(L"makeLoadSpeed").text);
	int simulationTime = Parse<int>(gui.textField(L"simulationTime").text);

	if (gui.button(L"exit").pressed)
	{
		System::Exit();
	}
	else if (gui.button(L"ok").pressed)
	{
		m_data->homeDevelopmentSpeed = homeDevelopmentSpeed;
		m_data->exitDevelopmentSpeed = exitDevelopmentSpeed;
		m_data->makeLoadSpeed = makeLoadSpeed;
		m_data->simulationTime = simulationTime;
		changeScene(eScene::simulation);
	}

	gui.button(L"ok").enabled = false;
	if (homeDevelopmentSpeed && exitDevelopmentSpeed && makeLoadSpeed && simulationTime)
	{
		gui.button(L"ok").enabled = true;
	}

}

void Title::draw() const
{
}
