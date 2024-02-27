#pragma once

#include "Base.h"
#include <string>

#define CE_CORE_CATEGORY_NAME "Core_Category"
#define CE_CLIENT_CATEGORY_NAME "Client_Category"
#define ce_LOGGER_MAX_MESSAGE_LENGTH 32000
#define CE_ENABLE_LOGGING 1

namespace Core
{
    /// @brief Static class used for logging
    class CE_API Logger
    {
    public:
        Logger(){};
        ~Logger(){};

        enum LoggingLevel
        {
            Info,
            Warn,
            Error,
            Trace,
            Debug,
        };

        struct LogCategory
        {
            std::string Pending;
            std::string Name;
        };

        static void Init();
        static void Shutdown();

        static void Log(const std::string &catName, LoggingLevel level, const char *message, ...);

        /// @brief Will define a new log category.
        /// @param pending The pending. ((PENDING LEVEL): MESSAGE)
        /// @param name The name of the category, used when referencing categories.
        /// @return True if added, otherwise false. (Will false if a category under this name exists already)
        static bool DefineLogCategory(const std::string &pending, const std::string &name);
    };
} // namespace Core

#define CE_CORE_ERROR(message, ...) Core::Logger::Log(CE_CORE_CATEGORY_NAME, Core::Logger::Error, message, ##__VA_ARGS__)
#define CE_ERROR(message, ...) Core::Logger::Log(CE_CLIENT_CATEGORY_NAME, Core::Logger::Error, message, ##__VA_ARGS__)

#if CE_ENABLE_LOGGING == 1
#define CE_CORE_INFO(message, ...) Core::Logger::Log(CE_CORE_CATEGORY_NAME, Core::Logger::Info, message, ##__VA_ARGS__)
#define CE_CORE_WARN(message, ...) Core::Logger::Log(CE_CORE_CATEGORY_NAME, Core::Logger::Warn, message, ##__VA_ARGS__)
#define CE_CORE_TRACE(message, ...) Core::Logger::Log(CE_CORE_CATEGORY_NAME, Core::Logger::Trace, message, ##__VA_ARGS__)
#define CE_CORE_DEBUG(message, ...) Core::Logger::Log(CE_CORE_CATEGORY_NAME, Core::Logger::Debug, message, ##__VA_ARGS__)
#define CE_INFO(message, ...) Core::Logger::Log(CE_CLIENT_CATEGORY_NAME, Core::Logger::Info, message, ##__VA_ARGS__)
#define CE_WARN(message, ...) Core::Logger::Log(CE_CLIENT_CATEGORY_NAME, Core::Logger::Warn, message, ##__VA_ARGS__)
#define CE_TRACE(message, ...) Core::Logger::Log(CE_CLIENT_CATEGORY_NAME, Core::Logger::Trace, message, ##__VA_ARGS__)
#define CE_DEBUG(message, ...) Core::Logger::Log(CE_CLIENT_CATEGORY_NAME, Core::Logger::Debug, message, ##__VA_ARGS__)
#define CE_LOG(category, level, message, ...) Core::Logger::Log(category, Core::Logger::level, message, ##__VA_ARGS__)
#else
#define CE_CORE_INFO(message, ...)
#define CE_CORE_WARN(message, ...)
#define CE_CORE_TRACE(message, ...)
#define CE_CORE_DEBUG(message, ...)
#define CE_INFO(message, ...)
#define CE_WARN(message, ...)
#define CE_TRACE(message, ...)
#define CE_DEBUG(message, ...)
#define CE_LOG(category, level, message, ...)
#endif

#define CE_DEFINE_LOG_CATEGORY(pending, name) Core::Logger::DefineLogCategory(pending, name)