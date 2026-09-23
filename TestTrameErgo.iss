; Define your application name and version
[Setup]
AppName=Test Trame ERGO
AppVersion=1.0
DefaultDirName={pf}\TrameErgo
DefaultGroupName=TrameErgo
OutputDir=Output
OutputBaseFilename=TrameErgoInstaller
Compression=lzma
SolidCompression=yes

; Create the "patients" directory in the installation directory
[Dirs]
Name: "{app}\patients"
Name: "{localappdata}\TrameErgo"
Name: "{userdocs}\TrameErgo"

; Include the application executable and all necessary files
[Files]
; Application executable
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\PILIZ.exe"; DestDir: "{app}"; Flags: ignoreversion

; Include Qt libraries and dependencies (adjust paths as necessary)
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion

; Include the arborescence of documents
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\arborescence\*"; DestDir: "{localappdata}\PILIZ\arborescence"; Flags: ignoreversion recursesubdirs createallsubdirs

; Include other necessary Qt plugins and resources (adjust paths as necessary)
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "D:\Template\build-PILIZ-Desktop_Qt_6_6_2_MinGW_64_bit-Release\release\styles\qwindowsvistastyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion

; Creating shortcuts in the Start Menu and on the Desktop
[Icons]
Name: "{group}\TrameErgo"; Filename: "{app}\PILIZ.exe"
Name: "{commondesktop}\TrameErgo"; Filename: "{app}\PILIZ.exe"; Tasks: desktopicon

; Optional: Creating a task for desktop icon creation
[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: 

; Uninstallation
[UninstallDelete]
Type: filesandordirs; Name: "{app}"
Type: filesandordirs; Name: "{localappdata}\TrameErgo\arborescence"
Type: filesandordirs; Name: "{localappdata}\TrameErgo"
Type: filesandordirs; Name: "{userdocs}\TrameErgo"
