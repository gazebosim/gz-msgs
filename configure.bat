@set build_type=Release
@if not "%1"=="" set build_type=%1
@echo Configuring for build type %build_type%

@set PROTOBUF_PATH=%cd%\..\..\protobuf-2.6.0-win64-vc12
@set IGN_MATH_PATH=%cd%\..\..\ign-math\build\install\%build_type%

cmake -G "NMake Makefiles"^
  -DCMAKE_PREFIX_PATH="%IGN_MATH_PATH%"^
  -DCMAKE_INSTALL_PREFIX="install\%build_type%"^
  -DCMAKE_BUILD_TYPE="%build_type%"^
  -DPROTOBUF_SRC_ROOT_FOLDER="%PROTOBUF_PATH%"^
  -DENABLE_TESTS_COMPILATION:BOOL=True ..
