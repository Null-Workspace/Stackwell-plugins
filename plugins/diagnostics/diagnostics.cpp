#include <stackwell/plugin_api.h>

#include <string>
#include <thread>

namespace
{
    const StackwellHostApi* g_host = nullptr;

    const char* platform_name()
    {
#if defined(_WIN32)
        return "Windows";
#elif defined(__APPLE__)
        return "macOS";
#elif defined(__linux__)
        return "Linux";
#else
        return "Unknown";
#endif
    }

    const char* architecture_name()
    {
#if defined(_M_X64) || defined(__x86_64__)
        return "x86_64";
#elif defined(_M_ARM64) || defined(__aarch64__)
        return "ARM64";
#elif defined(_M_IX86) || defined(__i386__)
        return "x86";
#else
        return "unknown";
#endif
    }

    void log_info(const std::string& message)
    {
        if (g_host != nullptr && g_host->log_info != nullptr)
        {
            g_host->log_info(message.c_str());
        }
    }

    int STACKWELL_PLUGIN_CALL initialize(const StackwellHostApi* host)
    {
        if (host == nullptr ||
            host->api_version != STACKWELL_PLUGIN_API_VERSION ||
            host->struct_size < sizeof(StackwellHostApi) ||
            host->log_info == nullptr)
        {
            return 1;
        }

        g_host = host;

        const unsigned int logical_cores =
            std::thread::hardware_concurrency();

        log_info("Diagnostics plugin initialized.");
        log_info(std::string("Platform: ") + platform_name());
        log_info(std::string("Architecture: ") + architecture_name());
        log_info(
            std::string("Pointer width: ") +
            std::to_string(sizeof(void*) * 8) +
            " bit"
        );
        log_info(
            std::string("C++ language level: ") +
            std::to_string(__cplusplus)
        );
        log_info(
            std::string("Logical processor count: ") +
            (logical_cores == 0
                ? std::string("unavailable")
                : std::to_string(logical_cores))
        );

#if defined(_MSC_VER)
        log_info(
            std::string("Compiler: MSVC ") +
            std::to_string(_MSC_VER)
        );
#elif defined(__clang__)
        log_info(
            std::string("Compiler: Clang ") +
            __clang_version__
        );
#elif defined(__GNUC__)
        log_info(
            std::string("Compiler: GCC ") +
            __VERSION__
        );
#else
        log_info("Compiler: unknown");
#endif

        return 0;
    }

    void STACKWELL_PLUGIN_CALL shutdown()
    {
        log_info("Diagnostics plugin stopped.");
        g_host = nullptr;
    }

    const StackwellPluginDescriptor DESCRIPTOR{
        sizeof(StackwellPluginDescriptor),
        STACKWELL_PLUGIN_API_VERSION,
        "Diagnostics",
        "0.1.0",
        initialize,
        shutdown,
        "NULL.WORKSPACE",
        "Reports basic host runtime and build information to the Stackwell log.",
        "0.1.0"
    };
}

extern "C" STACKWELL_PLUGIN_EXPORT
const StackwellPluginDescriptor*
STACKWELL_PLUGIN_CALL stackwell_plugin_query(void)
{
    return &DESCRIPTOR;
}
