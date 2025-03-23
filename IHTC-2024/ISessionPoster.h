#pragma once

#include "CObservable.h"
#include "CGameInfo.h"

class ISessionPoster
{
public:
	virtual void postSession() = 0;
};