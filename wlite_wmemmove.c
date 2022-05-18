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

wchar_t *
wlite_wmemmove(wchar_t *s1, const wchar_t *s2, size_t n) {
    wchar_t *sc1 = (wchar_t *) s1;
    const wchar_t *sc2 = (const wchar_t *) s2;

    if (sc2 < sc1 && sc1 < sc2 + n) {
        for (sc1 += n, sc2 += n; n != 0; n--) {
            *--sc1 = *--sc2;
        }
    }
    else while (n != 0) {
        *sc1++ = *sc2++;
        --n;
    }
    return s1;
}
