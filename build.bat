if not exist bin mkdir bin
if not exist build mkdir build
cd build

cmake ../cmake
cmake --build . --target FBX2glTF --config RelWithDebInfo
xcopy /y RelWithDebInfo\FBX2glTF.exe ..\bin
xcopy /y RelWithDebInfo\libfbxsdk.dll ..\bin

pause