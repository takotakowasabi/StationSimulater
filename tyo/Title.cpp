#include "Title.h"

void Title::init()
{
	gui = GUI(GUIStyle::Default);
	gui.setTitle(L"�ݒ�p�����[�^");

	gui.addln(GUIText::Create(L"�w�̔��W�V�~�����[�V�������s���܂��A"));
	gui.addln(GUIText::Create(L"�p�����[�^�[����͂��Ă��������B"));

	gui.add(GUIText::Create(L"�z�[���̔��W���x(ms)�F"));
	gui.addln(L"homeDevelopmentSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"�o���̔��W���x(ms)�F"));
	gui.addln(L"exitDevelopmentSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"���H�̐�������(ms)�F"));
	gui.addln(L"makeLoadSpeed", GUITextField::Create(8));

	gui.add(GUIText::Create(L"�V�~�����[�V��������(s)�F"));
	gui.addln(L"simulationTime", GUITextField::Create(8));

	gui.add(L"exit", GUIButton::Create(L"�I��"));
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
