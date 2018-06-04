
Debian
====================
This directory contains files used to package goodsd/goods-qt
for Debian-based Linux systems. If you compile goodsd/goods-qt yourself, there are some useful files here.

## goods: URI support ##


goods-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install goods-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your goodsqt binary to `/usr/bin`
and the `../../share/pixmaps/goods128.png` to `/usr/share/pixmaps`

goods-qt.protocol (KDE)

