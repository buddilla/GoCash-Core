
Debian
====================
This directory contains files used to package gocashd/gocash-qt
for Debian-based Linux systems. If you compile gocashd/gocash-qt yourself, there are some useful files here.

## gocash: URI support ##


gocash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gocash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gocashqt binary to `/usr/bin`
and the `../../share/pixmaps/gocash128.png` to `/usr/share/pixmaps`

gocash-qt.protocol (KDE)

