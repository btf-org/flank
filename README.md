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

## Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide]()]
- Schedule a script to run later (and view the logs afterwards) [[Guide]()]
- Customize the input fields to your script script [[Guide]()]

## Example of "Script-First" Development

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

#### The inputs are dynamically pulled from the "runner script"

#### Flank forwards `stdout` from your CLI to the browser

## An 80/20 Alternative

I use Flank as an 80/20 alternative to a wide-variety of cloud tools that are designed for a scale that, in practice, I rarely reach.*

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

<sub>\* When I say "Flank", "Flank" is really just a wrapper around (and interface on top of) the Unix toolset.</sub>


## Full Docs

- [Troubleshooting](/docs/not_written_yet.md)
- [Upgrading](/docs/not_written_yet.md)
- [More](/docs/not_written_yet.md)

## Contact

Shoot me an email at anguspmitchell@gmail.com
