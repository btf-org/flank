# Flank

Flank is a utility to help you manage your script runs. 

# Quickstart - Run a script

The first step is to run one of the scripts on your computer through Flank.

<details>
  <summary>strong>Python</strong></summary>

---

#### 1a. Install Flank (Mac)
```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### 1b. Install Flank (Linux)
```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### 2. Add your script to Flank

(Swap out `myscript.py` for whatever your script name is)

```
iflank add myscript.py
```

#### 3. Finish configuration

Follow the link outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.py).

#### 4. Run it!

Once you've run a script through Flank, check out some of the possible next steps below.

---

</details>

<details>
  
  <summary><strong>R</strong></summary>

---

#### 1a. Install Flank (Mac)
```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### 1b. Install Flank (Linux)

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### 2. Add your script to Flank

(Swap out `myscript.R` for whatever your script name is)

```
iflank add myscript.R
```

#### 3. Finish configuration

Follow the link outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R).

#### 4. Run it!

Once you've run a script through Flank, check out some of the possible next steps below.

---

</details>

# Possible Next Steps

- Use your phone to run a script away from your desk [[Guide]()]
- Schedule a script to run later (and view logs afterwards) [[Guide]()]
- Put a hyperlink to a script execution in some other documentation [[Guide]()]

# 80/20 Replacement For...

<details>
  
  <summary>BI Tools</summary>

---

Todo

---

</details>

<details>
  
  <summary>Orchestration Tools</summary>

---

Todo

---

</details>

<details>
  
  <summary>Internal Websites</summary>

---

Todo

---

</details>

<details>
  
  <summary>Serverless Functions</summary>

---

Todo

---

</details>

# How do you use it?

Flank works like the command line. You run commands, and you view output.

<img width="2600" height="2132" alt="Screenshot 2026-01-28 at 10 59 30 AM" src="https://github.com/user-attachments/assets/894fc7f6-da7e-4e63-a124-42dff7f6693f" />


# Language-by-Language Examples

| Language | Examples |
|:--------:|----------|
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/R_logo.svg/1200px-R_logo.svg.png" width=75/> | [R Examples](/docs/not_written_yet.md) |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/1200px-Python-logo-notext.svg.png" width=60/> | [Python Examples](/docs/not_written_yet.md) |
| <img src="https://upload.wikimedia.org/wikipedia/commons/d/d9/Node.js_logo.svg" width=80/> | [Node Examples](/docs/not_written_yet.md) |
| <img src="https://rust-lang.org/logos/rust-logo-512x512.png" width=60/> | [Rust Examples](/docs/not_written_yet.md) |
| <img src="https://logonoid.com/images/sql-server-logo.png" width=80/>| [SQL Server Examples](/docs/not_written_yet.md) |
| <img src="https://images.icon-icons.com/2415/PNG/512/postgresql_plain_wordmark_logo_icon_146390.png" width=70/> | [Postgres Examples](/docs/not_written_yet.md) |

# Systems built with Flank so far

Flank seems to have found the most utility with engineers who are really handy with one language and are frustrated with the constellation of "auxiliary tooling" that's needed to accomplish simple tasks these days. 

| Engineer | is handy with... | and wants to... | but is frustrated by... |
|----------|------------------|----------------------|-----------------|
| Tim | SQL Server | Expose SQL queries to business folks | BI tools |
| Rob | Python Lambdas | Run scripts away from his desk | AWS Console |
| Nik | R | Schedule his scripts in a pipeline | Orchestration tools |


# Full Docs

- [Troubleshooting](/docs/not_written_yet.md)
- [Upgrading](/docs/not_written_yet.md)
- [More](/docs/not_written_yet.md)

# Contact

Shoot me an email at anguspmitchell@gmail.com
