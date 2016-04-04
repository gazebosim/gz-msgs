@set build_type=Release
@if not "%1"=="" set build_type=%1
@echo Configuring for build type %build_type%

@set PROTOBUF_PATH=%cd%\..\..\protobuf-2.6.0-win64-vc12
@set IGNITION_MATH_PATH=%cd%\..\..\ign-math\build\install\%build_type%

cmake -G "NMake Makefiles"^
  -DCMAKE_PREFIX_PATH="%IGNITION-MATH_PATH%"^
  -DCMAKE_INSTALL_PREFIX="install\%build_type%"^
  -DCMAKE_BUILD_TYPE="%build_type%"^
  -DPROTOBUF_SRC_ROOT_FOLDER="%PROTOBUF_PATH%"^
  -DIGNITION-MATH_INCLUDE_DIRS:STRING="%IGN_MATH_PATH%\include\ignition\math2"^
  -DIGNITION-MATH_LIBRARY_DIRS:STRING="%IGN_MATH_PATH%\lib"^
  -DIGNITION-MATH_LIBRARIES="ignition-math2"^
  -DENABLE_TESTS_COMPILATION:BOOL=True ..
