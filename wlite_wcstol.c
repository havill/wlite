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

#include <errno.h>   // errno, EILSEQ, ERANGE
#include <limits.h>  // INT_MIN, ULONG_MAX, LONG_MIN

#include "wlite_config.h"   // wchar_t, NULL, size_t

#include "wlite_wchar.h"    // prototypes
#include "wlite_wctype.h"
#include "wlite_stdlib.h"

long
wlite_wcstol(const wchar_t *s, wchar_t **endptr, int base) {
    long long i;

    i = wlite_widetoll_(s, endptr, base);
    if (i > LONG_MAX) {
        errno = ERANGE;
        i = LONG_MAX;
    }
    if (i < LONG_MIN) {
        errno = ERANGE;
        i = LONG_MIN;
    }
    return (long) i;
}
