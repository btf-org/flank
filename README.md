# Flank, the Sequel

The open-source rewrite, in C!

## Mac / Homebrew 

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

## Windows / Linux Distros

Not available... yet

## About
#### Flank is for sharing programs
Write a script, on your computer, in whatever language. Then, from your CLI, share it with a non-engineer, as easily as you'd `cp your-script` into a new directory.

#### We actually had this... a long time ago
In the 70s, there were companies where everyone logged into the same Unix machine. Sharing a program really was as simple as `cp your-script` into another user’s home directory.

#### But then we lost it
We abandoned the team computer for PCs, and there it went. We held onto the idea of sharing files (Dropbox for documents, git for code), but for some reason we lost the idea of sharing programs.

#### Program-sharing is awesome
The way we currently share programs (i.e. allow a non-engineer to trigger backend code) is to build a full-blown website/BI tool.

If you can just... give the user the program they want... safely... intuitively... it eliminates lots of meetings, JIRA tickets, and tools.

#### How do we bring back program-sharing?
Your workstation can do 98% of the work. It's just missing 2 things:
1. Your CLI is not an intuitive interface for entering parameters and viewing/downloading results.
2. Your CLI has no guardrails. And poor out-of-the-box access control.

So Flank is a highly restricted, interactive shell. And then there's a thin web client on top.
