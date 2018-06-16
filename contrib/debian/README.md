
Debian
====================
This directory contains files used to package jaded/jade-qt
for Debian-based Linux systems. If you compile jaded/jade-qt yourself, there are some useful files here.

## jade: URI support ##


jade-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install jade-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your jadeqt binary to `/usr/bin`
and the `../../share/pixmaps/jade128.png` to `/usr/share/pixmaps`

jade-qt.protocol (KDE)

