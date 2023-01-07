# TPS Location SDK: Quick Start for Native
![Platform](https://img.shields.io/static/v1?label=platform&message=windows%20%7C%20macos%20%7C%20linux&color=informational)

The Quick Start project illustrates minimal steps to integrate the SDK into a simple app.

The CMake build system is used in this guide to demonstrate a cross-platform approach.

## Prerequisites

* Windows, macOS or Linux-based operating system
* C/C++ compiler suite or IDE (such as Xcode on macOS, Visual Studio on Windows, etc.)
* [CMake](https://cmake.org/)
* TPS Location SDK

## Initial CMake project

Create a new directory for the project, and put files inside with initial source code:

`location-quick-start.cpp`
```c++
#include <stdio.h>

int main(int argc, char** argv) {
    return 0;
}
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.0)
project(location-quick-start)

add_executable(location-quick-start location-quick-start.cpp)
```

## Contact TPS to obtain the SDK

Contact support.tps@qti.qualcomm.com to request access to the SDK and get the API key.

Unpack the SDK package to a subdirectory named `lib` in the root of your project.

## Add SDK dependency

In your `CMakeLists.txt` add dependency to the `wpsapi` library located in the `lib` subdirectory:
```cmake
include_directories(lib)
link_directories(lib)

add_executable(location-quick-start location-quick-start.cpp)
target_link_libraries(location-quick-start wpsapi)
```

The final `CMakeLists.txt` code is available [here](https://github.com/quic/tps-location-quick-start-native/tree/main/CMakeLists.txt).

## Import SDK

Import the API header file in the source code:
```c++
#include <wpsapi.h>
```

## Initialize SDK

Initialize the SDK by calling `WPS_load()` in your `main()` function:
```c++
    int rc = WPS_load();
    if (rc != WPS_OK) {
        fprintf(stderr, "WPS_load failed (%d)\n", rc);
        return rc;
    }
    // ...
```

Set your API key before making location calls:
```c++
    WPS_set_key("YOUR KEY");
```

Make sure to replace `"YOUR KEY"` with your real API key in the code.

## Determine location

You are now ready to determine your device's location:
```c++
    WPS_Location* location;
    rc = WPS_location(NULL, WPS_NO_STREET_ADDRESS_LOOKUP, &location);
    if (rc == WPS_OK) {
        printf("%.6f, %.6f +/-%.1fm\n", location->latitude, location->longitude, location->hpe);
        // could fall back here to WPS_ip_location to get a coarse location
    } else {
        fprintf(stderr, "WPS_location failed (%d)\n", rc);
    }
```

## Shut down SDK

It is recommended to free resources used by SDK when the program is about to terminate, such as at the end of the `main()` function:
```c++
    WPS_unload();
```

The complete source code in available [here](https://github.com/quic/tps-location-quick-start-native/tree/main/location-quick-start.cpp).

## Build the app

### Generate project files using CMake

Create a `build` directory in the project root:
```sh
mkdir build
cd build
```

In the `build` directory, run `cmake` against the parent directory (project root):
```sh
cmake ..
```

The command above will generate project files necessary to build the program. By default it will generate a `Makefile` on Linux and macOS, and an MSVC project on Windows if Visual Studio is installed.

Note that on Windows, CMake will generate a project for the 32-bit architecture by default, so you'll have to use the `win32` version of the SDK package.

You can specify a particular generator in the command line if desired, or use the CMake GUI application and specify the generator in the UI.

### Compile the project

Invoke the build command inside the `build` directory.

On macOS or Linux:
```sh
make
```

On Windows start the "Command Prompt" for Visual Studio from the Start Menu, and run:
```sh
msbuild location-quick-start.sln
```

As a result, a binary executable of `location-quick-start` will appear in the build directory.

On macOS or Linux:
```
build/location-quick-start
```

On Windows:
```
build/Debug/location-quick-start.exe
```

## Run the app

### Copy the wpsapi library

Copy the wpsapi library (`libwpsapi.dylib`, `libwpsapi.so` or `wpsapi.dll`) to the directory where the executable is located, so that the program can load the library when launched.

### Create an app bundle on macOS

Starting with macOS 10.15 Catalina and later versions, it is required to package the app in an app bundle directory with the `Info.plist` file in order for the app to be able to determine location.

Create the app bundle directory and copy the binaries:
```
mkdir build/LocationQuickStart.app
cp build/location-quick-start build/LocationQuickStart.app/
cp lib/libwpsapi.dylib build/LocationQuickStart.app/
```

Inside the app bundle directory, create an `Info.plist` file with app bundle information:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>location-quick-start</string>
    <key>CFBundleIdentifier</key>
    <string>com.skyhook.locationquickstart</string>
    <key>LSUIElement</key>
    <string>1</string>
</dict>
</plist>
```

`Info.plist` is available [here](https://github.com/quic/tps-location-quick-start-native/tree/main/Info.plist) for your reference.

### Start the app

If you've placed the necessary files in the directory along with the executable, you can now run the quick start app:
```sh
./location-quick-start
42.351974, -71.047722 +/-30.0m
```

## Further Read

Please refer to the [full SDK guide](https://quic.github.io/tps-location-sdk-native/) for more information.

# License
![License](https://img.shields.io/static/v1?label=license&message=CC-BY-ND-4.0&color=green)

Copyright (c) 2023 Qualcomm Innovation Center, Inc. All Rights Reserved.

This work is licensed under the [CC BY-ND 4.0 License](https://creativecommons.org/licenses/by-nd/4.0/). See [LICENSE](LICENSE) for more details.
