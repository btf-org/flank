# Flank

## What
Flank makes CLI commands easy to use, even for non-engineers. It's a browser-based UI.

## Comparison
Compared to other ways of building software, it has the speed & power of the CLI combined with the guardrails & easy of use of a designed application

## Who's it for
Backend engineers, SQL people, data scientists

## What else can it do
Flank ships with a “standard library” of programs that makes it easy to accomplish other tasks natively in the OS, without having to use other tools:
- Cron jobs
- Pipelines
- Monitoring running jobs
- Changelog
- Audit user actions

## Example
Teammate: “Hey can you get me those updated numbers?” You run a Python script on your machine and email them over.

Normally, you’re either stuck running the script yourself, getting your teammate on the CLI (dangerous), or hosting the code and building an interface for it (time consuming)

With Flank, you just share access and it handles the guardrails and creation of a simple interface.

## Compatible with
POSIX Shells

## Getting started
### Mac / Homebrew 

#### Installation

```bash
$ brew tap btf-org/flank
$ brew install btf-org/flank/flank

$ flank 
```

#### Getting updates
```bash
$ brew update # should update all your "taps", including btf-org/flank
$ brew install btf-org/flank/flank
```

### Windows / Linux Distros

Not available... yet
