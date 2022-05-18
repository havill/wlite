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

int
wlite_wcscoll(const wchar_t *s1, const wchar_t *s2) {
    wchar_t src1[2] = { L'\0', L'\0' }, src2[2] = { L'\0', L'\0' };
    int result;

    do {
        wchar_t dst1[2], dst2[2];
        size_t n;

        do {
            src1[0] = *s1++;
            n = wlite_wcsxfrm(dst1, src1, 2);
        } while (n != 1 && src1[0] != L'\0');
        do {
            src2[0] = *s2++;
            n = wlite_wcsxfrm(dst2, src2, 2);
        } while (n != 1 && src2[0] != L'\0');
        result = wlite_wcscmp(dst1, dst2);
    } while (result == 0 && src1[0] != L'\0' && src2[0] != L'\0');
    return result;
}
