# Install Flank

### Mac

(If you haven't installed Homebrew, [see here](https://brew.sh/))

```bash
brew tap btf-org/flank
brew install btf-org/flank/flank
brew services start flank
```

### Linux / Ubuntu / apt

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.60/flank_0.1.60_amd64.deb
sudo FLANK_USER=$(whoami) apt install ./flank_0.1.60_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time


# Update Flank

### Mac
```bash
brew update # should update all your "taps", including btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.60/flank_0.1.60_amd64.deb
sudo FLANK_USER=$(whoami) apt install ./flank_0.1.60_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time
