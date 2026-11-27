# Stackwell Plugins

**The official community plugin catalog and the public SDK entry point for Stackwell.**

[Русский](#русский) · [English](#english)

## English

This repository contains:

- the plugin catalog consumed by Stackwell clients in a future catalog integration;
- the public C ABI header matching the current Stackwell Plugin API v1;
- buildable example plugins;
- contribution and release requirements.

### Repository layout

```text
catalog.json
catalog.schema.json
sdk/include/stackwell/plugin_api.h
plugins/diagnostics/diagnostics.cpp
examples/minimal/minimal.cpp
docs/
.github/workflows/build-plugins.yml
```

### Build the plugins

Requirements: CMake 3.25+ and a C++20 compiler.

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The resulting plugin binaries are written to `build/dist/plugins`. On Windows they are standalone `.dll` files. Copy **one DLL per plugin** directly into Stackwell's configured plugin directory. Do not copy the source tree or SDK files into the runtime plugin directory.

### Current API scope

The current host implements Plugin API v1: plugin metadata, initialization/shutdown, and host logging callbacks. The Diagnostics example reports runtime/build facts to the Stackwell log. It does **not** yet provide a GUI page or live hardware telemetry; those require a later host API extension.

### Security

A native plugin is executable code loaded into the Stackwell process. Only install plugins from sources you trust. A checksum detects a mismatch with the catalog entry; it does not prove that a plugin is harmless.

## Русский

Это официальный репозиторий каталога плагинов и публичной точки входа в SDK Stackwell.

Здесь находятся:

- каталог плагинов;
- C ABI заголовок, совместимый с текущим Plugin API v1;
- собираемые примеры плагинов;
- правила публикации и сборки.

### Сборка

Нужны CMake 3.25+ и компилятор с поддержкой C++20.

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Готовые бинарники появятся в `build/dist/plugins`. В Windows каждый плагин — отдельный файл `.dll`. Для установки скопируй **только DLL** в настроенную папку плагинов Stackwell. Исходники и SDK в папку плагинов не копируются.

### Что умеет API сейчас

Текущая версия хоста поддерживает Plugin API v1: метаданные, запуск/остановку плагина и запись сообщений в лог Stackwell. Пример Diagnostics сообщает сведения о среде сборки и запуска. У него пока нет собственной GUI-страницы и мониторинга оборудования в реальном времени — для этого потребуется расширение API хоста.

### Безопасность

Нативный плагин — исполняемый код внутри процесса Stackwell. Устанавливай только плагины из источников, которым доверяешь. SHA-256 помогает проверить целостность файла, но не гарантирует безопасность его поведения.

## Releases

Tag a version (for example `v0.1.0`) to build the Windows x64 DLLs and attach them to a GitHub Release. Catalog entries point to release assets; source code remains available in this repository.
