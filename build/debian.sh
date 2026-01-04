latest_tag=$(git tag --list "v*.*.*" --sort=-v:refname | head -n1)
version=${latest_tag#v}
echo "Latest tag is $version"
read -rp "Hit [enter] to continue"
mkdir -p releases/flank_"$version"_amd64/DEBIAN
mkdir -p releases/flank_"$version"_amd64/usr/local/bin
mkdir -p releases/flank_"$version"_amd64/usr/share/flank
mkdir -p releases/flank_"$version"_amd64/var/lib/flank

cp build/DEBIAN/control build/DEBIAN/postinst build/DEBIAN/install releases/flank_"$version"_amd64/DEBIAN/
cp build/DEBIAN/flankserver.service releases/flank_"$version"_amd64/
sed -i '' 's/Version: .*$/Version: '$version'/' releases/flank_"$version"_amd64/DEBIAN/control
chmod 775 releases/flank_"$version"_amd64/DEBIAN/postinst
cp flank iflank releases/flank_"$version"_amd64/usr/local/bin/
docker run --platform linux/amd64 --rm -v "$PWD":/work -w /work flank-debian-builder bash -c "gcc flankserver.c -o releases/flank_"$version"_amd64/usr/local/bin/flankserver"
cp index.html releases/flank_"$version"_amd64/usr/share/flank/

docker run --platform linux/amd64 --rm -v "$PWD":/work -w /work flank-debian-builder bash -c "dpkg-deb --build releases/flank_"$version"_amd64"

git status
read -rp "Hit [enter] to commit & push ./releases"
git add releases
git commit -m "debian $latest_tag"
git push
printf 'https://github.com/btf-org/flank/releases/new'
