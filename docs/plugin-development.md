# Plugin development

## The one-file runtime rule

A Stackwell plugin is distributed as one native library:

- Windows: `.dll`
- Linux: `.so`
- macOS: `.dylib`

The plugin source repository may contain any number of source, build, and documentation files. The installed plugin itself is one library file placed directly in the host's plugin directory. Do not require a plugin-specific runtime folder for basic installation.

## API v1 lifecycle

A plugin exports exactly one entry point:

```cpp
extern "C" STACKWELL_PLUGIN_EXPORT
const StackwellPluginDescriptor*
STACKWELL_PLUGIN_CALL stackwell_plugin_query(void);
```

The returned descriptor contains the plugin metadata and two callbacks:

1. `initialize(const StackwellHostApi*)` — called when the host loads the plugin.
2. `shutdown()` — called before the host unloads the plugin.

Use only the functions present in `StackwellHostApi`. In API v1 these are `log_info` and `log_error`.

## Compatibility

- Set `api_version` to `STACKWELL_PLUGIN_API_VERSION`.
- Set `struct_size` to `sizeof(StackwellPluginDescriptor)`.
- Validate the host pointer and API version before using callbacks.
- Keep the descriptor and metadata strings alive for the lifetime of the loaded library.
- Do not let C++ exceptions cross the C ABI boundary.
- Match the host architecture and platform.

## Build

Run CMake from the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release
```

Artifacts are placed in `build/dist/plugins`.

## Important limitation

API v1 has no GUI-page registration, command registration, hardware telemetry, or inter-plugin messaging. A plugin cannot add a page to the current desktop UI using this API. Do not claim those features until a compatible host API is released.
