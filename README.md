# Flank

Flank is a tool for exposing shell commands, but with guardrails. I use it to take myself out of the loop on ad-hoc things that my teammates need.

FYI, it is currently lacking any concept of users or RBAC, and I use it in a high-trust setting, so this is very much a prototype of a "real" tool.

## Contents 

- [Installation](#installation)
- [A quick webpage for curl](#a-quick-webpage-for-curl)
- [The decoration API](#the-decoration-api)
- [How it works under the hood](#how-it-works-under-the-hood)

  
## Installation

#### Mac

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && nohup $(which flankserver) >> $(brew --prefix)/var/log/flank/flankserver.log 2>> $(brew --prefix)/var/log/flank/flankserver.err
```

#### Linux

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

## A quick webpage for `curl`



## The decoration API

### Command-Level

| Directive | Value | Default | Notes |
|-----------|-------|---------|-------|
| `@description` | none | - | Renders text underneath the title |

### Variable-Level

| Directive | Value | Default | Notes |
|-----------|-------|---------|-------|
| `@input` | none | yes | Renders `<input>`. Use with `@type` to control kind. |
| `@textarea` | none | no | Renders `<textarea>`. Increases default `@colspan` to 6. |
| `@select` | none | no | Renders `<select>`. Requires `@values`. |
| `@type` | HTML input type (`text`, `number`, `email`, `url`, `radio`, `checkbox`, …) | `text` | Maps to the HTML `type` attribute. `radio` and `checkbox` require `@values`. |
| `@values` | backtick shell expression | — | One option per line of output. Required for `@select`, `@type radio`, and `@type checkbox`. |
| `@default` | literal string or backtick shell expression | — | Sets initial value. `\n` in literals becomes a newline. Matching `@select` option is pre-selected. |
| `@colspan` | number | `2` (`6` for `@textarea`) | Grid column span. |
| `@description` | string | — | Small subtitle rendered beneath the variable name. |
| `@capturetab` | none | no | Tab key inserts a tab character instead of moving focus. |
| `@ignore` | none | no | Excludes the variable from the form entirely. |

## How it works under the hood

### Phase 0: I was the human run button

### Phase 1: Getting my command line into the browser.

I wrote a small webserver (see `flankserver.c` above) that starts a Bash process and 1) pipes POST bodies to stdin and 2) pipes the resulting stdout back into the POST response.

### Phase 2: Adding guardrails

I wrote a bash wrapper (see `iflank` above) that restricts the user to a sandboxed area in the filesystem. Also it restricts which commands users can run. 

### Phase 3: Turning the output into something that looks like a web app

I wrote a very simple parser on the website (see index.html above) that looks for keywords like “%PAGESTART%” and injects things into then DOM accordingly.
