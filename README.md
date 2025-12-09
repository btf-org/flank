# Flank
Flank is a wormhole from your browser to your command line.

**Who's it for:** Backend engineers, SQL developers, data scientists

**How do you use it:** Write a script and then run `$ flank myscript.py`. Flank will make a webpage for running that script. You'll see output in the browser as if you ran it in the terminal. Then you can add input fields, guardrails, and access control without writing HTML/CSS/JS. 

**Integrations:** Anything that's runnable from the CLI on Mac/Linux.

**Problem solved:** It depends. For a SQL developer asked to do lot of ad-hoc analysis, Flank saves him from having to run the same query twice. For a data scientist needing more compute, it allows him to just use EC2 and not have to futz with Docker, AWS Batch, and Airflow.

**Architecture:** Flank runs a web server on a computer (your laptop or a remote machine), and it exposes selected scripts on that computer.

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

Not available at this time
