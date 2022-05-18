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
wlite_wcstombs(char *s, const wchar_t *wcs, size_t n) {
    size_t stored = 0;

    while (n != 0) {
        char utf[7] = { 0 };
        int length = wlite_wctomb(utf, *wcs++);

        if (length == -1) return (size_t) -1;
        if (((long) n - (long) length) < 0) {
            wlite_memcpy_(s, utf, n);
            n = 0;
        }
        else {
            wlite_memcpy_(s, utf, length);
            n -= (size_t) length;
        }
        if (*s == '\0') break;
        else {
            s += (size_t) length;
            stored += (size_t) length;
        }
    }
    return stored;
}
