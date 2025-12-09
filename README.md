# Flank
Flank is a wormhole from your browser to your command line.

It lets you (or, even better, non-technical teammates) runs scripts on your machine (or a remote machine). 

By setting up a wormhole for you and your teammates, you can avoid things like...
- having to run the same ad-hoc query twice
- having to build an internal website to expose a CRUD operation
- having to deploy a script to a cloud function/API just to make it triggerable
- having to use an orchestration tool to run tasks on a schedule
  
## Mac / Homebrew

#### Installation

```bash
$ brew tap btf-org/flank
$ brew install btf-org/flank/flank
```

#### Usage
```bash
$ flank
```

#### Getting updates
```bash
$ brew update # should update all your "taps", including btf-org/flank
$ brew install btf-org/flank/flank
```

## Linux / Ubuntu / apt

#### Installation

```bash
# From any directory
$ wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
$ sudo apt install ./flank_0.1.36_amd64.deb
```

#### Usage
```bash
# From any directory
$ . flank
```

#### Getting updates
Same as installation process, but replace the version numbers with the new one

## Windows / Other Linux Distros

Not available... yet
