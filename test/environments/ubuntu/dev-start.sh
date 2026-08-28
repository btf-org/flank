docker run --platform linux/amd64 -p 8085:8084 -v "$PWD":/flank-repo -v $(brew --prefix)/var/flank:/var/lib/flank -it ubuntu-tester bash
