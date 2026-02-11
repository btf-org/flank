# Flank

Flank makes your scripts more powerful. 

## ⚡️ Quickstart ⚡️

In the quickstart, you will turn one of your scripts into a web UI. Then you can run it from your browser or your phone.

<details>
  <summary>Python</summary>

---

#### 1a. Install Flank (Mac)

_In this step, Homebrew installs a webserver and a program that wraps your CLI. Then it starts the webserver, running as the user who's logged into the shell._

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### 1b. Install Flank (Linux)

_In this step, apt installs a webserver and a program that wraps your CLI. It automatically starts the webserver, and uses `whoami` to run it as the current user rather than root._

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### 2. Add your script to Flank

_In this step, Flank will create a "wrapper script" that 1) `cd`s into the directory of your script, 2) if detected, activates your virtual environment, and 3) runs your script. The wrapper script lives on your computer like any other file, in a folder set up by Flank._

(Swap out `myscript.py` for whatever your script name is)

```
iflank add myscript.py
```

#### 3. Confirm that the Flank-generated "wrapper script" is correct

_In this step, you'll edit a file on your computer through the Flank web app, but you could also edit the same file through a text editor._

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.py?edit)
2. Confirm that Flank created the correct instructions to run your script.

#### 4. Run your script and view output in the browser

_In this step, Flank is calling the "wrapper script" under the hood._

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

_In this step, Homebrew installs a webserver and a program that wraps your CLI. Then it starts the webserver, running as the user who's logged into the shell._

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### 1b. Install Flank (Linux)

_In this step, apt installs a webserver and a program that wraps your CLI. It automatically starts the webserver, and uses `whoami` to run it as the current user rather than root._

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### 2. Add your script to Flank

_In this step, Flank will create a "wrapper script" that 1) `cd`s into the directory of your script and 2) runs your script. The wrapper script lives on your computer like any other file, in a folder set up by Flank._

(Swap out `myscript.R` for whatever your script name is)

```
iflank add myscript.R
```

#### 3. Confirm that the Flank-generated "wrapper script" is correct

_In this step, you'll edit a file on your computer through the Flank web app, but you could also edit the same file through a text editor._

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R?edit)
2. Confirm that Flank created the correct instructions to run your script.

#### 4. Run your script and view output in the browser

_In this step, Flank is calling the "wrapper script" under the hood._

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

_In this step, Homebrew installs a webserver and a program that wraps your CLI. Then it starts the webserver, running as the user who's logged into the shell._

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### 1b. Install Flank (Linux)

_In this step, apt installs a webserver and a program that wraps your CLI. It automatically starts the webserver, and uses `whoami` to run it as the current user rather than root._

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### 2. Add your script to Flank

_In this step, Flank will create a "wrapper script" that 1) `cd`s into the directory of your script and 2) runs your script. The wrapper script lives on your computer like any other file, in a folder set up by Flank._

(Swap out `myscript.js` for whatever your script name is)

```
iflank add myscript.js
```

#### 3. Confirm that the Flank-generated "wrapper script" is correct

_In this step, you'll edit a file on your computer through the Flank web app, but you could also edit the same file through a text editor._

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.js?edit)
2. Confirm that Flank created the correct instructions to run your script.

#### 4. Run your script and view output in the browser

_In this step, Flank is calling the "wrapper script" under the hood._

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

#### 5. Next Steps

Here are some possible next steps:

- Use your phone to run a script away from your desk [[Guide](/docs/not_written_yet.md)]
- Schedule a script to run later (and view the logs afterwards) [[Guide](/docs/not_written_yet.md)]
- Customize the input fields to your script [[Guide](/docs/not_written_yet.md)]
  
---

</details>


## Build a website from a script

When you add a script to Flank, Flank wraps your script with another script (see example below).

Using this "wrapper script" as a template, Flank generates a website for running your script. When you click "run", your script's output appears in the browser.

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

<img width="600" alt="Screenshot 2026-02-11 at 5 04 09 PM" src="https://github.com/user-attachments/assets/195718fb-832c-4a3d-b81c-26b55482cb58" />


#### Example: Flank forwards `stdout` from your CLI to the browser

<img width="600" alt="Screenshot 2026-02-11 at 5 04 32 PM" src="https://github.com/user-attachments/assets/affb410b-f1dc-45b7-a8bb-b87cc3c4d141" />

## Make a dashboard or an internal tool

Flank forwards the `stdout` from your CLI to the browser. By putting more interesting stuff in the output of your script, you can build more interesting tools...

- HTML tables [[Guide](/docs/not_written_yet.md)]
- Data graphics [[Guide](/docs/not_written_yet.md)]
- Links to run other scripts (every script in Flank has a unique URL)  [[Guide](/docs/not_written_yet.md)]

In this way, you can build dashboards, reports, internal tools, and CRUD apps by just writing scripts.

## Automate with scheduling and pipelining

Flank is really two programs: 1) an inner program that wraps the CLI, 2) a web interface on top of that wrapper. Together, they make it easy to use certain CLI features. Two such examples are scheduling and pipelining. 

- Run a script on a schedule [[Guide](/docs/not_written_yet.md)]
- Run a DAG of scripts in a pipeline [[Guide](/docs/not_written_yet.md)]

## When is Flank a BAD fit?

The main assumption behind Flank is that writing scripts is faster than writing backend code + building an interface. But depending on your skillset, existing scaffolding, or company policies, that may not be the case.

There are also certain design decisions that necessarily make certain problems a bad fit:

| Design Decision | Bad Fits |
| ---------- | -------- |
| Interaction = input → output | ❌ Chatbots<br>❌ Map-based UIs<br>❌ Dashboards with distinct, side-by-side components |
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
