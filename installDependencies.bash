# Install SDL2, SDL2_image, SDL2_TTF, json_develop, and hopscotch_map


# Make and clean dirs
if [[ -d tmp ]]
then
	rm -rf tmp
fi

if [[ -d Dependencies ]]
then
	rm -rf Dependencies
fi

if [[ -d executable ]]
then
	rm -rf executable
fi

mkdir tmp
mkdir Dependencies
mkdir executable

cd Dependencies
mkdir SDL_FULL
cd SDL_FULL
mkdir x86
mkdir include
cd ../../

# Install SDL2
cd tmp
if ! wget https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip
then
	echo "Could not download SDL2."
	exit 1
fi

unzip SDL2-devel-2.0.14-VC.zip

rm SDL2-devel-2.0.14-VC.zip

cd ../

mv tmp/SDL2-2.0.14/include/*.h Dependencies/SDL_FULL/include
mv tmp/SDL2-2.0.14/lib/x86/*.lib Dependencies/SDL_FULL/x86
mv tmp/SDL2-2.0.14/lib/x86/*.txt executable
mv tmp/SDL2-2.0.14/lib/x86/*.dll executable

# Install SDL2_image
cd tmp
if ! wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
then 
	echo "Could not download SDL2_image."
	exit 1
fi

unzip SDL2_image-devel-2.0.5-VC.zip

rm SDL2_image-devel-2.0.5-VC.zip

cd ../


mv tmp/SDL2_image-2.0.5/include/*.h Dependencies/SDL_FULL/include/
mv tmp/SDL2_image-2.0.5/lib/x86/*.lib Dependencies/SDL_FULL/x86
mv tmp/SDL2_image-2.0.5/lib/x86/*.txt executable
mv tmp/SDL2_image-2.0.5/lib/x86/*.dll executable

# Install SDL2_TTF
cd tmp
if ! wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip
then 
	echo "Could not download SDL2_ttf"
	exit 1
fi

unzip SDL2_ttf-devel-2.0.15-VC.zip

rm SDL2_ttf-devel-2.0.15-VC.zip

cd ../

mv tmp/SDL2_ttf-2.0.15/include/*.h Dependencies/SDL_FULL/include
mv tmp/SDL2_ttf-2.0.15/lib/x86/*.lib Dependencies/SDL_FULL/x86
mv tmp/SDL2_ttf-2.0.15/lib/x86/*.txt executable
mv tmp/SDL2_ttf-2.0.15/lib/x86/*.dll executable

# Install nlohmann/json
cd tmp
if ! wget https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip
then
	echo "Could not download nlohmann/json"
	exit 1
fi

mkdir json
unzip include.zip -d json
rm include.zip

cd ../

mv tmp/json/ Dependencies/


# Install Tessil/hopscotch-map
cd tmp
if ! git clone https://github.com/Tessil/hopscotch-map
then
	echo "Could not clone Tessil/hopscotch-map"
	exit 1
fi

cd ../
mv tmp/hopscotch-map/ Dependencies/

rm -rf tmp

echo "Installation complete. Run compile.bash to compile project."





