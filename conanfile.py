#!/usr/bin/env python
from conans import ConanFile, CMake


class ItertoolsConan(ConanFile):
    name = "itertools"
    description = "Python's iterators for modern C++"
    topics = ("conan", "iterator", "header-only", "itertools", )
    url = "https://github.com/cgsdfc/itertools.git"
    homepage = url
    license = "MIT License"
    exports = "LICENSE"
    exports_sources = ("include/*", "CMakeLists.txt", )
    generators = "cmake"

    def package(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = "OFF"
        cmake.definitions["CATCH_INSTALL_DOCS"] = "OFF"
        cmake.definitions["CATCH_INSTALL_HELPERS"] = "ON"
        cmake.configure()
        cmake.install()

        self.copy(pattern="LICENSE", dst="licenses")

    def package_id(self):
        self.info.header_only()
