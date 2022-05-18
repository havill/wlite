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

#include "wlite_config.h"

int
wlite_map_t_cmp_(const void *x, const void *y) {
    const wlite_map_t_ *a = x, *b = y;

    if (a->from < b->from) return -1;
    if (a->from > b->from) return +1;
    return 0;
}

int
wlite_wc_t_cmp_(const void *x, const void *y) {
    const wlite_wc_t_ *a = (const wlite_wc_t_ *) x;
    const wlite_wc_t_ *b = (const wlite_wc_t_ *) y;

    if (*a < *b) return -1;
    if (*a > *b) return +1;
    return 0;
}

int
wlite_locale_cmp_(const void *x, const void *y) {
    const char *a = x, *b = y;

    if (a == NULL) a = "";
    if (b == NULL) b = "";
    do {
        if (*a == '*' || *b == '*') break;
        if (*a < *b) return -1;
        if (*a > *b) return +1;
    } while (*a++ != '\0' && *b++ != '\0');
    return 0;
}
