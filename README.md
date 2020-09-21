# Airwaves
Open source game for the [itch.io Open Jam](https://itch.io/jam/open-jam-2020).

Use your mouse to control a travelling radio wave, and try not to get corrupted!

## How to play
You are a wave, and you must dodge other waves that may interfere with your signal.
You can change waveform with left or right click, and you will only take damage from waves that are
the same waveform as you.

## Open source tools
This game and the engine it's built on were created using the following open source libraries:
- [GLFW](https://github.com/glfw/glfw) (Window management, input handling)
- [glad](https://github.com/Dav1dde/glad) (OpenGL header)
- [glm](https://github.com/g-truc/glm) (Math)
- [PortAudio](https://app.assembla.com/spaces/portaudio/git/source) (Audio)
- [stb_image](https://github.com/nothings/stb) (Texture loading)

In addition, the textures were created in [GIMP](https://gitlab.gnome.org/GNOME/gimp/)

## Compiling
GLFW and PortAudio will need to be compiled into static libraries first. In addition, you will need to acquire 
a [glad.c](https://glad.dav1d.de/) file for your desired version of OpenGL. Everything else is a matter of including the right folder.