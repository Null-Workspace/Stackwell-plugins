# Plugin submission policy

The catalog is intended for useful, maintainable Stackwell extensions.

## Required for review

- Public source repository and a clear license.
- A concise description of purpose and required permissions.
- Versioned releases with platform and architecture stated.
- Plugin API version and minimum Stackwell host version.
- Build instructions and reproducible source for the submitted binary.
- SHA-256 checksum for every published binary.
- No hidden downloads, unrelated telemetry, credential collection, or destructive behavior.

## Review and listing

Submitting a plugin does not guarantee inclusion. Maintainers may request changes or decline a listing. Catalog metadata must point to the source repository and the exact release asset.

## Security note

Stackwell plugins are native code loaded into the host process. Catalog review and checksums reduce some risks but do not sandbox plugins or prove that code is safe. Users remain responsible for choosing trusted plugins.
