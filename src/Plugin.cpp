#include "MySkseLibraryExample.h"

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

struct Whatever {
    public:
    std::string text;
};

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLog();
    logger::info("Initialize ?");
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        logger::info("Message Type {}", event->type);

        SKSE::GetMessagingInterface()->RegisterListener("MySkseLibraryExample", [](SKSE::MessagingInterface::Message* event){
            logger::info("MESSAGE FROM THE MOD! {}", event->type);
            logger::info("It should be a singleton...");
            MySkseLibraryExample::MyDemoSingleton* singleton = (MySkseLibraryExample::MyDemoSingleton*) event->data;
            // auto* singleton = static_cast<MySkseLibraryExample::MyDemoSingleton*>(event->data);
            logger::info("There are X items? {}", singleton->GetCount());
            singleton->Add("Hello?");
            logger::info("There are X items? {}", singleton->GetCount());
        });

auto* plugin = SKSE::PluginDeclaration::GetSingleton();
auto name = plugin->GetName();
logger::info("MY NAME IS '{}'", name);

        auto* whatevs = new Whatever();
        SKSE::GetMessagingInterface()->Dispatch(1234, whatevs, sizeof(whatevs), "MySkseLibraryExample");
        SKSE::GetMessagingInterface()->Dispatch(1234, whatevs, sizeof(whatevs), nullptr);

    //     // if (event->type == SKSE::MessagingInterface::kDataLoaded) {
    //     //     logger::info("Hello from CLIENT example hoping to use the Skse Library API");
    //     //     // int something = MySkseLibraryExample::BasicTest();
    //     //     // logger::info("Can we {}?", something);
    //     //     // auto& thingy = MySkseLibraryExample::GetDemoSingleton();
    //     //     // thingy.Add("Hello 2");
    //     //     // thingy.Add("World 2");
    //     //     // logger::info("The count is now: {}", thingy.GetCount());
    //     //     // thingy.LogAll();
    //     // } else if (event->type == 6969) {
    //     //     logger::info("Ah! the CLIENT got 6969!");
    //     // }
    });
    return true;
}
