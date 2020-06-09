rm -r dist
mkdir dist
cp pa5.cpp dist/
cp hash* dist/
cp bloom* dist/
cp graph* dist/

cd dist
zip pa5.zip ./*