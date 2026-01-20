# Flank Examples - R

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/R_logo.svg/1200px-R_logo.svg.png" width=75/>

#### Quick Hitters
- [Run a script on a schedule (and view the logs)](/docs/run_script_on_schedule.md)
- [Build a pipeline of scripts](#build-a-pipeline-of-r-scripts)
- [Run a script with a lot of memory](#run-an-r-script-with-a-lot-of-memory)

#### Guides
  - [Build a memory-intensive pipeline without Docker, Airflow, etc.](#build-a-memory-intensive-pipeline-without-docker-airflow-etc)

<br>

## Help

If you run into any problems, shoot me an email at anguspmitchell@gmail.com

# Examples

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

## Always run the latest version of a script

## Strategies for optimizing VM cost
