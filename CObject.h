#pragma once
#include"pch.h"
class CObject
{
	private:
		Vec2 m_Pos;
		Vec2 m_Scale;
	public:
		void SetPos(Vec2 pos) { m_Pos = pos; };
		void SetScale(Vec2 scale) { m_Scale = scale; };

		Vec2 GetPos() { return m_Pos; }
		Vec2 GetScale() { return m_Scale; }
	public:
		CObject();
		~CObject();
};

