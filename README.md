# Flank

Flank is a tool for "go to" engineers.

It is small bridge from engineer-land (terminal) to user-land (browser).

It works with any language that can be invoked from the terminal, because it just forwards `stdout` from your terminal to your browser. It can be used to quickly build dashboards/apps, schedule cron jobs, run scripts away from your desk, etc.

<img width="838" height="292" alt="Can you run that for me github" src="https://github.com/user-attachments/assets/aeec2b5d-f39a-45b9-a5f6-b9dbd686b6d0" />

## Contents 

- [Installation](#installation)
- [A quick webpage for curl](#a-quick-webpage-for-curl)
- [How to configure the UI](#how-to-configure-the-ui)
- [What tools have people replaced with Flank?](#what-tools-have-people-replaced-with-flank)
- [Caveats / Limitations](#caveats--limitations)

  
## Installation

#### Mac

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && { nohup $(which flankserver) >> $(brew --prefix)/var/log/flank/flankserver.log 2>> $(brew --prefix)/var/log/flank/flankserver.err & } && sleep 1 && open http://localhost:8083
```

Should automatically open localhost:8083

#### Linux

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.83/flank_0.1.83_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.83_amd64.deb
```

Served on port 8083

## A quick webpage for `curl`

1. Click "Create Cmd" on the bottom bar
2. Choose the "Hello World" option
3. Remove the `echo`, paste in the following, and click "Save"

```bash
# @description This fetches the content from the URL
# ${method} @select @values `printf 'GET\nPOST\nPUT\nDELETE\nPATCH\nHEAD\nOPTIONS\nCONNECT\nTRACE'`
# ${url} @type url @colspan 4

curl -X "${method}" "${url}"
```

Now the page should look something like this:

<img width="838" height="550" alt="curl-ex-2" src="https://github.com/user-attachments/assets/3d95bdcf-e984-4768-a9aa-fa96524ca667" />


## How to configure the UI

You can tell Flank, "Make this field a dropdown". You do this through "decorations", which are just structured comments directly in the script.

### Anatomy of a decoration

```bash
# @description This fetches the content from the URL
  ──────┬─────
        │
        └─ command-level directive (no variable name)

# ${method} @select @values `echo $'GET\nPOST\nPUT\nDELETE\nPATCH\nHEAD\nOPTIONS\nCONNECT\nTRACE'`
                            ────┬─────────────────────────────────────────────────────────────────
                                │
                                │
                                └─ certain directives can accept
                                   backtick expressions as their value

# ${url} @type url @colspan 4
  ───┬── ──┬── ─┬─ ────┬─────
     │     │    │      │
     │     │    │      └─ (one line can contain multiple directives)
     │     │    │     
     │     │    └─ value 
     │     │
     │     └─ directive
     │
     └─ variable name

curl -X "${method}" "${url}"
        ─────┬─────
             │
             └─ variable must use curl brackets, like ${var}, not $var
````

### Command-Level

| Directive | Value | Default | Notes |
|-----------|-------|---------|-------|
| `@description` | none | - | Renders text underneath the title |
| `@page` | number | - | Splits the script into multiple forms |
| `@pass_hidden` | Space-separated list of vars | - | Used with @page. Passes any variables from that step to the next step. |

### Variable-Level

| Directive | Value | Default | Notes |
|-----------|-------|---------|-------|
| `@input` | none | yes | Renders `<input>`. Use with `@type` to control kind. |
| `@textarea` | none | no | Renders `<textarea>`. Increases default `@colspan` to 6. |
| `@select` | none | no | Renders `<select>`. Requires `@values`. |
| `@system_filepath` | none | no | Allows user to choose a filepath (not file) on the computer |
| `@type` | HTML input type (`text`, `number`, `email`, `url`, `radio`, `checkbox`, …) | `text` | Maps to the HTML `type` attribute. `radio` and `checkbox` require `@values`. |
| `@values` | backtick shell expression | — | One option per line of output. Required for `@select`, `@type radio`, and `@type checkbox`. |
| `@default` | literal string, backtick shell expression, or ${variable} if using `@page` (see above) | — | Sets initial value. `\n` in literals becomes a newline. Matching `@select` option is pre-selected. |
| `@colspan` | number (1 - 6) | `2` (`6` for `@textarea`) | Grid column span. |
| `@description` | string | — | Small subtitle rendered beneath the variable name. |
| `@capturetab` | none | no | Tab key inserts a tab character instead of moving focus. |

Where possible, I've tried to mirror vanilla HTML and not add any additional naming conventions. As an example, to specify that a variable be represented by a `<textarea/>`, you use `@textarea`, but to specify it be represented by radio buttons, you use `@input @type radio`, since radios are `<input type="radio"/>`.


## What tools have people replaced with Flank?

- PowerBI (SQL developer just exposes a query that generates a CSV)
- Portions of a React app (Python developer just exposes scripts that return updated sales data)
- Airflow (Data Scientist can edit pipelines/schedules and also run tasks on an ad-hoc basis when they fail)


## Caveats / Limitations

- As it currently stands, users can write destructive shell scripts, so beware! I am currently using this is in a small team, high-trust environment, so I haven't invested any effort into RBAC.
- The logic in flankserver.c is pretty unpolished. I'm pretty sure if you open 64 tabs, it'll just crash the server. A lot of these problems have been masked by systemctl's automatic restart behavior...
