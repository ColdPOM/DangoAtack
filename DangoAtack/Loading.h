#pragma once
#include "Common.h"
#include "Sprite2D.h"

class Loading
{
public:
	Loading(void);
	~Loading(void);

	void Init();
	void Update();
	void Draw();


private:
	Sprite2D texture;
};

