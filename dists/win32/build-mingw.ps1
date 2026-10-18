# Build libusb4java for win32-x86-64 with MinGW-w64 against libusb 1.0.30.
# The Visual Studio script is build.bat. This script is for a machine that has
# WinLibs gcc and a JDK, and no Visual Studio.

$ErrorActionPreference = "Stop"

$LibusbVersion = "1.0.30"
$GccRoot = Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin"
if (-not (Test-Path (Join-Path $GccRoot "gcc.exe"))) {
    throw "gcc.exe not found under $GccRoot"
}
$env:PATH = "$GccRoot;$env:PATH"

$ProjectDir = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$TargetDir = Join-Path $ProjectDir "target"
$BuildDir = Join-Path $TargetDir "build\win32-x86-64"
$LibusbSrc = Join-Path $BuildDir "libusb-$LibusbVersion\libusb"
$ObjDir = Join-Path $BuildDir "libusb-obj"
$ConfigDir = Join-Path $BuildDir "config"
New-Item -ItemType Directory -Force -Path $ObjDir, $ConfigDir | Out-Null

$Zip = Join-Path $BuildDir "v$LibusbVersion.zip"
if (-not (Test-Path $LibusbSrc)) {
    if (-not (Test-Path $Zip)) {
        curl.exe -L --http1.1 -o $Zip "https://github.com/libusb/libusb/archive/refs/tags/v$LibusbVersion.zip"
    }
    tar -xf $Zip -C $BuildDir
}

@"
#define DEFAULT_VISIBILITY __attribute__((visibility("default")))
#define ENABLE_LOGGING 1
#define PLATFORM_WINDOWS 1
#define PRINTF_FORMAT(a, b) __attribute__((__format__(__printf__, a, b)))
"@ | Set-Content -Encoding ASCII (Join-Path $ConfigDir "config.h")

$cflags = @(
    "-O2", "-c",
    "-DHAVE_STRUCT_TIMESPEC",
    "-DLIBUSB_WINDOWS_HOTPLUG",
    "-DWINVER=0x0601",
    "-D_WIN32_WINNT=0x0601",
    "-I$ConfigDir",
    "-I$LibusbSrc"
)
$sources = @(
    "core.c", "descriptor.c", "hotplug.c", "io.c", "strerror.c", "sync.c",
    "os\events_windows.c", "os\threads_windows.c", "os\windows_common.c",
    "os\windows_hotplug.c", "os\windows_usbdk.c", "os\windows_winusb.c"
)
Push-Location $LibusbSrc
foreach ($src in $sources) {
    $obj = Join-Path $ObjDir ((Split-Path $src -Leaf) + ".o")
    & gcc @cflags $src -o $obj
    if ($LASTEXITCODE -ne 0) { throw "gcc failed on $src" }
}
Pop-Location
$objects = Get-ChildItem $ObjDir -Filter *.o | ForEach-Object { $_.FullName }
& ar rcs (Join-Path $ObjDir "libusb.a") @objects
if ($LASTEXITCODE -ne 0) { throw "ar failed" }

$Jar = (Get-Command jar).Source
$Jdk = Split-Path (Split-Path $Jar -Parent) -Parent
$JniDll = Join-Path $BuildDir "libusb4java.dll"
$jniSources = Get-ChildItem (Join-Path $ProjectDir "src") -Filter *.c | ForEach-Object { $_.FullName }
& gcc -shared -static-libgcc "-Wl,--kill-at" -o $JniDll `
    @jniSources `
    "-I$LibusbSrc" `
    "-I$Jdk\include" `
    "-I$Jdk\include\win32" `
    (Join-Path $ObjDir "libusb.a") `
    -lsetupapi -lole32 -ladvapi32
if ($LASTEXITCODE -ne 0) { throw "jni link failed" }

$Classes = Join-Path $BuildDir "classes\org\usb4java\win32-x86-64"
New-Item -ItemType Directory -Force -Path $Classes | Out-Null
Copy-Item $JniDll (Join-Path $Classes "libusb4java.dll") -Force
$JarOut = Join-Path $TargetDir "libusb4java-win32-x86-64.jar"
if (Test-Path $JarOut) { Remove-Item $JarOut }
& jar cf $JarOut -C (Join-Path $BuildDir "classes") org
if ($LASTEXITCODE -ne 0) { throw "jar failed" }
Write-Host "Built $JarOut"
