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

void *
wlite_bsearch_(const void *key, const void *base, size_t n, size_t size,
               wlite_cmp_t_ cmp) {
    const char *left = (const char *) base;
    size_t right = n;

    while (right != 0) {
        const char *const middle = left + size * (right / 2);
        const int result = (*cmp)(key, middle);

        if (result < 0) {
            right = right / 2;
        }
        else if (result > 0) {
            left = middle + size;
            right -= right / 2 + 1;
        }
        else return (void *) middle;
    }
    return NULL;
}
