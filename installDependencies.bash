# Install json_develop and hopscotch_map
# Unix only


# Make and clean dirs
if [[ -d tmp ]]
then
	rm -rf tmp
fi

if [[ -d Dependencies ]]
then
	rm -rf Dependencies
fi

mkdir tmp
mkdir Dependencies

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





