param(
    [string]$Configuration = "Debug",
    [string]$Platform = "ARM64"
)

Write-Host "Assumes solution generated; run scripts/generate.bat if needed"

$solution = Join-Path -Path "$(Get-Location)" -ChildPath "build\gsc-tool.sln"
if (-not (Test-Path $solution)) {
    Write-Host "Solution not found: $solution" -ForegroundColor Yellow
    Write-Host "Check premake5 output or run this script from repo root."
    exit 2
}

Write-Host "Building solution $solution ($Configuration|$Platform)..."
msbuild.exe $solution /m /p:Configuration=$Configuration /p:Platform=$Platform

Write-Host "Build finished."
