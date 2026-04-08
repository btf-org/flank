# Flank

Flank is a tool for exposing shell commands with guardrails. 

<img width="838" height="524" alt="curl-ex" src="https://github.com/user-attachments/assets/44d54306-c60c-400e-93e8-98ab6dfb0483" />


## Contents 

- [Caveats / Limitations](#caveats--limitations)
- [Installation](#installation)
- [A quick webpage for curl](#a-quick-webpage-for-curl)
- [The decoration API](#the-decoration-api)

## Caveats / Limitations

- As it currently stands, users can write destructive shell scripts, so beware! I am currently using this is in a small team, high-trust environment, so I haven't invested any effort into RBAC.
- The logic in flankserver.c is pretty unpolished. I'm pretty sure if you open 64 tabs, it'll just crash the server. A lot of these problems have been masked by systemctl's automatic restart behavior...

  
## Installation

#### Mac

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && { nohup $(which flankserver) >> $(brew --prefix)/var/log/flank/flankserver.log 2>> $(brew --prefix)/var/log/flank/flankserver.err & } && sleep 1 && open http://localhost:8083
```

#### Linux

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.81/flank_0.1.81_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.81_amd64.deb
```

Served on port 8083

## A quick webpage for `curl`

### First, get it working

1. Click "Create Cmd" on the bottom bar
2. Choose the "Hello World" option
3. Remove the `echo`, paste in the following, and click "Save"

```bash
curl -X "${method}" "${url}"
```

You should see something like this:

<img width="838" height="550" alt="curl-ex-1" src="https://github.com/user-attachments/assets/553e1a6b-a24a-448f-b2db-4b62a2ad0345" />


### Then, add guardrails

1. Click "Edit template.sh" on the bottom bar
2. Above the `curl` line, add the following decorations for `${method}` and `${url}`, and click "Save"

```bash
# @description This fetches the content from the URL
# ${method} @select @values `echo $'GET\nPOST\nPUT\nDELETE\nPATCH\nHEAD\nOPTIONS\nCONNECT\nTRACE'`
# ${url} @type url @colspan 4

curl -X "${method}" "${url}"
```

Now the page should look something like this:

<img width="838" height="550" alt="curl-ex-2" src="https://github.com/user-attachments/assets/3d95bdcf-e984-4768-a9aa-fa96524ca667" />


## The decoration API

First, a variable needs to be wrapped in the curly bracket notation, ${}, to get picked up by Flank. Then, you can add guardrails through various decorations (see below).

Where possible, I've tried to mirror vanilla HTML and not add any additional naming conventions. As an example, to specify that a variable be represented by a `<textarea/>`, you use `@textarea`, but to specify it be represented by radio buttons, you use `@input @type radio`, since radios are `<input type="radio"/>`.

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
