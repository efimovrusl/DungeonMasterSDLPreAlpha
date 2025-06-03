SDL2_PATH=$(brew --prefix sdl2)
SDL2_MIXER_PATH=$(brew --prefix sdl2_mixer)

# Copy libraries using dynamic paths
cp -aRv "$SDL2_PATH/include/" resource/SDL/
cp -aRv "$SDL2_PATH/lib/" resource/SDL/lib/
cp -aRv "$SDL2_MIXER_PATH/include/" resource/SDL/
cp -aRv "$SDL2_MIXER_PATH/lib/" resource/SDL/lib/