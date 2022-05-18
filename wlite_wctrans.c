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

wlite_wctrans_t
wlite_wctrans(const char *name) {
    if (wlite_strcmp_(name, "toupper") == 0) return wlite_toupper_;
    if (wlite_strcmp_(name, "tolower") == 0) return wlite_tolower_;
#if WLITE_EXTENSIONS
    if (wlite_strcmp_(name, "katakana") == 0) return wlite_tokata_;
    if (wlite_strcmp_(name, "fixwidth") == 0) return wlite_tonorm_;
#endif
    return (wlite_wctrans_t) 0;
}
