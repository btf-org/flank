docker run --platform linux/amd64 -v "$PWD":/flank-repo -v $(brew --prefix)/var/flank:/var/lib/flank -it ubuntu:24.04 bash
