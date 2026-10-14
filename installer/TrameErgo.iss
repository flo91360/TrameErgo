; Installateur Windows de TrameErgo, fabriqué par .github/workflows/build-windows.yml.
; Compilation locale : iscc /DAppVersion=1.0.0 /DSourceDir=..\deploy installer\TrameErgo.iss
; (deploy\ contient TrameErgo.exe après windeployqt, et deploy\contenu le modèle Word bilan.docx).
#ifndef AppVersion
  #define AppVersion "0.0.0"
#endif
#ifndef SourceDir
  #define SourceDir "..\deploy"
#endif

[Setup]
AppId={{6F2C9B1E-4E57-4C1A-9F3B-7A2D5E8C1B40}
AppName=TrameErgo
AppVersion={#AppVersion}
AppPublisher=TrameErgo
DefaultDirName={autopf}\TrameErgo
DefaultGroupName=TrameErgo
; Installation pour l'utilisateur courant : le modèle va dans SON dossier
; %LOCALAPPDATA%\TrameErgo, là où l'application le cherche.
PrivilegesRequired=lowest
OutputDir=..\Output
OutputBaseFilename=TrameErgo-Installation-{#AppVersion}
UninstallDisplayIcon={app}\TrameErgo.exe
Compression=lzma2
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Dirs]
Name: "{userdocs}\TrameErgo"

[Files]
; Application et bibliothèques Qt rassemblées par windeployqt
Source: "{#SourceDir}\*"; DestDir: "{app}"; Excludes: "contenu\*"; Flags: ignoreversion recursesubdirs createallsubdirs
; Modèle Word du bilan, lu par l'application dans %LOCALAPPDATA%\TrameErgo\contenu
Source: "{#SourceDir}\contenu\*"; DestDir: "{localappdata}\TrameErgo\contenu"; Flags: ignoreversion recursesubdirs createallsubdirs

[InstallDelete]
; Anciens modèles (un par écran, jusqu'à la 1.0.1), remplacés par contenu\bilan.docx.
Type: filesandordirs; Name: "{localappdata}\TrameErgo\arborescence"

[Icons]
Name: "{group}\TrameErgo"; Filename: "{app}\TrameErgo.exe"
Name: "{autodesktop}\TrameErgo"; Filename: "{app}\TrameErgo.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Créer une icône sur le bureau"; GroupDescription: "Icônes supplémentaires :"

[Run]
Filename: "{app}\TrameErgo.exe"; Description: "Lancer TrameErgo"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
; Les bilans enregistrés dans Documents\TrameErgo sont conservés.
Type: filesandordirs; Name: "{localappdata}\TrameErgo\contenu"
Type: filesandordirs; Name: "{localappdata}\TrameErgo\arborescence"
