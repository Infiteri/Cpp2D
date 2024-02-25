#include "Logger.h"
#include <unordered_map>
#include "Platform/Platform.h"

// TODO: Refactor to classes
#include <iostream>
#include <cstdarg>

#define CEU_DEFINE_LOG_LEVEL(type, color) \
    levelToString[type] = #type;          \
    levelToColor[type] = Platform::color

namespace Core
{
    static bool Initialized = false;
    static std::unordered_map<std::string, Logger::LogCategory *> categories;
    static std::unordered_map<Logger::LoggingLevel, std::string> levelToString;
    static std::unordered_map<Logger::LoggingLevel, Platform::ConsoleColors> levelToColor;

    void Logger::Init()
    {
        if (Initialized)
            return;

        CEU_DEFINE_LOG_LEVEL(Info, Green);
        CEU_DEFINE_LOG_LEVEL(Warn, Yellow);
        CEU_DEFINE_LOG_LEVEL(Error, Red);
        CEU_DEFINE_LOG_LEVEL(Trace, Gray);
        CEU_DEFINE_LOG_LEVEL(Debug, Blue);

        DefineLogCategory("Core", CE_CORE_CATEGORY_NAME);
        DefineLogCategory("Client", CE_CLIENT_CATEGORY_NAME);

        Initialized = true;
    }

    void Logger::Shutdown()
    {
        if (!Initialized)
            return;

        Initialized = false;

        for (auto cat : categories)
            delete cat.second;
        categories.clear();
    }

    void Logger::Log(const std::string &catName, LoggingLevel level, const char *message, ...)
    {
        LogCategory *category = categories[catName];
        std::string logDescriptionString = levelToString[level];
        if (!category)
            return;

        char OutMessage[ce_LOGGER_MAX_MESSAGE_LENGTH];
        Platform::MemSet(OutMessage, 0, ce_LOGGER_MAX_MESSAGE_LENGTH);

        // Perform string pending
        __builtin_va_list arg_ptr;
        va_start(arg_ptr, message);
        vsnprintf(OutMessage, ce_LOGGER_MAX_MESSAGE_LENGTH, message, arg_ptr);
        va_end(arg_ptr);

        // Append levels
        char OutMessageWithLevels[ce_LOGGER_MAX_MESSAGE_LENGTH];
        Platform::MemSet(OutMessageWithLevels, 0, ce_LOGGER_MAX_MESSAGE_LENGTH);
        snprintf(OutMessageWithLevels, ce_LOGGER_MAX_MESSAGE_LENGTH, "[%s %s]: %s\n", category->Pending.c_str(), logDescriptionString.c_str(), OutMessage);

        Platform::SetConsoleColor(levelToColor[level]);
        Platform::Log(OutMessageWithLevels);
    }

    bool Logger::DefineLogCategory(const std::string &pending, const std::string &name)
    {
        if (categories[name] != nullptr)
            return false;

        categories[name] = new LogCategory;
        categories[name]->Name = name;
        categories[name]->Pending = pending;

        return true;
    }
}