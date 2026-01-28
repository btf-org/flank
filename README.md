# Flank

Flank is a utility to help you manage your script runs. 

# Quickstart - Hello World

1. Install Flank
2. Go to the website
3. Click on `Quickstarts` folder

#### Mac
```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank && open http://localhost:8083
```

#### Linux / Ubuntu / apt
```
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

# How do you use it?

Flank is basically a thin web wrapper around the command line


# Language-by-Language Examples

| Language | Examples |
|:--------:|----------|
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/R_logo.svg/1200px-R_logo.svg.png" width=75/> | [R Examples](/docs/not_written_yet.md) |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/1200px-Python-logo-notext.svg.png" width=60/> | [Python Examples]() |
| <img src="https://upload.wikimedia.org/wikipedia/commons/d/d9/Node.js_logo.svg" width=80/> | [Node Examples]() |
| <img src="https://rust-lang.org/logos/rust-logo-512x512.png" width=60/> | [Rust Examples]() |
| <img src="https://logonoid.com/images/sql-server-logo.png" width=80/>| [SQL Server Examples]() |
| <img src="https://images.icon-icons.com/2415/PNG/512/postgresql_plain_wordmark_logo_icon_146390.png" width=70/> | [Postgres Examples]() |

# How has it been used so far?

So far, the pattern seems to be: \[Some engineer\] is handy with \[some programming language\] and wants to do \[some simple thing\] but is frustrated by the complexity of \[the current way of doing that thing\]

| Engineer | is handy with... | and wants to... | but is frustrated by... |
|----------|------------------|----------------------|-----------------|
| Tim | SQL Server | Expose SQL queries to business folks | BI tools |
| Rob | Python Lambdas | Run scripts away from his desk | AWS Console |
| Nik | R | Run his scripts in a pipeline | Orchestration tools |


# Full Docs

- [Troubleshooting](/docs/not_written_yet.md)
- [Upgrading](/docs/not_written_yet.md)
- [More](/docs/not_written_yet.md)

# Contact

Shoot me an email at anguspmitchell@gmail.com
