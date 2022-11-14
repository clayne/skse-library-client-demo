#define DLL_EXPORTED __declspec(dllimport)

#include "MySkseLibraryExample.h"

#define DLL_EXPORTED __declspec(dllimport)

void InitializeLog() {
    // MySkse
	auto path = logger::log_directory();
	*path /= fmt::format("{}.log", SKSE::PluginDeclaration::GetSingleton()->GetName());
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	const auto level = spdlog::level::trace;
	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
	log->set_level(level);
	log->flush_on(level);
	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLog();
    logger::info("Initialize");
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            logger::info("Hello from CLIENT example hoping to use the Skse Library API");
            auto& thingy = MySkseLibraryExample::GetDemoSingleton();
            thingy.Add("Hello 2");
            thingy.Add("World 2");
            logger::info("The count is now: {}", thingy.GetCount());
            thingy.LogAll();
        }
    });
    return true;
}
