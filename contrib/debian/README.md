
Debian
====================
This directory contains files used to package lincd/linc-qt
for Debian-based Linux systems. If you compile lincd/linc-qt yourself, there are some useful files here.

## linc: URI support ##


linc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install linc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your linc-qt binary to `/usr/bin`
and the `../../share/pixmaps/linc128.png` to `/usr/share/pixmaps`

linc-qt.protocol (KDE)

