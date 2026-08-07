# Flank

> A modern, open-source SSRS

## Installation 

#### Mac

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && { nohup $(which flankserver) >> $(brew --prefix)/var/log/flank/flankserver.log 2>> $(brew --prefix)/var/log/flank/flankserver.err & } && sleep 1 && open http://localhost:8083
```

Should automatically open localhost:8083

#### Debian / Ubuntu

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.84/flank_0.1.84_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.84_amd64.deb
```

Served on port 8083
