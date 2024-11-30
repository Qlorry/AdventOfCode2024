param (
    [string]$DayNumber = "1"
)

$ProjectPath = Resolve-Path -Path (Join-Path (Get-Location) "../")

$TemplatesPath = Join-Path $ProjectPath "Templates"
$DaysPath = Join-Path $ProjectPath "Days"
$InputsPath = Join-Path $ProjectPath "Inputs"

$CppFileTemplate = Join-Path $TemplatesPath "TemplateDay.cpp"

$CppFile = Join-Path $DaysPath "Day$DayNumber.cpp"
$ExamplePuzzleInputFile = Join-Path $InputsPath "$DayNumber/example.txt"
$MyPuzzleInputFile = Join-Path $InputsPath "$DayNumber/input.txt"

Write-Host "Generating Day $DayNumber..."
Write-Host "    Example Puzzle Input File path: $ExamplePuzzleInputFile"
Write-Host "    My Puzzle Input File path: $MyPuzzleInputFile"

$ErrorActionPreference = "Stop"

# Step 1: Check if the file already exists
if (Test-Path $CppFile) {
    Write-Host "Error: $CppFile already exists. Aborting script." -ForegroundColor Red
    exit 1
}
if (Test-Path $ExamplePuzzleInputFile) {
    Write-Host "Error: $ExamplePuzzleInputFile already exists. Aborting script." -ForegroundColor Red
    exit 1
}
if (Test-Path $MyPuzzleInputFile) {
    Write-Host "Error: $MyPuzzleInputFile already exists. Aborting script." -ForegroundColor Red
    exit 1
}

# Step 2: Generate files
Copy-Item $CppFileTemplate $CppFile

New-Item -Path $ExamplePuzzleInputFile -ItemType File -Force
New-Item -Path $MyPuzzleInputFile -ItemType File -Force

# Step 3: Apply template
(Get-Content $CppFile).Replace("$<day_number>", "$DayNumber") | Set-Content $CppFile
Write-Host "Files generated, template applied"

# Step 4: Add files to Visual Studio project

$RelativeCppFile = $CppFile.Substring($ProjectPath.ToString().Length)
$RelativeExampleInputFile = $ExamplePuzzleInputFile.Substring($ProjectPath.ToString().Length)
$RelativeMyInputFile = $MyPuzzleInputFile.Substring($ProjectPath.ToString().Length)


Write-Host "Adding files to Visual Studio project..."
$ProjectFile = Join-Path $ProjectPath "AdventOfCode2024.vcxproj" # Update with your project file name
if (Test-Path $ProjectFile) {
    $ProjectContent = Get-Content $ProjectFile -Raw
    $PrjectContentByLine = $ProjectContent -split "`n";

    $CppInclude = '    <ClCompile Include="' + $RelativeCppFile + '" />'
    $RelativeExampleInputInclude = '    <None Include="' + $RelativeExampleInputFile + '" />'
    $RelativeMyInputInclude = '    <None Include="' + $RelativeMyInputFile + '" />'

    # Last place with ClCompile
    $lastMatch = ($PrjectContentByLine | Select-String '<ClCompile Include="') | Select-Object -Last 1
    $lineToInsertAfter = $lastMatch.LineNumber - 1
    $PrjectContentByLine = $PrjectContentByLine[0..$lineToInsertAfter] + $CppInclude + $PrjectContentByLine[($lineToInsertAfter + 1)..($PrjectContentByLine.Count - 1)]

    # Last place with None Include
    $lastMatch = ($PrjectContentByLine | Select-String '<None Include="') | Select-Object -Last 1
    $lineToInsertAfter = $lastMatch.LineNumber - 1
    $PrjectContentByLine = $PrjectContentByLine[0..$lineToInsertAfter] `
                         + $RelativeExampleInputInclude `
                         + $RelativeMyInputInclude `
                         + $PrjectContentByLine[($lineToInsertAfter + 1)..($PrjectContentByLine.Count - 1)]

    # Save the updated project file
    Set-Content $ProjectFile ($PrjectContentByLine -join "`n")
    # Write-Host "Files added to Visual Studio project: $CppFile, $HeaderFile"
} else {
    Write-Error "Project file not found: $ProjectFile"
}

Write-Host "Adding files to filters..."
$FiltersFile = Join-Path $ProjectPath "AdventOfCode2024.vcxproj.filters" # Update with your project file name
if (Test-Path $FiltersFile) {
    $ProjectContent = Get-Content $FiltersFile -Raw
    $PrjectContentByLine = $ProjectContent -split "`n";

    $CppInclude = '    <ClCompile Include="' + $RelativeCppFile + '">'+"`n"+'      <Filter>Days</Filter>'+"`n"+'    </ClCompile>'
    $RelativeExampleInputInclude = '    <None Include="' + $RelativeExampleInputFile + '">'+"`n"+'      <Filter>Inputs\Day' + $DayNumber + '</Filter>'+"`n"+'    </None>'
    $RelativeMyInputInclude = '    <None Include="' + $RelativeMyInputFile + '">'+"`n"+'      <Filter>Inputs\Day' + $DayNumber + '</Filter>'+"`n"+'    </None>'

    # Last place with ClCompile
    $lastMatch = ($PrjectContentByLine | Select-String '</ClCompile>') | Select-Object -Last 1
    $lineToInsertAfter = $lastMatch.LineNumber - 1
    $PrjectContentByLine = $PrjectContentByLine[0..$lineToInsertAfter] + $CppInclude + $PrjectContentByLine[($lineToInsertAfter + 1)..($PrjectContentByLine.Count - 1)]

    # Last place with None Include
    $lastMatch = ($PrjectContentByLine | Select-String '</None') | Select-Object -Last 1
    $lineToInsertAfter = $lastMatch.LineNumber - 1
    $PrjectContentByLine = $PrjectContentByLine[0..$lineToInsertAfter] `
                         + $RelativeExampleInputInclude `
                         + $RelativeMyInputInclude `
                         + $PrjectContentByLine[($lineToInsertAfter + 1)..($PrjectContentByLine.Count - 1)]

    # Last place with Filter def
    $lastMatch = ($PrjectContentByLine | Select-String '<Filter Include=') | Select-Object -Last 1
    $lineToInsertAfter = $lastMatch.LineNumber - 1
    $PrjectContentByLine = $PrjectContentByLine[0..$lineToInsertAfter] + ('    <Filter Include="Inputs\Day'+ $DayNumber + '"/>') + $PrjectContentByLine[($lineToInsertAfter + 1)..($PrjectContentByLine.Count - 1)]

    # Save the updated project file
    Set-Content $FiltersFile ($PrjectContentByLine -join "`n")
    # Write-Host "Files added to Visual Studio project: $CppFile, $HeaderFile"
} else {
    Write-Error "Project filter file not found: $FiltersFile"
}