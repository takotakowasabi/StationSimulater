#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "eScene.h"
#include "Paramater.h"

class Title : public SceneManager<eScene, Paramater>::Scene
{
public:
	void init() override;
	void update() override;
	void draw() const override;

private:
	GUI gui;

};