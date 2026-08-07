# Physics Engine

A simple plugin based physics engine brought to you by crux

## Development

### Install dependencies:

Ubuntu:
```
sudo apt-get install -y libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

Fedora:
```
sudo dnf install alsa-lib-devel libX11-devel libXrandr-devel libXi-devel mesa-libGL-devel mesa-libGLU-devel libXcursor-devel libXinerama-devel wayland-devel libxkbcommon-devel
```

### Build Makefile

```
cmake -B build
```

### Create executable

```
cd build
make
```

