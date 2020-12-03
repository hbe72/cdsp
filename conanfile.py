#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from conans import ConanFile
from conans.tools import load
import re, os

class CdspConan(ConanFile):
    name = "cdsp"
    def set_version(self):
        content = load(os.path.join(self.recipe_folder, "CMakeLists.txt"))
        version = re.search(r"project\(cdsp VERSION (.*)\)", content).group(1)
        self.version = version.strip()
    license = "Boost Software License 1.0"
    author = "Heikki Berg <cdsp.heikki.berg@gmail.com>"
    url = "https://github.com/hbe72/cdsp"
    homepage = "https://github.com/hbe72/cdsp"
    description = "A Compositional DSP Library for C++"
    topics = ("fixed-point", "value-types")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_paths", "cmake_find_package"
    no_copy_source = True
    requires = "gtest/1.10.0","cnl/1.1.0@johnmcfarlane/development"

    scm = {
        "type": "git",
        "url": "https://github.com/hbe72/cdsp.git",
        "revision": "auto"
    }

    def package(self):
        self.copy("include/*.h")
        self.copy("LICENSE_1_0.txt", "licenses")


    def package_id(self):
        self.info.header_only()
