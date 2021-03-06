# TGLangID

Fix Telegram Desktop (Windows) Chinese font issue under non-Chinese locales (LangIDs).

Only 14 KB in final release binary size!

Inspired by [FontMod](https://github.com/ysc3839/FontMod).

## Usage

1. Install Visual Studio 2019, select `Desktop development with C++`
2. Open `TGLangID.sln`
3. Select menu `Build` -> `Build Solution`
4. Locate `version.dll` under project root's `Release` folder
5. Copy `version.dll` to the same folder as [`Telegram.exe`](https://github.com/telegramdesktop/tdesktop/releases)
6. Run `Telegram.exe`

## What is this

This is a bare-bone DLL that can be loaded as `version.dll` which then hooks [`GetUserDefaultLangID`](https://docs.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getuserdefaultlangid), deceiving the [modified Qt](https://github.com/qt/qtbase/blob/5.12.2/src/platformsupport/fontdatabases/windows/qwindowsfontdatabase.cpp#L1839-L1846) Telegram Windows uses that the user's language ID is `0x0804`. Therefore, Qt would load the font set in the order I want.

Without the patch/hook, if the user language ID isn't `0x0804` or `0x1004`, it could load [Japanese fonts](https://github.com/desktop-app/patches/blob/1b2cdcbdc25e6870300b38998d2e06c1c9a2a3a9/qtbase_5_12_8/0006-fix-cjk-font-fallback.patch#L13-L21) with higher priority, leading to funny Chinese characters displays.
