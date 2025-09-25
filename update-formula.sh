curl -L https://github.com/btf-org/flank/archive/refs/heads/main.tar.gz -o /tmp/flank-main.tar.gz
SHA=$(shasum -a 256 /tmp/flank-main.tar.gz | awk '{print $1}')
rm /tmp/flank-main.tar.gz
sed -i "s/sha256 \".*\"/sha256 \""$SHA"\"/" flank.rb
