rm -r Ionosphere_build
mkdir Ionosphere_build
rm -r Ionosphere_out
mkdir Ionosphere_out

cd Ionosphere_build
cmake -DGeant4_DIR=/home/souravspace/Install/GEANT4/geant4/geant4.10.05-install/lib/Geant4-10.5.1 ../Ionosphere
make -j4


