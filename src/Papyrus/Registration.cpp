#include "Registration.h"

#include "PapyrusMath.h"


namespace Papyrus
{
	auto Register() -> void
	{
		const auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(PapyrusMath::RegisterFuncs);
		logger::info("Registered math functions");
	}
}
