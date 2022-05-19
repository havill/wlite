# wlite
A 16-bit Unicode based tiny Standard C 99 conforming &lt;wchar.h> library implementation with CJK features

# Purpose
At the advent of Y2K, Linux distributions were becoming truely internationalized and based on Unicode. Prior to this, most Linux distributions were
localized for a nationalized character set and encoding (ex. JIS X 0208 via Shift-JIS or more commonly EUC-JP for Unix based systems) often at the
expense of cross-compability with American and European distributions that used the charset/enc of Latin-1.

The technology -- Unicode based libraries, fonts, and input methods -- to have one release not just for the Americas and Europe, but East Asia as well,
was available for the release of what was then known as "Red Hat Linux 8.0".

However, at the time hardware limitations amongst the general public were such that it was still necessary to have a bootstrap environment, which
included the kernel, framebuffer-bitmapped graphics based terminal (X Windows was too large), drivers, and installer, fit on a 3.5 inch 1.44MB
floppy microdiskette.

glibc 2 had just been recently released and included true Unicode I18N support, but the library was far too big for this diskette environment. The
combination of all of its I18N metadata and conversion data was massive, and the huge (in comparison to the 256 character Latin-1 bitmapped fonts of
the time) multi-thousand character CJK (Chinese, Korean, Japanese) ideograph supporting fonts meant that real estate on the disc was extremely tight.

So instead of including a full glibc 2 on this floppy environment, a specialized minimal c library was used. However, this C library lacked the
relatively modern Standard C Wide Character library <wchar> which was used to provide standardized Unicode UCS-2 (16 bit Java "char" compatible)
string handling and transformations back and forth to the multibyte Unicode UTF-8 encoding.
  
This library fills that gap. It provides a Standard C 99 strictly compliant library for either freestanding C systems or hosted C systems (via macro overrides).
  
# Configuring & Installing
  
wlite can be compiled and installed on any system with a GNU compiler & toolchain. The make file understands and uses almost all the common
GNU make targets, including (but not limited to):
  
* `make`: will create a library / archive file that can be used to staticly link to C object files to produce a binary executable
* `make check`: will run simple unit/sanity tests against the compiled library
* `make install`: will install the archive/library and header file in the standard place on your system (usually `/usr/local/lib` and `/usr/local/include` on POSIX systems)
* `make uninstall`: will remove the files installed by the above command
