latest_tag=$(git tag --list "v*.*.*" --sort=-v:refname | head -n1)
version=${latest_tag#v}
echo "Latest tag is $version"
read -rp "Hit [enter] to continue"
mkdir -p releases/flank"$version"_amd64/DEBIAN
mkdir -p releases/flank"$version"_amd64/usr/local/bin
mkdir -p releases/flank"$version"_amd64/usr/share/flank
mkdir -p releases/flank"$version"_amd64/var/lib/flank

cp build/DEBIAN/control build/DEBIAN/postinst releases/flank"$version"_amd64/DEBIAN/
chmod 775 releases/flank"$version"_amd64/DEBIAN/postinst
cp flank iflank releases/flank"$version"_amd64/usr/local/bin/
docker run --rm -v "$PWD":/work -w /work ubuntu bash -c "apt update && apt install -y gcc && gcc flankserver.c -o releases/flank"$version"_amd64/usr/local/bin/flankserver"
cp index.html releases/flank"$version"_amd64/usr/share/flank/

docker run --rm -v "$PWD":/work -w /work ubuntu bash -c "apt update && apt install -y tree && tree && pwd && dpkg-deb --build releases/flank"$version"_amd64"

