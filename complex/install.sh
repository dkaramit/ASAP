if [ ! -d "lib" ]; then
  mkdir lib
fi

cd src/

g++ -c functions.cpp operators.cpp funcs.cpp

ar rvs lib-complex.a *o
mv lib-complex.a ../lib/
mkdir obj
mv *o obj/
rm -r obj
cd ../

echo "To uninstall, remove the lib directory"


echo "For examples run:"
echo "./compile.sh example"
echo "chmod +x ./example ; ./example"
