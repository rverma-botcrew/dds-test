# dds-test
```
# Export some build directories
export CYCLONE_INSTALL=$HOME/dds-install         # Core C library install prefix
export CXX_INSTALL=$HOME/dds-cxx-install         # C++ wrapper prefix

# Install CycloneDDS Core Library
git clone https://github.com/eclipse-cyclonedds/cyclonedds.git
cd cyclonedds
rm -rf build && mkdir build && cd build
cmake ../ \                     
 -DCMAKE_INSTALL_PREFIX="$CYCLONE_INSTALL" \
 -DBUILD_EXAMPLES=ON \
 -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --target install

# Install C++ wrapper for the core library
git clone https://github.com/eclipse-cyclonedds/cyclonedds-cxx.git
cd cyclonedds-cxx
rm -rf build && mkdir build && cd build
cmake .. \                
 -DCMAKE_PREFIX_PATH="$CYCLONE_INSTALL" \
 -DCMAKE_INSTALL_PREFIX="$CXX_INSTALL" \
 -DBUILD_EXAMPLES=ON \
 -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --target install

# Sanity-check:
ls "$CXX_INSTALL/lib/libddscxx.so"*    # should list the .so files
ls "$CXX_INSTALL/lib/libcycloneddsidlcxx.so"*

# Explicitly load the environment so it doesn't conflict with ROS2 
export LD_LIBRARY_PATH=$CXX_INSTALL/lib:$CYCLONE_INSTALL/lib:$LD_LIBRARY_PATH
```

```
# For building the application
cd my-dds-app/
rm -rf build && mkdir build && cd build
cmake .. \
  -DCMAKE_PREFIX_PATH="$CYCLONE_INSTALL;$CXX_INSTALL" \          
  -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . --parallel
```
