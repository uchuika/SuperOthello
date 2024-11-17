SET OutDir=%1


REM SDL2.dll をコピー
xcopy ".\External\SDL2-2.30.2\lib\x64\SDL2.dll" "%OutDir%" /y

REM SDL2_image.dll をコピー
xcopy ".\External\SDL2-2.30.2\SDL2_image-2.8.2\lib\x64\SDL2_image.dll" "%OutDir%" /y

xcopy ".\External\SDL2-2.30.2\SDL2_ttf-2.22.0\lib\x64\SDL2_ttf.dll" "%OutDir%" /y