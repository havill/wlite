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
  
## Compile Options
  
* `make SMALL=1`: if `SMALL` is defined (doesn't matter if it's set to 1, 0, true, or false), it will compile the source with the following features **disabled**:
  * `WLITE_EXTENSIONS=0`: <wcctype.h> & <wcsxfrm.h> extensions for Japanese (and some Korean and Chinese) Unicode will be disabled
  * `WLITE_AMBI_LOCALE=0`: wlite will not compile in Unicode data used to determine, based on the current locale, what monospaced width ambiguous characters are.
  * `WLITE_ENVIRONMENT=0`: wlite will only use the environment variable `WLITE_LC_ALL` to determine the behavior of locale sensitive functions.
* `make LARGE=1` if `LARGE` is defined (doesn't matter if it's set to 1, 0, true, or false), it will compile the source with the following features **enabled**:
  * `WLITE_XBMP_CHAR=1`: support past the first 64K Plane 0, the BMP (basic multilingual plane) will be enabled
* `make DEBUG=1`: if `DEBUG` is defined, all of the compiler's warnings will be enabled and machine code will not be optimized. Additionally, because C is not memory managed, DEBUG can be defined to the following values to assist in memory allocation, deallocation, and dangling pointer management:
  * `make DEBUG=dmalloc`: will be compiled and linked to your installed [the dmalloc library](https://dmalloc.com/), using the "dmalloc" versions of memory allocaton
  * `make DEBUG=efence`: will be compiled and linked to your installed [Electric Fence library](https://elinux.org/Electric_Fence), used to detect out of bounds memory references.

## Configuration Options

Other options that can be compiled in or out of the library can be controlled via C preprocessor macros listed and documented in the file `wlite_config.h`.
Every option and what it does is documented within that file. Macros can be set on the compiler/preprocessor command rather if you do not wish to edit the
file.

* `WLITE_REDEF_STDC`: (default setting: `!0`) If true, macros will be defined so that standard identifiers normally defined for wide character support in <stdlib.h> and <wchar.h>
   will all be re-mapped and re-written so that the relevant identifiers in your code will be prefixed with `wlite_` so they will link to this library.
* `WLITE_LC_ALL`: (default setting: `C`) if `WLITE_ENVIRONMENT` is definied as false (probably because your freestanding environment does not have or has incorrectly
   functioning <locale.h> support), this id (which is *not* a string surrounded by double quotes) will specify the locale the functions should assume. Four locales are supported:
   * `C`: an ASCII locale where the functions behave like a default hosted C environment that has not called `setlocale()`
   * `ja`: a locale for Unicode based Japanese
   * `zh`: a locale for Unicode based Chinese (simplified and traditional characters)
   * `ko`: a locale for Unicode based Korean (Hangul characters, both precomposed and combining)
* `WLITE_READ_6_BYTE_UTF8_SURROGATE`: (default setting: `0`) a surrogate sequence (a character from Plane 1 to 15 represented by 2 16-bit Unicode characters) should normally
   be encoded as a 4 byte UTF-8 sequence. There are some broken implementations that will convert it literally as two separate 3 byte UTF-8 characters.
   This is technically illegal and broken behavior, but the ability to convert into this broken sequence is provided for freestanding systems that
   have no other correct option.
* `WLITE_FFFD_WIDTH`: (default setting: `1`) the width of U+FFFD depends on the substitute glyph (if any) used to
   represent it. If you use "?" (ex. Java based character conversion), or a middle dot or
   small filled rectangle (ex. Windows), the width is one. If you use something
   like the replacement glyphs <http://crl.nmsu.edu/~mleisher/lr.html> or the
   ideograph replacement character (U+3013) (which is convenient because it
   already exists in most legacy CJK fonts), or a square with four hex symbols
   compressed in it, the width is probably two.

# wlite Extensions
  
### NAME
  
wctrans - wide-character translation mapping
  
### SYNOPSYS

```
#include "wlite_wctype.h"

wctrans_t wctrans(const char *name);
```
  
### DESCRIPTION
  
The `wctrans_t` type represents a mapping which can map a wide
character to another wide character.  Its nature is
implementation-dependent, but the special value `(wctrans_t) 0`
denotes an invalid mapping.  Nonzero `wctrans_t` values can be
passed to the `towctrans` function to actually perform the wide-
character mapping.

The `wctrans()` function returns a mapping, given by its name.  The
set of valid names depends on the `LC_CTYPE` category of the
current locale, but the following names are valid in all locales.

- `"tolower"` - realizes the tolower(3) mapping
- `"toupper"` - realizes the toupper(3) mapping
- **`"katakana"` - realizes a mapping from Japanese hiragana to katakana**
- **`"fixwidth"` - realizes a mapping that normalizes half-width kana and full-width alphanumeric characters and punctuation**
  
### RETURN VALUE
  
The `wctrans()` function returns a mapping descriptor if the name is valid.  Otherwise, it returns `(wctrans_t) 0`.
  
### NOTES

The behavior of `wctrans()` depends on the `LC_CTYPE` category of the current locale.
