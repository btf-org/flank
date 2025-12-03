# Flank
Flank is a web interface for your CLI.

The core use case is creating a web page for running a script/query. From there, you can go in various directions to productiionze it (e.g. guardrails, permissioning, etc.).

It works like this:
- You write a script
- You run `$ flank my-script` (roughly) and Flank creates another script for running your script
- This other script is triggerable through the web interface

The main benefit to users is that they can ship tools by just writing backend code.

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
