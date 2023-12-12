#pragma once
/**singleton ���� ��ũ��. */
#define SINGLE(type) public:\
						static type* GetInstance()\
						{\
							static type core;\
							return &core;\
						}\
					private:\
							type();\
							~type(); 
						

#define fDT CTimeMgr::GetInstance()->GetDeltaTimef()
#define DT CTimeMgr::GetInstance()->GetDeltaTimed()