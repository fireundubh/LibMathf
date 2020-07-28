#include "version.h"
#include "main.h"
#include "Registration.h"


extern "C" bool DLLEXPORT SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	try
	{
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory() / "Mathf.log"sv;
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true);
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
		log->set_level(spdlog::level::trace);
#else
		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::warn);
#endif

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

		logger::info("Mathf v{}"sv, MATH_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "Mathf";
		a_info->version = MATH_VERSION_MAJOR;

		if (a_skse->IsEditor())
		{
			logger::critical("Loaded in editor, marking as incompatible"sv);
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver < SKSE::RUNTIME_1_5_39)
		{
			logger::critical("Unsupported runtime version {}", ver.GetString());
			return false;
		}
	}
	catch (const std::exception& e)
	{
		logger::critical(e.what());
		return false;
	}
	catch (...)
	{
		logger::critical("caught unknown exception"sv);
		return false;
	}

	return true;
}


extern "C" bool DLLEXPORT SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	try
	{
		logger::info("Mathf loaded");

		if (!SKSE::Init(a_skse))
		{
			return false;
		}

		Papyrus::Register();
	}
	catch (const std::exception& e)
	{
		logger::critical(e.what());
		return false;
	}
	catch (...)
	{
		logger::critical("caught unknown exception"sv);
		return false;
	}

	return true;
}


extern "C" float DLLEXPORT __declspec(dllexport) GetPluginVersion()
{
	return Version::version;
}
