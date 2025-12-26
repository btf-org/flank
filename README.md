# Flank
I'm a data analytics consultant, and I built the following to speed up my work. I use it for everything from BI to internal tools to setting up pipelines.

### Examples
- R
  - [Run an R script on a schedule](#run-an-r-script-on-a-schedule)
  - Build a pipeline of R scripts

### Case Studies
- [Building a data pipeline without Docker, Airflow, etc.](#building-a-data-pipeline-without-docker-airflow-etc)

# Examples
## Run an R script on a schedule
1. [Install Flank](#install-flank)
2. [Start Flank](#start-flank)
3. [Add your script to Flank](#add-your-script-to-flank)
4. Schedule exeuction of script through Flank website

# Case Studies
## Building a data pipeline without Docker, Airflow, etc.

## Install Flank

### Mac

```bash
brew tap btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu / apt

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time


## Start Flank

```bash
flank start
```

## Update Flank

### Mac
```bash
brew update # should update all your "taps", including btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time

## Add Your Script to Flank

1. Run the following command
  ```bash
  flank add helloWorld.R
  
  # Example output:
  # localhost:8083/helloWorld.R
  ```
2. Add parameters in Flank
   - Go to URL outputted above
   - Click on "Edit" at the bottom
