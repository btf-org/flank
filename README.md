# Flank
At a lot of companies, after you've written a Python script or SQL query, the business problem is far from solved. There is often a lot of work left to either 1) safely expose whatever you built to a non-engineer, or 2) automatically run it on some sort of trigger.

Flank is a CLI wrapper that allows engineers to incrementally "scale up" solutions by providing UI, guardrails, and permissioning around solutions that work on the CLI. It allows a single engineer to solve a problem end-to-end in the programming language of their choice, without necessitating meetings with designers, cloud engineers, etc.

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
