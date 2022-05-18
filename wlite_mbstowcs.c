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
wlite_mbstowcs(wchar_t *wcs, const char *s, size_t n) {
    wlite_mbstate_t internal = { 0 };  // always begin in initial state
    size_t stored = 0;

    while (n != 0) {
        size_t length;

#if WLITE_GENERATE_SURROGATES || !WLITE_XBMP_CHAR
        if (n > 1) {
            internal.flags_ |= WLITE_MBSTATE_SURROGATE_;
        }
        else internal.flags_ &= ~WLITE_MBSTATE_SURROGATE_;
#endif
        length = wlite_mbrtowc(wcs, s, n, &internal);
        wcs += (size_t) internal.wcout_;
        n -= (size_t) internal.wcout_;
        if (length == (size_t) -1 || length == (size_t) -2) return (size_t) -1;
        else if (length == 0) break;
        else {
            stored += length;
            s += length;
        }
    }
    return stored;
}
