[Setup]
AppName=Flank
AppVersion=0.1.0
DefaultDirName={autopf}\Flank
DefaultGroupName=Flank
OutputBaseFilename=FlankSetup
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

[Files]
Source: "C:\Users\angus\flank\flank.exe"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Flank"; Filename: "{app}\flank.exe"

[Run]
Filename: "{app}\flank.exe"; Description: "Run Flank"; Flags: nowait postinstall skipifsilent