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
  
This library fills that gap. It provides a Standard C 99 strictly compliant library.
  
Additionally, this library provides addition features that go above and beyond what Standard C requires for East Asian, especially Japanese, support:
  
* Japanese kana, full & half width character transformations for natural language string collation and sorting
* Japanese monowidth full/half width character and string width measurement (for non-proportion dumb terminal cursor control)
* Extended Character classification that understands space, digits, alphabet, and Japanese characters
  
# Limitations
  
* Unlike glibc (but still compliant with Standard C), it provides an implementation of `wchar_t` that is 2 bytes long. For this reason, it is *not* binary compatible with glibc or other 32-bit implementations.
* Because the wide character support is only 16 bits (Unicode is 20-bits), support is only possible for characters in Plane 0 (the BMP: basic multilingual plane). Surrogate characters are handled to allow for strings using Unicode planes 1 to 15, but character classification and collation functions do not support these characters.
