latest_tag=$(git tag --list "v*.*.*" --sort=-v:refname | head -n1)
version=${latest_tag#v}
echo "Latest tag is $version"
read -rp "Hit [enter] to continue"
mkdir -p releases/flank_"$version"_amd64/DEBIAN
mkdir -p releases/flank_"$version"_amd64/usr/local/bin
mkdir -p releases/flank_"$version"_amd64/usr/share/flank
mkdir -p releases/flank_"$version"_amd64/var/lib/flank
mkdir -p releases/flank_"$version"_amd64/lib/systemd/system
mkdir -p releases/flank_"$version"_amd64/etc/default

cp build/DEBIAN/control build/DEBIAN/postinst build/DEBIAN/conffiles releases/flank_"$version"_amd64/DEBIAN/
cp build/DEBIAN/flankserver.service releases/flank_"$version"_amd64/lib/systemd/system
cp build/DEBIAN/flank releases/flank_"$version"_amd64/etc/default/flank

sed -i '' 's/Version: .*$/Version: '$version'/' releases/flank_"$version"_amd64/DEBIAN/control
chmod 775 releases/flank_"$version"_amd64/DEBIAN/postinst
cp iflank releases/flank_"$version"_amd64/usr/local/bin/
docker run --platform linux/amd64 --rm -v "$PWD":/work -w /work flank-debian-builder bash -c "gcc flankserver.c -o releases/flank_"$version"_amd64/usr/local/bin/flankserver"
cp index.html releases/flank_"$version"_amd64/usr/share/flank/

docker run --platform linux/amd64 --rm -v "$PWD":/work -w /work flank-debian-builder bash -c "dpkg-deb --build releases/flank_"$version"_amd64"

printf 'https://github.com/btf-org/flank/releases/new'
