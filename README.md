
# **About MAME_PLAYABLE** #

mame_playable is an up-to-date repo based on the official release of mame64 to add minor quality-of-life improvements to help emulate games better for playing.

It was initially a build to include overclocked settings for a few games like Metal Slug 2 and Double Dragon.
The fork will always keep up-to-date with the official mame release. If new playable games or some improvements are made in the official repo, it will also merge those changes as well.

mame_playable will only overclocked emulated CPUs for games tested to have worked better without glitches, freezes or crashes.
Games that rely on slowdowns such as Cave shooters will not have their CPUs overclocked.

Do not report any bugs to the mame dev or here on those games. If we find a problem to overclocked games, we're going to simply revert the change and live with the slowdowns.
Please don't bother the mame devs especially.

If you have any games with slowdowns that can be fixed with overclocking, let us know and we'll run through a heavy testing to make sure they work, and apply changes.

# **List of Enhancements** #
1. Overclocked emulated CPUs for games with slowdowns. Only supports games that passed overclock testing.
- Double Dragon 1
- Metal Slug 2 Turbo

2. Raised maximum volume for emulated sound channels from 2.0 to 10.0. This should greatly help with low-volume games like ones from Psikyosh.

3. Validates English translation hacks as main ROMs for machines that do not have English translations.
- Valkyrie No Densetsu

License
=======
The MAME project as a whole is distributed under the terms of the [GNU General Public License, version 2](http://opensource.org/licenses/GPL-2.0) or later (GPL-2.0+), since it contains code made available under multiple GPL-compatible licenses. A great majority of files (over 90% including core files) are under the [BSD-3-Clause License](http://opensource.org/licenses/BSD-3-Clause) and we would encourage new contributors to distribute files under this license.

Please note that MAME is a registered trademark of Gregory Ember, and permission is required to use the "MAME" name, logo, or wordmark.

<a href="http://opensource.org/licenses/GPL-2.0" target="_blank">
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">
</a>

    Copyright (C) 1997-2019  MAMEDev and contributors

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Please see [LICENSE.md](LICENSE.md) for further details.
