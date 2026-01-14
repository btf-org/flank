# Flank Examples - R

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/R_logo.svg/1200px-R_logo.svg.png" width=75/>


- [Run on a recurring schedule](#run-an-r-script-on-a-schedule)
- [Build a pipeline](#build-a-pipeline-of-r-scripts)
- [Run with a lot of memory](#run-an-r-script-with-a-lot-of-memory)

<br>

# Examples

## Run an R script on a schedule

1. [Install Flank](#install-flank)
2. [Add your script to Flank](#add-your-script-to-flank)
3. [Parameterize your script](#parameterize-your-script)
4. Create a scheduled job
   1. Navigate to your script in Flank
   2. Click on "Create Cron" at the bottom

## Build a pipeline of R scripts
1. [Install Flank](#install-flank)
2. [Add 2 scripts to Flank](#add-your-script-to-flank)
3. [Parameterize your scripts](#parameterize-your-script)
4. Create a pipeline
   1. TBD

## Run an R script with a lot of memory
TODO

## Build a memory-intensive pipeline without Docker, Airflow, etc.
TODO

# Setup
## Install Flank

### Mac

```bash
brew tap btf-org/flank
brew install btf-org/flank/flank
brew services start flank
```

### Linux / Ubuntu / apt

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.60/flank_0.1.60_amd64.deb
sudo FLANK_USER=$(whoami) apt install ./flank_0.1.60_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time


## Update Flank

### Mac
```bash
brew update # should update all your "taps", including btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.60/flank_0.1.60_amd64.deb
sudo FLANK_USER=$(whoami) apt install ./flank_0.1.60_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time

# Guides

## Add Your Script to Flank

1. Go to the Flank website
2. Click on "Create Command" at the bottom
3. After naming your command, paste whatever you would run from the command line into the box, e.g. `Rscript myscript.R --arg1=hello` or `python myscript.py`.
4. [Parameterize your script](#parameterize-your-script)

## Parameterize your script

(If you're already in the process of adding your script, skip to #3)
1. Navigate to your command
2. Click on "Edit" at the bottom
3. Create parameterized values by substituting `%%varname%%`, e.g. if your CLI command is `Rscript myscript.R --arg1=hello` and you want to parameterize the "hello" part, change it to `Rscript myscript.R --arg1=%%arg1%%`

## Always run the latest version of a script

## Strategies for optimizing VM cost
