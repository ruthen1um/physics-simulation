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

After that [create build directory with cmake and conan-created
preset](https://docs.conan.io/2/examples/tools/cmake/cmake_toolchain/build_project_cmake_presets.html#building-the-project-using-cmakepresets):
```shell
$ cmake --preset conan-<configuration>
```

Finally, build the project:
```shell
$ cmake --build --preset conan-<configuration>
```
