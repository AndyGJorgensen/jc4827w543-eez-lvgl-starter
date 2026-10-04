# Project guardrails

This is the `touchscreen/` project folder: a self-contained PlatformIO + EEZ Studio project for the
JC4827W543C board, meant to sit inside a larger repository next to other boards' projects. All paths
below are relative to this folder, and PlatformIO/git commands run from it (e.g. `cd touchscreen` first,
or `pio run -d touchscreen`).

## Generated UI code (`src/ui/`)
- `src/ui/` is generated output from the design tool (EEZ Studio Build overwrites it). Permanent fixes never go in `src/ui/`.
- Temporary edits in `src/ui/` ARE allowed to debug and find bugs (logging, experiments). Treat them as throwaway: they will be overwritten by the next EEZ Build, so the real fix must then be made outside `src/ui` (config, driver code, `src/*.cpp`, or the `.eez-project`). Tell the user when `src/ui` has been temporarily changed.
- If a generator tries to overwrite `src/ui/`, reject the overwrite and regenerate from the design tool in a safe configuration instead.

## Fixing problems
- Prefer fixes in project config, board settings, driver setup, global LVGL config, and library configuration.
- For any build or upload issue, trace the failure to config or driver code outside `src/ui` before making changes.

## Build and upload
- To try changes, upload directly (it builds as part of the upload); don't run a separate build first, to save time.

## Git shortcuts
- When the user's whole message is `c`: commit all pending changes with a descriptive message. Review the staged file list before committing and leave out anything unintended (e.g. files deleted outside your own commands).
- When the user's whole message is `p`: do the same commit, then push. If no remote is configured yet, ask for the repository URL.

## Settings workflow
- Anything the user may want to change later (host name, feature defaults such as OTA on/off at boot, passwords, timeouts, screen orientation, etc.) goes in `include/app_config.h` as a named `#define` with a comment. Code reads it from there; never hard-code such values in other files. When adding a new feature, put its tunable values in that file. If a value must also appear in `platformio.ini` (e.g. OTA upload host/password), note the duplication in both places.
- Board pins live in `include/board_pins.h` (checked against the schematics).

## Firmware code conventions (`src/*.cpp`)
- One module per feature (`display`, `touch` + `gt911`/`xpt2046`, `gui`, `wifi_manager`, `wifi_saved`, `ota`, `spi_bus`, `sd_card`, `audio`, `battery`), each with `<name>_init()` and, if needed, `<name>_update()` called from `main.cpp`.
- EEZ native variables use the macros in `src/eez_vars.h` (`EEZ_VAR_STRING_RO`, `EEZ_VAR_INT_RO`, `EEZ_VAR_BOOL`); on-screen text uses `StatusText<N>` (`src/status_text.h`); periodic work uses `Interval` (`src/interval.h`).
- No geometry calls (`lv_obj_set_pos/size/align`...) on EEZ `objects.*` from C: layout belongs in the `.eez-project`.

## Hardware reference
- `docs/hardware/` holds the hardware reference kept from the seller's package: schematics, spec sheet, dimensions, amp datasheet, the vendor's working demo setup and factory firmware (index in `docs/hardware/README.md`). Read it freely when you need hardware details. The schematics (`docs/hardware/schematic/JC4827W543-1.png`, `-2.png`) are the reliable pin source. The rest of the seller's package was removed on purpose (and purged from git history to keep the repo small); if something specific is needed, it can be re-downloaded from the seller (link in `docs/hardware/README.md`).
- `BoardsInfo.md` is where notes specific to the ESP32-S3 + JC4827W543C board go (480×272 QSPI NV3041A LCD, not RGB; GT911 touch). It is an all-in-one board: ESP32-S3 with LCD and touch screen, speaker, SD card, battery charging circuit and more.

## EEZ Studio
- EEZ Studio project work (screens, widgets, styles, fonts, flow, the `.eez-project` JSON): use the project skill in `.claude/skills/eezstudio/SKILL.md`. Its top "READ FIRST" section adapts it to this project (PlatformIO, `src/ui`, LVGL 9.5, flow enabled) and overrides the downloaded text where they conflict.
