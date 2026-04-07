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

#### Get it working

1. Click "Create Cmd" on the bottom bar
2. Choose the "Hello World" option
3. Remove the echo and paste in the following, and click "Save"

```bash
curl -X "${method}" "${url}"
```

You should see something like this:

#### Add guardrails

1. Click "Edit template.sh" on the bottom bar
2. Above the curl line, add the following decorations for `${method}` and `{url}`, and click "Save"

```bash
# @description This fetches the content from the URL
# ${method} @select @values `echo $'GET\nPOST\nPUT\nDELETE\nPATCH\nHEAD\nOPTIONS\nCONNECT\nTRACE'`
# ${url} @type url @colspan 4
curl -X "${method}" "${url}"
```

Now it should look something like this:

## The decoration API

Where possible, I've tried to mirror vanilla HTML and not add any more layers of abstraction than I'm already adding. As an example, to specify that a variable be represented by a `<textarea/>`, you use `@textarea`, but to specify radio buttons, you use `@input @type radio`, since radios are wrapped in an `<input/>`

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
````

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
| `@colspan` | number (1 - 6) | `2` (`6` for `@textarea`) | Grid column span. |
| `@description` | string | — | Small subtitle rendered beneath the variable name. |
| `@capturetab` | none | no | Tab key inserts a tab character instead of moving focus. |
| `@ignore` | none | no | Excludes the variable from the form entirely. |

## How it works under the hood

### Phase 0: I was the human run button

<img width="838" height="354" alt="Can you run that for me readme" src="https://github.com/user-attachments/assets/abcd5512-ee47-4780-9298-b4eaddcbda69" />

### Phase 1: Getting my command line into the browser.

I wrote a small webserver (see `flankserver.c` above) that starts a Bash process and 1) pipes POST bodies to stdin and 2) pipes the resulting stdout back into the POST response.

### Phase 2: Adding guardrails

I wrote a bash wrapper (see `iflank` above) that restricts the user to a sandboxed area in the filesystem. Also it restricts which commands users can run. 

### Phase 3: Turning the output into something that looks like a web app

I wrote a very simple parser on the website (see index.html above) that looks for keywords like “%PAGESTART%” and injects things into then DOM accordingly.
