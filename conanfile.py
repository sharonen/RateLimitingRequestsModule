from conans import ConanFile, CMake
import traceback

class RequesterModuleConan(ConanFile):
    name = "RequesterModule"
    settings = "os", "compiler", "build_type", "arch"
    requires = ("catch2/2.1.1@bincrafters/stable",
                "trompeloeil/v29@rollbear/stable",
                "boost_asio/1.66.0@bincrafters/stable")
    generators = "cmake", "cmake_multi"