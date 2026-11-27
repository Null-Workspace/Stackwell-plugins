#pragma once

#include <stdint.h>

#define STACKWELL_PLUGIN_API_VERSION 1

#if defined(_WIN32)
    #define STACKWELL_PLUGIN_CALL __cdecl

    #if defined(STACKWELL_PLUGIN_BUILD)
        #define STACKWELL_PLUGIN_EXPORT __declspec(dllexport)
    #else
        #define STACKWELL_PLUGIN_EXPORT
    #endif
#else
    #define STACKWELL_PLUGIN_CALL

    #if defined(STACKWELL_PLUGIN_BUILD)
        #define STACKWELL_PLUGIN_EXPORT \
            __attribute__((visibility("default")))
    #else
        #define STACKWELL_PLUGIN_EXPORT
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (STACKWELL_PLUGIN_CALL *StackwellLogFn)(
    const char* message
);

typedef struct StackwellHostApi
{
    uint32_t api_version;
    uint32_t struct_size;

    StackwellLogFn log_info;
    StackwellLogFn log_error;

} StackwellHostApi;

typedef int (STACKWELL_PLUGIN_CALL *StackwellPluginInitializeFn)(
    const StackwellHostApi* host
);

typedef void (STACKWELL_PLUGIN_CALL *StackwellPluginShutdownFn)(void);

typedef struct StackwellPluginDescriptor
{
    uint32_t struct_size;
    uint32_t api_version;

    const char* name;
    const char* version;

    StackwellPluginInitializeFn initialize;
    StackwellPluginShutdownFn shutdown;

    const char* author;
    const char* description;
    const char* min_host_version;

} StackwellPluginDescriptor;

typedef const StackwellPluginDescriptor*
    (STACKWELL_PLUGIN_CALL *StackwellPluginQueryFn)(void);

#if defined(STACKWELL_PLUGIN_BUILD)
STACKWELL_PLUGIN_EXPORT
const StackwellPluginDescriptor*
STACKWELL_PLUGIN_CALL stackwell_plugin_query(void);
#endif

#ifdef __cplusplus
}
#endif
