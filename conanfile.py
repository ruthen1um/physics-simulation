from conan import ConanFile
from conan.tools.cmake import cmake_layout


class PhysicsSimulationRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/3.2.20")

    def layout(self):
        cmake_layout(self)
