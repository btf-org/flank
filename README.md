# Flank, the Sequel

The open-source rewrite, in C!

## What is it?
Flank is a web interface for running command-line programs (and sharing that access with others).

## What else can it do?
- Cron
- Download output
- View logs
- Pipe output of cmd1 => input of cmd2

## How does it work?
```
1. You put a command in a special directory (varies by OS)

/var
   /lib
      /flank
         wrapping-your-cmd.sh


2. Flank runs a special shell that can only run stuff there

/var
   /lib
     +-------- FLANK SHELL --------+
     |   /flank                    |
     |      wrapping-your-cmd.sh   |
     +-----------------------------+


3. There's a web interface that makes input easy and output pretty
   
```

## How do I get started?
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
