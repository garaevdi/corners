# Corners
Simple utility for drawing rounded corners on every monitor, just like [this gnome extension](https://github.com/lennart-k/gnome-rounded-corners), but for wayland WMs. Written in C++ using [peel](https://gitlab.gnome.org/bugaevc/peel).

# Building
Build dependencies:

- gtk4
- gtk4-layer-shell

Build
```
git clone https://github.com/garaevdi/corners.git
cd corners
meson setup _build
ninja -C _build
```

# Installing
```
sudo ninja -C _build install
```

# Uninstalling
```
sudo ninja -C _build uninstall
```

# Configuring
Change corner radius (range: 0-128)
```
gsettings set com.github.garaevdi.corners corner-radius 16
```