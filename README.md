# About
A simulator game where you can create, drag, drop objects and change their physical parameters.

# Building
At first install required packages (specify profile if needed):
```shell
$ conan install --build=missing
```
> Note: if you did not use conan before, you need to read the
> [documentation](https://docs.conan.io/2/) and create a
> [profile](https://docs.conan.io/2/reference/config_files/profiles.html) file

After that [create build directory with cmake and conan-created release
preset](https://docs.conan.io/2/examples/tools/cmake/cmake_toolchain/build_project_cmake_presets.html#building-the-project-using-cmakepresets):
```shell
$ cmake --preset conan-release -DBUILD_TESTING=OFF
```

Finally, build the project:
```shell
$ cmake --build --preset conan-release
```

# Development
Create build directory with conan debug preset (tests are built by default)
```shell
$ cmake --preset conan-debug
```

Build the project:
```shell
$ cmake --build --preset conan-debug
```

You can run tests with ctest:
```shell
$ ctest --preset conan-debug
```
