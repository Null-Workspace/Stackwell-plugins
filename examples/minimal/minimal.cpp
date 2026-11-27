#include <stackwell/plugin_api.h>

namespace
{
    const StackwellHostApi* g_host = nullptr;

    int STACKWELL_PLUGIN_CALL initialize(const StackwellHostApi* host)
    {
        if (host == nullptr ||
            host->api_version != STACKWELL_PLUGIN_API_VERSION ||
            host->struct_size < sizeof(StackwellHostApi))
        {
            return 1;
        }

        g_host = host;

        if (g_host->log_info != nullptr)
        {
            g_host->log_info("Minimal example plugin initialized.");
        }

        return 0;
    }

    void STACKWELL_PLUGIN_CALL shutdown()
    {
        if (g_host != nullptr && g_host->log_info != nullptr)
        {
            g_host->log_info("Minimal example plugin stopped.");
        }

        g_host = nullptr;
    }

    const StackwellPluginDescriptor DESCRIPTOR{
        sizeof(StackwellPluginDescriptor),
        STACKWELL_PLUGIN_API_VERSION,
        "MinimalExample",
        "0.1.0",
        initialize,
        shutdown,
        "NULL.WORKSPACE",
        "Smallest supported Stackwell Plugin API v1 example.",
        "0.1.0"
    };
}

extern "C" STACKWELL_PLUGIN_EXPORT
const StackwellPluginDescriptor*
STACKWELL_PLUGIN_CALL stackwell_plugin_query(void)
{
    return &DESCRIPTOR;
}
