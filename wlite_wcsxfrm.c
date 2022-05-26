/*
 * wlite: A 16-bit Unicode based tiny <wchar.h> library with CJK features
 * Copyright (C) 2022 Eido INOUE
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Lesser Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "wlite_config.h"   // wchar_t, NULL, size_t

#include "wlite_wchar.h"    // prototypes
#include "wlite_wctype.h"
#include "wlite_stdlib.h"

size_t
wlite_wcsxfrm(wchar_t *s1, const wchar_t *s2, size_t n) {
    size_t i = 0, j = 0;
    int lwsp = !0;

    if (WLITE_IS_POSIX_(LC_COLLATE)) {
        if (n != 0) {
            wlite_wcsncpy(s1, s2, n);
        }
        return wlite_wcslen(s2);
    }
    do {
        wlite_wint_t c = (wlite_wint_t) s2[j++];

        /* reduce all runs of whitespace to one character, and transform
         * different types of whitespace into plain ' ' chars
         */
        if (wlite_iswctype(c, wlite_space_)) {
            if (lwsp) continue;
            lwsp = !0;
            c = L' ';
        }
        else {
            c = wlite_towctrans(c, wlite_tolower_);
            c = wlite_towctrans(c, wlite_tocase_);
#if WLITE_EXTENSIONS
            c = wlite_towctrans(c, wlite_tokata_);
            c = wlite_towctrans(c, wlite_tonorm_);
            if (wlite_iswctype(c, wlite_ignore_)) continue;
#endif
        }
        if (c != WLITE_WEOF) {
            if (i < n) {
                s1[i] = (wchar_t) c;
            }
            i++;
        }
    } while (s2[j] != L'\0');
    if (i != 0 && lwsp) {
        s1[--i] = L'\0';        // remove last unneeded whitespace
        lwsp = 0;
    }
    // TODO: transform to Unicode NFC (UAX #15)
    return i;
}
