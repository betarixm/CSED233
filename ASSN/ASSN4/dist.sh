rm -r dist
mkdir dist
cp pa4.cpp dist/
cp avl.* dist/
cp hash_function.* dist/
cp hash_table.* dist/

cd dist
zip pa4.zip ./*