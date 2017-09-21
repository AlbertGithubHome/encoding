[![Version](https://img.shields.io/badge/version-0.2.0-green.svg)](https://github.com/AlbertGithubHome/encoding/releases/tag/v0.2.0)
[![Platform](https://img.shields.io/badge/platform-linux%7Cwindows-lightgrey.svg)](https://github.com/AlbertGithubHome/encoding)
[![Build](https://img.shields.io/badge/build-linux-yellow.svg)](https://github.com/AlbertGithubHome/encoding/tree/master/core/tools/make4linux)
[![Build](https://img.shields.io/badge/build-windows-yellow.svg)](https://github.com/AlbertGithubHome/encoding/tree/master/core/tools/make4windows)
[![License](https://img.shields.io/badge/license-GPL3.0-blue.svg)](https://github.com/AlbertGithubHome/encoding/blob/master/LICENSE)

# encoding
Designed to deal with file coding issues

---

# build

### *windows*

1. run **make.bat** to generate project solution.
2. run **makeclean.bat** to delete project solution.
3. **premake.lua** is the configuration file for generating project solution.
4. run **makefull.bat** to generate project solution and bulid it immediately.

>tools directory: **encoding\core\tools\make4windows**

>warm prompt: **you have two ways to build this project.**

### *linux*

1. run **makefull.sh** to generate Makefile and make it.


>tools directory: **encoding\core\tools\make4linux**

>warm prompt: **modify execute permission of the makefull.sh file before to run it.**

---

# description

### *detection*

We can't detect the encoding of the file through the byte streams accurately in some time.

---

# license

AlbertGithubHome/encoding is licensed under the GNU General Public License v3.0 license. Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.
