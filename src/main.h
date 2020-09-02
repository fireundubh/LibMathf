#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"


extern "C" {
__declspec(dllexport) float GetPluginVersion();
};


namespace Version
{
	inline constexpr float VERSION = 0.1f;
}
