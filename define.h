#pragma once
/**singleton ���� ��ũ��. */
#define SINGLE(type) public:\
static type* GetInstance()\
{\
	static type core;\
	return &core;\
}