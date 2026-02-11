# Flank

Flank makes your scripts more powerful. 

## ⚡️ Quickstart ⚡️

In the quickstart, you will run a script on your computer through Flank.

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

#### 3. Confirm that the Flank-generated "wrapper script" is correct

Flank will create a "wrapper script" that:

1. `cd`s into the directory of your script
2. If detected, activates your virtual environment
3. Runs your script

By following the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.js?edit), you'll be able to confirm that Flank filled these out correctly, and you can tweak if need be.

#### 4. Run your script and view output in the browser

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

#### 5. Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide](/docs/not_written_yet.md)]
- Schedule a script to run later (and view the logs afterwards) [[Guide](/docs/not_written_yet.md)]
- Customize the input fields to your script [[Guide](/docs/not_written_yet.md)]
  
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

#### 3. Confirm that the Flank-generated "wrapper script" is correct

Flank will create a "wrapper script" that:

1. `cd`s into the directory of your script
2. Runs your script

By following the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R?edit), you'll be able to confirm that Flank filled these out correctly, and you can tweak if need be.

#### 4. Run your script and view output in the browser

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

#### 5. Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide](/docs/not_written_yet.md)]
- Schedule a script to run later (and view the logs afterwards) [[Guide](/docs/not_written_yet.md)]
- Customize the input fields to your script [[Guide](/docs/not_written_yet.md)]
  
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

#### 3. Confirm that the Flank-generated "wrapper script" is correct

Flank will create a "wrapper script" that:

1. `cd`s into the directory of your script
2. Runs your script

By following the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.js?edit), you'll be able to confirm that Flank filled these out correctly, and you can tweak if need be.

#### 4. Run your script and view output in the browser

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

#### 5. Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide](/docs/not_written_yet.md)]
- Schedule a script to run later (and view the logs afterwards) [[Guide](/docs/not_written_yet.md)]
- Customize the input fields to your script [[Guide](/docs/not_written_yet.md)]
  
---

</details>


## Build a website from a script

Flank is a website that wraps your CLI.

When you add a script to Flank, Flank wraps your script with another script. Using this "wrapper script" as a template, Flank generates a website for running your script. And when you run it, the output appears in the browser.

#### Example: `city_filter.py`
```python
import pandas as pd
import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description='Filter data by city')
parser.add_argument('--city', default='New York', help='City to filter by')
args = parser.parse_args()

df = pd.DataFrame({
        'Name': ['Alice', 'Bob', 'Charlie', 'Diana', 'Edie', 'Frankie'],
        'Age': [25, 30, 35, 28, 58, 18],
        'City': ['New York', 'London', 'New York', 'Paris', 'London', 'New York']
})

filtered_df = df[df['City'] == args.city]
html_output = filtered_df.to_html(index=False)
print(html_output)
```

#### Example: The "wrapper script" generated by Flank

```bash
cd /Users/anguspmitchell/Workspace/data-proc/city-filter.py
. ./venv/bin/activate
python city-filter.py --city '${city}'
```

#### Example: Template page generated from the "wrapper script"

<img/>

#### Example: Flank forwards `stdout` from your CLI to the browser

<img/>

## Build a dashboard from a script

In the output of your script, you can include:

- HTML tables [[Guide](/docs/not_written_yet.md)]
- Data graphics [[Guide](/docs/not_written_yet.md)]
- Links to run other scripts (every script in Flank has a unique URL)  [[Guide](/docs/not_written_yet.md)]

In this way, you can build dashboards, reports, internal tools, and CRUD apps by just writing scripts.

## Automate with scheduling and pipelining

Through the Flank web app, you can set scripts to run on a schedule. 

- Run a script on a schedule [[Guide](/docs/not_written_yet.md)]
- Run a DAG of scripts in a pipeline [[Guide](/docs/not_written_yet.md)]

## When is Flank a BAD fit?

The main assumption behind Flank is writing scripts is fast for you, the developer. If scripts aren't fast for whatever reason -- e.g. maybe the dependencies in your codebase or the policies of your org mean that every little script has a huge overhead anyway -- then Flank won't offer much of a speedup.

| Design Decision | Bad Fits |
| ---------- | -------- |
| UI paradigm of input → output (~CLI) | ❌ Chatbots<br>❌ Map-based UIs<br>❌ Dashboards with distinct, side-by-side components |
| Barebones UI | ❌ Polished apps |
| Not hosted | ❌ It's easier to just connect your DB to a hosted app-builder |
| Browser UI | ❌ Offline applications<br>❌ Slackbots |
| No built-in multi-machine orchestration | ❌ Workload exceeds what a single machine can handle |
| System cron | ❌ Thousands of cron jobs<br>❌ To-the-millisecond cron precision |
| `make` for pipelines | ❌ Advanced pipelining (e.g. runtime dynamic graphs) |


## Full Docs

- [Troubleshooting](/docs/not_written_yet.md)
- [Upgrading](/docs/not_written_yet.md)
- [More](/docs/not_written_yet.md)

## Contact

If you have any questions, feel free to shoot me an email at anguspmitchell@gmail.com
