#include "Loading.h"


Loading::Loading(void)
{
}


Loading::~Loading(void)
{
}


void Loading::Init(){
	texture.Load("texture/heart.dds");
	texture.setPos(WIN_W - texture.getWidth()*2, WIN_H - texture.getHeight()*2);
}


void Loading::Update(){
	texture.setRotate(texture.getRotate() + 10.0f);
}


void Loading::Draw(){
	texture.Draw();
}