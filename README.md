# Flank

Flank is a utility to help you manage your script runs. 

## ⚡️ Quickstart ⚡️

The first step is to **run a script on your computer** through Flank.

<details>
  <summary>Python</summary>

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
  
  <summary>R</summary>

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

<details>
  
  <summary>Other Languages</summary>

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

(Swap out `myscript.js` for whatever your script name is)

```
iflank add myscript.js
```

#### 3. Finish configuration

Follow the link outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.js).

#### 4. Run it!

Once you've run a script through Flank, check out some of the possible next steps below.

---

</details>

## Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide](/docs/not_written_yet.md)]
- Schedule a script to run later (and view the logs afterwards) [[Guide](/docs/not_written_yet.md)]
- Customize the input fields to your script script [[Guide](/docs/not_written_yet.md)]

## Script-Driven Development

Flank automatically builds UI for running your scripts. And then it shows the output in a browser.

So, instead of building a website to show a table, you could make your Python script return HTML, and then run that script through Flank.

#### Example: Python script that outputs HTML
```python
import pandas as pd
import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description='Filter data by city')
parser.add_argument('--city', default='New York', help='City to filter by')
args = parser.parse_args()

df = pd.DataFrame({
    'Name': ['Alice', 'Bob', 'Charlie', 'Diana'],
    'Age': [25, 30, 35, 28],
    'City': ['New York', 'London', 'New York', 'Paris']
})

filtered_df = df[df['City'] == args.city]
filtered_df.to_html('output.html', index=False)
print(f"Generated table for {args.city}: {len(filtered_df)} rows")
```

#### The "runner" script that Flank generates and you tweak

```bash
```

#### The inputs are dynamically pulled from the "runner script"

<img/>

#### Flank forwards `stdout` from your CLI to the browser

<img/>

## The Anti-Pitch

Flank is an 80/20 tool. If your primary use cases lie outside the 80% of common use cases, you should probably use another tool.

More details:

<details>
  
  <summary><strong>Reporting / Dashboards</strong> (vs. Tableau, Looker, Metabase, etc.)</summary>

---

Todo

---

</details>

<details>
  
  <summary><strong>Internal Tools</strong> (vs. Retool, custom apps, React)</summary>
  <br>
Don't use Flank if:

- **The complexity of your app lies in the UI/UX**
- **Polished UI/UX is more important than developer efficiency**

</details>
 
<details>
  
  <summary><strong>Scheduling / Pipelines</strong> (vs. Airflow, Step Functions, etc.)</summary>

---

Todo

---

</details>

<details>
  
  <summary><strong>Deploying Scripts to the Cloud</strong> (vs. Lambda, Cloud Functions, containers)</summary>

---

Todo

---

</details>


## Full Docs

- [Troubleshooting](/docs/not_written_yet.md)
- [Upgrading](/docs/not_written_yet.md)
- [More](/docs/not_written_yet.md)

## About the project



Shoot me an email at anguspmitchell@gmail.com
