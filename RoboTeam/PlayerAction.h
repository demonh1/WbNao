#pragma once

//КЛАСС ЗАПОЛНЯЕТСЯ ТАНЕЙ

enum Actions 
{
	Kick=0,
	MoveTo=1,
};
class PlayerAction
{
public:
	PlayerAction(void);
	~PlayerAction(void);
	bool MoveTo(float X, float Y);
	bool Kick(float X,float Y, float force);
	int ID;
};
