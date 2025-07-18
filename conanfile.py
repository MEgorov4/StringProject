from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps
import os

class StringProjectConan(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"
    exports_sources = "*"

    def requirements(self):
        self.test_requires("gtest/1.8.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        
        self.output.info("Enabling compile_commands.json")
        toolchain_path = os.path.join(self.generators_folder, "conan_toolchain.cmake")
        with open(toolchain_path, "a") as f: f.write("\nset(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n")
