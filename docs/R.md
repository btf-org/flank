# Flank Examples - R

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/R_logo.svg/1200px-R_logo.svg.png" width=75/>

- Quick Hitters
  - [Run a script on a schedule and view the logs](#run-an-r-script-on-a-schedule)
  - [Build a pipeline of scripts](#build-a-pipeline-of-r-scripts)
  - [Run a script with a lot of memory](#run-an-r-script-with-a-lot-of-memory)
- Guides
  - [Build a memory-intensive pipeline without Docker, Airflow, etc.](#build-a-memory-intensive-pipeline-without-docker-airflow-etc)

<br>

# Help

If you run into any problems, shoot me an email at anguspmitchell@gmail.com

# Examples

## Run an R script on a schedule

(Assuming your R script is already written and lives in file on your machine...)

1. **Install Flank** - [See here](#install-flank)
2. **Go to the Flank website** - This will be at http://localhost:8083 by default
3. **Add your script to Flank** - From the website , click on "Create Cmd" on the bottom bar
4. **Create a cron job** - If you're not already, drill into your newly created command and click on "Create Cron" on the bottom bar
5. **View Logs** - If you're not already, drill into your newly created command and click "History" on the bottom bar

**Next:** Always pull the latest version of the script from a repo

## Build a pipeline of R scripts

(Assuming your R scripts are already written and live in files on your machine...)

1. **Install Flank** - [See here](#install-flank)
2. **Go to the Flank website** - This will be at http://localhost:8083 by default
3. **Add two scripts to Flank** - From the website , click on "Create Cmd" on the bottom bar. Follow instructions and then repeat.
4. **Create a pipeline command** - From the website , click on "Create Pipeline" on the bottom bar.
5. **View Pipeline Status** - If you're not already, drill into your pipeline command and click "History" on the bottom bar

**Next:** Run the pipeline on a schedule

## Run an R script with a lot of memory
TODO

## Build a memory-intensive pipeline without Docker, Airflow, etc.
TODO

# Setup
## Install Flank

### Mac

(If you haven't installed Homebrew, [see here](https://brew.sh/))

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

## Always run the latest version of a script

## Strategies for optimizing VM cost
