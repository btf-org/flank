# Flank, the Sequel

The open-source rewrite, in C!

## What is Flank

Flank is a tool for sharing programs from your CLI, with a simple UI and built-in guardrails.

## How does Flank help engineers

Flank allows backend engineers to solve business problems by themselves, by just writing code in their favorite language. It eliminates lots of meetings, tools, and messages.

## Quickstart

```bash
$ brew tap blahblahblah
$ brew install flank

$ flank 

# hopefully self-explanatory from here :)
```

## Background and Motivation

I discovered the Unix ecosystem late in life. It blew my mind. I like having my own personal computer, but I kept thinking about how wild it would be to work at a company where everyone used one Unix machine. Especially if you worked at Bell, and all other engineers were future Turing Award winners. That'd be nice.

At this time, I was a data engineer, and I was constantly re-running jobs for people. Living in this hellish cyberspace between Slack and the AWS Console. And I realized how simple this was in 1979. I could have just moved the program into the user's home directory and _they could run it whenever they wanted to!_

## How does Flank work

There are a couple constraints from the old days of Unix that make program-sharing difficult today:

- The interface has no mouse (bad for user)
- The interface has no guardrails (bad for engineer)
- The permissioning system doesn't natively support Access Control Lists (ACLs) or Principle of Least Privilege (PoLP)

Flank is a specialized, restricted shell with a simple web interface that sits on top. The hope is that we can bring the power (of Unix) to the people!
