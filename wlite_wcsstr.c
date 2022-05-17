/*
 * $Id: wlite_wcsstr.c,v 1.1 2002/12/10 21:57:58 havill Exp havill $
 *
 * Copyright (C) 2003  Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Original Author: Adrian Havill <havill@redhat.com>
 *
 * Contributors:
 */

#include "wlite_config.h"   // wchar_t, NULL, size_t

#include "wlite_wchar.h"    // prototypes
#include "wlite_wctype.h"
#include "wlite_stdlib.h"

wchar_t *
wlite_wcsstr(const wchar_t *s1, const wchar_t *s2) {
    if (*s2 == L'\0') return (wchar_t *) s1;
    while ((s1 = wlite_wcschr(s1, *s2)) != NULL) {
        const wchar_t *sc1, *sc2;

        for (sc1 = s1, sc2 = s2;;) {
            if (*++sc2 == L'\0') return (wchar_t *) s1;
            else if (*++sc1 != *sc2) break;
        }
        s1++;
    }
    return NULL;
}
