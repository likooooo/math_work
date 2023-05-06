mkdir ../build
cd ../build
if [ "debug" == "$1" ];then
    BuildType=Debug
else
    BuildType=Release
fi
cmake ..  -DCMAKE_BUILD_TYPE=$BuildType -DENABLE_GENRATE_PDB=OFF
cmake --build . --config $BuildType
