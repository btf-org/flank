# Flank

Flank is an app for running your scripts.

In the same way that Postman is a dedicated UI for `curl`, Flank is a dedicated UI for the command that runs your script (e.g. `python filter-data.py --year 2019`).

## Flank is for frequent script-runners

There is overhead in having a separate app, and, generally, it's only worth it if you spend a lot of time running scripts. This is doubly true if you run scripts on behalf of other people.

## Advantages over CLI

Normally you'd run a script from the CLI by typing in `python filter-data.py ...`. Flank is a dedicated app that replaces that process, with the following advantages:

- Inputs fields
- Stores history of all runs (both inputs and outputs)
- Non-engineers can use it

## Advantages over exposing a script through a web app

- It's as fast as the CLI

