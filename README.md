# Flank, the Sequel

The open-source rewrite, in C!

## Flank is for sharing programs
Write a script. On your computer. In whatever language. Then, from your CLI, share it with a non-engineer, as easily as you'd `cp your-script` into a new directory.
 
## Program-sharing simplifies a lot hassles
What is “BI” or “internal tools” or “dashboards” if not program-sharing? It’s just an interface around some backend code. That’s a lot of meetings, tools, and Slack messages to accomplish something we already had in 1979 (see below). Not to mention all the engineering time that is wasted running ad-hoc queries/scripts when there isn’t time to build an interface. 

## Easiest thing is just to try it

### Mac / Homebrew 

#### Installation

```bash
$ brew tap btf-org/flank
$ brew install btf-org/flank/flank

$ flank 

# hopefully self-explanatory from here :)
```

### Windows / Linux Distros

Not available... yet

## We actually had this, before
In the 70s, there were companies where everyone logged into the same Unix machine. Sharing a program was as simple as copying a script into another user’s home directory.

## But then we lost it
We abandoned the team computer for PCs, and there it went. For whatever reason, held onto the idea of sharing files (Dropbox for documents, git for code) but we lost the idea of sharing programs.

## Adding it back is actually sort of simple
The system just needs to do two things:
1. Provide an intuitive UX for non-engineers to run things.
2. Access your computer in a way it's locked down and can only do one thing (run the script).

As a mode of interaction, the CLI is actually very intuitive if you provide good prompting. It’s just missing a mouse and input fields. So Flank is just a specialized, restricted shell with a thin web client. 
