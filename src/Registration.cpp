#include "Registration.h"


#include "PapyrusMath.h"


auto Papyrus::Register() -> void
{
	const auto papyrus = SKSE::GetPapyrusInterface();

	papyrus->Register(papyrusMath::RegisterFuncs);
	logger::info("Registered math functions");
}
