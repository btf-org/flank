# Flank
Flank is a CLI wrapper that lets you solve business problems by just writing code.

First, you write something that is runnable from the CLI (script or SQL query). Then, you run `flank my-script` (roughly) and Flank moves it to a part of your computer where it can be run through a website. From there, Flank makes it easy to add guardrails, permissioning, run it on a schedule, move it to a remote machine, and so on.

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
