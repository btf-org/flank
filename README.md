# Flank
I'm a data analytics consultant and I built the following to speed up my work. I use it for everything from BI to internal tools to setting up pipelines.

# Examples
- Node
  - Run a Node script on a schedule
- R
  - Run an R script on a schedule
  - Build a pipeline of R scripts

## Run a Node script on a schedule
1. [Install Flank](#install-flank)
2. [Start Flank](#start-flank)
3. Add your script to Flank
   ```bash
   # assuming a Node script called "hello.js"...
   flank add hello.js
   ```
4. Schedule exeuction of script through Flank website

## Install Flank

### Mac

```bash
brew tap btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu / apt

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time


## Start Flank

```bash
flank start
```

## Update Flank

### Mac
```bash
brew update # should update all your "taps", including btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time

