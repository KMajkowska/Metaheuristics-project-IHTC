#pragma once

#include "CGameInfo.h"

/**
 * @brief Class used as na  interface to provide sessions
*/
class ISessionPoster
{
public:
	virtual void postSession() = 0;
};